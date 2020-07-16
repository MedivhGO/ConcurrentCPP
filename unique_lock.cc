#include <iostream>
#include <mutex>
std::mutex mlock;
class some_big_object;
void swap(some_big_object& lhs,some_big_object& rhs);
class X
{
    private:
        some_big_object some_detail;
        std::mutex m;
    public:
        X(some_big_object const& sd): some_detail(sd){}
        friend void swap(X& lhs,X& rhs)
        {
            if(&lhs == &rhs)
                return;
            std::unique_lock<std::mutex> lock_a(lhs.m,std::defer_lock);
            std::unique_lock<std::mutex> lock_b(rhs.m,std::defer_lock);
            std::lock(lock_a,lock_b);
            swap(lhs.some_detail,rhs.some_detail);
        }
};
void work1(int& s)
{
    for (int i=1;i<=5000;i++)
    {
        std::unique_lock<std::mutex> munique(mlock,std::try_to_lock);//效率会比lock_guard低一些
        //std::adopt_lock表示互斥量已经被lock，不需要再重复lock,该互斥量必须已经lock才能使用该参数
        //std::try_to_lock可以避免一些不必要的等待，会判断当前mutex能否被lock,如果不能被lock，可以先去
        //执行其他代码。这个和adopt不同，不需要自己提前加锁。
        //std::defer_lock这个参数表示暂时先不lock，之后在手动lock,但是使用之前也是不允许lock的，当使用了
        //defer_lock参数时，在创建了unique_lock的对象时就不会自动加锁，那么就需要借助lock这个成员函数来
        //进行手动加锁，当然也有unlock来手动解锁。这个和mutex的lock和unlock使用方法一样。
        //release函数，解除unique_lock和mutex对象的联系，并将原mutex对象的指针返回出来。如果之前的
        //mutex已经加锁，需在后面自动unlock解锁。
        if (munique.owns_lock()==true){
            s+=i;
        }
        else{
            do_some_thing();
        }
    }
}
void work2(int& s)
{
    for(int i=5001;i<=10000;i++){
        std::unique_lock<std::mutex> munique(mlock,std::try_to_lock);
        if(munique.own_lock()==true){
            s+=i;
        }
        else{
            do_some_thing();
        }
    }
}
std::unique_lock<std::mutex> munique1(mlock);
std::unique_lock<std::mutex> munique2(std::move(munique1));
int main()
{
    int ans=0;
    std::thread t1(work1,std::ref(ans));
    std::thread t2(work2,std::ref(ans));
    t1.join();
    t2.join();
    std::cout << ans << std::endl;
    return 0;
}

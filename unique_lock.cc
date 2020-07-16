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
        std::unique_lock<std::mutex> munique(mlock,std::try_to_lock);
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

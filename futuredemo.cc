#include <iostream>
#include <future>
/*
int find_the_answer_to_ltuae();
void do_other_stuff();
int main()
{
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout << "The answer is " << the_answer.get() << std::endl;
}
*/
#include <thread>
// std::promise常配合std::future使用。其作用是在一个线程中保存一个类型的值，可供相绑定的std::future对象在另一个线程中获取。
int main()
{
    std::packaged_task<int()> task([]{return 7;});
    std::future<int> f1 = task.get_future();
    std::thread t(std::move(task));

    std::future<int> f2 = std::async(std::launch::async,[]{return 8;});

    std::promise<int> p; // 声明一个promise对象p，其保存的值的类型为int
    std::future<int> f3 = p.get_future(); // 声明一个std::future对象f3，并通过std::promise的get_future()函数与p绑定
    std::thread([&p]{p.set_value_at_thread_exit(9);}).detach();

    std::cout << "Waiting..." << std::flush;

    f1.wait();
    f2.wait();
    f3.wait();

    std::cout << "Done!\n Result are:"
    << f1.get() << ' ' << f2.get() << ' ' <<f3.get() << '\n';

    t.join();

}

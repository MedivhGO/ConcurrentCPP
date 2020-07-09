#include <iostream>
#include <thread>

void hello()
{
   std::cout << "Hello Concurrent World\n"
    << std::this_thread::get_id() << std::endl;
}
int main()
{
    std::thread t(hello);
    std::cout << t.get_id() << std::endl;
    t.join();
}

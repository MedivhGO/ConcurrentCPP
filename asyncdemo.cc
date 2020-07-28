#include <string>
#include <future>

struct X
{
    void foo(int,std::string const&);
    std::string bar(std::string const&);
};
X x;
atuo f1 = std::async(&X::foo,&x,42,"hello");
auto f2 = std::async(&X::bar,x,"goodbye");
struct Y
{
    double operator()(double);
}
Y y;
auto f3 = std::async(Y(),3.141);
auto f4 = std::async(std::ref(y),2.718);
X baz(X&);
std::async(baz,std::ref(x));
class move_only
{
    public:
        move_only();
        move_only(move_only&&);
        move_only(move_only const&) = delete;
        move_only& move_only(move_only&&);
        move_only& move_only(move_only const&) = delete;
        void operator()();
};
auto f5 = std::async(move_only());
//可以在async中第一个参数传入std::launch::async来立刻执行该异步任务
//或者传入std::launch::deferred当结果被需要时执行该异步任务

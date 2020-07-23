double square_root(double x)
{
    if (x < 0)
    {
        throw std::out_of_range("x<0");
    }
    return sqrt(x);
}

double y=square_root(-1);
std::future<double> f = std::async(square_root,-1);
double y = f.get();

extern std::promise<double> some_promise;
try
{
    some_promise.set_value(calculate_value());
}
catch(...)
{
    some_promise.et_exception(std::current_exception());
}
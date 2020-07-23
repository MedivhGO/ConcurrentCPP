//如果需要多余一个的线程等待同一个事件，则需要使用std::shared_future来替代
std::promise<int> p;
std::future<int> f(p.get_future());
assert(f.valid);
std::shared_future<int> sf(std::move(f));
assert(!f.valid());
assert(sf.valid());

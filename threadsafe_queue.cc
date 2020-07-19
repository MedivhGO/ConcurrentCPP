#include <memory>

template<typename T>
class threadsafe_queue
{
public:
    threadsafe_queue();
    threadsafe_queue(threadsafe_queue &&) = default;
    threadsafe_queue(const threadsafe_queue &) = default;
    threadsafe_queue &operator=(threadsafe_queue &&) = delete;
    threadsafe_queue &operator=(const threadsafe_queue &) = delete;
    ~threadsafe_queue();

    void push(T new_value);
    bool try_pop(T& value);
    std::shared_ptr<T> tyr_pop();

    void wait_and_pop(T& value);
    std::shared_ptr<T> wait_and_pop();

    bool empty() const;

private:

};

threadsafe_queue::threadsafe_queue()
{
}

threadsafe_queue::~threadsafe_queue()
{
}
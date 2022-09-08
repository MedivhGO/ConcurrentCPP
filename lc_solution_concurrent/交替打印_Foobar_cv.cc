class FooBar {
  private:
    int n;
    int flag;
    mutex mut;
    condition_variable connd;

  public:
    FooBar(int n) {
        this->n = n;
        flag = 0;
    }
    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lck(mut);
            cond.wait(lck, [this]() { return flag == 0; });
            printFoo();
            flag = 1;
            cond.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lck(mut);
            cond.wait(lck, [this]() { return flag == 1; });
            printBar();
            flag = 0;
            cond.notify_one();
        }
    }
};
class ZeroEvenOdd {
  private:
    int n;
    int cur;
    std::mutex m;
    std::condition_variable cond;
    int flag = 1;
    int oflag = 0;
    int eflag = 0;

  public:
    ZeroEvenOdd(int n) { this->n = n; }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            unique_lock<std::mutex> lk(m);
            cond.wait(lk, [this]() { return flag && !oflag && !eflag; });
            printNumber(0);
            flag = 0;
            if (i % 2 == 0) {
                eflag = 1;
                oflag = 0;
            } else {
                eflag = 0;
                oflag = 1;
            }
            cond.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {

        for (int i = 2; i <= n; i += 2) {
            unique_lock<std::mutex> lk(m);
            cond.wait(lk, [this]() { return !flag && !oflag && eflag; });
            printNumber(i);
            flag = 1;
            oflag = 0;
            eflag = 0;
            cond.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {
            unique_lock<std::mutex> lk(m);
            cond.wait(lk, [this]() { return !flag && oflag && !eflag; });
            printNumber(i);
            flag = 1;
            eflag = 0;
            oflag = 0;
            cond.notify_all();
        }
    }
};
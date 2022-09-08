class H2O {

  public:
    H2O() {}
    void hydrogen(function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lk(m);
        cond.wait(lk, [this]() { return h_count < 2; });
        releaseHydrogen();
        h_count++;
        if (h_count + o_count == 3) {
            h_count = 0;
            o_count = 0;
        }
        cond.notify_all();
    }
    void oxygen(function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lk(m);
        cond.wait(lk, [this] { return o_count < 1; });

        releaseOxygen();
        o_count++;

        if (h_count + o_count == 3) {
            h_count = 0;
            o_count = 0;
        }
        cond.notify_all();
    }

  private:
    std::mutex m;
    std::condition_variable cond;
    int h_count = 0;
    int o_count = 0;
};

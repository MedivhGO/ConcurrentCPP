#include <condition_variable>
#include <iostream>
#include <mutex>

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread() {
    while (more_data_to_prepare()) {
        data_chunk const data = prepare_data();
        std::lock_guard<std::mutex> lk(mut); //锁定共享队列
        data_queue.push(data);
        data_cond.notify_one(); //通知等待中的线程 通知wait处阻塞的线程进行进行条件检查
    }
}
void data_processing_thread() {
    while (true) {
        std::unique_lock<std::mutex> lk(mut); //锁定共享队列
        data_cond.wait(
            lk, [] { return !data_queue.empty(); }); // wait条件如果为false就会阻塞,true会解除阻塞
                                                     // 因为阻塞时需要解锁互斥量,所以使用unique_lock(提供更多的灵活性)
        data_queue.pop();
        lk.unlock();
        process(data);
        if (is_last_chunk(data))
            break;
    }
}
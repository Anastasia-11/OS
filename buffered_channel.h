#ifndef OS_LAB2_BUFFERED_CHANNEL_H
#define OS_LAB2_BUFFERED_CHANNEL_H

#include <queue>
#include <mutex>

template <typename T>
class BufferedChannel {
private:
    std::mutex                      lockQueue;
    std::condition_variable         recvCheck;
    std::condition_variable         sendCheck;
    std::queue<T>                   queue;
    unsigned int                    bufferSize;
    bool                            isOpen;

public:
    BufferedChannel() : BufferedChannel(10) {}

    BufferedChannel(const unsigned int& size)
    : bufferSize(size), isOpen(true) {}

    void Send(const T& value) {
        if(!isOpen) {
            throw std::runtime_error("channel is closed!");
        }

        std::unique_lock<std::mutex> locker(lockQueue);
        sendCheck.wait(locker, [this](){return queue.size() != bufferSize || isOpen;});

        queue.push(value);
        locker.unlock();
        recvCheck.notify_one();
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> locker(lockQueue);
        recvCheck.wait(locker, [this](){return !queue.empty() || !isOpen;});

        T value = queue.front();
        queue.pop();
        locker.unlock();
        sendCheck.notify_one();
        return std::pair(value, isOpen);
    }

    void Close() {
        std::unique_lock<std::mutex> locker(lockQueue);
        isOpen = false;
        locker.unlock();
        recvCheck.notify_one();
        sendCheck.notify_one();
    }
};

#endif //OS_LAB2_BUFFERED_CHANNEL_H

#pragma once


#include <thread>
#include <chrono>
/*!
 * Thread method
 */

class IThread
{
public:
    IThread();

    void start();
    void join();
    void sleep(int milliseconds);

    virtual bool ThreadMethod() = 0;
    bool mIsRunning;

private:
    std::thread mThread;
    static int ThreadProxy(void* ptr);
};
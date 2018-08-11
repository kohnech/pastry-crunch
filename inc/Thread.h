#pragma once


#include <thread>
/*!
 * Thread method
 */

class IThread
{
public:
    IThread();

    void start();
    void join();

    virtual bool ThreadMethod() = 0;
    bool mIsRunning;

private:
    std::thread mThread;
    static int ThreadProxy(void* ptr);
};
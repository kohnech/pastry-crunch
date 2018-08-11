#pragma once


#include <thread>
/*!
 * Thread method
 */

class Thread
{
public:
    Thread();

    void start();
    void join();

    virtual bool ThreadMethod() = 0;
    bool mIsRunning;

private:
    std::thread mThread;
    static int ThreadProxy(void* lpParam);
};
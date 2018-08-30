#pragma once

#include <thread>
/*!
 * Thread method
 */

class IThread
{
public:
    IThread();
	virtual ~IThread() = default;
	IThread(const IThread& arg) = delete;
	IThread& operator=(const IThread& arg) = delete;
	IThread(IThread &&) = delete;
	IThread & operator=(IThread &&) = delete;

    void start();
    void join();
    static void sleep(int milliseconds);

    virtual bool ThreadMethod() = 0;
    bool mIsRunning;

    bool getRunningState() const;

private:
	std::thread mThread;
    static int ThreadProxy(void* ptr);
};
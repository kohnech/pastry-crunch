#include "IThread.h"

#include <iostream>

IThread::IThread()
{
}

void IThread::start()
{
    std::cout << "IThread start..." << std::endl;
    mThread = std::thread(ThreadProxy, this);
}

void IThread::join()
{
    std::cout << "IThread join..." << std::endl;
    try
    {
        mThread.join();
    }
    catch (const std::system_error& e)
    {
        std::cerr << "Caught system_error with code " << e.code() << " meaning " << e.what() << '\n';
    }
}

void IThread::sleep(int milliseconds)
{
    std::cout << "IThread sleep..." << std::endl;
    try
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
    catch (const std::system_error& e)
    {
        std::cerr << "Caught system_error with code " << e.code() << " meaning " << e.what() << '\n';
    }
}

int IThread::ThreadProxy(void* ptr)
{
    std::cout << "ThreadProxy..." << std::endl;
    if (ptr == NULL)
    {
        return EXIT_FAILURE;
    }
    std::string threadName;

    try
    {
        IThread* pThread = static_cast<IThread*>(ptr);
        if (pThread != NULL)
        {
            pThread->mIsRunning = true;
            pThread->ThreadMethod();
            pThread->mIsRunning = false;
        }
        return EXIT_SUCCESS;
    }

    catch (...)
    {
        std::cerr << "Unhandled exception!" << std::endl;
    }
    return EXIT_FAILURE;
}

bool IThread::getRunningState() const
{
    return mIsRunning;
}

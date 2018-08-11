#include "Thread.h"

#include <iostream>

Thread::Thread() {
}

void Thread::start() {
    mThread = std::thread(ThreadProxy, this);
}

void Thread::join() {
    mThread.join();
}

int Thread::ThreadProxy(void* lpParam) {
    std::string threadName;
    //int dwWorkingThreadId = 0;
    try {
        Thread *pThread = static_cast<Thread *>(lpParam);
        if (pThread != NULL) {
            pThread->mIsRunning = true;
            //dwWorkingThreadId = pThread->GetWorkingThreadId();
            //pThread->GetThreadName(threadName);
            pThread->ThreadMethod();
            pThread->mIsRunning = false;
        }
        return EXIT_SUCCESS;
    }

    catch (...) {
        std::cout << "Unhandled exception!" << std::endl;
    }
    return EXIT_FAILURE;
}
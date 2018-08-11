#include "IThread.h"

#include <iostream>

IThread::IThread() {
}

void IThread::start() {
    mThread = std::thread(ThreadProxy, this);
}

void IThread::join() {
    mThread.join();
}

void IThread::sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int IThread::ThreadProxy(void* ptr) {
    if (ptr == NULL)
    {
        return EXIT_FAILURE;
    }

    std::string threadName;

    try {
        IThread *pThread = static_cast<IThread *>(ptr);
        if (pThread != NULL) {
            pThread->mIsRunning = true;
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

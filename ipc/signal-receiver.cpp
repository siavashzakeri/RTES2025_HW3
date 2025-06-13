// -------------------------------------------
// signal-receiver.cpp
// g++ -std=c++17 signal-receiver.cpp -o signal-receiver
// -------------------------------------------
#include <csignal>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include <ctime>

std::ofstream logFile;

std::string now()
{
    std::time_t t = std::time(nullptr);
    std::tm     tm{};
    localtime_r(&t, &tm);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%F %T");
    return oss.str();
}

void signalHandler(int sig)
{
    const char *name = strsignal(sig);                    
    std::cout << "Received signal: " << sig
              << " (" << (name ? name : "unknown") << ")\n"
              << std::flush;

    logFile << '[' << now() << "] "
            << "Signal " << sig << " (" << (name ? name : "unknown") << ')'
            << std::endl;
}


void registerHandlers()
{
    for (int s = 1; s < NSIG; ++s)
    {
        if (s == SIGKILL || s == SIGSTOP) continue;       
        std::signal(s, signalHandler);
    }
}

int main()
{
    std::cout << "PID: " << getpid() << '\n'
              << "Waiting for signals...\n" << std::flush;

    logFile.open("signals.log", std::ios::app);
    if (!logFile)
    {
        std::perror("log open");
        return 1;
    }

    registerHandlers();

    while (true) pause();
}


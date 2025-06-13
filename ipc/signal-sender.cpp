// -------------------------------------------
// signal-sender.cpp
// g++ -std=c++17 signal-sender.cpp -o signal-sender
// -------------------------------------------
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <unistd.h>

void printCommonSignals()
{
    struct Pair { int num; const char* name; };
    Pair tbl[] = {
        {1,"SIGHUP"}, {2,"SIGINT"},  {3,"SIGQUIT"}, {9,"SIGKILL"},
        {10,"SIGUSR1"},{12,"SIGUSR2"},{15,"SIGTERM"},{17,"SIGCHLD"},
        {18,"SIGCONT"},{19,"SIGSTOP"},{20,"SIGTSTP"}
    };
    std::cout << "Common signals:\n";
    for (const auto &p : tbl)
        std::cout << std::left << std::setw(4) << p.num << '=' << p.name << ", ";
    std::cout << "\n\n";
}

int main(int argc, char* argv[])
{
    pid_t pid{};
    int   sig{};

    if (argc == 3)
    {
        pid = std::stoi(argv[1]);
        sig = std::stoi(argv[2]);
    }
    else
    {
        printCommonSignals();
        std::cout << "Enter PID: ";
        std::cin  >> pid;
        std::cout << "Enter signal number (e.g., 9 for SIGKILL): ";
        std::cin  >> sig;
    }

    if (pid <= 0 || sig <= 0 || sig >= NSIG)
    {
        std::cerr << "Invalid PID or signal number.\n";
        return 1;
    }

    if (::kill(pid, sig) == -1)
    {
        std::perror("kill");
        return 1;
    }

    std::cout << "Signal " << sig << " sent to PID " << pid << '\n';
}


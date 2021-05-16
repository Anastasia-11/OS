#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>

int main() {
    std::string PROC_TO_KILL = "PROC_TO_KILL";
    const char *values = "shotwell,rhythmbox";
    setenv(PROC_TO_KILL.c_str(), values, 0);

    // first check for PROC_TO_KILL
    printf("%s", "PROC_TO_KILL:");
    printf("%s %c", getenv(PROC_TO_KILL.c_str()), '\n');

    std::cout << "Choose how to kill: 1 - by PID, 2 -by name\n";
    int answer;
    std::cin >> answer;

    const int BUFF_SIZE = 100;
    char buff[BUFF_SIZE];
    std::string someProc = "telegram-desktop";
    std::string str;
    switch(answer) {
        case 1: {
            str = "--id ";
            std::string command = "pidof " + someProc;
            FILE* cmdPipe = popen(command.c_str(), "r");
            fgets(buff, BUFF_SIZE, cmdPipe);
            pid_t pid = strtoul(buff, nullptr, 10);
            str += std::to_string(pid);
            break;
        }
        case 2: {
            str = "--name " + someProc;
            break;
        }
        default: {
            std::cout << "Wrong answer!";
            exit(-1);
        }
    }

    system("g++ Killer.cpp -o Killer");
    std::string command = "./Killer " + str;
    system(command.c_str());

    //second check for PROC_TO_KILL
    unsetenv(PROC_TO_KILL.c_str());
    printf("%s", "PROC_TO_KILL:");
    printf("%s %c", getenv(PROC_TO_KILL.c_str()), '\n');
}
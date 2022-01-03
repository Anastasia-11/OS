#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "constants.h"
#include <string>

void func(const std::string& procName, int fd[2]);

int main(int argc, char *argv[]) {
    std::cout << "End sign is:" << END << "\nEnter numbers:\n";
    int fd[2];
    const int LEN = 4;
    std::string processes[LEN] = {"procP", "procM", "procA", "procS"};

    for (int i = 0; i < LEN - 1; ++i) {
        func(processes[i], fd);
    }

    std::string lastProc = processes[LEN - 1];
    execl(lastProc.c_str(), lastProc.c_str(), NULL);

    return 0;
}

void func(const std::string& procName, int fd[2]) {
    pipe(fd);
    if(!fork()) {
        dup2(fd[1], 1);
        execl(procName.c_str(), procName.c_str(), NULL);
        exit(0);
    } else {
        dup2(fd[0], 0);
        close(fd[1]);
    }
}
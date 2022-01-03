#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <csignal>

void terminateByName(const std::string& names) {
    const int BUFF_SIZE = 100;
    char buff[BUFF_SIZE];

    std::stringstream stream(names);
    std::string proc;
    while(std::getline(stream, proc, ',')) {
        std::string str = "pidof " + proc;
        FILE* cmdPipe = popen(str.c_str(), "r");
        fgets(buff, BUFF_SIZE, cmdPipe);
        pid_t pid = strtoul(buff, nullptr, 10);
        kill(pid, SIGKILL);
    }
}

void terminateById(const std::string& pids) {
    std::stringstream stream(pids);
    std::string proc;
    while(std::getline(stream, proc, ',')) {
        pid_t t = stoi(proc);
        kill(t, 1);
    }
}

void terminateByProcToKill() {
    const int BUFF_SIZE = 100;
    char buff[BUFF_SIZE];
    const char* values = getenv("PROC_TO_KILL");

    std::string proc;
    std::stringstream stream(values);

    while(std::getline(stream, proc, ',')) {
        std::string command = "pidof " + proc;
        FILE* cmdPipe = popen(command.c_str(), "r");
        fgets(buff, BUFF_SIZE, cmdPipe);
        pid_t pid = strtoul(buff, nullptr, 10);
        kill(pid, SIGKILL);
    }
}

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "--name") == 0) {
        terminateByName(argv[2]);
    } else if (strcmp(argv[1], "--id") == 0) {
        terminateById(argv[2]);
    }
    terminateByProcToKill();
}
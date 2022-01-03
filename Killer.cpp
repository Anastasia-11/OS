#include <iostream>
#include <string>
#include <cstdio>
#include <windows.h>
#include <TlHelp32.h>
#include <sstream>

void terminateByName(char* name) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    std::string strId(name);

    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            std::string szExeFile(entry.szExeFile);
            if (szExeFile == strId) {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                TerminateProcess(hProcess, 0);
                WaitForSingleObject(hProcess, INFINITE);
                CloseHandle(hProcess);
            }
        }
    }
    CloseHandle(snapshot);
}

void terminateById(char* id) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    std::string strId(id);

    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            if (std::to_string(entry.th32ProcessID) == strId) {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                TerminateProcess(hProcess, 0);
                WaitForSingleObject(hProcess, INFINITE);
                CloseHandle(hProcess);
            }
        }
    }
    CloseHandle(snapshot);
}

void terminateByProcToKill() {
    const CHAR* PROC_TO_KILL = "PROC_TO_KILL";
    const int BUFF_SIZE = 100;
    CHAR buff[BUFF_SIZE];
    GetEnvironmentVariableA(PROC_TO_KILL, buff, BUFF_SIZE);

    std::string proc;
    std::stringstream stream(buff);

    while(std::getline(stream, proc, ',')) {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

        if (Process32First(snapshot, &entry) == TRUE) {
            while (Process32Next(snapshot, &entry) == TRUE) {
                std::string szExeFile(entry.szExeFile);
                if (szExeFile == proc) {
                    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                    TerminateProcess(hProcess, 0);
                    WaitForSingleObject(hProcess, INFINITE);
                    CloseHandle(hProcess);
                }
            }
        }
        CloseHandle(snapshot);
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
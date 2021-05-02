#include <iostream>
#include <string>
#include <cstdio>
#include <windows.h>
#include <sstream>
#include <chrono>
#include <thread>

int main()
{
    STARTUPINFO StartupInfo = { 0 };
    PROCESS_INFORMATION ProcInfo = { nullptr };

    const CHAR *PROC_TO_KILL = "PROC_TO_KILL";
    std::string values = "notepad.exe,mspaint.exe,chrome.exe";
    SetEnvironmentVariableA(PROC_TO_KILL, values.c_str());

    // first check for PROC_TO_KILL
    const int BUFF_SIZE = 100;
    CHAR buff[BUFF_SIZE];
    GetEnvironmentVariableA(PROC_TO_KILL, buff, BUFF_SIZE);
    printf("%s", "PROC_TO_KILL:");
    printf("%s %c", buff, '\n');

    if(!CreateProcess("C:\\Windows\\System32\\mspaint.exe", nullptr, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &StartupInfo, &ProcInfo)) {
        printf( "CreateProcess for mspaint failed.\n" );
        return -1;
    }

    if(!CreateProcess("C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe", nullptr, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &StartupInfo, &ProcInfo)) {
        printf( "CreateProcess for chrome failed.\n" );
        return -1;
    }

    std::chrono::milliseconds timespan(3000);
    std::this_thread::sleep_for(timespan);

    // kill chrome by id
    std::stringstream command;
    command << "Killer.exe --id " << ProcInfo.dwProcessId;
    if(!CreateProcess(nullptr, (LPSTR)command.str().c_str(), nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &StartupInfo, &ProcInfo)) {
        printf( "CreateProcess for command failed.\n" );
        return -1;
    }
    WaitForSingleObject(ProcInfo.hProcess, INFINITE);
    CloseHandle(ProcInfo.hProcess);

    if(!CreateProcess("C:\\Windows\\System32\\notepad.exe", nullptr, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &StartupInfo, &ProcInfo)) {
        printf( "CreateProcess for notepad failed.\n" );
        return -1;
    }
    if(!CreateProcess("C:\\Windows\\System32\\mspaint.exe", nullptr, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &StartupInfo, &ProcInfo)) {
        printf( "CreateProcess for mspaint failed.\n" );
        return -1;
    }

    std::this_thread::sleep_for(timespan);

    // kill notepad by name
    command.str("");
    command << "Killer.exe --name " << "notepad.exe";

    if(!CreateProcess(nullptr, (LPSTR)command.str().c_str(), nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &StartupInfo, &ProcInfo)) {
        printf( "CreateProcess for command failed.\n" );
        return -1;
    }
    WaitForSingleObject(ProcInfo.hProcess, INFINITE);
    CloseHandle(ProcInfo.hProcess);

    // clear PROC_TO_KILL
    SetEnvironmentVariableA(PROC_TO_KILL, "");

    // second check for PROC_TO_KILL
    GetEnvironmentVariableA(PROC_TO_KILL, buff, BUFF_SIZE);
    printf("%s", "PROC_TO_KILL:");
    printf("%s %c", buff, '\n');
}
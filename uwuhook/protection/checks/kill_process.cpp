//⠀  ⢸⠂⠀⠀⠀⠘⣧⠀⠀⣟⠛⠲⢤⡀⠀⠀⣰⠏⠀⠀⠀⠀⠀⢹⡀
//	⠀⡿⠀⠀⠀⠀⠀⠈⢷⡀⢻⡀⠀⠀⠙⢦⣰⠏⠀⠀⠀⠀⠀⠀⢸⠀
//	⠀⡇⠀⠀⠀⠀⠀⠀⢀⣻⠞⠛⠀⠀⠀⠀⠻⠀⠀⠀⠀⠀⠀⠀⢸⠀
//	⠀⡇⠀⠀⠀⠀⠀⠀⠛⠓⠒⠓⠓⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀
//	⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠀              It sucks to say but i am self leaking this source code today
//	⠀⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⠀⠀⢀⡟⠀              this project has been sat on my cdn for a long time and lowkey. i wanna self leak it so people can learn from this
//	⠀⠘⣇⠀⠘⣿⠋⢹⠛⣿⡇⠀⠀⠀⠀⣿⣿⡇⠀⢳⠉⠀⣠⡾⠁⠀              Please dont redistribute this source code without giving me credit, i put a lot of work into this and it would be nice to get some recognition for it.
//	⣦⣤⣽⣆⢀⡇⠀⢸⡇⣾⡇⠀⠀⠀⠀⣿⣿⡷⠀⢸⡇⠐⠛⠛⣿               Im just a solo dev after all and i would like to get some recognition for my work, i know this is cringe but hey, i put a lot of work into this and it would be nice to get some recognition for it.
//	⠹⣦⠀⠀⠸⡇⠀⠸⣿⡿⠁⢀⡀⠀⠀⠿⠿⠃⠀⢸⠇⠀⢀⡾⠁
//	⠀⠈⡿⢠⢶⣡⡄⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⣴⣧⠆⠀⢻⡄                Enjoy the leak chat <3
//	⠀⢸⠃⠀⠘⠉⠀⠀⠀⠠⣄⡴⠲⠶⠴⠃⠀⠀⠀⠉⡀⠀⠀⢻⡄               - ego / @humbleness on discord
//	⠀⠘⠒⠒⠻⢦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⠞⠛⠒⠛⠋⠁               https://uwuhook.club
//	⠀⠀⠀⠀⠀⠀⠸⣟⠓⠒⠂⠀⠀⠀⠀⠀⠈⢷⡀
//	⠀⠀⠀⠀⠀⠀⠀⠙⣦⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⠀⠀⠀⠀⠀⠀
//	⠀⠀⠀⠀⠀⠀⠀⣼⣃⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣆⠀⠀⠀⠀⠀⠀
//	⠀⠀⠀⠀⠀⠀⠀⠉⣹⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀
//	⠀⠀⠀⠀⠀⠀⠀⠀⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡆⠀

#include <Windows.h>
#include <shellapi.h>
#include <thread>
#include <chrono>
#include <string>
#include <TlHelp32.h>
#include "kill_process.h"
#include "process.hpp"

#pragma comment(lib, "ntdll.lib")
extern "C"
{
    NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
    NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);
}

bool kill_process_by_name(const std::wstring& processName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(PROCESSENTRY32W);

    bool found = false;
    if (Process32FirstW(hSnapshot, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, processName.c_str()) == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (hProcess) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                    found = true;
                }
            }
        } while (Process32NextW(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
    return found;
}

bool stop_service_by_name(const std::wstring& serviceName) {
    SC_HANDLE scManager = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!scManager) return false;

    SC_HANDLE scService = OpenServiceW(scManager, serviceName.c_str(), SERVICE_STOP | SERVICE_QUERY_STATUS);
    if (!scService) {
        CloseServiceHandle(scManager);
        return false;
    }

    SERVICE_STATUS serviceStatus;
    bool result = ControlService(scService, SERVICE_CONTROL_STOP, &serviceStatus) != FALSE;

    CloseServiceHandle(scService);
    CloseServiceHandle(scManager);
    return result;
}

void kill_process()
{
    // Kill processes by name
    const std::wstring processes[] = {
        L"HTTPDebuggerUI.exe",
        L"HTTPDebuggerSvc.exe",
        L"cheatengine.exe",
        L"cheatengine-x86_64.exe",
        L"cheatengine-i386.exe",
        L"processhacker.exe",
        L"processhacker2.exe",
        L"processhacker3.exe"
    };

    for (const auto& proc : processes) {
        kill_process_by_name(proc);
    }

    stop_service_by_name(L"HTTPDebuggerPro");
}

void silly()
{
    // nice try cracking my shit
    HWND hwnd = GetConsoleWindow();
    if (hwnd) {
        ShowWindow(hwnd, SW_HIDE);
    }

    ShellExecuteW(nullptr, nullptr, L"https://www.youtube.com/watch?v=U1jsXFsnN9Y", nullptr, nullptr, SW_SHOW);
    ShellExecuteW(nullptr, nullptr, L"https://e-z.bio/%C2%A3", nullptr, nullptr, SW_SHOW);
    exit(EXIT_FAILURE);
}

void process_window()
{
    while (true) {
        if (process_find("KsDumperClient.exe") ||
            process_find("HTTPDebuggerUI.exe") ||
            process_find("HTTPDebuggerSvc.exe") ||
            process_find("FolderChangesView.exe") ||
            process_find("ProcessHacker.exe") ||
            process_find("procmon.exe") ||
            process_find("idaq.exe") ||
            process_find("idaq64.exe") ||
            process_find("Wireshark.exe") ||
            process_find("Fiddler.exe") ||
            process_find("Xenos64.exe") ||
            process_find("Cheat Engine.exe") ||
            process_find("HTTP Debugger Windows Service (32 bit).exe") ||
            process_find("KsDumper.exe") ||
            process_find("x64dbg.exe") ||
            FindWindowW(nullptr, L"IDA: Quick start") ||
            FindWindowW(nullptr, L"Memory Viewer") ||
            FindWindowW(nullptr, L"Process List") ||
            FindWindowW(nullptr, L"KsDumper") ||
            FindWindowW(nullptr, L"HTTP Debugger") ||
            FindWindowW(nullptr, L"OllyDbg"))
        {
            silly();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}
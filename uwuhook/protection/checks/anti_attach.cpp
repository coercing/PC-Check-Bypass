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
#include <string>
#include "anti_attach.h"

#define DbgBreakPoint_FUNC_SIZE 0x2
#define DbgUiRemoteBreakin_FUNC_SIZE 0x54
#define NtContinue_FUNC_SIZE 0x18

struct FUNC {
    const char* name;
    FARPROC addr;
    SIZE_T size;
};

FUNC funcList[] = {
    { "DbgBreakPoint", nullptr, DbgBreakPoint_FUNC_SIZE },
    { "DbgUiRemoteBreakin", nullptr, DbgUiRemoteBreakin_FUNC_SIZE },
    { "NtContinue", nullptr, NtContinue_FUNC_SIZE }
};

void AntiAttach() {
    while (true)
    {
        DWORD pid = GetCurrentProcessId();

        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        if (!hProcess) continue;

        HMODULE hMod = LoadLibraryA("ntdll.dll");
        if (!hMod) {
            CloseHandle(hProcess);
            continue;
        }

        for (int i = 0; i < sizeof(funcList) / sizeof(funcList[0]); ++i) {
            funcList[i].addr = GetProcAddress(hMod, funcList[i].name);
        }

        bool result = false;
        auto base_address = GetModuleHandleA(nullptr);

        WCHAR moduleName[MAX_PATH];
        if (GetModuleFileNameW((HMODULE)base_address, moduleName, MAX_PATH)) {
            std::wstring moduleNameStr = moduleName;
            if (moduleNameStr.find(L"ntdll") != std::wstring::npos ||
                moduleNameStr.find(L"NTDLL") != std::wstring::npos) {

                for (int i = 0; i < sizeof(funcList) / sizeof(funcList[0]); ++i) {
                    if (!funcList[i].addr) continue;

                    DWORD dwOldProtect;
                    if (VirtualProtectEx(hProcess, reinterpret_cast<LPVOID>(funcList[i].addr), funcList[i].size, PAGE_EXECUTE_READWRITE, &dwOldProtect)) {
                        result = WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(funcList[i].addr), funcList[i].addr, funcList[i].size, nullptr);
                        VirtualProtectEx(hProcess, reinterpret_cast<LPVOID>(funcList[i].addr), funcList[i].size, dwOldProtect, &dwOldProtect);

                        if (!result) break;
                    }
                }
            }
        }

        CloseHandle(hProcess);
        FreeLibrary(hMod);
        Sleep(1000);
    }
}
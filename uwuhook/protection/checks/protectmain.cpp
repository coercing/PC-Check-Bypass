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

#include "anti_attach.h"
#include "anti_debugger.h"
#include "anti_dump.h"
#include "integrity_check.h"
#include "kill_process.h"
#include "process.hpp"
#include "protectmain.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <windows.h>

// Global protection state
static std::atomic<ProtectionStage> g_current_stage = ProtectionStage::STAGE_NONE;
static std::atomic<bool> g_continuous_running = false;
static std::thread g_protection_thread;

// Function to hide all console windows
void hide_console_windows() {
    // Hide the main console window
    HWND hwnd = GetConsoleWindow();
    if (hwnd) {
        ShowWindow(hwnd, SW_HIDE);
    }

    // You might also want to hide any windows with "cmd" in the title
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        char window_title[256];
        GetWindowTextA(hwnd, window_title, sizeof(window_title));

        if (strstr(window_title, "cmd.exe") ||
            strstr(window_title, "Command Prompt") ||
            strstr(window_title, "Administrator:") && strstr(window_title, "cmd.exe")) {
            ShowWindow(hwnd, SW_HIDE);
        }
        return TRUE;
        }, 0);
}

bool execute_hidden_command(const std::string& command, const std::string& parameters = "") {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    ZeroMemory(&pi, sizeof(pi));

    std::string full_cmd = command + " " + parameters;

    BOOL result = CreateProcessA(
        NULL,
        (LPSTR)full_cmd.c_str(),
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (result) {
        WaitForSingleObject(pi.hProcess, 5000); // 5 second timeout
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return true;
    }

    return false;
}

void initialize_basic_protections()
{
    if (g_current_stage >= ProtectionStage::STAGE_INITIAL) {
        return;
    }

    // Hide consoles before starting protections
    hide_console_windows();

    anti_dump();
    hidethread();
    kill_process();

    g_current_stage = ProtectionStage::STAGE_INITIAL;
}

void continuous_protection_loop()
{
    while (g_continuous_running)
    {
        // Hide consoles at the start of each loop iteration
        hide_console_windows();

        if (debugstring() || remotepresent() || contextthread())
        {
            silly(); // Use modified version
        }

        if (check_integrity())
        {
            silly(); // Use modified version
        }

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

        static bool anti_attach_initialized = false;
        if (!anti_attach_initialized) {
            std::thread anti_attach_thread([]() {
                hide_console_windows();
                AntiAttach();
                });
            anti_attach_thread.detach();
            anti_attach_initialized = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void start_continuous_protection()
{
    if (g_continuous_running) {
        return;
    }

    if (g_current_stage < ProtectionStage::STAGE_INITIAL) {
        initialize_basic_protections();
    }

    g_continuous_running = true;
    g_protection_thread = std::thread(continuous_protection_loop);
    g_current_stage = ProtectionStage::STAGE_CONTINUOUS;
}

void stop_continuous_protection()
{
    g_continuous_running = false;
    if (g_protection_thread.joinable()) {
        g_protection_thread.join();
    }
    g_current_stage = ProtectionStage::STAGE_INITIAL;
}

void enable_critical_protections()
{
    if (g_current_stage < ProtectionStage::STAGE_INITIAL) {
        initialize_basic_protections();
    }

    if (g_current_stage < ProtectionStage::STAGE_CONTINUOUS) {
        start_continuous_protection();
    }

    g_current_stage = ProtectionStage::STAGE_FULL;
}

void disable_protections()
{
    stop_continuous_protection();
    g_current_stage = ProtectionStage::STAGE_NONE;
}

ProtectionStage get_current_protection_stage()
{
    return g_current_stage;
}

void mainprotect(ProtectionStage stage)
{
    switch (stage) {
    case ProtectionStage::STAGE_INITIAL:
        initialize_basic_protections();
        break;

    case ProtectionStage::STAGE_CONTINUOUS:
        start_continuous_protection();
        break;

    case ProtectionStage::STAGE_FULL:
        enable_critical_protections();
        break;

    case ProtectionStage::STAGE_NONE:
    default:
        disable_protections();
        break;
    }
}
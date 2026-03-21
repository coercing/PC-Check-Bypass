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

#pragma once

#include "../main/includes.hpp"
#include "../libs/xor/xorstr.hpp"
#include "../libs/keyauth/skStr.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <tlhelp32.h>
#include <wincrypt.h>
#include <winioctl.h>
#include <setupapi.h>

namespace fs = std::filesystem;

namespace utils
{
    inline std::string to_lower(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), static_cast<int(*)(int)>(::tolower));
        return str;
    }

    inline std::wstring to_lower(const std::wstring& str)
    {
        std::wstring result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::towlower);
        return result;
    }

    inline std::string to_upper(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), static_cast<int(*)(int)>(::toupper));
        return str;
    }

    inline bool kill_process(const std::string& proc)
    {
        if (proc.empty())
            return false;

        auto file = proc;
        if (file.find_last_of(".") != std::string::npos)
            file.erase(file.find_last_of("."), std::string::npos);

        file += ".exe";
        const auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        PROCESSENTRY32 entry; entry.dwSize = sizeof(entry);

        if (!Process32First(handle, &entry))
            return false;

        do
        {
            std::string exeFile;
            int len = WideCharToMultiByte(CP_UTF8, 0, entry.szExeFile, -1, nullptr, 0, nullptr, nullptr);
            if (len > 0) {
                exeFile.resize(len);
                WideCharToMultiByte(CP_UTF8, 0, entry.szExeFile, -1, &exeFile[0], len, nullptr, nullptr);
                exeFile.pop_back();
            }

            if (utils::to_lower(exeFile).compare(utils::to_lower(file)) == 0)
            {
                const auto process = OpenProcess(PROCESS_TERMINATE, false, entry.th32ProcessID);
                if (process != nullptr)
                {
                    TerminateProcess(process, 9);
                    CloseHandle(process);
                }

                CloseHandle(handle);
                return true;
            }
        } while (Process32Next(handle, &entry));

        return false;
    }

    namespace find_file
    {
        __inline bool containsPhrase(const fs::path& filepath, const std::string& phrase)
        {
            std::ifstream file(filepath);
            if (!file.is_open())
            {
                return false;
            }

            std::string line;
            while (std::getline(file, line))
            {
                if (line.find(phrase) != std::string::npos)
                {
                    return true;
                }
            }

            return false;
        }

        __inline void moveFile(const fs::path& source, const fs::path& destination, const std::string& newFilename)
        {
            try
            {
                fs::rename(source, destination / newFilename);
            }
            catch (const std::filesystem::filesystem_error& e)
            {
				MessageBoxA(NULL, e.what(), skCrypt("Error"), MB_OK | MB_ICONERROR);
            }
        }

        __inline void emptyDirectory(const fs::path& directory)
        {
            for (const auto& entry : fs::directory_iterator(directory))
            {
                try
                {
                    if (fs::is_regular_file(entry))
                    {
                        fs::remove(entry);
                    }
                    else if (fs::is_directory(entry))
                    {
                        fs::remove_all(entry);
                    }
                }
                catch (const std::filesystem::filesystem_error& e)
                {
					MessageBoxA(NULL, e.what(), skCrypt("Error"), MB_OK | MB_ICONERROR);
                }
            }
        }
    }

    namespace string
    {
        __inline std::string to_lower(std::string str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
            return str;
        }

        __inline std::string to_upper(std::string str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::toupper);
            return str;
        }

        __inline std::wstring to_lower(const std::wstring& str)
        {
            std::wstring result = str;
            std::transform(result.begin(), result.end(), result.begin(), ::towlower);
            return result;
        }
    }

    namespace machine
    {
        __inline std::string serial()
        {
            HANDLE device = CreateFileA(skCrypt("\\\\.\\PhysicalDrive0"), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

            if (!device || device == INVALID_HANDLE_VALUE)
                return {};

            char volumeName[MAX_PATH] = { 0 };
            char fileSystemName[MAX_PATH] = { 0 };
            DWORD serialNumber = 0;
            DWORD maxComponentLen = 0;
            DWORD fileSystemFlags = 0;

            if (GetVolumeInformationA(skCrypt("C:\\"), volumeName, MAX_PATH, &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystemName, MAX_PATH))
            {
                CloseHandle(device);
                return std::to_string(serialNumber);
            }

            CloseHandle(device);
            return {};
        }

        __inline bool check_driver(const std::string& driver_name)
        {
            LPVOID drivers_buffer[512];
            DWORD bytes_returned;

            if (EnumDeviceDrivers(drivers_buffer, sizeof(drivers_buffer), &bytes_returned))
            {
                std::uint16_t drivers = bytes_returned / sizeof(drivers_buffer[0]);

                for (std::uint16_t i = 0; i < drivers; ++i)
                {
                    wchar_t current_driver[MAX_PATH] = { 0 };
                    if (GetDeviceDriverBaseNameW(drivers_buffer[i], current_driver, MAX_PATH))
                    {
                        std::string driverNameStr;
                        int len = WideCharToMultiByte(CP_UTF8, 0, current_driver, -1, nullptr, 0, nullptr, nullptr);
                        if (len > 0) {
                            driverNameStr.resize(len);
                            WideCharToMultiByte(CP_UTF8, 0, current_driver, -1, &driverNameStr[0], len, nullptr, nullptr);
                            driverNameStr.pop_back();
                        }

                        if (driver_name == driverNameStr)
                            return true;
                    }
                }
            }
            return false;
        }

        __inline bool stop_service(const char* serviceName)
        {
            const auto sc_manager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);
            if (sc_manager == nullptr || sc_manager == INVALID_HANDLE_VALUE)
                return false;

            const auto service_handle = OpenServiceA(sc_manager, serviceName, SERVICE_STOP);
            if (service_handle == nullptr || service_handle == INVALID_HANDLE_VALUE)
            {
                CloseServiceHandle(sc_manager);
                return false;
            }

            SERVICE_STATUS serviceStatus;
            ControlService(service_handle, SERVICE_CONTROL_STOP, &serviceStatus);
            CloseServiceHandle(service_handle);
            CloseServiceHandle(sc_manager);

            return true;
        }

        __inline bool start_service(const char* serviceName)
        {
            const auto sc_manager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);
            if (sc_manager == nullptr || sc_manager == INVALID_HANDLE_VALUE)
                return false;

            const auto service_handle = OpenServiceA(sc_manager, serviceName, SERVICE_START);
            if (service_handle == nullptr || service_handle == INVALID_HANDLE_VALUE)
            {
                CloseServiceHandle(sc_manager);
                return false;
            }

            StartServiceA(service_handle, 0, NULL);
            CloseServiceHandle(service_handle);
            CloseServiceHandle(sc_manager);

            return true;
        }

        __inline void copy_to_clipboard(const std::string& text)
        {
            if (OpenClipboard(nullptr))
            {
                EmptyClipboard();

                HGLOBAL hClipboardData = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);

                if (hClipboardData != nullptr)
                {
                    char* pClipboardData = static_cast<char*>(GlobalLock(hClipboardData));

                    if (pClipboardData != nullptr)
                    {
                        strcpy_s(pClipboardData, text.size() + 1, text.c_str());
                        GlobalUnlock(hClipboardData);
                        SetClipboardData(CF_TEXT, hClipboardData);
                    }
                }
                CloseClipboard();
            }
        }

        __inline bool clear_pagefile()
        {
            HKEY hKey;
            if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, skCrypt("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management"), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
            {
                DWORD value = 1;
                if (RegSetValueExA(hKey, skCrypt("ClearPageFileAtShutdown"), 0, REG_DWORD, (BYTE*)&value, sizeof(value)) == ERROR_SUCCESS)
                {
                    RegCloseKey(hKey);
                    return true;
                }
                RegCloseKey(hKey);
            }
            return false;
        }

        __inline bool wipe_free_space(const std::wstring& drivePath)
        {
            HANDLE hFile = CreateFileW(drivePath.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
                return false;

            DWORD bytesReturned;
            FILE_ZERO_DATA_INFORMATION zeroData;
            zeroData.FileOffset.QuadPart = 0;
            zeroData.BeyondFinalZero.QuadPart = MAXLONGLONG;

            BOOL result = DeviceIoControl(hFile, FSCTL_SET_ZERO_DATA, &zeroData, sizeof(zeroData), NULL, 0, &bytesReturned, NULL);
            CloseHandle(hFile);

            return result != FALSE;
        }
    }

    namespace process
    {
        __inline std::wstring get_exe_path()
        {
            wchar_t path[MAX_PATH];
            GetModuleFileNameW(0, path, MAX_PATH);
            return path;
        }

        __inline std::wstring get_exe_name()
        {
            std::wstring path = get_exe_path();
            return std::wstring(path.substr(path.find_last_of(L"\\") + 1));
        }

        __inline DWORD get_id(const std::string& proc)
        {
            if (proc.find(".") != std::string::npos)
            {
                const auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

                if (handle != INVALID_HANDLE_VALUE)
                {
                    PROCESSENTRY32 entry;
                    entry.dwSize = sizeof(entry);

                    if (Process32First(handle, &entry))
                    {
                        do
                        {
                            std::string exeFile;
                            int len = WideCharToMultiByte(CP_UTF8, 0, entry.szExeFile, -1, nullptr, 0, nullptr, nullptr);
                            if (len > 0) {
                                exeFile.resize(len);
                                WideCharToMultiByte(CP_UTF8, 0, entry.szExeFile, -1, &exeFile[0], len, nullptr, nullptr);
                                exeFile.pop_back();
                            }

                            if (utils::string::to_lower(proc) == utils::string::to_lower(exeFile))
                            {
                                CloseHandle(handle);
                                return entry.th32ProcessID;
                            }
                        } while (Process32Next(handle, &entry));
                    }
                    CloseHandle(handle);
                }
            }
            else
            {
                const auto service_manager = OpenSCManager(nullptr, nullptr, NULL);
                if (service_manager)
                {
                    std::wstring wideProc(proc.begin(), proc.end());
                    const auto service_handle = OpenServiceW(service_manager, wideProc.c_str(), SERVICE_QUERY_STATUS);

                    if (service_handle)
                    {
                        SERVICE_STATUS_PROCESS service = {};
                        DWORD bytes = 0;

                        QueryServiceStatusEx(service_handle, SC_STATUS_PROCESS_INFO,
                            reinterpret_cast<LPBYTE>(&service), sizeof(service), &bytes);
                        CloseServiceHandle(service_handle);
                        CloseServiceHandle(service_manager);

                        return service.dwProcessId;
                    }
                    CloseServiceHandle(service_manager);
                }
            }
            return 0;
        }

        __inline bool EnablePrivilege()
        {
            HANDLE hToken;
            TOKEN_PRIVILEGES tokenPrivileges;
            LUID luid;

            if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
                return false;

            if (!LookupPrivilegeValueA(NULL, skCrypt("SeDebugPrivilege").decrypt(), &luid))
            {
                CloseHandle(hToken);
                return false;
            }

            tokenPrivileges.PrivilegeCount = 1;
            tokenPrivileges.Privileges[0].Luid = luid;
            tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

            if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
            {
                CloseHandle(hToken);
                return false;
            }

            CloseHandle(hToken);
            return true;
        }

        __inline bool is_elevated()
        {
            HANDLE hToken;
            TOKEN_ELEVATION elevation;
            DWORD dwSize;

            if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
                return false;

            bool result = false;
            if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &dwSize))
            {
                result = elevation.TokenIsElevated != 0;
            }

            CloseHandle(hToken);
            return result;
        }

        __inline bool execute_hidden(const std::string& command, const std::string& parameters = "")
        {
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

            if (result)
            {
                WaitForSingleObject(pi.hProcess, 10000);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                return true;
            }

            return false;
        }
    }

    namespace security
    {
        __inline bool obfuscate_string(std::string& str)
        {
            for (auto& c : str) {
                c = ~c;
            }
            return true;
        }

        __inline bool deobfuscate_string(std::string& str)
        {
            for (auto& c : str) {
                c = ~c;
            }
            return true;
        }

        __inline void secure_zero_memory(void* ptr, size_t size)
        {
            if (ptr && size > 0) {
                volatile char* vptr = static_cast<volatile char*>(ptr);
                while (size--) {
                    *vptr++ = 0;
                }
            }
        }

        __inline bool erase_file_secure(const std::wstring& filepath)
        {
            HANDLE hFile = CreateFileW(filepath.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
                return false;

            DWORD fileSize = GetFileSize(hFile, NULL);
            if (fileSize == INVALID_FILE_SIZE)
            {
                CloseHandle(hFile);
                return false;
            }

            HANDLE hMap = CreateFileMappingW(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
            if (!hMap)
            {
                CloseHandle(hFile);
                return false;
            }

            LPVOID pData = MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, fileSize);
            if (!pData)
            {
                CloseHandle(hMap);
                CloseHandle(hFile);
                return false;
            }

            secure_zero_memory(pData, fileSize);
            FlushViewOfFile(pData, fileSize);
            UnmapViewOfFile(pData);
            CloseHandle(hMap);
            CloseHandle(hFile);

            return DeleteFileW(filepath.c_str()) != FALSE;
        }
    }

    namespace system
    {
        __inline void shutdown_system()
        {
            utils::process::execute_hidden("shutdown", "/s /t 0");
        }

        __inline void restart_system()
        {
            utils::process::execute_hidden("shutdown", "/r /t 0");
        }

        __inline bool disable_task_manager()
        {
            HKEY hKey;
            if (RegCreateKeyA(HKEY_CURRENT_USER, skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System").decrypt(), &hKey) == ERROR_SUCCESS)
            {
                DWORD value = 1;
                if (RegSetValueExA(hKey, skCrypt("DisableTaskMgr").decrypt(), 0, REG_DWORD, (BYTE*)&value, sizeof(value)) == ERROR_SUCCESS)
                {
                    RegCloseKey(hKey);
                    return true;
                }
                RegCloseKey(hKey);
            }
            return false;
        }

        __inline bool enable_task_manager()
        {
            HKEY hKey;
            if (RegOpenKeyA(HKEY_CURRENT_USER, skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System").decrypt(), &hKey) == ERROR_SUCCESS)
            {
                if (RegDeleteValueA(hKey, skCrypt("DisableTaskMgr").decrypt()) == ERROR_SUCCESS)
                {
                    RegCloseKey(hKey);
                    return true;
                }
                RegCloseKey(hKey);
            }
            return false;
        }
    }
}
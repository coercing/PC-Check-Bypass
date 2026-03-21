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

#include "../main/includes.hpp"
#include "../libs/xor/xorstr.hpp"
#include "utils.hpp"
#include "memory.hpp"
#include "cleaner.hpp"
#include <iostream>
#include <windows.h>
#include <winioctl.h>

namespace cleaner
{
    auto c_cleaner::clear_bam_traces() -> bool
    {
        HKEY hKey;
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, xorstr_("SYSTEM\\CurrentControlSet\\Services\\bam\\State\\UserSettings"), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
            RegDeleteTreeA(hKey, NULL);
            RegCloseKey(hKey);
        }

        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, xorstr_("SYSTEM\\CurrentControlSet\\Services\\dam\\State\\UserSettings"), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
            RegDeleteTreeA(hKey, NULL);
            RegCloseKey(hKey);
        }

        return true;
    }

    auto c_cleaner::clear_memory(const int pid, const std::wstring str, bool is_dps) -> void
    {
        const auto memory = std::make_unique<memory::c_memory>(pid);

        auto unicode_addresses = memory->scan_unicode(str);
        for (auto addr : unicode_addresses)
            memory->rewrite_unicode(addr, str);

        auto multibyte_addresses = memory->scan_multibyte(str);
        for (auto addr : multibyte_addresses)
            memory->rewrite_multibyte(addr, str);

        if (is_dps)
        {
            for (auto addr : unicode_addresses)
                memory->rewrite_unicode_dps(addr, str);

            for (auto addr : multibyte_addresses)
                memory->rewrite_multibyte_dps(addr, str);
        }
    }

    auto c_cleaner::clear_regedit(HKEY hkey, const char* directory) -> bool
    {
        auto result = RegDeleteKeyA(hkey, directory);

        if (result == ERROR_SUCCESS)
            return true;

        HKEY hSubKey;
        result = RegOpenKeyExA(hkey, directory, 0, KEY_READ, &hSubKey);

        switch (result)
        {
        case ERROR_FILE_NOT_FOUND:
            return false;
        case ERROR_SUCCESS:
            break;
        default:
            return false;
        }

        do
        {
            HKEY hCurrentKey;
            if (RegOpenKeyExA(HKEY_CURRENT_USER, directory, 0, KEY_ALL_ACCESS, &hCurrentKey) == ERROR_SUCCESS)
            {
                DWORD dwNumValues, dwValueNameLen;
                if (RegQueryInfoKeyA(hCurrentKey, 0, 0, 0, 0, 0, 0, &dwNumValues, &dwValueNameLen, 0, 0, 0) == ERROR_SUCCESS)
                {
                    if (dwValueNameLen > 0)
                    {
                        char* tchValName = new char[dwValueNameLen + 1];
                        for (DWORD i = 0; i < dwNumValues; ++i)
                        {
                            DWORD dwLen = dwValueNameLen + 1;
                            if (RegEnumValueA(hCurrentKey, i, tchValName, &dwLen, 0, 0, 0, 0) == ERROR_SUCCESS)
                                RegDeleteValueA(hCurrentKey, tchValName);
                        }
                        delete[] tchValName;
                    }
                }
                RegCloseKey(hCurrentKey);
            }
        } while (false);

        RegCloseKey(hSubKey);
        result = RegDeleteKeyA(hkey, directory);

        return result == ERROR_SUCCESS;
    }

    auto c_cleaner::delete_file(const std::string_view path, const std::string file_name) -> void
    {
        try
        {
            for (const auto& dir_entry : std::filesystem::directory_iterator{ path })
            {
                if (dir_entry.is_regular_file())
                {
                    std::string filename = dir_entry.path().filename().string();
                    if (filename.find(utils::string::to_upper(file_name)) != std::string::npos)
                    {
                        std::remove(dir_entry.path().string().c_str());
                    }
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e)
        {
			MessageBoxA(NULL, e.what(), xorstr_("Error"), MB_OK | MB_ICONERROR);
        }
    }


    auto c_cleaner::clear_usn_journal(const std::wstring& drive_letter) -> bool
    {
        std::wstring volume_path = xorstr_(L"\\\\.\\") + drive_letter + xorstr_(L":");

        HANDLE hVolume = CreateFileW(
            volume_path.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (hVolume == INVALID_HANDLE_VALUE)
            return false;

        DWORD bytesReturned;
        DELETE_USN_JOURNAL_DATA dujd;

        ZeroMemory(&dujd, sizeof(dujd));
        dujd.UsnJournalID = 0;
        dujd.DeleteFlags = USN_DELETE_FLAG_DELETE;

        BOOL result = DeviceIoControl(
            hVolume,
            FSCTL_DELETE_USN_JOURNAL,
            &dujd, sizeof(dujd),
            NULL, 0,
            &bytesReturned,
            NULL
        );

        CloseHandle(hVolume);

        if (!result)
        {
            DWORD error = GetLastError();
            if (error == ERROR_JOURNAL_NOT_ACTIVE || error == ERROR_JOURNAL_DELETE_IN_PROGRESS)
                return true;
            return false;
        }

        return true;
    }
}
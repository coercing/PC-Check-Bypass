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
#include "../libs/keyauth/skStr.h"
#include "modules.hpp"
#include "cleaner.hpp"
#include "utils.hpp"
#include "memory.hpp"

#pragma warning(disable: 4996)

namespace modules
{
    auto c_modules::clean_traces() -> void
    {
        if (!utils::process::EnablePrivilege()) {
            MessageBoxA(NULL,
                skCrypt("Failed to enable debug privileges").decrypt(),
                skCrypt("Cleaner Error").decrypt(),
                MB_OK | MB_ICONERROR
            );
            return;
        }

        auto strings_to_clean = get_default_cleanlist();
        const auto cleaner = std::make_unique<cleaner::c_cleaner>();

        for (auto& info : strings_to_clean)
        {
            if (validate_process(info.first))
            {
                clean_process_memory(info.first, info.second);
            }
        }

        secure_delete_registry_key(HKEY_CURRENT_USER,
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
        secure_delete_registry_key(HKEY_LOCAL_MACHINE,
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
    }

    auto c_modules::clean_custom_traces(const std::vector<std::pair<std::string, std::wstring>>& processes_and_strings) -> void
    {
        if (!utils::process::is_elevated()) {
            MessageBoxA(NULL,
                xorstr_("Administrator privileges required"),
                xorstr_("Elevation Required"),
                MB_OK | MB_ICONWARNING
            );
            return;
        }

        const auto cleaner = std::make_unique<cleaner::c_cleaner>();

        const char* encrypted_paths[] = {
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU"),
            skCrypt("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"),
            skCrypt("SYSTEM\\CurrentControlSet\\Services\\xbgm"),
            skCrypt("SOFTWARE\\Policies\\Microsoft\\Windows\\GameDVR"),
            skCrypt("SOFTWARE\\Microsoft\\MSLicensing\\HardwareID"),
            skCrypt("SOFTWARE\\Microsoft\\MSLicensing\\Store"),
            skCrypt("Software\\WinRAR\\ArcHistory"),
            skCrypt("SYSTEM\\ControlSet001\\Services\\bam\\State\\UserSettings\\S-1-5-21-1282084573-1681065996-3115981261-1001"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FeatureUsage\\ShowJumpView"),
            skCrypt("Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\MuiCache"),
            skCrypt("Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Compatibility Assistant\\Store"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FeatureUsage\\AppSwitched"),
            skCrypt("SYSTEM\\ControlSet001\\Services\\bam\\State\\UserSettings\\S-1-5-21-332004695-2829936588-140372829-1002")
        };

        for (auto& info : processes_and_strings)
        {
            if (validate_process(info.first))
            {
                clean_process_memory(info.first, info.second);

                for (const auto& path : encrypted_paths) {
                    secure_delete_registry_key(HKEY_CURRENT_USER, path);
                    secure_delete_registry_key(HKEY_LOCAL_MACHINE, path);
                }
            }
        }
    }

    __inline BOOL EnablePrivilege()
    {
        HANDLE hToken;
        TOKEN_PRIVILEGES tokenPrivileges;
        LUID luid;

        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
            return FALSE;

        if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
        {
            CloseHandle(hToken);
            return FALSE;
        }

        tokenPrivileges.PrivilegeCount = 1;
        tokenPrivileges.Privileges[0].Luid = luid;
        tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
        {
            CloseHandle(hToken);
            return FALSE;
        }

        CloseHandle(hToken);
        return TRUE;
    }

    auto c_modules::comprehensive_clean() -> void
    {
        if (!utils::process::EnablePrivilege()) {
            return;
        }

        auto strings_to_clean = get_default_cleanlist();
        const auto cleaner = std::make_unique<cleaner::c_cleaner>();

        std::vector<std::wstring> drives = { L"C", L"D", L"E" };
        clean_drive_journals(drives);

        cleaner->clear_bam_traces();

        for (auto& info : strings_to_clean)
        {
            if (validate_process(info.first))
            {
                clean_process_memory(info.first, info.second);
            }
        }

        // In comprehensive_clean() - update registry_paths vector:
        std::vector<const char*> registry_paths = {
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\RunServices"),
            skCrypt("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"),
            skCrypt("Software\\Microsoft\\Active Setup\\Installed Components"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32"),
            skCrypt("SYSTEM\\CurrentControlSet\\Services\\xbgm"),
            skCrypt("SOFTWARE\\Policies\\Microsoft\\Windows\\GameDVR"),
            skCrypt("SOFTWARE\\Microsoft\\MSLicensing\\HardwareID"),
            skCrypt("SOFTWARE\\Microsoft\\MSLicensing\\Store"),
            skCrypt("Software\\WinRAR\\ArcHistory"),
            skCrypt("SYSTEM\\ControlSet001\\Services\\bam\\State\\UserSettings\\S-1-5-21-1282084573-1681065996-3115981261-1001"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FeatureUsage\\ShowJumpView"),
            skCrypt("Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\MuiCache"),
            skCrypt("Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Compatibility Assistant\\Store"),
            skCrypt("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FeatureUsage\\AppSwitched"),
            skCrypt("SYSTEM\\ControlSet001\\Services\\bam\\State\\UserSettings\\S-1-5-21-332004695-2829936588-140372829-1002"),
            skCrypt("CLASSES_ROOT\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\MuiCache")
        };

        for (auto& path : registry_paths)
        {
            secure_delete_registry_key(HKEY_CURRENT_USER, path);
            secure_delete_registry_key(HKEY_LOCAL_MACHINE, path);
        }

        const char* file_paths[] = {
            skCrypt("%temp%"),
            skCrypt("%windir%\\prefetch"),
            skCrypt("%windir%\\Temp"),
            skCrypt("%userprofile%\\AppData\\Local\\Temp"),
            skCrypt("%userprofile%\\AppData\\Roaming\\Microsoft\\Windows\\Recent"),
            skCrypt("%systemroot%\\prefetch"),
            skCrypt("%userprofile%\\AppData\\Local\\Microsoft\\Windows\\WebCache"),
            skCrypt("%windir%\\logs\\cbs"),
            skCrypt("%windir%\\Logs\\MoSetup"),
            skCrypt("%windir%\\Panther"),
            skCrypt("%windir%\\inf"),
            skCrypt("%windir%\\logs"),
            skCrypt("%windir%\\SoftwareDistribution"),
            skCrypt("%windir%\\Microsoft.NET"),
            skCrypt("%userprofile%\\AppData\\Local\\Microsoft\\Windows\\SettingSync"),
            skCrypt("%userprofile%\\AppData\\Local\\Microsoft\\Windows\\Explorer\\ThumbCacheToDelete"),
        };

        for (const auto& path : file_paths) {
            expand_and_clean_path(path);
        }

        clear_system_cache();
        reset_network();
    }

    auto c_modules::check_traces() -> bool
    {
        if (!utils::process::is_elevated()) {
            return false;
        }

        auto strings_to_check = get_default_cleanlist();

        for (auto& info : strings_to_check)
        {
            if (validate_process(info.first))
            {
                DWORD pid = utils::process::get_id(info.first);
                if (pid != 0)
                {
                    const auto memory = std::make_unique<memory::c_memory>(pid);
                    auto unicode_addresses = memory->scan_unicode(info.second);
                    auto multibyte_addresses = memory->scan_multibyte(info.second);

                    if (!unicode_addresses.empty() || !multibyte_addresses.empty())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    auto c_modules::secure_clean() -> bool
    {
        MessageBoxA(NULL,
            xorstr_("Starting secure cleaning procedure..."),
            xorstr_("Secure Clean"),
            MB_OK | MB_ICONINFORMATION
        );

        if (!utils::process::is_elevated()) {
            MessageBoxA(NULL,
                xorstr_("Admin privileges required for secure clean"),
                xorstr_("Access Denied"),
                MB_OK | MB_ICONERROR
            );
            return false;
        }

        comprehensive_clean();
        wipe_free_space({ L"C" });

        utils::machine::clear_pagefile();

        MessageBoxA(NULL,
            xorstr_("Secure cleaning completed successfully"),
            xorstr_("Clean Complete"),
            MB_OK | MB_ICONINFORMATION
        );

        return true;
    }

    auto c_modules::clean_drive_journals(const std::vector<std::wstring>& drives) -> bool
    {
        const auto cleaner = std::make_unique<cleaner::c_cleaner>();
        bool success = true;

        for (const auto& drive : drives) {
            if (!cleaner->clear_usn_journal(drive)) {
                success = false;
            }
        }

        return success;
    }

    auto c_modules::wipe_free_space(const std::vector<std::wstring>& drives) -> bool
    {
        bool success = true;

        for (const auto& drive : drives) {
            std::wstring drive_path = drive + L":\\";
            if (!utils::machine::wipe_free_space(drive_path)) {
                success = false;
            }
        }

        return success;
    }

    auto c_modules::clear_system_cache() -> bool
    {

        utils::process::execute_hidden("ipconfig", "/flushdns");
        utils::process::execute_hidden("netsh", "winsock reset");
        utils::process::execute_hidden("netsh", "int ip reset");
        utils::process::execute_hidden("takeown", "/A /R /D Y /F C:\\windows\\temp");
        utils::process::execute_hidden("md", "c:\\windows\\temp");
        utils::process::execute_hidden("del", "c:\\windows\\logs\\cbs\\*.log");
        utils::process::execute_hidden("del", "C:\\Windows\\Logs\\MoSetup\\*.log");
        utils::process::execute_hidden("del", "C:\\Windows\\Panther\\*.log /s /q");
        utils::process::execute_hidden("del", "C:\\Windows\\inf\\*.log /s /q");
        utils::process::execute_hidden("del", "C:\\Windows\\logs\\*.log /s /q");
        utils::process::execute_hidden("del", "C:\\Windows\\SoftwareDistribution\\*.log /s /q");
        utils::process::execute_hidden("del", "C:\\Windows\\Microsoft.NET\\*.log /s /q");
        utils::process::execute_hidden("del", "C:\\Users\\%USERNAME%\\AppData\\Local\\Microsoft\\Windows\\WebCache\\*.log /s /q");
        utils::process::execute_hidden("del", "C:\\Users\\%USERNAME%\\AppData\\Local\\Microsoft\\Windows\\SettingSync\\*.log /s /q");
        utils::process::execute_hidden("del", "C:\\Users\\%USERNAME%\\AppData\\Local\\Microsoft\\Windows\\Explorer\\ThumbCacheToDelete\\*.tmp /s /q");
        utils::process::execute_hidden("del", "C:\\Users\\%USERNAME%\\AppData\\Local\\Microsoft\\\"Terminal Server Client\"\\Cache\\*.bin /s /q");
        utils::process::execute_hidden("deltree", "/y c:\\windows\\tempor~1");
        utils::process::execute_hidden("deltree", "/y c:\\windows\\temp");
        utils::process::execute_hidden("deltree", "/y c:\\windows\\tmp");
        utils::process::execute_hidden("deltree", "/y c:\\windows\\ff*.tmp");
        utils::process::execute_hidden("deltree", "/y c:\\windows\\history");
        utils::process::execute_hidden("deltree", "/y c:\\windows\\cookies");
        utils::process::execute_hidden("deltree", "/y c:\\windows\\recent");

        return true;
    }

    auto c_modules::reset_network() -> bool
    {
        utils::process::EnablePrivilege();

        utils::process::execute_hidden("ipconfig", "/release");
        utils::process::execute_hidden("ipconfig", "/renew");
        utils::process::execute_hidden("arp", "-d *");
        utils::process::execute_hidden("nbtstat", "-R");
        utils::process::execute_hidden("set", "hostspath=%windir%\\System32\\drivers\\etc\\hosts");
        utils::process::execute_hidden("echo", "127.0.0.1 xboxlive.com >> %hostspath%");
        utils::process::execute_hidden("echo", "127.0.0.1 user.auth.xboxlive.com >> %hostspath%");
        utils::process::execute_hidden("echo", "127.0.0.1 presence-heartbeat.xboxlive.com >> %hostspath%");

        return true;
    }

    auto c_modules::clean_processes_and_services() -> bool
    {

        utils::process::execute_hidden("sc", "stop XblAuthManager >NUL 2>NUL");
        utils::process::execute_hidden("sc", "stop XblGameSave >NUL 2>NUL");
        utils::process::execute_hidden("sc", "stop XboxNetApiSvc >NUL 2>NUL");
        utils::process::execute_hidden("sc", "stop XboxGipSvc >NUL 2>NUL");
        utils::process::execute_hidden("sc", "delete XblAuthManager >NUL 2>NUL");
        utils::process::execute_hidden("sc", "delete XblGameSave >NUL 2>NUL");
        utils::process::execute_hidden("sc", "delete XboxNetApiSvc >NUL 2>NUL");
        utils::process::execute_hidden("sc", "delete XboxGipSvc >NUL 2>NUL");
        return true;
    }


    auto c_modules::get_default_cleanlist() -> std::vector<std::pair<std::string, std::wstring>>
    {
        EnablePrivilege();

        return {
            {"Dnscache",  L"skript.gg"},
            {"Dnscache",  L"skript"},
            {"Dnscache",  L"keyauth"},
            {"Dnscache",  L"keyauth.win"},
            {"Dnscache",  L"oauth2"},
            {"Dnscache",  L"validate"},
            {"Dnscache",  L"authenticate"},
            {"Dnscache",  L"license"},
            {"Dnscache",  L".com/api/"},
            {"Dnscache",  L"token"},

            {"Dps",  L"winhlp64.exe"},
            {"Dps",  L"!!winhlp64.exe!2023 / 12 / 13:20 : 14 : 01!0!"},
            {"Dps",  L"!!winhlp64.exe!2023 / 12 / 13:20 : 14 : 01!0!"},

            {"Pcasvc",  L"winhlp64.exe"},
            {"Pcasvc",  L"skript"},
            {"Pcasvc",  L"keyauth"},
            {"Pcasvc",  L"0x2e1f000"},
            {"Pcasvc",  L"keyauth.win"},

            {"lsass.exe",  L"skript.gg"},
            {"lsass.exe",  L"skript"},
            {"lsass.exe",  L"keyauth"},
            {"lsass.exe",  L"keyauth.win"},
            {"lsass.exe",  L"50301"},
            {"lsass.exe",  L"Google Trust Services LLC1"},
            {"lsass.exe",  L"1.3.6.1.4.1.11129.2.5.3"},
            {"lsass.exe",  L"http://crls.pki.goog/gts1p5/bJcOhcmiYRM.crl0"},
            {"lsass.exe",  L"http://pki.goog/repo/certs/gts1p5.der0!"},
            {"lsass.exe",  L"GTS Root R10"},
            {"lsass.exe",  L"20231226154332Z0"},
            {"lsass.exe",  L"http://ocsp.pki.goog/s/gts1p5/ghf_lTR8_n801"},
            {"lsass.exe",  L"GTS CA 1P5"},
            {"lsass.exe",  L"??\\MAILSLOT\\NET\\GETDC7D32A39B"},
            {"lsass.exe",  L"http://ocsp.pki.goog/s/gts1p5/ghf_lTR8_n8"},
            {"lsass.exe",  L"20231219164333Z"},
            {"lsass.exe",  L"http://ocsp.pki.goog/gtsr100"},
            {"lsass.exe",  L"!http://crl.pki.goog/gsr1/gsr1.crl0;"},
            {"lsass.exe",  L"$http://pki.goog/repo/certs/gtsr1.der04"},
            {"lsass.exe",  L"http://ocsp.pki.goog/gsr10)"},
            {"lsass.exe",  L"+http://crls.pki.goog/gts1p5/_W4pCBAcO48.crl0"},
            {"lsass.exe",  L"https://pki.goog/repository/0"},
            {"lsass.exe",  L"http://pki.goog/gsr1/gsr1.crt02"},
            {"lsass.exe",  L"%http://pki.goog/repo/certs/gts1p5.der0!"},
            {"lsass.exe",  L"#http://crl.pki.goog/gtsr1/gtsr1.crl0M"},
            {"lsass.exe",  L"http://crls.pki.goog/gts1p5/_7T6Mrwy7MI.crl0"},
            {"lsass.exe",  L"http://ocsp.pki.goog/s/gts1p5/Z6slLsZWaiw01"},
            {"lsass.exe",  L"api."},
            {"lsass.exe",  L"auth."},
            {"lsass.exe",  L"key."},
            {"lsass.exe",  L"verify."},
            {"lsass.exe",  L"token"},
            {"lsass.exe",  L"HKEY_CURRENT_USER\\Software"},

            {"memorycompression.exe",  L"skript.gg"},
            {"memorycompression.exe",  L"skript"},
            {"memorycompression.exe",  L"keyauth"},
            {"memorycompression.exe",  L"keyauth.win"},

            {"explorer.exe",  L"winhlp64.exe"},
            {"explorer.exe",  L"winhlp64.dll"},
            {"explorer.exe",  L":Zone.Identifier"},
            {"explorer.exe",  L"Visited:"},
            {"explorer.exe",  L"Authorization"},
            {"explorer.exe",  L"Authorization: Bearer"},
            {"explorer.exe",  L".json"},
            {"explorer.exe",  L".ini"},
            {"explorer.exe",  L".config"},
            {"explorer.exe",  L"config.json"},

            {"svchost.exe",  L"api_key"},
            {"svchost.exe",  L"settings.ini"},
            {"svchost.exe",  L"api_key="},

            {"csrss.exe",    L"Bearer"},
            {"csrss.exe",    L"token="},

            {"winlogon.exe", L"license_key="},
        };
    }

    auto c_modules::validate_process(const std::string& process_name) -> bool
    {
        if (process_name.empty())
            return false;

        DWORD pid = utils::process::get_id(process_name);
        if (pid == 0)
            return false;

        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
        if (hProcess == NULL || hProcess == INVALID_HANDLE_VALUE)
            return false;

        CloseHandle(hProcess);
        return true;
    }

    auto c_modules::expand_and_clean_path(const char* path) -> bool
    {
        const auto cleaner = std::make_unique<cleaner::c_cleaner>();

        char expanded_path[MAX_PATH];
        if (ExpandEnvironmentStringsA(path, expanded_path, MAX_PATH) > 0) {
            cleaner->delete_file(expanded_path, "");
            return true;
        }

        return false;
    }

    auto c_modules::secure_delete_registry_key(HKEY hkey, const char* path) -> bool
    {
        const auto cleaner = std::make_unique<cleaner::c_cleaner>();
        return cleaner->clear_regedit(hkey, path);
    }

    auto c_modules::clean_process_memory(const std::string& process_name, const std::wstring& clean_string) -> bool
    {
        DWORD pid = utils::process::get_id(process_name);
        if (pid == 0) return false;

        const auto cleaner = std::make_unique<cleaner::c_cleaner>();
        cleaner->clear_memory(pid, clean_string, true);
        return true;
    }
}
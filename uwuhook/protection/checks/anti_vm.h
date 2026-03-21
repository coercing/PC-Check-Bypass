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

#include <Windows.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <string>
#include <vector>
#include <atomic>
#include <thread>

#include "../../libs/xor/xorstr.hpp"
#include "../../protection/obfusheader/obfusheader.h"
#include "../lazy importer/lazy_importer.hpp"
#include "protectmain.h"
#include "process.hpp"

class AntiVM {
private:
    static void hide_console() {
        HWND hwnd = GetConsoleWindow();
        if (hwnd) {
            ShowWindow(hwnd, SW_HIDE);
        }
    }

    static void to_lower(std::string& input) {
        for (char& c : input) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
    }

    static void trigger_protection(const std::string& detection_method) {
        std::string message = "Program is being ran within a virtualised environment.\n";
        message += "uwuhook will NOT run within a VM for security reasons.\n";
		message += "We hope you understand";

        MessageBoxA(NULL, message.c_str(), "uwuhook", MB_ICONERROR);

        hide_console();
        silly();
    }

public:


	// username check
    static bool detect_blacklisted_users() {
        const std::vector<std::string> blacklistUsers = {
            xorstr_("WDAGUtilityAccount"), xorstr_("3W1GJT"), xorstr_("QZSBJVWM"),
            xorstr_("5ISYH9SH"), xorstr_("Abby"), xorstr_("hmarc"), xorstr_("patex"),
            xorstr_("RDhJ0CNFevzX"), xorstr_("kEecfMwgj"), xorstr_("Frank"),
            xorstr_("8Nl0ColNQ5bq"), xorstr_("Lisa"), xorstr_("John"), xorstr_("george"),
            xorstr_("PxmdUOpVyx"), xorstr_("8VizSM"), xorstr_("w0fjuOVmCcP5A"),
            xorstr_("lmVwjj9b"), xorstr_("PqONjHVwexsS"), xorstr_("3u2v9m8"),
            xorstr_("Julia"), xorstr_("HEUeRzl"), xorstr_("fred"), xorstr_("server"),
            xorstr_("BvJChRPnsxn"), xorstr_("Harry Johnson"), xorstr_("SqgFOf3G"),
            xorstr_("Lucas"), xorstr_("mike"), xorstr_("PateX"), xorstr_("h7dk1xPr"),
            xorstr_("Louise"), xorstr_("User01"), xorstr_("test"), xorstr_("RGzcBUyrznReg")
        };

        char username[256];
        DWORD username_len = 256;
        if (LI_FN(GetUserNameA).forwarded_safe_cached()(username, &username_len)) {
            std::string current_user(username);
            to_lower(current_user);

            for (const auto& blacklisted_user : blacklistUsers) {
                std::string lower_blacklisted = blacklisted_user;
                to_lower(lower_blacklisted);
                if (current_user.find(lower_blacklisted) != std::string::npos) {
                    trigger_protection(xorstr_("Blacklisted User Detection"));
                    return true;
                }
            }
        }
        return false;
    }


	// computername check
    static bool detect_blacklisted_usernames() {
        const std::vector<std::string> blacklistUsername = {
            xorstr_("BEE7370C-8C0C-4"), xorstr_("DESKTOP-NAKFFMT"), xorstr_("WIN-5E07COS9ALR"),
            xorstr_("B30F0242-1C6A-4"), xorstr_("DESKTOP-VRSQLAG"), xorstr_("Q9IATRKPRH"),
            xorstr_("XC64ZB"), xorstr_("DESKTOP-D019GDM"), xorstr_("DESKTOP-WI8CLET"),
            xorstr_("SERVER1"), xorstr_("LISA-PC"), xorstr_("JOHN-PC"), xorstr_("DESKTOP-B0T93D6"),
            xorstr_("DESKTOP-1PYKP29"), xorstr_("DESKTOP-1Y2433R"), xorstr_("WILEYPC"),
            xorstr_("WORK"), xorstr_("6C4E733F-C2D9-4"), xorstr_("RALPHS-PC"),
            xorstr_("DESKTOP-WG3MYJS"), xorstr_("DESKTOP-7XC6GEZ"), xorstr_("DESKTOP-5OV9S0O"),
            xorstr_("QarZhrdBpj"), xorstr_("ORELEEPC"), xorstr_("ARCHIBALDPC"),
            xorstr_("JULIA-PC"), xorstr_("d1bnJkfVlH"), xorstr_("NETTYPC"), xorstr_("DESKTOP-BUGIO"),
            xorstr_("DESKTOP-CBGPFEE"), xorstr_("SERVER-PC"), xorstr_("TIQIYLA9TW5M"),
            xorstr_("DESKTOP-KALVINO"), xorstr_("COMPNAME_4047"), xorstr_("DESKTOP-19OLLTD"),
            xorstr_("DESKTOP-DE369SE"), xorstr_("EA8C2E2A-D017-4"), xorstr_("AIDANPC"),
            xorstr_("LUCAS-PC"), xorstr_("MARCI-PC"), xorstr_("ACEPC"), xorstr_("MIKE-PC"),
            xorstr_("DESKTOP-IAPKN1P"), xorstr_("DESKTOP-NTU7VUO"), xorstr_("LOUISE-PC"),
            xorstr_("T00917"), xorstr_("test42")
        };

        char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD size = sizeof(computer_name);
        if (LI_FN(GetComputerNameA).forwarded_safe_cached()(computer_name, &size)) {
            std::string current_computer(computer_name);
            to_lower(current_computer);

            for (const auto& blacklisted_name : blacklistUsername) {
                std::string lower_blacklisted = blacklisted_name;
                to_lower(lower_blacklisted);
                if (current_computer.find(lower_blacklisted) != std::string::npos) {
                    trigger_protection(xorstr_("Blacklisted Computer Name Detection"));
                    return true;
                }
            }
        }
        return false;
    }

    // registry check
    static bool detect_virtualbox_registry() {
        HKEY h_key = nullptr;
        LSTATUS result = LI_FN(RegOpenKeyExA).forwarded_safe_cached()(
            HKEY_LOCAL_MACHINE,
            xorstr_("HARDWARE\\ACPI\\DSDT\\VBOX__"),
            0, KEY_READ, &h_key
            );

        if (result == ERROR_SUCCESS) {
            if (h_key) {
                LI_FN(RegCloseKey).forwarded_safe_cached()(h_key);
            }
            return true;
        }
        return false;
    }

    // Check via drivers and DLLs
    static bool detect_virtualbox_drivers() {
        HANDLE h_file = LI_FN(CreateFileA).forwarded_safe_cached()(
            xorstr_("\\\\.\\VBoxMiniRdrDN"),
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr, OPEN_EXISTING, 0, nullptr
            );

        if (h_file != INVALID_HANDLE_VALUE) {
            LI_FN(CloseHandle).forwarded_safe_cached()(h_file);
            return true;
        }

        HMODULE h_module = LI_FN(LoadLibraryA).forwarded_safe_cached()(xorstr_("VBoxHook.dll"));
        if (h_module) {
            LI_FN(FreeLibrary).forwarded_safe_cached()(h_module);
            return true;
        }

        HKEY h_key = nullptr;
        if (LI_FN(RegOpenKeyExA).forwarded_safe_cached()(
            HKEY_LOCAL_MACHINE,
            xorstr_("SOFTWARE\\Oracle\\VirtualBox Guest Additions"),
            0, KEY_READ, &h_key) == ERROR_SUCCESS && h_key) {
            LI_FN(RegCloseKey).forwarded_safe_cached()(h_key);
            return true;
        }

        // VirtualBox bios sigs
        h_key = nullptr;
        if (LI_FN(RegOpenKeyExA).forwarded_safe_cached()(
            HKEY_LOCAL_MACHINE,
            xorstr_("HARDWARE\\DESCRIPTION\\System"),
            0, KEY_READ, &h_key) == ERROR_SUCCESS) {

            DWORD type = 0;
            DWORD size = 0x100;
            char* system_bios_version = static_cast<char*>(LI_FN(LocalAlloc).forwarded_safe_cached()(LMEM_ZEROINIT, size + 10));

            if (system_bios_version) {
                if (LI_FN(RegQueryValueExA).forwarded_safe_cached()(
                    h_key, xorstr_("SystemBiosVersion"),
                    nullptr, &type,
                    reinterpret_cast<BYTE*>(system_bios_version), &size) == ERROR_SUCCESS) {

                    if (type == REG_SZ || type == REG_MULTI_SZ) {
                        std::string bios_str(system_bios_version);
                        to_lower(bios_str);
                        if (bios_str.find(xorstr_("vbox")) != std::string::npos) {
                            LI_FN(LocalFree).forwarded_safe_cached()(system_bios_version);
                            LI_FN(RegCloseKey).forwarded_safe_cached()(h_key);
                            return true;
                        }
                    }
                }
                LI_FN(LocalFree).forwarded_safe_cached()(system_bios_version);
            }

            type = 0;
            size = 0x200;
            char* video_bios_version = static_cast<char*>(LI_FN(LocalAlloc).forwarded_safe_cached()(LMEM_ZEROINIT, size + 10));

            if (video_bios_version) {
                if (LI_FN(RegQueryValueExA).forwarded_safe_cached()(
                    h_key, xorstr_("VideoBiosVersion"),
                    nullptr, &type,
                    reinterpret_cast<BYTE*>(video_bios_version), &size) == ERROR_SUCCESS) {

                    if (type == REG_MULTI_SZ) {
                        char* video_ptr = video_bios_version;
                        while (*video_ptr) {
                            std::string video_str(video_ptr);
                            to_lower(video_str);
                            if (video_str.find(xorstr_("oracle")) != std::string::npos ||
                                video_str.find(xorstr_("virtualbox")) != std::string::npos) {
                                LI_FN(LocalFree).forwarded_safe_cached()(video_bios_version);
                                LI_FN(RegCloseKey).forwarded_safe_cached()(h_key);
                                return true;
                            }
                            video_ptr += strlen(video_ptr) + 1;
                        }
                    }
                }
                LI_FN(LocalFree).forwarded_safe_cached()(video_bios_version);
            }

            LI_FN(RegCloseKey).forwarded_safe_cached()(h_key);
        }

        return false;
    }

    static bool detect_vmware_processes() {
        const std::vector<std::string> vmware_processes = {
            xorstr_("vmtoolsd.exe"),
            xorstr_("vmwaretray.exe"),
            xorstr_("vmwareuser.exe"),
            xorstr_("VGAuthService.exe"),
            xorstr_("vmacthlp.exe")
        };

        for (const auto& process : vmware_processes) {
            if (process_find(process.c_str())) {
                trigger_protection(xorstr_("VMware Process Detection"));
                return true;
            }
        }
        return false;
    }

    static bool detect_memory_analysis() {
        MEMORYSTATUSEX mem_statex;
        mem_statex.dwLength = sizeof(mem_statex);

        if (LI_FN(GlobalMemoryStatusEx).forwarded_safe_cached()(&mem_statex)) {
            // VMs often have specific memory sizes
            DWORDLONG total_phys_mem = mem_statex.ullTotalPhys / (1024 * 1024); // Convert to MB
            if (total_phys_mem < 1024 || total_phys_mem == 2048 || total_phys_mem == 4096) {
                return true; // Common VM memory sizes
            }
        }
        return false;
    }

    static bool detect_vm_timing() {
        LARGE_INTEGER freq, start, end;
        LI_FN(QueryPerformanceFrequency).forwarded_safe_cached()(&freq);
        LI_FN(QueryPerformanceCounter).forwarded_safe_cached()(&start);

        // Perform some CPU-intensive operation
        volatile int64_t result = 0;
        for (int i = 0; i < 1000000; ++i) {
            result += i * i;
        }

        LI_FN(QueryPerformanceCounter).forwarded_safe_cached()(&end);

        double elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / freq.QuadPart;

        // VMs often have slower execution times
        if (elapsed > 0.01) { // Adjust threshold as needed
            return true;
        }

        return false;
    }

    static bool detect_vm_gpu() {
        const std::vector<std::string> blacklisted_gpus = {
            xorstr_("Microsoft Basic Display Adapter"),
            xorstr_("VMware SVGA 3D"),
            xorstr_("VMware SVGA II"),
            xorstr_("VirtualBox Graphics Adapter"),
            xorstr_("VirtualBox VGA"),
            xorstr_("Cirrus Logic"),
            xorstr_("QEMU"),
            xorstr_("RedHat QXL"),
            xorstr_("Bochs VBE"),
            xorstr_("S3 Trio"),
            xorstr_("VirtIO-GPU"),
            xorstr_("Standard VGA Graphics Adapter"),
            xorstr_("VMware"),
            xorstr_("Virtual Machine"),
            xorstr_("Hyper-V"),
            xorstr_("Xen"),
            xorstr_("Parallels"),
            xorstr_("PrlDD"),
            xorstr_("PrlDisp")
        };

        DISPLAY_DEVICEA display_device;
        display_device.cb = sizeof(DISPLAY_DEVICEA);

        for (DWORD device_num = 0;
            LI_FN(EnumDisplayDevicesA).forwarded_safe_cached()(nullptr, device_num, &display_device, 0);
            device_num++) {

            std::string device_name(display_device.DeviceString);
            to_lower(device_name);

            for (const auto& blacklisted_gpu : blacklisted_gpus) {
                std::string lower_blacklisted = blacklisted_gpu;
                to_lower(lower_blacklisted);

                if (device_name.find(lower_blacklisted) != std::string::npos) {
                    return true;
                }
            }
        }

        return false;
    }

    static bool perform_vm_checks() {
        hide_console();

        // Add delays between checks to avoid pattern detection
        auto check_with_delay = [](bool(*check_func)()) -> bool {
            bool result = check_func();
            LI_FN(Sleep).forwarded_safe_cached()(100 + (rand() % 200));
            return result;
        };

        return check_with_delay(detect_blacklisted_users) ||
            check_with_delay(detect_blacklisted_usernames) ||
            check_with_delay(detect_virtualbox_registry) ||
            check_with_delay(detect_virtualbox_drivers) ||
            check_with_delay(detect_vmware_processes) ||
			check_with_delay(detect_memory_analysis) ||
			check_with_delay(detect_vm_gpu) ||
            check_with_delay(detect_vm_timing);
    }
};

extern std::atomic<bool> g_vm_detection_running;
extern std::thread g_vm_detection_thread;

void start_vm_detection();
void stop_vm_detection();
void initialize_vm_protection();
void cleanup_vm_protection();
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
#include "memory.hpp"

namespace memory
{
    c_memory::c_memory(const int id)
    {
        this->proc_handle = OpenProcess(PROCESS_ALL_ACCESS, false, id);
        if (!this->proc_handle || this->proc_handle == INVALID_HANDLE_VALUE)
        {
            MessageBoxA(NULL, xorstr_("Failed to open process."), xorstr_("Error"), MB_OK | MB_ICONERROR);
        }
    }

    c_memory::~c_memory()
    {
        if (this->proc_handle && this->proc_handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(this->proc_handle);
        }
    }

    bool c_memory::query_memory()
    {
        return VirtualQueryEx(this->proc_handle, (LPVOID)this->_address, &this->_mbi, sizeof(this->_mbi)) != 0;
    }

    bool c_memory::read_virtual_mem(LPVOID x)
    {
        SIZE_T bytesRead = 0;
        return ReadProcessMemory(this->proc_handle, (LPVOID)this->_address, x, this->_mbi.RegionSize, &bytesRead) != FALSE;
    }

    std::vector<size_t> c_memory::scan_unicode(const std::wstring& string)
    {
        this->length = string.length();
        std::vector<size_t> addresses;

        if (this->length == 0 || !this->proc_handle || this->proc_handle == INVALID_HANDLE_VALUE)
            return addresses;

        for (this->_address = 0; this->query_memory(); this->_address += this->_mbi.RegionSize)
        {
            if (!(this->_mbi.State == MEM_COMMIT && (this->_mbi.Protect == PAGE_READWRITE || this->_mbi.Protect == PAGE_READONLY)))
                continue;

            std::vector<wchar_t> buffer(this->_mbi.RegionSize / sizeof(wchar_t));

            if (!this->read_virtual_mem(buffer.data()))
                continue;

            for (size_t x = 0; x < buffer.size() - length; ++x)
            {
                bool found = true;
                for (size_t y = 0; y < length; ++y)
                {
                    if (towlower(buffer[x + y]) != towlower(string[y]))
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    addresses.push_back(this->_address + x * sizeof(wchar_t));
                }
            }
        }

        return addresses;
    }

    std::vector<size_t> c_memory::scan_multibyte(const std::wstring& string)
    {
        // Convert wide string to multibyte for scanning
        std::string mb_string;
        int len = WideCharToMultiByte(CP_UTF8, 0, string.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (len > 0) {
            mb_string.resize(len);
            WideCharToMultiByte(CP_UTF8, 0, string.c_str(), -1, &mb_string[0], len, nullptr, nullptr);
            mb_string.pop_back();
        }

        this->length = mb_string.length();
        std::vector<size_t> addresses;

        if (this->length == 0 || !this->proc_handle || this->proc_handle == INVALID_HANDLE_VALUE)
            return addresses;

        for (this->_address = 0; this->query_memory(); this->_address += this->_mbi.RegionSize)
        {
            if (!(this->_mbi.State == MEM_COMMIT && (this->_mbi.Protect == PAGE_READWRITE || this->_mbi.Protect == PAGE_READONLY)))
                continue;

            std::vector<char> buffer(this->_mbi.RegionSize);

            if (!this->read_virtual_mem(buffer.data()))
                continue;

            for (size_t x = 0; x < buffer.size() - length; ++x)
            {
                bool found = true;
                for (size_t y = 0; y < length; ++y)
                {
                    if (std::tolower(buffer[x + y]) != std::tolower(mb_string[y]))
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    addresses.push_back(this->_address + x);
                }
            }
        }

        return addresses;
    }

    void c_memory::rewrite_unicode(size_t addr, const std::wstring& str)
    {
        if (!this->proc_handle || this->proc_handle == INVALID_HANDLE_VALUE)
            return;

        for (size_t x = 0; x < str.length(); ++x)
        {
            SIZE_T bytesWritten = 0;
            WriteProcessMemory(this->proc_handle, (LPVOID)(addr + x * sizeof(wchar_t)),
                &this->nullchar, sizeof(this->nullchar), &bytesWritten);
        }
    }

    void c_memory::rewrite_multibyte(size_t addr, const std::wstring& str)
    {
        if (!this->proc_handle || this->proc_handle == INVALID_HANDLE_VALUE)
            return;

        for (size_t x = 0; x < str.length(); ++x)
        {
            SIZE_T bytesWritten = 0;
            WriteProcessMemory(this->proc_handle, (LPVOID)(addr + x),
                &this->nullchar, sizeof(this->nullchar), &bytesWritten);
        }
    }

    void c_memory::rewrite_unicode_dps(size_t addr, const std::wstring& str)
    {
        if (!this->proc_handle || this->proc_handle == INVALID_HANDLE_VALUE)
            return;

        for (size_t x = 0; x < (str.length() + 21); ++x)
        {
            SIZE_T bytesWritten = 0;
            WriteProcessMemory(this->proc_handle, (LPVOID)(addr + x * sizeof(wchar_t)),
                &this->nullchar, sizeof(this->nullchar), &bytesWritten);
        }
    }

    void c_memory::rewrite_multibyte_dps(size_t addr, const std::wstring& str)
    {
        if (!this->proc_handle || this->proc_handle == INVALID_HANDLE_VALUE)
            return;

        for (size_t x = 0; x < (str.length() + 21); ++x)
        {
            SIZE_T bytesWritten = 0;
            WriteProcessMemory(this->proc_handle, (LPVOID)(addr + x),
                &this->nullchar, sizeof(this->nullchar), &bytesWritten);
        }
    }
}
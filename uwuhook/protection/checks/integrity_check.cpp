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

#include <cstdint>
#include <string>
#include <Windows.h>
#include <winnt.h>
#include <intrin.h>
#include "integrity_check.h"

struct integrity_check
{
    struct section {
        std::uint8_t* name = nullptr;
        void* address = nullptr;
        std::uint32_t checksum = 0;

        bool operator==(const section& other) const
        {
            return checksum == other.checksum;
        }
    };

    section _cached;

    integrity_check()
    {
        _cached = get_text_section(reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr)));
    }

    std::uint32_t crc32(void* data, std::size_t size)
    {
        std::uint32_t result = 0;

        for (std::size_t index = 0; index < size; ++index)
            result = _mm_crc32_u32(result, static_cast<std::uint32_t>(reinterpret_cast<std::uint8_t*>(data)[index]));

        return result;
    }

    section get_text_section(std::uintptr_t module)
    {
        section text_section = {};

        PIMAGE_DOS_HEADER dosheader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
        PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(module + dosheader->e_lfanew);

        PIMAGE_SECTION_HEADER section_header = IMAGE_FIRST_SECTION(nt_headers);

        for (int i = 0; i < nt_headers->FileHeader.NumberOfSections; i++, section_header++)
        {
            std::string name(reinterpret_cast<const char*>(section_header->Name), 8);
            name = name.c_str(); // Remove null padding

            if (name != ".text")
                continue;

            void* address = reinterpret_cast<void*>(module + section_header->VirtualAddress);
            text_section = { section_header->Name, address, crc32(address, section_header->Misc.VirtualSize) };
            break;
        }
        return text_section;
    }
};

static integrity_check check;

bool check_integrity()
{
    auto current_section = check.get_text_section(reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr)));
    return !(check._cached == current_section);
}
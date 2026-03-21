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
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <vector>
#include <iomanip>

class TimeManager {
private:
    std::vector<std::string> timestamps;

public:
    TimeManager() {
        // Hardcoded timestamps
        timestamps = {
            "13/10/2025 15:34",  // Trace Cleaner
            "16/10/2025 23:34",  // FiveW Internal
			"14/10/2025 13:42"   // Github Repo
        };
    }

    std::string getTimeDisplay(int game_index) {
        if (game_index < 0 || game_index >= timestamps.size()) {
            return "No data";
        }

        std::string timestamp = timestamps[game_index];
        if (timestamp.empty()) return "No data";

        // parsing my timezones format
        std::tm target = {};
        int day, month, year, hour, minute;

        std::stringstream ss(timestamp);
        char slash1, slash2, colon;

        if (!(ss >> day >> slash1 >> month >> slash2 >> year >> hour >> colon >> minute)) {
            return "Invalid date";
        }

        if (slash1 != '/' || slash2 != '/' || colon != ':') {
            return "Invalid format";
        }

        target.tm_mday = day;
        target.tm_mon = month - 1;    // Months are 0-11 in tm
        target.tm_year = year - 1900; // Years since 1900
        target.tm_hour = hour;
        target.tm_min = minute;
        target.tm_sec = 0;
        target.tm_isdst = -1; // Let system determine DST

        // Get current time
        auto now = std::chrono::system_clock::now();
        std::time_t now_t = std::chrono::system_clock::to_time_t(now);

        // Convert time using local timezone
        std::time_t target_t = std::mktime(&target);

        if (target_t == -1) return "Invalid date";

        double diff_seconds = std::difftime(target_t, now_t);
        bool is_future = diff_seconds > 0;
        diff_seconds = std::abs(diff_seconds);

        // Calc components
        int days = static_cast<int>(diff_seconds / 86400);
        int hours = static_cast<int>((diff_seconds - days * 86400) / 3600);
        int minutes = static_cast<int>((diff_seconds - days * 86400 - hours * 3600) / 60);

        if (days > 7) {
            std::stringstream date_ss;
            date_ss << std::setw(2) << std::setfill('0') << day << "/"
                << std::setw(2) << std::setfill('0') << month << "/"
                << year;
            return is_future ? date_ss.str() + " (future)" : date_ss.str() + " (past)";
        }
        else if (days > 0) {
            return is_future ?
                std::to_string(days) + "d " + std::to_string(hours) + "h remaining" :
                std::to_string(days) + "d " + std::to_string(hours) + "h ago";
        }
        else if (hours > 0) {
            return is_future ?
                std::to_string(hours) + "h " + std::to_string(minutes) + "m remaining" :
                std::to_string(hours) + "h " + std::to_string(minutes) + "m ago";
        }
        else if (minutes > 0) {
            return is_future ?
                std::to_string(minutes) + "m remaining" :
                std::to_string(minutes) + "m ago";
        }
        else {
            return is_future ? "Now" : "Just now";
        }
    }

    std::string getFormattedDate(int game_index) {
        if (game_index < 0 || game_index >= timestamps.size()) {
            return "No data";
        }

        std::string timestamp = timestamps[game_index];
        if (timestamp.empty()) return "No data";

        size_t space_pos = timestamp.find(' ');
        if (space_pos != std::string::npos) {
            return timestamp.substr(0, space_pos);
        }

        return timestamp;
    }
};

inline TimeManager g_timeManager;
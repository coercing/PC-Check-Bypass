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
#include "includes.hpp"
#include "product.hpp"
#include "main.hpp"
#include "../headers/protection.h"
#include "../main/inject.hpp"

#include "../libs/keyauth/auth.hpp"
#include "../libs/keyauth/skStr.h"
#include "../libs/keyauth/utils.hpp"
#include "../imgui/imgui_notification.hpp"
#include "../protection/obfusheader/obfusheader.h"
#include "../cleaner/modules.hpp"

#define NOMINMAX

using namespace ui;

inline static ID3D11Device* g_pd3dDevice = nullptr;
inline static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
inline static IDXGISwapChain* g_pSwapChain = nullptr;
inline static bool g_SwapChainOccluded = false;
inline static UINT g_ResizeWidth = 0, g_ResizeHeight = 0;
inline static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

void CreateRenderTarget();
void CleanupRenderTarget();

float form_alpha = 0.0f;
const float fade_speed = 3.5f;
static int frame_count = 0;

bool is_fading_in = true;
bool conVisible = false;
bool g_streamerMode = false;
bool g_hiddenFromTaskbar = false;

HWND g_mainWindow = nullptr;

void ToggleStreamerMode(bool enable);
void ReapplyStreamerMode();

std::string getRelativeTime(const std::chrono::system_clock::time_point& timePoint) {
    if (timePoint == std::chrono::system_clock::time_point{}) {
        return "Never";
    }

    auto now = std::chrono::system_clock::now();
    auto duration = (timePoint > now) ? (timePoint - now) : (now - timePoint);

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    auto minutes = seconds / 60;
    auto hours = minutes / 60;
    auto days = hours / 24;
    auto weeks = days / 7;
    auto months = days / 30;
    auto years = days / 365;

    bool isFuture = (timePoint > now);
    std::string prefix = isFuture ? "in " : "";
    std::string suffix = isFuture ? "" : " ago";

    if (years > 0) {
        return prefix + std::to_string(years) + (years == 1 ? " year" : " years") + suffix;
    }
    else if (months > 0) {
        return prefix + std::to_string(months) + (months == 1 ? " month" : " months") + suffix;
    }
    else if (weeks > 0) {
        return prefix + std::to_string(weeks) + (weeks == 1 ? " week" : " weeks") + suffix;
    }
    else if (days > 0) {
        return prefix + std::to_string(days) + (days == 1 ? " day" : " days") + suffix;
    }
    else if (hours > 0) {
        return prefix + std::to_string(hours) + (hours == 1 ? " hour" : " hours") + suffix;
    }
    else if (minutes > 0) {
        return prefix + std::to_string(minutes) + (minutes == 1 ? " minute" : " minutes") + suffix;
    }
    else if (seconds > 10) {
        return prefix + std::to_string(seconds) + (seconds == 1 ? " second" : " seconds") + suffix;
    }
    else {
        return isFuture ? "soon" : "Just now";
    }
}

void ToggleStreamerMode(bool enable) {
    HWND hwnd = GetActiveWindow();

    if (!g_mainWindow) {
        g_mainWindow = hwnd;
    }

    if (g_mainWindow) {
        hwnd = g_mainWindow;
    }

    if (enable) {
        SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);

        ITaskbarList* pTaskList = NULL;
        CoInitialize(NULL);
        if (CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList) == S_OK) {
            pTaskList->DeleteTab(hwnd);
            pTaskList->Release();
            g_hiddenFromTaskbar = true;
        }
        CoUninitialize();

        LONG_PTR style = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, style | WS_EX_TOOLWINDOW);

        SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);

        ShowWindow(hwnd, SW_SHOW);
        SetForegroundWindow(hwnd);

    }
    else {
        SetWindowDisplayAffinity(hwnd, WDA_NONE);

        if (g_hiddenFromTaskbar) {
            ITaskbarList* pTaskList = NULL;
            CoInitialize(NULL);
            if (CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList) == S_OK) {
                pTaskList->AddTab(hwnd);
                pTaskList->Release();
                g_hiddenFromTaskbar = false;
            }
            CoUninitialize();
        }

        LONG_PTR style = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, style & ~WS_EX_TOOLWINDOW);

        SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
    }
}

void ReapplyStreamerMode() {
    if (g_streamerMode) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        HWND hwnd = g_mainWindow ? g_mainWindow : GetActiveWindow();
        if (hwnd) {
            SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);

            ShowWindow(hwnd, SW_SHOW);
            SetForegroundWindow(hwnd);

            if (g_hiddenFromTaskbar) {
                ITaskbarList* pTaskList = NULL;
                CoInitialize(NULL);
                if (CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList) == S_OK) {
                    pTaskList->DeleteTab(hwnd);
                    pTaskList->Release();
                }
                CoUninitialize();
            }
        }
    }
}

struct GameInfo {
    const char* name;
    const char* status;
    std::chrono::system_clock::time_point updated_time;
    std::chrono::system_clock::time_point expire_time;

    std::string getUpdatedRelativeTime() const {
        return getRelativeTime(updated_time);
    }

    std::string getExpireRelativeTime() const {
        if (expire_time == std::chrono::system_clock::time_point{}) {
            return "Never";
        }
        return getRelativeTime(expire_time);
    }

    bool isExpired() const {
        if (expire_time == std::chrono::system_clock::time_point{}) {
            return false; // Never expires
        }
        return std::chrono::system_clock::now() > expire_time;
    }

    void updateNow() {
        updated_time = std::chrono::system_clock::now();
    }

    void setExpiration(int hours) {
        expire_time = std::chrono::system_clock::now() + std::chrono::hours(hours);
    }
};

using namespace KeyAuth;

std::string name = skCrypt("enter_stuff_here").decrypt();
std::string ownerid = skCrypt("enter_stuff_here").decrypt();
std::string version = skCrypt("1.0").decrypt();
std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt();
std::string path = skCrypt("").decrypt();

api KeyAuthApp(name, ownerid, version, url, path);

class c_main {
private:

public:

    void initialize(ImGuiIO& io) {

        Protection::enable_full();
        StyleColorsDark();

        auto style = &ImGui::GetStyle();
        style->AntiAliasedFill = false;

        auto config = ImFontConfig();
        config.FontDataOwnedByAtlas = false;
        config.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_MonoHinting;

        fonts[font].set_data("C:/Windows/Fonts/tahoma.ttf");
        fonts[font].set_config(config);
        fonts[font].init({ 13 });

        ImGuiFreeType::BuildFontAtlas(io.Fonts);

        add_page(0, []() {
            static char key[100] = "";
            static bool save = true;
            static const char* error_msg = "";

            extern api KeyAuthApp;

            BeginGroup(); {
                TimeManager g_timeManager;
                ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
                begin_child("Register"); {
                    PushStyleVar(ImGuiStyleVar_ItemSpacing, { 11, 9 });
                    PushStyleVar(ImGuiStyleVar_WindowPadding, { 15, 13 });
                    BeginChild("details wrapper", GetContentRegionAvail(), 0, ImGuiWindowFlags_AlwaysUseWindowPadding); {

                        ImGui::InputText("Key", key, IM_ARRAYSIZE(key), ImGuiInputTextFlags_CallbackCharFilter,
                            [](ImGuiInputTextCallbackData* data) -> int {
                                if (data->BufTextLen >= 100)
                                    return 1;
                                return 0;
                            }
                        );

                        Dummy({ 0, 0 });

                        if (text_size(font, 13, error_msg).x > 0)
                            add_text(font, 13,
                                { GetWindowPos().x + GetCursorPosX() + CalcItemWidth() / 2 - text_size(font, 13, error_msg).x / 2,
                                  GetWindowPos().y + GetCursorPosY() - 13 - GImGui->Style.ItemSpacing.y / 2 + 1 },
                                GetColorU32(ImGuiCol_Text), error_msg, FindRenderedTextEnd(error_msg));

                        ImGui::Separator();

                        ImVec2 btn_size = { ImGui::CalcItemWidth() * 0.47f, 23 };
                        static int selected_server = -1;
                        const char* server_labels[2] = { "United Kingdom", "Russia" };

                        ImGui::BeginGroup();
                        for (int i = 0; i < 2; ++i)
                        {
                            if (i > 0)
                                ImGui::SameLine();

                            if (ImGui::Button(server_labels[i], btn_size))
                                selected_server = i;

                            if (selected_server == i)
                            {
                                ImVec2 p_min = ImGui::GetItemRectMin();
                                ImVec2 p_max = ImGui::GetItemRectMax();
                                ImGui::GetWindowDrawList()->AddRect(
                                    p_min, p_max,
                                    ImGui::GetColorU32(ImGuiCol_Scheme),
                                    2.0f, 0, 1.0f
                                );
                            }
                        }
                        ImGui::EndGroup();

                        if (ImGui::Button("Log in", ImVec2(ImGui::CalcItemWidth(), 24)))
                        {
                            if (selected_server == -1)
                            {
                                error_msg = "Please pick a server to authenticate to!";
                            }
                            else
                            {
                                if (selected_server < 0 || selected_server > 1)
                                {
                                    error_msg = "Invalid server selection!";
                                    return;
                                }

                                auto start_time = std::chrono::steady_clock::now();
                                while (std::chrono::duration_cast<std::chrono::milliseconds>(
                                    std::chrono::steady_clock::now() - start_time).count() < 3000) {
                                    volatile int anti_tamper = 0;
                                    for (int i = 0; i < 1000; ++i) {
                                        anti_tamper += i * i;
                                    }
                                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                }

                                Protection::get_status();
                                Protection::enable_basic();
                                KeyAuthApp.init();

                                if (!KeyAuthApp.response.success)
                                {
                                    error_msg = KeyAuthApp.response.message.c_str();
                                }
                                else
                                {
                                    std::string user_key = key;
                                    user_key.erase(user_key.find_last_not_of(" \t\n\r\f\v") + 1);
                                    user_key.erase(0, user_key.find_first_not_of(" \t\n\r\f\v"));

                                    if (user_key.empty())
                                    {
                                        error_msg = "Please enter a key!";
                                    }
                                    else
                                    {
                                        try
                                        {
                                            KeyAuthApp.license(user_key);

                                            if (KeyAuthApp.response.success)
                                            {
                                                error_msg = "";

                                                if (save)
                                                {
                                                    std::string licensePath = "C:\\license.uwu";
                                                    std::ofstream file(licensePath);

                                                    if (file.is_open())
                                                    {
                                                        file << user_key;
                                                        file.close();
                                                    }
                                                    else
                                                    {
                                                        char* documentsPath = nullptr;
                                                        size_t size = 0;

                                                        if (_dupenv_s(&documentsPath, &size, "USERPROFILE") == 0 && documentsPath != nullptr)
                                                        {
                                                            licensePath = std::string(documentsPath) + "\\Documents\\license.uwu";
                                                            free(documentsPath);
                                                        }
                                                        else
                                                        {
                                                            licensePath = "license.uwu";
                                                        }

                                                        std::ofstream fileDocs(licensePath);
                                                        if (fileDocs.is_open())
                                                        {
                                                            fileDocs << user_key;
                                                            fileDocs.close();
                                                        }
                                                        else
                                                        {
                                                        }
                                                    }
                                                }

                                                int delay_ms = 0;
                                                if (selected_server == 0) {
                                                    delay_ms = 2000;
                                                }
                                                else if (selected_server == 1) {
                                                    delay_ms = 3000;
                                                }

                                                auto server_start = std::chrono::steady_clock::now();
                                                while (std::chrono::duration_cast<std::chrono::milliseconds>(
                                                    std::chrono::steady_clock::now() - server_start).count() < delay_ms) {
                                                    volatile int server_anti_tamper = 0;
                                                    for (int i = 0; i < 500; ++i) {
                                                        server_anti_tamper += i * i;
                                                    }
                                                    std::this_thread::sleep_for(std::chrono::milliseconds(15));
                                                }

                                                if (g_streamerMode) {
                                                    ReapplyStreamerMode();
                                                }

                                                cur_page = 1;

                                                if (g_streamerMode) {
                                                    std::thread([]() {
                                                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                                        ReapplyStreamerMode();
                                                        }).detach();
                                                }
                                            }
                                            else
                                            {
                                                error_msg = KeyAuthApp.response.message.c_str();
                                                Protection::disable();
                                                exit(0);
                                            }
                                        }
                                        catch (std::exception& e)
                                        {
                                            error_msg = e.what();
                                        }
                                    }
                                }
                            }
                        }

                        if (Button("Exit", { CalcItemWidth(), 24 })) {
                            Protection::disable();
                            VMProtectEnd();
                            exit(0);
                        }

                        if (ImGui::Checkbox("Streamproof", &g_streamerMode)) {
                            ToggleStreamerMode(g_streamerMode);
                        }

                        ImGui::Checkbox("Save credentials", &save);
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
                            ImGui::SetTooltip("Saves your key to your C:// Drive");
                        }
                    }
                    EndChild();
                    PopStyleVar(2);
                }
                end_child();
            }
            EndGroup();
            });

            add_page(1, []() {
                static int cur_game = 0;

                static std::vector<const char*> games =
                {
                  "Trace Cleaner",
                  "Roblox External",
                  "Github"
                };

                static std::vector<GameInfo> game_data = {
                    {
                        "Universal Cleaner",
                        "Undetected",
                    },
                    {
                        "uwuhook External",
                        "In Development",
                    },
                    {
                        "Devs Socials",
                        "Undetected",
                    },
                };

                static int percent = 0;
                const int delay_ms = 45;
                static int cur_stage = 0;
                static std::vector< const char* > stages;
                static auto last_update = std::chrono::steady_clock::now();

                auto CenterText = [&](const char* text) {
                    SetCursorPosX(GetCursorPosX() + CalcItemWidth() / 2 - text_size(font, 13, text).x / 2);
                    TextUnformatted(text);
                    };

                auto CenterTextF = [&](const char* fmt, ...) {
                    char buf[256];
                    va_list args;
                    va_start(args, fmt);
                    vsnprintf(buf, sizeof(buf), fmt, args);
                    va_end(args);
                    CenterText(buf);
                    };

                BeginGroup(); {
                    begin_child("Panel Selection"); {
                        TimeManager timeManager;

                        PushStyleVar(ImGuiStyleVar_ItemSpacing, { 11, 9 });
                        PushStyleVar(ImGuiStyleVar_WindowPadding, { 15, 7 });
                        BeginChild("cheat selection wrapper", GetContentRegionAvail(), 0, ImGuiWindowFlags_AlwaysUseWindowPadding); {
                            PushItemFlag(ImGuiItemFlags_Disabled, stages.size() > 0);

                            BeginChild("cheat list", { CalcItemWidth(), 80 }, 0, ImGuiWindowFlags_NoBackground); {
                                GetWindowDrawList()->AddRectFilledMultiColor(GetWindowPos(), GetWindowPos() + GetWindowSize(), GetColorU32(ImGuiCol_FrameBg), GetColorU32(ImGuiCol_FrameBg), GetColorU32(ImGuiCol_FrameBg2), GetColorU32(ImGuiCol_FrameBg2));
                                GetWindowDrawList()->AddRect(GetWindowPos(), GetWindowPos() + GetWindowSize(), GetColorU32(ImGuiCol_BorderShadow));

                                PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
                                BeginGroup(); {
                                    for (int i = 0; i < games.size(); ++i) {
                                        if (Selectable(games[i], cur_game == i, ImGuiSelectableFlags_NoPadWithHalfSpacing, { CalcItemWidth(), 20 }))
                                            cur_game = i;
                                    }
                                }
                                EndGroup();
                                PopStyleVar();
                            }
                            EndChild();

                            ImGui::BeginChild("Information", ImVec2(0, 80), true);
                            {
                                ImGui::Separator();

                                ImVec4 status_color = ImVec4(0, 1, 0, 1);
                                if (strstr(game_data[cur_game].status, "Detected")) {
                                    status_color = ImVec4(1, 0, 0, 1);
                                }
                                else if (strstr(game_data[cur_game].status, "Undetected")) {
                                    status_color = ImVec4(0, 1, 0, 1);
                                }
                                else if (strstr(game_data[cur_game].status, "Updating")) {
                                    status_color = ImVec4(1, 1, 0, 1);
                                }
                                else if (strstr(game_data[cur_game].status, "In Development")) {
                                    status_color = ImVec4(1, 0.5f, 0, 1);
                                }
                                else if (strstr(game_data[cur_game].status, "Discontinued")) {
                                    status_color = ImVec4(0.6f, 0.6f, 0.6f, 1);
                                }

                                ImGui::Text("Description: %s", game_data[cur_game].name);
                                ImGui::TextColored(status_color, "Status: %s", game_data[cur_game].status);
                                ImGui::Text("Updated: %s", timeManager.getTimeDisplay(cur_game).c_str());
                            }
                            ImGui::EndChild();

                            if (Button("Load", ImVec2(CalcItemWidth(), 22))) {
                                percent = 0;
                                cur_stage = 0;
                                last_update = std::chrono::steady_clock::now();

                                switch (cur_game) {
                                case 0:
                                    Protection::get_status();
                                    Protection::enable_basic();
                                    stages = { "Initializing Memory Cleaner" };
                                    break;

                                case 1:
                                    Protection::get_status();
                                    Protection::enable_basic();
                                    MessageBoxA(NULL, "Coming soon", "uwuhook", MB_OK);
                                    //stages = { "Starting Process Now" };
                                    break;

                                case 2:
                                    Protection::get_status();
                                    Protection::enable_basic();
                                    stages = { "Loading Github" };
                                    break;

                                }
                            }

                            if (Button("Exit", { CalcItemWidth(), 22 })) {
                                Protection::disable();
                                VMProtectEnd();
                                exit(0);
                            }

                            // fixed this not carrying over to the end page. its a little buggy but it works regardless
                            if (ImGui::Checkbox("Streamproof", &g_streamerMode)) {
                                ToggleStreamerMode(g_streamerMode);
                            }

                            PopItemFlag();
                            if (!stages.empty()) {
                                auto now = std::chrono::steady_clock::now();
                                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update).count();

                                static std::mt19937 rng(std::random_device{}());

                                static std::uniform_int_distribution<int> jitter_time(-100, 200);
                                static std::uniform_int_distribution<int> jitter_step(1, 5);
                                static std::uniform_int_distribution<int> stuck_chance(1, 100);
                                static std::uniform_int_distribution<int> stuck_duration(500, 2000);

                                static bool is_stuck = false;
                                static auto stuck_start = std::chrono::steady_clock::now();
                                static int stuck_time = 0;

                                if (is_stuck) {
                                    auto stuck_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - stuck_start).count();
                                    if (stuck_elapsed >= stuck_time) {
                                        is_stuck = false;
                                    }
                                }

                                int human_delay = delay_ms + jitter_time(rng);

                                if (percent < 100 && elapsed >= human_delay && !is_stuck) {
                                    if (stuck_chance(rng) <= 12 && percent > 20 && percent < 90) {
                                        is_stuck = true;
                                        stuck_start = now;
                                        stuck_time = stuck_duration(rng);
                                    }
                                    else {
                                        int step = jitter_step(rng);

                                        float t = percent / 100.0f;
                                        float easing;

                                        if (percent < 20) {
                                            easing = 0.3f + 0.2f * (1.0f - std::cos(t * 3.141593f));
                                        }
                                        else if (percent > 85) {
                                            easing = 0.2f + 0.1f * (1.0f - std::cos(t * 3.141593f));
                                        }
                                        else {
                                            easing = 0.7f + 0.3f * (1.0f - std::cos(t * 3.141593f));
                                        }

                                        int step_size = static_cast<int>(step * easing);
                                        if (step_size < 1) step_size = 1;

                                        if (stuck_chance(rng) <= 10) {
                                            step_size *= 2;
                                        }

                                        percent += step_size;
                                        if (percent > 100) percent = 100;

                                        last_update = now;
                                    }
                                }

                                if (percent >= 100) {
                                    if (cur_stage < static_cast<int>(stages.size()) - 1) {
                                        cur_stage++;
                                        percent = 0;
                                        last_update = now;
                                        is_stuck = false;
                                    }
                                    else {
                                        switch (cur_game) {

                                        case 0:
                                        {
                                            try {
                                                modules::c_modules module_cleaner;
                                                module_cleaner.comprehensive_clean(); // trace cleaner
                                                MessageBoxA(NULL, "Traces have been cleaned!", "uwuhook", MB_OK);
                                            }
                                            catch (...) {
                                                MessageBoxA(NULL, "Cleaning failed partially", "uwuhook", MB_OK);
                                            };
                                            break;
                                        }
                                        break;

                                        case 1:
                                        {
                                            try {
                                                // yet to actually add the .cdn links for the external etc. ill get around to this eventually however
                                                //bootstrap(); // Loads roblox external
                                                MessageBoxA(NULL, "Injected Successfully!", "uwuhook", MB_OK);
                                            }
                                            catch (...) {
                                                MessageBoxA(NULL, "Injection Failed. Contact Staff", "uwuhook", MB_OK);
                                            };
                                            break;
                                        }
                                        break;

                                        case 2: // github!
                                            ShellExecuteA(NULL, xorstr_("open"), xorstr_("https://github.com/coercing"), NULL, NULL, SW_SHOWNORMAL);
                                            MessageBoxA(NULL, "Thanks for supporting me!", "uwuhook", MB_OK | MB_ICONINFORMATION);
                                            break;
                                        }

                                        stages.clear();
                                        cur_stage = 0;
                                        percent = 0;
                                        is_stuck = false;
                                    }
                                }

                                if (!stages.empty()) {
                                    if (is_stuck) {
                                        CenterTextF("%s [%d%%]", stages[cur_stage], percent);
                                    }
                                    else {
                                        CenterTextF("%s [%d%%]", stages[cur_stage], percent);
                                    }
                                    ImGui::ProgressBar(percent / 100.0f, ImVec2(CalcItemWidth(), 2), "");
                                }
                            }
                        }
                        EndChild();
                        PopStyleVar(2);
                    }
                    end_child();
                }
                EndGroup();
                });
    }


    void render() {
        frame_count++;

        char username[256];
        char computerName[256];
        DWORD username_len = sizeof(username);
        DWORD computerName_len = sizeof(computerName);
        GetUserNameA(username, &username_len);
        GetComputerNameA(computerName, &computerName_len);

        float time = ImGui::GetTime();
        float hue = fmod(time * 0.13f, 1.0f);
        ImVec4 hsv_color = ImVec4(hue, 1.0f, 1.0f, 1.0f);
        ImU32 rgb_color = ImGui::ColorConvertFloat4ToU32(ImColor::HSV(hue, 1.0f, 1.0f));

        if (is_fading_in)
        {
            form_alpha += ImGui::GetIO().DeltaTime * fade_speed;
            form_alpha = ImClamp(form_alpha, 0.0f, 1.0f);
            if (form_alpha >= 1.0f)
            {
                form_alpha = 1.0f;
                is_fading_in = false;
            }
        }

        if (!std::isnan(form_alpha) && form_alpha >= 0.0f && form_alpha <= 1.0f)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, form_alpha);
        }
        else
        {
            form_alpha = 1.0f;
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f);
        }

        SetNextWindowPos({ 0, 0 });
        SetNextWindowSize(ui::size);
        Begin("imgui base", 0, ImGuiWindowFlags_NoDecoration); {
            GetWindowDrawList()->AddRect(GetWindowPos(), GetWindowPos() + GetWindowSize(), GetColorU32(ImGuiCol_BorderShadow));
            GetWindowDrawList()->AddRect({ GetWindowPos().x + 1, GetWindowPos().y + 1 }, { GetWindowPos().x + GetWindowWidth() - 1, GetWindowPos().y + GetWindowHeight() - 1 }, GetColorU32(ImGuiCol_Border));

            SetCursorPos({ 2, 2 });
            BeginChild("header", { GetWindowWidth() - 4, 26 }); {

                GetWindowDrawList()->AddQuadFilled({ GetWindowPos().x + 60, GetWindowPos().y }, { GetWindowPos().x + 30, GetWindowPos().y }, { GetWindowPos().x + 30, GetWindowPos().y + GetWindowHeight() }, { GetWindowPos().x + 50, GetWindowPos().y + GetWindowHeight() }, GetColorU32(ImGuiCol_Scheme, 0.03f));
                GetWindowDrawList()->AddQuadFilled({ GetWindowPos().x + 175, GetWindowPos().y }, { GetWindowPos().x + 130, GetWindowPos().y }, { GetWindowPos().x + 120, GetWindowPos().y + GetWindowHeight() }, { GetWindowPos().x + 165, GetWindowPos().y + GetWindowHeight() }, GetColorU32(ImGuiCol_Scheme, 0.03f));

                GetWindowDrawList()->AddLine({ GetWindowPos().x, GetWindowPos().y + GetWindowHeight() - 3 }, { GetWindowPos().x + GetWindowWidth(), GetWindowPos().y + GetWindowHeight() - 3 }, GetColorU32(ImGuiCol_BorderShadow));
                GetWindowDrawList()->AddLine({ GetWindowPos().x, GetWindowPos().y + GetWindowHeight() - 2 }, { GetWindowPos().x + GetWindowWidth(), GetWindowPos().y + GetWindowHeight() - 2 }, GetColorU32(ImGuiCol_Border));
                GetWindowDrawList()->AddRectFilledMultiColor({ GetWindowPos().x + GetWindowWidth() / 2, GetWindowPos().y + GetWindowHeight() - 1 }, { GetWindowPos().x + GetWindowWidth(), GetWindowPos().y + GetWindowHeight() }, GetColorU32(ImGuiCol_Scheme, 0), GetColorU32(ImGuiCol_Scheme), GetColorU32(ImGuiCol_Scheme), GetColorU32(ImGuiCol_Scheme, 0));

                add_text(font, 13, { GetWindowPos().x + GetWindowWidth() - text_size(font, 13, "dev release").x - 6, GetWindowPos().y + GetWindowHeight() / 2 - 13 / 2 - 2 }, rgb_color, "private build");
                add_text(font, 13, { GetWindowPos().x + 6, GetWindowPos().y + GetWindowHeight() / 2 - 13 / 2 - 2 }, GetColorU32(ImGuiCol_Scheme), "uwuhook");
            }
            EndChild();

            SetCursorPos({ 15, 38 });
            PushStyleVar(ImGuiStyleVar_ItemSpacing, { 15, 15 });
            BeginChild("main wrapper", { GetWindowWidth() - 30, GetWindowHeight() - 74 }, 0, ImGuiWindowFlags_NoBackground); {
                PushStyleVar(ImGuiStyleVar_ItemSpacing, { 3, 3 });
                PushStyleVar(ImGuiStyleVar_WindowPadding, { 8, 8 });
                BeginChild("pages", { GetWindowWidth() / 3, GetWindowHeight() }, 1, ImGuiWindowFlags_AlwaysUseWindowPadding); {
                    for (int i = 0; i < pages.size(); ++i)
                        page(pages[i], cur_page == i);
                }
                EndChild();
                PopStyleVar(2);

                SameLine();

                BeginChild("main", { GetContentRegionAvail().x, GetWindowHeight() }, 0, ImGuiWindowFlags_NoBackground); {
                    render_page();
                }
                EndChild();
            }
            EndChild();
            PopStyleVar();

            SetCursorPos({ 2, GetWindowHeight() - 24 });
            BeginChild("footer", { GetWindowWidth() - 4, 22 }); {
                GetWindowDrawList()->AddLine(GetWindowPos(), { GetWindowPos().x + GetWindowWidth(), GetWindowPos().y }, GetColorU32(ImGuiCol_Border));
                GetWindowDrawList()->AddLine({ GetWindowPos().x, GetWindowPos().y + 1 }, { GetWindowPos().x + GetWindowWidth(), GetWindowPos().y + 1 }, GetColorU32(ImGuiCol_BorderShadow));

                char username[256];
                char computerName[256];
                DWORD username_len = sizeof(username);
                DWORD computerName_len = sizeof(computerName);

                GetUserNameA(username, &username_len);
                GetComputerNameA(computerName, &computerName_len);

                ImVec2 base_pos = { GetWindowPos().x + 6, GetWindowPos().y + GetWindowHeight() / 2 - 13.0f / 2 - 1 };

                const char* welcome_text = "Welcome back: ";
                ImVec2 welcome_size = text_size(font, 13, welcome_text);

                add_text(font, 13, base_pos, GetColorU32(ImGuiCol_TextDisabled), welcome_text);
                add_text(font, 13, { base_pos.x + welcome_size.x, base_pos.y }, GetColorU32(rgb_color), username);

                std::string pc_text = "@" + std::string(computerName);
                ImVec2 pc_text_size = text_size(font, 13, pc_text.c_str());
                float right_pos_x = GetWindowPos().x + GetWindowWidth() - pc_text_size.x - 6;

                add_text(font, 13, { right_pos_x, base_pos.y }, GetColorU32(ImGuiCol_Scheme), pc_text.c_str());

            }
            EndChild();
        }
        End();
        ImGui::PopStyleVar();

    }
};

class c_frame {
public:
    c_frame() {
        if (init_fonts) {
            auto& io = GetIO();
            io.Fonts->Clear();

            for (int i = 0; i < fonts.size(); ++i) {
                fonts[i].get_fonts().clear();

                for (int f = 0; f < fonts[i].should_init.size(); ++f) {
                    fonts[i].init({ fonts[i].should_init[f] }, false);
                }
            }

            ImGuiFreeType::BuildFontAtlas(io.Fonts);
            ImGui_ImplDX11_CreateDeviceObjects();

            init_fonts = false;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        NewFrame();
    }

    ~c_frame() {
        Render();
        const float clear_c[4] = { GetStyleColorVec4(ImGuiCol_WindowBg).x, GetStyleColorVec4(ImGuiCol_WindowBg).y, GetStyleColorVec4(ImGuiCol_WindowBg).z, GetStyleColorVec4(ImGuiCol_WindowBg).w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_c);
        ImGui_ImplDX11_RenderDrawData(GetDrawData());

        HRESULT hr = g_pSwapChain->Present(1, 0);
        g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }
};

class c_context {
public:
    c_context(HWND hwnd) {
        CreateContext();
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
    }

    ~c_context() {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        DestroyContext();
    }
};

bool CreateDeviceD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 144;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D() {
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget() {
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget() {
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam);
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
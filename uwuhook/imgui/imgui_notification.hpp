#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include <string>

inline ImColor main_color(255, 0, 0, 250);
inline ImColor background_color(15, 15, 15, 200);
inline ImColor second_color(55, 55, 55, 250);
inline ImColor text_color[2] = { ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 150) };

inline ImVec2 menu_size = ImVec2(400, 300);
inline float anim_speed = 8.f;
inline ImVec2 frame_size = ImVec2(300, 50);

inline ImVec2 center_text(ImVec2 min, ImVec2 max, const char* text)
{
    return min + (max - min) / 2 - ImGui::CalcTextSize(text) / 2;
}

inline ImFont* second_font = nullptr;
inline ImFont* bold_font = nullptr;
inline ImFont* icon_font = nullptr;

inline ImGuiWindow* main_window = nullptr;
inline char search[64] = "";

struct NotificationState
{
    std::string message, information;
    ImColor color;
    ImRect bb;
    ImVec2 offset = ImVec2(400, 0);
    ImVec2 target_offset = ImVec2(400, 0);
    float timer = 0.0f;
    bool active = false;
    float duration = 3.0f; // Show for 3 seconds
};

inline NotificationState notif_state;

class NotificationSystem
{
public:
    void ShowNotification(const std::string& message, const std::string& information, ImColor color, float duration = 3.0f)
    {
        notif_state.offset = ImVec2(400, 0);
        notif_state.target_offset = ImVec2(0, 0);
        notif_state.timer = 0.0f;
        notif_state.color = color;
        notif_state.message = message;
        notif_state.information = information;
        notif_state.active = true;
        notif_state.duration = duration;
    }

    void DrawNotification()
    {
        if (!notif_state.active) return;

        notif_state.timer += ImGui::GetIO().DeltaTime;

        // Show notification for the specified duration, then start hiding
        if (notif_state.timer > notif_state.duration) {
            notif_state.target_offset = ImVec2(400.f, 0.f);

            // Completely remove after hide animation
            if (notif_state.timer > (notif_state.duration + 0.5f)) {
                notif_state.active = false;
                return;
            }
        }
        else {
            notif_state.target_offset = ImVec2(0.f, 0.f);
        }

        // Smooth interpolation
        float t = ImMin(1.0f, ImGui::GetIO().DeltaTime * anim_speed);
        notif_state.offset.x = ImLerp(notif_state.offset.x, notif_state.target_offset.x, t);

        // Get the main viewport
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 screen_size = viewport->Size;
        ImVec2 screen_pos = viewport->Pos;

        // Calculate notification position (top-right corner)
        float notification_width = 340.0f;
        float notification_height = 60.0f;
        float margin = 10.0f;

        ImVec2 notification_pos = ImVec2(
            screen_pos.x + screen_size.x - notification_width - margin + notif_state.offset.x,
            screen_pos.y + margin
        );

        notif_state.bb = ImRect(
            notification_pos,
            notification_pos + ImVec2(notification_width, notification_height)
        );

        ImDrawList* draw_list = ImGui::GetForegroundDrawList();

        // Draw notification background with rounded corners
        draw_list->AddRectFilled(notif_state.bb.Min, notif_state.bb.Max, background_color, 5.0f);

        // Draw border
        draw_list->AddRect(notif_state.bb.Min, notif_state.bb.Max, second_color, 5.0f);

        // Draw colored accent bar on left
        draw_list->AddRectFilled(
            notif_state.bb.Min,
            ImVec2(notif_state.bb.Min.x + 4.0f, notif_state.bb.Max.y),
            notif_state.color
        );

        // Draw message (title)
        ImVec2 text_pos = notif_state.bb.Min + ImVec2(15.0f, 8.0f);
        draw_list->AddText(text_pos, text_color[0], notif_state.message.c_str());

        // Draw information (subtitle)
        ImVec2 info_pos = notif_state.bb.Min + ImVec2(15.0f, 30.0f);
        if (second_font) {
            draw_list->AddText(second_font, second_font->FontSize, info_pos, text_color[1], notif_state.information.c_str());
        }
        else {
            draw_list->AddText(info_pos, text_color[1], notif_state.information.c_str());
        }
    }

    void Update()
    {
        DrawNotification();
    }
};

inline NotificationSystem notificationSystem;
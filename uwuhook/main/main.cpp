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

#include "main.hpp"
#include "../headers/protection.h"
#include "../protection/obfusheader/obfusheader.h"
#include "../libs/xor/xorstr.hpp"
#include "../headers/rename.h"

c_main gui;

static std::wstring moduldernamechange()
{
    wchar_t path[MAX_PATH];
    if (GetModuleFileNameW(nullptr, path, MAX_PATH) == 0) {
        return {};
    }

    std::wstring fullPath(path);
    size_t lastSlash = fullPath.find_last_of(L"\\/");
    std::wstring filename = (lastSlash == std::wstring::npos) ? fullPath : fullPath.substr(lastSlash + 1);

    size_t dot = filename.find_last_of(L'.');
    if (dot != std::wstring::npos)
        filename = filename.substr(0, dot);

    return filename;
}


int main(int, char**) {
    initialize_vm_protection();
    mainprotect(ProtectionStage::STAGE_FULL);

    PlaySoundA(reinterpret_cast<LPCSTR>(wavData), NULL, SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
	Sleep(4300);

    VMProtectBeginUltra("main");
	Sleep(150);
    Beep(500, 500);

    static std::wstring originalName = moduldernamechange();
    static std::wstring exeName = originalName;

    size_t dotPos = exeName.find(L".exe");
    if (dotPos != std::wstring::npos) {
        exeName = exeName.substr(0, dotPos);
    }

    static std::wstring wndClassName = exeName + xorstr_(L"_Class");
    static std::wstring wndTitle = exeName;

    std::string ansiTitle(wndTitle.begin(), wndTitle.end());

    SetWindowPos(FindWindowA(NULL, ansiTitle.c_str()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    SetWindowPos(FindWindowA(NULL, ansiTitle.c_str()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = wndClassName.c_str();
    wc.hIconSm = NULL;

    if (::RegisterClassExW(&wc) == 0) {
        DWORD err = GetLastError();
        VMProtectEnd();
        return 1;
    }

    HWND hwnd = ::CreateWindowW(
        wc.lpszClassName,
        wndTitle.c_str(),  // This will now show without .exe
        WS_POPUP,
        static_cast<int>(GetSystemMetrics(SM_CXSCREEN) / 2 - ui::size.x / 2),
        static_cast<int>(GetSystemMetrics(SM_CYSCREEN) / 2 - ui::size.y / 2),
        static_cast<int>(ui::size.x),
        static_cast<int>(ui::size.y),
        NULL, NULL, wc.hInstance, NULL);

    if (!hwnd) {
        DWORD err = GetLastError();
        ::UnregisterClassW(wndClassName.c_str(), wc.hInstance);
        VMProtectEnd();
        cleanup_vm_protection();
        return 1;
    }

    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;

    CreateDeviceD3D(hwnd);

    {
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

        ::c_context context(hwnd);

        gui.initialize(io);

        ::ShowWindow(hwnd, SW_SHOWDEFAULT);
        ::UpdateWindow(hwnd);

        bool done = false;
        while (!done) {
            MSG msg;
            while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                    done = true;
            }
            if (done)
                break;

            if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED) {
                ::Sleep(10);
                continue;
            }
            g_SwapChainOccluded = false;

            if (g_ResizeWidth != 0 && g_ResizeHeight != 0) {
                CleanupRenderTarget();
                g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
                g_ResizeWidth = g_ResizeHeight = 0;
                CreateRenderTarget();
            }

            {
                ::c_frame frame{};

                RECT rect;
                GetWindowRect(hwnd, &rect);

                if (GImGui->MovingWindow != NULL) {
                    MoveWindow(hwnd,
                        static_cast<int>(rect.left + ImGui::GetMouseDragDelta().x),
                        static_cast<int>(rect.top + ImGui::GetMouseDragDelta().y),
                        static_cast<int>(ui::size.x),
                        static_cast<int>(ui::size.y),
                        TRUE);
                }

                gui.render();
            }
        }

        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wndClassName.c_str(), wc.hInstance);

    VMProtectEnd();
    cleanup_vm_protection();
    mainprotect(ProtectionStage::STAGE_NONE);
    return 0;
}
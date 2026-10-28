# Naruto Senki - V2

- [Naruto Senki - V2](#naruto-senki---v2)
  - [Introduction](#introduction)
    - [Changelog](#changelog)
    - [New features](#new-features)
      - [Game Mode](#game-mode)
    - [What have I done?](#what-have-i-done)
    - [What is the next?](#what-is-the-next)
  - [Know Issues](#know-issues)
  - [TODO](#todo)
  - [How to build?](#how-to-build)
    - [Android](#android)
    - [Linux](#linux)
    - [Windows](#windows)
  - [Structure](#structure)
  - [How to develop?](#how-to-develop)
  - [What is NarutoSenki: Re?](#what-is-narutosenki-re)

---

> For More details visit [game.naruto.re](https://game.naruto.re)
>
> Based on NarutoSenki source code

Get the latest developments👇
- Telegram: [t.me/narutosenki_re](https://t.me/narutosenki_re)
- Discord: [discord.gg/JGA6P8p](https://discord.gg/JGA6P8p)
- Youtube: [Re Offical Channel](https://www.youtube.com/channel/UCL9gDeedGZdf3hjRd-Zr7cg)

## Introduction

> Full desktop preview on [here](https://youtu.be/AaHkA1RmXxkg)

> `NOTE: This project will no longer develop after a few months`

### Changelog

- 2021-9-28
  - [UI] Added game mode selection panel
  - [UI] Added a return button to the select character panel on the desktop
  - [Added] Clone Mode ([Click me](#game-mode))
  - [Added] Random Deathmatch Mode ([Click me](#game-mode))
  - [Added] Click logo will enable custom select for all game modes (Except 1v1 and clone)
  - [Added] If no character is selected in any mode, it will be selected randomly
  - [Fixed] V2 version bugs (Lee, Kakuzu, Kisame)

- 2021-9-29
  - [Fixed] Audio playback error in debug mode on windows

### New features 

#### Game Mode

- Clone

> 

- Random Deathmatch

> 

### What have I done?

- **UPDATED**
  - Updated the project to cocos2d-x 2.2.6 & Visual Studio 2022 preview
  - Most dependent libraries have been upgraded to the latest version
  - Updated glfw2 to glfw3
  - [Android] Support android 12.0 and rounded icons
  - [Android] Support android arm64-v8a
  - [Linux] Use OpenAL instead of FMod
  - [Windows] Use OpenAL instead of native music player
  - [Assets] Use `ogg` format instead of `mp3` (Only support ogg)
  - Upgrade LuaJit to git master（Updated luajit android build script）
  - Added old characters Orochimaru/Pain/Kimimaro
- **FIXED**
  - Correct wrong words && Use english word instead of some chinese variables
  - Combined `NetworkLayer` and `SelectLayer` to `SelectLayer`
  - Separated a few of highly coupled code (All in `Core` folder)
  - Make some not core UI classes implemented by lua
  - [Config] Added some not existed sound files (`HokageMinato_xxx`, etc...)
  - [Gameplay] Fixed character spawn on the wrong direction when the character is right team `Akatsuki`
  - [Gameplay] Fixed character will flip when player only move up or down
  - [Gameplay] Fixed sometimes you can't move when you touched a tower (It still exist)
  - [Android] Fixed battle not fluent
  - [Windows] Fixed high CPU usage (It happened on low cocos2d-x version)
  - [UI] Extended map background
  - [UI] Fullscreen menu background
  - [UI] Make a new battle UI for Desktop platform
- **REMOVED**
  - All network codes & dependence (websocket)
  - [Config] Removed `Hidan` & `Kakuzu` & `Chiyo` hurt sound (It doesn't existed)
- **FEATURES**
  - [Linux & Windows] Half keyboard supported (Only working on battle scene)

### What is the next?

> I dont't want this project to take up more of my time.
>
> So I will back to the main work ---
> continue develop [NarutoSenki: Re](#what-is-narutosenki-re)
>
> I may continue to develop this project if I want.

## Know Issues

- Windows
  - You tell me !
- Linux
  - The `Text Component` manifested are incomplete.
- Android
  - Some sounds will not playing when the battle starts in the first few seconds.
  - Menu's notice clipper not working on android 10.0+. (But it works great on the other platforms)
  - Not be fluent on your android 10.0+ device.

## TODO

- Support shortcut switch from `windowed` to `fullscreen` and more
- Use `OpenAL` play music on `android` platform (May be fixed sounds not wordking)

---

## How to build?

### Android

**Required:** [Android Studio Hedgehog | 2023.1.1](https://developer.android.com/studio/archive) (use this exact release line; the project is configured for Android Gradle Plugin 8.2.0 / Gradle 8.2, which Hedgehog supports out of the box).

- JDK 17 is bundled with Hedgehog (JetBrains Runtime), so no separate JDK install is needed.
- If a newer Android Studio offers to run the *AGP Upgrade Assistant*, decline it. The project is set up for AGP 8.2.0 and the NDK build config has not been migrated to newer plugin versions.

Open `projects/NarutoSenki/proj.android-studio` with Android Studio.

One-time setup, all inside Android Studio (no manual NDK download, no `ndk.dir`, no `NDK_ROOT`):

1. `Settings > Languages & Frameworks > Android SDK > SDK Platforms`: install **Android 14.0 (API 34)**.
2. `Settings > Languages & Frameworks > Android SDK > SDK Tools`: tick **Show Package Details**, then under **NDK (Side by side)** tick **21.4.7075529** (r21e) and click Apply.
   (If you skip this, Gradle will download it automatically on first build once the SDK licenses are accepted.)
3. `File > Sync Project with Gradle Files`

Press `Ctrl + F9` to make project

### Linux

dependence:
  - Arch
    > `pacman -Syu freetype gcc glfw freealut pthread sqlite3 tolua++ gdb`

    or you can also use yay

    > `yay -Syu freetype gcc glfw freealut pthread sqlite3 tolua++ gdb`

``` bash
git clone https://github.com/real-re/NarutoSenki-V2
cd NarutoSenki-V2
./build.sh
```
or
``` bash
cd NarutoSenki-V2
cd tools/tolua++
make
cd ../../
make # DEBUG=1 # -j12
```

### Windows

**Required:** Visual Studio 2022 (v143 toolset). Older versions (2019 and below) will not work.

In the Visual Studio Installer, install the **Desktop development with C++** workload, and make sure these components are ticked:

- **MSVC v143 - VS 2022 C++ x64/x86 build tools** (Latest). Keep VS 2022 updated, because the game code is built with `/std:c++latest`.
- **Windows 10 SDK** or **Windows 11 SDK** (any recent version; the projects target "10.0", i.e. the newest SDK installed)

Notes:
- The solution only has a **Win32 (x86)** platform, so build **Debug|Win32** or **Release|Win32** (not x64).
- No extra libraries need to be installed. FreeType, libpng, OpenAL Soft, GLFW, etc. are already included in the repository.

Build option 1 (recommended):

- Open `cocos2d-win32.sln` with Visual Studio 2022, select `Win32`, and build the `NarutoSenki` project.

Build option 2 (command line):

- Run `build.bat`. This also needs:
  - The `VS143COMNTOOLS` environment variable, which the script reads to find the Visual Studio tools. If it is not defined on your machine, use option 1 instead.
  - `msbuild.exe` at `C:\Program Files\Microsoft Visual Studio\2022\Preview\Msbuild\Current\Bin\`, because `build-win32.bat` hardcodes the **Preview** edition path. If you installed the regular VS 2022 (Community/Professional/Enterprise), edit the `MSBUILD=` line in `build-win32.bat` (and `build-win32-debug.bat`) to your install path first, or use option 1.
  - A Unix `rm` command on your `PATH` (the scripts call `rm -rf`). Installing [Git for Windows](https://git-scm.com/download/win) and adding its `usr\bin` folder to `PATH` provides it.

### macOS

Requires **Xcode** and **Python 3** (to run the Xcode patch utility).

From the repository root:

1. Build **LuaJIT** as a static library (outputs `scripting/lua/luajit/mac/libluajit.a`).
   Clone [LuaJIT](https://github.com/LuaJIT/LuaJIT) into `scripting/lua/luajit/LuaJIT`, then run:

```bash
cd scripting/lua/luajit
./build_mac_luajit.sh
```

2. Patch the Xcode project so it links Naruto Senki gameplay and Lua scripting sources:

```bash
python3 tools/patch_mac_xcode.py
```

3. Open `projects/NarutoSenki/proj.mac/hello.xcodeproj` in Xcode.

If the build fails because **`external/imgui/...` is missing**, the cocos2dx Mac project may still reference Dear ImGui (not shipped in this repo; ImGui is off in `EAGLView.mm`). Run once from the repo root:

```bash
python3 tools/strip_imgui_from_cocos2dx_mac_xcode.py
```

If Xcode reports **missing `external/chipmunk/...` or `CMakeLists.txt` under Chipmunk** (template points to vendored physics that is not in this tree), run once:

```bash
python3 tools/strip_chipmunk_from_hello_mac_xcode.py
```

4. Add **folder references** (blue folders) for `projects/NarutoSenki/Resources` and `projects/NarutoSenki/lua` to the application target so they are copied into `.app/Contents/Resources/` (needed for gameplay assets and Lua at runtime).

5. Optional: rename the Xcode target/product from `hello` to `Naruto Senki`; set **C++ language dialect** to C++17 or C++20 to match other desktop builds; set **macOS Deployment Target** to **11.0** or newer if Xcode warns (the project is updated to **11.0** in tree).

```bash
xcodebuild -project projects/NarutoSenki/proj.mac/hello.xcodeproj -scheme hello -configuration Debug
```

## Structure

```
root: projects/NarutoSenki

├───Classes
│   ├───Core
│   │   ├───Bullet
│   │   ├───Guardian
│   │   ├───Kuchiyose
│   │   ├───Scripts
│   │   ├───Shinobi
│   │   │   └───Bunshin
│   │   ├───Tower
│   │   └───Warrior
│   └───MyUtils
├───lua
│   ├───class
│   ├───core
│   ├───framework
│   │   └───cocos2dx
│   ├───ui
│   └───utils
├───proj.android-studio
├───proj.ios
├───proj.linux
├───proj.mac
├───proj.win32
├───Resources
│   ├───Audio
│   ├───Effects
│   ├───Element
│   ├───Fonts
│   └───Tiles
├───sprites
└───__BIN__
```

- Meaning
  - Classes : C++ source files
    - Core
      - Bullet
      - Guardian
      - Kuchiyose
      - Scripts
      - Shinobi
        - Bunshin
    - MyUtils
  - lua : Lua script files
  - proj.android-studio : Android project
  - proj.ios : IOS project (Not support)
  - proj.linux : Linux project
  - proj.mac : macOS (Xcode) — see **How to build › macOS**
  - proj.win32 : Windows project
  - Resources
  - sprites : Unused assets
  - \_\_BIN__ : Build output (Linux & Windows)

## How to develop?

- Tools
  - [TexturePacker](https://www.codeandweb.com/texturepacker)
  - [TextureUnpacker](https://github.com/real-re/TextureUnpacker)
    - Batch split textures that made by TexturePacker
  - [Tiled](https://www.mapeditor.org/)
    - Can create maps (Get more rules open `xxx.tmx` in `projects/NarutoSenki/Resources/Tiles/` with tiled)

## What is NarutoSenki: RE?

> Made with Unity3D and still in development naruto video game.
>
> For now, looks like it's just NarutoSenki developed with another game engine.

You can get all the notices at the above `telegram` or `discord`.

---

**<font color=#D32F2F>M</font><font color=#FF5722>a</font><font color=#FFEB3B>d</font><font color=#8BC34A>e</font> <font color=#00BCD4>b</font><font color=#448AFF>y</font> <font color=#673AB7>R</font><font color=#FF4081>E</font>**


**<font color=#D32F2F>F</font><font color=#FF5722>i</font><font color=#FFEB3B>x</font><font color=#8BC34A>e</font><font color=#00BCD4>d</font> <font color=#448AFF>b</font><font color=#673AB7>y</font> <font color=#FF4081>S</font><font color=#D32F2F>i</font><font color=#FF5722>l</font><font color=#FFEB3B>x</font><font color=#8BC34A>n</font><font color=#00BCD4>t</font><font color=#448AFF>H</font><font color=#673AB7>i</font><font color=#FF4081>k</font><font color=#D32F2F>a</font><font color=#FF5722>r</font><font color=#FFEB3B>u</font>**

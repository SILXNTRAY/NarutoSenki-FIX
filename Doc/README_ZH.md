# Naruto Senki - V2

- [Naruto Senki - V2](#naruto-senki---v2)
  - [介绍](#介绍)
    - [更新日志](#更新日志)
    - [新功能](#新功能)
      - [游戏模式](#游戏模式)
    - [我都做了什么？](#我都做了什么)
    - [下一步？](#下一步)
  - [已知问题](#已知问题)
  - [TODO](#todo)
  - [如何编译？](#如何编译)
    - [Adnroid](#adnroid)
    - [Linux](#linux)
    - [Windows](#windows)
  - [目录结构](#目录结构)
  - [如何二次开发？](#如何二次开发)
  - [NarutoSenki: Re是什么?](#narutosenki-re是什么)

---

> 更多信息请访问 [game.naruto.re](https://game.naruto.re)
>
> 基于火影战记源码

获取最新动态👇
- QQ群: 806656456
- Telegram: [电报群](https://t.me/narutosenki_re)
- Bilibili: [B站](https://space.bilibili.com/122989580/video)
- Youtube: [油管](https://www.youtube.com/channel/UCL9gDeedGZdf3hjRd-Zr7cg)

## 介绍

> 桌面端完整演示 [B站](https://www.bilibili.com/video/BV1ry4y1S7yk)

> `注意：本项目将在不久后不再维护，另行通知。`

### 更新日志

- 2021-9-28
  - [UI] 新增游戏模式选择界面
  - [UI] 角色选择界面适配桌面端，增添返回按钮
  - [新增] 克隆模式 ([详细点击](#游戏模式))
  - [新增] 随机死亡竞技模式 ([详细点击](#游戏模式))
  - [新增] LOGO彩蛋为所有模式启用自选角色功能 (除了1v1和克隆模式)
  - [新增] 任何模式下不选择角色则进行随机选择
  - [修复] V2旧版本遗留的Bug及各种问题（主要包括小李、角都、鬼鲛）

- 2021-9-29
  - [修复] Windows端Debug模式下播放音频报错

### 新功能

#### 游戏模式

- 克隆模式

> 

- 随机死亡竞技模式

> 

### 我都做了什么？

- **更新**
  - 升级项目到cocos2d-x 2.2.6 & Visual Studio 2022 preview
  - 升级大多数依赖库到最新版
  - 升级glfw2到glfw3
  - [Adnroid] 支持android 12.0和圆形图标
  - [Adnroid] 支持 arm64-v8a
  - [Linux] 使用OpenAL取缔FMod
  - [Windows] 使用OpenAL取缔原生音乐播放器
  - [Assets] 使用`ogg`格式音频取缔`mp3`（仅支持ogg格式音频）
  - LuaJit 更新为git master源（更新安卓luajit编译）
  - 添加了旧角色 大蛇丸/佩恩/君麻吕
- **修复**
  - 修复错误的单词 & 使用英语单词替换一些中文变量
  - 合并 `NetworkLayer`、`SelectLayer` 到 `SelectLayer`
  - 分离部分高耦合代码 (全部在`Core`文件夹)
  - 使非核心的UI转由Lua实现
  - [Config] 添加一些被使用但不存在的音频文件 (`HokageMinato_xxx`, etc...)
  - [Gameplay] 修复角色为右侧出生时错误的出生方向
  - [Gameplay] 修复角色仅上下移动时自动翻转角色
  - [Gameplay] 修复某些情况触碰塔后无法移动 (始终存在)
  - [Android] 修复战斗不流畅
  - [Windows] 修复高CPU用量 (发生在低版本Cocos2d-x)
  - [UI] 地图背景加长
  - [UI] 菜单背景全屏化
  - [UI] 新的UI布局给桌面端
- **移除**
  - 所有网络相关的代码 & 依赖 (websocket)
  - [Config] 注释了 `Hidan` & `Kakuzu` & `Chiyo` 的hurt音效配置
- **特点**
  - [Linux & Windows] 键盘支持 (只有在战斗场景才会完全支持)

### 下一步？

> 我不想让此项目继续占用我的时间了。
>
> 所以我接下来会回到主要工作上 ---
> 继续开发 [NarutoSenki: Re](#narutosenki-re是什么).
>
> 我可能会继续开发如果我想的话。

## 已知问题

- Windows
  - 群里反馈！
- Linux
  - `文本组件`的内容显示不完整。
- Android
  - 战斗开始几秒内部分音效无法播放。
  - Android 10.0及以上的图片遮罩无法正常工作。(其他平台正常工作)
  - Android 10.0及以上游戏卡顿。

## TODO

- 支持快捷键切换`窗口化`到`全屏`和更多
- 使用`OpenAL`播放音频在安卓端 (可能会修复音频无法播放错误)

---

## 如何编译？

### Adnroid

Android Studio打开`project/NarutoSenki/proj.android-studio`

按`Ctrl + F9`编译项目

### Linux

依赖:
  - Arch
    > `pacman -Syu freetype2 gcc glfw freealut sqlite3 tolua++ gdb`

    你也可以使用yay

    > `yay -Syu freetype2 gcc glfw freealut sqlite3 tolua++ gdb`

``` bash
git clone https://github.com/real-re/NarutoSenki-V2
cd NarutoSenki-V2
./build.sh
```
或
``` bash
cd NarutoSenki-V2
cd tools/tolua++
make
cd ../../
make # DEBUG=1 # -j12
```

### Windows

- Visual Studio 2022 打开`cocos2d-win32.sln`

或

- 执行`build.bat`



## 目录结构

```
根目录: projects/NarutoSenki

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

- 含义
  - Classes : C++源文件
    - Core
      - Bullet
      - Guardian
      - Kuchiyose
      - Scripts
      - Shinobi
        - Bunshin
    - MyUtils
  - lua : Lua脚本文件目录
  - proj.android-studio : 安卓项目
  - proj.ios : IOS项目 (未支持)
  - proj.linux : Linux项目
  - proj.mac : MAC项目 (未支持)
  - proj.win32 : Windows项目
  - Resources
  - sprites : 未使用资源
  - \_\_BIN__ : 构建可执行文件输出目录 (Linux & Windows)

## 如何二次开发？

- 工具
  - [TexturePacker](https://www.codeandweb.com/texturepacker)
    - 打包图片资源（资源优化选项为3即可）
  - [TextureUnpacker](https://github.com/real-re/TextureUnpacker)
    - 基于开源项目二次开发，支持批量分割由TexturePacker合成的图集
  - [Tiled](https://www.mapeditor.org/)
    - 用于开发地图（规则参照原版地图文件即可，用tiled打开`xxx.tmx`在`projects/NarutoSenki/Resources/Tiles/`）

## NarutoSenki: Re是什么?

> 由Unity3D引擎开发（仍在开发中）
>
> 现在看起来就像原版火战，但是还需要大量时间去完善细节，那才是游戏的核心所在。

你可以加入[QQ群](#naruto-senki---v2)，有任何消息或进展我会很快发布公告。

---

**<font color=#D32F2F>M</font><font color=#FF5722>a</font><font color=#FFEB3B>d</font><font color=#8BC34A>e</font> <font color=#00BCD4>b</font><font color=#448AFF>y</font> <font color=#673AB7>R</font><font color=#FF4081>e</font>**

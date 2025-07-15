ShadowPlayer-BLumia
===================

## 使用前必读

> [!WARNING]  
> **这是一个历史项目**，仅因仍在被使用的缘故而在偶然的进行维护。

## 构建方式

### 获取前置依赖

在此段落更新前，请参见 [旧仓库 README](https://github.com/BLumia/ShadowPlayer-BLumia-HistoryRepo) 中提供的描述。

此项目依赖 [bass](https://www.un4seen.com/bass.html) 库，且目前仅支持 Windows/MSVC 构建。出于方便起见，此仓库放置了其相关二进制，故对于 `x86_64` 架构，不需要额外获取 BASS 库依赖。若非特别情况所需，此仓库也不计划对这些二进制文件进行版本更新，以避免仓库体积因此膨胀。

### 载入工程与构建

如果你需要 IDE，那用 IDE 打开 `ShadowPlayer` 目录下的 `CMakeLists.txt`。你需要自己确保 IDE 找得到 Qt。

## 其它

- 此项目的替代项目是 [BLumia/pineapple-music](https://github.com/BLumia/pineapple-music)。
- 此项目是 [ShadowPower/ShadowPlayer](https://github.com/ShadowPower/ShadowPlayer) 的派生版本。
- 此项目的提交历史参见 [BLumia/ShadowPlayer-BLumia-HistoryRepo](https://github.com/BLumia/ShadowPlayer-BLumia-HistoryRepo)。由于旧仓库存在对 Git 的误用，旧仓库体积较大，故另建仓库存储代码。此仓库初始状态和原始仓库的归档时最终状态几乎一致。

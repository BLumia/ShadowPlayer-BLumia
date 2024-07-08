ShadowPlayer-BLumia
===================

## 使用前必读

这是一个历史项目，出于仍在被使用的缘故而在偶然的进行维护。此项目依赖 [bass](https://www.un4seen.com/bass.html) 库，且目前仅支持 Qt 5 + Windows/MSVC 构建。出于方便起见，此仓库也放置了一些二进制文件。

此项目不包含任何曲库管理功能，且以后也不会包含此功能。

项目的提交历史中有非常不规范的 Git 用法（例如在仓库里丢构建好的二进制等），不建议查看提交历史。

## 构建方式

### 获取前置依赖

- Qt 5.15.2，模块：core, gui, widgets, winextras。
  - 如果懒得下载 Qt 官方的下载器/维护工具，可通过 [aqtinstall](https://github.com/miurahr/aqtinstall) 获取： `aqt install-qt windows desktop 5.15.2 win64_msvc2019_64` （在哪执行就会下载到哪儿）
- MSVC 2022（2019 应该也行，没试，也不打算试）
- CMake 越新越好（作为参考，截至目前我使用的是 3.29.2）
- bass 库
  - 为方便起见，仓库内已提供 x64 架构使用的 lib 与 dll 文件，不需要额外下载
  - 若需构建 x86 版，自己下载去

### 载入工程与构建

如果你需要 IDE，那用 IDE 打开 `ShadowPlayer` 目录下的 `CMakeLists.txt`。恕不支持用于 qmake 的 `.pro` 文件。你需要自己确保 IDE 找得到 Qt 5.15。

对于手动命令构建，请参阅 `ShadowPlayer/compile.bat` 批处理脚本，里面包括了设置相关环境变量、构建（Release 版）以及部署的步骤。除非你计算机用户名和我一样，否则你需要修改此批处理中 `QTDIR` 指向的 Qt 所在位置。方便起见，可直接执行 `.\compile.bat help`

## 其它

此项目是基于 [ShadowPower/ShadowPlayer](https://github.com/ShadowPower/ShadowPlayer) 的派生版本，原 repo 中包含一些截图。

<details><summary>下面是此派生版本的原 README 内容。</summary>

这个播放器是基于[ShadowPower](https://github.com/ShadowPower)的[ShadowPlayer](https://github.com/ShadowPower/ShadowPlayer)的修改版，在原版的基础上增加了ab循环设定和自动载入循环，mini窗口播放，可选的列表加载模式和列表调整等功能。

### 与原版的区别

 1. 增加了ab循环设定和自动载入循环（即保存设定好的ab循环位置）
 2. 增加了仿[Osu!](http://osu.ppy.sh/)的游戏标题界面右上角的Mini窗口模式
 3. 增加了杀马特列表模式（默认杀马特模式，可切换为经典）。
 4. 增加了文件夹扫描导入和列表导出功能，可以将列表内的所有歌曲本体复制到指定的位置。
 5. 歌曲歌词Offset调整
 6. 对于杀马特模式增加了列表的文件名自动排序。
 
### 这些修改有什么用

 1. AB循环的自动载入功能适用于游戏或其他可Loop乐曲的循环洗脑
 2. 杀马特模式，即播放歌曲时自动导入歌曲同文件夹的所有（符合最短时常设定的）歌曲到播放列表的模式，和WMP是一样的...经典模式则和千千静听等一样使用播放一个就添加一个到列表的方式。个人表示前者更符合使用习惯。
 3. 列表导出功能适用于从文件夹扫描导入的歌曲列表的歌曲迁移导出，比如在设定最短歌曲长度限制后扫描了位于/osu!/songs下的所有歌曲文件，那么可以通过列表导出功能把列表内的所有歌曲存到MP3播放器中。
 4. 歌词Offset功能，当歌词和实际歌曲有一定的时间差时可以在歌词秀窗口调整offset
 5. 文件名排序针对播放专辑时，文件名包含数字序号时的合理处理。避免纯字典序导致（1,2,10,11）被排序为（1,10,11,2）的情况
 
### 已知问题和修复计划

其实大多的已知问题都因为我基本遇不到所以没打算修（我太baka了..）。如果您知道怎么处理或者您乐意修复，欢迎帮忙。

 1. **部分文件名会导致乱码**<br>少见的编码没处理，绝大多是没问题的，我自己甚至没遇到过这种情况。
 2. **歌词文件乱码**<br>将歌词转为ansi编码即可解决。支持utf8在处理上有点问题，还没仔细研究过。
 3. **从文件夹包含子文件夹导入列表时会出现卡顿，导出列表也会**<br>应该使用多线程进行此类操作，然而我手头的qt多线程一用就炸了。硬伤，非代码问题。
 4. **点击红心列表没反应**<br>原因是压根没写这部分代码。。关闭播放器会自动保存当前列表为playlist.sdql，复制一份命名OsuList.sdpl后打开播放器点红心列表就管用了，不过并没有什么卵用。实际上播放列表打算整个重写，不过鉴于目前不是很需要这个功能所以懒得写了。。。。
 5. **APE格式的音频没专辑封面**<br>我读书少，求APE带封面的歌曲的文件。虽然ape格式说明有写，但真心没见过，没办法写。。
 
### 其他相关

这个播放器实际上是为了自己使用方便才改的，自己能根据自己的需求增加或者删除功能，所以会往自己用着爽的方向改。也当学习编程了。由于推到github上的时候还不怎么会用git，所以我其实本应fork原版而实际是全新推了一份上来。也所以一堆配置文件也被推了上来，对于这些文件。。无视即可。

因为是针对我个人日常的使用而做的修改，所以并不一定适合我之外的用户使用，而且很多坑还没填（比如cue格式的播放列表处理，重写播放列表部分的代码，解决各种上述bug等）。不过我发誓这软件日用是没问题的，我一直日用来着。

如果你在使用这软件（真的会有除了我之外的人用吗？）并且出现了上面没提到的bug，欢迎反馈给我，如果有新功能建议也可以提出。不过，如果我认为您提出的新功能似乎并没有太大的实际用途，我就不会去改了。毕竟只是我个人用的软件而已，不过如果你也拿去日用了，我会考虑添加新功能的XD。兴许某一天，如果有必要，我可能会自己造轮子写个播放器，虽然可能性极其小。

原作者说版权没有但是却说明了不能用于充当作业上交。既然我把我的修改版推到github上来了那还是也声明一下为好。此程序所有代码不能够用于拿去交作业。

### English Intro

**What's Shadow Player?**<br>
Shadow Player is a music player created by ShadowPower(61) with Qt5 and bass library.

**What's Shadow Player - BLumia**<br>
Shadow Player - BLumia is a fork of Shadow Player, which included some useful functions.

**How to get the original version of Shadow Player**<br>
Just [Click here](https://github.com/ShadowPower/ShadowPlayer)

**How to get Shadow Player - BLumia**<br>
So... Where you are now? LOL

**Is this a Full-Chinese-Language Software**<br>
Emm... Yes. Since this player is modified for myself..

</details>

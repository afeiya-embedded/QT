# Qt C++ 示例与工具集

本仓库收集了一组基于 **Qt Widgets** 的 C++ 示例程序与桌面工具，覆盖界面开发、文件处理、绘图、网络通信、数据库访问、语音播报以及物联网通信等常见场景。每个示例都是独立的 **qmake 工程**，可在 Qt Creator 中单独打开对应的 `.pro` 文件。

仓库同时保留了 MinGW / MSVC 的编译发布副本与 NSIS 安装包工程，便于直接运行或参考 Windows 发布流程。**修改功能时请优先编辑不带后缀的源码目录。**

- 远程仓库：`git@github.com:afeiya-embedded/QT.git`
- 配套笔记：[`qt.md`](qt.md) —— Qt 学习笔记，可与示例源码配合阅读

---

## 项目一览

| 目录 | 内容 | 主要 Qt 模块 | 核心知识点 |
| --- | --- | --- | --- |
| `01-helloworld` | 基础窗口与 Qt Designer 入门 | `Widgets` | `QApplication`、`Ui::Widget` 与继承关系 |
| `02-PictureToIcon` | 选择图片并转换为 `.ico` 图标 | `Widgets` | `QFileDialog`、`QFileInfo`、`QPixmap`、`explicit` |
| `03-TextToSpeech` | 文本转语音、语音引擎/语言/声音选择 | `Widgets`, `TextToSpeech` | `QTextToSpeech`、`QComboBox`、`QLocale`、`QVoice`、`QVariant` |
| `04-Timer` | 定时器、计时显示、数据表格与中英切换 | `Widgets` | `QTimer`、`QLCDNumber`、`QStandardItemModel`、`QTableView`、`QTranslator` |
| `05-notepad` | 简易文本编辑器，支持打开/保存/打印/字体 | `Widgets`, `PrintSupport`, `Gui` | `QFile`、`QMessageBox`、`closeEvent`、`QPrinter`、`QFontDialog` |
| `06-Painter` | `QPainter` 绘图与图像文件操作 | `Widgets`, `Gui` | `paintEvent`、鼠标事件、拖拽、`QSettings`、子窗体与自定义信号 |
| `07-NetAssist` | 网络调试助手：TCP 客户端/服务端与 UDP | `Widgets`, `Network` | `QTcpSocket/Server`、`QUdpSocket`、`QHostInfo`、无边框窗体、QSS 换肤 |
| `08-Sqlite` | SQLite 数据库连接、建表、增删改查 | `Widgets`, `Sql` | `QSqlDatabase`、`QSqlQuery`、`QSQLITE` 驱动 |
| `09-Mysql` | MySQL 数据库连接与 SQL 操作 | `Widgets`, `Sql` | `QSqlDatabase`、`QMYSQL` 驱动编译 |
| `IOTClient` | 串口 / Modbus、MQTT、CANopen 上位机 | `Widgets`, `SerialPort`, `Network`, `Mqtt`, `Concurrent` | `QSerialPort`、`QMqttClient`、`QtConcurrent`、CandleApiDriver |
| `simpleclient` | Qt MQTT 客户端官方示例（BSD） | `Core`, `Gui`, `Network`, `Mqtt` | `QMqttClient` 最小可用客户端 |

> 带 `_MinGW`、`_MSVC` 后缀的目录是对应编译器的运行产物；`02-PictureToIcon_install` 包含 NSIS 安装包工程与成品安装程序。所有这些目录均已被 `.gitignore` 排除，属于本地生成内容。

---

## 目录结构

```
QT/
├─ 01-helloworld/            # 基础窗口示例
├─ 02-PictureToIcon/         # 图片转图标工具
│  └─ images/                # logo.ico 等资源
├─ 02-PictureToIcon_install/ # NSIS 安装包工程 + 成品 exe
├─ 03-TextToSpeech/          # 文本转语音
├─ 04-Timer/                 # 秒表计时器（含翻译文件）
│  ├─ translations/          # en_US.ts 语言包
│  └─ en_US.ts
├─ 05-notepad/               # 记事本（含 en_US.qm 编译后的语言包）
├─ 06-Painter/               # 画图工具（polygon 子窗体）
├─ 07-NetAssist/             # 网络调试助手
│  └─ qss/                   # silvery / psblack 皮肤样式表
├─ 08-Sqlite/                # SQLite 示例
│  └─ qss/
├─ 09-Mysql/                 # MySQL 示例
│  └─ qss/
├─ IOTClient/                # 物联网上位机
│  ├─ modbus.*               # 串口 Modbus（主界面）
│  ├─ mqtt.*                 # MQTT 客户端
│  ├─ canopen.*              # CANopen（CAN 驱动）
│  └─ CandleApiDriver/       # candle 驱动 API 与 .pri
├─ simpleclient/             # Qt MQTT 官方示例
├─ *_MinGW / *_MSVC          # 编译发布副本（不入库）
├─ image.png                 # 前台 UI / 后台控制程序 关系图
├─ image-1.png ~ image-3.png # NSIS 打包步骤截图
├─ qt.md                     # Qt 学习笔记
├─ .gitignore                # 构建产物忽略规则
└─ README.md
```

---

## 环境要求

- **Qt 5.15.2**（本仓库构建目录基于该版本；其他 5.15.x 兼容版本通常也可用）
- **C++17**：所有 `.pro` 均声明 `CONFIG += c++17`
- **Qt Creator**，或命令行 `qmake` + 对应 C++ 编译器
- Windows 工具链二选一：
  - **MinGW 64-bit**（`Desktop_Qt_5_15_2_MinGW_64_bit_*`）
  - **MSVC 2019 / 2022 64-bit**（`Desktop_Qt_5_15_2_MSVC2019_64bit_*`）

各示例的模块依赖（见对应 `.pro`）：

| 示例 | 额外模块 / 依赖 |
| --- | --- |
| `03-TextToSpeech` | Qt TextToSpeech 模块 + 系统可用的语音引擎 |
| `05-notepad` | Qt PrintSupport（打印功能） |
| `07-NetAssist` | Qt Network |
| `08-Sqlite` | Qt Sql（`QSQLITE` 驱动，随 Qt 自带） |
| `09-Mysql` | Qt Sql（需自行编译 `QMYSQL` 驱动）+ 可访问的 MySQL 服务 |
| `IOTClient` | Qt SerialPort、Qt MQTT、Qt Concurrent；CANopen 功能需 `CandleApiDriver`（已随仓库提供，经 `CandleApiDriver.pri` 引入） |
| `simpleclient` | Qt MQTT |

---

## 快速开始

### 使用 Qt Creator

1. 打开 Qt Creator，选择 **文件 → 打开文件或项目**。
2. 选择目标项目文件，例如 `07-NetAssist/07-NetAssist.pro`。
3. 选择已安装的 Qt Kit（MinGW 64-bit 或 MSVC2019 64-bit）。
4. 配置构建目录（建议使用仓库外的 `build-*` 目录），点击 **构建**，再点击 **运行**。

### 使用命令行 qmake

以 `07-NetAssist` 为例，在项目目录中执行：

```bash
cd 07-NetAssist
qmake 07-NetAssist.pro
qmake --build .            # 或 make / mingw32-make / nmake
```

Debug 构建产物位于 `debug/`，Release 构建先执行 `qmake CONFIG+=release`，再运行生成的 `release/` 目录中的程序。不同 Qt Kit 的输出目录和可执行文件名可能略有差异，请以构建日志为准。

---

## 示例详解

### 01-helloworld —— 基础窗口

最小的 Qt Widgets 工程，用于理解 Qt 的「前台 UI」与「后台控制程序」的对应关系（见 [`image.png`](image.png)）。

```cpp
QApplication a(argc, argv);
Widget w;
w.show();
return QApplication::exec();
```

要点：

- `widget.ui` 经 `uic` 编译生成 `ui_widget.h`，其中 `Ui::Widget::setupUi()` 负责构建前台窗口内容。
- `Widget` 继承 `QWidget`，并持有成员指针 `Ui::Widget *ui`；在构造函数中完成 `ui = new Ui::Widget` 与 `ui->setupUi(this)`。
- 后台控制逻辑（键盘、鼠标事件处理）写在 `widget.cpp` 中。

### 02-PictureToIcon —— 图片转图标

选择本地图片并转换为 `.ico` 图标文件，是 `QFileDialog` / `QFileInfo` / `QPixmap` 的综合练习。

- `QFileDialog::getOpenFileName()` 选择源图片，`getSaveFileName()` 指定输出路径。
- `QFileInfo` 获取文件名、路径、大小、创建/修改时间等元信息。
- `QPixmap` 负责加载、缩放（`scaled()`）与保存（`save()`）。
- 工程通过 `RC_ICONS = images/logo.ico` 设置可执行程序图标。
- `main.cpp` 中演示 `QApplication::setAttribute(Qt::AA_EnableHighDpiScaling)` 启用高 DPI 缩放。
- 笔记中还包含 `explicit` 关键字对构造函数隐式转换的限制说明。

### 03-TextToSpeech —— 文本转语音

使用 `QTextToSpeech` 实现文字朗读，并动态枚举可用的引擎、语言与声音。

- `QTextToSpeech::availableEngines()` 枚举有效引擎，通过 `QComboBox::addItem()` 填充下拉列表。
- `availableLocales()` 返回 `QVector<QLocale>`，配合 `QLocale::countryToString / languageToString / scriptToString` 展示可读信息。
- `availableVoices()` 返回 `QVector<QVoice>`，用 `QVoice::genderName()` 展示性别。
- 下拉项使用 `QVariant(locale)` 携带附加数据，实现「显示文本」与「实际对象」的绑定。
- `QSlider` 控制语速：`setRate()` 接受 -1.0 ~ 1.0 的浮点值。
- `main.cpp` 通过 `QStyleFactory::create("fusion")` 设置应用外观。

### 04-Timer —— 秒表计时器

综合演示定时器、数码管显示、表格模型与多语言切换。

- `QTimer` + `connect(timer, &QTimer::timeout, this, &MainWindow::timeout_slot)` 实现 10ms 周期刷新。
- `QLCDNumber` 通过 `setDigitCount()`、`setSegmentStyle(QLCDNumber::Flat)` 显示 `mm:ss.cc`。
- `QStandardItemModel` 作为数据模型，`QTableView` 作为显示视图：`setColumnCount()`、`setHeaderData()`、`setItem()`、`removeRows()`。
- `QPushButton::setCheckable(true)` 实现开始/停止自锁按钮，`isChecked()` 读取状态。
- `QTranslator` 加载 `en_US.qm` 实现中英切换，切换后调用 `ui->retranslateUi(this)` 重新初始化界面。
- `.pro` 中通过 `TRANSLATIONS += translations/en_US.ts en_US.ts` 声明语言包，`msvc { QMAKE_CXXFLAGS += /utf-8 }` 解决 MSVC 中文编码问题。

### 05-notepad —— 记事本

简易文本编辑器，涵盖文件读写、编码转换、弹窗与打印。

- `QFile` 完成 `open / close / readAll / write`；写入前用 `toUtf8()` 编码，读取后用 `QString(data)` 解码。
- `QFileInfo::fileName()` 用于更新窗口标题。
- `QMessageBox` 处理「保存 / 不保存 / 取消」三态选择，支持对象式与静态式两种用法（`about()`、`aboutQt()`）。
- 重写 `closeEvent(QCloseEvent *)`，用 `event->accept()` / `event->ignore()` 决定是否真正关闭窗口。
- `QPrinter` + `QPrintDialog` 打印 `QTextEdit` 内容。
- `QFontDialog::getFont()` 选择字体，`QAction::setCheckable(true)` 实现粗体开关。
- 工程额外依赖 `QT += printsupport`。

### 06-Painter —— 画图工具

基于 `paintEvent` 的绘图程序，支持画线、画多边形以及鼠标拖拽编辑。

- 重写 `paintEvent(QPaintEvent *)`，在窗口显示、尺寸变化或被遮挡时自动重绘，调用 `update()` 也可主动触发。
- `QPainter` 配合 `QPen`（颜色、线宽）绘制直线（`drawLine`）、圆形端点（`drawEllipse`）、多边形（`drawPolygon`）。
- `setRenderHint(QPainter::Antialiasing)` 开启抗锯齿。
- 重写 `mousePressEvent / mouseReleaseEvent / mouseMoveEvent`；用「绝对值误差 < 10 像素」判定是否选中端点，并用 `setCursor()` 反馈命中状态。
- 拖拽时通过 `QLine::setP1/setP2` 或 `QPolygon::replace()` 更新坐标，再 `update()` 重绘。
- 子窗体 `polygon` 独立创建（不使用 `this` 作父对象以避免内嵌），通过自定义信号 `emit add_newpolygon()` 与主窗口通信。
- 子窗体内部控件通过公开接口 `getPolygonPoints()` 访问，避免直接暴露 `ui` 指针。
- `QSettings` 读写 `config.ini`，用 `beginGroup / contains / value / setValue / endGroup` 持久化线段配置。
- 需在 `MainWindow` 与 `centralwidget` 两处 `setMouseTracking(true)` 才能实现实时鼠标跟踪。

### 07-NetAssist —— 网络调试助手

TCP 客户端/服务端与 UDP 通信调试工具，界面基于无边框窗体 + QSS 换肤。

- `QT += network`；使用 `QTcpSocket` / `QTcpServer` 与 `QUdpSocket` 完成收发。
- `QHostInfo::localHostName()` 获取计算机名，`fromName()` + `addresses()` 枚举本机 IP，仅保留 `IPv4Protocol`。
- `QUdpSocket::bind()` 绑定地址与端口，`readyRead()` 信号触发 `readDatagram()` 读取数据报。
- ASCII 与 HEX 互转工具函数：`convertAsciiToHex()`、`convertHexToAscii()`、`convertStringToHex()`。
- `QUIWidget` 继承 `QDialog`，通过 `Qt::FramelessWindowHint` 实现无边框窗体，`setMainWidget()` 将主窗体嵌入并自动调整尺寸，`installEventFilter()` 监听鼠标实现拖动与缩放。
- 通过 `QFile` 读取 `:/qss/silvery.css`（或 `psblack.css`）并用 `qApp->setStyleSheet()` 加载皮肤，`qss.mid(20, 7)` 提取调色板颜色。
- `main.cpp` 中默认加载 `silvery` 皮肤并启用高 DPI 缩放。

### 08-Sqlite —— SQLite 数据库

SQLite 的连接、建表与增删改查示例。

```cpp
QStringList lists = QSqlDatabase::drivers();     // 查看支持的驱动
db = QSqlDatabase::addDatabase("QSQLITE");       // 选择驱动
db.setDatabaseName("my.db");                     // 文件不存在则创建
bool ok = db.open();
```

- 使用 `QSqlQuery::exec(sql)` 执行 SQL，失败时通过 `query.lastError().text()` 获取错误信息。
- 建表语句示例：`create table student(number int primary key, name char, gender char, age int, score float);`
- 数据库文件默认在程序当前工作目录创建；界面同样加载 `:/qss/silvery.css` 皮肤。

### 09-Mysql —— MySQL 数据库

与 SQLite 示例结构一致，差异在于驱动与连接参数：

- 使用 `QSqlDatabase::addDatabase("QMYSQL")`，需额外设置 `setHostName()` / `setPort()` / `setDatabaseName()` / `setUserName()` / `setPassword()`。
- Qt 官方不预置 MySQL 驱动，需要修改 Qt 源码后自行编译 `QMYSQL` 插件（笔记中记录了该流程）。
- 运行前需保证目标机器已安装对应驱动且 MySQL 服务可访问。

### IOTClient —— 物联网上位机

一个上位机工程内聚合三种工业通信方式，通过 `main.cpp` 引入 `modbus.h` 并以 `Widget w` 作为主界面，MQTT、CANopen 作为独立子窗体。

| 模块 | 关键类 | 说明 |
| --- | --- | --- |
| Modbus | `QSerialPort`, `QSerialPortInfo`, `QTimer`, `QMutex` | 串口打开/刷新、读取从机数据、LED/蜂鸣器/继电器控制，定时 2s 轮询 |
| MQTT | `QMqttClient`, `QJsonDocument`, `QSettings` | 连接 Broker、订阅/发布主题、上传/下载配置，服务器地址可配置 |
| CANopen | `QtConcurrent`, `QTimer`, `candle_handle` | 基于 `CandleApiDriver` 枚举 CAN 设备，异步读取报文，自定义信号 `receiveeCanData` 转发数据 |

- 工程通过 `INCLUDEPATH += $$PWD/CandleApiDriver` 与 `include($$PWD/CandleApiDriver/CandleApiDriver.pri)` 引入 CAN 驱动。
- 界面默认加载 `:/qss/psblack.css` 深色皮肤，并启用高 DPI 缩放。

### simpleclient —— Qt MQTT 官方示例

来自 Qt 官方示例（Qt Company，BSD 许可），`TARGET = simplemqttclient`，演示 `QMqttClient` 的最小可用客户端：连接 Broker、订阅主题、接收与发布消息。

---

## Windows 发布与打包

### 1. 收集运行库（windeployqt）

在与目标 Kit 匹配的终端（MinGW 或 MSVC）中执行：

```bash
windeployqt release\YourApp.exe
```

`windeployqt` 会自动拷贝所需的 `Qt5Core.dll`、`Qt5Gui.dll`、`platforms/qwindows.dll`、`imageformats/` 等目录。**请确保 `windeployqt` 与编译程序使用同一套 Qt 安装。** 使用 MSVC 构建时，目标机器还可能需要对应的 Visual C++ Redistributable（`vc_redist.x64.exe`）。

仓库中的 `*_MinGW`、`*_MSVC` 目录可作为发布目录结构的参考。

### 2. 制作安装包（NSIS）

`02-PictureToIcon_install/` 提供了完整的 NSIS 打包示例：

- `PictureToIcon.nsi`：脚本使用 HM VNISEdit 向导生成，产品名 `PictureToIcon`、版本 `1.1`、发布者 `afeiya`，安装界面语言为简体中文，压缩算法 LZMA。
- 打包内容直接引用 `..\02-PictureToIcon_MSVC\` 下经 `windeployqt` 部署后的文件（exe、Qt DLL、plugins、translations、`license.txt`、`vc_redist.x64.exe`）。
- 安装过程会创建开始菜单与桌面快捷方式，并写入卸载注册表项。
- 许可协议页面读取 `..\02-PictureToIcon_MSVC\license.txt`。
- 成品：`PictureToIcon_Setup_1.1.exe`。

**打包流程**：先完成程序构建 → `windeployqt` 部署到 `02-PictureToIcon_MSVC` → 准备 `license.txt` → 用 NSIS 编译 `.nsi` 生成安装程序。

### 3. 静态编译（MinGW）

默认情况下 Qt Creator 使用动态编译，程序运行时需要附带大量 DLL。若希望把依赖库一起打包进单个可执行文件，可对 Qt 进行静态编译：

- Qt 官方不提供静态编译好的安装包，需要在本地自行编译。
- 静态编译生成的 exe 体积通常比动态编译方案小很多，且无需分发 Qt DLL。

---

## 常用工程配置速查

| 需求 | 做法 |
| --- | --- |
| 设置可执行程序图标 | `.pro` 中添加 `RC_ICONS = images/logo.ico` |
| 启用高 DPI 缩放 | 在创建 `QApplication` **之前**调用 `QApplication::setAttribute(Qt::AA_EnableHighDpiScaling)` |
| 设置应用风格 | `a.setStyle(QStyleFactory::create("fusion"))` |
| 加载 QSS 皮肤 | `QFile` 读取 `:/qss/*.css` → `qApp->setStyleSheet(qss)` |
| 解决 MSVC 中文乱码 | `.pro` 中添加 `msvc { QMAKE_CXXFLAGS += /utf-8; QMAKE_CFLAGS += /utf-8 }` |
| 添加语言包 | `.pro` 中 `TRANSLATIONS += xxx.ts`，用 `lupdate`/`lrelease` 生成 `.qm` |
| 引入资源文件 | `.pro` 中 `RESOURCES += images.qrc` |

---

## Qt 学习笔记索引

根目录的 [`qt.md`](qt.md) 是一份完整的 Qt 学习笔记，与各示例源码一一对应，主要章节如下：

- **Qt 概述**：跨平台性、功能库、Qt Designer、信号与槽机制
- **运行关系**：`widget.ui → ui_widget.h → setupUi()`，前台 UI 与后台控制程序的对应（见 [`image.png`](image.png)）
- **打包与发布**：`windeployqt`、NSIS 制作安装包（见 `image-1.png` ~ `image-3.png`）
- **常用配置**：可执行程序图标、高 DPI 缩放、风格样式、QSS 皮肤、MSVC 编码转换
- **PictureToIcon**：`explicit`、`QFileDialog`、`QFileInfo`、`QLabel`、`QRadioButton`、`QPixmap`
- **TextToSpeech**：`QTextToSpeech`、`QStringList`、`QComboBox`、`QLocale`、`tr/arg`、`QVariant`、`QVoice`、`QSlider`、`QTextEdit`
- **Timer**：`QString::asprintf`、`QTimer`、`QPushButton`、`QLCDNumber`、`QStandardItemModel`、`QTableView`、`QTranslator`、ts/qm 文件
- **Notepad**：`QFile`、`QFileInfo`、`QByteArray`、编码转换、`QMessageBox`、`closeEvent`、`QPrinter`、`QPrintDialog`、`QFont`、`QFontDialog`、`QAction`
- **Painter**：`paintEvent`、鼠标事件、`QPainter`、`QPen`、拖拽、子窗体、`emit` 自定义信号、`QSettings`
- **NetAssist**：`QUIWidget` 无边框窗体、`QHostInfo`、`QUdpSocket`、ASCII/HEX 互转、QSS 皮肤
- **数据库**：`QSqlDatabase`、`QSqlQuery`、SQLite 与 MySQL
- **静态编译**：MinGW 静态编译流程

---

## 关于 `.gitignore`

仓库根目录的 `.gitignore` 用于排除 Qt 构建产物与本地配置，避免生成文件进入版本库。当前生效的规则包括：

- **构建目录**：`build/`、`build-*/`、`debug/`、`release/`
- **qmake 生成**：`.qmake.stash`、`Makefile*`（保留 `Makefile.pri`）
- **编译产物**：`*.exe`、`*.dll`、`*.lib`、`*.a`、`*.o`、`*.obj`、`*.pch`、`*.pdb`、`*.ilk`、`*.idb`
- **Qt 自动生成**：`moc_*.cpp/h`、`ui_*.h`、`qrc_*.cpp`、`*.autosave`
- **本地用户配置**：`*.pro.user*`、`.vs/`、`*.suo`、`*.user`

文件前半部分以 `#` 注释保留了多组历史规则，可作为扩展参考。

---

## 目录约定

- **源码、界面与资源文件**：各示例不带后缀的目录
- **编译/发布副本**：`*_MinGW`、`*_MSVC`、`*_install`
- **图片资源**：各项目的 `images/` 目录与 `images.qrc` 资源文件
- **皮肤样式表**：`07-NetAssist/qss`、`08-Sqlite/qss`、`09-Mysql/qss`
- **构建产物**：建议放在项目外部的 `build-*` 目录，避免提交到版本库

---

## 许可

仓库当前未提供单独的许可证文件。使用或再分发其中代码前，请先确认项目维护者的授权范围。

其中 `simpleclient` 源自 Qt 官方示例，遵循其 BSD 许可条款（详见源码头部版权声明）；Qt 本身遵循其对应版本的许可条款。

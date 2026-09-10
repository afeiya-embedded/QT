## QT

### QT 是一个跨平台的 C++ 应用程序开发框架 
### 主要特点
- 1. 跨平台性: QT 可以在多种操作系统上运行，包括 Windows、 macOS、 Linux、 Android 和 iOS 等。这使得开发者可以编写一次代码，然后在不同的平台上进行编译和部署，大大提高了开发效率。无论在哪个平台上， QT 都能提供一致的用户界面和功能，确保应用程序在不同操作系统上具有相似的外观和行为
- 2. 丰富的功能库: QT 提供了大量的类库和工具，涵盖了图形用户界面（GUI）设计、网络编程、数据库访问、多线程处理等各个方面 例如， QT 的 GUI 库提供了丰富的控件和布局管理器，使开发者能够轻松创建美观、易用的用户界面。网络库则支持各种网络协议，方便进行网络通信开发。
- 3. 强大的图形界面设计: QT Creator 是 QT 提供的集成开发环境（IDE），其中包含了可视化的界面设计工具 Qt Designer。通过 Qt Designer，开发者可以通过拖拽控件、设置属性等方式快速设计用户界面，然后生成相应的 C++ 代码。这大大简化了 GUI 开发的过程。
- 4. 信号与槽机制: QT 引入了信号与槽（Signals and Slots）机制，用于实现对象之间的事件通信。当一个特定的事件发生时，一个对象可以发出一个信号。其他对象可以连接到这个信号，并在接收到信号时执行相应的槽函数。这种机制使得代码的耦合度降低，提高了代码的可维护性和可扩展性

### 运行关系
![alt text](image.png)

### 打包程序
#### 在对应的终端（MSVC\MinGW）执行windeployqt *.exe

### 制作安装包
#### nsis
- 1. 设置软件图标
![alt text](image-1.png)
- 2. 编写授权文件
![alt text](image-2.png)
- 3. 打包程序目录
![alt text](image-3.png)

### 添加可执行程序图标
```c
RC_ICONS = images/logo.ico
```

### 启用高DPI缩放
#### 这个函数是用来启用高DPI缩放的。当应用程序在高分辨率的显示设备上运行时， Qt会自动根据系统的DPI设置来缩放界面元素，使得界面在不同分辨率的显示器上具有合适的大小和清晰度。此属性应在创建QApplication对象之前设置
```c
// 启用高DPI缩放
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
```

### 应用程序风格样式
```c
#include <QStyleFactory>

a.setStyle(QStyleFactory::create("fusion")); // fusion 这个主题比较好看
```

### 加载皮肤
```c
//在文本中加载样式表
//QFile file(":/qss/silvery.css");
QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
```

### 编码转换
```c
//*.pro

msvc {
    QMAKE_CXXFLAGS += /utf-8
    QMAKE_CFLAGS   += /utf-8
}
```
---

### 图片转换工具PictureToIcon

#### QT关键explicit的理解
```c
class MyClass {
    public:
    explicit MyClass(int value);
};
MyClass obj = 5; // 错误， 因为构造函数是explicit， 不允许这样的隐式转换
MyClass obj(5); // 正确， 显式调用构造函数
//没有 explicit 关键字时，编译器会尝试进行隐式转换，将 5 转换为 MyClass 类型的对象，这种隐式转换可能会导致一些意外的行为，尤其是当这种转换不是直观或者不符合设计意图的时候
```

#### QFileDialog类
##### QFileDialog 类允许用户遍历文件系统，以便选择一个或多个文件或目录，在文件管理器、文本编辑器、图片编辑工具等应用场景中非常实用
```c
// 1. 获取要打开的文件名 返回文件名
QString getOpenFileName(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir =QString(), const QString &filter = QString(), QString *selectedFilter = nullptr, QFileDialog::Optionsoptions = Options())

// 2. 获取要打开的多个文件名 , 返回一个文件名列表
QStringList getOpenFileNames(QWidget *parent = nullptr, const QString &caption = QString(), const QString&dir = QString(), const QString &filter = QString(), QString *selectedFilter = nullptr, QFileDialog::Optionsoptions = Options())

// 3. 获取要保存的文件名 , 返回一个文件名
QString getSaveFileName(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir =QString(), const QString &filter = QString(), QString *selectedFilter = nullptr, QFileDialog::Optionsoptions = Options())
```

#### QFileInfo类
- 1. 文件基本信息获取：
    - QString fileName() ：返回不带路径的文件名称。例如对于路径 “/home/user/file.txt”，返回 “file.txt”
    - QString filePath() ：返回包含文件名的文件路径。对于上述路径，返回 “/home/user/file.txt”
    - QString path() ：返回文件的路径，不包含文件名。对于 “/home/user/file.txt”，返回 “/home/user”qint64 size() ：获取文件的大小，以字节为单位
- 2. 文件类型判断：
    - bool isFile() ：判断对象是否指向文件或指向文件的符号链接（如果文件是符号链接，并且目标是常规文件，则返回true ）
    - bool isDir() ：判断对象是否指向目录或指向目录的符号链接1
    - bool isSymLink() ：判断对象是否指向符号链接或快捷方式1
- 3. 路径相关判断：
    - bool isAbsolute() ：判断文件路径是否为绝对路径。以冒号 ( : ) 开头的路径始终被视为绝对路径（因为它们表示 Qt 资源）
    - bool isRelative() ：判断文件路径是否为相对路径
- 4. 日期时间信息：
    - QDateTime created() ：返回文件的创建时间。如果文件是符号链接，则返回目标文件的创建时间
    - QDateTime lastModified() ：返回文件的最近修改时间
    - QDateTime lastRead() ：返回文件的最近读取时间

#### QLabel类
- setText 设置显示内容
```c
void setText(const QString &)
```
- text() 获取label中的内容
```c
QString text() const
```
- setPixmap 设置显示图片
```c
void setPixmap(const QPixmap &)
```

#### QRadioButton单选按钮
- 这是一个选项按钮，可以打开(选中)或关闭(未选中)。单选按钮通常 为用户提供“众多选择中的一个”
- 在一组单选按钮中，一次只能选中一个单选按钮;如果用户选择另一个按钮，先前选择的按钮将被关闭
- 单选按钮默认情况下是自动排他的。如果启用了自动排他，那么属于同一个父小部件的单选按钮的行为就像属于同一个排他按钮组一样。如果您需要多个独占按钮组用于属于同一个父小部件的单选按钮，请将它们放入QButtonGroup中
- 每当按钮被打开或关闭时，它都会发出toggled()信号。如果您想在每次按钮改变状态时触发一个操作，则连接到此信号
- 使用isChecked()查看特定的按钮是否被选中

#### QPixmap类
##### Qt提供了四个类来处理图像数据 ： QImage, QPixmap, QBitmap和QPicture。QPixmap 是 Qt 框架中用于图像处理的类
- 获取图像信息：
    - int width() const ：获取图像的宽度，单位是像素
    - int height() const ：获取图像的高度，单位是像素
    - QSize size() const ：获取图像的大小，即 QSize(width(), height()) 
    - int depth() const ：获取图像的颜色深度，即每像素所占的比特数
    - QRect rect() const ：获取图像的矩形区域，即 QRect(QPoint(0, 0), size()) 
- 图像加载与保存：
    -bool load(const QString &filename, const char *format = 0, Qt::ImageConversionFlags flags =
    - Qt::AutoColor) ：从文件加载图像，参数含义与构造函数中相同，返回值为 true 表示加载成功， false 表示加载失败
    - bool save(const QString &filename, const char *format = 0, int quality = -1) const ：将QPixmap 代表的图像保存到文件。 filename 是文件名； format 表示图像文件的格式，如果为 0，将根据文件名的后缀自动确定文件格式； quality 对于有损压缩的文件格式来说，它表示图像保存的质量，取值范围为 0 -100， -1 表示采用默认值。返回值为 true 表示保存成功， false 表示保存失败
- 图像缩放： QPixmap scaled(const QSize &size, Qt::AspectRatioMode aspectRatioMode =Qt::IgnoreAspectRatio, Qt::TransformationMode transformMode = Qt::FastTransformation) const 或QPixmap scaled(int width, int height, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio,
Qt::TransformationMode transformMode = Qt::FastTransformation) const 等函数可用于对图像进行缩放操作。例如， scaled 函数的第一个参数是目标大小， aspectRatioMode 是宽高比模式， transformMode 是变换模式2
---

### 文本转语音TextToSpeech

#### QTextToSpeech类
- 可以实现文字转语音的功能， 使用say()开始合成文本
- 可以使用setLocale()来指定语言
- 要在可用的语音之间进行选择，请使用setVoice()
- 语言和声音取决于每个平台上可用的合成器。 Linux操作系统默认使用语音调度器

#### availableEngines静态方法
```c
QStringList list = QTextToSpeech::availableEngines() ;// 获取有效地引擎
for(QString &engine:list) // 使用迭代器的方式, 访问list中的所有成员
{   
    qDebug()<<"engine:"<<engine;
    ui->comboBox_engine->addItem(engine);
}
```

#### QStringList字符串列表
```c
- QStringList继承自 QList<QString> ， QList就是C++的List， 底层实现时一个双链表， 可以使用这个类来处理多个字符串，还等价于c语言的字符指针数组 
- 像QList一样， QStringList是隐式共享的。它提供了基于索引的快速访问以及快速插入和删除 将字符串列表作为值参数传递既快速又安全
- QList的所有功能也适用于QStringList。例如，可以使用isEmpty()来测试列表是否为空，还可以调用append()、 prepend()、insert()、 replace()、 removeAll()、 removeAt()等函数。 removeFirst()、 removeLast()和remove One()修改QStringList。此外，QStringList提供了一些方便的函数，使处理字符串列表更容易
```

#### QComboBox类
- ComboBox提供了一种方法，以占用最小的屏幕空间的方式向用户显示选项列表， 就是我们理解的下拉列表。
- 组合框是一个显示当前项的选择小部件，可以弹出可选择项的列表。组合框可以是可编辑的，允许用户修改列表中的每一项。组合框可以包含像素图和字符串;
如果组合框的当前项发生变化，则会发出三个信号:currentindexChanged()、currentTextChanged()和activated()
- currentIndexChanged()和currentTextChanged()总是被触发，而不管更改是通过编程方式还是通过用户交互完成的，而activate()只在更改是由用户交互引起的时候被触发
```c
Q
StringList list = QTextToSpeech::availableEngines() ;// 获取有效地引擎
for(QString &engine:list)
{
    qDebug()<<"engine:"<<engine;
    ui->comboBox_engine->addItem(engine); // 向comboBox_engine中添加元素
}
```

#### availableLocales方法
- QTextToSpeech类的一个成员方法(成员函数)
- 获取当前支持的语言种类，返回一个向量列表。
- QVector 就是C++中的vector , 底层实现是一个顺序表
- 函数原型
```c
QVector<QLocale> QTextToSpeech::availableLocales();
```
- 代码实现
```c
QVector<QLocale> language = tts->availableLocales(); // 获取语音引擎支持的语言

for(QLocale local:language) // 模板容器都支持迭代器的功能
{
    qDebug()<<"local:"<<local; // 显示所有
    qDebug()<<"local language:"<<local.language(); // 显示语言
    qDebug()<<"local country :"<<local.country(); // 显示国家
    qDebug()<<"country :"<<QLocale::countryToString(local.country()); // 显示国家
    qDebug()<<"language:"<<QLocale::languageToString(local.language()); // 显示言
    qDebug()<<"script :"<<QLocale::scriptToString(local.script()); // 显示描述信息
    
    ui->comboBox_language->addItem(QString(tr("%0-%1-%2")
                        .arg(QLocale::countryToString(local.country()))
                        .arg(QLocale::scriptToString(local.script()))
                        .arg(QLocale::languageToString(local.language()))
                        ),QVariant(local)
                        );
}
```

#### QLocale类
- 是表示一个语言类。里面支持国家信息、语言和描述信息
- QLocale在其构造函数中使用语言/国家对进行初始化，并提供类似于QString中的数字到字符串和字符串到数字的转换函数。
- country() 得到国家的枚举类型常量
```c
QString countryToString(QLocale::Country country) // 把国家信息转成字符串
QString languageToString(QLocale::Language language) // 把语言信息转成字符串
QString scriptToString(QLocale::Script script) // 把描述信息转成字符串

QVector<QLocale> language = tts->availableLocales(); // 获取语音引擎支持的语言
for(QLocale local:language) // 模板容器都支持迭代器的功能
{
    qDebug()<<"local:"<<local; // 显示所有
    qDebug()<<"local language:"<<local.language(); // 显示语言
    qDebug()<<"local country :"<<local.country(); // 显示国家
    qDebug()<<"country :"<<QLocale::countryToString(local.country()); // 显示国家
    qDebug()<<"language:"<<QLocale::languageToString(local.language()); // 显示言
    qDebug()<<"script :"<<QLocale::scriptToString(local.script()); // 显示描述信息
    
    ui->comboBox_language->addItem(QString(tr("%0-%1-%2")
                .arg(QLocale::countryToString(local.country()))
                .arg(QLocale::scriptToString(local.script()))
                .arg(QLocale::languageToString(local.language()))
                ),QVariant(local)
                );
}
```

#### 字符串拼接tr与arg
- 等价于C语言的sprintf函数
- tr函数用于生成多国语言, 在tr函数内可以使用中文，将来这个中文可以自动转换成英文，俄文，法语，日语...
- 还可以使用arg的方式来进行字符串的拼接
```c
QString i; // current file's number
QString total; // number of files to process
QString fileName; // current file's name
QString status = QString("Processing file %1 of %2: %3").arg(i).arg(total).arg(fileName);

QVector<QLocale> language = tts->availableLocales(); // 获取语音引擎支持的语言
for(QLocale local:language) // 模板容器都支持迭代器的功能
{
    qDebug()<<"local:"<<local; // 显示所有
    qDebug()<<"local language:"<<local.language(); // 显示语言
    qDebug()<<"local country :"<<local.country(); // 显示国家
    qDebug()<<"country :"<<QLocale::countryToString(local.country()); // 显示国家
    qDebug()<<"language:"<<QLocale::languageToString(local.language()); // 显示语言
    qDebug()<<"script :"<<QLocale::scriptToString(local.script()); // 显示描述信息
    
    ui->comboBox_language->addItem(QString(tr("%0-%1-%2")
                .arg(QLocale::countryToString(local.country()))
                .arg(QLocale::scriptToString(local.script()))
                .arg(QLocale::languageToString(local.language()))
                ),QVariant(local)
                );
}
```

#### QVariant联合体
- 这个是一个联合体， 共享一段内存， 可以存放不同类型的变量， 在C++中存放不同类型的类对象。
- 可以通过构造函数构造出各种类型的QVariant ， 也就是支持很多类型的存放
```c
QVector<QLocale> language = tts->availableLocales(); // 获取语音引擎支持的语言
for(QLocale local:language)
{
    qDebug()<<"local:"<<local; // 显示所有
    qDebug()<<"local language:"<<local.language(); // 显示语言
    qDebug()<<"local country :"<<local.country(); // 显示国家
    qDebug()<<"country :"<<QLocale::countryToString(local.country()); // 显示国家
    qDebug()<<"language:"<<QLocale::languageToString(local.language()); // 显示语言
    qDebug()<<"script :"<<QLocale::scriptToString(local.script()); // 显示描述信息
    ui->comboBox_language->addItem(QString(tr("%0-%1-%2")
                .arg(QLocale::countryToString(local.country()))
                .arg(QLocale::scriptToString(local.script()))
                .arg(QLocale::languageToString(local.language()))
                ),QVariant(local)
                );
// 把local存放到下拉列表中, 每一个选项(一个对象字符串)对应一个QVariant变量
}
```

#### availableVoices获取支持的声音
- 获取语音引擎支持的声音
- 代码实现
```c
Q
Vector<QVoice> voices = tts->availableVoices(); // 获取语音引擎支持的声音
for(QVoice voice:voices) // C++ 的迭代器
{
    //qDebug()<<"voice:"<<voice; // 显示所有
    qDebug()<<"genderName :"<<QVoice::genderName(voice.gender()); // 显示性别
    qDebug()<<"name :"<<voice.name() ; // 显示姓名
    ui->comboBox_gender->addItem(QString(tr("%0(%1)")
                .arg(voice.name())
                .arg(QVoice::genderName(voice.gender()))
                )
                );
}
```

#### QVoice声音类
- 成员函数
```c
QVoice::Age age() const // 声音的年龄
QVoice::Gender gender() const // 声音的性别
QString name() const // 声音的姓名
```
- 静态成员函数
```c
QString ageName(QVoice::Age age) // 把声音年龄转换成字符串
QString genderName(QVoice::Gender gender) // 把声音性别转换成字符串
```
- 代码实现
```c
QVector<QVoice> voices = tts->availableVoices(); // 获取语音引擎支持的声音
for(QVoice voice:voices) // C++ 的迭代器
{
    //qDebug()<<"voice:"<<voice; // 显示所有
    qDebug()<<"genderName :"<<QVoice::genderName(voice.gender()); // 显示性别
    qDebug()<<"name :"<<voice.name() ; // 显示姓名
    ui->comboBox_gender->addItem(QString(tr("%0(%1)")
                .arg(voice.name())
                .arg(QVoice::genderName(voice.gender()))
                )
                );
}
```

#### QSlider滑动条类 
- 滑块是控制有界值的经典小部件。它允许用户沿着水平或垂直槽移动滑块手柄，并将手柄的位置转换为合法范围内的整数值。
- QSlider自己的函数很少;大部分功能都在QAbstractSlider中。最有用的函数是setValue()，它将滑块直接设置为某值;
- triggerAction()来模拟点击的效果(对于快捷键很有用);setSingleStep()， setPageStep()设置步骤;和setMinimum()和setMaximum()来定义滚动条的范围。 QSlider提供了控制标记的方法。
- 您可以使用setTickPosition()来指示您想要标记的位置，使用setTickinterval()来指示您想要标记的数量。当前设置的滴答位置和间隔可以分别使用tickPosition()和ticklnterval()函数查询
- 代码实现
```c
void widget::on_horizontalSlider_speed_valueChanged(int value)
{
    //qDebug()<<"on_horizontalSlider_speed_valueChanged:"<<value;
    ui->label_speed->setNum(value); // 设置显示的数字
    // 让0-100 的值 转成-1.0 到正1.0 之间的数
    double newvalue = (value-50)/50.0 ; // 0-100 减去50 变为 -50 ~ 50 之间 , 再除以50.0 即可
    if(tts != nullptr)
    {
        tts->setRate(newvalue);// 设置播放语速
    }
}
```

#### QTextEdit多行文本控件
#### 这个类是处理多行文本的控件 , 目前只需要知道2个方法即可
- 设置文本 setText(const QString &text)
- 获取文本 toPlainText() , 这个文本没有格式 
---

### 秒表计时器Timer

#### QString::asprintf字符串的拼接
```c
QString data = QString::asprintf("%02d:%02d.%02d",min,sec,ms); // 拼接字符串
```

#### QTimer类
- 这个类提供了单次定时和连续定时的功能
- connect 设置信号处理函数
- start() 启动定时器
- stop() 停止定时器
```c
// 定义一个定时器 , 等价于C语言的malloc
timer = new QTimer(this);
// 设置定时器的信号处理函数， 等价于linux c 的signal函数功能
// 参数1 : 发送信号者 timer
// 参数2 : 发送信号者 发送什么信号 , &类名::信号
// 参数3 : 接收信号者 this, 就是这个应用程序MainWindow
// 参数4 : 信号处理函数 用于自定义
connect(timer,&QTimer::timeout,this ,&MainWindow::timeout_slot);
// 启动定时器 , 10ms 执行一次信号处理函数
timer->start(10);
// 这个函数是信号处理函数
// 让定时器10ms执行一次timeout_slot
void MainWindow::timeout_slot()
{
    qDebug()<<"timerout_slot():";
    //qDebug()<<data;
} 

if(timer != nullptr)
    {
    timer->stop() ; // 定时器停止工作
}
```

#### QPushButton按下与抬起功能
- 可以实现按钮的按下效果和抬起效果两种功能 
- 这种按钮也叫作自锁按钮
- 可以使用接口函数setCheckable（）进行设置
```c
pushButton_start->setCheckable(true);
```

#### QPushButton的按钮状态获取
- 可以获取按钮按下或则是弹起的状态
- 使用isChecked() 成员函数来获取
```c
// pushButton_start是否被按下, 如果按下返回为真 , 否则返回为假
if(ui->pushButton_start->isChecked()) //
{
    qDebug()<<"pushButton_start被按下";
    // 计数
    qDebug()<< QString::asprintf("%02d:%02d.%02d",min,sec,ms); // 拼接字符串
}
```

#### QLCDNumber类
- 可以设置显示数码管的位数
```c
lcdNumber = new QLCDNumber(centralwidget); // 申请内存
lcdNumber->setObjectName(QString::fromUtf8("lcdNumber")); // 设置对象的名称
lcdNumber->setGeometry(QRect(0, 0, 400, 100)); // 设置数码管的尺寸
lcdNumber->setSmallDecimalPoint(true); // 设置 数码管的点 , 不占用一个位置
lcdNumber->setDigitCount(7); // 数码管的位数
lcdNumber->setSegmentStyle(QLCDNumber::Flat);// 数码管的显示样式
ui->lcdNumber->display( QString::asprintf("%02d:%02d.%02d",min,sec,ms)); // 拼接字符串 , 在数码管上显示数字的字符串
```

#### QStandardItemModel类
- 是model/view 框架的model部分 , 数据保存部分
- QStandardItemModel负责保存数据，每个数据项被表示为类QStandardItem的对象
- QStandardItem用来保存一个数据项，再使用QStandardItemModel将这些数据项组织起来，形成列表、表格或者树，以供其他视图类显示
```c
QStandardItemModel * model ; // QStandardItemModel 这是一个标准的model/view的框架
model = new QStandardItemModel(this); // 定义一个数据结构 , 用来保存数据
/*设置列字段名*/
model->setColumnCount(2); // 设置这个数据模型为2列 , 设置 一行有2列
model->setHeaderData(0,Qt::Horizontal, tr("序号")); // 第一列名 序号
model->setHeaderData(1,Qt::Horizontal, tr("数值")); // 第二列名 数值
// 把 数据模型和显示模型进行关联
ui->tableView->setModel(model) ; // 给tableview 安装一个数据模型 model ， 数据此时就显示出来了
```
- 设置一条数据
```c
/*设置一条数据*/
// lineCount : 是数据的第几行
// 0 : 第几列
model->setItem(lineCount, 0, new QStandardItem(QString::asprintf("%03d",lineCount+1)));
model->setItem(lineCount, 1, new QStandardItem(QString::asprintf("%02d:%02d.%02d",min,sec,ms)));
model->item(lineCount, 0)->setTextAlignment(Qt::AlignCenter); // 设置文本居中对齐
model->item(lineCount, 1)->setTextAlignment(Qt::AlignCenter); // 设置文本居中对齐
ui->tableView->setModel(model) ; // 给tableview 安装一个模型 model
```
- 删除数据
```c
model->removeRows(0,lineCount); // 从0行 一直删除到 指定的行
```

#### QTableView类
- 从数据模型中关联数据并按照表的形式显示数据，是一个显示模型
- 是model / view 的view显示部分
```c
ui->tableView->horizontalHeader()->setDefaultSectionSize(199); // 设置水平头的宽度
ui->tableView->verticalHeader()->setHidden(true); // 行名隐藏
ui->tableView->setModel(model) ; // 给tableview 安装一个模型 model
//设置选中时为整行选中
ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//设置表格的单元为只读属性， 即不能编辑
ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
```

#### QTranslator类
- 可以使程序实现多语言的切换
- 设置启动英文语言
```c
QTranslator translator; // 语言翻译类
translator.load("en_US.qm"); // 去当前目录下去查 , 05-Timer-Desktop_Qt_5_15_2_MSVC2019_64bit-Debug
// 以下两种办法都可以, 静态方法更加适用
#if 1
    QApplication::installTranslator(&translator);
#else
    if(appPointer != nullptr)
    {
    appPointer->installTranslator(&translator); // 安装英文
    }
#endif
ui->retranslateUi(this); // 重新初始化界面
model->clear(); // 把model中的所有内容清空
model->setColumnCount(2); // 设置列数 ,一共是2列
model->setHeaderData(0,Qt::Horizontal,tr("NO")); // 第1列的列名
model->setHeaderData(1,Qt::Horizontal,tr("Value")); // 第2列的列名
ui->tableView->setModel(model);
```
- 设置恢复中文语言
```c
// 以下两种办法都可以, 静态方法更加适用
#if 1
    QApplication::installTranslator(nullptr);
#else
    if(appPointer != nullptr)
    {
    appPointer->installTranslator(NULL); // 不安装语言包, 使用默认语言中文
    }`
#endif
ui->retranslateUi(this);
model->clear(); // 把model中的所有内容清空
model->setColumnCount(2); // 设置 一行有2列
model->setHeaderData(0,Qt::Horizontal, tr("序号")); // 第一列名 序号
model->setHeaderData(1,Qt::Horizontal, tr("数值")); // 第二列名 数值
ui->tableView->setModel(model);
```

#### ts文件生成与配置
- 默认的情况下 , 如果没有在新建工程时选择添加语言包时，需要手动添加ts语言包
- 新创建一个工程 , 选择要添加的语言包， 会生成一个语言包， 把这个语言包复制到我们的工程内

#### qm文件的生成与配置
- 这个文件是由ts生成的目标文件 ， 可以直接被加载的文件
---

### 记事本Notepad

#### 判断字符串是否为空
```c
// 是否获取到了文件名
    if(!fileName.isEmpty()) // 获取到文件名后, 才可以操作
    {
        QFile file(fileName) ; // 创建一个文件对象
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        QByteArray data = file.readAll(); // data 就是一个数组,带编码格式的数组, 需要解码
        ui->textEdit->setText(QString(data));// 显示到控件上
        QFileInfo fileinfo(fileName);
        this->setWindowTitle(fileinfo.fileName()+tr(" - 记事本"));
        file.close();// 关闭文件
        saveFlag = true;// 数据已经存盘
    }
```

#### 文件操作QFile类
- QFile 类提供了 操作文件的类，可以对文件进行打开， 关闭， 读写， 定位的功能
- open() 打开文件 , 等价于C语言的open函数
- close() 关闭文件
- readAll() 读文件
- write() 写文件
```c
// 是否获取到了文件名
    if(!fileName.isEmpty()) // 获取到文件名后, 才可以操作
    {
        QFile file(fileName) ; // 创建一个文件对象
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        QByteArray data = file.readAll(); // data 就是一个数组,带编码格式的数组, 需要解码
        ui->textEdit->setText(QString(data));// 显示到控件上
        QFileInfo fileinfo(fileName);
        this->setWindowTitle(fileinfo.fileName()+tr(" - 记事本"));
        file.close();// 关闭文件
        saveFlag = true;// 数据已经存盘
    }
```

#### 获取文件信息QFileInfo类
- 可以获取文件名和路径
- fileName() 可以获取文件名
```c
QFileInfo fileinfo(fileName);
this->setWindowTitle(fileinfo.fileName()+tr(" - 记事本"));
```

#### 文件读写的编码转换
- 在读写文件时，需要对读回来的内容进行解码
- 写文件时， 要对写入的内容进行编码
```c
//例如 ， 写文件时， 要把QString 转换成QByteArray , 需要对字符串进行编码即可
// 文件名 存在
QFile file(fileName) ; // 创建一个文件对象
// 文件存在, 要清空
if (!file.open(QIODevice::ReadWrite | QIODevice::Text|QIODevice::Truncate))
    return;
// 把 QString 转换成QByteArray , 需要对字符串进行编码即可
file.write(ui->textEdit->toPlainText().toUtf8());// 把数据写入到文件内
file.close() ; // 关闭文件


//例如 ， 读文件时， 要把QByteArray转换成QString , 需要对字符串进行解码
// 打开文件
fileName = QFileDialog::getOpenFileName(this,tr("打开"),".","Text Files (*.txt);; All Files (*.*)");
qDebug()<<"fileName="<<fileName;
// 是否获取到了文件名
if(!fileName.isEmpty()) // 获取到文件名后, 才可以操作
{
    QFile file(fileName) ; // 创建一个文件对象
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QByteArray data = file.readAll(); // data 就是一个数组,带编码格式的数组, 需要解码
    ui->textEdit->setText(QString(data));// 显示到控件上， 就是解码
    QFileInfo fileinfo(fileName);
    this->setWindowTitle(fileinfo.fileName()+tr(" - 记事本"));
    file.close();// 关闭文件
    saveFlag = true;// 数据已经存盘
}
```

#### QByteArray类
- 我们可以这么理解， 这个类就是一个带编码的字符串， 写入文件时需要使用QByteArray 格式， 显示到控件上时， 需要转换成QString
- 网络通信时, 也需要使用QByteArray格式的字节数组

```c
//读文件的QByteArray
// 打开文件
fileName = QFileDialog::getOpenFileName(this,tr("打开"),".","Text Files (*.txt);; All Files (*.*)");
qDebug()<<"fileName="<<fileName;
// 是否获取到了文件名
if(!fileName.isEmpty()) // 获取到文件名后, 才可以操作
{
    QFile file(fileName) ; // 创建一个文件对象
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QByteArray data = file.readAll(); // data 就是一个数组,带编码格式的数组, 需要解码
    ui->textEdit->setText(QString(data));// 显示到控件上
    QFileInfo fileinfo(fileName);
    this->setWindowTitle(fileinfo.fileName()+tr(" - 记事本"));
    file.close();// 关闭文件
    saveFlag = true;// 数据已经存盘
}

//写文件的QByteArray
// 文件名 存在
QFile file(fileName) ; // 创建一个文件对象
// 文件存在, 要清空
if (!file.open(QIODevice::ReadWrite | QIODevice::Text|QIODevice::Truncate))
return;
// 把 QString 转换成QByteArray , 需要对字符串进行编码即可
file.write(ui->textEdit->toPlainText().toUtf8());// 把数据写入到文件内
file.close() ; // 关闭文件
```

#### QMessageBox类
- 用来处理弹窗显示的类
- 可以使用类创建对象的方式，进行使用
```c
// 且 textedit 中有内容, , 提示是否需要保存
if(!ui->textEdit->toPlainText().isEmpty()) //textedit 中有内容
{
    // 弹窗
    qDebug()<<"要弹窗";
    QMessageBox msgBox;
    // 遗留问题1: 如何改变弹窗的尺寸, 目前改不了
    msgBox.setWindowTitle(tr("记事本"));
    //msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save); // 默认选择
    int ret = msgBox.exec();
    switch (ret)
    {
        case QMessageBox::Save:
        // Save was clicked
        on_action_save_triggered();
        // fileName 字符串清空
        fileName.clear();
        ui->textEdit->clear();
        this->setWindowTitle(tr("无标题")+tr(" - 记事本"));
        break;
        case QMessageBox::Discard:
        // Don't Save was clicked
        fileName.clear();
        ui->textEdit->clear();
        this->setWindowTitle(tr("无标题")+tr(" - 记事本"));
        break;
        case QMessageBox::Cancel:
        // Cancel was clicked
        break;
        default:
        // should never be reached
        break;
    }
}

//还可以使用静态成员函数的方式
void MainWindow::on_action_about_notepad_triggered()
{
    QMessageBox::about(this,tr("记事本"),tr("这是记事本 1.5 "));
} v
oid MainWindow::on_action_aboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}
```

#### 事件触发closeEvent方法
- 每次关闭窗口时, 发送一个事件QCloseEvent ，应用程序可以接收这个事件, 并对事件进行处理
- 要实现关闭窗口时, 提示是否保存文件, 必须使用重新实现 QMainWindow中的一个方法 closeEvent
- accept() 让事件继续传递下去， 不影响事件最终的效果， 关闭窗体
- ignore() 忽略关闭窗体的操作
```c
//mainwindow.h 中声明
// 声明一个父类的虚函数, 用子类替换父类的实现
void closeEvent(QCloseEvent *event);

//mainwindow.cpp
// 要实现关闭窗口时, 提示是否保存文件, 必须使用重新实现 QMainWindow中的一个方法 closeEvent
// 每次关闭窗口时, 发送一个事件QCloseEvent ,应用程序可以接收这个事件, 并对事件进行处理
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"closeEvent被触发";
    //
    if(fileName.isEmpty()) // 文件名为空
    {
        // 且 textedit 中有内容, 需要弹窗, 提示是否需要保存
        if(!ui->textEdit->toPlainText().isEmpty()) //textedit 中有内容
        {
            // 弹窗
            qDebug()<<"要弹窗";
            QMessageBox msgBox;
            // 遗留问题1: 如何改变弹窗的尺寸, 目前改不了
            msgBox.setWindowTitle(tr("记事本"));
            //msgBox.setText("The document has been modified.");
            msgBox.setInformativeText("Do you want to save your changes?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save); // 默认选择
            int ret = msgBox.exec();
            switch (ret)
            {
                case QMessageBox::Save:
                    // Save was clicked
                    // 继续让事件传递下去
                    event->accept();
                    break;
                case QMessageBox::Discard:
                    // Don't Save was clicked
                    // 继续让事件传递下去
                    event->accept();
                    break;
                case QMessageBox::Cancel:
                    // Cancel was clicked
                    event->ignore(); // 忽略关闭窗体的操作
                    break;
                default:
                    // should never be reached
                    break;
            }
        } 
        else // 文件名为空 , textedit没有内容, 不需要弹窗
        {
            qDebug()<<"文件名为空 , textedit没有内容, 不需要弹窗";
        }
    } 
    else // 文件名不为空
    {
        // 文件是否存盘
        // 文件是否保存标志位, true: 表示存盘 , false : 没有存盘
        if(!saveFlag) // 条件满足 , 表示没有存盘 , 需要弹窗提示保存
        {
            qDebug()<<"文件名不为空 文件没有保存,需要弹窗";
            QMessageBox msgBox;
            // 遗留问题1: 如何改变弹窗的尺寸, 目前改不了
            //msgBox.setText("The document has been modified.");
            msgBox.setInformativeText("Do you want to save your changes?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save); // 默认选择
            int ret = msgBox.exec();
            switch (ret)
            {
                case QMessageBox::Save:
                    // Save was clicked
                    // 继续让事件传递下去
                    event->accept();
                    break;
                case QMessageBox::Discard:
                    // Don't Save was clicked
                    // 继续让事件传递下去
                    event->accept();
                    break;
                case QMessageBox::Cancel:
                    // Cancel was clicked
                    event->ignore(); // 忽略关闭窗体的操作
                    break;
                default:
                    // should never be reached
                    break;
            }
        } 
        else // 文件已存盘
        {

        }
    }
}
```

#### QPrinter类
- 这是一个打印机类， 表示一个打印机
```c
    QPrinter printer ; // 定义一个打印机
    QPrintDialog printDialog(&printer, this); // 定义一个打印对话窗口
    if (printDialog.exec() == QDialog::Accepted) 
    { 
    // 点击确定时, 开始打印
    // print ...
        ui->textEdit->print(&printer); // 把textedit中的内容打印
    }
```

#### QPrintDialog类
- 这是一个打印对话框， 可以选择打印机和打印设置的对话框
```c
Printer printer ; // 定义一个打印机
QPrintDialog printDialog(&printer, this); // 定义一个打印对话窗口
if (printDialog.exec() == QDialog::Accepted) { 
    // 点击确定时, 开始打印
    // print ...    
    ui->textEdit->print(&printer); // 把textedit中的内容打印
}
```

#### QFont类
- 表示一个字体的信息
- 一个字体信息如下， 字体名 ， 字体大小， 宽度 ， 是否斜体
```c
QFont(Adobe Devanagari,22,-1,5,50,0,0,0,0,0,Regular)
QFont(Arial,12,-1,5,50,0,0,0,0,0,Regular)
```

#### QFontDialog类
- 字体对话框类
- getFont() 获取字体
```c
void MainWindow::on_action_font_triggered()
{
    bool ok;
    // 获取字体
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) 
    {
    // the user clicked OK and font is set to the font the user selected
    } 
    else 
    {
    // the user canceled the dialog; font is set to the initial
    // value, in this case Helvetica [Cronyx], 10
    } 
    qDebug()<<"font="<<font;
    ui->textEdit->setFont(font); // 对选中的文本设置字体
}
```

#### QAction类
- 这个是菜单中的动作类 , 用来表示一个菜单中的选项
- setCheckable() 可以让QAction 实现两种状态切换 , 实现开关的切换
```c
QAction *action_bold;
action_bold = new QAction(MainWindow);
action_bold->setObjectName(QString::fromUtf8("action_bold"));
action_bold->setCheckable(true);


void MainWindow::on_action_bold_triggered(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontWeight(QFont::Bold); //设置粗体
    } 
    else
    {
        ui->textEdit->setFontWeight(QFont::Normal); //设置正常字体
    }
}
```
---

### 画图工具Painter

#### paintEvent事件
- 这是一个绘画事件，在窗体被显示，隐藏， 或则被遮挡时自动执行的一个事件。
- 这个函数是一个虚函数， 需要在子类中重新实现
- 手动使用update 函数时，也会被调用
```c
protected slots:
    // 这个函数是虚函数, 子类重新实现父类的方法
    // 实现绘画事件 paintEvent
    // 在窗口被显示的时候调用一次 , 窗口发生改变时都会被调用
    // 手动使用update 函数时 也会被调用
    void paintEvent(QPaintEvent *event) ;
```

#### 鼠标事件
- 鼠标事件有按下， 释放， 单击， 右击， 移动， 滚轮事件。
- 在程序中可以判断鼠标的操作。
```c
// 这几个函数是虚函数, 这里时重新实现QWidget的函数, 子类覆盖父类
void mousePressEvent(QMouseEvent *event); // 鼠标按压事件
void mouseReleaseEvent(QMouseEvent *event); // 鼠标释放事件
void mouseMoveEvent(QMouseEvent *event); // 鼠标移动事件
```

#### 鼠标的按压事件mousePressEvent
-分为单击， 右击 ， 双击都属于按压事件
```c
void MainWindow::mousePressEvent(QMouseEvent *event) // 鼠标按下事件
{
    if(event->button() == Qt::LeftButton){ // 如果是鼠标左键按下
        qDebug()<<"鼠标左键被按下";
        qDebug()<<"鼠标被单击:"<<event->pos(); // 打印鼠标的位置
    }
}
```

#### 鼠标的释放事件mouseReleaseEvent
- 这个就是鼠标在点击后释放的时候， 发生的事件
```c
void MainWindow::mouseReleaseEvent(QMouseEvent *event) // 鼠标释放事件
{
    // 释放鼠标后 , 要恢复鼠标的形状
    setCursor(Qt::ArrowCursor); // 正常鼠标样式
}
```

#### 鼠标的移动事件mouseMoveEvent
- 在程序中认为鼠标移动时， 是单击后移动鼠标时， 才认定为移动
```c
// 可设置单击后移动, 认为是鼠标移动
// 也可以实时的捕捉
void MainWindow::mouseMoveEvent(QMouseEvent *event) // 鼠标移动事件
{
    qDebug()<<"鼠标移动";
    // 是判断鼠标在单击的过程中移动了鼠标
    if(event->buttons() & Qt::LeftButton)
    {

    }
}
```
- 设置鼠标跟踪
1. 设置鼠标跟踪，默认鼠标需要单机后才可以跟踪，需要设置一下才可以实时跟踪
2. 需要设置2个地方才可以实现实时跟踪
    - MainWindow设置鼠标跟踪
    - centralwidget设置鼠标跟踪
```c
MainWindow->resize(800, 600);
MainWindow->setMouseTracking(true);
centralwidget = new QWidget(MainWindow);
centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
centralwidget->setMouseTracking(true);
```

#### 设置窗体的形状
- setWindowState() 这个函数可以设置窗体的形式 ， 可以全屏， 最大化， 常规形式，最小化几种形式
```c
setWindowState(Qt::WindowMaximized) ; // 让窗体最大化
```

#### 使用paintEvent事件加载一张图片
- 可以使用paintEvent绘画事件， 给程序加载一张背景图片
- 可以使用update 手动产生一次绘图事件
```c
// 在构造函数中, 对fileName进行赋值, 这样可以自动加载这个图片
fileName = ":/images/backgroud.png"; // 这个图片必须在资源文件中
void MainWindow::on_action_picture_triggered()
{
    fileName = QFileDialog::getOpenFileName(this,tr("打开图片"),".",
                                            "Piture Files (*.jdp *.png *.bmp);; All Files (*.*)"
                                            ) ;
    if(!fileName.isEmpty()) //不等于空, 要把这个图片显示到控件内
    {
        update(); // 这个函数被调用后, 会产生一个绘画事件 paintEvent ,paintEvent 事件 是一个虚函数, 我们要重新实现这个函数
    } 
    qDebug()<<"fileName="<<fileName;
}
// 实现绘画事件 paintEvent
// 在窗口被显示的时候调用一次 , 窗口发生改变时都会被调用
// 手动使用update 函数时 也会被调用
void MainWindow::paintEvent(QPaintEvent *event)
{
    qDebug()<<"paintEvent() 被调用";
    QPainter painter(this);// 定义一个画笔, 这个画笔可以画出很多种形状, 图片
    // 把背景图片显示到控件上
    if(!fileName.isEmpty())
    {
        QPixmap map(fileName); // 定义一个pixmap对象
        painter.drawPixmap(QPoint(0,0),map);// 把图片绘制到窗体中
    }
}
```

#### QPainter绘画类
- 这个类可以在图形界面上绘画出指定的形状，文字， 图片等内容
- drawPixmap() 绘制一张图片在指定的窗口上
```c
// 实现绘画事件 paintEvent
// 在窗口被显示的时候调用一次 , 窗口发生改变时都会被调用
// 手动使用update 函数时 也会被调用
void MainWindow::paintEvent(QPaintEvent *event)
{
    qDebug()<<"paintEvent() 被调用";
    QPainter painter(this);// 定义一个画笔, 这个画笔可以画出很多种形状, 图片
    // 把背景图片显示到控件上
    if(!fileName.isEmpty())
    {
        QPixmap map(fileName); // 定义一个pixmap对象
        painter.drawPixmap(QPoint(0,0),map);// 把图片绘制到窗体中
    }
}
```
- drawLine() 绘画出一个直线
- drawEllipse() 绘画出一个同心圆
- QPen 用来定义一个画笔, 笔的颜色, 笔的宽度, 是否抗锯齿
```c
// 实现绘画事件 paintEvent
// 在窗口被显示的时候调用一次 , 窗口发生改变时都会被调用
// 手动使用update 函数时 也会被调用
void MainWindow::paintEvent(QPaintEvent *event)
{
    qDebug()<<"paintEvent() 被调用";
    QPainter painter(this);// 定义一个画笔, 这个画笔可以画出很多种形状, 图片
    if(drawLineFlag) // 为真时表示要画线
    {
        if(linep != nullptr)
        {
            QPen pen ;
            pen.setColor(Qt::red); // 设置画笔的颜色
            pen.setWidth(5) ; // 设置笔的宽度, 以像素为单位
            painter.setPen(pen) ; // 安装一个画笔
            painter.drawLine(linep->p1(),linep->p2());
            painter.drawEllipse(linep->p1(),4,4); // 画出线的弧度, 同心的圆
            painter.drawEllipse(linep->p2(),4,4); // 画出线的弧度, 同心的圆
        }
    }
}
```
- drawPolygon() 绘画多边形
- setRenderHint() 设置画笔是否抗锯齿
```c
// 实现绘画事件 paintEvent
// 在窗口被显示的时候调用一次 , 窗口发生改变时都会被调用
// 手动使用update 函数时 也会被调用
void MainWindow::paintEvent(QPaintEvent *event)
{
    qDebug()<<"paintEvent() 被调用";
    QPainter painter(this);// 定义一个画笔, 这个画笔可以画出很多种形状, 图片
    if(drawPolygonFlag) // 为真时表示要画多边形
    {
        QPen pen ;
        pen.setColor(Qt::yellow); // 设置画笔的颜色
        pen.setWidth(5) ; // 设置笔的宽度, 以像素为单位
        painter.setPen(pen) ; // 安装一个画笔
        painter.setRenderHint(QPainter::Antialiasing); // 边缘抗锯齿 在绘制各种形状时 可以设置抗锯齿
        // 先构建一个多边形 QPolygon
        QPolygon pol(Polygons) ; // 用Polygons 这个容器, 去构建一个pol
        painter.drawPolygon(pol); // 画多边形
        for(int i=0;i<Polygons.size();i++)
        {
            painter.drawEllipse(Polygons.at(i),4,4); // 画出线的弧度, 同心的圆
        }
    }
}
```

#### 判断单击的点是否是指定的点
- 可以使用event指针获取鼠标单击点的位置
- 可以使用绝对值误差的方式来判断是否选中指定的点
- setCursor() 用来设置光标形状，来区分点是否被选中
```c
v
oid MainWindow::mousePressEvent(QMouseEvent *event) // 鼠标按下事件
{
    if(event->button() == Qt::LeftButton)
    { // 如果是鼠标左键按下
    
        qDebug()<<"鼠标左键被按下";
        qDebug()<<"鼠标被单击:"<<event->pos(); // 打印鼠标的位置
        if(linep !=nullptr)
        {
            // 鼠标点击的位置 和 线的坐标位置保持误差在10以内 我们认为就是点击了这个点
            if( (abs( event->pos().x() - linep->p1().x()) < 10 ) &&
                    (abs( event->pos().y() - linep->p1().y()) < 10 ) )
            {
                qDebug()<<"p1 被选中";
                linePointIndex = 1;
                setCursor(Qt::CrossCursor); // 设置鼠标为十字光标
            } 
            else if( (abs( event->pos().x() - linep->p2().x()) < 10 ) &&
                    (abs( event->pos().y() - linep->p2().y()) < 10 ) )
            {
                qDebug()<<"p2 被选中";
                linePointIndex = 2;
                setCursor(Qt::CrossCursor); // 设置鼠标为十字光标
            }
            else
            {
                linePointIndex = 0 ;
                setCursor(Qt::ArrowCursor); // 正常鼠标样式
            }
        } 
        // 鼠标点击的位置 和 多边形的坐标位置保持误差在10以内 我们认为就是点击了这个点
        for(int i=0;i<Polygons.count();i++)
        {
            if( (abs( event->pos().x() - Polygons.at(i).x()) < 10 ) &&
            (abs( event->pos().y() - Polygons.at(i).y()) < 10 ) )
            {
                polygonPointIndex = i+1; // 记录哪一个点被选中
                qDebug()<<"Polygons 被选中:"<<polygonPointIndex;
                //linePointIndex = 2; =
                setCursor(Qt::CrossCursor); // 设置鼠标为十字光标
                break; // 选中点后 , 退出循环
            } 
            else
            {
                polygonPointIndex = 0 ;
                setCursor(Qt::ArrowCursor); // 正常鼠标样式
            }
        }
    }
}
```

#### 直线或多边形拖拽功能实现
- 实时记录鼠标在单击时移动的位置， 并用最新的位置替换被选中的坐标点
- 线的实现使用setP1和setP2来进行更新
- 多边形的话使用replace函数来进行更新
- 更新后手动使用update()来产生一次绘画事件
```c
// 可设置点击后移动, 认为是鼠标移动
// 也可以实时的捕捉
void MainWindow::mouseMoveEvent(QMouseEvent *event) // 鼠标移动事件
{
    qDebug()<<"鼠标移动";
    // 是判断鼠标在单击的过程中移动了鼠标
    if(event->buttons() & Qt::LeftButton)
    { // 这里必须使用buttons()
        drawLineFlag = true;// 设置线绘制标志位 , 会对线进行重新绘制
        
        if(linePointIndex ==1) // 表示选中的p1点
        {
            linep->setP1(QPoint(event->pos())); // 使用当前鼠标的坐标来替换线段的点
            update(); // 产生一次绘图事件
        }
        else if(linePointIndex ==2) // 表示选中的p1点
        {
            linep->setP2(QPoint(event->pos())); // 使用当前鼠标的坐标来替换线段的点
            update(); // 产生一次绘图事件
        } 

        drawPolygonFlag = true;// 设置绘制多边形标志位 , 会对多边形进行重新绘制
        if(polygonPointIndex > 0) // 表示多边形有点被选中
        {
            qDebug()<<"mouseMoveEvent:polygonPointIndex="<<polygonPointIndex;
            Polygons.replace(polygonPointIndex-1,QPoint(event->pos()));
            update(); // 产生一次绘图事件
        }
    }
}
```

#### 子窗体的实现
- qt工程中新建一个设计师界面类
- 添加这个类后， 在需要时可以使用 new 去手动创建这个窗体并显示
- 同时设置信号处理函数
```c
void MainWindow::on_action_polygon_triggered()
{
    if(polygonP != nullptr)
    {
        delete polygonP ;// 释放内存
    } 
    //要做一个弹窗, 在qt 中需要一个子窗体时, 需要单独创建一个窗体类
    polygonP = new polygon; // 这里父窗体不用this,使用了this以后, 会出现内嵌的情况, 让这个窗体独立显示
    // polygon 设置信号处理函数
    connect(polygonP,&polygon::add_newpolygon,this,&MainWindow::add_newpolygon_slot);
    polygonP->show() ;// 显示控件 , 让子窗体显示
}
```

#### emit发送自定义信号
- 在程序中可以自定义一个信号
```c
//polygon.h
class polygon : public QWidget
{
    Q_OBJECT
    public:
    explicit polygon(QWidget *parent = nullptr);
    ~polygon();
    qint32 getPolygonPoints();
    signals:
    void add_newpolygon(); // 自定义信号
    private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();
    private:
    Ui::polygon *ui;
};
```
- 使用emit来发送指定的信号
```c
void polygon::on_pushButton_ok_clicked()
{
    // 发送一个信号
    emit add_newpolygon();
    qDebug()<<"add_newpolygon() 信号被发送";
    this->hide();// 隐藏窗口
}
```

#### 访问子窗体控件中的内容方法
- 应为我们不能通过指针的形式方位子窗体的ui ， 也就不能直接访问子窗体控件中的内容
- 实现方法就是封装共有接口（public）， 然后去调用
```c
class polygon : public QWidget
{
    Q_OBJECT
    public:
    explicit polygon(QWidget *parent = nullptr);
    ~polygon();
    qint32 getPolygonPoints();
    signals:
    void add_newpolygon(); // 实现一个共有接口, 可以使用对象或指针进行访问
    private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();
    private:
    Ui::polygon *ui;
};

qint32 polygon::getPolygonPoints()
{
    return ui->comboBox->currentIndex()+3;
}
```
- 通过指针访问子窗体控件的内容
```c
void MainWindow::add_newpolygon_slot()
{
    qDebug()<<"add_newpolygon_slot被调用";
    if(set.contains("x1")) // 可以在config.ini 进行搜索 , 找到和没找到两种
    { 

    } 
    else // 如果没有就创建 这些值
    {
        // 获取子窗体多边形的吧边数
        if(polygonP != nullptr)
        {
            qint32 count = polygonP->getPolygonPoints(); // 获取要画多边形的点数
        }
    }
}
```

#### QSettings用来保存用户的设置
- QSettings 可以保存用户的设置， 同样也可以加载用户的设置
- 没有这个配置文件会自动创建， 有这个文件自动打开
- beginGroup 函数用来定位一个组， 所有的操作都在这个组内完成
- endGroup 函数用来结束一个组
- contains 函数用来判断组内是否有我们要想的内容，如果没有就创建， 如果有就加载
- value 读取组名内的key值， 这个类似于c++的map
- setValue 把程序的信息写入到文件内
```c
void MainWindow::on_action_line_triggered()
{
    // 设置一个标志位 , 实现要在paintEvent函数内实现, 在这里只需要设置update即可
    drawLineFlag = true ; // 表示可以画线
    update(); // 更新绘画 , 调用paintEvent函数
    // 如果系统已经保存了 line的信息, 则需要自动加载线的信息
    // 如果没有保存, 则使用默认的线信息
    // 创建一个config.ini文件 , 文件不存在则创建, 文件存在则打开
    QSettings set("config.ini",QSettings::IniFormat);
    set.beginGroup("Line1");// 开始的组
    //如果Line1有x1 这个key , 说明我们配置文件中已经保存了线 , 此时就需要我们加载即可
    if(set.contains("x1")) // 可以在config.ini 进行搜索 , 找到和没找到两种
    {
        qint32 x1 = set.value("x1").toInt();
        qint32 y1 = set.value("y1").toInt();
        qint32 x2 = set.value("x2").toInt();
        qint32 y2 = set.value("y2").toInt();
        linep = new QLine(x1,y1,x2,y2);
    } 
    else // 如果没有就创建 这些值
    {
        qint32 x1 = 100;
        qint32 y1 = 100;
        qint32 x2 = 200;
        qint32 y2 = 200;
        linep = new QLine(x1,y1,x2,y2);
        set.setValue("x1",x1);
        set.setValue("y1",y1);
        set.setValue("x2",x2);
        set.setValue("y2",y2);
    } 
    set.endGroup();
}
```


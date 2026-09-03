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
- 这是一个选项按钮，可以打开(选中)或关闭(未选中)。单选按钮通常为用户提供“众多选择中的一个”
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

### 记事本Notepad

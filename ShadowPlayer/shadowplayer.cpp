/*
 * 高低16位定义：
 * #define LOWORD(a) (WORD)(a)
 * #define HIWORD(a) (WORD)((a)>>16)
 */
#include "shadowplayer.h"
#include "ui_shadowplayer.h"
#include "ID3v2Pic.h"
#include "FlacPic.h"

/*
 * QFileDialog中存在内存泄漏BUG
 * 此BUG在QtCreator中同样存在……
 *
 * 倒放状态下，点击停止或播放结束，定位在末尾。
 * 倒放状态下，使用单曲播放模式时，存在一个BUG：不能在播放结束后定位到末尾
 *
 * 在Windows系统下，均衡器的频率范围只有60~16000
 * 在Linux/Mac/Android/iOS系统下（如果有移植意向的话……），均衡器的频率范围 0Hz~(音频采样率的一半)Hz
 * （此程序曾移植到Linux下，无法正常使用……）
 * （错误：文件格式不支持……）
 */

ShadowPlayer::ShadowPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShadowPlayer)
{
    ui->setupUi(this);
    //this->setFixedSize(this->width(), this->height());//锁定窗口大小

    player = new Player();//播放功能封装
    lyrics = new Lyrics();//歌词功能封装
    playList = new PlayList(player, ui->playerListArea);
    osd = new OSD();
    miniUi = new miniForm(0,player);
    timer = new QTimer(this);//定时器
    lrcTimer = new QTimer(this);//歌词显示定时器

    lb = new LrcBar(lyrics, player, 0);//传递对象指针以便访问
    curMonitor = 0;
    playing = false;
    lyrics->lrcOffset = 0;//当前歌词时间偏移量（ms）
    this->setWindowIcon(QIcon(":icon/ICO/ShadowPlayer.ico"));//设置窗口图标
    if (!QFileInfo(QCoreApplication::applicationDirPath() + "/Stream.mod").exists()) {
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);//无边框
        this->setAttribute(Qt::WA_TranslucentBackground, true);//背景透明
    }
    ui->coverLabel->setScaledContents(true);//自动缩放内容
    ui->coverLabel->setPixmap(QPixmap(":image/image/ShadowPlayer.png"));

    //阴影标签相关设置
    ui->tagLabel->setShadowMode(1);
    ui->mediaInfoLabel->setShadowMode(1);
    ui->tagLabel->setShadowColor(QColor(0, 0, 0, 80));
    ui->mediaInfoLabel->setShadowColor(QColor(0, 0, 0, 80));
    ui->curTimeLabel->setShadowMode(1);
    ui->totalTimeLabel->setShadowMode(1);
    ui->curTimeLabel->setShadowColor(QColor(0, 0, 0, 80));
    ui->totalTimeLabel->setShadowColor(QColor(0, 0, 0, 80));

    player->devInit();

    //信号与槽的关联
    connect(timer,SIGNAL(timeout()),this,SLOT(UpdateTime()));
    connect(lrcTimer,SIGNAL(timeout()),this,SLOT(UpdateLrc()));
    miniForm * miniUiPtr = miniUi; //以下为mini界面相关
    connect(this, SIGNAL(sendCurTitle(QString)), miniUiPtr, SLOT(refreshTitle(QString)));
    connect(miniUiPtr, SIGNAL(on_playBtn_clicked()), this, SLOT(on_playButton_clicked()));
    connect(miniUiPtr, SIGNAL(on_playNextBtn_clicked()), this, SLOT(on_playNextButton_clicked()));
    connect(miniUiPtr, SIGNAL(on_playPrevBtn_clicked()), this, SLOT(on_playPreButton_clicked()));
    connect(miniUiPtr, SIGNAL(on_stopBtn_clicked()), this, SLOT(on_stopButton_clicked()));
    connect(miniUiPtr, SIGNAL(on_muteBtn_clicked()), this, SLOT(on_muteButton_clicked()));
    connect(miniUiPtr, SIGNAL(showMainPlayer(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));
    connect(this, SIGNAL(hideMiniFrom()), miniUiPtr, SLOT(hideMiniUi()));
    connect(ui->playSlider, SIGNAL(valueChanged(int)), miniUiPtr, SLOT(setSliderValue(int)));
    connect(miniUiPtr, SIGNAL(nowPlayValue(int)), ui->playSlider, SLOT(setValue(int)));

    //均衡器
    connect(ui->eqSlider_1, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));
    connect(ui->eqSlider_2, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));
    connect(ui->eqSlider_3, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));
    connect(ui->eqSlider_4, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));
    connect(ui->eqSlider_5, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));
    connect(ui->eqSlider_6, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));
    connect(ui->eqSlider_7, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));
    connect(ui->eqSlider_8, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));
    connect(ui->eqSlider_9, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));
    connect(ui->eqSlider_10, SIGNAL(valueChanged(int)), this, SLOT(applyEQ()));

    connect(playList, SIGNAL(callPlayer()), this, SLOT(callFromPlayList()));

    MyGlobalShortCut *playShortcut = new MyGlobalShortCut("Ctrl+F2", this);
    connect(playShortcut,SIGNAL(activated()), this,SLOT(on_playButton_clicked()));//播放键热键
    MyGlobalShortCut *stopShortcut = new MyGlobalShortCut("Ctrl+F3", this);
    connect(stopShortcut,SIGNAL(activated()), this,SLOT(on_stopButton_clicked()));//停止键热键
    MyGlobalShortCut *muteShortcut = new MyGlobalShortCut("Ctrl+F4", this);
    connect(muteShortcut,SIGNAL(activated()), this,SLOT(on_muteButton_clicked()));//静音热键
    MyGlobalShortCut *preShortcut = new MyGlobalShortCut("Ctrl+F5", this);
    connect(preShortcut,SIGNAL(activated()), this,SLOT(on_playPreButton_clicked()));//上一曲热键
    MyGlobalShortCut *nextShortcut = new MyGlobalShortCut("Ctrl+F6", this);
    connect(nextShortcut,SIGNAL(activated()), this,SLOT(on_playNextButton_clicked()));//下一曲热键
    //Media Keys(键盘上的多媒体键)
    MyGlobalShortCut *mplayShortcut = new MyGlobalShortCut("Media Play", this);
    connect(mplayShortcut,SIGNAL(activated()), this,SLOT(on_playButton_clicked()));//播放键热键
    MyGlobalShortCut *mmuteShortcut = new MyGlobalShortCut("Volume Mute", this);
    connect(mmuteShortcut,SIGNAL(activated()), this,SLOT(on_muteButton_clicked()));//静音热键
    MyGlobalShortCut *mpreShortcut = new MyGlobalShortCut("Media Previous", this);
    connect(mpreShortcut,SIGNAL(activated()), this,SLOT(on_playPreButton_clicked()));//上一曲热键
    MyGlobalShortCut *mnextShortcut = new MyGlobalShortCut("Media Next", this);
    connect(mnextShortcut,SIGNAL(activated()), this,SLOT(on_playNextButton_clicked()));//下一曲热键

    skinMode = 2; //皮肤模式 0.不更改大小 1.左侧 2.全窗口 3.自动 4.动态缩放
    skinPos = 1;//背景图片位置 0.显示顶端 1.显示中间 2.显示底部
    skinDrawPos = 0;//绘制背景图片时，使用的百分比位置 0 = 顶部 1 = 底部
    aspectRatio = 0;//图片宽高比，用于动态缩放

    playMode = 2;//播放模式 0.单曲播放 1.单曲循环 2.顺序播放 3.列表循环 4.随机播放
    playlistMode = false;////播放列表使用的模式 true.61模式 false.bl模式
    isReverse = false;//默认不倒放

    nowPlaying = "暂时没有播放任何文件哦";//播放列表bl使用模式，ab循环保存loop文件时也用得到
    nowPlayingPath = "暂时没有播放任何文件哦";//记录 当前播放的文件的路径 和 文件所在文件夹的路径

    clickOnFrame = false;//是否点击到窗体（面板）上，用于解决点击控件后窗口瞬移的BUG
    clickOnLeft = false;

    isFromPlayListFlag = false;//初始化为非，不要在除loadFile或formPlayList外的函数中使用

    bPointSeting = false;//设置ab循环按钮第一次按下应该设置a点
    autoLoadLoop = false; //是否启用自动载入循环功能，根据配置功能决定，默认false
    player->removeJumpPoint();//启动时默认为不在循环状态

    isMute = false;//是否静音
    isPlaySliderPress = false;

    timer->start(27);//定时器太慢会触发进度条setValue的BUG
    lrcTimer->start(70);

    setAcceptDrops(true);//允许拖放
    loadSkin(":/image/image/Skin1.jpg", false);//应用默认皮肤
    ui->playerListArea->setGeometry(QRect(370, 200, 331, 0));//将播放列表放在默认位置

    //背景渐变
    bgLinearGradient.setColorAt(0, QColor(255, 255, 255, 0));
    bgLinearGradient.setColorAt(1, QColor(255, 255, 255, 200));//255, 255, 255, 255
    bgLinearGradient.setStart(0, 0);
    bgLinearGradient.setFinalStop(0, height());

    //NT6特色

    //任务栏进度条初始化
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(windowHandle());
    taskbarProgress = taskbarButton->progress();
    taskbarProgress->setRange(0, 1000);
    connect(ui->playSlider, SIGNAL(valueChanged(int)), taskbarProgress, SLOT(setValue(int)));

    //任务栏缩略图按钮
    thumbnailToolBar = new QWinThumbnailToolBar(this);
    playToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    stopToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    backwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    forwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    playToolButton->setToolTip("播放");
    playToolButton->setIcon(QIcon(":/icon/ICO/Play.png"));
    stopToolButton->setToolTip("停止");
    stopToolButton->setIcon(QIcon(":/icon/ICO/Stop.png"));
    backwardToolButton->setToolTip("上一曲");
    backwardToolButton->setIcon(QIcon(":/icon/ICO/Pre.png"));
    forwardToolButton->setToolTip("下一曲");
    forwardToolButton->setIcon(QIcon(":/icon/ICO/Next.png"));
    thumbnailToolBar->addButton(playToolButton);
    thumbnailToolBar->addButton(stopToolButton);
    thumbnailToolBar->addButton(backwardToolButton);
    thumbnailToolBar->addButton(forwardToolButton);
    connect(playToolButton, SIGNAL(clicked()), this, SLOT(on_playButton_clicked()));
    connect(stopToolButton, SIGNAL(clicked()), this, SLOT(on_stopButton_clicked()));
    connect(backwardToolButton, SIGNAL(clicked()), this, SLOT(on_playPreButton_clicked()));
    connect(forwardToolButton, SIGNAL(clicked()), this, SLOT(on_playNextButton_clicked()));

    //载入设置
    loadConfig();
    loadSkinData();

    //初始化动画

    //窗口展开收缩动画
    sizeSlideAnimation = new QPropertyAnimation(this, "geometry");
    sizeSlideAnimation->setDuration(700);
    sizeSlideAnimation->setEasingCurve(QEasingCurve::OutCirc);

    //载入文件时，三个标签的动画
    tagAnimation = new QPropertyAnimation(ui->tagLabel, "geometry");
    tagAnimation->setDuration(700);
    tagAnimation->setStartValue(QRect(130, 30, 0, 16));
    tagAnimation->setEndValue(QRect(130, 30, 221, 16));
    mediaInfoAnimation = new QPropertyAnimation(ui->mediaInfoLabel, "geometry");
    mediaInfoAnimation->setDuration(800);
    mediaInfoAnimation->setStartValue(QRect(130, 50, 0, 16));
    mediaInfoAnimation->setEndValue(QRect(130, 50, 221, 16));
    coverAnimation = new QPropertyAnimation(ui->coverLabel, "geometry");
    coverAnimation->setEasingCurve(QEasingCurve::OutCirc);
    coverAnimation->setDuration(600);
    coverAnimation->setStartValue(QRect(60, 60, 1, 1));
    coverAnimation->setEndValue(QRect(10, 10, 111, 111));

    //播放列表相关
    //隐藏均衡器
    eqHideAnimation = new QPropertyAnimation(ui->eqGroupBox, "geometry");
    eqHideAnimation->setDuration(600);
    eqHideAnimation->setStartValue(QRect(370, 30, 331, 171));
    eqHideAnimation->setEndValue(QRect(370, 30, 331, 0));

    //显示均衡器
    eqShowAnimation = new QPropertyAnimation(ui->eqGroupBox, "geometry");
    eqShowAnimation->setDuration(600);
    eqShowAnimation->setStartValue(QRect(370, 30, 331, 0));
    eqShowAnimation->setEndValue(QRect(370, 30, 331, 171));

    //隐藏歌词
    lyricsHideAnimation = new QPropertyAnimation(ui->lyricsBox, "geometry");
    lyricsHideAnimation->setDuration(600);
    lyricsHideAnimation->setStartValue(QRect(370, 210, 331, 181));
    lyricsHideAnimation->setEndValue(QRect(370, 391, 331, 0));

    //显示歌词
    lyricsShowAnimation = new QPropertyAnimation(ui->lyricsBox, "geometry");
    lyricsShowAnimation->setDuration(600);
    lyricsShowAnimation->setStartValue(QRect(370, 391, 331, 0));
    lyricsShowAnimation->setEndValue(QRect(370, 210, 331, 181));

    //隐藏播放列表
    playListHideAnimation = new QPropertyAnimation(ui->playerListArea, "geometry");
    playListHideAnimation->setDuration(600);
    playListHideAnimation->setStartValue(QRect(370, 30, 331, 361));
    playListHideAnimation->setEndValue(QRect(370, 205, 331, 0));

    //显示播放列表
    playListShowAnimation = new QPropertyAnimation(ui->playerListArea, "geometry");
    playListShowAnimation->setDuration(600);
    playListShowAnimation->setStartValue(QRect(370, 205, 331, 0));
    playListShowAnimation->setEndValue(QRect(370, 30, 331, 361));

    connect(playListHideAnimation, SIGNAL(finished()), this, SLOT(update()));
    connect(playListShowAnimation, SIGNAL(finished()), this, SLOT(update()));//动画完成后刷新窗口

    //淡出动画，动画结束后程序退出
    fadeOutAnimation = new QPropertyAnimation(this, "windowOpacity");
    fadeOutAnimation->setDuration(400);
    fadeOutAnimation->setStartValue(1);
    fadeOutAnimation->setEndValue(0);
    connect(fadeOutAnimation, SIGNAL(finished()), this, SLOT(close()));

    //淡入窗口
    fadeInAnimation = new QPropertyAnimation(this, "windowOpacity");
    fadeInAnimation->setDuration(400);
    fadeInAnimation->setStartValue(0);
    fadeInAnimation->setEndValue(1);
    fadeInAnimation->start();
    //启用nt6功能
    connect(fadeInAnimation, SIGNAL(finished()), this, SLOT(setTaskbarButtonWindow()));

    //托盘图标部分
    trayicon = new QSystemTrayIcon(this);
    //创建QIcon对象，参数是图标资源，值为项目的资源文件中图标的地址
    QIcon icon(":icon/ICO/ShadowPlayer.ico");
    trayiconMenu = new QMenu(this);
    //为托盘菜单添加菜单项
    trayiconMenu->addAction("显示主窗体" , this, SLOT(showMainFormRequire()));
    trayiconMenu->addSeparator();//分割一下区分上下那俩
    trayiconMenu->addAction("退出啊喵~" , this, SLOT(exitQAppFromTrayIcon()));
    //将创建的QIcon对象作为系统托盘图标
    trayicon->setIcon(icon);
    //设置系统托盘提示
    trayicon->setToolTip(tr("Shadow Player(BLumia分支)"));
    //将创建菜单作为系统托盘菜单
    trayicon->setContextMenu(trayiconMenu);
    //为系统托盘绑定单击信号的槽 即图标激活时
    connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));   
}

ShadowPlayer::~ShadowPlayer()
{
    saveConfig();
    delete ui;
    delete lb;
    delete player;
    delete timer;
    delete lyrics;
    delete playList;
    delete osd;
    delete miniUi;
    delete sizeSlideAnimation;
    delete fadeInAnimation;
    delete tagAnimation;
    delete mediaInfoAnimation;
    delete coverAnimation;
    delete fadeOutAnimation;
    delete eqHideAnimation;
    delete eqShowAnimation;
    delete lyricsHideAnimation;
    delete lyricsShowAnimation;
    delete playListHideAnimation;
    delete playListShowAnimation;
    delete trayicon;
    /*delete thumbnailToolBar;
    delete playToolButton;
    delete stopToolButton;
    delete backwardToolButton;
    delete forwardToolButton;*/
}

void ShadowPlayer::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void ShadowPlayer::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty())
        return;

    if(fileName.toLower().endsWith(".jpg")||
            fileName.toLower().endsWith(".jpeg")||
            fileName.toLower().endsWith(".png")||
            fileName.toLower().endsWith(".gif")||
            fileName.toLower().endsWith(".bmp"))
    {
        loadSkin(fileName);
    } else if (fileName.toLower().endsWith(".lrc")) {
        lyrics->resolve(fileName, true);
    } else {
        addToListAndPlay(urls);
    }
}

void ShadowPlayer::paintEvent(QPaintEvent *)
{
    //覆盖绘图函数绘制背景图片
    QPainter painter(this);

    //如果存在背景图片
    if (!skin.isNull())
    {

        int topY = 0;//图片顶部坐标

        switch (skinPos) {
        case 0:
            //显示顶部
            skinDrawPos = 0;
            break;
        case 1:
            //图片居中
            skinDrawPos = 0.5;
            break;
        case 2:
            //显示底部
            skinDrawPos = 1;
            break;
        default:
            break;
        }

        //绘制图片
        switch (skinMode) {
        case 0:
            //原始大小
            topY = -(skin.height() - 400) * skinDrawPos;
            painter.drawPixmap(0, topY, skin);
            break;
        case 1:
            //左侧宽度
            topY = -(skinLeft.height() - 400) * skinDrawPos;
            painter.drawPixmap(0, topY, skinLeft);
            break;
        case 2:
            //全窗口宽度
            topY = -(skinFull.height() - 400) * skinDrawPos;
            painter.drawPixmap(0, topY, skinFull);
            break;
        case 3:
            //自动缩放
            if (this->geometry().width() > 361)
            {
                topY = -(skinFull.height() - 400) * skinDrawPos;
                painter.drawPixmap(0, topY, skinFull);
            } else {
                topY = -(skinLeft.height() - 400) * skinDrawPos;
                painter.drawPixmap(0, topY, skinLeft);
            }
            break;
        case 4:
            //动态缩放
            if (this->geometry().width() <= 360) //若窗口为最小，绘制高质量小图
            {
                topY = -(skinLeft.height() - 400) * skinDrawPos;
                painter.drawPixmap(0, topY, skinLeft);
            } else if (this->geometry().width() >= 710) { //若窗口为最大，绘制高质量大图
                topY = -(skinFull.height() - 400) * skinDrawPos;
                painter.drawPixmap(0, topY, skinFull);
            } else { //其余情况
                topY = -(this->width()*aspectRatio - 400) * skinDrawPos; //根据宽高比比来计算位置
                painter.drawPixmap(0, topY, this->width(), this->width()*aspectRatio, skin); //保持宽高比绘制
            }
            break;
        default:
            break;
        }
    }

    //绘制背景渐变
    painter.setBrush(QBrush(bgLinearGradient));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width(), height());
}

//右键菜单
void ShadowPlayer::contextMenuEvent(QContextMenuEvent *)
{
    QCursor cur=this->cursor();

    QAction textAction1("拖动窗口左侧可以精确调节位置", this);
    textAction1.setEnabled(false);

    QMenu menu;
    menu.addAction("载入默认皮肤" , this, SLOT(loadDefaultSkin()));
    menu.addSeparator();
    menu.addAction("适配皮肤到左窗口（适合较窄图片）", this, SLOT(fixSkinSizeLeft()));
    menu.addAction("适配皮肤到全窗口（适合较宽图片）", this, SLOT(fixSkinSizeFull()));
    menu.addAction("不更改皮肤大小", this, SLOT(originalSkinSize()));
    menu.addAction("根据窗口大小自动调整皮肤", this, SLOT(autoSkinSize()));
    menu.addAction("动态缩放皮肤", this, SLOT(dynamicSkinSize()));
    menu.addSeparator();
    menu.addAction("背景图顶部显示", this, SLOT(skinOnTop()));
    menu.addAction("背景图居中显示", this, SLOT(skinOnCenter()));
    menu.addAction("背景图底部显示", this, SLOT(skinOnButtom()));
    menu.addAction(&textAction1);
    menu.addSeparator();
    menu.addAction("不使用皮肤（优化性能）", this, SLOT(skinDisable()));
    menu.addSeparator();
    menu.addAction("设置物理参数（毫无人性）", this, SLOT(physicsSetting()));
    menu.addAction("载入预设 - 物理版频谱", this, SLOT(enableFFTPhysics()));
    menu.addAction("载入预设 - 正常版频谱", this, SLOT(disableFFTPhysics()));
    menu.addSeparator();
    menu.addAction("循环自动载入功能（开启或关闭）", this, SLOT(autoLoadLoopCfg()));
    menu.addAction("播放器列表模式（经典或杀马特）", this, SLOT(playlistModeCfg()));
    menu.addSeparator();
    menu.addAction("关于作者", this, SLOT(showDeveloperInfo()));
    menu.exec(cur.pos());
}

//载入默认背景
void ShadowPlayer::loadDefaultSkin()
{
    loadSkin(":/image/image/Skin1.jpg", false);
    QFile skinFile(QCoreApplication::applicationDirPath() + "/skin.dat");
    skinFile.remove();
}

//更改皮肤模式的实现
void ShadowPlayer::fixSkinSizeLeft()
{
    skinMode = 1;
    this->repaint();//使用update函数无效果，原因不明，改用repaint
}

void ShadowPlayer::fixSkinSizeFull()
{
    skinMode = 2;
    this->repaint();
}

void ShadowPlayer::originalSkinSize()
{
    skinMode = 0;
    this->repaint();
}

void ShadowPlayer::autoSkinSize()
{
    skinMode = 3;
    this->repaint();
}

void ShadowPlayer::dynamicSkinSize()
{
    skinMode = 4;
    this->repaint();
}

void ShadowPlayer::skinOnTop()
{
    skinPos = 0;
    this->repaint();
}

void ShadowPlayer::skinOnCenter()
{
    skinPos = 1;
    this->repaint();
}

void ShadowPlayer::skinOnButtom()
{
    skinPos = 2;
    this->repaint();
}

//禁用皮肤
void ShadowPlayer::skinDisable()
{
    skin = QPixmap();
    skinLeft = skin;
    skinFull = skin;
    this->repaint();
}

void ShadowPlayer::autoLoadLoopCfg()
{
    QString temp = autoLoadLoop ? "启用" : "关闭";
            switch(QMessageBox::question(NULL, "是否启用从loop文件自动载入AB循环数据？", "当前状态：" + temp +
                                         "。\n你可以点击Yes启用或通过点击No关闭此功能。",
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
    {
    case QMessageBox::Yes:
        autoLoadLoop = true;
        QMessageBox::information(0, "成功启用", "您刚刚启用了自动载入循环数据功能.");
        break;
    case QMessageBox::No:
        autoLoadLoop = false;
        QMessageBox::information(0, "成功取消", "您刚刚关闭了自动载入循环数据功能.");
        break;
    default :
        autoLoadLoop = false;
        QMessageBox::information(0, "诶？", "不知道刚刚发生了什么，总之关闭自动载入功能了.");
        break;
    }
}

void ShadowPlayer::playlistModeCfg()
{
    QString temp = playlistMode ? "经典模式" : "杀马特模式";
    switch(QMessageBox::question(NULL, "想要变更播放器播放列表模式？", "当前模式：" + temp +
                                 "。\n经典模式即为任意播放一个音频都会将其添加到播放列表，百度音乐等采用的就是这个模式。" +
                                 "。\n杀马特模式即为播放时根据音频文件所在的文件夹导入文件夹内的所有文件，WMP等采用的就是这个模式。",
                                 "我采用 经典模式" , "我采用 杀马特模式", 0 , 1))
    {
    case 0:
        playlistMode = true;
        QMessageBox::information(0, "成功采用 经典模式", "您刚刚采用了 经典模式.");
        break;
    case 1:
        playlistMode = false;
        QMessageBox::information(0, "成功采用 杀马特模式", "您刚刚采用了 杀马特模式.");
        break;
    default :
        playlistMode = true;
        QMessageBox::information(0, "诶？", "不知道刚刚发生了什么，总之采用 经典模式 了.");
        break;
    }
}

//播放界面三个标签的动画效果
void ShadowPlayer::infoLabelAnimation()
{
    tagAnimation->stop();
    mediaInfoAnimation->stop();
    coverAnimation->stop();

    tagAnimation->start();
    mediaInfoAnimation->start();
    coverAnimation->start();
    this->update();//刷新窗口
}

void ShadowPlayer::loadFile(QString file)
{
    //载入文件
    if (player->openFile(file) != "err")
    {
        QFileInfo fileinfo(file);

        //调整播放列表
        if (!isFromPlayListFlag)
            playList->setPlayListCombo(0);//如果载入的文件不是来自播放列表则设置列表到常规列表
        isFromPlayListFlag = false;
        //专辑封面部分
        using namespace spID3;
        using namespace spFLAC;
        QFile(QCoreApplication::applicationDirPath() + "/cover").remove();//先删除专辑封面文件
        /*
        if(!spID3::extractPicture(file.toLocal8Bit().data(), QString(QCoreApplication::applicationDirPath() + "/cover").toStdString().c_str()))
            spFLAC::extractPicture(file.toLocal8Bit().data(), QString(QCoreApplication::applicationDirPath() + "/cover").toStdString().c_str());//释放出专辑封面文件
        showCoverPic(fileinfo.path());//显示专辑封面
        */
        showCoverPic(file);//显示专辑封面
        QFile(QCoreApplication::applicationDirPath() + "/cover").remove();//删除专辑封面文件

        //清除ab循环
        jumpingFrom = jumpingTo = 0;
        bPointSeting = false;//这个也得清理掉，以免设置a点后自动下一曲，点循环会抽掉。
        player->removeJumpPoint();
        ui->setAbPointBtn->setIcon(QIcon(":/icon/ICO/Loop.png"));

        if (autoLoadLoop)   //检查并加载ab循环点
            loadAbPointFile(fileinfo.path() + "/" + fileinfo.completeBaseName());

        //this->setWindowTitle("ShadowPlayer - " + fileinfo.fileName());
        ui->mediaInfoLabel->setText(player->getNowPlayInfo());
        ui->totalTimeLabel->setText(player->getTotalTime());
        oriFreq = player->getFreq();//存储初始采样率
        //ui->freqSlider->setSliderPosition(0);//恢复采样率设置条默认设置
        on_freqSlider_valueChanged(ui->freqSlider->value());//设置采样率
        player->setVol(ui->volSlider->value());//设置音量
        applyEQ();//设置均衡器

        //设置倒放
        if (isReverse)
            player->setReverse(true);
        else
            player->setReverse(false);

        //设置均衡器
        on_eqEnableCheckBox_clicked(ui->eqEnableCheckBox->isChecked());

        //更新混响参数
        player->updateReverb(ui->reverbDial->value());

        //ab循环和一部分数据更新
        jumpingFrom = jumpingTo = 0; // 清除跳点存储值
        nowPlaying = fileinfo.filePath();// 当前播放的文件的路径（含文件名）
        nowPlayingPath = fileinfo.path();// 当前播放的文件所在文件夹的路径

        //----------设置播放按钮状态&启动播放
        player->play();//启动播放
        if (player->isPlaying())//检测播放状态
        {
            playing = true;
            ui->playButton->setIcon(QIcon(":/icon/ICO/Pause.png"));
            ui->playButton->setToolTip("暂停（Ctrl+F2）");
            taskbarProgress->show();
            taskbarProgress->resume();
            taskbarButton->setOverlayIcon(QIcon(":/icon/ICO/Play.png"));
            playToolButton->setIcon(QIcon(":/icon/ICO/Pause.png"));
            playToolButton->setToolTip("暂停");
        }
        //----------结束设置播放按钮&启动播放

        /*
        playing = false;//设置状态以便下一步播放
        on_playButton_clicked();//点击播放按钮，开始播放
        */

        if (!lyrics->resolve(file))//载入文件目录下的歌词文件
            if(!lyrics->loadFromLrcDir(file))//失败则载入程序目录下的歌词
                if(!lyrics->loadFromFileRelativePath(file, "/Lyrics/"))//失败则载入文件目录下子歌词目录的歌词
                    lyrics->loadFromFileRelativePath(file, "/../Lyrics/");//新版百度音乐的路径

        if (player->getTags() == "Show_File_Name")//Show_File_Name = 要显示文件名
            ui->tagLabel->setText(fileinfo.fileName());
        else
            ui->tagLabel->setText(player->getTags());

        emit sendCurTitle(ui->tagLabel->text());
        infoLabelAnimation();//使用动画效果
        if (!miniUi->isVisible())
            osd->showOSD(ui->tagLabel->text(), player->getTotalTime());
    }
}

void ShadowPlayer::loadSkin(QString image, bool save)
{
    //载入皮肤，自动预存3种尺寸
    skin = QPixmap(image);
    skinLeft = skin.scaledToWidth(360, Qt::SmoothTransformation);
    skinFull = skin.scaledToWidth(710, Qt::SmoothTransformation);
    aspectRatio = (double)skin.height() / skin.width();
    if (save)
        saveSkinData();//保存皮肤
    this->update();//重绘界面
}

void ShadowPlayer::UpdateTime()
{
    //Timer周期
    //音量计更新
    ui->leftLevel->setValue(LOWORD(player->getLevel()));
    ui->rightLevel->setValue(HIWORD(player->getLevel()));
    ui->leftLevel->update();//不显示文字进度时，不会立即重绘，故手动重绘
    ui->rightLevel->update();

    //计算对数音量
    //公式：dB=20log(X/V0)
    //最大音量：20log(32768/32768)=20log(1)=0dB
    //最小音量：20log(0) = 20(-∞) ……
    //最小音量此处以-60dB截止（参考foobar2000

    //后来参考Audition发现公式有误……
    //未修改，去掉20即可（音量计较短……还是不修改比较好）
    double ldB = 20*log((double)ui->leftLevel->value()/32768);
    double rdB = 20*log((double)ui->rightLevel->value()/32768);
    if (ldB < -60)
        ldB = -60;
    if (rdB < -60)
        rdB = -60;
    ui->leftdB->setValue(ldB);
    ui->rightdB->setValue(rdB);
    ui->leftdB->update();
    ui->rightdB->update();

    if (skinPos == 3)
        this->update();

    ui->curTimeLabel->setText(player->getCurTime());
    if (isPlaySliderPress == false)//当进度条按下时，不自动滚动
        ui->playSlider->setSliderPosition(player->getPos());

    this->UpdateFFT();

    //播放结束后相关操作
    if (!player->isPlaying())
    {
        switch (playMode) {
        case 0:
            //单曲播放
            //倒放模式会有BUG
            playing = false;
            ui->playButton->setIcon(QIcon(":/icon/ICO/Play.png"));
            ui->playButton->setToolTip("播放（Ctrl+F2）");//停止播放
            taskbarProgress->hide();
            taskbarButton->setOverlayIcon(QIcon(":/icon/ICO/Stop.png"));
            playToolButton->setIcon(QIcon(":/icon/ICO/Play.png"));
            playToolButton->setToolTip("播放");
            break;
        case 1:
            //单曲循环
            if (playing)
            {
                //如果没有暂停、停止
                player->stop();
                player->play();
                //再次播放
            }
            break;
        case 2:
            //顺序播放
            if (playing)
            {
                QString nextFile = playList->next(false);//跳至下一曲
                if (nextFile == "stop")//如果已经没有下一曲
                {
                    playing = false;
                    ui->playButton->setIcon(QIcon(":/icon/ICO/Play.png"));
                    ui->playButton->setToolTip("播放（Ctrl+F2）");//停止播放
                    taskbarProgress->hide();
                    taskbarButton->setOverlayIcon(QIcon(":/icon/ICO/Stop.png"));
                    playToolButton->setIcon(QIcon(":/icon/ICO/Play.png"));
                    playToolButton->setToolTip("播放");
                } else {
                    loadFile(nextFile);//如果有，继续播放
                }
            }
            break;
        case 3:
            //列表循环
            if (playing)
            {
                loadFile(playList->next(true));
            }
            break;
        case 4:
            //随机播放
            if (playing)
            {
                QTime time;
                time = QTime::currentTime();
                qsrand(time.msec() + time.second() * 1000);
                int index = qrand() % playList->getLength();
                //随机数
                loadFile(playList->playIndex(index));
            }
        default:
            break;
        }
    }
}

void ShadowPlayer::UpdateLrc()
{
    //刷新歌词时间
    lyrics->updateTime(player->getCurTimeMS()+lyrics->lrcOffset, player->getTotalTimeMS());
    double pos = 0;
    double curTimePos = lyrics->getTimePos(player->getCurTimeMS()+lyrics->lrcOffset);
    //改变歌词文本
    ui->lrcLabel_1->setText(lyrics->getLrcString(-3));
    ui->lrcLabel_2->setText(lyrics->getLrcString(-2));
    ui->lrcLabel_3->setText(lyrics->getLrcString(-1));
    ui->lrcLabel_4->setText(lyrics->getLrcString(0));
    ui->lrcLabel_5->setText(lyrics->getLrcString(1));
    ui->lrcLabel_6->setText(lyrics->getLrcString(2));
    ui->lrcLabel_7->setText(lyrics->getLrcString(3));

    ui->lrcLabel_1->setToolTip(ui->lrcLabel_1->text());
    ui->lrcLabel_2->setToolTip(ui->lrcLabel_2->text());
    ui->lrcLabel_3->setToolTip(ui->lrcLabel_3->text());
    ui->lrcLabel_4->setToolTip(ui->lrcLabel_4->text());
    ui->lrcLabel_5->setToolTip(ui->lrcLabel_5->text());
    ui->lrcLabel_6->setToolTip(ui->lrcLabel_6->text());
    ui->lrcLabel_7->setToolTip(ui->lrcLabel_7->text());

    //根据歌词位置，滚动歌词
    if (curTimePos >= 0.2 && curTimePos <= 0.8)
    {
        pos = 0.5;
    } else if (curTimePos < 0.2) {
        pos = curTimePos * 2.5;//0~0.5
    } else if (curTimePos > 0.8) {
        pos = (curTimePos - 0.8) * 2.5 + 0.5;//0.5~1
    }
    ui->lrcLabel_1->setGeometry(10, 35 - 20 * pos, 311, 16);
    //ui->lrcLabel_1->setStyleSheet(QString("color: rgba(0, 0, 0, %1)").arg(245 - 235 * curTimePos));
    ui->lrcLabel_2->setGeometry(10, 55 - 20 * pos, 311, 16);
    ui->lrcLabel_3->setGeometry(10, 75 - 20 * pos, 311, 16);
    ui->lrcLabel_4->setGeometry(10, 95 - 20 * pos, 311, 16);
    ui->lrcLabel_5->setGeometry(10, 115 - 20 * pos, 311, 16);
    ui->lrcLabel_6->setGeometry(10, 135 - 20 * pos, 311, 16);
    ui->lrcLabel_7->setGeometry(10, 155 - 20 * pos, 311, 16);
    //ui->lrcLabel_7->setStyleSheet(QString("color: rgba(0, 0, 0, %1)").arg(235 * curTimePos + 10));
}

void ShadowPlayer::showCoverPic(QString filePath){

    QFileInfo fileinfo(filePath);
    QString path = fileinfo.path();

    QFileInfo mapIDInfo(path);
    QString maptitle = mapIDInfo.baseName();
    char mapid[7];
    sscanf(maptitle.toStdString().c_str(), "%s", mapid);
    //QMessageBox::information(0, "mapid", maptitle+" "+mapid);
    /*
    if (QFileInfo(QCoreApplication::applicationDirPath() + "/cover").exists())
        ui->coverLabel->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/cover"));
    */
    if (spID3::loadPictureData(filePath.toLocal8Bit().data()))
    {
        QByteArray picData((const char*)spID3::getPictureDataPtr(), spID3::getPictureLength());
        ui->coverLabel->setPixmap(QPixmap::fromImage(QImage::fromData(picData)));
        spID3::freePictureData();
    } else if (spFLAC::loadPictureData(filePath.toLocal8Bit().data()))
    {
        QByteArray picData((const char*)spFLAC::getPictureDataPtr(), spFLAC::getPictureLength());
        ui->coverLabel->setPixmap(QPixmap::fromImage(QImage::fromData(picData)));
        spFLAC::freePictureData();
    }
    else if (QFileInfo(path + "/cover.jpg").exists())
        ui->coverLabel->setPixmap(QPixmap(path + "/cover.jpg"));
    else if (QFileInfo(path + "/cover.jpeg").exists())
        ui->coverLabel->setPixmap(QPixmap(path + "/cover.jpeg"));
    else if (QFileInfo(path + "/cover.png").exists())
        ui->coverLabel->setPixmap(QPixmap(path + "/cover.png"));
    else if (QFileInfo(path + "/cover.gif").exists())
        ui->coverLabel->setPixmap(QPixmap(path + "/cover.gif"));
    else if (QFileInfo(path + "/bg.jpg").exists())        //osu! simple support solution.
        ui->coverLabel->setPixmap(QPixmap(path + "/bg.jpg"));
    else if (QFileInfo(path + "/../../Data/bt/"+mapid+".jpg").exists())//osu! support solution.
        ui->coverLabel->setPixmap(QPixmap(path + "/../../Data/bt/"+mapid+".jpg"));
    else
        ui->coverLabel->setPixmap(QPixmap(":image/image/ShadowPlayer.png"));
}

void ShadowPlayer::loadAbPointFile(QString path){
    if (QFileInfo(path + ".loop").exists()){ //上面太长了所以把扩展名写这里
        //读取文件并设置ab循环点
        QFile abfile(path + ".loop");
        if (!abfile.open(QIODevice::ReadOnly|QIODevice::Text)) {
            return;//打开loop文件失败（歌词不存在，歌词文件被独占）
        }
        QTextStream infile(&abfile);
        QString twoPoint = QString(infile.readAll());
        abfile.close();
        QStringList lines = twoPoint.split("\n");
        jumpingFrom = lines.at(0).toDouble();
        jumpingTo = lines.at(1).toDouble();
        if ((jumpingFrom==0)&&(jumpingTo==0))
            ui->setAbPointBtn->setIcon(QIcon(":/icon/ICO/Loop.png"));
        else {
        player->setJumpPoint(jumpingFrom, jumpingTo);
        ui->setAbPointBtn->setIcon(QIcon(":/icon/ICO/LoopAB.png"));
        }
    }
    else
        ui->setAbPointBtn->setIcon(QIcon(":/icon/ICO/Loop.png"));
}

void ShadowPlayer::on_openButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, QString::fromUtf8("打开"),0,QString::fromUtf8("音频文件 (*.mp3 *.mp2 *.mp1 *.wav *.aiff *.ogg *.ape *.mp4 *.m4a *.m4v *.aac *.alac *.tta *.flac *.wma *.wv)"));
    int newIndex = playList->getLength();
    int length = files.length();
    if (!files.isEmpty())
    {
        for (int i = 0 ;i < length; i++)
        {
            playList->add(files[i]);
        }
        if (playList->getLength() > newIndex) //如果添加了文件
        {
            loadFile(playList->playIndex(newIndex));//上次的列表长度就是此次播放的索引
        }
    }
}

void ShadowPlayer::on_playButton_clicked()
{
    if (!playing)
    {
        player->play();//启动播放

        if (player->isPlaying())//检测播放状态
        {
            playing = true;
            ui->playButton->setIcon(QIcon(":/icon/ICO/Pause.png"));
            ui->playButton->setToolTip("暂停（Ctrl+F2）");
            taskbarProgress->show();
            taskbarProgress->resume();
            taskbarButton->setOverlayIcon(QIcon(":/icon/ICO/Play.png"));
            playToolButton->setIcon(QIcon(":/icon/ICO/Pause.png"));
            playToolButton->setToolTip("暂停");
        } else {
            //不播放可能是文件没载入，尝试载入
            if(playList->getLength() > 0)
                loadFile(playList->playIndex(playList->getIndex()));
        }
    }
    else
    {
        player->pause();
        playing = false;
        ui->playButton->setIcon(QIcon(":/icon/ICO/Play.png"));
        ui->playButton->setToolTip("播放（Ctrl+F2）");
        taskbarProgress->show();
        taskbarProgress->pause();
        taskbarButton->setOverlayIcon(QIcon(":/icon/ICO/Pause.png"));
        playToolButton->setIcon(QIcon(":/icon/ICO/Play.png"));
        playToolButton->setToolTip("播放");
    }
}

void ShadowPlayer::on_stopButton_clicked()
{
    player->stop();
    playing = false;
    ui->playButton->setToolTip("播放（Ctrl+F2）");
    ui->playButton->setIcon(QIcon(":/icon/ICO/Play.png"));
    taskbarProgress->hide();
    taskbarButton->setOverlayIcon(QIcon(":/icon/ICO/Stop.png"));
    playToolButton->setIcon(QIcon(":/icon/ICO/Play.png"));
    playToolButton->setToolTip("播放");
}

void ShadowPlayer::on_volSlider_valueChanged(int value)
{
    player->setVol(value);
    isMute = false;//解除静音
    ui->muteButton->setIcon(QIcon(":/icon/ICO/Vol.png"));
}


void ShadowPlayer::on_muteButton_clicked()
{
    if (isMute == false)
    {
        //程序有改动，现在setValue即可变更静音状态
        //如果没有静音
        lastVol = ui->volSlider->value();
        ui->volSlider->setValue(0);
        //player->setVol(0);//已无需
        ui->muteButton->setIcon(QIcon(":/icon/ICO/Mute.png"));
        isMute = true;//必须先更改value才能静音，否则自动解除静音
    }
    else
    {
        ui->volSlider->setValue(lastVol);
        //player->setVol(lastVol);//已无需
        ui->muteButton->setIcon(QIcon(":/icon/ICO/Vol.png"));
        isMute = false;//无用代码，setValue已经解除静音
    }
}

float ShadowPlayer::arraySUM(int start, int end, float *array)
{
    float sum = 0;
    for(int i=start; i<=end; i++)
    {
        sum += array[i];
    }
    return sum;
}

void ShadowPlayer::fullZero(int length, float *array)
{
    for(int i = 0; i < length; i++)
    {
        array[i] = 0;
    }
}

void ShadowPlayer::UpdateFFT()
{
    //更新频谱分析（之前）
    //由于2 * x ^ 29 = 2047
    //故x ≈ 1.269
    //起始值 = 2 * pow(1.27,index);
    //终止值 = start * 1.27;

    //现又改为大约50Hz开始
    //为了优化代码……循环
    //x ≈ 1.23048
	
	/*
	  频谱分析（对数）的FFT采样数据终止位置算法
	  例如有1024个样本数据
	  那么每一条包含的采样数据应为：
	  第一条的起点为0
	  从上一条的中点开始，直至【2^((条序号-1)*10/(总条数-1))】的数据
	  将FFT结果数组中此范围的 全部数值相加得到的结果即为对数比例的频谱条高度
	  如果样本数量翻倍，则只需将上述公式中的10加上倍数即可
	  例如：2048个样本数据（本播放器的情况）则将10改为11
	  
	  例：总条数29条，计算第⑨条的长度所需的FFT数据：
	  从2^(7*11/28)+1开始，直到2^(8*11/28)，全部相加
	  （其实这个值应该-1，因为数组的序号是从0开始的）
	*/

    if (player->isPlaying())
    {
        if (ui->leftLevel->value() > 6 || ui->rightLevel->value() > 6)
            player->getFFT(fftData);
        else
            fullZero(2048, fftData);

        double start = pow(2.0, 8*11/(28.0+9)) - 1;
        for (int i = 0; i < 29; i++)
        {
            double end = pow(2.0, (i+9)*11/(28.0+9)) - 1;
            if ((int)end <= (int)start) end = start + 1;
            ui->FFTGroupBox->fftBarValue[i] = sqrt(arraySUM((int)start,(int)end, fftData));
            start = end;
        }

        //限制最大最小值
        ui->FFTGroupBox->cutValue();
        //下滑峰值
        ui->FFTGroupBox->peakSlideDown();
        //重绘
        ui->FFTGroupBox->update();
    } else {
        ui->FFTGroupBox->peakSlideDown();
        ui->FFTGroupBox->update();
    }
}

void ShadowPlayer::on_playSlider_sliderPressed()
{
    isPlaySliderPress = true;
}

void ShadowPlayer::on_playSlider_sliderReleased()
{
    isPlaySliderPress = false;
    player->setPos(ui->playSlider->sliderPosition());
}

void ShadowPlayer::on_resetFreqButton_clicked()
{
    ui->freqSlider->setSliderPosition(0);
    player->setFreq(oriFreq);
}

//设置EQ效果
void ShadowPlayer::applyEQ()
{
    player->setEQ(0, ui->eqSlider_1->value());
    player->setEQ(1, ui->eqSlider_2->value());
    player->setEQ(2, ui->eqSlider_3->value());
    player->setEQ(3, ui->eqSlider_4->value());
    player->setEQ(4, ui->eqSlider_5->value());
    player->setEQ(5, ui->eqSlider_6->value());
    player->setEQ(6, ui->eqSlider_7->value());
    player->setEQ(7, ui->eqSlider_8->value());
    player->setEQ(8, ui->eqSlider_9->value());
    player->setEQ(9, ui->eqSlider_10->value());
}

//窗口拖动相关
void ShadowPlayer::mousePressEvent(QMouseEvent *event)
{
    //如果点击到控件上的话，pos无法取得数值，窗口会瞬移……
    //于是稍作修改
    if (event->button() == Qt::LeftButton && event->x() > 10) //只处理左键+x坐标大于10的情况
    {
        //下一行解决点击控件瞬移BUG
        pos = event->pos();
        clickOnFrame = true;//点击到窗口框架上才会变成true，改动之后新增功能：判断点击是否在边框右侧
        event->accept();
    } else if (event->button() == Qt::LeftButton && event->x() <= 10) {
        clickOnLeft = true;//点击了左侧，开启背景图位置调整
    }

}

void ShadowPlayer::mouseReleaseEvent(QMouseEvent *)
{
    clickOnFrame = false;//弹起鼠标按键时，恢复
    clickOnLeft = false;

    //移动后更新窗体所在屏幕
    QDesktopWidget * deskTop = QApplication::desktop();
    this->curMonitor = deskTop->screenNumber ( this );
}

void ShadowPlayer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && clickOnFrame && event->x() > 10)
    {
        //如果鼠标按住左键在窗口右侧移动，并且点击在窗口上，则移动窗口
        move(event->globalPos() - pos);
        event->accept();
    } else if (event->buttons() & Qt::LeftButton && clickOnLeft && event->y() >= 0 && event->y() <= 400) {
        //如果鼠标点击到左侧小于10像素的区域，并移动，则调整背景图位置
        //已限制调节范围
        skinDrawPos = (double)event->y() / 400; //400：窗口高度
        skinPos = -1;//-1在switch语句中不存在此case
        this->update();
    }
}

//展开窗口右侧部分
void ShadowPlayer::on_extraButton_clicked()
{
    if (this->geometry().width() < 535)
    {
        sizeSlideAnimation->stop();
        sizeSlideAnimation->setStartValue(QRect(this->geometry().x(), this->geometry().y(), 360, 402));
        sizeSlideAnimation->setEndValue(QRect(this->geometry().x() - 175, this->geometry().y(), 710, 400));
        sizeSlideAnimation->start();
        ui->extraButton->setText("←");
    } else {
        sizeSlideAnimation->stop();
        sizeSlideAnimation->setStartValue(QRect(this->geometry().x(), this->geometry().y(), 710, 402));
        sizeSlideAnimation->setEndValue(QRect(this->geometry().x() + 175, this->geometry().y(), 360, 400));
        sizeSlideAnimation->start();
        ui->extraButton->setText("→");
    }
}

void ShadowPlayer::on_closeButton_clicked()
{
    fadeOutAnimation->start();//动画完成之后，程序将退出
    //qApp->quit();//退出
}

void ShadowPlayer::closeEvent(QCloseEvent *)
{
    qApp->exit();//主窗口关闭后，关闭程序
}

void ShadowPlayer::on_setSkinButton_clicked()
{
    QString image = QFileDialog::getOpenFileName(this, QString::fromUtf8("选择皮肤"),0,QString::fromUtf8("图像文件 (*.bmp *.jpg *.jpeg *.png *.gif)"));
    if(!image.isEmpty())
    {
        loadSkin(image);
    }
}

void ShadowPlayer::on_miniSizeButton_clicked()
{
    this->showMinimized();
}

//切换播放模式
void ShadowPlayer::on_playModeButton_clicked()
{
    playMode = ++playMode % 5;//切换模式
    //改了上述语句后编译时总有警告……
    //其实构造函数已经初始化这个变量啦> <
    //这里没有问题哦~
    switch (playMode) {
    case 0:
        ui->playModeButton->setIcon(QIcon(":/icon/ICO/Single.png"));
        ui->playModeButton->setToolTip("单曲播放");
        break;
    case 1:
        ui->playModeButton->setIcon(QIcon(":/icon/ICO/Repeat.png"));
        ui->playModeButton->setToolTip("单曲循环");
        break;
    case 2:
        ui->playModeButton->setIcon(QIcon(":/icon/ICO/Order.png"));
        ui->playModeButton->setToolTip("顺序播放");
        break;
    case 3:
        ui->playModeButton->setIcon(QIcon(":/icon/ICO/AllRepeat.png"));
        ui->playModeButton->setToolTip("列表循环");
        break;
    case 4:
        ui->playModeButton->setIcon(QIcon(":/icon/ICO/Shuffle.png"));
        ui->playModeButton->setToolTip("随机播放");
        break;
    default:
        break;
    }
    QToolTip::showText(QCursor::pos(), ui->playModeButton->toolTip());//立即显示工具提示
}

void ShadowPlayer::on_showDskLrcButton_clicked()
{
    if(lb->isVisible())
        lb->hide();
    else
        lb->show();
}

void ShadowPlayer::on_loadLrcButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, QString::fromUtf8("载入歌词"),0,QString::fromUtf8("LRC歌词 (*.lrc)"));
    if(!file.isEmpty())
        lyrics->resolve(file, true);
}

void ShadowPlayer::on_playSlider_valueChanged(int value)
{
    //防止进度发生变更时，递归触发setPos
    if (qAbs(player->getPos() - value) > 2)
    {
        player->setPos(value);
    }
}

void ShadowPlayer::on_freqSlider_valueChanged(int value)
{
    player->setFreq(oriFreq + (oriFreq * value * 0.0001));
    ui->textLabel1->setText(QString::fromUtf8("回放速度 ") + "(x" + QString::number(value * 0.0001 + 1) + ")");
}

//预设的EQ方案（总觉得用文本文件存储好点……）
void ShadowPlayer::on_eqComboBox_currentIndexChanged(int index)
{
    //只要选择就启用均衡器
    if (!ui->eqEnableCheckBox->isChecked()){
        ui->eqEnableCheckBox->setChecked(true);
        player->eqReady();//初始化均衡器
        //applyEQ(); 应用当前值（这个不必要）
    }

    switch (index) {
    case 0:
        //还原
        ui->eqSlider_1->setSliderPosition(0);
        ui->eqSlider_2->setSliderPosition(0);
        ui->eqSlider_3->setSliderPosition(0);
        ui->eqSlider_4->setSliderPosition(0);
        ui->eqSlider_5->setSliderPosition(0);
        ui->eqSlider_6->setSliderPosition(0);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(0);
        ui->eqSlider_10->setSliderPosition(0);
        applyEQ();
        break;
    case 1:
        //流行
        ui->eqSlider_1->setSliderPosition(3);
        ui->eqSlider_2->setSliderPosition(1);
        ui->eqSlider_3->setSliderPosition(0);
        ui->eqSlider_4->setSliderPosition(-2);
        ui->eqSlider_5->setSliderPosition(-4);
        ui->eqSlider_6->setSliderPosition(-4);
        ui->eqSlider_7->setSliderPosition(-2);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(1);
        ui->eqSlider_10->setSliderPosition(2);
        applyEQ();
        break;
    case 2:
        //摇滚
        ui->eqSlider_1->setSliderPosition(-2);
        ui->eqSlider_2->setSliderPosition(0);
        ui->eqSlider_3->setSliderPosition(2);
        ui->eqSlider_4->setSliderPosition(4);
        ui->eqSlider_5->setSliderPosition(-2);
        ui->eqSlider_6->setSliderPosition(-2);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(4);
        ui->eqSlider_10->setSliderPosition(4);
        applyEQ();
        break;
    case 3:
        //电子
        ui->eqSlider_1->setSliderPosition(-6);
        ui->eqSlider_2->setSliderPosition(1);
        ui->eqSlider_3->setSliderPosition(4);
        ui->eqSlider_4->setSliderPosition(-2);
        ui->eqSlider_5->setSliderPosition(-2);
        ui->eqSlider_6->setSliderPosition(-4);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(6);
        ui->eqSlider_10->setSliderPosition(6);
        applyEQ();
        break;
    case 4:
        //古典
        ui->eqSlider_1->setSliderPosition(0);
        ui->eqSlider_2->setSliderPosition(8);
        ui->eqSlider_3->setSliderPosition(8);
        ui->eqSlider_4->setSliderPosition(4);
        ui->eqSlider_5->setSliderPosition(0);
        ui->eqSlider_6->setSliderPosition(0);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(2);
        ui->eqSlider_10->setSliderPosition(2);
        applyEQ();
        break;
    case 5:
        //金属
        ui->eqSlider_1->setSliderPosition(-6);
        ui->eqSlider_2->setSliderPosition(0);
        ui->eqSlider_3->setSliderPosition(0);
        ui->eqSlider_4->setSliderPosition(0);
        ui->eqSlider_5->setSliderPosition(0);
        ui->eqSlider_6->setSliderPosition(0);
        ui->eqSlider_7->setSliderPosition(4);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(4);
        ui->eqSlider_10->setSliderPosition(0);
        applyEQ();
        break;
    case 6:
        //舞曲
        ui->eqSlider_1->setSliderPosition(-2);
        ui->eqSlider_2->setSliderPosition(3);
        ui->eqSlider_3->setSliderPosition(4);
        ui->eqSlider_4->setSliderPosition(1);
        ui->eqSlider_5->setSliderPosition(-2);
        ui->eqSlider_6->setSliderPosition(-2);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(4);
        ui->eqSlider_10->setSliderPosition(4);
        applyEQ();
        break;
    case 7:
        //乡村
        ui->eqSlider_1->setSliderPosition(-2);
        ui->eqSlider_2->setSliderPosition(0);
        ui->eqSlider_3->setSliderPosition(0);
        ui->eqSlider_4->setSliderPosition(2);
        ui->eqSlider_5->setSliderPosition(2);
        ui->eqSlider_6->setSliderPosition(0);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(4);
        ui->eqSlider_10->setSliderPosition(4);
        applyEQ();
        break;
    case 8:
        //爵士
        ui->eqSlider_1->setSliderPosition(0);
        ui->eqSlider_2->setSliderPosition(0);
        ui->eqSlider_3->setSliderPosition(0);
        ui->eqSlider_4->setSliderPosition(4);
        ui->eqSlider_5->setSliderPosition(4);
        ui->eqSlider_6->setSliderPosition(4);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(2);
        ui->eqSlider_9->setSliderPosition(3);
        ui->eqSlider_10->setSliderPosition(4);
        applyEQ();
        break;
    case 9:
        //布鲁斯
        ui->eqSlider_1->setSliderPosition(-2);
        ui->eqSlider_2->setSliderPosition(0);
        ui->eqSlider_3->setSliderPosition(2);
        ui->eqSlider_4->setSliderPosition(1);
        ui->eqSlider_5->setSliderPosition(0);
        ui->eqSlider_6->setSliderPosition(0);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(-2);
        ui->eqSlider_10->setSliderPosition(-4);
        applyEQ();
        break;
    case 10:
        //怀旧
        ui->eqSlider_1->setSliderPosition(-4);
        ui->eqSlider_2->setSliderPosition(0);
        ui->eqSlider_3->setSliderPosition(2);
        ui->eqSlider_4->setSliderPosition(1);
        ui->eqSlider_5->setSliderPosition(0);
        ui->eqSlider_6->setSliderPosition(0);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(-4);
        ui->eqSlider_10->setSliderPosition(-6);
        applyEQ();
        break;
    case 11:
        //歌剧
        ui->eqSlider_1->setSliderPosition(0);
        ui->eqSlider_2->setSliderPosition(0);
        ui->eqSlider_3->setSliderPosition(0);
        ui->eqSlider_4->setSliderPosition(4);
        ui->eqSlider_5->setSliderPosition(5);
        ui->eqSlider_6->setSliderPosition(3);
        ui->eqSlider_7->setSliderPosition(6);
        ui->eqSlider_8->setSliderPosition(3);
        ui->eqSlider_9->setSliderPosition(0);
        ui->eqSlider_10->setSliderPosition(0);
        applyEQ();
        break;
    case 12:
        //语音
        ui->eqSlider_1->setSliderPosition(-4);
        ui->eqSlider_2->setSliderPosition(0);
        ui->eqSlider_3->setSliderPosition(2);
        ui->eqSlider_4->setSliderPosition(0);
        ui->eqSlider_5->setSliderPosition(0);
        ui->eqSlider_6->setSliderPosition(0);
        ui->eqSlider_7->setSliderPosition(0);
        ui->eqSlider_8->setSliderPosition(0);
        ui->eqSlider_9->setSliderPosition(-4);
        ui->eqSlider_10->setSliderPosition(-6);
        applyEQ();
        break;
    default:
        break;
    }
}

void ShadowPlayer::addToListAndPlay(QList<QUrl> files)
{
    int newIndex = playList->getLength();
    int length = files.length();
    if (!files.isEmpty())
    {
        for (int i = 0 ;i < length; i++)
        {
            playList->add(files[i].toLocalFile());
        }
        if (playList->getLength() > newIndex) //如果添加了文件
            loadFile(playList->playIndex(newIndex));
    }
}

void ShadowPlayer::addToListAndPlay(QStringList files)
{
    int newIndex = playList->getLength();
    int length = files.length();
    if (length > 0)
    {
        for (int i = 0; i < length; i++)
        {
            playList->add(files[i]);
        }
        if (playList->getLength() > newIndex) //如果添加了文件
            loadFile(playList->playIndex(newIndex));
    }
}

void ShadowPlayer::addToListAndPlay(QString file)
{
    int newIndex = playList->getLength();
    playList->add(file);
    if (playList->getLength() > newIndex) //如果添加了文件
        loadFile(playList->playIndex(newIndex));
}

void ShadowPlayer::blsmtPlay(QStringList files)
{
    //计划的情况只处理一个文件，如果文件列表出现多个文件的情况那就有问题了
    int length = files.length();
    if (length == 1)
    {
        QFileInfo fileInfo(files[0]);
        if (nowPlayingPath == fileInfo.path())
        {
            if (!playList->justSearch(fileInfo.fileName())){
                playList->add(files[0]);
                playList->setSelectedByIndex(playList->getLength() -1);
            }
        } else {
            playList->clearAll();
            playList->loadFromFloder(fileInfo.path());
            if (!playList->justSearch(fileInfo.fileName())){
                playList->add(files[0]);
                playList->setSelectedByIndex(playList->getLength() -1);
            }
        }
        if (playList->getLength() > 0){ //简单判定
            loadFile(playList->getSelFile());
            playList->tableUpdate();
        }
    }
}

void ShadowPlayer::blsmtPlay(QString file)
{
    //计划的情况只处理一个文件，如果文件列表出现多个文件的情况那就有问题了
    if (!file.isEmpty())
    {
        QFileInfo fileInfo(file);
        if (nowPlayingPath == fileInfo.path())
        {
            if (!playList->justSearch(fileInfo.fileName())){
                playList->add(file);
                playList->setSelectedByIndex(playList->getLength() -1);
            }
        } else {
            playList->clearAll();
            playList->loadFromFloder(fileInfo.path());
            if (!playList->justSearch(fileInfo.fileName())){
                playList->add(file);
                playList->setSelectedByIndex(playList->getLength() -1);
            }
        }
        if (playList->getLength() > 0){ //简单判定
            loadFile(playList->getSelFile());
            playList->tableUpdate();
        }
    }
}

void ShadowPlayer::on_playPreButton_clicked()
{
    //先清理掉ab循环
    player->removeJumpPoint();
    bPointSeting = false;//这个也得清理掉，以免设置a点后自动下一曲，点循环会抽掉。

    if (playMode == 3)
    {
        //列表循环
        loadFile(playList->previous(true));
    } else if (playMode == 4) {
        if (!playList->isEmpty())//如果列表非空
        {
            //随机播放
            QTime time;
            time = QTime::currentTime();
            qsrand(time.msec() + time.second() * 1000);
            int index = qrand() % playList->getLength();
            //随机数
            loadFile(playList->playIndex(index));
        }
    } else {
        //正常情况
        loadFile(playList->previous(false));
    }
}

void ShadowPlayer::on_playNextButton_clicked()
{
    //先清理掉ab循环
    player->removeJumpPoint();
    bPointSeting = false;//这个也得清理掉，以免设置a点后自动下一曲，点循环会抽掉。

    if (playMode == 3)
    {
        //列表循环
        loadFile(playList->next(true));
    } else if (playMode == 4) {
        if (!playList->isEmpty())//如果列表非空
        {
            //随机播放
            QTime time;
            time = QTime::currentTime();
            qsrand(time.msec() + time.second() * 1000);
            int index = qrand() % playList->getLength();
            //随机数
            loadFile(playList->playIndex(index));
        }
    } else {
        loadFile(playList->next(false));
    }
}

void ShadowPlayer::on_playListButton_clicked()
{
    //如果右侧没有展开，则展开窗口
    if (width() < 370)
        on_extraButton_clicked();

    //判断动画是否不在播放
    if (playListHideAnimation->state() != QAbstractAnimation::Running &&
            playListShowAnimation->state() != QAbstractAnimation::Running)
    {
        if (ui->playerListArea->height() < 190)
        {
            eqHideAnimation->stop();
            lyricsHideAnimation->stop();
            playListShowAnimation->stop();
            eqHideAnimation->start();
            lyricsHideAnimation->start();
            playListShowAnimation->start();
        } else {
            if (width() > 370) //如果窗口已展开，则收起播放列表。否则什么都不做
            {
                eqShowAnimation->stop();
                lyricsShowAnimation->stop();
                playListHideAnimation->stop();
                eqShowAnimation->start();
                lyricsShowAnimation->start();
                playListHideAnimation->start();
            }
        }
    }
}

void ShadowPlayer::callFromPlayList()
{
    //播放列表的播放请求
    isFromPlayListFlag = true;
    loadFile(playList->getCurFile());
    //双击时触发的事件，已经无需选中，直接播放。
}

//倒放按钮事件
void ShadowPlayer::on_reverseButton_clicked()
{
    if (isReverse)
    {
        isReverse = false;
        ui->reverseButton->setText("正放");
        player->setReverse(false);
    } else {
        isReverse = true;
        ui->reverseButton->setText("倒放");
        player->setReverse(true);
    }
}

//混响效果调节
void ShadowPlayer::on_reverbDial_valueChanged(int value)
{
    player->updateReverb(value);
}

void ShadowPlayer::physicsSetting()
{
    double temp = 0;
    bool ok = false;

    temp = QInputDialog::getDouble(0, "加速度", "重力加速度\n【参数均为比率，1 = 频谱条总长度】", ui->FFTGroupBox->acc, 0, 2147483647, 3, &ok);
    if (ok)
    {
        ui->FFTGroupBox->acc = temp;
    }

    temp = QInputDialog::getDouble(0, "最大下落速度", "物体下落的最大速度", ui->FFTGroupBox->maxSpeed, 0, 2147483647, 3, &ok);
    if (ok)
    {
        ui->FFTGroupBox->maxSpeed = temp;
    }

    temp = QInputDialog::getDouble(0, "基准速度", "总体速度、力的倍增值\n此数值影响弹力、抛力\n最初版本用于下落速度，当时无物理效果\n【谨慎修改】", ui->FFTGroupBox->speed, 0, 2147483647, 3, &ok);
    if (ok)
    {
        ui->FFTGroupBox->speed = temp;
    }

    temp = QInputDialog::getDouble(0, "抛力倍增系数", "频谱条对物体的抛力强度倍增系数\n抛力将按此倍数加倍", ui->FFTGroupBox->forceD, 0, 2147483647, 3, &ok);
    if (ok)
    {
        ui->FFTGroupBox->forceD = temp;
    }

    temp = QInputDialog::getDouble(0, "弹力系数", "落地后动能保留量\n物体落地时，部分动能转化为声音和热能\n此参数决定碰撞后剩余的动能百分比\n【注：由于算法BUG，每次下落都将损失最后一帧离地高度的势能，所以动能一直损耗】\n因为没做空气阻力，所以应该让动能损耗更多\n1 = 完全反弹", ui->FFTGroupBox->elasticCoefficient, 0, 2147483647, 3, &ok);
    if (ok)
    {
        ui->FFTGroupBox->elasticCoefficient = temp;
    }

    temp = QInputDialog::getDouble(0, "弹力阀值", "当物体一帧下落的百分比（视为可穿透）小于该值时\n不计算弹力", ui->FFTGroupBox->minElasticStep, 0, 2147483647, 3, &ok);
    if (ok)
    {
        ui->FFTGroupBox->minElasticStep = temp;
    }
}

//频谱分析预设物理开
void ShadowPlayer::enableFFTPhysics()
{
    ui->FFTGroupBox->acc = 0.35;
    ui->FFTGroupBox->maxSpeed = 9;
    ui->FFTGroupBox->speed = 0.025;
    ui->FFTGroupBox->forceD = 6;
    ui->FFTGroupBox->elasticCoefficient = 0.6;
    ui->FFTGroupBox->minElasticStep = 0.02;
}

//频谱分析预设物理关
void ShadowPlayer::disableFFTPhysics()
{
    ui->FFTGroupBox->acc = 0.15;
    ui->FFTGroupBox->maxSpeed = 2;
    ui->FFTGroupBox->speed = 0.025;
    ui->FFTGroupBox->forceD = 0;
    ui->FFTGroupBox->elasticCoefficient = 0;
    ui->FFTGroupBox->minElasticStep = 0.02;
}

void ShadowPlayer::resizeEvent(QResizeEvent *)
{
    ui->extraButton->setGeometry(width() - 20, 0, 20, 20);
    ui->closeButton->setGeometry(width() - 65, 0, 40, 20);
    ui->miniSizeButton->setGeometry(width() - 90, 0, 25, 20);
    ui->setSkinButton->setGeometry(width() - 115, 0, 25, 20);
    ui->miniPlayer->setGeometry(width() - 140, 0, 25, 20);
}

void ShadowPlayer::showDeveloperInfo()
{
    QMessageBox::information(0, "暗影播放器-BLumia分支", "版本:正式版\n原作者：暗影夜光（陈XX）\n后期折腾：BLumia（王XX）\n\n原作者联系方式：\nQQ:617274873\nBLumia联系方式：\nQQ:782970009\n版权没有，自由使用");
}

void ShadowPlayer::saveConfig()
{
    QFile file(QCoreApplication::applicationDirPath() + "/config.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    stream << (quint32)0x78297000  //原来是0x61727480 XD
           << ui->freqSlider->value()
           << ui->volSlider->value()
           << isMute
           << ui->reverbDial->value()
           << playMode
           << skinMode
           << skinPos
           << skinDrawPos
           << ui->eqComboBox->currentIndex()
           << ui->eqEnableCheckBox->isChecked()
           << ui->eqSlider_1->value()
           << ui->eqSlider_2->value()
           << ui->eqSlider_3->value()
           << ui->eqSlider_4->value()
           << ui->eqSlider_5->value()
           << ui->eqSlider_6->value()
           << ui->eqSlider_7->value()
           << ui->eqSlider_8->value()
           << ui->eqSlider_9->value()
           << ui->eqSlider_10->value()
           << lb->isVisible()
           << autoLoadLoop
           << playlistMode;
    file.close();
}

void ShadowPlayer::loadConfig()
{
    QFile file(QCoreApplication::applicationDirPath() + "/config.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    quint32 magic;
    stream >> magic;
    if ((magic == 0x61727480)||(magic == 0x78297000))
    {
        int dataInt = 0;
        stream >> dataInt;
        ui->freqSlider->setValue(dataInt);
        stream >> dataInt;
        ui->volSlider->setValue(dataInt);
        bool dataBool = false;
        stream >> dataBool;
        this->isMute = dataBool;
        if (isMute)
        {
            ui->muteButton->setIcon(QIcon(":/icon/ICO/Mute.png"));
        } else {
            ui->muteButton->setIcon(QIcon(":/icon/ICO/Vol.png"));
        }
        stream >> dataInt;
        ui->reverbDial->setValue(dataInt);
        stream >> this->playMode;
        switch (playMode) {
        case 0:
            ui->playModeButton->setIcon(QIcon(":/icon/ICO/Single.png"));
            ui->playModeButton->setToolTip("单曲播放");
            break;
        case 1:
            ui->playModeButton->setIcon(QIcon(":/icon/ICO/Repeat.png"));
            ui->playModeButton->setToolTip("单曲循环");
            break;
        case 2:
            ui->playModeButton->setIcon(QIcon(":/icon/ICO/Order.png"));
            ui->playModeButton->setToolTip("顺序播放");
            break;
        case 3:
            ui->playModeButton->setIcon(QIcon(":/icon/ICO/AllRepeat.png"));
            ui->playModeButton->setToolTip("列表循环");
            break;
        case 4:
            ui->playModeButton->setIcon(QIcon(":/icon/ICO/Shuffle.png"));
            ui->playModeButton->setToolTip("随机播放");
            break;
        default:
            break;
        }
        stream >> this->skinMode;
        stream >> this->skinPos;
        stream >> this->skinDrawPos;
        stream >> dataInt;
        ui->eqComboBox->setCurrentIndex(dataInt);
        stream >> dataBool;
        ui->eqEnableCheckBox->setChecked(dataBool);
        stream >> dataInt;
        ui->eqSlider_1->setValue(dataInt);
        stream >> dataInt;
        ui->eqSlider_2->setValue(dataInt);
        stream >> dataInt;
        ui->eqSlider_3->setValue(dataInt);
        stream >> dataInt;
        ui->eqSlider_4->setValue(dataInt);
        stream >> dataInt;
        ui->eqSlider_5->setValue(dataInt);
        stream >> dataInt;
        ui->eqSlider_6->setValue(dataInt);
        stream >> dataInt;
        ui->eqSlider_7->setValue(dataInt);
        stream >> dataInt;
        ui->eqSlider_8->setValue(dataInt);
        stream >> dataInt;
        ui->eqSlider_9->setValue(dataInt);
        stream >> dataInt;
        ui->eqSlider_10->setValue(dataInt);
        stream >> dataBool;
        lb->setVisible(dataBool);
        stream >> dataBool;
        this->autoLoadLoop = dataBool;
        stream >> dataBool;
        this->playlistMode = dataBool;
    }
    file.close();
}

void ShadowPlayer::saveSkinData()
{
    QFile file(QCoreApplication::applicationDirPath() + "/skin.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    stream << (quint32)0x61727481 << skin;
    file.close();
}

void ShadowPlayer::loadSkinData()
{
    QFile file(QCoreApplication::applicationDirPath() + "/skin.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    quint32 magic;
    stream >> magic;
    if (magic == 0x61727481)
    {
        stream >> this->skin;
        skinLeft = skin.scaledToWidth(360, Qt::SmoothTransformation);
        skinFull = skin.scaledToWidth(710, Qt::SmoothTransformation);
        aspectRatio = (double)skin.height() / skin.width();
    }
    file.close();
}

bool ShadowPlayer::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    if (msg->message == WM_COPYDATA){
        COPYDATASTRUCT *p = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);
        if (!playlistMode)
            blsmtPlay(QString::fromUtf8((LPCSTR)(p->lpData)));//仅当播放模式是bl杀马特模式时进行此模式形式播放
        else
            addToListAndPlay(QString::fromUtf8((LPCSTR)(p->lpData)));
        return true;
    }
    return false;
}

void ShadowPlayer::on_setJumpButton_clicked()
{
    if (!player->isLooping()){
        bool ok = false;
        bool ok2 = false;
        jumpingTo = QInputDialog::getDouble(0, "上限" + QString::number(player->getTotalTimeSec()), "请输入跳转目标（即A点，单位：秒）\n当前位置：" + QString::number(player->getCurTimeSec()), jumpingTo, 0, player->getTotalTimeSec(), 4, &ok2);
        jumpingFrom = QInputDialog::getDouble(0, "上限" + QString::number(player->getTotalTimeSec()), "请输入跳转起点（即点，单位：秒）\n当前位置：" + QString::number(player->getCurTimeSec()) + "\n两个均点ok则生效", jumpingFrom, 0, player->getTotalTimeSec(), 4, &ok);
        if (ok && ok2) {
            player->setJumpPoint(jumpingFrom, jumpingTo);
            ui->setAbPointBtn->setIcon(QIcon(":/icon/ICO/LoopAB.png"));
            player->setPosByTime(jumpingFrom);
            if (autoLoadLoop) {
                switch(QMessageBox::question(NULL, "是否保存本音乐的loop循环数据?", "如果保存，下次播放本音乐会自动启用ab循环。你可以点击Yes进行保存\n你可以通过点击No取消保存，也可以在保存后通过删除同名的*.loop文件清除loop数据。", QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
                {
                case QMessageBox::Yes:
                    if (QFileInfo(playList->getCurFile()).exists()){
                        QFileInfo fileinfo(playList->getCurFile());
                        QFile file(fileinfo.path() + "/" + fileinfo.completeBaseName()+".loop");
                        if(!file.open(QIODevice::WriteOnly | QFile::Text))
                        {
                           file.close();
                           file.open(QIODevice::WriteOnly | QFile::Text);
                           return;
                        }

                        QTextCodec* codec=QTextCodec::codecForName("UTF-8");

                        QTextStream out(&file);
                        out.setCodec(codec);
                        out <<QString::number(jumpingFrom)<<"\n";
                        out <<QString::number(jumpingTo);
                        file.flush();
                        file.close();
                    } else {
                        QMessageBox::information(0, "失败", "无法获取当前正在播放的文件名，给你看看这个算了.");
                        QMessageBox::aboutQt(NULL, "关于神奇的Qt");
                    }
                    break;
                case QMessageBox::No:
                    QMessageBox::information(0, "成功取消", "您没有保存循环数据哦.");
                    break;
                default :
                    QMessageBox::information(0, "没有保存循环数据", "您没有保存循环数据哦.");
                    break;
                }
            }
        }
    } else {
        jumpingFrom = jumpingTo = 0;
        player->removeJumpPoint();
        ui->setAbPointBtn->setIcon(QIcon(":/icon/ICO/Loop.png"));
        on_setJumpButton_clicked();
    }
}

void ShadowPlayer::on_setAbPointBtn_clicked()
{
    if (!player->isLooping()){
        if (!bPointSeting) {
            jumpingTo = player->getCurTimeSec();
            bPointSeting = true;
            ui->setAbPointBtn->setIcon(QIcon(":/icon/ICO/LoopA.png"));
        } else {
            jumpingFrom = player->getCurTimeSec();
            bPointSeting = false;
            player->setJumpPoint(jumpingFrom, jumpingTo);
            player->setPosByTime(jumpingFrom);
            ui->setAbPointBtn->setIcon(QIcon(":/icon/ICO/LoopAB.png"));
        }
    } else {
        jumpingFrom = jumpingTo = 0;
        player->removeJumpPoint();
        ui->setAbPointBtn->setIcon(QIcon(":/icon/ICO/Loop.png"));
    }
}

void ShadowPlayer::on_miniPlayer_clicked()
{
    miniUi->showMiniForm(this->curMonitor);
    //显示托盘图标
    trayicon->show();
    //在系统托盘显示气泡消息提示
    trayicon->showMessage(tr("Shadow Player"), tr("您可以通过点击这里显示主窗体"), QSystemTrayIcon::Information, 5000);
    //隐藏主窗体
    if(trayicon->isVisible())
    {
        hide();
    }
}

void ShadowPlayer::onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
  switch(reason)
  {
  //单击
  case QSystemTrayIcon::Trigger:
  //双击
  case QSystemTrayIcon::DoubleClick:
      //恢复窗口显示
      this->setWindowState(Qt::WindowActive);
      this->show();
      trayicon->hide();
      emit hideMiniFrom();
      break;
  case QSystemTrayIcon::Context:
      //不会有这里了，转到这里吧：
      //就是下面紧跟的俩函数啦
      break;
  default:
      break;
  }
}

void ShadowPlayer::showMainFormRequire(){
     this->setWindowState(Qt::WindowActive);
     this->show();
     trayicon->hide();
     emit hideMiniFrom();
}

void ShadowPlayer::exitQAppFromTrayIcon(){
    trayicon->hide();
    emit hideMiniFrom();
    fadeOutAnimation->start();
    //close();上一行通过主窗体的淡出触发程序退出
}

//设置Win nt6任务栏按钮对应窗口
void ShadowPlayer::setTaskbarButtonWindow()
{
    taskbarButton->setWindow(windowHandle());
    thumbnailToolBar->setWindow(windowHandle());
}


void ShadowPlayer::on_eqEnableCheckBox_clicked(bool checked)
{
    if (checked)
    {
        player->eqReady();//初始化均衡器
        applyEQ();//应用当前值
    } else {
        player->disableEQ();//移除均衡器
    }
}

void ShadowPlayer::on_offsetSlider_valueChanged(int value)
{
    lyrics->lrcOffset = value;
    ui->offsetLabel->setText(QString::number(value, 10));
}

void ShadowPlayer::on_offsetLabel_clicked()
{
    lyrics->lrcOffset = 0;
    ui->offsetSlider->setValue(0);
    ui->offsetLabel->setText("lrcOffset");
}

#include "playlist.h"
#include "thread.h"
#include "ui_playlist.h"

PlayList::PlayList(Player *player, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayList)
{
    ui->setupUi(this);
    curIndex = 0;
    lengthFilter = 0;
    this->player = player;
    ui->playListTable->horizontalHeader()->setStretchLastSection(true);//自动设置最后一列宽度
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    this->setFixedSize(this->width(), this->height());

    //“查找”文本框，绑定回车键到“查找”按钮
    connect(ui->searchEdit, SIGNAL(returnPressed()), this, SLOT(on_searchButton_clicked()));

    readFromFile(QCoreApplication::applicationDirPath() + "/PlayList.sdpl");

    //搜索功能部分的动画
    //搜索条
    finderAnimation = new QPropertyAnimation(ui->finderFlame, "geometry");
    finderAnimation->setEasingCurve(QEasingCurve::OutCirc);
    finderAnimation->setDuration(600);
    finderAnimation->setStartValue(QRect(331, 330, 331, 31));
    finderAnimation->setEndValue(QRect(0, 330, 331, 31));
    //播放列表
    playListAnimation = new QPropertyAnimation(ui->playListTable, "geometry");
    playListAnimation->setDuration(600);
    playListAnimation->setEasingCurve(QEasingCurve::OutCirc);
}

PlayList::~PlayList()
{
    saveToFile(QCoreApplication::applicationDirPath() + "/PlayList.sdpl");
    delete ui;
    delete finderAnimation;
}

bool PlayList::fixSuffix(QString fileName)
{
    if(fileName.toLower().endsWith(".mp3")||
            fileName.toLower().endsWith(".mp2")||
            fileName.toLower().endsWith(".mp1")||
            fileName.toLower().endsWith(".wav")||
            fileName.toLower().endsWith(".ogg")||
            fileName.toLower().endsWith(".aiff")||
            fileName.toLower().endsWith(".ape")||
            fileName.toLower().endsWith(".mp4")||
            fileName.toLower().endsWith(".m4a")||
            fileName.toLower().endsWith(".m4v")||
            fileName.toLower().endsWith(".aac")||
            fileName.toLower().endsWith(".alac")||
            fileName.toLower().endsWith(".tta")||
            fileName.toLower().endsWith(".flac")||
            fileName.toLower().endsWith(".wma")||
            fileName.toLower().endsWith(".wv")
            )
    {
        return true;
    } else {
        return false;
    }
}

bool PlayList::isEmpty()
{
    if (fileList.isEmpty())
        return true;
    else
        return false;
}

//核心函数，添加歌曲
void PlayList::add(QString fileName)
{
    if (fixSuffix(fileName))
    {
        if ((int)(player->getFileSecond(fileName)) >= lengthFilter)
        {
            fileList.append(fileName);
            timeList.append(player->getFileTotalTime(fileName));
        }
    }
    tableUpdate();
}

//核心函数
void PlayList::insert(int index, QString fileName)
{
    if (fixSuffix(fileName))
    {
        if ((int)(player->getFileSecond(fileName)) >= lengthFilter)
        {
            if (index < curIndex)
                ++curIndex;//如果在前端插入，后移播放索引
            fileList.insert(index, fileName);
            timeList.insert(index, player->getFileTotalTime(fileName));
        }
    }
    tableUpdate();
}

void PlayList::remove(int index)
{
    if (index <= curIndex && index > -1)//大于-1用于判断是否未选任何项
        --curIndex;//删除前方项，上移当前项索引
    fileList.removeAt(index);
    timeList.removeAt(index);
    tableUpdate();
}

void PlayList::clearAll()
{
    fileList.clear();
    timeList.clear();
    curIndex = 0;
    tableUpdate();
}

int PlayList::getLength()
{
    return fileList.length();
}

int PlayList::getIndex()
{
    if (!fileList.isEmpty())
    {
        return curIndex;
    }
    else
    {
        return -1;
    }
}

//下一曲 参数：是否循环
QString PlayList::next(bool isLoop)
{
    if (!fileList.isEmpty())
    {
        if (isLoop)
        {
            if (curIndex < fileList.length() - 1)
            {
                ++curIndex;
            } else {
                curIndex = 0;
            }
            ui->playListTable->selectRow(curIndex);//让视图跟随当前播放歌曲，下一句使该行不选中
            tableUpdate();
            return fileList[curIndex];
        } else {
            if (curIndex < fileList.length() - 1)
            {
                ++curIndex;
                ui->playListTable->selectRow(curIndex);
                tableUpdate();
                return fileList[curIndex];
            } else {
                return "stop";//后面没有了。此信息将不处理
            }
        }
    }
    return "";//空列表
}

//上一曲
QString PlayList::previous(bool isLoop)
{
    if (!fileList.isEmpty())
    {
        if (isLoop)
        {
            if (curIndex == 0)
            {
                curIndex = fileList.length() - 1;//循环读取
            } else {
                --curIndex;
            }
            ui->playListTable->selectRow(curIndex);
            tableUpdate();
            return fileList[curIndex];
        } else {
            if (curIndex > 0)
            {
                --curIndex;
                ui->playListTable->selectRow(curIndex);
                tableUpdate();
                return fileList[curIndex];
            } else {
                return "stop";//前面没有了。
            }
        }
    }
    return "";//空列表
}

//index从0开始计
QString PlayList::playIndex(int index)
{
    curIndex = index;
    ui->playListTable->selectRow(curIndex);
    tableUpdate();
    return fileList[curIndex];
}

//返回指定索引的文件名
QString PlayList::getFileNameForIndex(int index)
{
    return fileList[index];
}

//返回当前文件名
QString PlayList::getCurFile()
{
    return fileList[curIndex];
}

//返回选中的文件名（不是绿条）
QString PlayList::getSelFile()
{
    return fileList[ui->playListTable->currentRow()];
}

//返回最后一个文件名，并设置索引
QString PlayList::playLast()
{
    if (!fileList.isEmpty())
    {
        curIndex = fileList.length() - 1;
        ui->playListTable->selectRow(curIndex);
        tableUpdate();
        return fileList[curIndex];
    } else {
        return "";
    }
}

//刷新表格
void PlayList::tableUpdate()
{
    //这里不能调用此类中任何一个操作元素的函数
    //否则将造成循环递归
    ui->playListTable->clear();
    ui->playListTable->setRowCount(getLength());//删除项目后，更改表格总行数，防止出现空白行。
    int count = fileList.size();//循环效率优化
    //重新生成表格项目
    for (int i = 0; i < count; i++)
    {
        QString fileName = fileList[i];
        QFileInfo fileInfo(fileName);

        QTableWidgetItem *item = new QTableWidgetItem(fileInfo.fileName());
        QTableWidgetItem *timeItem = new QTableWidgetItem(timeList[i]);

        if (i == curIndex)
        {
            item->setBackgroundColor(QColor(128, 255, 0, 128));
            timeItem->setBackgroundColor(QColor(128, 255, 0, 128));
        }

        ui->playListTable->setItem(i, 0, item);
        ui->playListTable->setItem(i, 1, timeItem);
    }
}

void PlayList::removeFromList()
{
    /*
     * 这里做了好久，若直接删除对应行号，由于上次删除操作使得行号发生变动，误删
     * 试过遍历列表得到选中的项目，倒序访问，结果发现排列方式可能不是倒序（访问越界）
     * 试过顺序+偏移量的方式，后几项误删
     * 以下方法仍为倒序删除。
     * 测试正常
     * 此方法来自：http://hi.baidu.com/speedylvshirly/item/27c37571f56deb19d1dcb3ee
     */

    //获得列表模型
    QItemSelectionModel *selectionModel = ui->playListTable->selectionModel();
    //获得选择项的列表
    QModelIndexList selected = selectionModel->selectedIndexes();
    QMap<int, int> rowMap;//利用QMap的自动排序功能来排列顺序以便删除
    foreach (QModelIndex index, selected)
    {
        rowMap.insert(index.row(), 0);//遍历元素，取得要删除的行数Map
    }

    int row;//要删除的行
    //创建一个迭代器
    QMapIterator<int, int> rowMapIterator(rowMap);
    rowMapIterator.toBack();
    //循环倒序删除
    while (rowMapIterator.hasPrevious())
    {
        rowMapIterator.previous();
        row = rowMapIterator.key();
        remove(row);
    }
}

void PlayList::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void PlayList::dropEvent(QDropEvent *event)
{
    /*
     * 不同于主窗口
     * 允许多文件拖放
     */
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    int urlCount = urls.size();
    QString fileName;

    for (int i = 0; i < urlCount; i++)
    {
        fileName = urls[i].toLocalFile();
        if (fixSuffix(fileName))
        {
            add(fileName);
        }
    }
}

void PlayList::loadFromFloder(const QString path)
{
    /*
     * 从文件夹导入音频
     * 主要目的是供WMP式播放列表自动载入用
     * 从路径导入，不遍历子文件夹
     * 文件的导入方式参考了这个内容：
     * http://blog.csdn.net/fouder_li/article/details/6680793
     */
    QDir *dir=new QDir(path);
    QStringList filter;
    //filter<<"*.dat";
    //dir->setNameFilters(filter);
    QList<QFileInfo> *urls=new QList<QFileInfo>(dir->entryInfoList(filter));
    if (urls->isEmpty()) //(urls.count()==0)
        return;

    int urlCount = urls->size();
    QString fileName;

    for (int i = 0; i < urlCount; i++)
    {
        fileName = urls->at(i).filePath();
        if (fixSuffix(fileName))
        {
            add(fileName);
        }
        //防止界面假死（多线程尝试失败所以先用这个）
        QApplication::processEvents();
    }
    sortPlayList(1);
    delete urls;//上面创建了指针
}

void PlayList::loadFromFloderAndSub(const QString path)
{
    /*
     * 从文件夹导入音频
     * 实现基本的文件夹导入音频功能
     * 从路径导入，使用迭代器遍历文件夹
     * 文件的导入方式参考了这个内容：
     * http://blog.sina.com.cn/s/blog_a6fb6cc90101f1ur.html
     */
    //判断路径是否存在
    QDir dir(path);
    if(!dir.exists())
    {
        return;
    }

    //获取所选文件类型过滤器
    QStringList filters;
    filters<<QString("*.mp3")<<QString("*.mp2")<<QString("*.mp1")<<QString("*.wav")
           <<QString("*.aiff")<<QString("*.ogg")<<QString("*.ape")<<QString("*.m4a")
           <<QString("*.flac")<<QString("*.aac")<<QString("*.wma");//差不多够了...

    //定义迭代器并设置过滤器
    QDirIterator dir_iterator(path,
        filters,
        QDir::Files | QDir::NoSymLinks,
        QDirIterator::Subdirectories);
    while(dir_iterator.hasNext())
    {
        dir_iterator.next();
        QFileInfo fileInfo = dir_iterator.fileInfo();
        QString file_path = fileInfo.filePath();
        add(file_path);
    }
}

void PlayList::on_playListTable_cellDoubleClicked(int row, int )
{
    curIndex = row;
    emit callPlayer();//发送信号给播放器
    tableUpdate();
}

void PlayList::clearCurList()
{
    clearAll();
}

void PlayList::insertToList()
{
    int index = ui->playListTable->currentRow();//记录当前选中的列
    if (index < 0)
        index = 0;//如果没有选中任何项，在开头插入
    QStringList fileNames = QFileDialog::getOpenFileNames(this, QString::fromUtf8("在选择项前插入"), 0, QString::fromUtf8("音频文件 (*.mp3 *.mp2 *.mp1 *.wav *.aiff *.ogg *.ape *.mp4 *.m4a *.m4v *.aac *.alac *.tta *.flac *.wma *.wv)"));
    int count = fileNames.size();
    for (int i = 0; i < count; i++)
    {
        QString fileName = fileNames[i];
        insert(index + i, fileName);
    }
}

void PlayList::addToList()
{
    //QFileDialog存在莫名其妙的内存泄漏问题
    //选中文件会占用内存空间
    //取消选中不会释放
    //无解……
    QStringList fileNames = QFileDialog::getOpenFileNames(this, QString::fromUtf8("添加音频"), 0, QString::fromUtf8("音频文件 (*.mp3 *.mp2 *.mp1 *.wav *.aiff *.ogg *.ape *.mp4 *.m4a *.m4v *.aac *.alac *.tta *.flac *.wma *.wv)"));
    int count = fileNames.size();
    for (int i = 0; i < count; i++)
    {
        QString fileName = fileNames[i];
        add(fileName);
    }
}

//查找项目
void PlayList::on_searchButton_clicked()
{
    if (!fileList.isEmpty() && !ui->searchEdit->text().isEmpty())
    {
        int resultIndex = -1;
        int count = fileList.size();
        //在列表中查找字符串
        for (int i = 0; i < count; i++)
        {
            QString fileName = fileList[i];
            QFileInfo fileInfo(fileName);

            //判断“区分大小写”复选框
            if (ui->isCaseSensitive->isChecked())
            {
                if (fileInfo.fileName().indexOf(ui->searchEdit->text()) > -1)//区分大小写
                {
                    //得到结果，记录
                    resultIndex = i;
                    break;
                }
            } else {
                if (fileInfo.fileName().toLower().indexOf(ui->searchEdit->text().toLower()) > -1)//不区分大小写
                {
                    resultIndex = i;
                    break;
                }
            }
        }

        //如果查找到结果
        if (resultIndex != -1)
        {
            ui->playListTable->selectRow(resultIndex);
        } else {
            QMessageBox::information(0, "很抱歉", "找不到您要查找的内容", "谢谢");
        }
    } else if (ui->searchEdit->text().isEmpty()) {
        QMessageBox::information(0, "您好", "请问您要查找什么？", "我忘记了");
    } else {
        QMessageBox::information(0, "这是什么情况", "明明什么都没有，为什么我还要在里面找东西呢？。。", "~(>_<。)＼");
    }
}

void PlayList::setSelectedByIndex(int index)//index范围为0到总个数-1
{
    if (!fileList.isEmpty() && (index < fileList.size()) && (index >= 0)){
        ui->playListTable->selectRow(index);
        curIndex = index;
        //tableUpdate();
    }
}

bool PlayList::justSearch(QString file)//传递进来的应该是一个文件名，fileInfo.fileName()得到的
{
    if (!fileList.isEmpty() && !file.isEmpty())
    {
        int resultIndex = -1;
        int count = fileList.size();
        //在列表中查找字符串
        for (int i = 0; i < count; i++)
        {
            QString fileName = fileList[i];
            QFileInfo fileInfo(fileName);

            //判断“区分大小写”复选框
            if (file == fileInfo.fileName())
            {
                //得到结果，记录
                resultIndex = i;
                break;
            }
        }

        //如果查找到结果
        if (resultIndex != -1)
        {
            ui->playListTable->selectRow(resultIndex);
            curIndex = resultIndex;
            //tableUpdate();
            return true;
        } else {
            return false;
        }
    } else if (file.isEmpty()) {
        QMessageBox::information(0, "诶？", "程序竟然不知道需要找什么文件了", "一定哪里搞错了");
    } else {
        QMessageBox::information(0, "诶？", "列表竟然是空的呐_(:з」∠)_", "一定哪里搞错了");
    }
    return false;
}

//查找下一个
void PlayList::on_searchNextButton_clicked()
{
    if (!fileList.isEmpty() && !ui->searchEdit->text().isEmpty())
    {
        int resultIndex = -1;
        int start = ui->playListTable->currentRow() + 1;
        int count = fileList.size();

        if (start < count) //检测是否越界
            for (int i = start; i < count; i++)
            {
                QString fileName = fileList[i];
                QFileInfo fileInfo(fileName);

                if (ui->isCaseSensitive->isChecked())
                {
                    if (fileInfo.fileName().indexOf(ui->searchEdit->text()) > -1)
                    {

                        resultIndex = i;
                        break;
                    }
                } else {
                    if (fileInfo.fileName().toLower().indexOf(ui->searchEdit->text().toLower()) > -1)
                    {
                        resultIndex = i;
                        break;
                    }
                }
            }

        if (resultIndex != -1)
        {
            ui->playListTable->selectRow(resultIndex);
        } else {
            QMessageBox::information(0, "已完成查找", "所有的内容都查找完毕啦", "辛苦了");
        }
    } else if (ui->searchEdit->text().isEmpty()) {
        QMessageBox::information(0, "您好", "请问您要查找什么呢？", "我忘记了");
    } else {
        QMessageBox::information(0, "这是什么情况", "明明什么都没有，为什么我还要在里面找东西呢？。。", "~(>_<。)＼");
    }
}

void PlayList::setLenFiler()
{
    bool ok;
    int set = QInputDialog::getInt(0, "最小播放长度", "小于该长度的音频文件将不被接受\n单位：秒" ,lengthFilter, 0, 2147483647, 1, &ok);
    if (ok)
        lengthFilter = set;
}

//保存播放列表，参数：文件路径
void PlayList::saveToFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    stream << (quint32)0x78297000 << fileList << timeList << curIndex;
    file.close();
}

//载入播放列表，参数：文件路径
void PlayList::readFromFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    quint32 magic;
    stream >> magic;
    if ((magic == 0x61727487)||(magic == 0x78297000))
    {
        stream >> fileList;
        stream >> timeList;
        stream >> curIndex;
    }
    file.close();
    tableUpdate();
}

//从文件夹添加文件到列表
void PlayList::addFromFloderToList()
{
    QString path=QFileDialog::getExistingDirectory(NULL, tr("选择文件夹（取消并在右键菜单选择“歌曲最短长度过滤选项”可设置音频长度过滤）"),"/",QFileDialog::ShowDirsOnly);
    QFileInfo pathX(path);
    if (pathX.isDir()){
        switch(QMessageBox::question(NULL, "是否遍历子文件夹?", "是否遍历子文件夹?\n如果遍历子文件夹可能需要使用较长时间导入。",
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
        {
        case QMessageBox::Yes:
            loadFromFloderAndSub(path);
            break;
        case QMessageBox::No:
            loadFromFloder(path);
            break;
        default :
            loadFromFloder(path);
            break;
        }
    }
}

//右键菜单
void PlayList::contextMenuEvent(QContextMenuEvent *)
{
    QCursor cur=this->cursor();

    //根据是否选中文件判断是不是需要弹出右键菜单
    int item = ui->playListTable->currentRow();


    if (item >= 0)//如果在表格上右键（因为重载的右键菜单函数对整个Widget有效所以需要判断,可能有问题）
    {
        QMenu menu;
        menu.addAction("[插入]插入歌曲到当前列表" , this ,SLOT(insertToList()));
        menu.addAction("[添加]添加歌曲到选中项前" , this ,SLOT(addToList()));
        menu.addAction("[目录]从文件夹导入歌曲" , this ,SLOT(addFromFloderToList()));
        menu.addAction("[移除]从列表移除选定项目" , this ,SLOT(removeFromList()));
        menu.addAction("[清空]清空当前列表" , this ,SLOT(clearCurList()));
        menu.addAction("[选项]歌曲最短长度过滤选项" , this ,SLOT(setLenFiler()));

        menu.addSeparator();//我是华丽的分割线
        menu.addAction("打开歌曲所在文件夹" , this ,SLOT(openFileFloder()));
        menu.exec(cur.pos());
    }
}

void PlayList::on_listOptionButton_clicked()
{
    QCursor cur=this->cursor();

    QMenu menu;
    menu.addAction("[导入]从文件夹导入歌曲" , this ,SLOT(addFromFloderToList()));
    menu.addAction("[导出]复制列表歌曲到目录" , this ,SLOT(listFileCopyer()));
    menu.addAction("[查找]从列表中查找歌曲" , this ,SLOT(showFinder()));
    menu.exec(cur.pos());

}

void PlayList::openFileFloder()
{
    QFileInfo fi= QFileInfo(getSelFile());
    QString filePath;
    filePath=fi.filePath();
    filePath.replace("/","\\");//将地址中的"/"替换为"\"，因为在Windows下使用的是"\"。
    QProcess::startDetached("explorer /select, \""+filePath+"\"");//打开上面获取的目录
}

void PlayList::on_playListCombo_currentIndexChanged(int index)
{
    switch(index){
        case 0: readFromFile(QCoreApplication::applicationDirPath() + "/PlayList.sdpl"); break;
        case 1: readFromFile(QCoreApplication::applicationDirPath() + "/OsuList.sdpl"); break;
    }
}

void PlayList::setPlayListCombo(int index){
    ui->playListCombo->setCurrentIndex(index);
    //on_playListCombo_currentIndexChanged(index);
}

void PlayList::on_fliterOptionButton_clicked()
{
    QCursor cur=this->cursor();

    QMenu menu;
    menu.addAction("[选项]歌曲最短长度过滤选项" , this ,SLOT(setLenFiler()));
    //menu.addAction("[测试]核弹反应堆" , this ,SLOT(debuger()));
    menu.exec(cur.pos());

}

void PlayList::on_musicOptionButton_clicked()
{
    QCursor cur=this->cursor();

    //根据是否选中文件判断是不是需要弹出右键菜单
    int item = ui->playListTable->currentRow();

    if (item >= 0)//如果在表格上右键（因为重载的右键菜单函数对整个Widget有效所以需要判断,可能有问题）
    {
        QMenu menu;
        menu.addAction("打开歌曲所在文件夹" , this ,SLOT(openFileFloder()));
        menu.exec(cur.pos());
    } else {
        QMessageBox::information(0, "错误了呢", "您还没有选择任何一个条目呢喵\n快快选择一个吧", "忘记了喵~");
    }
}

void PlayList::showFinder(){
    if (ui->finderFlame->x() > 150)
    {
        playListAnimation->setStartValue(QRect(0, 25, 331, 325));
        playListAnimation->setEndValue(QRect(0, 25, 331, 297));
        playListAnimation->start();
        finderAnimation->setStartValue(QRect(331, 330, 331, 31));
        finderAnimation->setEndValue(QRect(0, 330, 331, 31));
        finderAnimation->start();
    } else {
        playListAnimation->setStartValue(QRect(0, 25, 331, 297));
        playListAnimation->setEndValue(QRect(0, 25, 331, 325));
        playListAnimation->start();
        finderAnimation->setStartValue(QRect(0, 330, 331, 31));
        finderAnimation->setEndValue(QRect(331, 330, 331, 31));
        finderAnimation->start();
    }
}

bool PlayList::listFileCopyer(){

    int copied = 0,same = 0;
    QString pathTo=QFileDialog::getExistingDirectory(NULL, tr("选择要导出（复制）到的文件夹"),"/",QFileDialog::ShowDirsOnly);
    QFileInfo pathX(pathTo);
    if (!pathX.isDir()){
        //路径都不是，应该是人工取消，返回。
        return false;
    }

    if (!fileList.isEmpty())
    {
        int count = fileList.size();
        //遍历列表挨个儿复制
        for (int i = 0; i < count; i++)
        {
            QString fileName = fileList[i];
            QFileInfo fileInfo(fileName);
            //复制
            QDir dir(pathTo+"\\"+fileInfo.fileName());
            if (dir.exists()) {
                same++;
                continue;
            }
            if (!QFile::copy(fileInfo.filePath(),pathTo+"\\"+fileInfo.fileName()))
            {
                //复制过程中出错，返回
                QMessageBox::information(0, "诶？", "复制过程中出错了呐_(:з」∠)_\n倒霉孩子是："+pathTo+"\\"+fileInfo.fileName(), "shenmegui");
                return false;
            }
            copied++;
            //防止界面假死（多线程尝试失败所以先用这个）
            QApplication::processEvents();
        }
    } else {
        QMessageBox::information(0, "诶？", "列表竟然是空的呐_(:з」∠)_", "一定哪里搞错了...");
        return false;
    }
    QMessageBox::information(0, "It's done", "完成啦\(^.^)//\n一共复制了"+ QString::number(copied,10)+"个新曲目，另有"+ QString::number(same,10)+"个已有项目被跳过", "好棒~");
    return true;
}

static inline QChar getNextChar(const QString &s, int location) {
    return (location < s.length()) ? s.at(location) : QChar();
}

bool smartFileNameSort(const QString s1,const QString s2) {
    //qfilesystemmodle.cpp
    for (int l1 = 0, l2 = 0; l1 <= s1.count() && l2 <= s2.count(); ++l1, ++l2) {
        // skip spaces, tabs and 0's
        QChar c1 = getNextChar(s1, l1);
        while (c1.isSpace())
            c1 = getNextChar(s1, ++l1);
        QChar c2 = getNextChar(s2, l2);
        while (c2.isSpace())
            c2 = getNextChar(s2, ++l2);

        if (c1.isDigit() && c2.isDigit()) {
            while (c1.digitValue() == 0)
                c1 = getNextChar(s1, ++l1);
            while (c2.digitValue() == 0)
                c2 = getNextChar(s2, ++l2);

            int lookAheadLocation1 = l1;
            int lookAheadLocation2 = l2;
            int currentReturnValue = 0;
            // find the last digit, setting currentReturnValue as we go if it isn't equal
            for (
                QChar lookAhead1 = c1, lookAhead2 = c2;
                (lookAheadLocation1 <= s1.length() && lookAheadLocation2 <= s2.length());
                lookAhead1 = getNextChar(s1, ++lookAheadLocation1),
                lookAhead2 = getNextChar(s2, ++lookAheadLocation2)
                ) {
                bool is1ADigit = !lookAhead1.isNull() && lookAhead1.isDigit();
                bool is2ADigit = !lookAhead2.isNull() && lookAhead2.isDigit();
                if (!is1ADigit && !is2ADigit)
                    break;
                if (!is1ADigit)
                    return true;
                if (!is2ADigit)
                    return false;
                if (currentReturnValue == 0) {
                    if (lookAhead1 < lookAhead2) {
                        currentReturnValue = -1;
                    } else if (lookAhead1 > lookAhead2) {
                        currentReturnValue = 1;
                    }
                }
            }
            if (currentReturnValue != 0)
                return currentReturnValue==-1?true:false;
        }

        if (true) {
            if (!c1.isLower()) c1 = c1.toLower();
            if (!c2.isLower()) c2 = c2.toLower();
        }
        int r = QString::localeAwareCompare(c1, c2);
        if (r < 0)
            return -1;
        if (r > 0)
            return 1;
    }
    // The two strings are the same (02 == 2) so fall back to the normal sort
    return QString::compare(s1, s2)==-1?true:false;

}

bool foolishFileNameSort(const QString s1,const QString s2) {
    return QString::compare(s1, s2)==-1?true:false;
}

//提供文件名排序功能，以便排序文件名。主要为实现智能的文件名排序提供的比较函数。
void PlayList::sortPlayList(int howToSort) {
    //fileList排序
    switch (howToSort) {
        case 1:
            qSort(fileList.begin(),fileList.end(),smartFileNameSort);
            break;
        case 2:
            qSort(fileList.begin(),fileList.end(),foolishFileNameSort);
            break;
        default :
            qSort(fileList.begin(),fileList.end(),smartFileNameSort);
    }
    //设置当前播放索引并重绘表格
    //QMessageBox::information(0, "执行了排序啦", "刚刚执行了排序啦_(:з」∠)_", "shenmegui");

    //设置索引暂略
    tableUpdate();
}

void PlayList::debuger(){
    MutiThread Thread1;
    Thread1.setFunc(1);
    Thread1.start();//只要执行这行就爆炸，原因不明。。。
    //第704行启用测试。
}

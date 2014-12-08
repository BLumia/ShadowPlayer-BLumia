#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "player.h"

namespace Ui {
class PlayList;
}

class PlayList : public QWidget
{
    Q_OBJECT

public:
    explicit PlayList(Player *player, QWidget *parent = 0);
    ~PlayList();
    bool fixSuffix(QString fileName);
    bool isEmpty();
    void add(QString fileName);//添加文件
    void insert(int index, QString fileName);//插入文件
    void remove(int index);
    void clearAll();
    int getLength();
    int getIndex();//取得当前播放索引
    QString next(bool isLoop = false);//得到下一曲路径，索引+1 参数：是否循环
    QString previous(bool isLoop = false);//得到上一曲地址路径
    QString playIndex(int index);//播放指定索引
    QString getFileNameForIndex(int index);
    QString getCurFile();
    QString getSelFile();
    QString playLast();//播放列表末尾文件
    void tableUpdate();//更新显示内容
    void saveToFile(QString fileName);
    void readFromFile(QString fileName);
    bool justSearch(QString file);
    void setSelectedByIndex(int index);
    void loadFromFloder(const QString path);//从路径（文件夹）导入音乐文件，不含子文件夹
    void loadFromFloderAndSub(const QString path);//从路径（文件夹）导入音乐文件,含子文件夹
    void setPlayListCombo(int index);

private slots:
    void on_playListTable_cellDoubleClicked(int row, int);
    void on_searchButton_clicked();
    void on_searchNextButton_clicked();
    void setLenFiler();//右键菜单：歌曲最短长度过滤器，原on_setLenFilButton_clicked();
    void showFinder();
    void openFileFloder();//右键菜单：打开所在文件夹
    void addFromFloderToList();//右键菜单：从文件夹导入歌曲，原on_addFloderButton_clicked();
    void insertToList();//右键菜单：插入歌曲到列表，原on_insertButton_clicked();
    void addToList();//右键菜单：添加歌曲到列表，原on_addButton_clicked();
    void removeFromList();//右键菜单：从播放列表移除选定的项目，原on_deleteButton_clicked();
    void clearCurList();//右键菜单：清空当前列表，原on_clearButton_clicked();
    bool listFileCopyer();//右键菜单：导出到目录。
    void on_listOptionButton_clicked();//显示列表的一些选项，比如导入导出

    void on_playListCombo_currentIndexChanged(int index);


    void on_fliterOptionButton_clicked();

    void on_musicOptionButton_clicked();

signals:
    void callPlayer();//请求主窗口播放文件

private:
    Ui::PlayList *ui;
    QList<QString> fileList;
    QList<QString> timeList;
    int curIndex;//正在播放的文件索引
    Player *player;
    int lengthFilter;//播放长度过滤
    QPropertyAnimation *finderAnimation;
    QPropertyAnimation *playListAnimation;

protected:
    void dragEnterEvent(QDragEnterEvent *event);//拖放相关
    void dropEvent(QDropEvent *event);
    void contextMenuEvent(QContextMenuEvent *);//右键菜单
};

#endif // PLAYLIST_H

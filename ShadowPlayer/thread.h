#ifndef THREAD_H
#define THREAD_H

/*
多线程部分
主要是为了解决从文件夹导入列表和导出列表到目录操作所导致的界面不能响应。
参考了以下文档：
http://blog.csdn.net/xipiaoyouzi/article/details/8450704
http://www.kuqin.com/qtdocument/threads.html
http://my.oschina.net/u/200628/blog/187865（这个最科学）
*/

#include <QThread>
#include <QtWidgets>


class MutiThread : public QThread
{
   Q_OBJECT
public:
    MutiThread(/*Player *plr,PlayList *pls*/);
    void setMessage(QString message);
    void setFunc(int num);
    void stop();

protected:
    void run();
    void doMutiThreadThing(int funcID);

private:
    QString messageStr;
    volatile int funcID;
    volatile bool stopped;
    /*Player *player;
    PlayList *playlist;*/
};


#endif // THREAD_H

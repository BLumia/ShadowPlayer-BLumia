#include "thread.h"

MutiThread::MutiThread()
{
    /*this->player = plr;
    this->playlist = pls;*/
    stopped = false;
    funcID = 0;
}

void MutiThread::run()
{
    doMutiThreadThing(funcID);

    stopped = true;
    //stop();
}

void MutiThread::stop()
{
    stopped = true;
    funcID = 0;
}

void MutiThread::doMutiThreadThing(int funcID)
{
    switch(funcID){
        case 0: //funcID默认值，拦截未设置时执行线程的动作
                QMessageBox::information(0, "Nuclear Fusion", "WARNING!!!\n线程未被指定，这是超级危险的", "哦...");
                break;
        case 1: //1.
                QMessageBox::information(0, "测试", "ID为1的指令被执行", "哦...");
                break;
        case 2: //2.
                QMessageBox::information(0, "测试", "ID为2的指令被执行", "哦...");
                break;
    }
    stopped = true;
}

void MutiThread::setFunc(int num)
{
    funcID = num;
    //QMessageBox::information(0, "测试", "shenmegui "+QString::number(funcID), "哦...");
}

void MutiThread::setMessage(QString message)
{
    //
}

/*
ID3v2标签图片提取
ShadowPower
目前完成了ID3v2.3
*/
#ifndef _ShadowPower_ID3V2PIC___
#define _ShadowPower_ID3V2PIC___

#define _CRT_SECURE_NO_WARNINGS //VS如此蛋疼

#ifndef NULL
#define NULL 0
#endif
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef unsigned char byte;
using namespace std;

//ID3v2标签头部结构体定义
typedef struct
{
	char  identi[3];//ID3头部校验，必须为“ID3”否则认为不存在ID3标签
	byte  major;	//ID3版本号，3是ID3v2.3，4是ID3v2.4，以此类推
	byte  revsion;	//ID3副版本号，此版本为00
	byte  flags;    //标志位
	byte  size[4];	//标签大小，不含标签头的10个字节
}ID3V2Header;

//ID3v2标签帧头部结构体定义
typedef struct
{
	char FrameId[4];//标识符，用于描述此标签帧的内容类型
	byte size[4];	//标签帧的大小，不含标签头的10个字节  
	byte flags[2];	//标志位  
}ID3V2FrameHeader;

//检测图片格式，参数1：数据，参数2：指向存放文件格式（扩展名）的指针，返回值：是否成功（不是图片则失败）
bool verificationPictureFormat(char *data, char *format = 0)
{
	char fmt[4] = {};
	//支持格式：JPEG/PNG/BMP/GIF
	byte jpeg[2] = { 0xff, 0xd8 };
	byte png[8] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };
	byte gif[6] = { 0x47, 0x49, 0x46, 0x38, 0x39, 0x61 };
	byte gif2[6] = { 0x47, 0x49, 0x46, 0x38, 0x37, 0x61 };
	byte bmp[2] = { 0x42, 0x4d };
	if (memcmp(data, &jpeg, 2) == 0)
	{
		strcpy(fmt, "jpg");
	} 
	else if (memcmp(data, &png, 8) == 0)
	{
		strcpy(fmt, "png");
	}
	else if (memcmp(data, &gif, 6) == 0 || memcpy(data, &gif2, 6) == 0)
	{
		strcpy(fmt, "gif");
	}
	else if (memcmp(data, &bmp, 2) == 0)
	{
		strcpy(fmt, "bmp");
	}
	else
	{
		return false;
	}

	if (format)
	{
		strcpy(format, fmt);
	}

	return true;
}

//提取图片文件，参数1：输入文件，参数2：输出文件，返回值：是否成功
bool extractPicture(const char *inFilePath, const char *outFilePath)
{
	FILE *fp = NULL;				//初始化文件指针，置空
	fp = fopen(inFilePath, "rb");	//以只读&二进制方式打开文件
	if (!fp)						//如果打开失败
	{
		fp = NULL;
		return false;
	}
	fseek(fp, 0, SEEK_SET);			//设文件流指针到文件头部（印象中打开之后默认在尾部）

	//读取
	ID3V2Header id3v2h;				//创建一个ID3v2标签头结构体
	memset(&id3v2h, 0, 10);			//内存填0，10个字节
	fread(&id3v2h, 10, 1, fp);		//把文件头部10个字节写入结构体内存

	//文件头识别
	if (strncmp(id3v2h.identi, "ID3", 3) != 0)//这里“ID3”字符需要正确的文字编码？ UTF-8和ASCII没有区别不必在意
	{
		fclose(fp);
		fp = NULL;
		return false;
	}
	
	//能运行到这里应该已经成功打开文件了

	//计算整个标签长度，每个字节仅7位有效
	int tagTotalLength = (id3v2h.size[0] & 0x7f) * 0x200000 + (id3v2h.size[1] & 0x7f) * 0x4000 + (id3v2h.size[2] & 0x7f) * 0x80 + (id3v2h.size[3] & 0x7f);

	ID3V2FrameHeader id3v2fh;		//创建一个ID3v2标签帧头结构体
	memset(&id3v2fh, 0, 10);

	if (id3v2h.major == 3)	//ID3v2.3
	{
		fread(&id3v2fh, 10, 1, fp);				//将数据写到ID3V2FrameHeader结构体中
		int curDataLength = 10;					//存放当前已经读取的数据大小
		while ((strncmp(id3v2fh.FrameId, "APIC", 4) != 0))//如果帧头没有APIC标识符则循环执行
		{
			if (curDataLength > tagTotalLength)
			{
				fclose(fp);
				fp = NULL;
				return false;					//未发现图片数据
			}
			//计算帧数据长度
			int frameLength = id3v2fh.size[0] * 0x1000000 + id3v2fh.size[1] * 0x10000 + id3v2fh.size[2] * 0x100 + id3v2fh.size[3];
			fseek(fp, frameLength, SEEK_CUR);	//向前跳跃到下一个帧头
			memset(&id3v2fh, 0, 10);			//清除帧头结构体数据
			fread(&id3v2fh, 10, 1, fp);			//重新读取数据
			curDataLength += frameLength + 10;		//记录当前所在的ID3标签位置，以便退出循环
		}

		//计算一下当前图片帧的数据长度
		int frameLength = id3v2fh.size[0] * 0x1000000 + id3v2fh.size[1] * 0x10000 + id3v2fh.size[2] * 0x100 + id3v2fh.size[3];
		
		/*
		这是ID3v2.3图片帧的结构：

		<Header for 'Attached picture', ID: "APIC">
		头部10个字节的帧头

		Text encoding      $xx
		要跳过一个字节（文字编码）

		MIME type          <text string> $00
		跳过（文本 + /0），这里可得到文件格式

		Picture type       $xx
		跳过一个字节（图片类型）

		Description        <text string according to encoding> $00 (00)
		跳过（文本 + /0），这里可得到描述信息

		Picture data       <binary data>
		这是真正的图片数据
		*/
		int nonPicDataLength = 0;	//非图片数据的长度
		fseek(fp, 1, SEEK_CUR);		//信仰之跃
		nonPicDataLength++;

		char tempData[20] = {};		//临时存放数据的空间
		char mimeType[20] = {};		//图片类型
		int mimeTypeLength = 0;		//图片类型文本长度

		fread(&tempData, 20, 1, fp);//取得一小段数据
		fseek(fp, -20, SEEK_CUR);	//回到原位

		strcpy(mimeType, tempData);				//复制出一个字符串
		mimeTypeLength = strlen(mimeType) + 1;	//测试字符串长度，补上末尾00
		fseek(fp, mimeTypeLength, SEEK_CUR);	//跳到此数据之后
		nonPicDataLength += mimeTypeLength;		//记录长度

		fseek(fp, 1, SEEK_CUR);		//再一次信仰之跃
		nonPicDataLength++;

		int temp = 0;				//记录当前字节数据的变量
		fread(&temp, 1, 1, fp);		//读取一个字节
		nonPicDataLength++;			//+1
		while (temp)				//循环到temp为0
		{
			fread(&temp, 1, 1, fp);	//如果不是0继续读一字节的数据
			nonPicDataLength++;		//计数
		}
		//跳过了Description文本，以及末尾的\0

		//非主流情况检测
		memset(tempData, 0, 20);
		fread(&tempData, 8, 1, fp);
		fseek(fp, -8, SEEK_CUR);	//回到原位
		//判断40次，一位一位跳到文件头
		bool ok = false;			//是否正确识别出文件头
		for (int i = 0; i < 40; i++)
		{
			if (verificationPictureFormat(tempData, 0))
			{
				ok = true;
				break;
			}
			else
			{
				fseek(fp, 1, SEEK_CUR);
				nonPicDataLength++;
				fread(&tempData, 8, 1, fp);
				fseek(fp, -8, SEEK_CUR);
			}
		}

		if (!ok)
		{
			return false;			//无法识别的数据
		}

		int picLength = frameLength - nonPicDataLength;	//计算图片数据长度
		byte *pPicData = new byte[picLength];			//动态分配图片数据内存空间
		memset(pPicData, 0, picLength);					//清空图片数据内存
		fread(pPicData, picLength, 1, fp);				//得到图片数据
		fclose(fp);										//搞定，关闭文件。

		fp = fopen(outFilePath, "wb");//打开目标文件
		fwrite(pPicData, picLength, 1, fp);//写入文件
		delete []pPicData;//回收内存
		fclose(fp);//关闭
		//printf("文件类型：%s", &mimeType);
	}
	else if (id3v2h.major == 4)
	{
		//ID3v2.4
		fclose(fp);//关闭
	}
	else if (id3v2h.major == 2)
	{
		//ID3v2.2
		fclose(fp);//关闭
	}
	else
	{
		//其余不支持的版本
		fclose(fp);//关闭
		return false;
	}
	return true;
}
#endif
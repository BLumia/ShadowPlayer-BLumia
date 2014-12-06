/*
ID3v2��ǩͼƬ��ȡ
ShadowPower
Ŀǰ�����ID3v2.3
*/
#ifndef _ShadowPower_ID3V2PIC___
#define _ShadowPower_ID3V2PIC___

#define _CRT_SECURE_NO_WARNINGS //VS��˵���

#ifndef NULL
#define NULL 0
#endif
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef unsigned char byte;
using namespace std;

//ID3v2��ǩͷ���ṹ�嶨��
typedef struct
{
	char  identi[3];//ID3ͷ��У�飬����Ϊ��ID3��������Ϊ������ID3��ǩ
	byte  major;	//ID3�汾�ţ�3��ID3v2.3��4��ID3v2.4���Դ�����
	byte  revsion;	//ID3���汾�ţ��˰汾Ϊ00
	byte  flags;    //��־λ
	byte  size[4];	//��ǩ��С��������ǩͷ��10���ֽ�
}ID3V2Header;

//ID3v2��ǩ֡ͷ���ṹ�嶨��
typedef struct
{
	char FrameId[4];//��ʶ�������������˱�ǩ֡����������
	byte size[4];	//��ǩ֡�Ĵ�С��������ǩͷ��10���ֽ�  
	byte flags[2];	//��־λ  
}ID3V2FrameHeader;

//���ͼƬ��ʽ������1�����ݣ�����2��ָ�����ļ���ʽ����չ������ָ�룬����ֵ���Ƿ�ɹ�������ͼƬ��ʧ�ܣ�
bool verificationPictureFormat(char *data, char *format = 0)
{
	char fmt[4] = {};
	//֧�ָ�ʽ��JPEG/PNG/BMP/GIF
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

//��ȡͼƬ�ļ�������1�������ļ�������2������ļ�������ֵ���Ƿ�ɹ�
bool extractPicture(const char *inFilePath, const char *outFilePath)
{
	FILE *fp = NULL;				//��ʼ���ļ�ָ�룬�ÿ�
	fp = fopen(inFilePath, "rb");	//��ֻ��&�����Ʒ�ʽ���ļ�
	if (!fp)						//�����ʧ��
	{
		fp = NULL;
		return false;
	}
	fseek(fp, 0, SEEK_SET);			//���ļ���ָ�뵽�ļ�ͷ����ӡ���д�֮��Ĭ����β����

	//��ȡ
	ID3V2Header id3v2h;				//����һ��ID3v2��ǩͷ�ṹ��
	memset(&id3v2h, 0, 10);			//�ڴ���0��10���ֽ�
	fread(&id3v2h, 10, 1, fp);		//���ļ�ͷ��10���ֽ�д��ṹ���ڴ�

	//�ļ�ͷʶ��
	if (strncmp(id3v2h.identi, "ID3", 3) != 0)//���ID3���ַ���Ҫ��ȷ�����ֱ��룿 UTF-8��ASCIIû�����𲻱�����
	{
		fclose(fp);
		fp = NULL;
		return false;
	}
	
	//�����е�����Ӧ���Ѿ��ɹ����ļ���

	//����������ǩ���ȣ�ÿ���ֽڽ�7λ��Ч
	int tagTotalLength = (id3v2h.size[0] & 0x7f) * 0x200000 + (id3v2h.size[1] & 0x7f) * 0x4000 + (id3v2h.size[2] & 0x7f) * 0x80 + (id3v2h.size[3] & 0x7f);

	ID3V2FrameHeader id3v2fh;		//����һ��ID3v2��ǩ֡ͷ�ṹ��
	memset(&id3v2fh, 0, 10);

	if (id3v2h.major == 3)	//ID3v2.3
	{
		fread(&id3v2fh, 10, 1, fp);				//������д��ID3V2FrameHeader�ṹ����
		int curDataLength = 10;					//��ŵ�ǰ�Ѿ���ȡ�����ݴ�С
		while ((strncmp(id3v2fh.FrameId, "APIC", 4) != 0))//���֡ͷû��APIC��ʶ����ѭ��ִ��
		{
			if (curDataLength > tagTotalLength)
			{
				fclose(fp);
				fp = NULL;
				return false;					//δ����ͼƬ����
			}
			//����֡���ݳ���
			int frameLength = id3v2fh.size[0] * 0x1000000 + id3v2fh.size[1] * 0x10000 + id3v2fh.size[2] * 0x100 + id3v2fh.size[3];
			fseek(fp, frameLength, SEEK_CUR);	//��ǰ��Ծ����һ��֡ͷ
			memset(&id3v2fh, 0, 10);			//���֡ͷ�ṹ������
			fread(&id3v2fh, 10, 1, fp);			//���¶�ȡ����
			curDataLength += frameLength + 10;		//��¼��ǰ���ڵ�ID3��ǩλ�ã��Ա��˳�ѭ��
		}

		//����һ�µ�ǰͼƬ֡�����ݳ���
		int frameLength = id3v2fh.size[0] * 0x1000000 + id3v2fh.size[1] * 0x10000 + id3v2fh.size[2] * 0x100 + id3v2fh.size[3];
		
		/*
		����ID3v2.3ͼƬ֡�Ľṹ��

		<Header for 'Attached picture', ID: "APIC">
		ͷ��10���ֽڵ�֡ͷ

		Text encoding      $xx
		Ҫ����һ���ֽڣ����ֱ��룩

		MIME type          <text string> $00
		�������ı� + /0��������ɵõ��ļ���ʽ

		Picture type       $xx
		����һ���ֽڣ�ͼƬ���ͣ�

		Description        <text string according to encoding> $00 (00)
		�������ı� + /0��������ɵõ�������Ϣ

		Picture data       <binary data>
		����������ͼƬ����
		*/
		int nonPicDataLength = 0;	//��ͼƬ���ݵĳ���
		fseek(fp, 1, SEEK_CUR);		//����֮Ծ
		nonPicDataLength++;

		char tempData[20] = {};		//��ʱ������ݵĿռ�
		char mimeType[20] = {};		//ͼƬ����
		int mimeTypeLength = 0;		//ͼƬ�����ı�����

		fread(&tempData, 20, 1, fp);//ȡ��һС������
		fseek(fp, -20, SEEK_CUR);	//�ص�ԭλ

		strcpy(mimeType, tempData);				//���Ƴ�һ���ַ���
		mimeTypeLength = strlen(mimeType) + 1;	//�����ַ������ȣ�����ĩβ00
		fseek(fp, mimeTypeLength, SEEK_CUR);	//����������֮��
		nonPicDataLength += mimeTypeLength;		//��¼����

		fseek(fp, 1, SEEK_CUR);		//��һ������֮Ծ
		nonPicDataLength++;

		int temp = 0;				//��¼��ǰ�ֽ����ݵı���
		fread(&temp, 1, 1, fp);		//��ȡһ���ֽ�
		nonPicDataLength++;			//+1
		while (temp)				//ѭ����tempΪ0
		{
			fread(&temp, 1, 1, fp);	//�������0������һ�ֽڵ�����
			nonPicDataLength++;		//����
		}
		//������Description�ı����Լ�ĩβ��\0

		//������������
		memset(tempData, 0, 20);
		fread(&tempData, 8, 1, fp);
		fseek(fp, -8, SEEK_CUR);	//�ص�ԭλ
		//�ж�40�Σ�һλһλ�����ļ�ͷ
		bool ok = false;			//�Ƿ���ȷʶ����ļ�ͷ
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
			return false;			//�޷�ʶ�������
		}

		int picLength = frameLength - nonPicDataLength;	//����ͼƬ���ݳ���
		byte *pPicData = new byte[picLength];			//��̬����ͼƬ�����ڴ�ռ�
		memset(pPicData, 0, picLength);					//���ͼƬ�����ڴ�
		fread(pPicData, picLength, 1, fp);				//�õ�ͼƬ����
		fclose(fp);										//�㶨���ر��ļ���

		fp = fopen(outFilePath, "wb");//��Ŀ���ļ�
		fwrite(pPicData, picLength, 1, fp);//д���ļ�
		delete []pPicData;//�����ڴ�
		fclose(fp);//�ر�
		//printf("�ļ����ͣ�%s", &mimeType);
	}
	else if (id3v2h.major == 4)
	{
		//ID3v2.4
		fclose(fp);//�ر�
	}
	else if (id3v2h.major == 2)
	{
		//ID3v2.2
		fclose(fp);//�ر�
	}
	else
	{
		//���಻֧�ֵİ汾
		fclose(fp);//�ر�
		return false;
	}
	return true;
}
#endif
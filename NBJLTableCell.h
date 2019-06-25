#ifndef __NBJL_TableCell_H__
#define __NBJL_TableCell_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "HNNetExport.h"
#include "NBJLMessageHead.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;
using namespace extension;

namespace NBJL
{
	/// ���б�ṹ
	struct DownLeftStruct
	{
		bool	bRefresh;			//�Ƿ�ˢ��
		BYTE	ZiVaule[6];			//��ֵ  һ����6��
		DownLeftStruct()
		{
			memset(this, 0, sizeof(DownLeftStruct));
		}
	};
	//Ȧ�б��ϰ벿�ִ�·�����ƽṹ
	struct DownRightDaLuStruct
	{
		bool	bRefresh;			    //�Ƿ�ˢ��
		bool	bLastHe;			    //���һ���Ƿ�Ϊ�ͣ�����֮ǰ��ʣ�����ݣ�
		vector<BYTE>	QuanVaule;		//��·Ȧֵ
		DownRightDaLuStruct()
		{
			memset(this, 0, sizeof(DownRightDaLuStruct));
		}
	};

	//���б�
	class DownLeftItemCell :public TableViewCell
	{
	public:
		static DownLeftItemCell* create();
	public:
		void bulidCell(DownLeftStruct DownLeftInfo);

	private:
		Layout* _layout;

		DrawNode* drawNode= nullptr;          //���ƹ���
	private:
		void drawRedPoint(int idx);             //����һ����ɫ��  ��ͼƬ�����Ͻ�

		void drawBluePoint(int idx);            //����һ����ɫ��  ��ͼƬ�����½�

		void drawRedAndBluePoint(int idx);      //���ƺ죬��ɫ��������
	};
	//��·Ȧ�б�
	class DownRightDaLuItemCell :public TableViewCell
	{
	public:
		static DownRightDaLuItemCell* create();
	public:
		void bulidCell(struct DownRightDaLuStruct  DownRightInfo);
	private:
		Layout* _layout;
		DrawNode* drawNode = nullptr;           //���ƹ���
		Text*   text_he = nullptr;              //��������text ��ʾ��
	private:
		void drawRedPoint(int idx);             //����һ����ɫ��  �����Ͻ�

		void drawBluePoint(int idx);            //����һ����ɫ��  �����½�

		void drawRedAndBluePoint(int idx);      //���ƺ죬��ɫ��������

		void drawRedRound(int idx);             //����һ����ɫȦ  

		void drawBlueRound(int idx);            //����һ����ɫȦ  
	};

	//������Ȧ�б�
	class DownRightDaYanZaiItemCell :public TableViewCell
	{
	public:
		static DownRightDaYanZaiItemCell* create();
	public:
		void bulidCell(struct DownRightDaLuStruct  DownRightInfo);
	private:
		Layout* _layout;
		DrawNode* drawNode = nullptr;           //���ƹ���
		Text*   text_he = nullptr;              //��������text ��ʾ��
	private:
	    
		void drawRedRound(int x);            //����һ����ɫȦ  

		void drawBlueRound(int x);            //����һ����ɫȦ  
	};

	//С·Ȧ�б�
	class DownRightXiaoLuItemCell :public TableViewCell
	{
	public:
		static DownRightXiaoLuItemCell* create();
	public:
		void bulidCell(struct DownRightDaLuStruct  DownRightInfo);
	private:
		Layout* _layout;
		DrawNode* drawNode = nullptr;           //���ƹ���
		Text*   text_he = nullptr;              //��������text ��ʾ��
	private:

		void drawRedDot(int idx);            //����һ����ɫȦ  

		void drawBlueDot(int idx);            //����һ����ɫȦ  
	};

	//���·Ȧ�б�
	class DownRightZhangLangItemCell :public TableViewCell
	{
	public:
		static DownRightZhangLangItemCell* create();
	public:
		void bulidCell(struct DownRightDaLuStruct  DownRightInfo);
	private:
		Layout* _layout;
		DrawNode* drawNode = nullptr;           //���ƹ���
		Text*   text_he = nullptr;              //��������text ��ʾ��
	private:

		void drawRedLine(int idx);
		void drawBlueLine(int idx);            //����һ����ɫȦ  
	};
}
#endif // __NBJL_TableCell_H__
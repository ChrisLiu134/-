#ifndef __NBJLPaiLu_h__
#define __NBJLPaiLu_h__

#include "NBJLMessageHead.h"
#include "HNUIExport.h"
#include "cocos2d.h"
#include <vector>
#include "NBJLpaiLuDelegate.h"
USING_NS_CC;

namespace NBJL
{
	class NBJLPaiLu : public HNLayer
	{
	public:
		static NBJLPaiLu* create(vector<LuziData> luZiDatas);
		bool init(vector<LuziData> luZiDatas);

		NBJLPaiLu();
		virtual ~NBJLPaiLu();
   
		typedef std::function<void()> CloseCallBack;
		CloseCallBack	onCloseCallBack = nullptr;
	private: //�м�����ݲ�
		Layout*       leftTableView               = nullptr;         //��ߵ����б���
		Layout*       rightDaluTableView          = nullptr;         //�ұ��ϰ벿�ֵĴ�· ����

		//��·�Ӵ�
		TableView*    _DownLeftTable              = nullptr;         //��ߵ��ִ���
		TableView*    _DownRightDaluTable             = nullptr;         //�ұߵ��ϰ벿�ִ���

		//��·����
		PaiLuLeftDelegate*       _DownLeftDelegate            = nullptr;     //��ߵ��ִ����������
		PaiLuRightDaLuDelegate*  _DownRightDaluDelegate       = nullptr;     //�ұߵ��ϰ벿�ִ�����Ĵ�·����

	private:  //�����в�
		Layout*       rightDaYanZaiView = nullptr;                        //�ұߵĴ����в�
		//��·�Ӵ�
		TableView*    _DownRightDaYanZaiTable = nullptr;                  //�ұߵĴ����д���
		//��·����
		PaiLuRighDaYanZaiDelegate*       _DownRightDaYanZaiDelegate = nullptr;     //��ߵ��ִ����������

	private:  //С·��
		Layout*       rightXiaoLuView = nullptr;                        //�ұߵĴ����в�
		//��·�Ӵ�
		TableView*    _DownRightXiaoLuTable = nullptr;                  //�ұߵĴ����д���
		//��·����
		PaiLuRighXiaoLuDelegate*       _DownRightXiaoLuDelegate = nullptr;     //��ߵ��ִ����������

	private:  //���·��
		Layout*       rightZhangLangView = nullptr;                        //�ұߵĴ����в�
		//��·�Ӵ�
		TableView*    _DownRightZhangLangTable = nullptr;                  //�ұߵĴ����д���
		//��·����
		PaiLuRighZhangLangDelegate*       _DownRightZhangLangDelegate = nullptr;     //��ߵ��ִ����������
	private:   // top ��
		ImageView*   image_top                   = nullptr;         //����top��
		Text*        zhuang_win                  = nullptr;         //ׯӮ�ľ���
		Text*        xian_win                    = nullptr;         //ׯӮ�ľ���
		Text*        he                          = nullptr;         //ׯӮ�ľ���
		Text*        gameCount                   = nullptr;         //��ǰ��Ϸ����   
		ImageView*   quanZhuang                  = nullptr;         //������ ��һ�ֿ�ׯ����ʾ
		ImageView*   dianZhuang                  = nullptr;         //С· ��һ�ֿ�ׯ����ʾ
		ImageView*   xianZhuang                  = nullptr;         //���· ��һ�ֿ�ׯ����ʾ
		
		ImageView*   quanXian                    = nullptr;         //������ ��һ�ֿ�ׯ����ʾ
		ImageView*   dianXian                    = nullptr;         //С· ��һ�ֿ�ׯ����ʾ
		ImageView*   xianXian                    = nullptr;         //���· ��һ�ֿ�ׯ����ʾ
	public:
		void isShow(bool isShow);   //�����Ƿ���ʾ

		void refreshLuZiData(vector<LuziData> luZiDatas);
	};
}

#endif // __NBJLPaiLu_h__

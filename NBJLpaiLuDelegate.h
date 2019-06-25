#ifndef __NBJL_paiLuDelegate_H__
#define __NBJL_paiLuDelegate_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include <vector>
#include "HNUIExport.h"
#include "NBJLTableCell.h"
#include "NBJLMessageHead.h"
#include <string>
USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;
using namespace extension;

namespace NBJL
{
	struct HePos
	{
		int x = 0;
		int y = 0;
	};

	class PaiLuLeftDelegate :public TableViewDelegate   //������б�
		,public TableViewDataSource
	{
	public:
		PaiLuLeftDelegate();
		~PaiLuLeftDelegate();
		/* ����ʵ�ֵĺ��� */
		// ������tableviewʱ�����÷��� ����Ϊ��ǰ��tableview����
		virtual void scrollViewDidScroll(ui::ScrollView* view) {};
		// ��tableview���Ŵ����Сʱ�����÷���  ����Ϊ��ǰtableview����
		virtual void scrollViewDidZoom(ui::ScrollView* view) {}
		// ��cell�����ʱ���ø÷��� ����Ϊ��ǰ��tableview�����뱻�����cell����
		virtual void tableCellTouched(TableView* table, TableViewCell* cell){};
		// ����tableview��Cell��С
		virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
		// ��ȡ���Ϊidx��cell
		virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
		// ����tableview��cell�ĸ���
		virtual ssize_t numberOfCellsInTableView(TableView *table);

		//����������
		void setAllResultData(vector<BYTE> AllResultData);
	private:
		
		vector<BYTE> _AllLeftResultData;//���н������     ���б��е��������ݣ������� //�м�Ӯ //ׯ��Ӯ //�� //��Ӯ�ж��� //��Ӯׯ����//ׯӮׯ����//ׯӮ�ж��� //�ж���ׯ������Ӯ//�ж���ׯ����ׯӮ

	};
	class PaiLuRightDaLuDelegate :public TableViewDelegate   //Ȧ�б� ��·
		, public TableViewDataSource
	{
	public:
		PaiLuRightDaLuDelegate();
		~PaiLuRightDaLuDelegate();
		/* ����ʵ�ֵĺ��� */
		// ������tableviewʱ�����÷��� ����Ϊ��ǰ��tableview����
		virtual void scrollViewDidScroll(ui::ScrollView* view) {};
		// ��tableview���Ŵ����Сʱ�����÷���  ����Ϊ��ǰtableview����
		virtual void scrollViewDidZoom(ui::ScrollView* view) {}
		// ��cell�����ʱ���ø÷��� ����Ϊ��ǰ��tableview�����뱻�����cell����
		virtual void tableCellTouched(TableView* table, TableViewCell* cell){};
		// ����tableview��Cell��С
		virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
		// ��ȡ���Ϊidx��cell
		virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
		// ����tableview��cell�ĸ���
		virtual ssize_t numberOfCellsInTableView(TableView *table);

		//����������
		void setAllResultData(vector<BYTE> AllResultData);
		//��ȡ�������ݵĴ�С
		int getClassResultDataSize();

	private:
		//ˢ�¶�ά���� ������������ �����ݹ���
		void refreshArray();
		//�ж����ͣ�������һ�������Ƿ�Ҫ���뱾����
		int determineType(int num);
		//������ʱ��������ݣ�����Щ���ݼ��뵽��ά�����С�
		void disposeTempData(int idx ,vector<BYTE> nums);
		//�����������ݡ�
		void exportData();

	private:
		vector<BYTE>			_AllRightDaLuResultData;	//���н������
		vector<vector<BYTE>>	_ClassResultData;		    //�Ѿ��ֺ����ź��򱣴������

		
		int dataArray[80][6] = {};              //��ά���� �����������
		
		vector<HePos> heList;               //�����Ѻ͵�λ�ô�����
	};

	class PaiLuRighDaYanZaiDelegate :public TableViewDelegate   //Ȧ�б������·
		, public TableViewDataSource
	{
	public:
		PaiLuRighDaYanZaiDelegate();
		~PaiLuRighDaYanZaiDelegate();
		/* ����ʵ�ֵĺ��� */
		// ������tableviewʱ�����÷��� ����Ϊ��ǰ��tableview����
		virtual void scrollViewDidScroll(ui::ScrollView* view) {};
		// ��tableview���Ŵ����Сʱ�����÷���  ����Ϊ��ǰtableview����
		virtual void scrollViewDidZoom(ui::ScrollView* view) {}
		// ��cell�����ʱ���ø÷��� ����Ϊ��ǰ��tableview�����뱻�����cell����
		virtual void tableCellTouched(TableView* table, TableViewCell* cell){};
		// ����tableview��Cell��С
		virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
		// ��ȡ���Ϊidx��cell
		virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
		// ����tableview��cell�ĸ���
		virtual ssize_t numberOfCellsInTableView(TableView *table);

		//����������
		void setAllResultData(vector<BYTE> AllResultData);
		//��ȡ�������ݵĴ�С
		int getClassResultDataSize();

	private:
		//ˢ�¶�ά���� ������������ �����ݹ���
		void refreshArray();
		//�ж����ͣ�������һ�������Ƿ�Ҫ���뱾����
		int determineType(int num);
		//�������������Լ��ĺ������У����뵽һ�� byte������
		vector<BYTE> analyzeDayYanZaiRedAndBlue(vector<vector<BYTE>> temps);
		//��������еĺ������ݣ�����Щ���ݼ��뵽��ά�����С�
		void disposeTempData(int idx, vector<BYTE> nums);
		//�����������ݡ�
		void exportData();

		
	private:
		vector<BYTE>			_AllRightDaLuResultData;	//�ӷ������ϻ�ȡ�����н������
		vector<vector<BYTE>>	_tempDataList;		        //��ź������е����ݼ���
		vector<vector<BYTE>>	_ClassResultData;		    //�Ѿ��ֺ����ź��򱣴������

		int dataArray[80][6] = {};              //��ά���� �����������

	public:
		//��������·�㷨���õ������Ҫ�Ƚϵ��������е���Ϣ��Ȼ�� ���һ��ׯ������һ����Ӯ��ȥ��������ɫ����ʲô��
		int judgeRedOrBlue(vector<BYTE>frist, vector<BYTE>scend, int type);
		
		int nextZhuang = 0;   //����������һ�ֿ�ׯ������
		int nextXian = 0;     //����������һ�ֿ��͵�����

		int getNextZhuang();   //������һ�ֿ�ׯ�ĺ������
		int getNextXian();     //������һ�ֿ��еĺ������
	};

	class PaiLuRighXiaoLuDelegate :public TableViewDelegate   //Ȧ�б�С·
		, public TableViewDataSource
	{
	public:
		PaiLuRighXiaoLuDelegate();
		~PaiLuRighXiaoLuDelegate();
		/* ����ʵ�ֵĺ��� */
		// ������tableviewʱ�����÷��� ����Ϊ��ǰ��tableview����
		virtual void scrollViewDidScroll(ui::ScrollView* view) {};
		// ��tableview���Ŵ����Сʱ�����÷���  ����Ϊ��ǰtableview����
		virtual void scrollViewDidZoom(ui::ScrollView* view) {}
		// ��cell�����ʱ���ø÷��� ����Ϊ��ǰ��tableview�����뱻�����cell����
		virtual void tableCellTouched(TableView* table, TableViewCell* cell){};
		// ����tableview��Cell��С
		virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
		// ��ȡ���Ϊidx��cell
		virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
		// ����tableview��cell�ĸ���
		virtual ssize_t numberOfCellsInTableView(TableView *table);

		//����������
		void setAllResultData(vector<BYTE> AllResultData);
		//��ȡ�������ݵĴ�С
		int getClassResultDataSize();

	private:
		//ˢ�¶�ά���� ������������ �����ݹ���
		void refreshArray();
		//�ж����ͣ�������һ�������Ƿ�Ҫ���뱾����
		int determineType(int num);
		//������С·�Լ��ĺ������У����뵽һ�� byte������
		vector<BYTE> analyzeXiaoLuRedAndBlue(vector<vector<BYTE>> temps);
		//������ʱ��������ݣ�����Щ���ݼ��뵽��ά�����С�
		void disposeTempData(int idx, vector<BYTE> nums);
		//�����������ݡ�
		void exportData();
	private:
		vector<BYTE>			_AllRightDaLuResultData;	//�ӷ������ϻ�ȡ�����н������
		vector<vector<BYTE>>	_tempDataList;		        //��ź������е����ݼ���
		vector<vector<BYTE>>	_ClassResultData;		    //�Ѿ��ֺ����ź��򱣴������

		int dataArray[80][6] = {};              //��ά���� �����������

	public:
		//��������·�㷨���õ������Ҫ�Ƚϵ��������е���Ϣ��Ȼ�� ���һ��ׯ������һ����Ӯ��ȥ��������ɫ����ʲô��
		int judgeRedOrBlue(vector<BYTE>frist, vector<BYTE>scend, int type);

		int nextZhuang = 0;   //����������һ�ֿ�ׯ������
		int nextXian = 0;     //����������һ�ֿ��͵�����

		int getNextZhuang();   //������һ�ֿ�ׯ�ĺ������
		int getNextXian();     //������һ�ֿ��еĺ������
	};

	class PaiLuRighZhangLangDelegate :public TableViewDelegate   //Ȧ�б����·
		, public TableViewDataSource
	{
	public:
		PaiLuRighZhangLangDelegate();
		~PaiLuRighZhangLangDelegate();
		/* ����ʵ�ֵĺ��� */
		// ������tableviewʱ�����÷��� ����Ϊ��ǰ��tableview����
		virtual void scrollViewDidScroll(ui::ScrollView* view) {};
		// ��tableview���Ŵ����Сʱ�����÷���  ����Ϊ��ǰtableview����
		virtual void scrollViewDidZoom(ui::ScrollView* view) {}
		// ��cell�����ʱ���ø÷��� ����Ϊ��ǰ��tableview�����뱻�����cell����
		virtual void tableCellTouched(TableView* table, TableViewCell* cell){};
		// ����tableview��Cell��С
		virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
		// ��ȡ���Ϊidx��cell
		virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
		// ����tableview��cell�ĸ���
		virtual ssize_t numberOfCellsInTableView(TableView *table);

		//����������
		void setAllResultData(vector<BYTE> AllResultData);
		//��ȡ�������ݵĴ�С
		int getClassResultDataSize();

	private:
		//ˢ�¶�ά���� ������������ �����ݹ���
		void refreshArray();
		//�ж����ͣ�������һ�������Ƿ�Ҫ���뱾����
		int determineType(int num);
		//���������·�Լ��ĺ������У����뵽һ�� byte������
		vector<BYTE> analyzeXiaoLuRedAndBlue(vector<vector<BYTE>> temps);
		//������ʱ��������ݣ�����Щ���ݼ��뵽��ά�����С�
		void disposeTempData(int idx, vector<BYTE> nums);
		//�����������ݡ�
		void exportData();
	private:
		vector<BYTE>			_AllRightDaLuResultData;	//�ӷ������ϻ�ȡ�����н������
		vector<vector<BYTE>>	_tempDataList;		        //��ź������е����ݼ���
		vector<vector<BYTE>>	_ClassResultData;		    //�Ѿ��ֺ����ź��򱣴������

		int dataArray[80][6] = {};              //��ά���� �����������
	public:
		//��������·�㷨���õ������Ҫ�Ƚϵ��������е���Ϣ��Ȼ�� ���һ��ׯ������һ����Ӯ��ȥ��������ɫ����ʲô��
		int judgeRedOrBlue(vector<BYTE>frist, vector<BYTE>scend, int type);

		int nextZhuang = 0;   //����������һ�ֿ�ׯ������
		int nextXian = 0;     //����������һ�ֿ��͵�����

		int getNextZhuang();   //������һ�ֿ�ׯ�ĺ������
		int getNextXian();     //������һ�ֿ��еĺ������
	};
}
#endif //__NBJL_paiLuDelegate_H__

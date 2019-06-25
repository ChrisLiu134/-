#include "NBJLpaiLuDelegate.h"

namespace NBJL
{
	/*******************���б�******************/
	PaiLuLeftDelegate::PaiLuLeftDelegate()
	{

	}
	PaiLuLeftDelegate::~PaiLuLeftDelegate()
	{

	}
	Size PaiLuLeftDelegate::tableCellSizeForIndex(TableView *table, ssize_t idx)
	{
		return CCSizeMake(50, 300);
	}

	TableViewCell* PaiLuLeftDelegate::tableCellAtIndex(TableView *table, ssize_t idx)
	{
		// �����ö����л�ȡһ��cell Ȼ���ж�cell�Ƿ�Ϊ�� Ϊ���򴴽�һ���µ�
		DownLeftItemCell* cell = dynamic_cast<DownLeftItemCell*>(table->dequeueCell());
		bool isRefresh = cell;//�Ƿ����
		if (!cell)
		{
			cell = DownLeftItemCell::create();
		}
		DownLeftStruct downleftInfo;
		downleftInfo.bRefresh = isRefresh;
		if (!_AllLeftResultData.empty())
		{
			for (int i = 0; i < leftListitemCount; i++)
			{
				if (idx * leftListitemCount + i > _AllLeftResultData.size() - 1)   break;
					
				if (_AllLeftResultData.at(idx * leftListitemCount + i) > 9 || _AllLeftResultData.at(idx * leftListitemCount + i) < 0)
				{
					downleftInfo.ZiVaule[i] = 0;
				}
				else
				{
					downleftInfo.ZiVaule[i] = _AllLeftResultData.at(idx * leftListitemCount + i);
				}
			}
		}
		cell->setIdx(idx);
		cell->bulidCell(downleftInfo);
		return cell;
	}

	ssize_t PaiLuLeftDelegate::numberOfCellsInTableView(TableView *table)
	{
		if (_AllLeftResultData.size() < leftListitemCount * leftListCount)         // ���˵����û����48�����Ͱ�ʣ�µ���0���������ٳ���8������
		{
			for (int i = _AllLeftResultData.size(); i < leftListitemCount * leftListCount; i++)
			{
				_AllLeftResultData.push_back(0);
			}
		}
		if (_AllLeftResultData.size() % leftListitemCount == 0)
		{
			return _AllLeftResultData.size() / leftListitemCount;
		}
		return  _AllLeftResultData.size() / leftListitemCount + 1;

	}
	//����������
	void PaiLuLeftDelegate::setAllResultData(vector<BYTE> AllResultData)
	{
		_AllLeftResultData.clear();
		for (int i = 0; i < AllResultData.size(); i++)
		{
			_AllLeftResultData.push_back(AllResultData.at(i));
		}
	}

	/*******************Ȧ�б��·******************/
	PaiLuRightDaLuDelegate::PaiLuRightDaLuDelegate()
	{

	}
	PaiLuRightDaLuDelegate::~PaiLuRightDaLuDelegate()
	{

	}
	Size PaiLuRightDaLuDelegate::tableCellSizeForIndex(TableView *table, ssize_t idx)
	{
		return CCSizeMake(26, 150);
	}

	TableViewCell* PaiLuRightDaLuDelegate::tableCellAtIndex(TableView *table, ssize_t idx)
	{
		// �����ö����л�ȡһ��cell Ȼ���ж�cell�Ƿ�Ϊ�� Ϊ���򴴽�һ���µ�
		DownRightDaLuItemCell* cell = dynamic_cast<DownRightDaLuItemCell*>(table->dequeueCell());
		bool isRefresh = cell;//�Ƿ����
		if (!cell)
		{
			cell = DownRightDaLuItemCell::create();
		}
		DownRightDaLuStruct downRightDaLu;
		downRightDaLu.bRefresh = isRefresh;
		if (!_ClassResultData.empty())
		{
			downRightDaLu.QuanVaule.assign(_ClassResultData[idx].begin(), _ClassResultData[idx].end());
		}
		cell->setIdx(idx);
		cell->bulidCell(downRightDaLu);
		return cell;
	}

	ssize_t PaiLuRightDaLuDelegate::numberOfCellsInTableView(TableView *table)
	{
		int idx = 0;  //��ǰ��
		vector<BYTE> temp; //��ǰ�Ľ���������ж��ǲ��Ǻ���һ�������ԣ��������Ⱦͻ��С� 
		PailuType  type = None;
		_ClassResultData.clear(); //�����һ�ֱ��������
		heList.clear();  // �����һ�ֺ͵ļ���
		refreshArray();  // ���ö�ά����

		if (_AllRightDaLuResultData.size() <= 0)  return 0;
		for (int i = 0; i < _AllRightDaLuResultData.size();i++)
		{
			//�����У��ߵ�һ��Ԫ�ص�ʱ�����ж���û����һ�����У�Ȼ��ȶ�һ�£��ɲ����Լ���������У���������ԣ���ô�Ͱ���һ�������㵽��ά��������ȥ��Ȼ�������Ȼ���� �� Ȼ��ʼһ���µĶ��У����Ҽ����µĶ��е����͡�
			if (temp.size() > 0)
			{
				if ((PailuType)determineType(_AllRightDaLuResultData[i]) == type || type == PailuType::he || (PailuType)determineType(_AllRightDaLuResultData[i]) == PailuType::he)   
					//���������еĿ�ͷ�Ǻͣ� �������Ͷ����Լ��룬  ��������Ҫ�ж��Ƿ��������.  ����µ�Ԫ���Ǻͣ���ôҲֱ���������������
				{
					if (type == PailuType::he)
					{
						type = (PailuType)determineType(_AllRightDaLuResultData[i]);
					}
					
					temp.push_back(_AllRightDaLuResultData[i]);
				}
				else
				{
					disposeTempData(idx, temp);
					idx++;
					temp.clear();   
				}
			}
			//���û����һ�����У��Ϳ����µĶ���
			if (temp.size() == 0)
			{
				temp.push_back(_AllRightDaLuResultData[i]);
				type = (PailuType)determineType(_AllRightDaLuResultData[i]);
			}
		}

		if (temp.size()>0)   //���һ�����е�ʱ�� ���ܻ�©��
		{
			disposeTempData(idx, temp);
			temp.clear();  
		}

		exportData();
		
		return  _ClassResultData.size();
	}
	//����������
	void PaiLuRightDaLuDelegate::setAllResultData(vector<BYTE> AllResultData)
	{
		_AllRightDaLuResultData.clear();
		for (int i = 0; i < AllResultData.size(); i++)
		{
			_AllRightDaLuResultData.push_back(AllResultData.at(i));
		}
	}

	int PaiLuRightDaLuDelegate::getClassResultDataSize()
	{
		return _ClassResultData.size();
	}

	void PaiLuRightDaLuDelegate::refreshArray()
	{
		memset(dataArray, 0, sizeof(dataArray));
	}

	int PaiLuRightDaLuDelegate::determineType(int num)
	{
		if (num == 1 || num == 4 || num == 5 || num == 8)
		{
			return 1;
		}
		else if (num == 2 || num == 6 || num == 7 || num == 9)
		{
			return 2;
		}
		else if (num == 3)
		{
			return 3;
		}

		return 0;
	}

	void PaiLuRightDaLuDelegate::disposeTempData(int idx, vector<BYTE> nums)
	{

		int i = 0;          //��ǰ�е�λ��   0-5   �������1-6
		int lastI = 0;      //�����������Ǹ��ͼ�¼��
		int lastIdx = idx;  //�����������Ǹ��ͼ�¼��

		for (auto num : nums)
		{
			//��������ҵ��뷨�ǣ� ���� �ж�num�ǲ��Ǻͣ� ����Ǻͣ���ô��ס���ڵ�λ��  x ��y��  ������Ǻͣ���ô��ӵ���ά����������һ�У�1����6�����ߵ����ˣ������ұ����졣 ���������У�����ߵ�֮ǰ�������ˣ���ô�ͼ������Լ����ұ�����
			if (num == 3)  // ����Ǻ͵Ļ�
			{
				HePos  hePos;
				hePos.x = lastIdx;
				hePos.y = lastI;
				heList.push_back(hePos);
			}
			else
			{
				if (i < 6)   // i����С��6
				{
					if (dataArray[idx][i] == 0)   //���iû�е�6���������¿��Լ�����
					{
						lastI = i;         //�������ȸ�ֵ ��++  ������++ǰ��¼
						dataArray[idx][i] = num;
						i++;
					}
					else      //���iû�е�6������λ���Ѿ���ǰ���ռ�ˡ���ôֱ������
					{
						idx++;
						lastIdx = idx;       //��������++��ֵ��������++���¼
						dataArray[idx][lastI] = num;   //�����õ�����һ��i�� ��Ϊi++֮�󣬽����ж��ǲ��ܼ����ߣ���ô����͵ûص���һ��i��
					}
				}
				else   //���˵i��6�ˣ�Ҳ������һ�е�6�������ˣ���ô�����ұ��ߡ�
				{
					idx++;          //��Ϊ����������ƣ� ������Ҫ��ס�ƶ����λ��
					lastIdx = idx;
					if (i == 6 ) 
					{
						i -= 1;
					}
					dataArray[idx][i] = num;
				}
			}
		}
	}

	void PaiLuRightDaLuDelegate::exportData()
	{
		int idx = 0;
		vector<BYTE> temp;
		for (int i = 0; i < 80; i++)
		{
			temp.clear();
			for (int j = 0; j < 6; j++)
			{
				
				if (idx < heList.size() && heList[idx].x == i && heList[idx].y == j)  //��������˺�Ҫ�ѺͲ����ȥ
				{
					temp.push_back(3);
					idx++;                  //��Ϊ���Ǵ������ұ��棬 ��������ֱ�ӰѺ�list���������һ��������ǰ�����жϣ��������Ա���ÿ�ζ�Ҫ������list
					j--;                    //������������Ǻͣ���ô�ͼ��������λ������һ���ͣ�ֱ����Ϊ
				}
				else
				{
					temp.push_back(dataArray[i][j]);
				}
			}
			_ClassResultData.push_back(temp);

			if (i - 4 > 0 && dataArray[i - 4][0] == 0)  //���������4�ſյġ����ϵ���������������ɶ��ٿն���
			{
				break;
			}
		}
	}


	/*******************Ȧ�б������·******************/
	PaiLuRighDaYanZaiDelegate::PaiLuRighDaYanZaiDelegate()
	{

	}
	PaiLuRighDaYanZaiDelegate::~PaiLuRighDaYanZaiDelegate()
	{

	}
	Size PaiLuRighDaYanZaiDelegate::tableCellSizeForIndex(TableView *table, ssize_t idx)
	{
		return CCSizeMake(26, 75);
	}

	TableViewCell* PaiLuRighDaYanZaiDelegate::tableCellAtIndex(TableView *table, ssize_t idx)
	{
		// �����ö����л�ȡһ��cell Ȼ���ж�cell�Ƿ�Ϊ�� Ϊ���򴴽�һ���µ�
		DownRightDaYanZaiItemCell* cell = dynamic_cast<DownRightDaYanZaiItemCell*>(table->dequeueCell());
		bool isRefresh = cell;//�Ƿ����
		if (!cell)
		{
			cell = DownRightDaYanZaiItemCell::create();
		}
		DownRightDaLuStruct downRightDaLu;
		downRightDaLu.bRefresh = isRefresh;
		if (!_ClassResultData.empty() && idx<_ClassResultData.size())
		{
			downRightDaLu.QuanVaule.assign(_ClassResultData[idx].begin(), _ClassResultData[idx].end());
		}

		cell->setIdx(idx);
		cell->bulidCell(downRightDaLu);
		return cell;
	}
	ssize_t PaiLuRighDaYanZaiDelegate::numberOfCellsInTableView(TableView *table)
	{
		refreshArray();
		_ClassResultData.clear();
		_tempDataList.clear();
		if (_AllRightDaLuResultData.size() <= 0) return 0;
		
		vector<BYTE> temp;
		PailuType  type = None;
		for (int i = 0; i < _AllRightDaLuResultData.size(); i++)  //���forѭ���������·�ĺ������
		{
			if (_AllRightDaLuResultData[i] == 3)  continue;  //������ֱ�Ӹɵ�
				
			if (temp.size() > 0)
			{
				if ((PailuType)determineType(_AllRightDaLuResultData[i]) == type)
				{
					temp.push_back(_AllRightDaLuResultData[i]);
				}
				else
				{
					_tempDataList.push_back(temp);
					temp.clear();
				}
			}

			//���û����һ�����У��Ϳ����µĶ���
			if (temp.size() == 0)
			{
				temp.push_back(_AllRightDaLuResultData[i]);
				type  = (PailuType)determineType(_AllRightDaLuResultData[i]);
			}
		}
		if (temp.size() > 0)
		{
			_tempDataList.push_back(temp);
			temp.clear();
		}
		
		//���ȷ�����������·�Լ��ĺ�������
		if (_tempDataList.size() <= 0) return 0;   
		vector<BYTE> tempDatas;
		tempDatas = analyzeDayYanZaiRedAndBlue(_tempDataList);   // ���tempDatas����ֻ�� 1 �� 2

		//ͨ����Ŷ��еļ��ϣ����ж����һ����ׯ���߿��Ͽ��ܳ��ֵ�
		if (_tempDataList.size() > 2)
		{
			nextZhuang = judgeRedOrBlue(_tempDataList[_tempDataList.size() - 2], _tempDataList[_tempDataList.size() - 1], XiaSanLuType::red);
			nextXian = judgeRedOrBlue(_tempDataList[_tempDataList.size() - 2], _tempDataList[_tempDataList.size() - 1], XiaSanLuType::blue);
		}
	
		//Ȼ�����Щ���������ö�ά�������к�
		if (tempDatas.size() <= 0)  return 0;  
		vector<BYTE> temp_1;
		int idx = 0;
		PailuType type_1 = None;
		for (size_t i = 0; i < tempDatas.size(); i++)
		{
			if (temp_1.size() > 0)
			{
				if ((PailuType)determineType(tempDatas[i]) == type_1)
				{
					temp_1.push_back(tempDatas[i]);
				}
				else
				{
					disposeTempData(idx, temp_1);
					temp_1.clear();
					idx++;
				}
			}
			if (temp_1.size() == 0)
			{
				temp_1.push_back(tempDatas[i]);
				type_1 = (PailuType)determineType(tempDatas[i]);
			}
		}

		if (temp_1.size()>0)   //���һ�����е�ʱ�� ���ܻ�©��
		{
			disposeTempData(idx, temp_1);
			temp_1.clear();
		}

		//�ó��������� ���ҷ�������size
		exportData();

		if (_ClassResultData.size() < rightLongListCount)
		{
			return 22; 
		}
		else
		{
			return  _ClassResultData.size();
		}
		
	}
	//����������
	void PaiLuRighDaYanZaiDelegate::setAllResultData(vector<BYTE> AllResultData)
	{
		_AllRightDaLuResultData.clear();
		for (int i = 0; i < AllResultData.size(); i++)
		{
			_AllRightDaLuResultData.push_back(AllResultData.at(i));
		}
	}

	int PaiLuRighDaYanZaiDelegate::getClassResultDataSize()
	{
		return _ClassResultData.size();
	}

	void PaiLuRighDaYanZaiDelegate::refreshArray()
	{
		memset(dataArray, 0, sizeof(dataArray));
	}

	int PaiLuRighDaYanZaiDelegate::determineType(int num)
	{
		if (num == 1 || num == 4 || num == 5 || num == 8)  //���е�
		{
			return 1;
		}
		else if (num == 2 || num == 6 || num == 7 || num == 9)   //��ׯ
		{
			return 2;
		}
		else
		{
			return 0;    // ������· �Ͳ�����
		}

	}

	vector<BYTE> PaiLuRighDaYanZaiDelegate::analyzeDayYanZaiRedAndBlue(vector<vector<BYTE>> temps)
	{
		vector<BYTE> temp;
		if (temps.size() <= 1)  return temp;   //ֻ�е�һ�е�ʱ�� ֱ��return
		if (temps.size() == 2 && temps[1].size() <= 1) return temp;  //���ֻ�����У����ҵڶ��л�ֻ��1����ʱ��return  ��Ϊ�ӵڶ��еڶ��� ��ʼ
		int beforeFrist = -1;//�ȶ�ʱ��һ�е�ǰһ��
		int frist ;  //�ȶ�ʱ��һ��
		int scend = 1;  //�ȶ�ʱ�ĵڶ���
		for ( frist = 0; scend < temps.size() ; frist++, scend++, beforeFrist++)
		{
			//��֣� ֻ�ȶԵ�ǰ�У���ǰһ�У�     ����˵����һ�кͺ�һ��
			int f = temps[frist].size();
			int s = temps[scend].size();

			if (scend > 1)  //�����Ҫ�ȶԵĵڶ������в������������еĵڶ���
			{
				//�������ֻ��һ��Ԫ�ػ���ĳһ�еĵ�һ��Ԫ�أ���ô����ô�ȶ�: ��ǰһ�� + 1 ��ǰǰ�н��бȶԡ�  ����жԣ���������ׯ������Ӧ��д�죬����д�� �� ������ǶԺ���ׯ����ô����д��		
				//������в���ֻ��һ��Ԫ�أ���ô���еĵ�һ��Ԫ����Ҫ���ж�ǰǰ�к�ǰ�е�Ԫ��������Ȼ��ǲ������������
				if (temps[beforeFrist].size() == f)  //��ȣ����������������Ȼ�޶ԣ��޳���  ����д��
				{
					temp.push_back(XiaSanLuType::red);
				}
				else       //�����: ������ͻ������ ���еĵ�һ����ȥ��ǰһ�жԱȣ������жԣ� �����г�ׯ��  ����д��
				{
					temp.push_back(XiaSanLuType::blue);
				}

				if (s == 1)  continue; //����ȶԵĵڶ���ֻ��1��Ԫ�أ���ô�����Ѿ������˶�Ӧ�ĺ���������ֱ��continue�ˡ�

				if (f >= s)  //�ȶԵĵ�һ�бȵڶ��г���������ȵ����
				{
					for (int i = 0; i < s - 1; i++)     //ȥ����һ���Ѿ��ȶԹ���ʣ�µĺ���߶��ܶ��ϣ�����ȫ���Ӻ�
					{
						temp.push_back(XiaSanLuType::red);
					}
				}
				else  //�ȶԵĵڶ��бȵ�һ�г�
				{
					for (int i = 0; i < f - 1; i++)   //���ж��ܶ��ϵ�Ԫ�� д��
					{
						temp.push_back(XiaSanLuType::red);
					}

					temp.push_back(XiaSanLuType::blue);  //��������֮���м����һ���޶Լ���  

					for (int i = 0; i < s - f - 1; i++)   //Ȼ���ж��γ��˳����Ĳ���
					{
						temp.push_back(XiaSanLuType::red);
					}
				}

			}
			else//�����Ҫ�ȶԵĵڶ������иպ����������ϵĵڶ���
			{
				if (s == 1)  //�������ڶ���ֻ��һ��Ԫ��
				{
					continue; //ֱ��continue ���ж�
				}
				else
				{
					if (f >= s)  //�ȶԵĵ�һ�бȵڶ��г���������ȵ����
					{
						for (int i = 0; i < s - 1; i++)     //ȥ����һ���Ѿ��ȶԹ���ʣ�µĺ���߶��ܶ��ϣ�����ȫ���Ӻ�
						{
							temp.push_back(XiaSanLuType::red);
						}
					}
					else  //�ȶԵĵڶ��бȵ�һ�г�
					{
						for (int i = 0; i < f - 1; i++)   //���ж��ܶ��ϵ�Ԫ�� д��
						{
							temp.push_back(XiaSanLuType::red);
						}

						temp.push_back(XiaSanLuType::blue);  //��������֮���м����һ���޶Լ���  

						for (int i = 0; i < s - f - 1; i++)   //Ȼ���ж��γ��˳����Ĳ���
						{
							temp.push_back(XiaSanLuType::red);
						}
					}
				}
			}
		}
		return temp;
	}

	void PaiLuRighDaYanZaiDelegate::disposeTempData(int idx, vector<BYTE> nums)
	{
		int i = 0;          //��ǰ�е�λ��   0-5   �������1-6
		int lastI = 0;      

		for (auto num : nums)
		{
			//��������ҵ��뷨�ǣ� ���� �ж�num�ǲ��Ǻͣ� ����Ǻͣ���ô��ס���ڵ�λ��  x ��y��  ������Ǻͣ���ô��ӵ���ά����������һ�У�1����6�����ߵ����ˣ������ұ����졣 ���������У�����ߵ�֮ǰ�������ˣ���ô�ͼ������Լ����ұ�����
			if (i < 6)   // i����С��6
			{
				if (dataArray[idx][i] == 0)   //���iû�е�6���������¿��Լ�����
				{
					lastI = i;         //�������ȸ�ֵ ��++  ������++ǰ��¼
					dataArray[idx][i] = num;
					i++;
				}
				else      //���iû�е�6������λ���Ѿ���ǰ���ռ�ˡ���ôֱ������
				{
					idx++;
					dataArray[idx][lastI] = num;   
				}
			}
			else   //���˵i��6�ˣ�Ҳ������һ�е�6�������ˣ���ô�����ұ��ߡ�
			{
				idx++;          //��Ϊ����������ƣ� ������Ҫ��ס�ƶ����λ��
				if (i == 6)
				{
					i -= 1;
				}
				dataArray[idx][i] = num;
			}
		}
	}

	void PaiLuRighDaYanZaiDelegate::exportData()
	{
		int idx = 0;
		vector<BYTE> temp;
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				temp.push_back(dataArray[i][j]);
			}

			if (i % 2 != 0)
			{
				_ClassResultData.push_back(temp);
				temp.clear();
			}
			

			if (i - 4 > 0 && dataArray[i - 4][0] == 0)  //���������4�ſյġ����ϵ���������������ɶ��ٿն���
			{
				break;
			}
		}
	}

	int PaiLuRighDaYanZaiDelegate::judgeRedOrBlue(vector<BYTE>frist, vector<BYTE>scend, int type)
	{
		
		if (determineType(scend[0]) == type)  //������ʱ��������ͬ��
		{
			if (frist.size() == scend.size())//���� ������Ե�ʱ�� �����µ�Ԫ�ص��ڶ�����ô����
			{
				return 1;    
			}
			else  //���򿪺�   ��һ�е�size�󣬻��ߵڶ��е�size��  �ڶ�������Ԫ�ض����Ƿ��غ죬  ��ΪҪô�жԣ�Ҫô����
			{
				return 2;      //���غ�
			}
		}
		else   //������Ͳ�ͬ ��ô���ǿ��µ�һ����   ������ͻ������������
		{
			if (frist.size() == scend.size())     //��� �ڶ��к͵�һ�г�����ȣ� �µ�Ԫ�ص�����������������Ǻ죬 �����κ������������
			{
				return 2;    //���غ�
			}
			else
			{
				return 1;
			}
		}
	}

	int PaiLuRighDaYanZaiDelegate::getNextZhuang()
	{
		return nextZhuang > 2 || nextZhuang < 0 ? 0 : nextZhuang;
	}

	int PaiLuRighDaYanZaiDelegate::getNextXian()
	{
		return nextXian > 2 || nextXian < 0 ? 0 : nextXian;
	}


	/*******************Ȧ�б�С·******************/
	PaiLuRighXiaoLuDelegate::PaiLuRighXiaoLuDelegate()
	{

	}
	PaiLuRighXiaoLuDelegate::~PaiLuRighXiaoLuDelegate()
	{

	}
	Size PaiLuRighXiaoLuDelegate::tableCellSizeForIndex(TableView *table, ssize_t idx)
	{
		return CCSizeMake(26, 75);
	}

	TableViewCell* PaiLuRighXiaoLuDelegate::tableCellAtIndex(TableView *table, ssize_t idx)
	{
		// �����ö����л�ȡһ��cell Ȼ���ж�cell�Ƿ�Ϊ�� Ϊ���򴴽�һ���µ�
		DownRightXiaoLuItemCell* cell = dynamic_cast<DownRightXiaoLuItemCell*>(table->dequeueCell());
		bool isRefresh = cell;//�Ƿ����
		if (!cell)
		{
			cell = DownRightXiaoLuItemCell::create();
		}
		DownRightDaLuStruct downRightDaLu;
		downRightDaLu.bRefresh = isRefresh;
		if (!_ClassResultData.empty() && idx < _ClassResultData.size())
		{
			downRightDaLu.QuanVaule.assign(_ClassResultData[idx].begin(), _ClassResultData[idx].end());
		}

		cell->setIdx(idx);
		cell->bulidCell(downRightDaLu);
		return cell;
	}
	ssize_t PaiLuRighXiaoLuDelegate::numberOfCellsInTableView(TableView *table)
	{
		refreshArray();
		_ClassResultData.clear();
		_tempDataList.clear();
		if (_AllRightDaLuResultData.size() <= 0) return 0;

		vector<BYTE> temp;
		PailuType  type = None;
		for (int i = 0; i < _AllRightDaLuResultData.size(); i++)  //���forѭ���������·�ĺ������
		{
			if (_AllRightDaLuResultData[i] == 3)  continue;  //������ֱ�Ӹɵ�

			if (temp.size() > 0)
			{
				if ((PailuType)determineType(_AllRightDaLuResultData[i]) == type)
				{
					temp.push_back(_AllRightDaLuResultData[i]);
				}
				else
				{
					_tempDataList.push_back(temp);
					temp.clear();
				}
			}

			//���û����һ�����У��Ϳ����µĶ���
			if (temp.size() == 0)
			{
				temp.push_back(_AllRightDaLuResultData[i]);
				type = (PailuType)determineType(_AllRightDaLuResultData[i]);
			}
		}
		if (temp.size() > 0)
		{
			_tempDataList.push_back(temp);
			temp.clear();
		}

		//���ȷ�����������·�Լ��ĺ�������
		if (_tempDataList.size() <= 0) return 0;
		vector<BYTE> tempDatas;
		tempDatas = analyzeXiaoLuRedAndBlue(_tempDataList);   // ���temp����ֻ�� 1 �� 2

		//ͨ����Ŷ��еļ��ϣ����ж����һ����ׯ���߿��Ͽ��ܳ��ֵ�
		if (_tempDataList.size() > 3)
		{
			nextZhuang = judgeRedOrBlue(_tempDataList[_tempDataList.size() - 3], _tempDataList[_tempDataList.size() - 1], XiaSanLuType::red);
			nextXian = judgeRedOrBlue(_tempDataList[_tempDataList.size() - 3], _tempDataList[_tempDataList.size() - 1], XiaSanLuType::blue);
		}

		//Ȼ�����Щ���������ö�ά�������к�
		if (tempDatas.size() <= 0)  return 0;
		vector<BYTE> temp_1;
		int idx = 0;
		PailuType type_1 = None;
		for (size_t i = 0; i < tempDatas.size(); i++)
		{
			if (temp_1.size() > 0)
			{
				if ((PailuType)determineType(tempDatas[i]) == type_1)
				{
					temp_1.push_back(tempDatas[i]);
				}
				else
				{
					disposeTempData(idx, temp_1);
					temp_1.clear();
					idx++;
				}
			}
			if (temp_1.size() == 0)
			{
				temp_1.push_back(tempDatas[i]);
				type_1 = (PailuType)determineType(tempDatas[i]);
			}
		}

		if (temp_1.size() > 0)   //���һ�����е�ʱ�� ���ܻ�©��
		{
			disposeTempData(idx, temp_1);
			temp_1.clear();
		}

		//�ó��������� ���ҷ�������size
		exportData();

		if (_ClassResultData.size() < rightShotListCount)
		{
			return rightShotListCount;
		}
		else
		{
			return  _ClassResultData.size();
		}
	}
	//����������
	void PaiLuRighXiaoLuDelegate::setAllResultData(vector<BYTE> AllResultData)
	{
		_AllRightDaLuResultData.clear();
		for (int i = 0; i < AllResultData.size(); i++)
		{
			_AllRightDaLuResultData.push_back(AllResultData.at(i));
		}
	}

	int PaiLuRighXiaoLuDelegate::getClassResultDataSize()
	{
		return _ClassResultData.size();
	}

	void PaiLuRighXiaoLuDelegate::refreshArray()
	{
		memset(dataArray, 0, sizeof(dataArray));
	}

	int PaiLuRighXiaoLuDelegate::determineType(int num)
	{
		if (num == 1 || num == 4 || num == 5 || num == 8)  //���е�
		{
			return 1;
		}
		else if (num == 2 || num == 6 || num == 7 || num == 9)   //��ׯ
		{
			return 2;
		}
		else
		{
			return 0;    // �Ͳ�����
		}

	}
	//�õ����жԱȵ�һ�У�
	vector<BYTE> PaiLuRighXiaoLuDelegate::analyzeXiaoLuRedAndBlue(vector<vector<BYTE>> temps)
	{
		vector<BYTE> temp;
		if (temps.size() < 3)  return temp;   //ֻ��ǰ���е�ʱ�� ֱ��return
		if (temps.size() == 3 && temps[2].size() <= 1) return temp;  //���ֻ�����У����ҵ����л�ֻ��1����ʱ��return  ��Ϊ�ӵ����еڶ��� ��ʼ
		int beforeFrist = -1;//�ȶ�ʱ�����е�ǰһ��  
		int frist ;  //�ȶ�ʱ��һ��
		int beforeScend = 1;//�ȶ�ʱ�ĵ����е�ǰһ��
		int scend = 2;  //�ȶ�ʱ�ĵ�����
		for (frist = 0; scend < temps.size(); frist++, scend++, beforeFrist++,beforeScend++)
		{
			int f = temps[frist].size();
			int s = temps[scend].size();

			if (scend > 2) 
			{
				if (temps[beforeFrist].size() == temps[beforeScend].size())   //�����һ���жϵ�ʱ��ʹ����в�һ�����жϵ��ǵ�ǰ�����е�ǰһ�У� �ȶԵ�ǰ��һ�е�ǰһ��
				{
					temp.push_back(XiaSanLuType::red);
				}
				else      
				{
					temp.push_back(XiaSanLuType::blue);
				}

				if (s == 1)  continue; 

				if (f >= s)  
				{
					for (int i = 0; i < s - 1; i++)   
					{
						temp.push_back(XiaSanLuType::red);
					}
				}
				else 
				{
					for (int i = 0; i < f - 1; i++) 
					{
						temp.push_back(XiaSanLuType::red);
					}

					temp.push_back(XiaSanLuType::blue); 

					for (int i = 0; i < s - f - 1; i++)  
					{
						temp.push_back(XiaSanLuType::red);
					}
				}

			}
			else
			{
				if (s == 1) 
				{
					continue;
				}
				else
				{
					if (f >= s)  
					{
						for (int i = 0; i < s - 1; i++)     
						{
							temp.push_back(XiaSanLuType::red);
						}
					}
					else  
					{
						for (int i = 0; i < f - 1; i++)   
						{
							temp.push_back(XiaSanLuType::red);
						}

						temp.push_back(XiaSanLuType::blue); 

						for (int i = 0; i < s - f - 1; i++)  
						{
							temp.push_back(XiaSanLuType::red);
						}
					}
				}
			}
		}
		return temp;
	}

	void PaiLuRighXiaoLuDelegate::disposeTempData(int idx, vector<BYTE> nums)
	{
		int i = 0;          //��ǰ�е�λ��   0-5   �������1-6
		int lastI = 0;

		for (auto num : nums)
		{
			//��������ҵ��뷨�ǣ� ���� �ж�num�ǲ��Ǻͣ� ����Ǻͣ���ô��ס���ڵ�λ��  x ��y��  ������Ǻͣ���ô��ӵ���ά����������һ�У�1����6�����ߵ����ˣ������ұ����졣 ���������У�����ߵ�֮ǰ�������ˣ���ô�ͼ������Լ����ұ�����
			if (i < 6)   // i����С��6
			{
				if (dataArray[idx][i] == 0)   //���iû�е�6���������¿��Լ�����
				{
					lastI = i;         //�������ȸ�ֵ ��++  ������++ǰ��¼
					dataArray[idx][i] = num;
					i++;
				}
				else      //���iû�е�6������λ���Ѿ���ǰ���ռ�ˡ���ôֱ������
				{
					idx++;
					dataArray[idx][lastI] = num;
				}
			}
			else   //���˵i��6�ˣ�Ҳ������һ�е�6�������ˣ���ô�����ұ��ߡ�
			{
				idx++;          //��Ϊ����������ƣ� ������Ҫ��ס�ƶ����λ��
				if (i == 6)
				{
					i -= 1;
				}
				dataArray[idx][i] = num;
			}
		}
	}

	void PaiLuRighXiaoLuDelegate::exportData()
	{
		int idx = 0;
		vector<BYTE> temp;
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				temp.push_back(dataArray[i][j]);
			}

			if (i % 2 != 0)
			{
				_ClassResultData.push_back(temp);
				temp.clear();
			}


			if (i - 4 > 0 && dataArray[i - 4][0] == 0)  //���������4�ſյġ����ϵ���������������ɶ��ٿն���
			{
				break;
			}
		}
	}

	int PaiLuRighXiaoLuDelegate::judgeRedOrBlue(vector<BYTE>frist, vector<BYTE>scend, int type)
	{

		if (determineType(scend[0]) == type)  //������ʱ��������ͬ��
		{
			if (frist.size() == scend.size())//���� ������Ե�ʱ�� �����µ�Ԫ�ص��ڶ�����ô����
			{
				return 1;
			}
			else  //���򿪺�   ��һ�е�size�󣬻��ߵڶ��е�size��  �ڶ�������Ԫ�ض����Ƿ��غ죬  ��ΪҪô�жԣ�Ҫô����
			{
				return 2;      //���غ�
			}
		}
		else   //������Ͳ�ͬ ��ô���ǿ��µ�һ����   ������ͻ������������
		{
			if (frist.size() == scend.size())     //��� �ڶ��к͵�һ�г�����ȣ� �µ�Ԫ�ص�����������������Ǻ죬 �����κ������������
			{
				return 2;    //���غ�
			}
			else
			{
				return 1;
			}
		}
	}

	int PaiLuRighXiaoLuDelegate::getNextZhuang()
	{
		return nextZhuang > 2 || nextZhuang < 0 ? 0 : nextZhuang;
	}

	int PaiLuRighXiaoLuDelegate::getNextXian()
	{
		return nextXian > 2 || nextXian < 0 ? 0 : nextXian;
	}

	/*******************Ȧ�б����·******************/
	PaiLuRighZhangLangDelegate::PaiLuRighZhangLangDelegate()
	{

	}
	PaiLuRighZhangLangDelegate::~PaiLuRighZhangLangDelegate()
	{

	}
	Size PaiLuRighZhangLangDelegate::tableCellSizeForIndex(TableView *table, ssize_t idx)
	{
		return CCSizeMake(26, 75);
	}

	TableViewCell* PaiLuRighZhangLangDelegate::tableCellAtIndex(TableView *table, ssize_t idx)
	{
		// �����ö����л�ȡһ��cell Ȼ���ж�cell�Ƿ�Ϊ�� Ϊ���򴴽�һ���µ�
		DownRightZhangLangItemCell* cell = dynamic_cast<DownRightZhangLangItemCell*>(table->dequeueCell());
		bool isRefresh = cell;//�Ƿ����
		if (!cell)
		{
			cell = DownRightZhangLangItemCell::create();
		}
		DownRightDaLuStruct downRightDaLu;
		downRightDaLu.bRefresh = isRefresh;
		if (!_ClassResultData.empty() && idx < _ClassResultData.size())
		{
			downRightDaLu.QuanVaule.assign(_ClassResultData[idx].begin(), _ClassResultData[idx].end());
		}

		cell->setIdx(idx);
		cell->bulidCell(downRightDaLu);
		return cell;
	}
	ssize_t PaiLuRighZhangLangDelegate::numberOfCellsInTableView(TableView *table)
	{
		refreshArray();
		_ClassResultData.clear();
		_tempDataList.clear();
		if (_AllRightDaLuResultData.size() <= 0) return 0;

		vector<BYTE> temp;
		PailuType  type = None;
		for (int i = 0; i < _AllRightDaLuResultData.size(); i++)  //���forѭ���������·�ĺ������
		{
			if (_AllRightDaLuResultData[i] == 3)  continue;  //������ֱ�Ӹɵ�

			if (temp.size() > 0)
			{
				if ((PailuType)determineType(_AllRightDaLuResultData[i]) == type)
				{
					temp.push_back(_AllRightDaLuResultData[i]);
				}
				else
				{
					_tempDataList.push_back(temp);
					temp.clear();
				}
			}

			//���û����һ�����У��Ϳ����µĶ���
			if (temp.size() == 0)
			{
				temp.push_back(_AllRightDaLuResultData[i]);
				type = (PailuType)determineType(_AllRightDaLuResultData[i]);
			}
		}
		if (temp.size() > 0)
		{
			_tempDataList.push_back(temp);
			temp.clear();
		}

		//���ȷ�����������·�Լ��ĺ�������
		if (_tempDataList.size() <= 0) return 0;
		vector<BYTE> tempDatas;
		tempDatas = analyzeXiaoLuRedAndBlue(_tempDataList);   // ���temp����ֻ�� 1 �� 2

		//ͨ����Ŷ��еļ��ϣ����ж����һ����ׯ���߿��Ͽ��ܳ��ֵ�
		if (_tempDataList.size() > 4)
		{
			nextZhuang = judgeRedOrBlue(_tempDataList[_tempDataList.size() - 4], _tempDataList[_tempDataList.size() - 1], XiaSanLuType::red);
			nextXian = judgeRedOrBlue(_tempDataList[_tempDataList.size() - 4], _tempDataList[_tempDataList.size() - 1], XiaSanLuType::blue);
		}

		//Ȼ�����Щ���������ö�ά�������к�
		if (tempDatas.size() <= 0)  return 0;
		vector<BYTE> temp_1;
		int idx = 0;
		PailuType type_1 = None;
		for (size_t i = 0; i < tempDatas.size(); i++)
		{
			if (temp_1.size() > 0)
			{
				if ((PailuType)determineType(tempDatas[i]) == type_1)
				{
					temp_1.push_back(tempDatas[i]);
				}
				else
				{
					disposeTempData(idx, temp_1);
					temp_1.clear();
					idx++;
				}
			}
			if (temp_1.size() == 0)
			{
				temp_1.push_back(tempDatas[i]);
				type_1 = (PailuType)determineType(tempDatas[i]);
			}
		}

		if (temp_1.size() > 0)   //���һ�����е�ʱ�� ���ܻ�©��
		{
			disposeTempData(idx, temp_1);
			temp_1.clear();
		}

		//�ó��������� ���ҷ�������size
		exportData();

		if (_ClassResultData.size() < rightShotListCount)
		{
			return rightShotListCount;
		}
		else
		{
			return  _ClassResultData.size();
		}
	}
	//����������
	void PaiLuRighZhangLangDelegate::setAllResultData(vector<BYTE> AllResultData)
	{
		_AllRightDaLuResultData.clear();
		for (int i = 0; i < AllResultData.size(); i++)
		{
			_AllRightDaLuResultData.push_back(AllResultData.at(i));
		}
	}

	int PaiLuRighZhangLangDelegate::getClassResultDataSize()
	{
		return _ClassResultData.size();
	}

	void PaiLuRighZhangLangDelegate::refreshArray()
	{
		memset(dataArray, 0, sizeof(dataArray));
	}

	int PaiLuRighZhangLangDelegate::determineType(int num)
	{
		if (num == 1 || num == 4 || num == 5 || num == 8)  //���е�
		{
			return 1;
		}
		else if (num == 2 || num == 6 || num == 7 || num == 9)   //��ׯ
		{
			return 2;
		}
		else
		{
			return 0;    // �Ͳ�����
		}

	}

	//�õ����жԱȵ�һ�У�
	vector<BYTE> PaiLuRighZhangLangDelegate::analyzeXiaoLuRedAndBlue(vector<vector<BYTE>> temps)
	{
		vector<BYTE> temp;
		if (temps.size() < 4)  return temp;   //ֻ��ǰ3�е�ʱ�� ֱ��return
		if (temps.size() == 4 && temps[3].size() <= 1) return temp;  //���ֻ�����У����ҵ����л�ֻ��1����ʱ��return  ��Ϊ�ӵ����еڶ��� ��ʼ
		int beforeFrist = -1;//�ȶ�ʱ�����е�ǰһ��  
		int frist;  //�ȶ�ʱ��һ��
		int beforeScend = 2;//�ȶ�ʱ�ĵ����е�ǰһ��
		int scend = 3;  //�ȶ�ʱ�ĵ�����
		for (frist = 0; frist < temps.size() && scend < temps.size(); frist++, scend++, beforeFrist++, beforeScend++)
		{
			int f = temps[frist].size();
			int s = temps[scend].size();

			if (scend > 3)
			{
				if (temps[beforeFrist].size() == temps[beforeScend].size())   //�����һ���жϵ�ʱ��ʹ����в�һ�����жϵ��ǵ�ǰ�����е�ǰһ�У� �ȶԵ�ǰ��һ�е�ǰһ��
				{
					temp.push_back(XiaSanLuType::red);
				}
				else
				{
					temp.push_back(XiaSanLuType::blue);
				}

				if (s == 1)  continue;

				if (f >= s)
				{
					for (int i = 0; i < s - 1; i++)
					{
						temp.push_back(XiaSanLuType::red);
					}
				}
				else
				{
					for (int i = 0; i < f - 1; i++)
					{
						temp.push_back(XiaSanLuType::red);
					}

					temp.push_back(XiaSanLuType::blue);

					for (int i = 0; i < s - f - 1; i++)
					{
						temp.push_back(XiaSanLuType::red);
					}
				}

			}
			else
			{
				if (s == 1)
				{
					continue;
				}
				else
				{
					if (f >= s)
					{
						for (int i = 0; i < s - 1; i++)
						{
							temp.push_back(XiaSanLuType::red);
						}
					}
					else
					{
						for (int i = 0; i < f - 1; i++)
						{
							temp.push_back(XiaSanLuType::red);
						}

						temp.push_back(XiaSanLuType::blue);

						for (int i = 0; i < s - f - 1; i++)
						{
							temp.push_back(XiaSanLuType::red);
						}
					}
				}
			}
		}
		return temp;
	}

	void PaiLuRighZhangLangDelegate::disposeTempData(int idx, vector<BYTE> nums)
	{
		int i = 0;          //��ǰ�е�λ��   0-5   �������1-6
		int lastI = 0;

		for (auto num : nums)
		{
			//��������ҵ��뷨�ǣ� ���� �ж�num�ǲ��Ǻͣ� ����Ǻͣ���ô��ס���ڵ�λ��  x ��y��  ������Ǻͣ���ô��ӵ���ά����������һ�У�1����6�����ߵ����ˣ������ұ����졣 ���������У�����ߵ�֮ǰ�������ˣ���ô�ͼ������Լ����ұ�����
			if (i < 6)   // i����С��6
			{
				if (dataArray[idx][i] == 0)   //���iû�е�6���������¿��Լ�����
				{
					lastI = i;         //�������ȸ�ֵ ��++  ������++ǰ��¼
					dataArray[idx][i] = num;
					i++;
				}
				else      //���iû�е�6������λ���Ѿ���ǰ���ռ�ˡ���ôֱ������
				{
					idx++;
					dataArray[idx][lastI] = num;
				}
			}
			else   //���˵i��6�ˣ�Ҳ������һ�е�6�������ˣ���ô�����ұ��ߡ�
			{
				idx++;          //��Ϊ����������ƣ� ������Ҫ��ס�ƶ����λ��
				if (i == 6)
				{
					i -= 1;
				}
				dataArray[idx][i] = num;
			}
		}
	}

	void PaiLuRighZhangLangDelegate::exportData()
	{
		int idx = 0;
		vector<BYTE> temp;
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				temp.push_back(dataArray[i][j]);
			}

			if (i % 2 != 0)
			{
				_ClassResultData.push_back(temp);
				temp.clear();
			}

			if (i - 4 > 0 && dataArray[i - 4][0] == 0)  //������������ſյġ����ϵ���������������ɶ��ٿն���
			{
				break;
			}
		}
	}

	int PaiLuRighZhangLangDelegate::judgeRedOrBlue(vector<BYTE>frist, vector<BYTE>scend, int type)
	{

		if (determineType(scend[0]) == type)  //������ʱ��������ͬ��
		{
			if (frist.size() == scend.size())//���� ������Ե�ʱ�� �����µ�Ԫ�ص��ڶ�����ô����
			{
				return 1;
			}
			else  //���򿪺�   ��һ�е�size�󣬻��ߵڶ��е�size��  �ڶ�������Ԫ�ض����Ƿ��غ죬  ��ΪҪô�жԣ�Ҫô����
			{
				return 2;      //���غ�
			}
		}
		else   //������Ͳ�ͬ ��ô���ǿ��µ�һ����   ������ͻ������������
		{
			if (frist.size() == scend.size())     //��� �ڶ��к͵�һ�г�����ȣ� �µ�Ԫ�ص�����������������Ǻ죬 �����κ������������
			{
				return 2;    //���غ�
			}
			else
			{
				return 1;
			}
		}
	}

	int PaiLuRighZhangLangDelegate::getNextZhuang()
	{
		return nextZhuang > 2 || nextZhuang < 0 ? 0 : nextZhuang;
	}

	int PaiLuRighZhangLangDelegate::getNextXian()
	{
		return nextXian > 2 || nextXian < 0 ? 0 : nextXian;
	}
}
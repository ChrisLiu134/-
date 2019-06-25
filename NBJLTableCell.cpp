#include "NBJLTableCell.h"

namespace NBJL
{
	static const char* GAME_DOWNLEFT_CELL = "NBJL/paiLuCell1.csb";      //size   49 296  
	static const char* GAME_DOWNDALURIGHT_CELL = "NBJL/paiLuCell2.csb"; // size   25  148
	static const char* GAME_DOWNDAYanZaiRIGHT_CELL = "NBJL/paiLuCell3.csb"; // size   25  74

	/***********************���б�****************************/
	DownLeftItemCell* DownLeftItemCell::create()
	{
		DownLeftItemCell* cell = new::NBJL::DownLeftItemCell();
		if (cell&&cell->init())
		{
			
			cell->autorelease();		//���뵽�Զ��ͷų���
			return cell;
		}
		CC_SAFE_DELETE(cell);
		return NULL;
	}

	void DownLeftItemCell::bulidCell(DownLeftStruct DownLeftInfo)
	{
		//����Ѿ����������������ظ�����
		if (!DownLeftInfo.bRefresh)
		{
			auto rootNode = CSLoader::createNode(GAME_DOWNLEFT_CELL);
			_layout = dynamic_cast<Layout*>(rootNode->getChildByName("Panel_1"));
			_layout->removeFromParentAndCleanup(false);
			 drawNode = DrawNode::create();
			_layout->addChild(drawNode);
			this->addChild(_layout);
		}

		if (drawNode)  drawNode->clear(); //���֮ǰ�������ݣ�Ȼ���ػ�

		this->setContentSize(cocos2d::Size(50, 300));
		cocos2d::Size size = this->getContentSize();
		_layout->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
		for (int i = 0; i < leftListitemCount; i++)
		{
			auto img_Zi = dynamic_cast<ImageView*>(_layout->getChildByName(StringUtils::format("Image_paulu_%d",i)));
			img_Zi->setVisible(true);
			if (img_Zi)
			{
				switch (DownLeftInfo.ZiVaule[i])   //�ж����ݽ��
				{
				case Pailu::none:
					img_Zi->setVisible(false);
					break;
				case Pailu::xianWin:
					img_Zi->loadTexture("NBJL/pailu/xian.png");
						break;
				case Pailu::zhuangWin:
					img_Zi->loadTexture("NBJL/pailu/zhuang.png");
						break;
				case Pailu::heWin:
					img_Zi->loadTexture("NBJL/pailu/he.png");
					break;
				case Pailu::xianWinXianDui:
					img_Zi->loadTexture("NBJL/pailu/xian.png");
					drawBluePoint(i);
						break;
				case Pailu::xianWinZhuangDui:
					img_Zi->loadTexture("NBJL/pailu/xian.png");
					drawRedPoint(i);
						break;
				case Pailu::zhuangWinZhuangDui:
					img_Zi->loadTexture("NBJL/pailu/zhuang.png");
					drawRedPoint(i);
						break;
				case Pailu::zhuangWinXianDui:
					img_Zi->loadTexture("NBJL/pailu/zhuang.png");
					drawBluePoint(i);
						break;
				case Pailu::xianDUIzhuangDUIXianWin:
					img_Zi->loadTexture("NBJL/pailu/xian.png");
					drawRedAndBluePoint(i);
						break;
				case Pailu::xianDuiZhuangDuiZhuangWin:
					img_Zi->loadTexture("NBJL/pailu/zhuang.png");
					drawRedAndBluePoint(i);
						break;
					default:
						img_Zi->setVisible(false);
						break;
				}
			}
		}
	}

	void DownLeftItemCell::drawRedPoint(int idx)
	{
		if (drawNode)
		{			
			drawNode->drawDot(Vec2(10, 285 - idx*50), 8, Color4F::RED);
		}
	}

	void DownLeftItemCell::drawBluePoint(int idx)
	{
		if (drawNode)
		{
			drawNode->drawDot(Vec2(36.00, 260 - idx * 50), 8, Color4F::BLUE);
		}
	}
	
	void DownLeftItemCell::drawRedAndBluePoint(int idx)
	{
		if (drawNode)
		{
			drawNode->drawDot(Vec2(10, 285 - idx * 50), 8, Color4F::RED);
			drawNode->drawDot(Vec2(36.00, 260- idx * 50), 8, Color4F::BLUE);
		}
	}
	/***********************Ȧ�б��·****************************/
	DownRightDaLuItemCell* DownRightDaLuItemCell::create()
	{
		DownRightDaLuItemCell* cell = new::NBJL::DownRightDaLuItemCell();
		if (cell&&cell->init())
		{
			cell->autorelease();		//���뵽�Զ��ͷų���
			return cell;
		}
		CC_SAFE_DELETE(cell);
		return NULL;
	}
	void DownRightDaLuItemCell::bulidCell(DownRightDaLuStruct DownRightInfo)
	{
		//����Ѿ����������������ظ�����
		if (!DownRightInfo.bRefresh)
		{
			auto rootNode = CSLoader::createNode(GAME_DOWNDALURIGHT_CELL);
			_layout = dynamic_cast<Layout*>(rootNode->getChildByName("Panel_1"));
			_layout->removeFromParentAndCleanup(false);
			drawNode = DrawNode::create();
			_layout->addChild(drawNode);
			addChild(_layout);
		}
		if (drawNode)  drawNode->clear(); //���֮ǰ�������ݣ�Ȼ���ػ�

		for (int i = 0; i < _layout->getChildrenCount(); i++)  //ɾ���Լ����������text����Ϊ����Ҫ�������
		{
			if (_layout->getChildByName("he"))
			{
				_layout->removeChildByName("he");
			}
		}
		
		setContentSize(cocos2d::Size(25, 150));
		cocos2d::Size size = getContentSize();
		_layout->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
		
		int he_count = 0;   //������¼�͵Ĵ�����   ��Ϊ���ܻ���������
		int hePos = -5;    //������¼��һ�ο��͵�idx
		for (int i = 0, idx = 0; i < DownRightInfo.QuanVaule.size() /*&& idx < 6*/; i++, idx++ ) // idx ��6�����Ӷ�Ӧ���±� ����ϵ����ͼ������λ��
		{
			switch (DownRightInfo.QuanVaule[i])   //�ж����ݽ��
			{
			case Pailu::none:

				break;
			case Pailu::xianWin:
				drawBlueRound(idx);
				break;
			case Pailu::zhuangWin:
				drawRedRound(idx);
				break;
			case Pailu::heWin:
				if ( i - hePos != 1)   //Ҳ����˵����һ�γ����˺ͣ���һ���ֳ����˺ͣ���ô ֱ����ԭ�еĻ����� �����ּ�һ����֮ǰ��text��ʾ�� ������½�һ��
				{
					he_count = 0;
					text_he = Text::create();
					text_he->setTextColor(Color4B(94, 176, 63, 255));
					_layout->addChild(text_he);
					text_he->setName("he");
					text_he->setFontSize(16);
					text_he->setPosition(Vec2(12.5, 136 - idx * 25));
				}	
				he_count++;
				
				if (text_he)
				{
					text_he->setString(to_string(he_count));
					text_he->setVisible(true);
				}
				
				hePos = i;
				idx--;
				break;
			case Pailu::xianWinXianDui:
				drawBlueRound(idx);
				drawBluePoint(idx);
				break;
			case Pailu::xianWinZhuangDui:
				drawBlueRound(idx);
				drawRedPoint(idx);
				break;
			case Pailu::zhuangWinZhuangDui:
				drawRedRound(idx);
				drawRedPoint(idx);
				break;
			case Pailu::zhuangWinXianDui:
				drawRedRound(idx);
				drawBluePoint(idx);
				break;
			case Pailu::xianDUIzhuangDUIXianWin:
				drawBlueRound(idx);
				drawRedAndBluePoint(idx);
				break;
			case Pailu::xianDuiZhuangDuiZhuangWin:
				drawRedRound(idx);
				drawRedAndBluePoint(idx);
				break;
			default:
				break;
			}
		}
	}

	void DownRightDaLuItemCell::drawRedPoint(int idx)
	{
		if (drawNode)
		{
			drawNode->drawDot(Vec2(5, 142 - idx * 25), 4, Color4F::RED);
		}
	}

	void DownRightDaLuItemCell::drawBluePoint(int idx)
	{
		if (drawNode)
		{
			drawNode->drawDot(Vec2(20, 130 - idx * 25), 4, Color4F::BLUE);
		}
	}

	void DownRightDaLuItemCell::drawRedAndBluePoint(int idx)
	{
		if (drawNode)
		{
			drawNode->drawDot(Vec2(5, 142 - idx * 25), 4, Color4F::RED);
			drawNode->drawDot(Vec2(20, 130 - idx * 25), 4, Color4F::BLUE);
		}
	}

	void DownRightDaLuItemCell::drawRedRound(int idx)
	{
		if (drawNode)
		{
			drawNode->drawCircle(Vec2(12.5, 136 - idx * 25), 10, 0, 360, false, Color4F::RED);
		}
	}

	void DownRightDaLuItemCell::drawBlueRound(int idx)
	{
		if (drawNode)
		{
			drawNode->drawCircle(Vec2(12.5, 136 - idx * 25), 10, 0, 360, false,Color4F::BLUE);
		}
	}


	/***********************Ȧ�б������****************************/
	DownRightDaYanZaiItemCell* DownRightDaYanZaiItemCell::create()
	{
		DownRightDaYanZaiItemCell* cell = new::NBJL::DownRightDaYanZaiItemCell();
		if (cell && cell->init())
		{
			cell->autorelease();		//���뵽�Զ��ͷų���
			return cell;
		}
		CC_SAFE_DELETE(cell);
		return NULL;
	}

	void DownRightDaYanZaiItemCell::bulidCell(DownRightDaLuStruct  DownRightInfo)
	{
		//����Ѿ����������������ظ�����
		if (!DownRightInfo.bRefresh)
		{
			auto rootNode = CSLoader::createNode(GAME_DOWNDAYanZaiRIGHT_CELL);
			_layout = dynamic_cast<Layout*>(rootNode->getChildByName("Panel_1"));
			_layout->removeFromParentAndCleanup(false);
			drawNode = DrawNode::create();
			_layout->addChild(drawNode);
			this->addChild(_layout);
		}

		if (drawNode)  drawNode->clear(); //���֮ǰ�������ݣ�Ȼ���ػ�

		setContentSize(cocos2d::Size(26, 75));
		cocos2d::Size size = getContentSize();
		_layout->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
		XiaSanLuType type = NOne;
		for (int i = 0, idx = 0 ; i < DownRightInfo.QuanVaule.size() ; i++, idx++)
		{
			type = (XiaSanLuType)DownRightInfo.QuanVaule[i];
			switch (type)
			{
			case NBJL::NOne:
				break;
			case NBJL::red:
				drawRedRound(idx);
				break;
			case NBJL::blue:
				drawBlueRound(idx);
				break;
			default:
				break;
			}
		}

	}

	void DownRightDaYanZaiItemCell::drawRedRound(int idx)
	{
		if (drawNode)
		{
			if (idx < 6)
			{
				drawNode->drawCircle(Vec2(7.5, 68 - idx * 12.5), 5, 0, 360, false, Color4F::RED);
			}
			else
			{
				drawNode->drawCircle(Vec2(18.8, 68 - (idx-6) * 12.5), 5, 0, 360, false, Color4F::RED);
			}
		}
	}

	void DownRightDaYanZaiItemCell::drawBlueRound(int idx)
	{
		if (drawNode)
		{
			if (idx < 6)
			{
				drawNode->drawCircle(Vec2(7.5, 68 - idx * 12.5), 5, 0, 360, false, Color4F::BLUE);
			}
			else
			{
				drawNode->drawCircle(Vec2(18.8, 68 - (idx - 6) * 12.5), 5, 0, 360, false, Color4F::BLUE);
			}
		}
	}

	/***********************Ȧ�б�С·****************************/
	DownRightXiaoLuItemCell* DownRightXiaoLuItemCell::create()
	{
		DownRightXiaoLuItemCell* cell = new::NBJL::DownRightXiaoLuItemCell();
		if (cell && cell->init())
		{
			cell->autorelease();		//���뵽�Զ��ͷų���
			return cell;
		}
		CC_SAFE_DELETE(cell);
		return NULL;
	}

	void DownRightXiaoLuItemCell::bulidCell(DownRightDaLuStruct DownRightInfo)
	{
		//����Ѿ����������������ظ�����
		if (!DownRightInfo.bRefresh)
		{
			auto rootNode = CSLoader::createNode(GAME_DOWNDAYanZaiRIGHT_CELL);
			_layout = dynamic_cast<Layout*>(rootNode->getChildByName("Panel_1"));
			_layout->removeFromParentAndCleanup(false);
			drawNode = DrawNode::create();
			_layout->addChild(drawNode);
			this->addChild(_layout);
		}

		if (drawNode)  drawNode->clear(); //���֮ǰ�������ݣ�Ȼ���ػ�

		setContentSize(cocos2d::Size(26, 75));
		cocos2d::Size size = getContentSize();
		_layout->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
		XiaSanLuType type = NOne;
		for (int i = 0, idx = 0; i < DownRightInfo.QuanVaule.size(); i++, idx++)
		{
			type = (XiaSanLuType)DownRightInfo.QuanVaule[i];
			switch (type)
			{
			case NBJL::NOne:
				break;
			case NBJL::red:
				drawRedDot(idx);
				break;
			case NBJL::blue:
				drawBlueDot(idx);
				break;
			default:
				break;
			}
		}
	}

	void DownRightXiaoLuItemCell::drawRedDot(int idx)
	{
		if (drawNode)
		{
			if (idx < 6)
			{
				drawNode->drawDot(Vec2(7.2, 68 - idx * 12.5), 5, Color4F::RED);
			}
			else
			{
				drawNode->drawDot(Vec2(19.2, 68 - (idx - 6) * 12.5), 5, Color4F::RED);
			}
		}
	}

	void DownRightXiaoLuItemCell::drawBlueDot(int idx)
	{
		if (drawNode)
		{
			if (idx < 6)
			{
				drawNode->drawDot(Vec2(7.2, 68 - idx * 12.5), 5, Color4F::BLUE);
			}
			else
			{
				drawNode->drawDot(Vec2(19.2, 68 - (idx - 6) * 12.5), 5, Color4F::BLUE);
			}
		}
	}

	/***********************Ȧ�б����·****************************/
	DownRightZhangLangItemCell* DownRightZhangLangItemCell::create()
	{
		DownRightZhangLangItemCell* cell = new::NBJL::DownRightZhangLangItemCell();
		if (cell && cell->init())
		{
			cell->autorelease();		//���뵽�Զ��ͷų���
			return cell;
		}
		CC_SAFE_DELETE(cell);
		return NULL;
	}

	void DownRightZhangLangItemCell::bulidCell(DownRightDaLuStruct DownRightInfo)
	{
		//����Ѿ����������������ظ�����
		if (!DownRightInfo.bRefresh)
		{
			auto rootNode = CSLoader::createNode(GAME_DOWNDAYanZaiRIGHT_CELL);
			_layout = dynamic_cast<Layout*>(rootNode->getChildByName("Panel_1"));
			_layout->removeFromParentAndCleanup(false);
			drawNode = DrawNode::create();
			_layout->addChild(drawNode);
			this->addChild(_layout);
		}

		if (drawNode)  drawNode->clear(); //���֮ǰ�������ݣ�Ȼ���ػ�

		setContentSize(cocos2d::Size(26, 75));
		cocos2d::Size size = getContentSize();
		_layout->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
		XiaSanLuType type = NOne;
		for (int i = 0, idx = 0; i < DownRightInfo.QuanVaule.size(); i++, idx++)
		{
			type = (XiaSanLuType)DownRightInfo.QuanVaule[i];
			switch (type)
			{
			case NBJL::NOne:
				break;
			case NBJL::red:
				drawRedLine(idx);
				break;
			case NBJL::blue:
				drawBlueLine(idx);
				break;
			default:
				break;
			}
		}

	}

	void DownRightZhangLangItemCell::drawRedLine(int idx)
	{
		if (drawNode)
		{
			if (idx < 6)
			{
				drawNode->drawSegment(Vec2(10, 69 - idx * 11), Vec2(5, 62.5 - idx * 11), 1, Color4F::RED);
			}
			else
			{
				drawNode->drawSegment(Vec2(21, 69 - (idx - 6) * 11), Vec2(16, 62.5 - (idx - 6) * 11), 1, Color4F::RED);
			}
		}
	}

	void DownRightZhangLangItemCell::drawBlueLine(int idx)
	{
		if (drawNode)
		{
			if (idx < 6)
			{
				drawNode->drawSegment(Vec2(10, 69 - idx * 11), Vec2(5, 62.5 - idx * 11), 1, Color4F::BLUE);
			}
			else
			{
				drawNode->drawSegment(Vec2(21, 69 - (idx - 6) * 11), Vec2(16, 62.5 - (idx - 6) * 11), 1, Color4F::BLUE);
			}
		}
	}
}

#include "TiShi.h" 
#include "GameScene.h"
#include "GameData.h"

USING_NS_CC; 

TiShi * TiShi::create(int btnKind,std::string word,std::string wordtwo,int time,int GuanKaNum,bool ShouDong)
{
	TiShi * tishi = new TiShi();
	tishi->init(btnKind,word,wordtwo,time,GuanKaNum,ShouDong);
	tishi->autorelease();
	return tishi;
}

bool TiShi::init(int btnKind,std::string word,std::string wordtwo,int time,int GuanKaNum,bool ShouDong)

{  
	if ( !Node::init() )	
	{
		return false;
	}

	tishiTime = time; 
	 bShouDong = ShouDong; 
	if(btnKind == 8)
	{
	

		GuanKaNum++; 
	//	if(GuanKaNum< 11)
		{
			Size winSize = Director::getInstance()->getWinSize();
			auto guanka  = Sprite::createWithSpriteFrameName("guanchoose.png");
			guanka->setPosition(Point(winSize.width * 0.41,winSize.height* 0.8));
			this->addChild(guanka);
			 
			//if(GuanKaNum == 10)
			//	GuanKaNum = 0;
            //GuanKaNum = 19;
			auto  BibeiNumFont = Label::create();  
			BibeiNumFont->setCharMap("img/guannum.png",62,81, '0');
			this->addChild(BibeiNumFont,100);  
			char cNum[5];
			sprintf(cNum,"%d",GuanKaNum);
			BibeiNumFont->setString(cNum); 
			BibeiNumFont->setPosition(winSize.width * 0.59,winSize.height* 0.8);
		
		}
		/*else if(GuanKaNum < 20)
		{
			Size winSize = Director::getInstance()->getWinSize();
			auto guanka  = Sprite::create("guanchoosetwo.png");
			guanka->setPosition(Point(winSize.width * 0.41,winSize.height* 0.8));
			this->addChild(guanka);
			 
			auto  BibeiNumFont = Label::create();  
			BibeiNumFont->setCharMap("guannum.png",106,97, '0'); 
			this->addChild(BibeiNumFont,100);  
			char cNum[5];
			sprintf(cNum,"0%d",GuanKaNum%10);
			BibeiNumFont->setScale(0.8f);
			BibeiNumFont->setString(cNum); 
			BibeiNumFont->setPosition(winSize.width * 0.59,winSize.height* 0.8);
		}
		else if(GuanKaNum == 20)
		{
			Size winSize = Director::getInstance()->getWinSize();
			auto guanka  = Sprite::create("guanchoosetwo.png");
			guanka->setPosition(Point(winSize.width * 0.42,winSize.height* 0.8));
			this->addChild(guanka);

			auto  BibeiNumFont = Label::create();  
			BibeiNumFont->setCharMap("guannum.png",106,97, '0'); 
			this->addChild(BibeiNumFont,100);  
			char cNum[5];
			sprintf(cNum,"20");
			BibeiNumFont->setString(cNum); 
			BibeiNumFont->setScale(0.8f);
			BibeiNumFont->setPosition(winSize.width * 0.58,winSize.height* 0.8);
		}
		else
		{
			Size winSize = Director::getInstance()->getWinSize();
			auto guanka  = Sprite::create("guanchoosetwo.png");
			guanka->setPosition(Point(winSize.width * 0.41,winSize.height* 0.8));
			this->addChild(guanka);

			auto  BibeiNumFont = Label::create();  
			BibeiNumFont->setCharMap("guannum.png",106,97, '0'); 
			this->addChild(BibeiNumFont,100);  
			char cNum[5];
			sprintf(cNum,"2%d",GuanKaNum%20);
			BibeiNumFont->setString(cNum); 
			BibeiNumFont->setScale(0.8f);
			BibeiNumFont->setPosition(winSize.width * 0.59,winSize.height* 0.8);
		} */
	}
	else if(btnKind == 9)
	{
		Size winSize = Director::getInstance()->getWinSize();
		auto guanka  = Sprite::createWithSpriteFrameName("guangongxi.png");
		guanka->setPosition(Point(winSize.width * 0.5,winSize.height* 0.8)); 
		this->addChild(guanka);
	}
	else
	{
		auto tishiBg = Sprite::createWithSpriteFrameName( "tishiwf.png");
		 
		tishiBg->setTag(1);
		tishiBg->setAnchorPoint(Point(0.5,0.5));
		tishiBg->setPosition(Point(0,0)); 

		string text1 = (char *)word.c_str();
		auto wordTTF = Label::createWithSystemFont(text1,"",20);
		wordTTF->setColor(Color3B(233,227,205));
		tishiBg->addChild(wordTTF,1000);

		string text2 = (char *)wordtwo.c_str();

		auto wordTTF1 = Label::createWithSystemFont(text2,"",20);
		wordTTF1->setColor(Color3B(233,227,205));
		tishiBg->addChild(wordTTF1,1000);

		if(btnKind == 1)
		{

			wordTTF->setPosition(Point(150,39));
			wordTTF1->setPosition(Point(150,16));
		}
		else if(btnKind == 2)
		{
			tishiBg->setFlipY(true);
			wordTTF->setPosition(Point(165,128));
			wordTTF1->setPosition(Point(155,105));
		}
		else if(btnKind == 3)
		{
			tishiBg->setFlipX(true);
			wordTTF->setPosition(Point(80,42));
			wordTTF1->setPosition(Point(80,18));
		}

		else if(btnKind == 4)
		{
			tishiBg->setFlipX(true);
			tishiBg->setFlipY(true);
			wordTTF->setPosition(Point(80,127));
			wordTTF1->setPosition(Point(80,103));
		}
		

		this->addChild(tishiBg);

	} 

	this->schedule(schedule_selector(TiShi::tishiCD),0.5f);

	 return true;
}

void TiShi::tishiCD(float fdelta)
{
	tishiTime--;
	if(tishiTime == 0)
	{
		this->unschedule(schedule_selector(TiShi::tishiCD));
		this->setVisible(false);
		if(bShouDong == false) 
		this->removeFromParent();
	}
}

void TiShi::yuyue()
{
	tishiTime = 3;
	this->schedule(schedule_selector(TiShi::tishiCD),0.5f);
}
void TiShi::exit()
{
	this->removeFromParent();
}

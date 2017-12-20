 

#include "FishLayer.h"

//#include "FishTollGate.h"
#include "FishGroup.h"

#include "Gonggao.h"
 
#include "GameBegin.h"

#include "SimpleAudioEngine.h"
#include "time.h"

#include "GameScene.h"
#include "StaticData.h"
#include<algorithm>

#include "FishTrack.h"
#include "FishScript.h"  
#include <math.h>
#include "CannonLayer.h"
#include "GameHallLayer.h"
#include "LogoLayer.h"
#ifdef _WIN32
#include <windows.h>   
#endif
//#include "CCPlatformDefine.h"

#ifdef FISH_FAST_TEST
//#include "ControlFish.h"
#endif


map<int,TollGateInfoDef>FishLayer::m_mapTollGate;
bool  FishLayer::bDingping = false; 
char  FishLayer::cNewBoss = 0;

char  FishLayer::cAddFishNum = 0; 
bool  FishLayer::bYuZheng = false;
bool  FishLayer::bMoveFast = false;
bool FishLayer::bFirstBaoXiang = false;
bool FishLayer::bBulletShan = false;
int  FishLayer::m_fUpdateFishYuZheng = 0;  

bool FishLayer::Fishnodown = false;
int FishLayer::iBossChiFen = 0;
int FishLayer::fishlayerPeriod = 0;
int FishLayer::ifCatchJnum = 0;
Vector <LabelTTF *> FishLayer::catchLabel;

USING_NS_CC;
bool FishLayer::init()
{

	if ( !Layer::init() )	
	{
		return false;
	}
    m_fishRandSwatch.Reset();
    bBulletShan = false;
    Fishnodown = true;
	timeUpdate = 0.01;
	cAddFishNum = 6;
	bNetChoose = false;
	iBossChiFen = UserDefault::getInstance()->getIntegerForKey("Romm0JiangChi");
	 
    bDingping = false;

    int capacity = 50;
    m_iNowMaxFishMainID = 0;

    
	ShootFish[0]  = NULL;
	ShootFish[1]  = NULL;
	ShootFish[2]  = NULL;
    ShootFish[3]  = NULL;
    SetRandom();
    
//    this->schedule(schedule_selector(FishLayer::addFish), 1.0); 
	winSize = Director::getInstance()->getWinSize();
	visibleSize = Director::getInstance()->getVisibleSize();

    YuChao = Sprite::createWithSpriteFrameName("yuchao.png");
	YuChao->setPosition(Point(winSize.width * 0.5,winSize.height* 0.77));

	YuChao->setVisible(false);
	this->addChild(YuChao); 
	cRandGroupTime = 5; 


	 
    auto  FontBg = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName( "fontbgwf.png",Rect(10,10,10,10) );
    FontBg->setContentSize(Size(1300,274));
   
    FontBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(FontBg,100,269);
    FontBg->setVisible(false);
    
    
    
	SmallBossFont = Sprite::createWithSpriteFrameName("smallfontwf.png");
	SmallBossFont->setPosition(Point(winSize.width * 0.60,winSize.height* 0.5));
	this->addChild(SmallBossFont,100);
	SmallBossFont->setVisible(false);
    SmallBossFont->setScale(0.9);

	BigBossFont = Sprite::createWithSpriteFrameName("bigfontwf.png");
    BigBossFont->setPosition(Point(winSize.width * 0.60,winSize.height* 0.5));
	this->addChild(BigBossFont,100);
	BigBossFont->setVisible(false);
    BigBossFont->setScale(0.9);
    
    BossBgGuang = Sprite::create("bossbgguangwf.png");
    BossBgGuang->setPosition(Point(winSize.width * 0.5,winSize.height* 0.5));
    this->addChild(BossBgGuang,100);
    BossBgGuang->setVisible(false);
 
	 
    sprBossFish = Sprite::create();
    this->addChild(sprBossFish,100);
    sprBossFish->setPosition(Vec2(winSize.width * 0.185,winSize.height* 0.5));
    
    
	m_cBackGroundID = 0;
	m_bEnterRest = false;
	 
	UpdateGroupTime =7;

	m_iNowTollGateID = 0;
	m_iNowTollGateStatus = REST_STATUS;
	m_iNowTollGateFrameIndex = 0;
	m_iNowTollGateMaxFrame = 0;
	m_iNowFishMaxMainID = 0; 
	m_bServerSendRestMsg = false;
	m_iNowFishRestConFrame = 0;
	m_iNowFishRandSwatchID = 0;
	m_iNowFishFixedLineupID = 0;

	m_iNowFrame = 0;
	m_iFishFrame = 0;
	 
	m_fUpdateTime = 0;

	m_fTimeGroup = 0;
	m_fUpdateTimeGroup = 0;	

	m_fUpdateFish =2 ;
	m_fTimeFish=0;  
	m_fUpdateFishBoss =  0;   
	m_fUpdateFishYuZheng = 0;

	cNowBoss = -1; 
  
	bMoveFast = false; 
	bYuZheng = false;
	bFirstYuZhen = true;
  
	if(GameScene::cGameType != 2)
		schedule(schedule_selector(FishLayer::updateFishlayerBoss),1.0f);
	 
	schedule(schedule_selector(FishLayer::updateFishMove),0.01f ); 
	updateFishlayerPeriod(0.1);
	schedule(schedule_selector(FishLayer::updateFishlayerPeriod),60.0f);
    
   
    return true;
}


void FishLayer::RemoveAllFish()
{
  
    for(int i=0; i< m_Fishes.size(); i++)
    {
        m_Fishes[i]->stopAllActions();
        m_Fishes[i]->unscheduleAllSelectors();         m_Fishes[i]->removeChild(m_Fishes[i]->getFishSprite(),true);
        m_Fishes[i]->removeChild(m_Fishes[i]->dFish,true);

            m_Fishes[i]->removeAllChildrenWithCleanup(true);
          this->removeChild(m_Fishes[i], true);
         m_Fishes.erase(m_Fishes.begin()+i);
        
    }
    this->removeAllChildrenWithCleanup(true);
    this->unscheduleAllSelectors();
}
void FishLayer::ClearNet()
{
	if(m_FishingNet.size() >40)
	{
		vector<int> deleNum;
		int all = 0;
		 
		for(int i=0; i< m_FishingNet.size(); i++)
		{
			
			//isRunnning≈–∂œfish «∑Ò“—æ≠‘⁄∆¡ƒª…œœ‘ æ
			if(m_FishingNet[i]->bOver == true)
			{
				m_FishingNet[i]->stopAllActions(); 
				m_FishingNet[i]->getParent()->removeChild(m_FishingNet[i],true);
				deleNum.push_back(all); 
			}
			all++;
			if(all > 30)
				break;
		}
		for(int i=0; i< deleNum.size(); i++)
		{
			m_FishingNet.erase(m_FishingNet.begin()+deleNum[i]);
			for(int j=0; j<deleNum.size();j++)
			{
				deleNum[j]--;
			}
		}   
	} 
}
void FishLayer::addNet(char cBulletTypes,Point pos,char buletBeiShu,char cPos )
{
	FishingNet* fishingnet = FishingNet::create(cBulletTypes,cPos);
	m_FishingNet.push_back(fishingnet);  
	fishingnet->buletBeiShu  =  buletBeiShu;
	this->addChild(fishingnet,50); 
 
	if(bNetChoose == true)
	{
		bNetChoose = false; 
	
	}
	else
	{
		bNetChoose = true;  
	} 
	 
	fishingnet->showAt(pos); 

	//char tmp_tmp[30];
	//int tmpsuiji = (int)(CCRANDOM_0_1()*6);

	//sprintf(tmp_tmp,"yuwang_texiao_%d", 4); //( tmpsuiji == 6 ? 5 : tmpsuiji ) 

	//auto yw_texiao_animation = AnimationCache::getInstance()->getAnimation(tmp_tmp);
	//auto yw_texiao_animate = Animate::create(yw_texiao_animation);
 //
	//auto _fishingNet_texiao = Sprite::create();
	//_fishingNet_texiao->setScale(0.9);
	//_fishingNet_texiao->setPosition(pos);
	//this->addChild(_fishingNet_texiao,1001);
	//_fishingNet_texiao->runAction(Sequence::create(yw_texiao_animate,RemoveSelf::create(),nullptr));
}

void FishLayer::addFish(float dt)
{
    int countToAdd = CCRANDOM_0_1() * 10 + 1;
    int countHasAdded = 0;

 
	int type = CCRANDOM_0_1()*2;
	Fish* fish = Fish::create((FishType)type);
	m_Fishes.push_back(fish);
	 

	if (!m_Fishes.empty()) 
	{
		for(auto sp : m_Fishes)
		{
			Fish* fish = sp;

			if(fish->getParent() == NULL)
			{
				this->addChild(fish);
				this->resetFish(fish);
				countHasAdded++;
				if(countToAdd == countHasAdded)
				{
					break;
				}
			}
		}
	}
//	libcmt.lib°±”Î∆‰À˚ø‚µƒ π”√≥ÂÕª£ª«Î π”√ /NODEFAULTLIB:library
	//this->scheduleUpdate();


		/*
    CCObject* iterator;
    CCARRAY_FOREACH(m_Fishes,  iterator)
	{
        Fish* fish = (Fish*)iterator;
        if(fish->getParent() == NULL){
            this->addChild(fish);
            this->resetFish(fish);
            countHasAdded++;
            if(countToAdd == countHasAdded){
                break;
            }
        }
    }
	*/
}


FishLayer::~FishLayer()
{ 


	int i;
	if (!m_Fishes.empty()) 
	{
		for(auto sp : m_Fishes)
		{
			Fish* fish = sp;
			this->removeChild(fish);
		}
	}
	m_Fishes.clear();

	if (!m_FishingNet.empty()) 
	{
		for(auto sp1 : m_FishingNet)
		{
			FishingNet* fish1 = sp1;
			this->removeChild(fish1);
		}
	}
	m_FishingNet.clear();


	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors();

	/*for(i = 0;i<m_vcFish.size();)
	{
		Fish *pFish = m_vcFish[i];
		m_vcFish.erase(m_vcFish.begin()+i);
		delete pFish;
	}

	for(i = 0;i<m_vcFreeFish.size();)
	{
		Fish *pFish = m_vcFreeFish[i];
		m_vcFreeFish.erase(m_vcFreeFish.begin()+i);
		delete pFish;
	}


	for(i = 0;i<m_vcFishGroup.size();)
	{
		FishGroup *pGroup = m_vcFishGroup[i];
		m_vcFishGroup.erase(m_vcFishGroup.begin()+i);
		delete pGroup;
	}

	for(i = 0;i<m_vcFreeFishGroup.size();)
	{
		FishGroup *pGroup = m_vcFreeFishGroup[i];
		m_vcFreeFishGroup.erase(m_vcFreeFishGroup.begin()+i);
		delete pGroup;
	}

	if(m_pFish != NULL)
	{
		delete(m_pFish);
		m_pFish = NULL;
	}	
	*/ 
}




void FishLayer::resetFish(Fish* fish)
{
    
	Point start, destination;
	float startX, startY, endX, endY;
	Size winSize = Director::getInstance()->getWinSize();
	Size fishSize = fish->getFishSprite()->getContentSize();
	int direction = CCRANDOM_0_1()*2;
	if(direction){
		fish->setRotation(-90);
		startX = winSize.width + fishSize.width*0.5;
		endX = -fishSize.width*0.5;
	}else{
		fish->setRotation(90);
		startX = -fishSize.width*0.5;
		endX = winSize.width + fishSize.width*0.5;
	}
	startY = CCRANDOM_0_1()*(winSize.height-2*fishSize.height)+fishSize.height;
	endY = startY;

	start = Point(startX, startY);
	destination = Point(endX, endY);
	fish->setPosition(start); 
}
  
 

FishGroup* FishLayer::GetFreeFishGroup(int iGroupMainID,int iScriptID,int iTrackID,int iNowFrameIndex)
{
  FishGroup* pFishGroup = NULL; /* 
	if(!m_vcFreeFishGroup.empty())
	{
		pFishGroup = m_vcFreeFishGroup[0];
		m_vcFreeFishGroup.erase(m_vcFreeFishGroup.begin());
		pFishGroup->Reset(iGroupMainID,iScriptID,iTrackID,iNowFrameIndex);
	}
	else
	{
		pFishGroup = new FishGroup(this,iGroupMainID,iScriptID,iTrackID,iNowFrameIndex);
	}*/
	return pFishGroup;
}


void FishLayer::JudgeIfNeedEraseFishGroup(int iFishMainID,int iFishSubID)
{
/*	for(int i = 0;i<m_vcFishGroup.size();i++)
	{
		if(m_vcFishGroup[i]->m_iGroupMainID == iFishMainID)
		{
			m_vcFishGroup[i]->m_cSubLiveFlag[iFishSubID-1] = 0;
		}
		if (iFishMainID == 16)
		{
			for(int j = 0;j<m_vcFish.size();j++)
			{
				if(m_vcFish[j]->m_iMainID == iFishMainID)
				{
					printf("%d ",j);
				}
			}
			printf("\n");
		}
		if(m_vcFishGroup[i]->m_iGroupMainID == iFishMainID && m_vcFishGroup[i]->IsAllFishCreate()) //”„»∫¿ÔÀ˘”–”„∂º“—æ≠¥¥Ω®ÕÍ±œ
		{
			bool bNoGroupFish = true;
			for(int j = 0;j<m_vcFish.size();j++)
			{
				if(m_vcFish[j]->m_iMainID == iFishMainID)
				{
					bNoGroupFish = false;
					break;
				}
			}
			if(bNoGroupFish)
			{

				//printf("…æ≥˝”„»∫[%d],sub[%d]\n",iFishGroupID,iSubFishID);
				m_vcFreeFishGroup.push_back(m_vcFishGroup[i]);
				m_vcFishGroup.erase(m_vcFishGroup.begin()+i);				
			}
			break;
		}
	}
	*/
}
	



Fish* FishLayer::GetFishInfo(int iMainID,int iSubID)
{

	if (!m_Fishes.empty()) 
	{
		for(auto sp : m_Fishes)
		{
			Fish* fish = sp;

			if(fish->m_iMainID == iMainID && fish->m_iSubID == iSubID)
			{
				return fish;
			}
		}
	} 
	return NULL;
}





Fish *FishLayer::ShowDeadFish(int iMainID,int iSubID,int iPos)
{
	/*
	for(int i = 0;i<m_vcFish.size();i++)
	{
		if(m_vcFish[i]->m_iMainID == iMainID && m_vcFish[i]->m_iSubID == iSubID)
		{
			//printf("ShowDeadFish:MainID[%d],SubId[%d],pos[%d]\n",iMainID,iSubID,iPos);
			//wfpos
			//m_vcFish[i]->SetFishDead(iPos);
			return m_vcFish[i];
		}
	}	*/ 
	return NULL;
	
}



Fish* FishLayer::GroupAddTrackFish(int iFishType,bool bBigFish,int iMainID,int iSubID,int iTrackID, int iNowFrameIndex,int iCreateFrame,Point mMove)
{
	Fish* pFish =Fish::create(iFishType);
	 
	//≈–∂œ∏√Ãı”„ «∑Ò «Ω˚÷π…˙≥…µƒ
	/*if(m_pFishTollGate->JudgeIsForbidFish(iMainID,iSubID))
	{
		printf("AddFishΩ˚÷π…˙≥…[%d]-[%d]\n",iMainID,iSubID);
		return NULL;
	}*/ 
	if(pFish != NULL)
	{
		bool bSetOk = pFish->SetGroupFishInfo(iMainID,iSubID,iFishType,iTrackID,bBigFish,mMove,iNowFrameIndex);//÷ÿ–¬…Ë∂®”„µƒ∆‰À˚–≈œ¢
		if(bSetOk)
		{
			this->addChild(pFish,40-iFishType); 
			m_Fishes.push_back(pFish); 
			 
		}
		else
		{
		 
		}
		
	 
	}   
	else
	{
		printf("AddFishError:type[%d],bBig[%d],MainID[%d],subId[%d],track[%d] ,frame[%d]\n",iFishType,bBigFish,iMainID,iSubID,iTrackID, iNowFrameIndex);
	}
	return pFish;
}

Fish* FishLayer::AddTrackFish(Fish *pFish,int iFishType,bool bBigFish,int iMainID,int iSubID,int iTrackID, int iNowFrameIndex,int iCreateFrame)
{
	//≈–∂œ∏√Ãı”„ «∑Ò «Ω˚÷π…˙≥…µƒ
	/*if(m_pFishTollGate->JudgeIsForbidFish(iMainID,iSubID))
	{
		printf("AddFishΩ˚÷π…˙≥…[%d]-[%d]\n",iMainID,iSubID);
		return NULL;
	}*/ 
	if(pFish != NULL)
	{
		bool bSetOk = pFish->SetFishInfo(iMainID,iSubID,iFishType,iTrackID,bBigFish,iNowFrameIndex);//÷ÿ–¬…Ë∂®”„µƒ∆‰À˚–≈œ¢
		if(bSetOk)
		{
		 
			if(iFishType == 25 || iFishType == 24 || iFishType == 45)
			{
				this->addChild(pFish,41);
			}
			else
			{
				this->addChild(pFish,40-iFishType);
			}  
			m_Fishes.push_back(pFish); 
			 
		}
		else
		{
			 
		}
	 
	}   
	else
	{
		printf("AddFishError:type[%d],bBig[%d],MainID[%d],subId[%d],track[%d] ,frame[%d]\n",iFishType,bBigFish,iMainID,iSubID,iTrackID, iNowFrameIndex);
	}
	return pFish;
}

Fish* FishLayer::AddFreeFish(Fish *pFish,int iFishType,int iMainID,int iSubID,int iExistFrames,int iX,int iY,int iSpeed,double dAngleValue,double dAngleSpeed)
{

	/*if(pFish != NULL)
	{
		pFish->SetFishInfo(iMainID,iSubID,iFishType,iExistFrames,iX,iY,iSpeed,dAngleValue,dAngleSpeed);
		this->addChild(pFish);

		m_Fishes.pushBack(pFish);	
		if(iSubID == 0)
		{
			m_iNowSingleFishNum++;		
		}	
	}   */
	return pFish;
}
 

 
FishGroup* FishLayer::CreatFishGroup(int iScriptID,int iTrackID,int iMainID,int iNowFrameIndex/* = 0*/,int iGapTime/* = 0*/,int iMultiFishFlag /*= 0*/)
{
	//≈–∂œ“ªœ¬ «∑Ò“—æ≠”–∏√IDµƒ”„»∫¥Ê‘⁄
	for(int i = 0;i<m_vcFishGroup.size();i++)
	{
		if(m_vcFishGroup[i]->m_iGroupMainID == iMainID)
		{
			//_log(_ERROR,"FM","“—æ≠”–[%d]”„»∫¥Ê‘⁄",iMainID);
			return NULL;
		}
	}
	FishGroup *pFishGroup = pFishGroup = new FishGroup(this,iMainID,iScriptID,iTrackID,iNowFrameIndex);
	//GetFreeFishGroup(iMainID,iScriptID,iTrackID,iNowFrameIndex);	
	if(pFishGroup != NULL) 
	{		
		m_vcFishGroup.push_back(pFishGroup);  
		return pFishGroup;
	}
	return pFishGroup;
}

void FishLayer::ClearAllElement(bool bNeedClearTask/* =true*/)
{
	/*int i = 0;
	for(i = 0;i<m_vcFish.size();)
	{
		EraseFishFromVC(m_vcFish[0]);	
	}
	for(i = 0;i<m_vcFishGroup.size();i++)
	{
		m_vcFreeFishGroup.push_back(m_vcFishGroup[i]);
	}
	m_vcFishGroup.clear();

	*/
 
}

 
  

void FishLayer::GetNowNewFishType(vector<int>&vcNewFishType,char cFishType)
{

	int FishNumMax[MAX_FISH]={1,1,8,8,8, 8,8,8,6,5, 6,6,6,6,2, 2,1,1,1,1, 1,1};
	int FishNumMin[MAX_FISH]={1,1,4,4,4, 4,4,4,3,3, 3,3,3,3,2, 2,1,1,1,1, 1,1};

	
	int FishNum[MAX_FISH];
	memset(FishNum,0,sizeof(FishNum));
	int i,j;

	int iTempNum;
	if(GameScene::cGameType != 2)
	{
		iTempNum = 15;
	}
	else
	{
		iTempNum = 10;
	}
	for (i=0; i<iTempNum; i++)
	{
		FishNum[i] = CCRANDOM_0_1()*(FishNumMax[i]-FishNumMin[i]+1)+FishNumMin[i];
	}

	for(i = 0;i<iTempNum;i++)
	{

		if( cFishType == 1&& i>16)//boss
		{
			int iFishTypeNum = 0; 
			vcNewFishType.push_back(i);
			/*
			if (!m_Fishes.empty()) 
			{
				for(auto sp : m_Fishes)
				{
					Fish* fish = sp; 
					if(fish->m_iFishType == i )  //÷ªÀ„µ•”„
					{
						iFishTypeNum++;
					}

				}
			}  
			if(iFishTypeNum < FishNum[i])
			{
				
			}*/
		}
		if(cFishType ==2 && i<2) //÷ªÀÊª˙–°”„(“‘»∫ ˝º«)
		{
			vcNewFishType.push_back(i);
			/*
			int iFishTypeNum = 0;
			for(j = 0;j<m_vcFishGroup.size();j++)
			{

				if(FishScript::GetFishTypeByScriptID(m_vcFishGroup[j]->m_iFishScriptID) == i)  //÷ªÀ„◊‘”…”„»∫
				{
					iFishTypeNum++;
				}
			}
			if(iFishTypeNum < FishNum[i])
			{
				
			}*/
		}	
		if(cFishType == 3 && i>1 && i<17)
		{
			vcNewFishType.push_back(i);

			/*int iFishTypeNum = 0;  
			if (!m_Fishes.empty()) 
			{
				for(auto sp : m_Fishes)
				{
					Fish* fish = sp; 
					if(fish->m_iFishType == i )  //÷ªÀ„µ•”„
					{
						iFishTypeNum++;
					}

				}
			} 
			if(iFishTypeNum < FishNum[i])
			{
				
			}*/
		} 

	}
} 
unsigned int FishLayer::GetFishMainID()
{
	m_iNowMaxFishMainID++; 
	return m_iNowMaxFishMainID;
}



void FishLayer::updataFisDelDingPing(float dt)
{ 

	
}


void FishLayer::updateFishMove(float dt)
{
    
    
    //cocos2d::log("scene init updateFishMove1");
    
    if(bDingping == true  )
    {
        return;
    }
    static float ft = 0.0f;
    ft += dt;
    while(ft >= timeUpdate) // 0.028)
    {
        
        
        if (!m_Fishes.empty())
        {
            for(int i=0; i< m_Fishes.size(); i++)
            {
                if(m_Fishes[i]->bDead == false)
                {
                    m_Fishes[i]->UpdateFishwf(ft);
                }
            }
            
        }
        
        
        
        
        if(bDingping == false)
        {
            vector<int> ppp;
            if(m_fishLineUp.Update(ppp))
            {
                
                
                for (int i=0; i< ppp.size(); i++)
                {
                    FishGroup *PFishGroup = NULL;
                    
                    
                    PFishGroup = CreatFishGroup(ppp[i],0,GetFishMainID());  //…˙≥…ÀÊª˙”„»∫
                }
                
            }
        }
        if(m_FishingNet.size() >50)
        {
            
            ClearNet();
        }
        
        
        if (!m_Fishes.empty())
        {
            int iDeadNum = 0;
            for(int i=0; i< m_Fishes.size(); i++)
            {
                if(m_Fishes[i]->bDead == true)
                {
                    for(int j=0; j<4; j++)
                    {
                        if(m_Fishes[i] == ShootFish[j])
                        {
                            ShootFish[j] = NULL;
                        }
                    }
                    iDeadNum++;
                    
                }
            }
            
            
            if(iDeadNum >150)
            {
                vector<int> deleNum;
                int all =0;
                deleNum.clear();
                
                for(int i=0; i< m_Fishes.size(); i++)
                {
                    if(m_Fishes[i]->bDead == true)
                    {
                        
                        this->removeChild(m_Fishes[i], true);
                        deleNum.push_back(all);
                        if(deleNum.size()> 20)
                            break;
                    }
                    all++;
                }
                for(int i=0; i< deleNum.size(); i++)
                {
                    m_Fishes.erase(m_Fishes.begin()+deleNum[i]);
                    for(int j=0; j<deleNum.size();j++)
                    {
                        deleNum[j]--;
                    }
                }
            }
            
        }
        
        if(bDingping == true)
        {
            return;
        } 
        
        //m_iNowTollGateStatus =REST_STATUS;
        //∏˘æ›”„»∫Ω≈±æ≈–∂œ «∑Ò“™‘ˆº”–¬µƒ”„
        for(int i = 0;i<m_vcFishGroup.size();)
        {
            if(m_vcFishGroup[i]->Update() == false)
            {
                m_vcFishGroup.erase(m_vcFishGroup.begin()+i);
            } 
            else
            {
                i++;
            }
        }
        if(m_iNowTollGateStatus != REST_STATUS)//øÕªß∂À∫£π÷∆⁄≤ª…˙≥…∆‰À˚”„,∑˛ŒÒ∆˜’’≥£Ã·«∞…˙≥…
        {
            bool bNeedCreateFish = true;
            //static int wfwf = 0;
            vcFishInSwatch vcTempCrateFishInfo;
            JudgeIfNeedCreatSwatchFish(true,vcTempCrateFishInfo);
            if(!vcTempCrateFishInfo.empty()  && bNeedCreateFish)
            {
                //wfwf ++;
                for(int i = 0;i<vcTempCrateFishInfo.size();i++)
                {
                    //	if(vcTempCrateFishInfo[i].iFishType >= 0 && vcTempCrateFishInfo[i].iFishType<= 7)  //…˙≥…µ•”„
                    if(vcTempCrateFishInfo[i].iFishType != 100)
                    {
                        if(vcTempCrateFishInfo[i].iExistFramesOrTrack == 0)  //◊‘”……˙≥…µƒ”„
                        {
                            //if(vcTempCrateFishInfo[i].iFishType  == 20 )
                            //{
                            if(GameScene::cGameType == 1)
                            {
                                if(vcTempCrateFishInfo[i].iFishType  > 23 )
                                {
                                    
                                    char cTempType = 3+ CCRANDOM_0_1()*18;
                                    
                                    //vcTempCrateFishInfo[i].iFishType  =   3+ CCRANDOM_0_1()*11;
                                    int a  = CCRANDOM_0_1()*100;
                                    if(a < 30)
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 21;
                                    }
                                    else if(a < 40)
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 22;
                                    }
                                    else
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 16+ CCRANDOM_0_1()*5;
                                    }
                                }
                            }
                            if(GameScene::cGameType == 0  )
                            {
                                if(vcTempCrateFishInfo[i].iFishType  > 23 )
                                {
                                    
                                    int a  = CCRANDOM_0_1()*100;
                                    if(a > 40)
                                    {
                                        int typewfrand  = CCRANDOM_0_1()*100;
                                        if(typewfrand < 35)
                                        {
                                            vcTempCrateFishInfo[i].iFishType  = 21;
                                        }
                                        else if(typewfrand < 35)
                                        {
                                            vcTempCrateFishInfo[i].iFishType  = 22;
                                        }
                                        else
                                        {
                                            vcTempCrateFishInfo[i].iFishType  = 16+ CCRANDOM_0_1()*5;
                                        }
                                        
                                        
                                    }
                                    else
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 3+ CCRANDOM_0_1()*17;
                                    }
                                    
                                }
                                if(vcTempCrateFishInfo[i].iFishType  == 20 )
                                {
                                    
                                    
                                    int a  = CCRANDOM_0_1()*100;
                                    if(a > 40)
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 20;
                                    }
                                    else
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 3+ CCRANDOM_0_1()*17;
                                    }
                                }
                                if(vcTempCrateFishInfo[i].iFishType  == 21 )
                                {
                                    
                                    
                                    int a  = CCRANDOM_0_1()*100;
                                    if(a > 45)
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 21;
                                    }
                                    
                                    else
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 3+ CCRANDOM_0_1()*17;
                                    }
                                    
                                }
                                if(vcTempCrateFishInfo[i].iFishType  == 22 )
                                {
                                    int a  = CCRANDOM_0_1()*100;
                                    if(a > 60)
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 22;
                                    }
                                    
                                    else
                                    {
                                        vcTempCrateFishInfo[i].iFishType  = 3+ CCRANDOM_0_1()*17;
                                    }
                                    
                                }
                                
                            } 
                            Fish* fish =Fish::create(vcTempCrateFishInfo[i].iFishType); 
                            
                            
                            bool bSetOk = fish->SetFishInfo(0,0,vcTempCrateFishInfo[i].iFishType,vcTempCrateFishInfo[i].iTrackOrScriptID,true,0);//÷ÿ–¬…Ë∂®”„µƒ∆‰À˚–≈œ¢
                            if(bSetOk)
                            {
                                this->addChild(fish,40-vcTempCrateFishInfo[i].iFishType); 
                                m_Fishes.push_back(fish); 
                                
                            } 
                        }  
                    }
                    else if(vcTempCrateFishInfo[i].iFishType == 100) //…˙≥…”„»∫
                    { 
                        CreatFishGroupwf(vcTempCrateFishInfo[i].iTrackOrScriptID,vcTempCrateFishInfo[i].iExistFramesOrTrack,
                                         0,0,0,0);   
                        
                    }
                }
            }	 
        } 
        
        
       
        if(GameScene::cGameType == 1)
        {
            m_fTimeGroup += 1;
            if(m_fTimeGroup >380)
            {
                
                char cTempType = 12+ CCRANDOM_0_1()*8;
                Fish* fish =Fish::create(cTempType);
                
                bool bSetOk = fish->SetFishInfo(0,0,cTempType,GetRandTrack(),true,0);//÷ÿ–¬…Ë∂®”„µƒ∆‰À˚–≈œ¢
                if(bSetOk)
                {
                    this->addChild(fish,40-cTempType);
                    m_Fishes.push_back(fish);
                    
                }
                m_fTimeGroup = 0;
            }
            
        }
        if(GameScene::cGameType == 0)
        {
            //if(Fishnodown == false)
            if(false)
            {
                m_fTimeGroup += 1;
                if(m_fTimeGroup >250)
                {
                    
                    char cTempType = 8+ CCRANDOM_0_1()*12;
                    Fish* fish =Fish::create(cTempType);
                    
                    bool bSetOk = fish->SetFishInfo(0,0,cTempType,GetRandTrack(),true,0);//÷ÿ–¬…Ë∂®”„µƒ∆‰À˚–≈œ¢
                    if(bSetOk)
                    {
                        this->addChild(fish,40-cTempType);
                        m_Fishes.push_back(fish);
                        
                    }
                    m_fTimeGroup = 0;
                }
            }
            
        }
        
        if(GameScene::cGameType == 2)
        {
            m_fTimeGroup += 1;
            if(m_fTimeGroup >80)
            { 
                
                char cTempType =  CCRANDOM_0_1()*14;
                Fish* fish =Fish::create(cTempType); 
                
                bool bSetOk = fish->SetFishInfo(0,0,cTempType,GetRandTrack(),true,0);//÷ÿ–¬…Ë∂®”„µƒ∆‰À˚–≈œ¢
                if(bSetOk)
                {
                    this->addChild(fish,40-cTempType);
                    
                    m_Fishes.push_back(fish); 
                    
                }
                m_fTimeGroup = 0;
            }
            if(  cNewBoss > cNowBoss)
            {
                if(cNewBoss>23)
                {
                    return;
                }
                cNowBoss = cNewBoss;
                int iRandFishType =cNowBoss+22 ;
                
                
                Fish* fish =Fish::create(iRandFishType); 
                
                bool bSetOk = fish->SetFishInfo(0,0,iRandFishType,GetRandTrack(),true,0);//÷ÿ–¬…Ë∂®”„µƒ∆‰À˚–≈œ¢
                if(bSetOk)
				{
					this->addChild(fish,40-iRandFishType);

					m_Fishes.push_back(fish); 
				 
				}
			}
		}  
		ft -= 0.028;
	} 

	
	//cocos2d::log("scene init updateFishMove2");

}



int  FishLayer::GetRandTrack()
{

	char cTemp = CCRANDOM_0_1()*100;
	if(cTemp > 50)
	{
		return 4000+CCRANDOM_0_1()*20;
	}
	else 
	{
		return 4500+CCRANDOM_0_1()*20;
	}
}



void  FishLayer::CreatFishGroupwf(int iScriptID,int iTrackID,int iMainID,int iNowFrameIndex,int iMultiFishFlag,int iCreateFrame)//…˙≥…”„»∫ 
{


	//≈–∂œ“ªœ¬ «∑Ò“—æ≠”–∏√IDµƒ”„»∫¥Ê‘⁄
	for(int i = 0;i<m_vcFishGroup.size();i++)
	{
		if(m_vcFishGroup[i]->m_iGroupMainID == iMainID)
		{ 
			return ;
		}
	} 
	FishGroup*	pFishGroup = new FishGroup(this,iMainID,iScriptID,iTrackID,iNowFrameIndex);
	if(pFishGroup != NULL)
	{
		pFishGroup->m_iCreateFrame = iCreateFrame;
	}   


	if(pFishGroup != NULL) 
	{		
		m_vcFishGroup.push_back(pFishGroup); 	
	}
	return ;
}





void FishLayer::updateFishlayerPeriod(float dt)
{ 
	int a = CCRANDOM_0_1()*100;
	if(GameHallLayer::RoomType == 0)
	{
		if(a < 30)
		{
			fishlayerPeriod = 1;
		}else if(a < 100)
		{
			fishlayerPeriod = 2;
		}
    }else
	{
		if(a < 15)
		{
			fishlayerPeriod = 1;
		}else if(a < 60)
		{
			fishlayerPeriod = 2;
		}else 
		{
			fishlayerPeriod = 3;
		}
	}
	
}
 
bool FishLayer::CheckOutBoard(Point TempPoint)
{
	return false;
} 


    
void FishLayer::TollGateUpdate()
{

	if(m_iNowTollGateStatus != NORMAL_STATUS && m_iNowTollGateStatus != REST_STATUS)
	{
		return;
	}
	m_iNowTollGateFrameIndex++;

	if(m_iNowTollGateFrameIndex > m_iNowTollGateMaxFrame)
	{
		m_iNowTollGateStatus = REST_STATUS;//Ω¯»Î–›”Ê∆⁄
		//–›”Ê∆⁄ªπ «”…∑˛ŒÒ∆˜Õ®÷™∞…,Õ¨≤Ω“ªœ¬
	  
			m_iNowFishRestConFrame = -1;
			//printf("Ω¯»Î–›”Ê∆⁄\n");
			printf("go in fish rest\n");
	 
	}
	if(m_iNowTollGateStatus == REST_STATUS)
	{
		m_iNowFishRestConFrame++;
        int iNowRestConSec = (m_iNowFishRestConFrame*g_iFrameTime)/1000;//√Î
		if(iNowRestConSec >= g_iTollGateRestTime)
		{
			//Ω¯»Îœ¬“ªπÿø®
			int iNextTGID = GetNextTollGateID(m_iNowTollGateID);
			//SetNowTollGateInfo(iNextTGID);
			//printf("Ω¯»Îœ¬“ªπÿ:[%d]\n",iNextTGID);
			printf("next Level:[%d]\n",iNextTGID);
		}
	}
	else if(m_iNowTollGateStatus == NORMAL_STATUS)  //’˝≥£≥ˆ”„
	{
		vcFishInSwatch vcTempCrateFishInfo;
		JudgeIfNeedCreatFish(vcTempCrateFishInfo,m_iNowTollGateFrameIndex);	
		if(!vcTempCrateFishInfo.empty())
		{
			for(int i = 0;i<vcTempCrateFishInfo.size();i++)
			{
				m_iNowFishMaxMainID++;
 		
			}
		}		
	}
}  
void FishLayer::Reset()
{
	m_iNowTollGateID = 0;
	m_iNowTollGateStatus = 0;
	m_iNowTollGateFrameIndex = 0;
	m_iNowTollGateMaxFrame = 0;
	m_iNowFishMaxMainID = 0;
	m_iNowFishRandSwatchID = 0;
	m_iNowFishFixedLineupID = 0; 
} 

void FishLayer::SetNowTollGateInfo(int iNowTollGateID,int iNowRandSwatchID,int iNowFishLineupID,int iNowFishMaxID/* = 0*/,int iNowFrameIndex/* = 0*/,int iGapTime/* = 0*/)
{
	m_iNowTollGateID = iNowTollGateID;
	m_iNowTollGateStatus = NORMAL_STATUS;
	m_iNowTollGateFrameIndex = iNowFrameIndex;
	m_iNowFishMaxMainID = iNowFishMaxID;

	m_iNowFishRandSwatchID = iNowRandSwatchID;
	m_iNowFishFixedLineupID = iNowFishLineupID;

	m_fishRandSwatch.Reset();
	m_fishLineUp.Reset(m_iNowFishFixedLineupID,iNowFrameIndex);

	m_bServerSendRestMsg = false;
	m_vcForbidFish.clear();

	std::map<int,TollGateInfoDef>::iterator pos;
	pos = m_mapTollGate.find(m_iNowTollGateID);
	if(pos != m_mapTollGate.end())
	{
		m_iNowTollGateMaxFrame = (pos->second.iTollGateConTime*1000)/g_iFrameTime;
	}


}

void FishLayer::CreateFishForEnterInGame(vector<int>vcMainID,vector<int>vcMultiFishFlag,int iNowFrameIndex,int iTmGap)
{
	int iTempFishID = 0;
	int iTempFrame = 0;
	for(iTempFrame = 0;iTempFrame<iNowFrameIndex;iTempFrame++)
	{
 
	}
}

bool FishLayer::JudgeIsForbidFish(int iMainID,int iSubID)
{
	for(int i = 0;i<m_vcForbidFish.size();i++)
	{
		if(m_vcForbidFish[i].iMainID == iMainID && m_vcForbidFish[i].iSubID == iSubID)
		{
			return true;
		}
	}
	return false;
}


void FishLayer::AddForbidFish(int iMainID,int iSubID)
{
	ForbidFishDef temp;
	temp.iMainID = iMainID;
	temp.iSubID  = iSubID;
	m_vcForbidFish.push_back(temp);
}

int FishLayer::GetTollGateLeftTime()
{
	int iLeftSec = (m_iNowTollGateMaxFrame-m_iNowTollGateFrameIndex)*g_iFrameTime/1000;
	return iLeftSec;
}

int FishLayer::GetNowTollGateBackID()
{
	std::map<int,TollGateInfoDef>::iterator pos;
	pos = m_mapTollGate.find(m_iNowTollGateID);
	if(pos != m_mapTollGate.end())
	{
		return pos->second.iTollGateBackID; 
	}
	return 0;
}

void FishLayer::JudgeIfNeedCreatFish(vcFishInSwatch &vcNeedCreateFish,int iFrameIndex)
{
	
}

int  FishLayer::GetTollGateBackID(int iTollGateID)
{
	int iBackID = 0;
	std::map<int,TollGateInfoDef>::iterator pos;
	pos = m_mapTollGate.find(iTollGateID);
	if(pos!= m_mapTollGate.end())
	{
		iBackID  = pos->second.iTollGateBackID;
	}
	return iBackID;
}

int  FishLayer::GetNextTollGateID(int iTollGateID)
{
	int iNextTGID = 0;
	std::map<int,TollGateInfoDef>::iterator pos;
	pos = m_mapTollGate.find(iTollGateID);
	if(pos!= m_mapTollGate.end())
	{
		iNextTGID  = pos->second.iNextTollGateID;
	}
	return iNextTGID;
}

int  FishLayer::GetFirstTollGateID()
{
	if(!m_mapTollGate.empty())
	{
		std::map<int,TollGateInfoDef>::iterator pos = m_mapTollGate.begin();
		return pos->first;
	}
	return -1;
}

void FishLayer::LoadAllTollGateData()
{
	 
}
 

void FishLayer::JudgeIfNeedCreatSwatchFish(bool bNeedCreate,vcFishInSwatch &vcNeedCreateFish) // «∑Ò–Ë“™…˙≥…—˘±æ”„
{
	m_fishRandSwatch.update(bNeedCreate,vcNeedCreateFish); //√ª”–πÃ∂®’Û–Õ”„≤≈…˙≥…—˘±æ”„

}



void FishLayer::SetRandom()
{
    int cTempRandom =  0;
    for(int i =0; i<2; i++)
    {
		float iTempFloat = CCRANDOM_0_1()*23.999;
        int iTemp =iTempFloat;
        if(i == 1 && iTemp %2 == 0)
        {
            iTemp += 1;
        }
        else if(i == 0 && iTemp %2 != 0 )
        {
            iTemp  -= 1;
        }
		cBossThree[i] = 40+22+iTemp;
         
    }
    cBossThree[2] = 45;
    
    iBossTime[0] =  7+CCRANDOM_0_1()*100;
    iBossTime[1] =  115+CCRANDOM_0_1()*105;
    iBossTime[2] =  7+CCRANDOM_0_1()*213;
    
    paomadengwf.clear();
    paomadeng TempPaoma;
    TempPaoma.ShowTime =7+CCRANDOM_0_1()*213;
    TempPaoma.Type = 1;
    paomadengwf.push_back(TempPaoma);
    
    int iCount = 3+CCRANDOM_0_1()*3;
    for(int i=0; i< iCount; i++)
    {
        paomadeng TempPaomaok;
        TempPaomaok.ShowTime =7+CCRANDOM_0_1()*213;
        int iTempRandom = CCRANDOM_0_1()*100;
        if(iTempRandom < 70)
        {
            TempPaomaok.Type = 1;
        }
        else if(iTempRandom < 85)
        {
             TempPaomaok.Type = 2;
        }
        else
        {
             TempPaomaok.Type = 3;
        }
        paomadengwf.push_back(TempPaomaok);
        
    }
    
    
    
    iBossTime[3]=  7+CCRANDOM_0_1()*213;
    
    //108              115  105
    iRandomTime[0] = 7+CCRANDOM_0_1()*108;
    iRandomTime[1] = 7+CCRANDOM_0_1()*108;
    iRandomTime[2] = 115+CCRANDOM_0_1()*105;
    iRandomTime[3] = 115+CCRANDOM_0_1()*105;
    iRandomTime[4] = 7+CCRANDOM_0_1()*213;
    cTempRandom = CCRANDOM_0_1()* 100;
    if(cTempRandom > 50)
    {
        iRandomPanZi[1] = 30;
    }
    else
    {
        iRandomPanZi[1] = 31;
    }
    
    cTempRandom = CCRANDOM_0_1()* 100;
    if(cTempRandom > 50)
    {
        iRandomPanZi[2] = 30;
    }
    else
    {
        iRandomPanZi[2] = 31;
    }
    
    cTempRandom = CCRANDOM_0_1()* 100;
    if(cTempRandom > 85 )
    {
        iRandomPanZi[0] = 32;
    }
    else if(cTempRandom > 70)
    {
        iRandomPanZi[0] = 33;
    }
    
    else if(cTempRandom > 55)
    {
        iRandomPanZi[0] = 34;
    }
    else if(cTempRandom > 20)
    {
        iRandomPanZi[0] = 35;
    }
    else
    {
        iRandomPanZi[0] = 36;
    }
    
    
    
    
    
    cTempRandom = CCRANDOM_0_1()* 100;
    if(cTempRandom > 85 )
    {
        iRandomPanZi[3] = 38;
    }
    else if(cTempRandom > 70)
    {
        iRandomPanZi[3] = 39;
    }
    
    else if(cTempRandom > 55)
    {
        iRandomPanZi[3] = 40;
    }
    else if(cTempRandom > 20)
    {
        iRandomPanZi[3] = 41;
    }
    else
    {
        iRandomPanZi[3]  = 42;
    }
    
    
    
    cTempRandom = CCRANDOM_0_1()* 100;
    if(cTempRandom > 50)
    {
        cTempRandom = CCRANDOM_0_1()* 100;
        if(cTempRandom > 90 )
        {
            iRandomPanZi[4] = 32;
        }
        else if(cTempRandom > 80)
        {
            iRandomPanZi[4] = 33;
        }
        
        else if(cTempRandom > 70)
        {
            iRandomPanZi[4] = 34;
        }
        else if(cTempRandom > 35)
        {
            iRandomPanZi[4] = 35;
        }
        else
        {
            iRandomPanZi[4] = 36;
        }
        
    }
    else
    {
        cTempRandom = CCRANDOM_0_1()* 100;
        if(cTempRandom > 90 )
        {
            iRandomPanZi[4] = 38;
        }
        else if(cTempRandom > 80)
        {
            iRandomPanZi[4] = 39;
        }
        
        else if(cTempRandom > 70)
        {
            iRandomPanZi[4] = 40;
        }
        else if(cTempRandom > 35)
        {
            iRandomPanZi[4] = 41;
        }
        else
        {
            iRandomPanZi[4]  = 42;
        }

    }
    
}
void FishLayer::updateFishlayerBoss(float delta)
{
    //cocos2d::log("scene init updateFishlayerBoss 1");
    
    if(bDingping == true)
        return;
    if(GameScene::cGameType != 1)
    {
        if( bYuZheng == false )
        {
            if(FishLayer::m_fUpdateFishYuZheng == 0 && FishLayer::bYuZheng == false && FishLayer::bMoveFast == false )
            {
                m_vcFishGroup.clear();
            }
            m_fUpdateFishYuZheng++;
            
            if(bFirstYuZhen == true )
            {
                if(m_fUpdateFishYuZheng == 1)
                {
                    
                    int iFishLineupIndex = FishLineup::GetOneRandFixedLineupID();
                    m_fishLineUp.Reset(iFishLineupIndex,0);
                    timeUpdate = 0.01;
                }
                if(m_fUpdateFishYuZheng == 3)
                {
                    bYuZheng = true;
                    bFirstYuZhen = false;
                    timeUpdate = 0.028;
                    
                    
                    //	return;
                }
            }
            
            
            
            if(m_fUpdateFishYuZheng == 430)
            {
                
                m_iNowTollGateStatus = REST_STATUS;
                YuChao->setVisible(true);
                
            }
            else if(m_fUpdateFishYuZheng  == 435)
            {
                bMoveFast = true;
            }
            else if(m_fUpdateFishYuZheng == 445)
            {
                int iFishLineupIndex = FishLineup::GetOneRandFixedLineupID();
                m_fishLineUp.Reset(iFishLineupIndex,0);
                bYuZheng = true;
                YuChao->setVisible(false);
                m_fUpdateFishBoss  = 0;
                 Fishnodown = true;
                
            }
        }
        if(bMoveFast == true|| bYuZheng == true || bFirstYuZhen == true)
        {
            return;
        }
    }
    
    m_fUpdateFishBoss++;
    char cFishType = 124;
    
   
    for(int i =0; i< paomadengwf.size(); i++)
    {
        if( paomadengwf[i].ShowTime ==m_fUpdateFishBoss && UserDefault::getInstance()->getIntegerForKey("ios_dengluFlag") == 0 )
       {
           
            auto gonggao = Gonggao::create(paomadengwf[i].Type);
            gonggao->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.8));
            addChild(gonggao,1000);
            gonggao->setScale(0.8f);
           
       }
    }
    cocos2d::log("******m_fUpdateFishBoss %d" , m_fUpdateFishBoss);
    
    
    for(int i=0; i<2; i++)
    {
        if(m_fUpdateFishBoss == (iBossTime[i] - 1))
        {
            
            bosstype =  cBossThree[i]-40;
            sprBossFish->stopAllActions();
            if(GameScene::cGameType == 0)
            {
                if(i == 0)
                {
                    bosstype = 24;
                }
                else if(i == 1)
                {
                    bosstype = 25;
                }
                
                char cTempAni[100];
                sprintf(cTempAni,"fish_animation_%d_%d",GameHallLayer::RoomType,bosstype);
                Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni);
                Animate*  fishAnimate = Animate::create(fishAnimation);
                sprBossFish->runAction(RepeatForever::create(fishAnimate));
                sprBossFish->setScale(0.9f);
            }
            else if (GameScene::cGameType == 1)
            {
                char cTempAni[100];
                sprintf(cTempAni,"fish_animationwf_%d_%d",LogoLayer::room,bosstype);
                Animation* fishAnimation = AnimationCache::getInstance()->getAnimation(cTempAni);
                Animate*  fishAnimate = Animate::create(fishAnimation);
                sprBossFish->runAction(RepeatForever::create(fishAnimate));
                sprBossFish->setScale(0.9f);
            }
            
            if(bosstype == 24 || bosstype%2 == 0)
            {
                BigBossFont->setVisible(false);
                
                SmallBossFont->setVisible(true);
                BossBgGuang->setVisible(true);
                this->getChildByTag(269)->setVisible(true);
                
                
                
            }
            else
            {
                
                SmallBossFont->setVisible(false);
                
                BigBossFont->setVisible(true);
                BossBgGuang->setVisible(true);
                this->getChildByTag(269)->setVisible(true);
                
            }
            
            
            
            FadeOut *ac14=FadeOut::create(0.45f);
            FadeIn *ac15=FadeIn::create(0.45f);
            Sequence *spawn=Sequence::create(ac14,ac15,NULL);
            BossBgGuang->runAction(RepeatForever::create(spawn));

            sprBossFish->setVisible(true);
            
            
            
        } 
        else if(m_fUpdateFishBoss == iBossTime[i])
        {
            if(GameScene::bOverBisai == false)
            {
                GameBegin::stopMusic();
                GameBegin::playMusic("bosscome.mp3");
            }
            if(GameScene::cGameType == 0)
            {
                cFishType =  bosstype ;
            }
            else
            {
                cFishType = cBossThree[i];
            }
            
            
        }
        else if(m_fUpdateFishBoss == (iBossTime[i] + 3))
        {
            
            SmallBossFont->setVisible(false);
            
            BigBossFont->setVisible(false);
            
            BossBgGuang->stopAllActions();
            BossBgGuang->setVisible(false);
            this->getChildByTag(269)->setVisible(false);
            
            sprBossFish->stopAllActions();
            sprBossFish->setVisible(false);
            
        }
      
        else if(m_fUpdateFishBoss == (iBossTime[i] + 45))
        {
            if(GameScene::bOverBisai == false)
            {
                GameBegin::stopMusic();
                GameBegin::playMusic("bosscome.mp3",2);
            }
        }
    }
    for(int i=0; i< 5; i++)
    {
        if(iRandomTime[i] == m_fUpdateFishBoss)
        {
            cFishType = iRandomPanZi[i];
        }
    }
    
    if(m_fUpdateFishBoss == iBossTime[2])
    {
        Fish* fish =Fish::create(45);
        if(fish->CreateTrackFish(fish,45,true))
        {
            AddTrackFish(fish,fish->m_iFishType,true,GetFishMainID(),0,fish->m_iTrackID,0,0);
            
        }
        
        
    }
    
    if(m_fUpdateFishBoss == 1)
    {
        Fishnodown = false;
        if(GameScene::cGameType == 1)
        {
            
            bMoveFast = true;
        }
        m_iNowTollGateStatus = NORMAL_STATUS;
    }
    
    
    if(m_fUpdateFishBoss == 3)
    {
       
        if(GameScene::cGameType == 1)
            bMoveFast = false;
        
    }
    else if(m_fUpdateFishBoss == 10)
    {
        if(GameHallLayer::RoomType == 93 && !LogoLayer::dengluFlag )
        {
        /*    Fish* fish =Fish::create(46);
            if(fish->CreateTrackFish(fish,46,true))
            {
                AddTrackFish(fish,fish->m_iFishType,true,GetFishMainID(),0,fish->m_iTrackID,0,0);
                
            }*/
            
            return;
        }
    }
    else if(m_fUpdateFishBoss == 15)
    {
        timeUpdate = 0.028;
    }
    
    else if(m_fUpdateFishBoss == 60)
    {
        if(GameHallLayer::RoomType == 93  )
        {
            
        /*    Fish* fish =Fish::create(46);
            if(fish->CreateTrackFish(fish,46,true))
            {
                AddTrackFish(fish,fish->m_iFishType,true,GetFishMainID(),0,fish->m_iTrackID,0,0);
                
            }*/
            
        }
    }
    
    
    else if(m_fUpdateFishBoss == 129)
    {
        if(GameHallLayer::RoomType == 93 )
        {
            
        /*    Fish* fish =Fish::create(46);
            if(fish->CreateTrackFish(fish,46,true))
            {
                AddTrackFish(fish,fish->m_iFishType,true,GetFishMainID(),0,fish->m_iTrackID,0,0);
                
            }*/
            
        }
    }
    
    
    
    else if(m_fUpdateFishBoss == 175)
    {
        if(GameHallLayer::RoomType == 93 )
        {
            
        /*    Fish* fish =Fish::create(46);
            if(fish->CreateTrackFish(fish,46,true))
            {
                AddTrackFish(fish,fish->m_iFishType,true,GetFishMainID(),0,fish->m_iTrackID,0,0);
                
            }*/
            
            return;
        }
    }
    else if(m_fUpdateFishBoss == 215)
    {
        if(GameHallLayer::RoomType == 93 )
        {
            
         /*   Fish* fish =Fish::create(46);
            if(fish->CreateTrackFish(fish,46,true))
            {  
                AddTrackFish(fish,fish->m_iFishType,true,GetFishMainID(),0,fish->m_iTrackID,0,0);
                
            }*/
            
        }
    } 
    else if( m_fUpdateFishBoss == 265)
    {
        
        m_fUpdateFishBoss = 2;
        
        
        SetRandom();
        
        return;
    }
    
    if(cFishType != 124)
    {
        if(cFishType == 37)
        {
            Fish* fish =Fish::create(cFishType);  
            this->addChild(fish); 
            m_Fishes.push_back(fish); 
        }
        else //轨迹鱼
        { 
            
            if(cFishType > 31 && cFishType < 37)
            {  
                int iFishNum = 0;
                if(cFishType < 35)
                {
                    iFishNum = 3;
                }
                else if(cFishType < 36)
                {
                    iFishNum = 4;
                }
                else if(cFishType < 37)
                {
                    iFishNum = 5;
                } 
                int iTrackID = FishTrack::GetRandTrackID(8);//随机指定鱼的轨迹,返回-1为此鱼没有对应轨迹
                
                for(int i= 0; i< iFishNum; i++)
                {
                    Fish* fish =Fish::create(cFishType,i,iFishNum);    
                    if(fish->CreateTrackFish(fish,cFishType,false,iTrackID))
                    { 
                        AddTrackFish(fish,fish->m_iFishType,true,GetFishMainID(),0,fish->m_iTrackID,0,0);
                        
                    } 
                } 
            }
            else if(cFishType > 37&& cFishType < 43)
            {
                int iFishNum = 0;
                if(cFishType < 41)
                {
                    iFishNum = 3;
                }
                else if(cFishType < 42)
                {
                    iFishNum = 4;
                }
                else if(cFishType < 43)
                {
                    iFishNum = 5;
                }  
                for(int i= 0; i< iFishNum; i++)
                {
                    int iTrackID = FishTrack::GetRandTrackID(8);//随机指定鱼的轨迹,返回-1为此鱼没有对应轨迹 
                    Fish* fish =Fish::create(cFishType,10,iFishNum);   
                    //this->resetFish(fish); 
                    //	GetFreeFish(iRandFishType,fish);  
                    if(fish->CreateTrackFish(fish,cFishType,false,iTrackID))
                    { 
                        AddTrackFish(fish,fish->m_iFishType,true,GetFishMainID(),0,fish->m_iTrackID,0,0); 
                    } 
                } 
            } 
            else 
            {
                Fish* fish =Fish::create(cFishType); 
                
                //this->resetFish(fish);
                
                //	GetFreeFish(iRandFishType,fish); 
                if(fish->CreateTrackFish(fish,cFishType,true))
                { 
                    
                    AddTrackFish(fish,fish->m_iFishType,true,GetFishMainID(),0,fish->m_iTrackID,0,0);
                    
                } 
            }
        }
    }
    
    if(m_fUpdateFishBoss %15 == 0)
    {
        
        Fish* fish =Fish::create(150);
        this->addChild(fish,41);
        m_Fishes.push_back(fish);
    }
    
}
 
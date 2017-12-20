 
#include "StaticData.h"
#include "GameHallLayer.h"
#include "LoadRes.h"
USING_NS_CC;
using namespace std;

static StaticData* _sharedStaticData = NULL;
 int StaticData::roomread = 0;
StaticData* StaticData::sharedStaticData()
{
    if(_sharedStaticData == NULL )
	{
        _sharedStaticData = new StaticData();
        _sharedStaticData->init();
    }
	else
	{
		if(roomread != LoadRes::RoomType)
		{
			delete _sharedStaticData;
			_sharedStaticData =NULL;
			_sharedStaticData = new StaticData();
			_sharedStaticData->init();
		}
	}
    return _sharedStaticData;
}
StaticData::StaticData()
{
	 
	roomread = LoadRes::RoomType;
	char cFishInfoName[50];
	for(int i=0; i< 12; i++)
	{ 
		if(LoadRes::RoomType == i)
		{
			if(i>2)
			{
				string resourceRoad =  FileUtils::getInstance()->getWritablePath(); 
				sprintf(cFishInfoName,"scene%dfishinfo.plist",i+1);
				_staticDataPath =  resourceRoad + cFishInfoName;
				return;
			}
			else
			{

				sprintf(cFishInfoName,"scene/scene%dfishinfo.plist",i+1);
			}
			break;
		}
	}

	for(int i=0; i< 4; i++)
	{ 
		if(LoadRes::RoomType - 90== i)
		{
			sprintf(cFishInfoName,"BSscene/BSscene%dfishinfo.plist",i+2);
			if(LoadRes::RoomType == 93)
			{
				sprintf(cFishInfoName,"BSscene/BSscene%dfishinfo.plist",i+1);	
			}
			break;
		}
	}

    _staticDataPath = cFishInfoName;
}
StaticData::~StaticData()
{
    CC_SAFE_RELEASE_NULL(_dictionary);
}
bool StaticData::init()
{
    _dictionary = CCDictionary::createWithContentsOfFile(_staticDataPath.c_str());
    CC_SAFE_RETAIN(_dictionary);
    return true;
}
const char* StaticData::stringFromKey(string key)
{
    return _dictionary->valueForKey(key)->getCString();
}
int StaticData::intFromKey(string key)
{
    return _dictionary->valueForKey(key)->intValue();
}
float StaticData::floatFromKey(string key)
{
    return _dictionary->valueForKey(key)->floatValue();
}
bool StaticData::booleanFromKey(string key)
{
    return _dictionary->valueForKey(key)->boolValue();
}
cocos2d::Point StaticData::pointFromKey(string key)
{
    return PointFromString(_dictionary->valueForKey(key)->getCString());
}
cocos2d::Rect StaticData::rectFromKey(string key)
{
    return RectFromString(_dictionary->valueForKey(key)->getCString());
}
cocos2d::Size StaticData::sizeFromKey(string key)
{
    return SizeFromString(_dictionary->valueForKey(key)->getCString());
}
void StaticData::purge()
{
    CC_SAFE_RELEASE_NULL(_sharedStaticData);
}
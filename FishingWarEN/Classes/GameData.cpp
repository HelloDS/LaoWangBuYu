#include "GameData.h"
USING_NS_CC;
using namespace std;


static GameData * _sharedGameData = NULL;

GameData * GameData::sharedGameData()
{
	if(_sharedGameData == NULL)
	{
		_sharedGameData = new GameData();
		_sharedGameData->init();
	}
	return _sharedGameData;
}

GameData::GameData()
{
	std::string gameinfo = "gameinfo.plist"; 
	std::string gameinfowritelujin =  FileUtils::getInstance()->getWritablePath()+gameinfo; 
	_gameDataPath = gameinfo;

}

GameData::~GameData()
{
	CC_SAFE_RELEASE_NULL(_dictionary);
}

bool GameData::init()
{
	_dictionary = CCDictionary::createWithContentsOfFile(_gameDataPath.c_str());
	CC_SAFE_RETAIN(_dictionary);
	return true;
}

void GameData::purge()
{
    CC_SAFE_RELEASE_NULL(_sharedGameData);
}

const char* GameData::stringFromKey(string key)
{
    return _dictionary->valueForKey(key)->getCString();
}
int GameData::intFromKey(string key)
{
    return _dictionary->valueForKey(key)->intValue();
}
float GameData::floatFromKey(string key)
{
    return _dictionary->valueForKey(key)->floatValue();
}
bool GameData::booleanFromKey(string key)
{
    return _dictionary->valueForKey(key)->boolValue();
}
cocos2d::Point GameData::pointFromKey(string key)
{
    return PointFromString(_dictionary->valueForKey(key)->getCString());
}
cocos2d::Rect GameData::rectFromKey(string key)
{
    return RectFromString(_dictionary->valueForKey(key)->getCString());
}
cocos2d::Size GameData::sizeFromKey(string key)
{
    return SizeFromString(_dictionary->valueForKey(key)->getCString());
}
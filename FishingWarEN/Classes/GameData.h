
#ifndef __GameInfo__StaticData__
#define __GameInfo__StaticData__

#include "cocos2d.h"
#define GAME_DATA_STRING(key) GameData::sharedGameData()->stringFromKey(key)
#define GAME_DATA_INT(key) GameData::sharedGameData()->intFromKey(key)
#define GAME_DATA_FLOAT(key) GameData::sharedGameData()->floatFromKey(key)
#define GAME_DATA_BOOLEAN(key) GameData::sharedGameData()->booleanFromKey(key)
#define GAME_DATA_POINT(key) GameData::sharedGameData()->pointFromKey(key)
#define GAME_DATA_RECT(key) GameData::sharedGameData()->rectFromKey(key)
#define GAME_DATA_SIZE(key) GameData::sharedGameData()->sizeFromKey(key)

class GameData : public cocos2d::CCObject
{
public:    
    static GameData* sharedGameData();

    /**
     *	@brief	 外部访问接口
     *
     *	@param 	key 	对应的static_data.plist中的Key
     *
     *	@return	对应的Value
     */
    const char* stringFromKey(std::string key);
    int intFromKey(std::string key);
    float floatFromKey(std::string key);
    bool booleanFromKey(std::string key);
    cocos2d::Point pointFromKey(std::string key);
    cocos2d::Rect rectFromKey(std::string key);
    cocos2d::Size sizeFromKey(std::string key);
    
    /**
     *	@brief	 内存不足时调用
     */
    void purge();
    
    CC_SYNTHESIZE_READONLY(std::string, _gameDataPath, GameDataPath);

protected:
    cocos2d::CCDictionary* _dictionary;
 


private:
    GameData();
    ~GameData();
    bool init();
};
#endif /* defined(__FishingJoy__StaticData__) */

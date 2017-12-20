#ifndef __SHAKE_H__ 
#define __SHAKE_H__ 

#include "cocos2d.h" 
USING_NS_CC; 


class CCShake : public cocos2d::ActionInterval 
{ 
public: 
	CCShake(); 
 
	static CCShake *create(float d, float strength ); 
 
	static CCShake *createWithStrength(float d, float strength_x, float strength_y ); 
	bool initWithDuration(float d, float strength_x, float strength_y ); 

	virtual CCShake* clone() const override;
	virtual CCShake* reverse() const override;

protected: 

	void startWithTarget(cocos2d::CCNode *pTarget); 
	void update(float time); 
	void stop(void); 

	CCPoint m_StartPosition; 
	unsigned int _times;
	 FiniteTimeAction *_innerAction;
	// Strength of the action 
	float m_strength_x, m_strength_y; 
}; 

#endif //__SHAKE_H__ 
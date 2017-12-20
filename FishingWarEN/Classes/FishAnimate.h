#ifndef _FISHLAYER_H
#define _FISHLAYER_H
#include "cocos2d.h"
#include "3d/CCAnimation3D.h"
#include "3d/CCAnimate3D.h"
#include "3d/CCMesh.h"
#include "Math/Vec2.h"

NS_CC_BEGIN 
//����������ʾ3D��ģ�͵Ĳ�
class FishAnimate : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	//��ʼ����ǰ��
    virtual bool init();  
    CREATE_FUNC(FishAnimate);
	//���ػ��ƺ���
	virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
protected:

	//�㾫��
    cocos2d::Sprite3D*		m_Sprite;
	//��ǰ�εĶ���
    cocos2d::Animate3D*		m_Swim;
	//���˵Ķ���
    cocos2d::Animate3D*		m_Hurt;
	//uv����ֵ
	Vec2					m_LightAni;
}
;

NS_CC_END

#endif
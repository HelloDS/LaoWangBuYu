
#include "FishAnimate.h"

USING_NS_CC;

Scene * FishAnimate::createScene()
{
	auto scene = Scene::create();

	auto layer = FishAnimate::create();

	scene->addChild(layer);

	return scene;
}

bool FishAnimate::init()
{
	//����ģ���ļ�
	std::string fileName = "tortoise.c3b";
    m_Sprite = Sprite3D::create(fileName);
    m_Sprite->setScale(0.1f);
    auto s = Director::getInstance()->getWinSize();
    m_Sprite->setPosition(Vec2(s.width / 2.f, s.height / 2.f));
    addChild(m_Sprite);
	
	//��ȡ����������Ϣ
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
		//����ʼ��1.933���ȡΪ��Ӿ����
        m_Swim = Animate3D::create(animation, 0.f, 1.933f);
        m_Swim->retain();

		//��1.933�뵽2.8���ȡΪ���˵Ķ���
        m_Hurt = Animate3D::create(animation, 1.933f, 2.8f);
        m_Hurt->retain();

		//�þ���ѭ��������Ӿ�͵����˶���
		Sequence*	pSequence = Sequence::create(m_Swim,m_Hurt,NULL);
		m_Sprite->runAction(RepeatForever::create(pSequence));
    }

	// ��vsh��fshװ���һ��������Shader�ļ���
    auto glprogram = GLProgram::createWithFilenames("UVAnimation.vsh", "UVAnimation.fsh");
	// ��Shader�ļ��������Shader
    auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
	// �������������õ�Shader
    m_Sprite->setGLProgramState(glprogramstate);

	//�����������õ���ͼ��
	auto textrue1 = Director::getInstance()->getTextureCache()->addImage("tortoise.png");
	//����ͼ���ø�Shader�еı���ֵu_texture1
    glprogramstate->setUniformTexture("u_texture1", textrue1);

	//����������ͼ��
	auto textrue2 = Director::getInstance()->getTextureCache()->addImage("caustics.png");
	//����ͼ���ø�Shader�еı���ֵu_lightTexture
	glprogramstate->setUniformTexture("u_lightTexture", textrue2);

	//ע�⣬���ڲ�����ͼ������ϣ�����ڽ���UV����ʱ�ܲ����ķ�����Ч��������������������UVѰַ��ʽΪGL_REPEAT��
	Texture2D::TexParams		tRepeatParams;
	tRepeatParams.magFilter = GL_LINEAR_MIPMAP_LINEAR;
	tRepeatParams.minFilter = GL_LINEAR;
	tRepeatParams.wrapS = GL_REPEAT;
	tRepeatParams.wrapT = GL_REPEAT;
	textrue2->setTexParameters(tRepeatParams);

	//�������������һ���������ɫ����������Ϊ��ɫ��
	Vec4  tLightColor(1.0,1.0,1.0,1.0);
    glprogramstate->setUniformVec4("v_LightColor",tLightColor);

	//������һ�Σ���Ϊ�˽������Զ����Shader�����ǵ�ģ�Ͷ�����֯��ʽ����ƥ�䡣ģ�͵Ķ�������һ�����λ�ã����ߣ�ɫ�ʣ������Լ���������Ϣ����Shader��Ҫ���ڲ���Ӧ�Ķ�������ͨ����ģ����Ӧ�Ķ����������ݽ��а󶨲�����ȷ��ʾ�����㡣
	long offset = 0;
	auto attributeCount = m_Sprite->getMesh()->getMeshVertexAttribCount();
    for (auto k = 0; k < attributeCount; k++) {
        auto meshattribute = m_Sprite->getMesh()->getMeshVertexAttribute(k);
        glprogramstate->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
                                             meshattribute.size,
                                             meshattribute.type,
                                             GL_FALSE,
                                             m_Sprite->getMesh()->getVertexSizeInBytes(),
                                             (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    }

	//uv������ʼֵ��Ϊ0
	m_LightAni.x = m_LightAni.y = 0;
	return true;
}

void FishAnimate::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
	if(m_Sprite)
	{
		
		auto glprogramstate = m_Sprite->getGLProgramState();
		if(glprogramstate)
		{
			m_LightAni.x += 0.01;
			if(m_LightAni.x > 1.0)
			{
				m_LightAni.x-= 1.0;
			}
			m_LightAni.y += 0.01;
			if(m_LightAni.y > 1.0)
			{
				m_LightAni.y-= 1.0;
			}
			glprogramstate->setUniformVec2("v_animLight",m_LightAni);
		}
	}
	Node::draw(renderer,transform,flags);
}
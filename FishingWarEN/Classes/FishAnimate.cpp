
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
	//加载模型文件
	std::string fileName = "tortoise.c3b";
    m_Sprite = Sprite3D::create(fileName);
    m_Sprite->setScale(0.1f);
    auto s = Director::getInstance()->getWinSize();
    m_Sprite->setPosition(Vec2(s.width / 2.f, s.height / 2.f));
    addChild(m_Sprite);
	
	//获取骨骼动画信息
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
		//从起始到1.933秒截取为游泳动作
        m_Swim = Animate3D::create(animation, 0.f, 1.933f);
        m_Swim->retain();

		//从1.933秒到2.8秒截取为受伤的动作
        m_Hurt = Animate3D::create(animation, 1.933f, 2.8f);
        m_Hurt->retain();

		//让精灵循环播放游泳和的受伤动作
		Sequence*	pSequence = Sequence::create(m_Swim,m_Hurt,NULL);
		m_Sprite->runAction(RepeatForever::create(pSequence));
    }

	// 将vsh与fsh装配成一个完整的Shader文件。
    auto glprogram = GLProgram::createWithFilenames("UVAnimation.vsh", "UVAnimation.fsh");
	// 由Shader文件创建这个Shader
    auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
	// 给精灵设置所用的Shader
    m_Sprite->setGLProgramState(glprogramstate);

	//创建海龟所用的贴图。
	auto textrue1 = Director::getInstance()->getTextureCache()->addImage("tortoise.png");
	//将贴图设置给Shader中的变量值u_texture1
    glprogramstate->setUniformTexture("u_texture1", textrue1);

	//创建波光贴图。
	auto textrue2 = Director::getInstance()->getTextureCache()->addImage("caustics.png");
	//将贴图设置给Shader中的变量值u_lightTexture
	glprogramstate->setUniformTexture("u_lightTexture", textrue2);

	//注意，对于波光贴图，我们希望它在进行UV动画时能产生四方连续效果，必须设置它的纹理UV寻址方式为GL_REPEAT。
	Texture2D::TexParams		tRepeatParams;
	tRepeatParams.magFilter = GL_LINEAR_MIPMAP_LINEAR;
	tRepeatParams.minFilter = GL_LINEAR;
	tRepeatParams.wrapS = GL_REPEAT;
	tRepeatParams.wrapT = GL_REPEAT;
	textrue2->setTexParameters(tRepeatParams);

	//在这里，我们设置一个波光的颜色，这里设置为白色。
	Vec4  tLightColor(1.0,1.0,1.0,1.0);
    glprogramstate->setUniformVec4("v_LightColor",tLightColor);

	//下面这一段，是为了将我们自定义的Shader与我们的模型顶点组织方式进行匹配。模型的顶点数据一般包括位置，法线，色彩，纹理，以及骨骼绑定信息。而Shader需要将内部相应的顶点属性通道与模型相应的顶点属性数据进行绑定才能正确显示出顶点。
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

	//uv滚动初始值设为0
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
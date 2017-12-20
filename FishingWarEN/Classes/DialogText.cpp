
#include "DialogText.h"

#define FONT_NAME      "minijianling.ttf"
#define FONT_SIZE      24

//////////////////////////////////////////////////////////////////////////
// implement KeyboardNotificationLayer
//////////////////////////////////////////////////////////////////////////

static Rect getRect(Node * node)
{
    Rect rc;
    rc.origin = node->getPosition();
    rc.size = node->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}


DialogTextLayer::DialogTextLayer(): _trackNode(0)
{
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(DialogTextLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(DialogTextLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void DialogTextLayer::keyboardWillShow(IMEKeyboardNotificationInfo& info)
{
    log("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
        info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);

    if (! _trackNode)
    {
        return;
    }

    auto rectTracked = getRect(_trackNode);
    log("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
        rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);

    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
    {
        return;
    }

    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
    log("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);

    // move all the children node of KeyboardNotificationLayer
    auto& children = getChildren();
    Node * node = 0;
    ssize_t count = children.size();
    Vec2 pos;
    for (int i = 0; i < count; ++i)
    {
        node = children.at(i);
        pos = node->getPosition();
        pos.y += adjustVert;
        node->setPosition(pos);
    }
}

bool DialogTextLayer::onTouchBegan(Touch  *touch, Event  *event)
{
    log("++++++++++++++++++++++++++++++++++++++++++++");
    _beginPos = touch->getLocation();    
    return true;
}

void DialogTextLayer::onTouchEnded(Touch  *touch, Event  *event)
{
    if (! _trackNode)
    {
        return;
    }
    
    auto endPos = touch->getLocation();    

    float delta = 5.0f;
    if (::abs(endPos.x - _beginPos.x) > delta
        || ::abs(endPos.y - _beginPos.y) > delta)
    {
        // not click
        _beginPos.x = _beginPos.y = -1;
        return;
    }

    // decide the trackNode is clicked.
    Rect rect;
    auto point = convertTouchToNodeSpaceAR(touch);
    log("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);

    rect = getRect(_trackNode);
    log("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
        rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    this->onClickTrackNode(rect.containsPoint(point));
    log("----------------------------------");
}

//////////////////////////////////////////////////////////////////////////
// implement TextFieldTTFActionTest
//////////////////////////////////////////////////////////////////////////

std::string DialogText::subtitle() const
{
    return "CCTextFieldTTF with action and char limit test";
}

void DialogText::onClickTrackNode(bool bClicked)
{
    auto pTextField = (TextFieldTTF*)_trackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        log("TextFieldTTFActionTest:TextFieldTTF attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        log("TextFieldTTFActionTest:TextFieldTTF detachWithIME");
        pTextField->detachWithIME();
    }
}

DialogText * DialogText::createScene(int width,int high)
{
	auto scene = new DialogText();
	scene->init(width,high);
	scene->autorelease();
	return scene;
}

bool DialogText::init(int width,int high)
{
    _charLimit = 20000;

	textWidth = width;
	textHeight = high;

    _textFieldAction = RepeatForever::create(Sequence::create(FadeOut::create(0.25),FadeIn::create(0.25),nullptr));
    _textFieldAction->retain();
    _action = false;

    // add TextFieldTTF
	visibleSize = Director::getInstance()->getVisibleSize(); 
    _textField = TextFieldTTF::textFieldWithPlaceHolder(GAME_DATA_STRING("dianjishuru"),FONT_NAME,FONT_SIZE);
	_textField->setDimensions(width,high);
	_textField->setHorizontalAlignment(TextHAlignment::LEFT);
    addChild(_textField);

    _textField->setDelegate(this);
    
    _textField->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

    _trackNode = _textField;

	return true;
}
 
// TextFieldDelegate protocol
bool DialogText::onTextFieldAttachWithIME(TextFieldTTF * sender)
{
    if (! _action)
    {
        _textField->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
        _textField->runAction(_textFieldAction);
        _action = true;
    }
    return false;
}

bool DialogText::onTextFieldDetachWithIME(TextFieldTTF * sender)
{
    if (_action)
    {
        _textField->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
        _textField->stopAction(_textFieldAction);
        _textField->setOpacity(255);
        _action = false;
		_textField->setDimensions(textWidth,textHeight);
    }
    return false;
}

bool DialogText::onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen)
{
 
    if ('\n' == *text)
    {
        return false;
    }
 
    if (sender->getCharCount() >= _charLimit)
    {
        return true;
    }
 
	_textField->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    return false;
}

bool DialogText::onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen)
{
   _textField->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    return false;
}

bool DialogText::onDraw(TextFieldTTF * sender)
{
    return false;
}

void DialogText::callbackRemoveNodeWhenDidAction(Node * node)
{
    this->removeChild(node, true);
}

std::string DialogText::getString()
{
	return _textField->getString();
}

#ifndef __DIALOG_TEXT__
#define __DIALOG_TEXT__
#include "cocos-ext.h"
#include "GameData.h"
#include "Gongxi.h"
#include "cocos2d.h"

class DialogTextLayer : public Layer, public IMEDelegate
{
public:
    DialogTextLayer();

    virtual std::string subtitle() const = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);

    // Layer
    bool onTouchBegan(Touch  *touch, Event  *event);
    void onTouchEnded(Touch  *touch, Event  *event);

protected:
    Node * _trackNode;
    Vec2  _beginPos;
};

class DialogText : public DialogTextLayer, public TextFieldDelegate
{
    TextFieldTTF *    _textField;
    Action *          _textFieldAction;
    bool                _action;
    int                 _charLimit;       // the textfield max char limit

public:

	static DialogText * createScene(int width,int high);
	virtual bool init(int width,int high);
    void callbackRemoveNodeWhenDidAction(Node * node);

    // KeyboardNotificationLayer
    virtual std::string subtitle() const override;
    virtual void onClickTrackNode(bool bClicked);

	int textWidth;
	int textHeight;
    
    Size visibleSize;

	std::string  getString();

    // TextFieldDelegate
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender);
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender);
    virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen) override;
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen) override;
    virtual bool onDraw(TextFieldTTF * sender);
};
#endif 
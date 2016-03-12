#include "StoryPlayer.h"

static StoryPlayer* storyPlayer = NULL;

StoryPlayer* StoryPlayer::getInstance()
{
    if (storyPlayer == NULL)
    {
        storyPlayer = new StoryPlayer;
    }

    return storyPlayer;
}

void StoryPlayer::playStory(int startTag, int endTag, Node* scene)
{
    if (!scene || startTag > endTag)
    {
        return;
    }

    auto layer = Layer::create();
    scene->addChild(layer);

    init(layer);

    tagID = startTag;
    m_pName = LabelTTF::create("", "/fonts/MFYaYuan_Noncommercial-Regular.ttf", 24);
    m_pName->setColor(Color3B(0, 0, 0));
    m_pContext = LabelTTF::create("(Click...)", "/fonts/RTWSYueGoTrial-Regular.ttf", 22, Size(490, 0), TextHAlignment::CENTER);
    m_pContext->setColor(Color3B(0, 0, 0));
    m_pName->setPosition(315.9f, 640 - 462.0f);
    m_pContext->setPosition(479, 117.6f);
    Director::getInstance()->pause();

    layer->addChild(m_pName);
    layer->addChild(m_pContext);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* t, Event* e){
        if (tagID <= endTag)
        {
            m_pName->setString(TextReader::getInstance()->getName(tagID));
            log(TextReader::getInstance()->getName(tagID));
            m_pContext->setString(TextReader::getInstance()->getContent(tagID));
            imageSetter(scene, tagID);
            tagID++;
        }
        else
        {
            layer->removeAllChildren();
            layer->removeFromParent();
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            Director::getInstance()->resume();
        }
        return true;
    };
    listener->setSwallowTouches(true);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
}

bool StoryPlayer::init(Node* scene)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    chatBg = Sprite::create("chatBg.png");
    chatBg->setScale(0.6f);
    chatBg->setPosition(visibleSize.width / 2, chatBg->getContentSize().height / 2);
    scene->addChild(chatBg);

    return true;
}

void StoryPlayer::imageSetter(Node* scene, int tagID)
{
    auto xx = (Sprite*)scene->getChildByName("xx");
    auto ss = (Sprite*)scene->getChildByName("ss");
    auto hl = (Sprite*)scene->getChildByName("hl");

    switch (tagID)
    {
    case 4:
        xx->setTexture("Drawings/Tag4xx.png");
        break;
    case 5:
        hl->setTexture("Drawings/Tag5hl.png");
        break;
    case 6:
        xx->setTexture("Drawings/Tag6xx.png");
        break;
    case 7:
        hl->setTexture("Drawings/Tag7hl.png");
        break;
    case 8:
        xx->setTexture("Drawings/Tag8xx.png");
        break;
    case 9:
        hl->setTexture("Drawings/Tag9hl.png");
        break;
    case 10:
        xx->setTexture("Drawings/Tag10xx.png");
        break;
    case 11:
        hl->setTexture("Drawings/Tag11hl.png");
        break;
    case 12:
        xx->setTexture("Drawings/Tag12xx.png");
        break;
    case 13:
        hl->setTexture("Drawings/Tag13hl.png");
        break;
    case 14:
        xx->setTexture("Drawings/Tag14xx.png");
        hl->setTexture("Drawings/hl_Origional.png");
        break;
    case 16:
        ss->setTexture("Drawings/Tag16ss.png");
        break;
    case 17:
        ss->setTexture("Drawings/ss_Couhuo.png");
        break;
    case 19:
        ss->setTexture("Drawings/Tag19ss.png");
        scheduleOnce([=](float){
            ss->setTexture("Drawings/ss_Couhuo.png");
        }, 1, "ssOrig");
        break;
    case 20:
        ss->setTexture("Drawings/ss_Couhuo.png");
        break;
    default:
        break;
    }
}

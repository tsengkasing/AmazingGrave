#include "GraveMainScene.h"
#include "StoryPlayer.h"
#include "SceneIntro.h"
#include "SceneMComplete.h"
#include "FlappyBird\FirstGameLayer.h"
#include "ArrowShoot\FirstScene.h"
#include "FastDash\FastDash.h"
#include "ArrowShoot\MainScene.h"
#include "FinalWar\FinalWar.h"
#include "SceneIntro.h"
#include "LevelInfo.h"

extern enum _nowScene nowScene;

Scene* GraveMainScene::createScene()
{
    auto scene = Scene::create();

    auto layer = GraveMainScene::create();

    scene->addChild(layer);

    return scene;
}

bool GraveMainScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // ���õ�ǰ����Ϊһ
    NOW_LEVEL = 1;

    flagzj = false;
    flagss = false;
    flagxx = false;

    flagGame3 = true;
    flagSSGame = true;
    flagFinalGame = true;

    visibleSize = Director::getInstance()->getVisibleSize();

    // �����ײı���
    backGround = Sprite::create("GraveMainScene.png");

    backGround->setPosition(visibleSize / 2);

    addChild(backGround);

    backGround->runAction(Sequence::create(FadeOut::create(0), FadeIn::create(5), nullptr));

    // �����۹��
    light = Sprite::create("light.png");
    light->setPosition(2000, visibleSize.height / 2);
    addChild(light);

    // �������ߵĻ��
    auto emitter1 = ParticleSystemQuad::create("torch.plist");
    emitter1->retain();
    auto torch = ParticleBatchNode::createWithTexture(emitter1->getTexture());
    torch->addChild(emitter1);
    emitter1->setPosition(66, 358);
    emitter1->release();
    addChild(torch);
    torch->runAction(Sequence::create(FadeOut::create(0), FadeIn::create(5), nullptr));

    auto emitter3 = ParticleSystemQuad::create("torch.plist");
    emitter3->retain();
    auto torch2 = ParticleBatchNode::createWithTexture(emitter3->getTexture());
    torch2->addChild(emitter3);
    emitter3->setPosition(960 - 58, 365);
    emitter3->release();
    addChild(torch2);
    torch2->runAction(Sequence::create(FadeOut::create(0), FadeIn::create(5), nullptr));

    // �������ǵľ���
    xxOutOfGrave = Sprite::create("Drawings/xx_Origional.png");
    xxOutOfGrave->setPosition(2000, visibleSize.height / 2 - 80);
    xxOutOfGrave->setScale(0.9f);
    xxOutOfGrave->runAction(FadeOut::create(1));
    addChild(xxOutOfGrave, 0, "xx");

    // 
    ssOutOfGrave = Sprite::create("Drawings/ss_Couhuo.png");
    ssOutOfGrave->setPosition(2000, visibleSize.height / 2 - 80);
    ssOutOfGrave->runAction(FadeOut::create(1));
    ssOutOfGrave->setScale(0.85f);
    addChild(ssOutOfGrave, 0, "ss");

    //  
    zjOutOfGraveInnocent = Sprite::create("Drawings/zj_Innocent.png");
    zjOutOfGraveInnocent->setPosition(2000, visibleSize.height / 2);
    zjOutOfGraveInnocent->runAction(FadeOut::create(1));
    addChild(zjOutOfGraveInnocent);

    //  
    zjOutOfGraveEvilNoWing = Sprite::create("Drawings/zj_Evil_No_Wing.png");
    zjOutOfGraveEvilNoWing->setPosition(2000, visibleSize.height / 2);
    zjOutOfGraveEvilNoWing->runAction(FadeOut::create(1));
    addChild(zjOutOfGraveEvilNoWing);

    //  
    zjOutOfGraveEvilWithWing = Sprite::create("Drawings/zj_Evil_With_Wing.png");
    zjOutOfGraveEvilWithWing->setPosition(2000, visibleSize.height / 2);
    zjOutOfGraveEvilWithWing->runAction(FadeOut::create(1));
    addChild(zjOutOfGraveEvilWithWing);

    auto emitter2 = ParticleSystemQuad::create("Animation/whitelight1.plist");
    emitter2->retain();
    auto batch = ParticleBatchNode::createWithTexture(emitter2->getTexture());
    batch->addChild(emitter2, 0, "emitter");
    emitter2->setPosition(318.9f/0.44f, 548/0.44f);
    emitter2->release();
    zjOutOfGraveInnocent->addChild(batch, 0, "whitelight");

    // ����������Ĺ�������߽�
    zjGravebox = Sprite::create();
    ssGravebox = Sprite::create();
    xxGravebox = Sprite::create();
    zjGravebox->setContentSize(Size(123, 210));
    ssGravebox->setContentSize(Size(123, 210));
    xxGravebox->setContentSize(Size(123, 210));
    zjGravebox->setPosition(710, 195);
    ssGravebox->setPosition(480, 195);
    xxGravebox->setPosition(233.5f, 195);

    zjListener = EventListenerTouchOneByOne::create();
    ssListener = EventListenerTouchOneByOne::create();
    xxListener = EventListenerTouchOneByOne::create();

    zjListener->onTouchBegan = [=](Touch* t, Event* e){
        if (flagzj && e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
        {
            light->runAction(FadeOut::create(1));
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/BGMActive.mp3", true);
            Director::getInstance()->pushScene(TransitionFade::create(1, MainScene::CreateScene()));
            log("zj");
            flagzj = false;
        }

        return false;
    };

    ssListener->onTouchBegan = [=](Touch* t, Event* e){
        if (flagss && e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/BGMActive.mp3", true);
            huoLongFallOver->runAction(FadeOut::create(1));
            xxOutOfGrave->runAction(FadeOut::create(1));
            Director::getInstance()->pushScene(TransitionFade::create(1, FirstGameLayer::createScene()));
            log("ss");
            flagss = false;
        }

        return false;
    };

    xxListener->onTouchBegan = [=](Touch* t, Event* e){
        if (flagxx && e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/BGMActive.mp3", true);
            Director::getInstance()->pushScene(TransitionFade::create(1, FastDash::createScene()));
            log("xx");
            flagxx = false;
        }

        return false;
    };

    addChild(xxGravebox);
    addChild(ssGravebox);
    addChild(zjGravebox);

    // ���С������ת���ƶ������Ķ���
    huoLongFall = Sprite::create("/Drawings/hl_Origional_NOexpression.png");

    // ���ó�ʼ��С������Ϊ0
    huoLongFall->setScale(0.01f);
    huoLongFall->setPosition(417, 486);
    addChild(huoLongFall);
    scale = 0.01f;

    // С����վ������
    huoLongFallOver = Sprite::create("Drawings/hl_Origional.png");
    huoLongFallOver->runAction(FadeOut::create(0));
    huoLongFallOver->setScale(0.9f);
    addChild(huoLongFallOver, 0, "hl");

    // ��Ӻ�ɫ�������컨��
    celling = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("Celling.png"));
    black = LayerColor::create(Color4B(0, 0, 0, 255));
    celling->runAction(FadeOut::create(0));
    black->runAction(FadeOut::create(0));
    addChild(black);
    addChild(celling);
    // ִ���½�����
    scheduleOnce([=](float){
        schedule(schedule_selector(GraveMainScene::huoLongFallAction), 0.02f);
    }, 5, "start");
    // ֹͣ�½�����
    huoLongFall->runAction(Sequence::create(FadeOut::create(0), DelayTime::create(5), FadeIn::create(0.3f), MoveTo::create(5, Vec2(360, 38)), nullptr));
    scheduleOnce([=](float){
        unschedule(schedule_selector(GraveMainScene::huoLongFallAction));
        createBlankCelling();
        // ���������Ժ󲥷ž���
        scheduleOnce([=](float){
            StoryPlayer::getInstance()->playStory(1, 1, this);
            StoryPlayer::getInstance()->playStory(1, 2, this);

        }, 8, "dialogue");
    }, 10, "end");

    scheduleUpdate();

    // �����������
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(zjListener, zjGravebox);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(xxListener, xxGravebox);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ssListener, ssGravebox);
    return true;
}

void GraveMainScene::huoLongFallAction(float dt)
{
    // ���ϵ�����ͼƬ��С
    huoLongFall->runAction(CallFuncN::create([=](Node*){
        huoLongFall->setScale(scale);
        scale += 0.001f;
    }));
    huoLongFall->runAction(RotateBy::create(0, 2));
}

void GraveMainScene::createBlankCelling()
{
    black->runAction(Sequence::create(DelayTime::create(2), CallFunc::create([=](){
        black->runAction(FadeIn::create(0));
    }), nullptr));
    celling->runAction(Sequence::create(DelayTime::create(2), FadeIn::create(2), DelayTime::create(0.5f), FadeOut::create(2), FadeIn::create(2), DelayTime::create(2),
        CallFuncN::create([=](Node*){
        removeChild(celling);
        removeChild(black);
        // �����С�����ӵ�����ʧ
        scheduleOnce([=](float){
            huoLongFall->runAction(FadeOut::create(2));
            // ��ʧ�Ժ��ֳ���
            Vec2 pos = huoLongFall->getPosition();
            scheduleOnce([=](float){
                removeChild(huoLongFall);
                huoLongFallOver->setPosition(pos.x - 50, pos.y);
                huoLongFallOver->runAction(Sequence::create(FadeIn::create(2), nullptr));
                scheduleOnce([=](float){
                    // ���ž���
                    StoryPlayer::getInstance()->playStory(3, 3, this);
                    schedule([=](float){
                        if (!Director::getInstance()->isPaused())
                        {
                            huoLongFallOver->runAction(FadeOut::create(1));
                            Director::getInstance()->pushScene(TransitionFade::create(1, SceneIntro::createScene()));
                            unschedule("replaceToIntro");
                        }
                    }, 1 / 60.0f, "replaceToIntro");
                }, 2, "Tothewall");
            }, 2, "stand");
        }, 3, "huolongStand");
    }), nullptr));

    celling->setPosition(visibleSize / 2);
}

void GraveMainScene::update(float)
{
    log("%d", nowScene);
    switch (nowScene)
    {
    case Idle:
        break;
    case Grave:
        // ��Ϸ��ʼ
        // С���ǵĹײĿ��Ե���
        light->setPositionX(xxGravebox->getPositionX());
        flagxx = true;
        break;
    case Select:
        light->setPositionX(ssGravebox->getPositionX());
        flagss = true;
        flagxx = false;
        break;
    case Game1:
        // ��һ����ϷFastDash������������Ӧ����
        light->setPositionX(ssGravebox->getPositionX());
        if (flagGame3)
        {
            flagGame3 = false;
            huoLongFallOver->runAction(FadeIn::create(1));
            xxOutOfGrave->runAction(FadeIn::create(1));
            xxOutOfGrave->setPosition(huoLongFallOver->getPositionX() + 440, huoLongFallOver->getPositionY() - 100);
            
            scheduleOnce([=](float){
                StoryPlayer::getInstance()->playStory(4, 14, this);
                huoLongFallOver->runAction(FadeOut::create(1));
                xxOutOfGrave->runAction(FadeOut::create(1));
                
                scheduleOnce([=](float){
                    flagss = true;
                }, 1, "��ɭɭ��������׼����һ��");
            }, 1, "���Ǵӹײ�������ͻ�������");
        }
        flagxx = false;
        break;
    case Game2:
        // �ڶ�����ϷFlappyBird������������Ӧ����
        light->setPositionX(zjGravebox->getPositionX());
        if (flagSSGame)
        {
            flagSSGame = false;
            ssOutOfGrave->setPosition(visibleSize.width / 2, huoLongFallOver->getPositionY() - 100);
            ssOutOfGrave->runAction(FadeIn::create(1));
            
            scheduleOnce([=](float){
                StoryPlayer::getInstance()->playStory(15, 16, this);
                ssOutOfGrave->runAction(FadeOut::create(1));
            }, 1, "First");
            
            scheduleOnce([=](float){
                huoLongFallOver->runAction(FadeIn::create(1));
                xxOutOfGrave->runAction(FadeIn::create(1));
                
                scheduleOnce([=](float){
                    StoryPlayer::getInstance()->playStory(17, 18, this);
                    huoLongFallOver->runAction(FadeOut::create(1));
                    xxOutOfGrave->runAction(FadeOut::create(1));
                    
                    scheduleOnce([=](float){
                        ssOutOfGrave->runAction(FadeIn::create(1));
                        
                        scheduleOnce([=](float){
                            StoryPlayer::getInstance()->playStory(19, 19, this);
                            ssOutOfGrave->runAction(FadeOut::create(1));
                            
                            scheduleOnce([=](float){
                                flagzj = true;
                            }, 1, "���Ӽ���������׼����һ��");
                        }, 1, "��������������");
                    }, 1, "��һ��");
                }, 1, "��������˵һ�λ�");
            }, 1, "ɭɭ˵����");
        }
        flagss = false;
        break;
    case Game3:
        // ��������ϷArrorShoot������������Ӧ����
        flagzj = false;
        if (flagFinalGame)
        {
            flagFinalGame = false;
            zjOutOfGraveInnocent->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 40);
            zjOutOfGraveInnocent->runAction(FadeIn::create(1));
            zjOutOfGraveInnocent->setScale(0.44f);
            zjOutOfGraveInnocent->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Vec2(0, 30)), MoveBy::create(1, Vec2(0, -30)), nullptr)));
            
            scheduleOnce([=](float){
                StoryPlayer::getInstance()->playStory(20, 20, this);
                zjOutOfGraveInnocent->runAction(FadeOut::create(1));
                zjOutOfGraveInnocent->getChildByName("whitelight")->getChildByName("emitter")->removeFromParent();

                scheduleOnce([=](float){
                    huoLongFallOver->runAction(FadeIn::create(1));
                    xxOutOfGrave->runAction(FadeIn::create(1));
                    ssOutOfGrave->runAction(FadeIn::create(1));
                    ssOutOfGrave->setPositionX(ssOutOfGrave->getPositionX() + 50);
                    
                    scheduleOnce([=](float){
                        StoryPlayer::getInstance()->playStory(21, 21, this);
                        huoLongFallOver->runAction(FadeOut::create(1));
                        xxOutOfGrave->runAction(FadeOut::create(1));
                        ssOutOfGrave->runAction(FadeOut::create(1));
                        
                        scheduleOnce([=](float){
                            zjOutOfGraveInnocent->setPosition(visibleSize.width / 2, visibleSize.height / 2);
                            zjOutOfGraveInnocent->runAction(FadeIn::create(1));
                            
                            scheduleOnce([=](float){
                                StoryPlayer::getInstance()->playStory(22, 22, this);
                                zjOutOfGraveInnocent->runAction(FadeOut::create(1));
                                
                                scheduleOnce([=](float){
                                    huoLongFallOver->runAction(FadeIn::create(1));
                                    xxOutOfGrave->runAction(FadeIn::create(1));
                                    ssOutOfGrave->runAction(FadeIn::create(1));

                                    scheduleOnce([=](float){
                                        StoryPlayer::getInstance()->playStory(23, 23, this);
                                        huoLongFallOver->runAction(FadeOut::create(1));
                                        xxOutOfGrave->runAction(FadeOut::create(1));
                                        ssOutOfGrave->runAction(FadeOut::create(1));

                                        scheduleOnce([=](float){
                                            zjOutOfGraveEvilWithWing->setPosition(visibleSize.width / 2, visibleSize.height / 2);
                                            zjOutOfGraveEvilWithWing->runAction(FadeIn::create(1));
                                            zjOutOfGraveEvilWithWing->setScale(0.96f);

                                            scheduleOnce([=](float){
                                                StoryPlayer::getInstance()->playStory(24, 24, this);
                                                zjOutOfGraveEvilWithWing->runAction(FadeOut::create(1));


                                                scheduleOnce([=](float){
                                                    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/BGMActive.mp3", true);
                                                    Director::getInstance()->replaceScene(TransitionFade::create(1, FinalWar::createScene()));
                                                }, 1, "begin");
                                            }, 1, "Final");
                                        }, 1, "�ߣ��벻������ͦ�죡");
                                    }, 1, "����");
                                }, 1, "��������Boss��ս");
                            }, 1, "����������");
                        }, 1, "�⻰ʲô��˼");
                    }, 1, "˵����");
                }, 1, "���˳Ծ�");
            }, 5, "С�Ӽ�������");
        }
        break;
    default:
        break;
    }
}
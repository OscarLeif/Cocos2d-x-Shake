#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                         "CloseNormal.png",
                         "CloseSelected.png",
                         CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2( HelloWorld::onTouchBegan, this );
    _eventDispatcher->addEventListenerWithSceneGraphPriority( touchListener, this );

    return true;
}
bool HelloWorld::onTouchBegan(Touch* touch,Event* event)
{
    float interval = 1 / 60;
    float duration = 0.8f;
    float speed = 6.0f;
    float magnitude = 4.f;

    static float elapsed = 0.f;
    float randomStart = random(-1000.0f, 1000.0f);

    this->schedule([=](float dt)
                   {

                       elapsed += dt;

                       float percentComplete = elapsed / duration;

                       // We want to reduce the shake from full power to 0 starting half way through
                       float damper = 1.0f - clampf(2.0f * percentComplete - 1.0f, 0.0f, 1.0f);

                       // Calculate the noise parameter starting randomly and going as fast as speed allows
                       float alpha = randomStart + speed * percentComplete;

                       // map noise to [-1, 1]
                       float x = noise(alpha, 0.0f) * 2.0f - 1.0f;
                       float y = noise(0.0f, alpha) * 2.0f - 1.0f;

                       x *= magnitude * damper;
                       y *= magnitude * damper;
                       this->setPosition(x, y);//Here is where the magic goes

                       if (elapsed >= duration)
                       {
                           elapsed = 0;
                           this->unschedule("Shake");
                           this->setPosition(Vec2::ZERO);
                       }

                   }
                   , interval, CC_REPEAT_FOREVER, 0.f, "Shake");
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

    exit(0);
#endif
}

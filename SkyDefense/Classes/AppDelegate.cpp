#include "AppDelegate.h"



AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Sky Defense");
        director->setOpenGLView(glview);
    }

	//set desing size for iPad retina
	Size screenSize = glview->getFrameSize();
	Size desingSize = Size(2048, 1536);

	glview->setDesignResolutionSize(desingSize.width, desingSize.height, ResolutionPolicy::EXACT_FIT);
	auto fileUtils = FileUtils::getInstance();
	std::vector<std::string> resDirOrders;
	if (screenSize.height > 768) {
		resDirOrders.push_back("ipadhd");
	}
	else if (screenSize.height > 320) {
		resDirOrders.push_back("ipad");
	}
	else {
		resDirOrders.push_back("iphone");
	}
	director->setContentScaleFactor(screenSize.height / desingSize.height);
	fileUtils->setSearchPaths(resDirOrders);

	//preload sound effects and background music
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FileNameOrganicer::getInstance()->backgroundMusic);
	SimpleAudioEngine::getInstance()->preloadEffect(FileNameOrganicer::getInstance()->bombFailSound);
	SimpleAudioEngine::getInstance()->preloadEffect(FileNameOrganicer::getInstance()->bombReleaseSound);
	SimpleAudioEngine::getInstance()->preloadEffect(FileNameOrganicer::getInstance()->boomSound);
	SimpleAudioEngine::getInstance()->preloadEffect(FileNameOrganicer::getInstance()->healthSound);
	SimpleAudioEngine::getInstance()->preloadEffect(FileNameOrganicer::getInstance()->fireSound);

	//lower playback volume for effects
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.4f);


    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GameLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

#include "GameSprite.h"

GameSprite*
GameSprite::createWithFrameName(std::string pszSpriteFrameName) {

	GameSprite * sprite = new GameSprite();

	if (sprite && sprite->initWithSpriteFrameName(pszSpriteFrameName)) {
		sprite->setRadius(sprite->boundingBox().size.width * 0.5f);

		sprite->autorelease();

		return sprite;

	}

	CC_SAFE_DELETE(sprite);
	return NULL;

}



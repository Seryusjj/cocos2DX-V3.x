#include "Rocket.h"



Rocket::Rocket(void) :

_targetRotation(0),

_dr(0),

_ar(0),

_vr(0),

_rotationSpring(0.2f),

_rotationDamping(0.5f),

_pivot(ccp(-1, -1)),

_rotationOrientation(ROTATE_NONE)
{

	this->reset();

}



Rocket::~Rocket(void){}


Rocket* Rocket::create() {

	Rocket * sprite = new Rocket();


	if (sprite && sprite->initWithSpriteFrameName("rocket.png")) {

		sprite->autorelease();

		sprite->setRadius(sprite->boundingBox().size.height * 0.5f);

		return sprite;

	}

	CC_SAFE_DELETE(sprite);

	return NULL;
}


void Rocket::reset() {


	_speed = 50;
	_pivot = ccp(-1, 1);

	_rotationOrientation = ROTATE_NONE;
	this->setRotation(-90);

	_targetRotation = -90;
	float angle = CC_DEGREES_TO_RADIANS(this->getRotation());

	_vector = ccp(_speed * cos(angle),
		-_speed * sin(angle));


}



void Rocket::update(float dt) {

	CCPoint position = this->getPosition();
	if (_rotationOrientation == ROTATE_NONE) {

		position.x += _vector.x * dt;

		position.y += _vector.y * dt;


	}
	else {

		//rotate point around a pivot by a certain amount (rotation angle)

		CCPoint rotatedPoint = ccpRotateByAngle(position, _pivot, _angularSpeed * dt);


		position.x = rotatedPoint.x;

		position.y = rotatedPoint.y;
		float rotatedAngle;
		CCPoint clockwise = ccpRPerp(ccpSub(position, _pivot));

		if (_rotationOrientation == ROTATE_COUNTER) {

			rotatedAngle = atan2(-1 * clockwise.y, -1 * clockwise.x);
		}
		else {

			rotatedAngle = atan2(clockwise.y, clockwise.x);

		}

		//update rocket vector
		_vector.x = _speed * cos(rotatedAngle);

		_vector.y = _speed * sin(rotatedAngle);

		this->setRotationFromVector();
		//wrap rotation values to 0-360 degrees
		if (this->getRotation() > 0) {

			this->setRotation(fmodf(this->getRotation(), 360.0f));

		}
		else {

			this->setRotation(fmodf(this->getRotation(), -360.0f));

		}

	}
	if (_targetRotation > this->getRotation() + 180) {

		_targetRotation -= 360;

	}

	if (_targetRotation < this->getRotation() - 180) {

		_targetRotation += 360;

	}


	this->setPosition(position);


	_dr = _targetRotation - this->getRotation();
	_ar = _dr * _rotationSpring;
	_vr += _ar;
	_vr *= _rotationDamping;
	setRotation(getRotation() + _vr);


}




void Rocket::select(bool flag) {

	if (flag) {

		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("rocket_on.png"));

	}
	else {

		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("rocket.png"));

	}

}



bool Rocket::collidedWithSides() {


	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCPoint position = this->getPosition();


	if (position.x > screenSize.width - _radius) {

		position.x = screenSize.width - _radius;
		setPosition(position);

		_rotationOrientation = ROTATE_NONE;

		_vector = ccp(this->getVector().x * -1, this->getVector().y);

		this->setRotationFromVector();
		return true;
	}


	if (position.x < _radius) {

		position.x = _radius;

		setPosition(position);
		_rotationOrientation = ROTATE_NONE;

		_vector = ccp(this->getVector().x * -1, this->getVector().y);

		this->setRotationFromVector();

		return true;
	}


	if (position.y < _radius) {

		position.y = _radius;
		setPosition(position);
		_rotationOrientation = ROTATE_NONE;
		_vector = ccp(this->getVector().x, this->getVector().y * -1);
		this->setRotationFromVector();
		return true;

	}
	if (position.y > screenSize.height - _radius){

		position.y = screenSize.height - _radius;
		setPosition(position);

		_rotationOrientation = ROTATE_NONE;
		_vector = ccp(this->getVector().x, this->getVector().y * -1);
		this->setRotationFromVector();
		return true;
	}
	return false;

}

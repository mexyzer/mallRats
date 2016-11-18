#include <string>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "InventoryItem.h"
#include "Character.h"

using namespace std;

// Constructors --------------------------------------------------------------------------------------

Character::Character()			// Default Constructor
{
	sprite_ = sf::Sprite();
}

Character::Character( sf::Texture texture, float x, float y, float height, float width )
{
	sprite_ = sf::Sprite( texture );
	setPosition( x, y );
	setHitBox( height, width );
}

Character::~Character()			// Destructor
{
	
}

// Updaters -------------------------------------------------------------------------------------------

void Character::Update()
{
	void updateSprite();
	void updatePosition();
}

void Character::updateSprite()
{

}

void Character::updatePosition()
{

}

// Mutators ------------------------------------------------------------------------------------------

void Character::setPosition( float x, float y )
{
	sprite_.setPosition(x, y);
}

void Character::setHitBox( float height, float width )
{
	hitHeight_ = height;
	hitWidth_ = width;
}

void Character::move( float dx, float dy )
{
	sprite_.move( dx, dy );
}

// Inspectors ----------------------------------------------------------------------------------------

float Character::x()
{
	return sprite_.getPosition().x;
}

float Character::y()
{
	return sprite_.getPosition().y;
}

float Character::top()
{
	return y() - ( hitHeight_ / 2 );
}

float Character::bottom()
{
	return y() + ( hitHeight_ / 2 );
}

float Character::left()
{
	return x() - ( hitWidth_ / 2 );
}

float Character::right()
{
	return x() + ( hitWidth / 2 );
}

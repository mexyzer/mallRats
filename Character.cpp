#include <string>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "InventoryItem.h"
#include "Character.h"

using namespace std;

// Constructors/Initialization ------------------------------------------------------------------------

Character::Character()
// Default Constructor
{
	sprite_ = sf::Sprite();
}

Character::Character( string textureFile, float x, float y, float height, float width )
{
	loadTextures( textureFile );
	sprite_ = sf::Sprite( standTextures[1] );
	setPosition( x, y );
	setHitBox( height, width );
}

Character::~Character()
// Destructor
{
	
}

void Character::loadTextures( string inFile )
// Loads standing/walking/jumping textures to individual vectors for iteration
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

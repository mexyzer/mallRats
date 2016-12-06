#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//#include "InventoryItem.h"
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
	sprite_ = sf::Sprite( standTextures_[1] );
	setPosition( x, y );
	setHitBox( height, width );
	prevState_ = STAND;
	prevDir_ = RIGHT;
	prevAct_ = NONE;
	texIter_ = 0;
}

Character::~Character()
// Destructor
{
	
}

void Character::loadTextures( string inFile )
// Loads standing/walking/jumping textures to individual vectors for iteration.
// The RIGHT direction is always first in the vector and is followed by the left set.
// Each vector is subsequently double the amount of textures per direction (and even).
{
	ifstream fin( inFile );
	string line;
	sf::Texture temp;

	getline(fin, line);

	while( line != "$$$$" )
	{
		temp.loadFromFile( line );
		standTextures_.push_back( temp );
		getline(fin, line);
	}
}

// Updaters -------------------------------------------------------------------------------------------

void Character::Update( charState state, charDir dir, charAct action )
{
	updateSprite( state, dir, action );
	updatePosition( state, dir );
}

void Character::updateSprite( charState state, charDir dir, charAct action )
{
	switch ( state )
	{
		case STAND:
			if ( prevState_ == state ) {
				if ( prevDir_ == dir ) {
					if ( dir == RIGHT ) {
						texIter_++;
						if ( texIter_ > ( ( (int) standTextures_.size() ) / 2 ) - 1 ) {
							texIter_ = 0;
						}
					}
					else {
						texIter_++;
						if ( texIter_ > ( (int) standTextures_.size() ) - 1 ) {
							texIter_ = ( (int) standTextures_.size() ) / 2;
						}
					}
				}
				else {
					if ( dir == RIGHT ) {
						texIter_ = 0;
					}
					else {
						texIter_ = ( (int) standTextures_.size() ) / 2;
					}
				}
			}
			else {
				if ( dir == RIGHT ) {
					texIter_ = 0;
				}
				else {
					texIter_ = ( (int) standTextures_.size() ) / 2;
				}
			}

			sprite_ = sf::Sprite( standTextures_[ texIter_ ] );
			break;

		case WALK:
			break;

		case RUN:
			break;

		case JUMP:
			break;

	}

	prevState_ = state;
	prevDir_ = dir;
	prevAct_ = action;
}

void Character::updatePosition( charState state, charDir dir )
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
	return x() + ( hitWidth_ / 2 );
}

sf::Sprite Character::getSprite()
{
	return sprite_;
}

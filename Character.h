#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
//#include "InventoryItem.h"

using namespace std;

enum charState	{ STAND, WALK, RUN, JUMP };
enum charDir	{ LEFT, RIGHT };
enum charAct	{ NONE, JUMPED, ITEM, HIT };

class Character
{
	public:
		Character();	// Default Constructor
		Character( string textureFile,		// Alternate Constructor
					float x, float y,
					float height, float width );
		~Character();	// Destructor

		void Update( charState state, charDir dir, charAct action ); // Update sprite, position, direction, etc.
		
		float x();
		float y();
		float top();
		float bottom();
		float left();
		float right();

		sf::Sprite getSprite();

	protected:
		void setPosition( float x, float y );
		void move( float dx, float dy );

	private:
		float weight_;
		float walkSpeed_;
		float runSpeed_;

		float hitHeight_;
		float hitWidth_;

		int texIter_;

		charState prevState_;
		charDir prevDir_;
		charAct prevAct_;
		
		sf::Sprite sprite_;
		vector<sf::Texture> standTextures_;
		vector<sf::Texture> walkTextures_;
		vector<sf::Texture> jumpTextures_;

		void setHitBox( float height, float width );
		void updateSprite( charState state, charDir dir, charAct action );
		void updatePosition( charState state, charDir dir );
		void loadTextures( string inFile );
};

#endif

#include <string>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "InventoryItem.h"

using namespace std;

class Character
{
	public:
		Character();	// Default Constructor
		Character( sf::Texture texture,		// Alternate Constructor
					float x, float y,
					float height, float width );
		~Character();	// Destructor

		void Update();		// Update sprite, position, direction, etc.

	protected:
		void setPosition( float x, float y );
		void move( float dx, float dy );

	private:
		float weight_;

		float hitHeight_;
		float hitWidth_;
		
		sf::Sprite sprite_;
		vector<sf::Texture> standTextures_;
		vector<sf::Texture> walkTextures_;
		vector<sf::Texture> jumpTextures_;

		float x();
		float y();
		float top();
		float bottom();
		float left();
		float right();
		
		void setHitBox( float height, float width );
		void updateSprite();
		void updatePosition();
};

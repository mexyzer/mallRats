#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "Character.h"

using namespace std;

int main()
{
	Character wyatt( "wyattTextures.txt", 400, 300, 40, 30 );

	sf::RenderWindow window( sf::VideoMode(800, 600), "Test the Character Class");

	window.setFramerateLimit(12);

	while( window.isOpen() )
	{
		sf::Event event;
		while( window.pollEvent( event ) )
		{
			if ( event.type == sf::Event::Closed ) {
				window.close();
			}
		}

		window.clear();
		
		wyatt.Update( STAND, RIGHT, NONE );

		window.draw( wyatt.getSprite() );
		
		window.display();
	}
}

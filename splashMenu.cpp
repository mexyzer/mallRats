#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "common.h"

int splashMenu( sf::RenderWindow &window, std::string menuTextureFile, std::vector<sf::Texture> pointerTextures, int numOptions, float optionX, float optionStart, float optionSpacing )
{
	int option = 0;
	sf::Sprite menu, pointer; sf::Texture menuTexture;

	menuTexture.loadFromFile( menuTextureFile ); menu.setTexture( menuTexture );
	menu.setOrigin( menuTexture.getSize().x / 2.f, menuTexture.getSize().y / 2.f );
	menu.setPosition( window.getSize().x / 2, window.getSize().y / 2 );

	pointer.setTexture( pointerTextures[0] );
	pointer.setOrigin( pointerTextures[0].getSize().x / 2.f, pointerTextures[0].getSize().y / 2.f );

	bool flag = 1, pressed;
	float pointY;
	int pointerCount = 0;

// Siginificant y positions
	optionX += ( window.getSize().x / 2.f ) - ( menuTexture.getSize().x / 2.f );
	float start = optionStart + ( window.getSize().y / 2.f ) - ( menuTexture.getSize().y / 2.f );
	float end, pos[ numOptions ];

	for( int i = 0; i < numOptions; i++ )
	{
		pos[i] = start + ( i * optionSpacing );
		if( i == numOptions - 1 ) { end = pos[i]; }
	}
	pointer.setPosition( optionX, start );

	sf::Clock clock;
	while( clock.getElapsedTime().asMilliseconds() < 300 ) { }

	sf::Event event;
	while( flag )
	{
		pointerCount++; if( pointerCount > 40 ) { pointerCount = 0; }
		for( int i = 0; (unsigned int)i < pointerTextures.size(); i++ )
		{
			if( pointerCount > ( ( 40 / (int)pointerTextures.size() ) * ( i + 1 ) ) ) { pointer.setTexture( pointerTextures[i] ); break; }
		}
		pointY = pointer.getPosition().y;
		window.pollEvent( event );
		
		if( event.type == sf::Event::Closed ) {
			window.close(); }

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
			if( pointY == end ) { option = 0; pointer.setPosition( optionX, start ); }
			else { option++; pointer.setPosition( optionX, pos[option] ); }
			pressed = 1;
		}
		else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
			if( pointY == start ) { option = numOptions - 1; pointer.setPosition( optionX, pos[option] ); }
			else { option--; pointer.setPosition( optionX, pos[option] ); }
			pressed = 1;
		}
		else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ) {
			pressed = 1; flag = 0;
		}
		else { }

		window.clear();
		window.draw( menu ); window.draw( pointer );
		window.display();

		clock.restart();
		if( pressed ) { while( clock.getElapsedTime().asMilliseconds() < 400 ) { } }

		pressed = 0;
	}


	return option;
}

// --------------------------------
// --------------------------------
// Mallrats 0.0.1 Testing Phase ---
// Written by:	Tim Klein ---------
// Design by:	Greg Klein --------
// Last update:	29-Aug-2015 -------
// --------------------------------
// --------------------------------
// --------------------------------

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "common.h"
#include <vector>
#include <iostream>
#include <fstream>

const unsigned int frameLimit{ 50 };
extern const float blockX, blockY;
std::vector<sf::Vector2f> boundaries;

void loadBoundaries( sf::RenderWindow &window, sf::Texture bg, std::string fileName, std::vector<sf::Vector2f> &boundaries );
void resizeWindow( sf::RenderWindow &window, sf::View &view, sf::Sprite &playerSprite, sf::Vector2f oldWindow, float bgX = 360, float bgY = 180 );
void deadZoneView( sf::RenderWindow &window, sf::View &view, Player &player, sf::Texture bg );

int main() // -------------------------- MAIN START -----------------------------
{
	float startingPosX = 175.f, startingPosY = 100.f;
	float windowWidth = 350, windowHeight = 175;
	int count = 0, option = 3, level;
	bool flag = 1, quitFlag = 0;

	std::string inFileBounds;

	sf::VideoMode desktopMode; desktopMode.getDesktopMode();
	sf::RenderWindow window( sf::VideoMode( windowWidth, windowHeight, desktopMode.bitsPerPixel ), "MallRats 0.0.1 (testing)" );
	window.setFramerateLimit( frameLimit ); window.setMouseCursorVisible( false );
	sf::View view = window.getView();
	sf::Vector2f oldWindow; oldWindow.x = windowWidth; oldWindow.y = windowHeight;

	std::vector<sf::Texture> pointerTextures;
	loadTextures( pointerTextures, "pointerTextures.txt" );

	sf::Sprite background, foreground; std::vector<sf::Texture> bgTextures, fgTextures;
	loadTextures( bgTextures, "bgTextures.txt" ); loadTextures( fgTextures, "fgTextures.txt" );
	sf::Texture bgTemp = bgTextures[0], fgTemp = fgTextures[0];

	view.setCenter( window.getSize().x / 2.f, window.getSize().y / 2.f );
	view.setSize( bgTemp.getSize().x, bgTemp.getSize().y ); window.setView( view );

	float posX = startingPosX + ( window.getSize().x / 2.f ) - ( bgTemp.getSize().x / 2.f );
	float posY = startingPosY + ( window.getSize().y / 2.f ) - ( bgTemp.getSize().y / 2.f );
	Player player( posX, posY );

	deadZoneView( window, view, player, bgTemp );

	// Rectangle to draw boundaries for testing (if used, also uncomment the for-loop in draw sequence)
	//	sf::RectangleShape boundShape; boundShape.setSize( {38.f, 38.f} );
	//	boundShape.setOrigin( 19.f, 19.f ); boundShape.setFillColor( sf::Color::Green );
	//	boundShape.setOutlineColor( sf::Color::White ); boundShape.setOutlineThickness( 1.f );

// Large loop (contains main menu, level select, and game loop (game loop has pause menu with options)
	while( flag )
	{

	if( option == 3 ) {
	//	main splash menu;
		option = 0;
	}

	// Level Select
		if( option == 0 ) {
			level = splashMenu( window, "resources/levelSelect.png", pointerTextures, 2, 80, 110, 50 );
			if( level == 0 ) { inFileBounds = "bg1bounds.txt"; }
			else { inFileBounds = "bg2bounds.txt"; }
			option = 2;
			bgTemp = bgTextures[ level ]; fgTemp = fgTextures[ level ];
			background.setTexture( bgTemp ); foreground.setTexture( fgTemp );
			background.setOrigin( bgTemp.getSize().x / 2.f, bgTemp.getSize().y / 2.f );
			foreground.setOrigin( background.getOrigin() );
			background.setPosition( window.getSize().x / 2.f, window.getSize().y / 2.f ); foreground.setPosition( background.getPosition() );
			posX = startingPosX + ( window.getSize().x / 2.f ) - ( bgTemp.getSize().x / 2.f );
			posY = startingPosY + ( window.getSize().y / 2.f ) - ( bgTemp.getSize().y / 2.f );
			player.sprite.setPosition( posX, posY );
		}

		loadBoundaries( window, bgTemp, inFileBounds, boundaries );

		while( window.isOpen() )
		{
			oldWindow.x = window.getSize().x; oldWindow.y = window.getSize().y;
			sf::Event event;
			while( window.pollEvent(event) )
			{
				if( event.type == sf::Event::Closed ) {
					window.close(); }
				if( event.type == sf::Event::Resized || sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) ) {
					resizeWindow( window, view, player.sprite, oldWindow );
					background.setPosition( window.getSize().x / 2.f, window.getSize().y / 2.f );
					foreground.setPosition( background.getPosition() );
					loadBoundaries( window, bgTemp, inFileBounds, boundaries );
					deadZoneView( window, view, player, bgTemp );
				}
				if( event.type == sf::Event::KeyPressed ) {
					if( event.key.code == sf::Keyboard::BackSpace ) {
						option = splashMenu( window, "resources/pause.png", pointerTextures, 2, 80, 110, 50 ); }
					else { }
				}
			}
			count++; // Simple count used for anything

			player.update(); // All player motion and collision handling

		// Active/dead zone scrolling
			deadZoneView( window, view, player, bgTemp );

		// Mind the order of drawing layers
			window.clear(); // CLEAR
			window.draw( background );
			window.draw( player.sprite );
			window.draw( foreground );
			//for( int i = 0; (unsigned int)i < boundaries.size(); i++ ) { boundShape.setPosition( boundaries[i] ); window.draw( boundShape ); }
			window.display(); // DISPLAY

		// Option handling (selected from pause menu)
			if( option == 1 ) { quitFlag = 1; break; } // option 1 corresponds to quit game
			else if( option == 0 ) { break; } // option 0 corresponds to level select (will be changed later)
		} // while

		if( quitFlag ) { flag = 0; }

	} // while

	return 0;
} // ----------------------------- END MAIN --------------------------------

void deadZoneView ( sf::RenderWindow &window, sf::View &view, Player &player, sf::Texture bg )
{
	float deadLow = ( view.getSize().x / 2.f ) + ( (float)window.getSize().x / 2.f ) - ( bg.getSize().x / 2.f );
	float deadHigh = ( (float)window.getSize().x / 2.f ) + ( bg.getSize().x / 2.f ) - ( view.getSize().x / 2.f );
	if( player.x() > deadLow && player.x() < deadHigh ) {
		view.setCenter( player.x(), view.getCenter().y );
		window.setView( view ); }
}

void resizeWindow( sf::RenderWindow &window, sf::View &view, sf::Sprite &playerSprite, sf::Vector2f oldWindow, float bgX, float bgY )
{
	float oldX = oldWindow.x / 2.f, oldY = oldWindow.y / 2.f;
	float newX = bgX;
	float newY = bgY;
	sf::Vector2f playerRel;
	playerRel.x = playerSprite.getPosition().x - oldX;
	playerRel.y = playerSprite.getPosition().y - oldY;
	float scale = (float)window.getSize().x / (float)window.getSize().y;
	newX = newY * scale;
	if( newX < bgX ) { newX = bgX; newY = newX / scale; }
	if( newY < bgY ) { newY = bgY; newX = newY * scale; }
	view.setSize( newX, newY );
	view.setCenter( window.getSize().x / 2.f, window.getSize().y / 2.f );
	window.setView( view );
	playerRel.x = playerRel.x + ( window.getSize().x / 2.f );
	playerRel.y = playerRel.y + ( window.getSize().y / 2.f );
	playerSprite.setPosition( playerRel );
}

void loadTextures( std::vector<sf::Texture> &textures, std::string fileName )
{
	sf::Texture temp;
	std::string name;
	std::ifstream inFile( fileName );

	while( std::getline( inFile, name ) )
	{
		temp.loadFromFile( name );
		textures.push_back( temp );
	}

}

bool testCollide( sf::Vector2f block, float x, float y, sf::Vector2f &movement, std::vector<sf::Vector2f> boundaries )
{
	bool fallStop = true;
	float xLeft, xRight, yUp, yDown, yNext, xNext;
	float blockX = block.x, blockY = block.y;
	sf::Vector2f current;
	for( int i = 0; (unsigned int)i < boundaries.size(); i++ )
	{
		current = boundaries[i];
		xLeft = current.x - blockX; xRight = current.x + blockX;
		yUp = current.y - blockY; yDown = current.y + blockY;
		xNext = x + movement.x; yNext = y + movement.y;

		if( ( y < yDown ) && ( y > yUp ) ) {
			if( ( xNext > xLeft ) && ( xNext < xRight )  ) {
				if( movement.x > 0 ) {
					movement.x = xLeft - x; }
				else if(  movement.x < 0 ) {
					movement.x = xRight - x; }
			}
		}
		
		if( ( x < xRight ) && ( x > xLeft ) ) {
			if( ( yNext > yUp ) && ( yNext < yDown ) ) {
				if( movement.y > 0 ) {
					movement.y = yUp - y;
					fallStop = false; }
			}
			if( ( yNext > yUp ) && ( yNext < yDown ) ) {
				if( movement.y < 0 ) {
					movement.y =  yDown - y; }
			}
		}
	
	}

	return fallStop;
}

void loadBoundaries( sf::RenderWindow &window, sf::Texture bg, std::string fileName, std::vector<sf::Vector2f> &boundaries )
{
	boundaries.clear();
	float x, y;
	float bufX = ( window.getSize().x / 2.f ) - ( bg.getSize().x / 2.f );
	float bufY = ( window.getSize().y / 2.f ) - ( bg.getSize().y / 2.f );
	sf::Vector2f temp;
	std::string line;
	std::ifstream inFile( fileName );

	// Line format::000x 000y

	while( std::getline( inFile, line ) )
	{
		x = std::stof( line.substr( 0, 4 ) );
		y = std::stof( line.substr( 5, 4 ) );

		temp.x = x + bufX; temp.y = y + bufY;

		boundaries.push_back( temp );
	}
}

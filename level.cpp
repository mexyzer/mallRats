#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ciso646>
#include "common.h"

Level::Level()
{
std::cout << "level init ";
	loadTextures( bgTextures, "backgroundTextures.txt" );
//	background.setPosition( (float)window.getSize().x / 2.f, (float)window.getSize().y / 2.f );
	background.setTexture( bgTextures[0] );
	temp = bgTextures[0];
	background.setOrigin( temp.getSize().x / 2.f, temp.getSize().y / 2.f );
std::cout << "set background ";
	
	loadTextures( fgTextures, "foregroundTextures.txt" );
//	foreground.setPosition( background.getPosition() );
	foreground.setTexture( fgTextures[0] );
	foreground.setOrigin( background.getOrigin() );

	loadBoundsFiles( "levelBounds.txt", boundaryFiles );

	boundsFile = boundaryFiles[0];
std::cout << "initialized level obj ";
}

void Level::update( sf::RenderWindow &window )
{
	if( numLevel != currentLevel ) { currentLevel = numLevel; }
	temp = bgTextures[ currentLevel ];
	background.setTexture( temp );
	foreground.setTexture( fgTextures[ currentLevel ] );
	background.setPosition( (float)window.getSize().x / 2.f, (float)window.getSize().y / 2.f );
	foreground.setPosition( background.getPosition() );
	background.setOrigin( temp.getSize().x / 2.f, temp.getSize().y / 2.f );
	foreground.setOrigin( background.getOrigin() );
std::cout << "updated level ";
	boundsFile = boundaryFiles[ currentLevel ];
std::cout << "updated bouds ";
}

void Level::loadBoundsFiles( std::string fileName, std::vector<std::string> &boundaryFiles )
{
	std::string name;
	std::ifstream inFile( fileName );

	while( std::getline( inFile, name ) )
	{
		boundaryFiles.push_back( name );
	}
}

float Level::top() { return ( background.getPosition().y - ( temp.getSize().y / 2.f ) ); }
float Level::bottom() { return ( top() + temp.getSize().y ); }
float Level::left() { return ( background.getPosition().x - ( temp.getSize().x / 2.f ) ); }
float Level::right() { return ( left() + temp.getSize().x ); }

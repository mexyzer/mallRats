#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "common.h"
#include <vector>
#include <iostream>

extern const float playerWidth, playerHeight, playerSpeed;
extern const float gravity, jumpSpeed;
extern const float windowWidth, windowHeight;

const int maxBuf{ 100 }, numStandTextures{ 12 }, numRunTextures{ 4 },
		  numJumpTextures{ 1 };
const float standHitX{ 6 }, standHitY{ 9 }, runHitX{ 6 },
			runHitY{ 9 }, jumpHitX{ 6 }, jumpHitY{ 9 };

Player::Player( float x, float y )
{
	sprite.setPosition( x, y );
	sprite.setOrigin( playerWidth / 2.f, playerHeight / 2.f );
	loadTextures( textures, "playerTextures.txt" );
	sprite.setTexture( textures[0] ); numTexture = 0;
	movement.x = 0; movement.y = 0;
	countIndex = 0;
	hitBox.x = 20; hitBox.y = 30;
	block.x = 20 + hitBox.x; block.y = 20 + hitBox.y;
}

void Player::update()
{
	if( !isJumping ) { clock.restart(); }
	sprite.move( movement );

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )
	 && sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
		movement.x = 0;
		isMoving = false; }
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right )
	 && right() < windowWidth ) {
		movement.x = playerSpeed;
		isMoving = true;
		direction = true; }
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )
	 && left() > 0 ) {
		movement.x = -playerSpeed;
		isMoving = true;
		direction = false; }
	else {
		movement.x = 0;
		isMoving = false; }

// Update Texture
	countIndex++;
	updateTexture( numStandTextures, numRunTextures, numJumpTextures );

// Jumping
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && !justJumped ) {
		isJumping = true;
		justJumped = true;
		if( movement.y == 0 ) {
			clock.restart();
			movement.y = -jumpSpeed; }
		else if( top() <= 1 ) {
			movement.y = 1; }
		else {
			movement.y = movement.y + ( gravity * clock.getElapsedTime().asSeconds() );
			clock.restart(); }
	}
	else {
		if( bottom() < windowHeight - 1 ) {
			movement.y = movement.y + ( gravity * clock.getElapsedTime().asSeconds() );
			clock.restart();
			isJumping = true; }
		else {
			movement.y = 0;
			isJumping = false; }
	}

	if( !sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
		justJumped = false; }

	if( movement.y > gravity * 2 ) { movement.y = gravity * 2; }

// Test for boundary
	if( !testCollide( block, x(), y(), movement, boundaries ) ) { isJumping = false; }

	if( bottom() + movement.y >= windowHeight ) {
		movement.y = windowHeight - bottom() - 1; }

}

void Player::updateTexture( int numStand, int numRun, int numJump )
{
	int sIndex[ numStand * 2 ], rIndex[ numRun * 2 ], jIndex[ numJump * 2 ];
	int standBuf = maxBuf / numStand, runBuf = maxBuf / numRun,
		jumpBuf = maxBuf / numJump;

	for( int i = 0; i < numStand * 2; i++ ) { sIndex[i] = i; }
	for( int i = 0; i < numRun * 2; i++ ) { rIndex[i] = ( numStand * 2 ) + i; }
	for( int i = 0; i < numJump * 2; i++ ) { jIndex[i] = ( numStand * 2 ) + ( numRun * 2 ) +  i; }
	
	if( countIndex == maxBuf ) { countIndex = 0; }
	
	if( isJumping ) {
		if( direction ) {  
			for( int i = 0; i < numJump; i++ )
			{ if( countIndex < jumpBuf * ( i + 1 ) ) { numTexture = jIndex[ numJump + i ]; break; } } }
		else {
			for( int i = 0; i < numJump; i++ )
			{ if( countIndex < jumpBuf * ( i + 1 ) ) { numTexture = jIndex[ i ]; break; } } }
	}
	else if( isMoving ) {
		if( direction ) {
			for( int i = 0; i < numRun; i++ )
			{ if( countIndex < ( runBuf * ( i + 1 ) ) ) { numTexture = rIndex[ numRun + i ]; break; } } }
		else {
			for( int i = 0; i < numRun; i++ )
			{ if( countIndex < runBuf * ( i + 1 ) ) { numTexture = rIndex[ i ]; break; } } }
	}
	else {
		if( direction ) {
			for( int i = 0; i < numStand; i++ )
			{ if( countIndex < standBuf * ( i + 1 ) ) { numTexture = sIndex[ numStand + i ]; break; } } }
		else {
			for( int i = 0; i < numStand; i++ )
			{ if( countIndex < standBuf * ( i + 1 ) ) { numTexture = sIndex[ i ]; break; } } }
	}

	updateHitBox( numTexture );
	sprite.setTexture( textures[ numTexture ] );
}

void Player::updateHitBox( int numTexture )
{
	if( numTexture < numStandTextures * 2 ) {
		hitBox.x = standHitX; hitBox.y = standHitY; }
	else if( numTexture < ( ( numStandTextures * 2 ) + ( numRunTextures * 2 ) ) ) {
		hitBox.x = runHitX; hitBox.y = runHitY; }
	else {
		hitBox.x = jumpHitX; hitBox.y = jumpHitY; }
	block.x = 20 + hitBox.x; block.y = 20 + hitBox.y;
}

float Player::x() { return sprite.getPosition().x; }
float Player::y() { return sprite.getPosition().y; }
float Player::top() { return ( y() - hitBox.y ); }
float Player::bottom() { return ( top() + ( hitBox.y * 2 ) ); }
float Player::right() { return ( x() + hitBox.x ); }
float Player::left() { return ( right() - ( hitBox.x * 2 ) ); }

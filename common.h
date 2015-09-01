#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

const float playerWidth{ 12.f }, playerHeight{ 18.f },
			playerSpeed{ 1.f }, gravity{ 10.f }, jumpSpeed{ 3.f };

extern std::vector<sf::Vector2f> boundaries;

void loadTextures( std::vector<sf::Texture> &textures, std::string fileName );
bool testCollide( sf::Vector2f block, float x, float y, sf::Vector2f &movement, std::vector<sf::Vector2f> boundaries );

int splashMenu( sf::RenderWindow &window, std::string menuTextureFile, std::vector<sf::Texture> pointerTextures, int numOptions, float optionX, float optionStart, float optionSpacing );

class Player {

	public:
		sf::Sprite sprite;
		sf::Texture texture;
		std::vector<sf::Texture> textures;
		sf::Vector2f movement;
		sf::Clock clock;

		sf::Vector2f hitBox;
		sf::Vector2f block;

// Variables
		bool isMoving, direction, isCollide, isJumping, justJumped;
		int numTexture, standCount, runCount, jumpCount;

// Member functions
		Player( float x, float y );
		void update();
		void updateTexture( int numStand, int numRun, int numJump );
		void updateHitBox( int numTexture );
		float x();
		float y();
		float top();
		float bottom();
		float right();
		float left();

};

class Level {
	
	public:
		sf::Sprite background, foreground;
		std::vector<sf::Texture> bgTextures, fgTextures;
		sf::Texture temp;

// Variables
		int numLevel, currentLevel, numLighting;
		std::vector<std::string> boundaryFiles;
		std::string boundsFile;

// Member functions
		Level();
		void update( sf::RenderWindow &window );
		void loadBoundsFiles( std::string fileName );
		float top();
		float bottom();
		float right();
		float left();
};

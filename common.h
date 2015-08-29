#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

const float playerWidth{ 12.f }, playerHeight{ 18.f },
			playerSpeed{ 1.2 }, gravity{ 12.f }, jumpSpeed{ 4.f };

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

		bool isMoving, direction, isJumping, justJumped;
		int numTexture, standCount, runCount, jumpCount;

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

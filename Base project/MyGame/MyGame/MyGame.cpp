#include "Engine/GameEngine.h"
#include "IntroScene.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

const std::string WINDOW_TITLE = "FIRST Tower Defense";

int main()
{
	// Seed the random number generator.
	srand((int)time(NULL));

	// Initialize the game.
	GAME.initialize(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	// Create our scene.
	IntroScenePtr introScene_ = std::make_shared<IntroScene>();
	GAME.setScene(introScene_);

	// Run the game loop.
	GAME.run();

	return 0;
}
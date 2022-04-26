#include "Engine/GameEngine.h"
#include "GameScene.h"
using namespace std;

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

const string WINDOW_TITLE = "Dual Fight Flight";

int main()
{
	// Seed the random number generator.
	srand((int)time(NULL));

	// Initialize the game.
	GAME.initialize(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	// Create our scene.
	GameScenePtr gameScene_ = std::make_shared<GameScene>();
	GAME.setScene(gameScene_);

	// Run the game loop.
	GAME.run();

	return 0;
}
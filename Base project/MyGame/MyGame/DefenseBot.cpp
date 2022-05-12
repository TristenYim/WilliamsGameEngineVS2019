#include "DefenseBot.h"
#include "GameScene.h"
#include "PlayingField.h"

DefenseBot::DefenseBot(sf::Vector2f ipos) {
	sprite_.setTexture(GAME.getTexture("Resources/Orange Square.png"));
	sprite_.setPosition(ipos);
	assignTag("pc");
}

void DefenseBot::update(sf::Time& elapsed) {
	GameScene& currentScene_ = (GameScene&)GAME.getCurrentScene();
	PlayingFieldPtr playingField_ = (PlayingFieldPtr&)currentScene_.getGameObject("field");

	sf::Vector2f movementVector(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	movementVector.y -= DRIVING_SPEED * elapsed.asMilliseconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	movementVector.x += DRIVING_SPEED * elapsed.asMilliseconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	movementVector.y += DRIVING_SPEED * elapsed.asMilliseconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	movementVector.x -= DRIVING_SPEED * elapsed.asMilliseconds();
	sf::Vector2f neoPosition;
	neoPosition.x = sprite_.getPosition().x + movementVector.x;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	sprite_.move(sf::Vector2f(0.0f, -DRIVING_SPEED * elapsed.asMilliseconds()));
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	sprite_.move(sf::Vector2f(DRIVING_SPEED * elapsed.asMilliseconds(), 0.0f));
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	sprite_.move(sf::Vector2f(0.0f, DRIVING_SPEED * elapsed.asMilliseconds()));
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	sprite_.move(sf::Vector2f(-DRIVING_SPEED * elapsed.asMilliseconds(), 0.0f));
}

void DefenseBot::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}
#include "Ship.h"
#include "Laser.h"

Ship::Ship() {
	sprite_.setTexture(GAME.getTexture("Resources/Ship.png"));
	sprite_.setPosition(sf::Vector2f(192, 540));
	fireDelay = 200;
	fireTimer_ = 0;
	useWASDForMovement = false;
}

Ship::Ship(sf::Vector2f ipos, int ifireDelay, float ilaserSpeed, bool iuseWASDForMovement) {
	sprite_.setTexture(GAME.getTexture("Resources/Ship.png"));
	sprite_.setPosition(ipos);
	fireDelay = ifireDelay;
	fireTimer_ = 0;
	laserSpeed = ilaserSpeed;
	useWASDForMovement = iuseWASDForMovement;
}

void Ship::draw() {
	GAME.getRenderWindow().draw(sprite_);
}

void Ship::update(sf::Time& elapsed) {
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;
	int msElapsed = elapsed.asMilliseconds();
	if (0 < fireTimer_) {
		fireTimer_ -= msElapsed;
	}
	if (useWASDForMovement) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y -= SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y += SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x -= SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x += SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && 0 >= fireTimer_) {
			fireTimer_ = fireDelay;
			sf::FloatRect bounds = sprite_.getGlobalBounds();
			float ilaserX = x + bounds.width;
			float ilaserY = y + (bounds.height / 2.0f);
			LaserPtr laser = std::make_shared<Laser>(sf::Vector2f(ilaserX, ilaserY), laserSpeed);
			GAME.getCurrentScene().addGameObject(laser);
		}
	} else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) y -= SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) y += SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) x -= SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) x += SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && 0 >= fireTimer_) {
			fireTimer_ = fireDelay;
			sf::FloatRect bounds = sprite_.getGlobalBounds();
			float ilaserX = x + bounds.width;
			float ilaserY = y + (bounds.height / 2.0f);
			LaserPtr laser = std::make_shared<Laser>(sf::Vector2f(ilaserX, ilaserY), laserSpeed);
			GAME.getCurrentScene().addGameObject(laser);
		}
	}
	if (0 > x) {
		x += GAME.getRenderWindow().getSize().x;
	} else if (GAME.getRenderWindow().getSize().x < x) {
		x -= GAME.getRenderWindow().getSize().x;
	}
	if (0 > y) {
		y += GAME.getRenderWindow().getSize().y;
	} else if (GAME.getRenderWindow().getSize().y < y) {
		y -= GAME.getRenderWindow().getSize().y;
	}
	sprite_.setPosition(sf::Vector2f(x, y));
}
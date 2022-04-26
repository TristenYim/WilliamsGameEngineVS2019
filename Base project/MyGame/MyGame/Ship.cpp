#include "Ship.h"
#include "Gun.h"

Ship::Ship() {
	sprite_.setTexture(GAME.getTexture("Resources/Ship.png"));
	sprite_.setPosition(sf::Vector2f(192, 540));
	guns = { Gun(200, 1.0f, 0.5f) };
	useWASDQControls = true;
	holdPrevention = false;
}

Ship::Ship(sf::Vector2f ipos, std::vector<Gun> iguns, bool iuseWASDQControls, bool iholdPrevention) {
	sprite_.setTexture(GAME.getTexture("Resources/Ship.png"));
	sprite_.setPosition(ipos);
	guns = iguns;
	useWASDQControls = iuseWASDQControls;
	holdPrevention = iholdPrevention;
}

void Ship::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

void Ship::update(sf::Time& elapsed) {
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;
	int msElapsed = elapsed.asMilliseconds();
	sf::FloatRect bounds = sprite_.getGlobalBounds();
	for (int gunIndex = 0; gunIndex < guns.size(); gunIndex++) {
		guns[gunIndex].updateGun(msElapsed);
	}
	if (useWASDQControls) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y -= SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y += SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x -= SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x += SPEED * msElapsed;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			isHoldingQ = false;
		}
		for (int gunIndex = 0; gunIndex < guns.size(); gunIndex++) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && isHoldingQ != true) {
				guns[gunIndex].attemptToShoot(pos, sf::Vector2f(bounds.width, bounds.height));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && holdPrevention) {
			isHoldingQ = true;
		}
	} else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) y -= SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) y += SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) x -= SPEED * msElapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) x += SPEED * msElapsed;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			isHoldingU = false;
		}
		for (int gunIndex = 0; gunIndex < guns.size(); gunIndex++) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && !isHoldingU) {
				guns[gunIndex].attemptToShoot(pos, sf::Vector2f(bounds.width, bounds.height));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && holdPrevention) {
			isHoldingU = true;
		}
	}
	if (0 > x + bounds.width) {
		x += GAME.getRenderWindow().getSize().x;
	} else if (GAME.getRenderWindow().getSize().x < x) {
		x -= GAME.getRenderWindow().getSize().x;
	}
	if (0 > y + bounds.height) {
		y += GAME.getRenderWindow().getSize().y;
	} else if (GAME.getRenderWindow().getSize().y < y) {
		y -= GAME.getRenderWindow().getSize().y;
	}
	sprite_.setPosition(sf::Vector2f(x, y));
	return;
}
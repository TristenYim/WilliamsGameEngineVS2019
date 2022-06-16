#include "RamAnimation.h"

RamAnimation::RamAnimation(sf::Vector2f ipos) : AnimatedSprite(ipos, 25) {
	AnimatedSprite::setTexture(GAME.getTexture("Resources/Ram Spritesheet.png"));
	setupRamAnimation();
	playAnimation("ramAnim", AnimationMode::OnceForwards);
	ramSound_.setBuffer(GAME.getSoundBuffer("Resources/Hull-Breach-4.wav"));
	ramSound_.play();
}

void RamAnimation::update(sf::Time& elapsed) {
	AnimatedSprite::update(elapsed);
	if (!isPlaying()) {
		makeDead();
	}
	return;
}

void RamAnimation::setupRamAnimation() {
	std::vector<sf::IntRect> frames;
	frames.push_back(sf::IntRect(0, 0, 96, 96));
	frames.push_back(sf::IntRect(96, 0, 96, 96));
	frames.push_back(sf::IntRect(182, 0, 96, 96));
	frames.push_back(sf::IntRect(278, 0, 96, 96));
	frames.push_back(sf::IntRect(384, 0, 96, 96));
	frames.push_back(sf::IntRect(480, 0, 96, 96));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));

	addAnimation("ramAnim", frames);
	return;
}
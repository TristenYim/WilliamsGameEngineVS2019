#include "Explosion.h"

Explosion::Explosion(sf::Vector2f ipos) : AnimatedSprite(ipos) {
	AnimatedSprite::setTexture(GAME.getTexture("Resources/explosion-spritesheet.png"));
	setupExplosionAnimation();
	playAnimation("explosionAnim", AnimationMode::OnceForwards);
}

void Explosion::update(sf::Time& elapsed) {
	AnimatedSprite::update(elapsed);
	if (!isPlaying()) {
		makeDead();
	}
	return;
}

void Explosion::setupExplosionAnimation() {
	//Sets up the frames
	std::vector<sf::IntRect> frames;
	frames.push_back(sf::IntRect(0, 0, 64, 64));
	frames.push_back(sf::IntRect(64, 0, 64, 64));
	frames.push_back(sf::IntRect(128, 0, 64, 64));
	frames.push_back(sf::IntRect(192, 0, 64, 64));
	frames.push_back(sf::IntRect(256, 0, 64, 64));
	frames.push_back(sf::IntRect(320, 0, 64, 64));
	frames.push_back(sf::IntRect(384, 0, 64, 64));
	frames.push_back(sf::IntRect(448, 0, 64, 64));
	frames.push_back(sf::IntRect(512, 0, 64, 64));

	//Adds the animation
	addAnimation("explosionAnim", frames);
	return;
}
#include "BombExplosion.h"

BombExplosion::BombExplosion(sf::Vector2f ipos) : AnimatedSprite(ipos, 100) {
	AnimatedSprite::setTexture(GAME.getTexture("Resources/Bomb Explosion Spritesheet.png"));
	setupBombExplosionAnimation();
	playAnimation("bombExplosionAnim", AnimationMode::OnceForwards);
	bombBoom_.setBuffer(GAME.getSoundBuffer("Resources/Explosion3.wav"));
	bombBoom_.play();
}

void BombExplosion::update(sf::Time& elapsed) {
	AnimatedSprite::update(elapsed);
	if (!isPlaying()) {
		makeDead();
	}
	return;
}

void BombExplosion::setupBombExplosionAnimation() {
	std::vector<sf::IntRect> frames;
	frames.push_back(sf::IntRect(0, 0, 200, 200));
	frames.push_back(sf::IntRect(200, 0, 200, 200));
	frames.push_back(sf::IntRect(400, 0, 200, 200));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));
	frames.push_back(sf::IntRect(0, 0, 1, 1));

	addAnimation("bombExplosionAnim", frames);
	return;
}
#include "BotExplosion.h"

BotExplosion::BotExplosion(sf::Vector2f ipos) : AnimatedSprite(ipos, 100) {
	AnimatedSprite::setTexture(GAME.getTexture("Resources/Bot Explosion Spritesheet.png"));
	setupBombExplosionAnimation();
	playAnimation("botExplosionAnim", AnimationMode::OnceForwards);
}

void BotExplosion::update(sf::Time& elapsed) {
	AnimatedSprite::update(elapsed);
	if (!isPlaying()) {
		makeDead();
	}
	return;
}

void BotExplosion::setupBombExplosionAnimation() {
	std::vector<sf::IntRect> frames;
	frames.push_back(sf::IntRect(0, 0, 64, 64));
	frames.push_back(sf::IntRect(64, 0, 64, 64));
	frames.push_back(sf::IntRect(128, 0, 64, 64));

	addAnimation("botExplosionAnim", frames);
	return;
}
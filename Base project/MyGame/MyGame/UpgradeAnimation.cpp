#include "UpgradeAnimation.h"

UpgradeAnimation::UpgradeAnimation(sf::Vector2f ipos) : AnimatedSprite(ipos, 100) {
	AnimatedSprite::setTexture(GAME.getTexture("Resources/Upgrade Spritesheet.png"));
	setupUpgradeAnimation();
	playAnimation("upgradeAnim", AnimationMode::OnceForwards);
}

void UpgradeAnimation::update(sf::Time& elapsed) {
	AnimatedSprite::update(elapsed);
	if (!isPlaying()) {
		makeDead();
	}
	return;
}

void UpgradeAnimation::setupUpgradeAnimation() {
	std::vector<sf::IntRect> frames;
	frames.push_back(sf::IntRect(0, 0, 32, 32));
	frames.push_back(sf::IntRect(32, 0, 32, 32));
	frames.push_back(sf::IntRect(64, 0, 32, 32));

	addAnimation("upgradeAnim", frames);
	return;
}
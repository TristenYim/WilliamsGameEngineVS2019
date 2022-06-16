#pragma once

#include "Engine/GameEngine.h"

class UpgradeAnimation : public AnimatedSprite {
public:
	UpgradeAnimation(sf::Vector2f ipos);

	void update(sf::Time& elapsed);
private:
	void setupUpgradeAnimation();
};

typedef std::shared_ptr<UpgradeAnimation> UpgradeAnimationPtr;
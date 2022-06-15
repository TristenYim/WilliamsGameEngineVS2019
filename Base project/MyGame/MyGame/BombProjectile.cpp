#include "BombProjectile.h"
#include "BombExplosion.h"

std::vector<int> BombProjectile::explosionDamages;
int BombProjectile::explosionRange;

BombProjectile::BombProjectile(sf::Vector2f ipos, std::string itexture, sf::Vector2f distanceFromEnemy, float speed, int idamage, bool ipierces, int ilevel) {
	setup(ipos, itexture, distanceFromEnemy, speed, idamage, ipierces);
	level = ilevel;
	assignTag("bombprojectile");
}

void BombProjectile::setupProjectileType() {
	explosionDamages.push_back(40);
	explosionDamages.push_back(50);
	explosionDamages.push_back(60);
	explosionDamages.push_back(70);
	explosionDamages.push_back(90);
	explosionRange = 200;
	return;
}

void BombProjectile::update(sf::Time& elapsed) {
	if (Exploding == exploding_) {
		exploding_ = Exploded;
		BombExplosionPtr explosion_ = std::make_shared<BombExplosion>(sprite_.getPosition());
		GAME.getCurrentScene().addGameObject(explosion_);
	} else if (Exploded == exploding_) {
		makeDead();
	} else {
		updateSpritePosition(elapsed.asMilliseconds());
	}
}

void BombProjectile::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag("offense") && Hitting == exploding_) {
		exploding_ = Exploding;
		damage = explosionDamages[level];
	}
}

sf::FloatRect BombProjectile::getCollisionRect() {
	if (Exploding == exploding_) {
		return sf::FloatRect(sprite_.getPosition().x - explosionRange / 2.0, sprite_.getPosition().y - explosionRange / 2.0, explosionRange, explosionRange);
	} else {
		return sprite_.getGlobalBounds();
	}
}
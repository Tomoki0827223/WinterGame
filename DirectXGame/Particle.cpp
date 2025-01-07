//#include "Particle.h"
//
//Particle::Particle() : position(Vector3(0, 0, 0)), velocity(Vector3(0, 0, 0)), acceleration(Vector3(0, 0, 0)), lifeTime(0.0f), isActive(false) {}
//
//void Particle::Update(float deltaTime) {
//	if (!isActive)
//		return;
//
//	lifeTime -= deltaTime;
//	if (lifeTime <= 0) {
//		isActive = false;
//		return;
//	}
//
//	velocity.x += acceleration.x * deltaTime;
//	velocity.y += acceleration.y * deltaTime;
//	velocity.z += acceleration.z * deltaTime;
//	
//	position.x += velocity.x * deltaTime;
//	position.y += velocity.y * deltaTime;
//	position.z += velocity.z * deltaTime;
//}

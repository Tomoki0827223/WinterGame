//#include "ParticleSystem.h"
//#include <affine.h>
//
//ParticleSystem::ParticleSystem() = default;
//
//ParticleSystem::~ParticleSystem() { delete model_; }
//
//void ParticleSystem::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
//	model_ = model;
//	viewProjection_ = viewProjection;
//
//	objectColor_.Initialize();
//	color_ = {1, 1, 1, 1};
//
//	// パーティクル初期化
//	for (uint32_t i = 0; i < 8; ++i) {
//		Particle particle;
//		particle.worldTransform.Initialize();
//		particle.worldTransform.translation_ = position;
//
//		// 各方向に速度を設定
//		Vector3 velocity = {kSpeed, 0.0f, 0.0f};
//		float angle = kAngleUint * i;
//		Matrix4x4 rotationMatrix = MakeRotateZMatrix(angle);
//		particle.velocity = Transform(velocity, rotationMatrix);
//
//		particle.lifeTime = 0.0f;
//		particle.maxLifeTime = kDuration;
//
//		particles_.push_back(particle);
//	}
//}
//
//void ParticleSystem::Update() {
//	if (isFinished_) {
//		return;
//	}
//
//	counter_ += 1.0f / 60.0f;
//	if (counter_ >= kDuration) {
//		counter_ = kDuration;
//		isFinished_ = true;
//	}
//
//	for (auto& particle : particles_) {
//		if (particle.lifeTime < particle.maxLifeTime) {
//			particle.worldTransform.translation_.x += particle.velocity.x;
//			particle.worldTransform.translation_.y += particle.velocity.y;
//			particle.worldTransform.translation_.z += particle.velocity.z;
//			particle.lifeTime += 1.0f / 60.0f;
//		}
//	}
//
//	color_.w = max(0.0f, 1.0f - counter_ / kDuration);
//	objectColor_.SetColor(color_);
//	objectColor_.TransferMatrix();
//
//	for (auto& particle : particles_) {
//		particle.worldTransform.UpdateMatrix();
//	}
//}
//
//void ParticleSystem::Draw() {
//	if (isFinished_) {
//		return;
//	}
//
//	for (const auto& particle : particles_) {
//		model_->Draw(particle.worldTransform, *viewProjection_, &objectColor_);
//	}
//}

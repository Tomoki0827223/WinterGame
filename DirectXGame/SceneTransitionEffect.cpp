//#include "SceneTransitionEffect.h"
//#include <cstdlib> // rand()
//#include <memory>  // unique_ptr
//#include <random>
//
//SceneTransitionEffect::SceneTransitionEffect(int maxParticles) : isPlaying(false), particleSystem(std::make_unique<ParticleSystem>(maxParticles)) {}
//
//SceneTransitionEffect::~SceneTransitionEffect() = default;
//
//void SceneTransitionEffect::StartEffect(const Vector3& center, int numParticles) {
//	isPlaying = true;
//
//	// より良い乱数生成
//	std::random_device rd;
//	std::mt19937 gen(rd());
//	std::uniform_real_distribution<float> dis(-1.0f, 1.0f); // -1.0 から 1.0 の間のランダム値
//
//	for (int i = 0; i < numParticles; ++i) {
//		Vector3 randomVelocity = Vector3(dis(gen), dis(gen), dis(gen));
//		particleSystem->Emit(center, randomVelocity, Vector3(0, -0.1f, 0), 2.0f);
//	}
//}
//
//void SceneTransitionEffect::Update(float deltaTime) {
//	if (isPlaying) {
//		particleSystem->Update();
//	}
//}
//
//void SceneTransitionEffect::Draw() {
//	if (isPlaying) {
//		particleSystem->Draw();
//	}
//}
//
//bool SceneTransitionEffect::IsPlaying() const { return isPlaying; }

#include "WorldTransform.h"
#include "affine.h"

void WorldTransform::UpdateMatrix() {

	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	TransferMatrix();
}

bool WorldTransform::IsHit(const Vector3& bulletPosition) const {
	// ブロックのAABB範囲を定義
	Vector3 blockMin = translation_ - scale_ * 0.5f; // AABBの最小点
	Vector3 blockMax = translation_ + scale_ * 0.5f; // AABBの最大点

	// 弾がAABB内にあるかをチェック
	return (
	    bulletPosition.x >= blockMin.x && bulletPosition.x <= blockMax.x && bulletPosition.y >= blockMin.y && bulletPosition.y <= blockMax.y && bulletPosition.z >= blockMin.z &&
	    bulletPosition.z <= blockMax.z);
}

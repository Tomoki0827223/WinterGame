#pragma once
#include "Vector3.h"
#include <cmath>

class Distance {
public:
	// 2点間の距離を計算する関数
	static float Calculate(const Vector3& a, const Vector3& b);
};

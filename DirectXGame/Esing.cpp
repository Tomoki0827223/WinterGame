#include "Esing.h"
#include <cmath>

// 定数定義
#ifndef M_PI
#define M_PI 3.14159265358979323846f // float型の定義
#endif

// Ease Functions Implementation

float Esing::easeInSine(float x) { return 1.0f - cosf((x * M_PI) / 2.0f); }

float Esing::easeOutSine(float x) { return sinf((x * M_PI) / 2.0f); }

float Esing::easeInOutSine(float x) { return -(cosf(M_PI * x) - 1.0f) / 2.0f; }

float Esing::easeInQuad(float x) { return x * x; }

float Esing::easeOutQuad(float x) { return 1.0f - (1.0f - x) * (1.0f - x); }

float Esing::easeInOutQuad(float x) { return x < 0.5f ? 2.0f * x * x : 1.0f - powf(-2.0f * x + 2.0f, 2.0f) / 2.0f; }

float Esing::easeInCubic(float x) { return x * x * x; }

float Esing::easeOutCubic(float x) { return 1.0f - powf(1.0f - x, 3.0f); }

float Esing::easeInOutCubic(float x) { return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3.0f) / 2.0f; }

float Esing::easeInQuart(float x) { return x * x * x * x; }

float Esing::easeOutQuart(float x) { return 1.0f - powf(1.0f - x, 4.0f); }

float Esing::easeInOutQuart(float x) { return x < 0.5f ? 8.0f * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 4.0f) / 2.0f; }

float Esing::easeInQuint(float x) { return x * x * x * x * x; }

float Esing::easeOutQuint(float x) { return 1.0f - powf(1.0f - x, 5.0f); }

float Esing::easeInOutQuint(float x) { return x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 5.0f) / 2.0f; }

float Esing::easeInExpo(float x) { return x == 0.0f ? 0.0f : powf(2.0f, 10.0f * x - 10.0f); }

float Esing::easeOutExpo(float x) { return x == 1.0f ? 1.0f : 1.0f - powf(2.0f, -10.0f * x); }

float Esing::easeInOutExpo(float x) { return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : x < 0.5f ? powf(2.0f, 20.0f * x - 10.0f) / 2.0f : (2.0f - powf(2.0f, -20.0f * x + 10.0f)) / 2.0f; }

float Esing::easeInCirc(float x) { return 1.0f - sqrtf(1.0f - powf(x, 2.0f)); }

float Esing::easeOutCirc(float x) { return sqrtf(1.0f - powf(x - 1.0f, 2.0f)); }

float Esing::easeInOutCirc(float x) { return x < 0.5f ? (1.0f - sqrtf(1.0f - powf(2.0f * x, 2.0f))) / 2.0f : (sqrtf(1.0f - powf(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f; }

float Esing::easeInBack(float x) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;
	return c3 * x * x * x - c1 * x * x;
}

float Esing::easeOutBack(float x) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;
	return 1.0f + c3 * powf(x - 1.0f, 3.0f) + c1 * powf(x - 1.0f, 2.0f);
}

float Esing::easeInOutBack(float x) {
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;
	return x < 0.5f ? (powf(2.0f * x, 2.0f) * ((c2 + 1.0f) * 2.0f * x - c2)) / 2.0f : (powf(2.0f * x - 2.0f, 2.0f) * ((c2 + 1.0f) * (2.0f * x - 2.0f) + c2) + 2.0f) / 2.0f;
}

float Esing::easeInElastic(float x) {
	const float c4 = (2.0f * M_PI) / 3.0f;
	return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : -powf(2.0f, 10.0f * x - 10.0f) * sinf((x * 10.0f - 10.75f) * c4);
}

float Esing::easeOutElastic(float x) {
	const float c4 = (2.0f * M_PI) / 3.0f;
	return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : powf(2.0f, -10.0f * x) * sinf((x * 10.0f - 0.75f) * c4) + 1.0f;
}

float Esing::easeInOutElastic(float x) {
	const float c5 = (2.0f * M_PI) / 4.5f;
	return x == 0.0f   ? 0.0f
	       : x == 1.0f ? 1.0f
	       : x < 0.5f  ? -(powf(2.0f, 20.0f * x - 10.0f) * sinf((20.0f * x - 11.125f) * c5)) / 2.0f
	                   : (powf(2.0f, -20.0f * x + 10.0f) * sinf((20.0f * x - 11.125f) * c5)) / 2.0f + 1.0f;
}

float Esing::easeInBounce(float x) { return 1.0f - easeOutBounce(1.0f - x); }

float Esing::easeOutBounce(float x) {
	const float n1 = 7.5625f;
	const float d1 = 2.75f;
	if (x < 1.0f / d1) {
		return n1 * x * x;
	} else if (x < 2.0f / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	} else if (x < 2.5f / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	} else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}

float Esing::easeInOutBounce(float x) { return x < 0.5f ? (1.0f - easeOutBounce(1.0f - 2.0f * x)) / 2.0f : (1.0f + easeOutBounce(2.0f * x - 1.0f)) / 2.0f; }

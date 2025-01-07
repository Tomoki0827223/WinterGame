#include "Distance.h"

float Distance::Calculate(const Vector3& a, const Vector3& b) 

{ return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)); }

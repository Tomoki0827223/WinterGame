#pragma once
//#include "MathUtilityForText.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>
#include <numbers>

Matrix4x4 MatrixMultipry(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

Matrix4x4 ExtractRotation(const Matrix4x4& matWorld);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeRotateZMatrix(float angle);

Vector3 Transform(const Vector3& vec, const Matrix4x4& mat);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Normalize(const Vector3& v);
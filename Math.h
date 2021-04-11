#pragma once
namespace Math
{
	template<typename T>
	T Lerp(T _S, T _E, float _T)
	{
		return _S + (_E - _S) * _T;
	}

	int Random(int _Min, int _Max);
	float Random(float _Min, float _Max);
	float Clamp(float _Val, float _Min, float _Max);
	Vec2 RotateVec(Vec2 _Vec, float _Rot);
	float PointDirection(Vec2 _V1, Vec2 _V2);
}
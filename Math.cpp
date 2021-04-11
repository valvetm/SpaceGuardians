#include "DXUT.h"
#include "Math.h"


int Math::Random(int _Min, int _Max)
{
	return _Min + rand() % (_Max - _Min + 1);
}

float Math::Random(float _Min, float _Max)
{
	return _Min + (rand() | (rand() << 16)) % (int)(_Max * 10000 - _Min * 10000 + 1) * 0.0001;
}

float Math::Clamp(float _Val, float _Min, float _Max)
{
	return min(_Max, max(_Val, _Min));
}

Vec2 Math::RotateVec(Vec2 _Vec, float _Rot)
{
	float Rot = D3DXToRadian(_Rot);
	return Vec2(_Vec.x * cos(Rot) + _Vec.y * -sin(Rot), _Vec.x * sin(Rot) + _Vec.y * cos(Rot));
}

float Math::PointDirection(Vec2 _V1, Vec2 _V2)
{
	return D3DXToDegree(atan2(_V2.y - _V1.y, _V2.x - _V1.x));
}

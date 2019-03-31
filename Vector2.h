#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

struct Vector2
{
	double m_X;
	double m_Y;

	Vector2() : m_X(0), m_Y(0) {}
	Vector2(double _x, double _y) : m_X(_x), m_Y(_y) {}

	Vector2 operator+(const Vector2& _vector2)	const	{ return Vector2(m_X + _vector2.m_X,	m_Y + _vector2.m_Y); }
	Vector2 operator+(const double _value)		const	{ return Vector2(m_X + _value,			m_Y + _value); }
		
	Vector2& operator+=(const Vector2& _vector2)		{ m_X += _vector2.m_X;	m_Y += _vector2.m_Y;	return *this; }
	Vector2& operator+=(const double _value)			{ m_X += _value;		m_Y += _value;			return *this; }

	Vector2 operator-(const Vector2& _vector2)	const	{ return Vector2(m_X - _vector2.m_X,	m_Y - _vector2.m_Y); }
	Vector2 operator-(const double _value)		const	{ return Vector2(m_X - _value,			m_Y - _value); }

	Vector2& operator-=(const Vector2& _vector2)		{ m_X -= _vector2.m_X;	m_Y -= _vector2.m_Y;	return *this; }
	Vector2& operator-=(const double _value)			{ m_X -= _value;		m_Y -= _value; }

	Vector2 operator*(const Vector2& _vector2)	const	{ return Vector2(m_X * _vector2.m_X,	m_Y * _vector2.m_Y); }
	Vector2 operator*(const double _value)		const	{ return Vector2(m_X * _value,			m_Y * _value); }

	Vector2& operator*=(const Vector2& _vector2)		{ m_X *= _vector2.m_X;	m_Y *= _vector2.m_Y;	return *this; }
	Vector2& operator*=(const double _value)			{ m_X *= _value;		m_Y *= _value;			return *this; }

	Vector2 operator/(const Vector2& _vector2)	const	{ return Vector2(m_X / _vector2.m_X,	m_Y / _vector2.m_Y); }
	Vector2 operator/(const double _value)		const	{ return Vector2(m_X / _value,			m_Y / _value); }

	Vector2& operator/=(const Vector2& _vector2)		{ m_X /= _vector2.m_X;	m_Y /= _vector2.m_Y;	return *this; }
	Vector2& operator/=(const double _value)			{ m_X /= _value;		m_Y /= _value;			return *this; }

	inline double length()						const	{ return sqrt(lengthSquared()); }
	inline double lengthSquared()				const	{ return pow(m_X, 2) + pow(m_Y, 2); }
	inline Vector2 unit()						const	{ return *this / length(); }

	inline static Vector2 fromRadians(double _angle)	{ return Vector2(cos(_angle), sin(_angle)); }
};
#endif
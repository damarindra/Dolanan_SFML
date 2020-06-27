//
// Created by DamarIndra on 26-Jun-20.
//

#ifndef DOLANAN_CORE_MATH_H_
#define DOLANAN_CORE_MATH_H_

#include <SFML/Graphics.hpp>
#include <cmath>

class Math {
public:
	static inline float deg2rad(float v) { return v * M_PI / 180.0; }
	static inline float rad2deg(float v) { return v * 180.0 / M_PI; }

	static sf::Vector2f normalize(sf::Vector2f& v);
	static float dot(const sf::Vector2f &v, const sf::Vector2f &p_other);
	inline static float tdotx(const sf::Transform &t, const sf::Vector2f &v) {
		return t.getMatrix()[0] * v.x + t.getMatrix()[4] * v.y;
	}
	inline static float tdoty(const sf::Transform &t, const sf::Vector2f &v) {
		return t.getMatrix()[1] * v.x + t.getMatrix()[5] * v.y;
	}
	static sf::Vector2f xform(const sf::Transform &t, const sf::Vector2f &p_vec);
};

inline sf::Vector2f operator *(const sf::Vector2f& lhs, const sf::Vector2f& rhs){
	return sf::Vector2f (lhs.x * rhs.x, lhs.y * rhs.y);
}
//inline sf::Vector2f& operator *=(const sf::Vector2f& rhs){
//	return this = *this + rhs;
//	return sf::Vector2f (lhs.x * rhs.x, lhs.y * rhs.y);
//}
inline sf::Vector2f operator /(const sf::Vector2f& lhs, const sf::Vector2f& rhs){
	return sf::Vector2f (lhs.x / rhs.x, lhs.y / rhs.y);
}
inline sf::Vector2f operator /(const sf::Vector2f& lhs, const float& rhs){
	return sf::Vector2f (lhs.x / rhs, lhs.y / rhs);
}
inline sf::Vector2f operator /(const float& lhs, const sf::Vector2f& rhs){
	return sf::Vector2f (lhs / rhs.x, lhs / rhs.y);
}
//inline sf::Vector2f& operator /=(const sf::Vector2f& rhs){
//	return sf::Vector2f (lhs.x / rhs.x, lhs.y / rhs.y);
//}

#endif //DOLANAN_CORE_MATH_H_

//
// Created by DamarIndra on 26-Jun-20.
//

#include "core/Math.h"

namespace dln {

	sf::Vector2f Math::normalize(sf::Vector2f &v) {
		float l = v.x * v.x + v.y * v.y;
		if (l != 0) {

			l = std::sqrt(l);
			v.x = v.x / l;
			v.y = v.y / l;
		}
	}

	float Math::dot(const sf::Vector2f &v, const sf::Vector2f &p_other) {
		return v.x * p_other.x + v.y * p_other.y;
	}

	sf::Vector2f Math::xform(const sf::Transform &t, const sf::Vector2f &p_vec) {
		return sf::Vector2(Math::tdotx(t, p_vec), Math::tdoty(t, p_vec))
				+ sf::Vector2f(t.getMatrix()[12], t.getMatrix()[13]);
	}
}
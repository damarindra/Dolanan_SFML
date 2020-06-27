//
// Created by DamarIndra on 25-Jun-20.
//

#ifndef DOLANAN_TRANSFORM_H
#define DOLANAN_TRANSFORM_H

#include <memory>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>
#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>
#include <core/Math.h>
#include "Component.h"

#ifndef SGN
#define SGN(m_v) (((m_v) < 0) ? (-1.0) : (+1.0))
#endif

class Transform : private sf::Transformable, public Component {

public:
	Transform();
	~Transform();

	void set_position(const sf::Vector2f& v);
	void set_position(const float& x, const float& y);
	sf::Vector2f get_position() const;

	void set_rotation(const float& r);
	float get_rotation() const;

	void set_scale(const sf::Vector2f& v);
	sf::Vector2f get_scale();

	const sf::Transform& get_transform() const;

	void set_global_position(sf::Vector2f v);
	void set_global_position(float x, float y);
	sf::Vector2f get_global_position() const;

	void set_global_rotation(float r);
	float get_global_rotation() const;

//	void set_global_scale(sf::Vector2f v);
	sf::Vector2f get_global_scale() const;

	constexpr entt::entity get_parent() { return parent; }

	void set_parent(entt::entity p_parent);

	const float* get_matrix() { return getTransform().getMatrix(); }

	const sf::Transform& get_global_transform() const;

protected:
	inline float basis_determinant_global_transform() const{
		const float* matrix = get_global_transform().getMatrix();
		return matrix[0] * matrix[5] - matrix[1] * matrix[4];
	}

private:
	entt::entity parent = entt::null;
	std::vector<entt::entity> children{};
	mutable bool global_transform_need_update = false;
	mutable sf::Transform global_transform{};

	// requesting update, including childs
	void set_dirty();
};

#endif //DOLANAN_TRANSFORM_H

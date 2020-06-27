//
// Created by DamarIndra on 25-Jun-20.
//

#include "component/Transform.h"
#include "core/Game.h"
#include <spdlog/spdlog.h>
#include "core/Math.h"
#include "ecs/ECS.h"

namespace dln {

	Transform::Transform() :
			global_transform() {
	}

	Transform::~Transform() {
	}

	void Transform::set_position(const sf::Vector2f &v) {
		if (v != getPosition()) {
			set_dirty();
			setPosition(v);
		}
	}

	void Transform::set_position(const float &x, const float &y) {
		if (x != getPosition().x || y != getPosition().y) {
			set_dirty();
			setPosition(x, y);
		}
	}

	sf::Vector2f Transform::get_position() const {
		return getPosition();
	}

	void Transform::set_rotation(const float &r) {
		if (getRotation() != r) {
			set_dirty();
			setRotation(r);
		}
	}
	float Transform::get_rotation() const {
		return getRotation();
	}

	void Transform::set_scale(const sf::Vector2f &v) {
		if (v != getScale()) {
			set_dirty();
			setScale(v);
		}
	}
	sf::Vector2f Transform::get_scale() {
		return getScale();
	}

	const sf::Transform &Transform::get_transform() const {
		return getTransform();
	}

	void Transform::set_global_position(sf::Vector2f v) {
		if (dln::ECS::is_entity_valid(parent)) {
			const sf::Transform
					inverse = dln::ECS::get_registry().get<Transform>(parent).get_global_transform().getInverse();
			set_position(Math::xform(inverse, v));
		} else {
			set_position(v);
		}
	}

	void Transform::set_global_position(float x, float y) {
		if (dln::ECS::is_entity_valid(parent)) {
			const sf::Transform
					inverse = dln::ECS::get_registry().get<Transform>(parent).get_global_transform().getInverse();
			set_position(Math::xform(inverse, sf::Vector2f(x, y)));
		} else {
			set_position(x, y);
		}
	}

	sf::Vector2f Transform::get_global_position() const {
		const float *matrix = get_global_transform().getMatrix();
		return sf::Vector2f(matrix[12], matrix[13]);
	}

	void Transform::set_global_rotation(float r) {
		if (dln::ECS::is_entity_valid(parent)) {
			const float &parent_rot = dln::ECS::get_registry().get<Transform>(parent).get_global_rotation();
			set_rotation(r - parent_rot);
		} else {
			set_rotation(r);
		}

	}
	float Transform::get_global_rotation() const {
		const float *matrix = get_global_transform().getMatrix();
		return Math::rad2deg(atan2(matrix[1], matrix[0]));
	}
//
//void Transform::set_global_scale(sf::Vector2f v){
//	global_scale = v;
//}

	sf::Vector2f Transform::get_global_scale() const {
		const float *matrix = get_global_transform().getMatrix();
		return sf::Vector2f(sqrt(matrix[0] * matrix[0] + matrix[1] * matrix[1]),
							sqrt(matrix[4] * matrix[4] + matrix[5] * matrix[5]));
//		float det_sign = SGN(basis_determinant_global_transform());
//		return sf::Vector2f(sqrt(matrix[0] * matrix[0] + matrix[1] * matrix[1]),
//							det_sign * sqrt(matrix[4] * matrix[4] + matrix[5] * matrix[5]));
	}

	const sf::Transform &Transform::get_global_transform() const {
		if (global_transform_need_update) {
			if (dln::ECS::is_entity_valid(parent)) {
				Transform &parent_tr = dln::ECS::get_registry().get<Transform>(parent);
				global_transform = parent_tr.get_global_transform() * getTransform();
			} else global_transform = getTransform();

			global_transform_need_update = false;
		}

		return global_transform;
	}

	void Transform::set_parent(entt::entity p_parent) {
		if (ECS::is_entity_valid(p_parent) && !ECS::Instance()->registry.has<Transform>(p_parent)) {
			spdlog::error("Trying to set parent, but parent doesn't have transform!");
			return;
		}
		if (dln::ECS::is_entity_valid(parent)) {
			// remove parent child
			Transform &tr = dln::ECS::get_registry().get<Transform>(parent);
			tr.children.erase(std::remove(tr.children.begin(), tr.children.end(), get_owner()));
		}
		parent = p_parent;
		Transform &parent_tr = dln::ECS::get_registry().get<Transform>(p_parent);
		parent_tr.children.push_back(get_owner());
		global_transform_need_update = true;

	}

	void Transform::set_dirty() {
		global_transform_need_update = true;
		for (auto c: children) {
			if (dln::ECS::is_entity_valid(c)) {
				Transform &tr = dln::ECS::get_registry().get<Transform>(c);
				tr.set_dirty();
			}
		}
	}
}
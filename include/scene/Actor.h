//
// Created by DamarIndra on 27-Jun-20.
//

#ifndef SAMPLE_SRC_SCENE_ACTOR_H_
#define SAMPLE_SRC_SCENE_ACTOR_H_

#include <entt/entt.hpp>
#include <component/Transform.h>
#include <component/ActorDetail.h>
#include "ecs/ECS.h"

namespace dln {

	class Actor {
	public:
		Actor(const entt::entity& entity );

		entt::entity get_entity() const;
		ActorDetail& get_info() const;
		Transform& get_transform() const;

	private:
		// entity is just a int value, it is used for id
		entt::entity entity = entt::null;

	};
}
#endif //SAMPLE_SRC_SCENE_ACTOR_H_

//
// Created by DamarIndra on 27-Jun-20.
//

#include "scene/Actor.h"

namespace dln {

	Actor::Actor(const entt::entity &entity)  :
			entity(entity)
	{
		ECS::add_component<ActorDetail>(entity);
		ECS::add_component<Transform>(entity);
	}

	entt::entity Actor::get_entity() const { return entity; }
	ActorDetail& Actor::get_info() const { return ECS::get_registry().get<ActorDetail>(entity); }
	Transform& Actor::get_transform() const { return ECS::get_registry().get<Transform>(entity); }
}
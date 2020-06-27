//
// Created by DamarIndra on 27-Jun-20.
//

#ifndef SAMPLE_INCLUDE_COMPONENT_COMPONENT_H_
#define SAMPLE_INCLUDE_COMPONENT_COMPONENT_H_

#include <entt/entt.hpp>

namespace dln{
	struct Component{
		friend class ECS;
	public:
		inline entt::entity get_owner() const { return owner; }
	private:
		entt::entity owner = entt::null;
	};
}

#endif //SAMPLE_INCLUDE_COMPONENT_COMPONENT_H_

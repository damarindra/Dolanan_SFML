//
// Created by DamarIndra on 27-Jun-20.
//

#ifndef SAMPLE_INCLUDE_ECS_ECS_H_
#define SAMPLE_INCLUDE_ECS_ECS_H_

#include <memory>
#include <entt/entt.hpp>
#include <component/Component.h>

using namespace std;

namespace dln{
	class ECS {
		static shared_ptr<ECS> _instance;

	public:
		inline static shared_ptr<ECS>& Instance(){
			if(_instance == nullptr){
				_instance = std::make_shared<ECS>();
			}
			return _instance;
		}

		inline static bool is_entity_valid(const entt::entity& entity){
			return Instance()->registry.valid(entity);
		}

		template<typename Comp>
		static decltype(auto) add_component(const entt::entity entity){
			auto& result = (Instance()->registry.emplace<Comp>(entity));
			auto* is_comp = dynamic_cast<Component*>(&result);
			if(is_comp != nullptr)
				is_comp->owner = entity;
			is_comp = nullptr;
			return result;
		}

		inline static entt::registry& get_registry() {
			return (Instance()->registry);
		}


		entt::registry registry;

	};
}

#endif //SAMPLE_INCLUDE_ECS_ECS_H_

//
// Created by DamarIndra on 26-Jun-20.
//

#ifndef DOLANAN_CORE_GAME_H_
#define DOLANAN_CORE_GAME_H_

#include <memory>
#include <entt/entt.hpp>
#include <component/Component.h>

using namespace std;

namespace dln {

	class Game {
		static unique_ptr<Game> _instance;

	public:
		inline static unique_ptr<Game> &Instance() {
			if (_instance == nullptr) {
				_instance = std::make_unique<Game>();
			}
			return _instance;
		}
	};

}
#endif //DOLANAN_CORE_GAME_H_

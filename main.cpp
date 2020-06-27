#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "spdlog/spdlog.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <component/Transform.h>
#include "core/Game.h"
#include "ecs/ECS.h"

using namespace std;

struct Name : public Component {
	string name;
};

struct velocity : public Component {
	float dx = 0, dy = 0;
};

class RectShape : public sf::RectangleShape, public Component {
public:
	explicit RectShape(const sf::Vector2f &size = sf::Vector2f(0, 0)) : sf::RectangleShape(size), Component() {

	}
};

void update_rotation(float x) {
	auto view = dln::ECS::get_registry().view<Transform>();

	for (auto ent: view) {
		auto &tr = view.get<Transform>(ent);

		if (x != tr.get_rotation())
			tr.set_rotation(x);
	}
}

void update_scale(sf::Vector2f s) {
	auto view = dln::ECS::get_registry().view<Transform>();

	for (auto ent: view) {
		auto &tr = view.get<Transform>(ent);

		if (s != tr.get_scale())
			tr.set_scale(s);
	}
}

void update_velocity(float x, float y) {
	auto view = dln::ECS::Instance()->registry.view<velocity>();

	for (auto entity: view) {
		auto &vel = view.get<velocity>(entity);
		vel.dx = x;
		vel.dy = y;
	}
}

void update_position() {
	auto view = dln::ECS::Instance()->registry.view<Transform, velocity>();

	for (auto entity: view) {
		auto &vel = view.get<velocity>(entity);
		auto &tr = view.get<Transform>(entity);

		if (vel.dx != 0 || vel.dy != 0) {
			spdlog::info("Before {} {}", tr.get_global_position().x, tr.get_global_position().y);
			spdlog::info("Before {} {}", tr.get_position().x, tr.get_position().y);
			tr.set_position(tr.get_position() + sf::Vector2f(vel.dx, vel.dy));
			spdlog::info("After  {} {}", tr.get_global_position().x, tr.get_global_position().y);
			spdlog::info("After  {} {}", tr.get_position().x, tr.get_position().y);
			vel.dx = 0;
			vel.dy = 0;

		}
	}
}

void draw(sf::RenderWindow &window) {
	auto view = dln::ECS::Instance()->registry.view<RectShape, Transform>();

	for (auto entity: view) {
		auto &re = view.get<RectShape>(entity);
		auto &tr = view.get<Transform>(entity);

		re.setPosition(tr.get_global_position());
		re.setRotation(tr.get_global_rotation());
		re.setScale(tr.get_global_scale());

//		if(na.name == "child"){
//			spdlog::info("{} {}", tr.get_global_position().x, tr.get_global_position().y);
//		}

		window.draw(re);
	}
}

class actor {
public:
	actor(entt::entity entity, Name &name, Transform &transform) :
			entity(entity), name(name), transform(transform) {

	}
	entt::entity get_entity() const { return entity; }
	Transform &get_transform() const { return transform; }
	Name &get_name() const { return name; }

	template<typename Comp>
	decltype(auto) add_component(){
		return dln::ECS::add_component<Comp>(entity);
	}


protected:
	entt::entity entity = entt::null;
	Transform &transform;
	Name &name;
};

class player : public actor {
public:
	player(entt::entity &entity, Name &name, Transform &transform, RectShape &shape, velocity& velo) :
			shape(shape), velocity(velo), actor(entity, name, transform) {
	}

	RectShape &get_shape() const { return shape; }


protected:
	RectShape &shape;
	velocity &velocity;
};

player create_player() {
	auto et = dln::ECS::get_registry().create();
	return player(et, dln::ECS::add_component<Name>(et),
				  dln::ECS::add_component<Transform>(et),
				  dln::ECS::add_component<RectShape>(et),
				  dln::ECS::add_component<velocity>(et)
	);
}

int main() {
//	auto et = Game::get_registry().create();
	player p = create_player();
	p.get_shape().setSize(sf::Vector2f(100, 100));

	entt::entity ae = dln::ECS::get_registry().create();
	actor a(ae, dln::ECS::add_component<Name>(ae), dln::ECS::add_component<Transform>(ae));
	RectShape& rs = a.add_component<RectShape>();
	rs.setSize(sf::Vector2f(100, 100));
	a.get_transform().set_parent(p.get_entity());
	a.get_transform().set_position(110, 110);

	float movementSpeed = 50;

	spdlog::info(fmt::format("Clock "));

	spdlog::info("Yo this is speedlog");
	sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	float rot = 0, sca = 1;

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				window.close();
			}
		}

		auto dt = deltaClock.restart();
		ImGui::SFML::Update(window, dt);

		sf::Vector2f movementInput;

		//Input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			movementInput.x += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			movementInput.x -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			movementInput.y -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			movementInput.y += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			rot += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
			rot -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
			sca += 0.1f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
			sca -= 0.1f;

		sf::Vector2f veloRaw = movementInput * movementSpeed * dt.asSeconds();

		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::DragFloat("speed ", &movementSpeed);
//		ImGui::Text("%s", fmt::format("This is using fmt {} : {}", 3, 6).c_str());
//		ImGui::Text("%s", fmt::format("Clock {}", dt.asSeconds()).c_str());
//		ImGui::Text("%s", fmt::format("Input {}, {}", movementInput.x, movementInput.y).c_str());
//		ImGui::Text("%s", fmt::format("ve {}, {}", veloRaw.x, veloRaw.y).c_str());
//		ImGui::Text("%s", fmt::format("ve {}, {}", veloRaw.x, veloRaw.y).c_str());
//
//		ImGui::Text("%s", fmt::format("e loc rot {}", p.get_transform().get_rotation()).c_str());
//		ImGui::Text("%s", fmt::format("e glob rot {}", p.get_transform().get_global_rotation()).c_str());
//		ImGui::Text("%s",
//					fmt::format("e loc sca {}",
//								p.get_transform().get_scale().x,
//								p.get_transform().get_scale().y).c_str());
//		ImGui::Text("%s",
//					fmt::format("e glob sca {} {}",
//								p.get_transform().get_global_scale().x,
//								p.get_transform().get_global_scale().y).c_str());

//		ImGui::Text("%s", fmt::format("c loc rot {}", child_tr.get_rotation()).c_str());
//		ImGui::Text("%s", fmt::format("c glob rot {}", child_tr.get_global_rotation()).c_str());
//		ImGui::Text("%s", fmt::format("c loc sca {} {}", child_tr.get_scale().x, child_tr.get_scale().y).c_str());
//		ImGui::Text("%s", fmt::format("c glob sca {} {}", child_tr.get_global_scale().x, child_tr.get_global_scale().y).c_str());

//		const auto& matrix = child_tr.get_global_transform().getMatrix();
//		ImGui::Text("%s", fmt::format("sca {}, {}", child_tr.get_global_scale().x,  child_tr.get_global_scale().y).c_str());
//		ImGui::Text("%s", fmt::format("ve {}, {}, {}, {}", matrix[0], matrix[1], matrix[2], matrix[3]).c_str());
//		ImGui::Text("%s", fmt::format("ve {}, {}, {}, {}", matrix[4], matrix[5], matrix[6], matrix[7]).c_str());
//		ImGui::Text("%s", fmt::format("ve {}, {}, {}, {}", matrix[8], matrix[9], matrix[10], matrix[11]).c_str());
//		ImGui::Text("%s", fmt::format("ve {}, {}, {}, {}", matrix[12], matrix[13], matrix[14], matrix[15]).c_str());
		ImGui::End();

		sf::RenderStates states;
		window.clear();
		window.draw(shape);

		update_scale(sf::Vector2f(sca, sca));
		update_rotation(rot);
		update_velocity(veloRaw.x, veloRaw.y);
		update_position();
		draw(window);

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}
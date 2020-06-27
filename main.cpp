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
#include "scene/Actor.h"

using namespace std;
using namespace dln;

class RectShape : public sf::RectangleShape, public Component {
public:
	explicit RectShape(const sf::Vector2f &size = sf::Vector2f(0, 0)) : sf::RectangleShape(size), Component() {

	}
};

struct PlayerMovement {
	float dx, dy;
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
	auto view = dln::ECS::Instance()->registry.view<PlayerMovement>();

	for (auto entity: view) {
		auto &vel = view.get<PlayerMovement>(entity);
		vel.dx = x;
		vel.dy = y;
	}
}

void update_position() {
	auto view = dln::ECS::Instance()->registry.view<Transform, PlayerMovement>();

	for (auto entity: view) {
		auto &vel = view.get<PlayerMovement>(entity);
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

int main() {
	entt::entity player_ent = ECS::get_registry().create();
	Actor player(player_ent);
	Transform &watch = player.get_transform();

	auto& r = ECS::add_component<RectShape>(player_ent);
	r.setSize(sf::Vector2f(100, 100));
	r.setFillColor(sf::Color::Red);
	ECS::get_registry().emplace<PlayerMovement>(player_ent);
//	ECS::add_component<PlayerMovement>(player_ent);

	entt::entity a_ent = ECS::get_registry().create();
	dln::Actor a(a_ent);
	RectShape &rs = ECS::add_component<RectShape>(a_ent);
	rs.setSize(sf::Vector2f(100, 100));
	a.get_transform().set_parent(player.get_entity());
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
		ImGui::Text("%s", fmt::format("This is using fmt {} : {}", 3, 6).c_str());
		ImGui::Text("%s", fmt::format("Clock {}", dt.asSeconds()).c_str());
		ImGui::Text("%s", fmt::format("Input {}, {}", movementInput.x, movementInput.y).c_str());
		ImGui::Text("%s", fmt::format("ve {}, {}", veloRaw.x, veloRaw.y).c_str());
		ImGui::Text("%s", fmt::format("ve {}, {}", veloRaw.x, veloRaw.y).c_str());

		ImGui::Text("%s", fmt::format("e loc rot {}", player.get_transform().get_rotation()).c_str());
		ImGui::Text("%s", fmt::format("e glob rot {}", player.get_transform().get_global_rotation()).c_str());
		ImGui::Text("%s",
					fmt::format("e loc sca {} {}",
								player.get_transform().get_scale().x,
								player.get_transform().get_scale().y).c_str());
		ImGui::Text("%s",
					fmt::format("e glob sca {} {}",
								player.get_transform().get_global_scale().x,
								player.get_transform().get_global_scale().y).c_str());

		ImGui::Text("%s", fmt::format("c loc rot {}", a.get_transform().get_rotation()).c_str());
		ImGui::Text("%s", fmt::format("c glob rot {}", a.get_transform().get_global_rotation()).c_str());
		ImGui::Text("%s",
					fmt::format("c loc sca {} {}",
								a.get_transform().get_scale().x,
								a.get_transform().get_scale().y).c_str());
		ImGui::Text("%s",
					fmt::format("c glob sca {} {}",
								a.get_transform().get_global_scale().x,
								a.get_transform().get_global_scale().y).c_str());

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
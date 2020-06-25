#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "spdlog/spdlog.h"
#include "collision2d/cute_c2.h"
#include <entt/entt.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "scene/Component/Transform.h"

struct velocity{
	float dx, dy;
};

void update_velocity(float x, float y, entt::registry& registry){
	auto view = registry.view<velocity>();

	for(auto entity: view){
		auto &vel = view.get<velocity>(entity);
		vel.dx = x;
		vel.dy = y;
	}
}

void update_position(entt::registry &registry){
	auto view = registry.view<Transform, velocity>();

	for(auto entity: view){
		auto &vel = view.get<velocity>(entity);
		auto &tr = view.get<Transform>(entity);

		tr.set_position(tr.get_position() + sf::Vector2f(vel.dx, vel.dy));
		vel.dx = 0;
		vel.dy = 0;
	}
}

void draw(sf::RenderWindow& window, entt::registry& registry){
	auto view = registry.view<sf::RectangleShape, Transform>();

	for(auto entity: view) {
		auto &re = view.get<sf::RectangleShape>(entity);
		auto &tr = view.get<Transform>(entity);

		re.setPosition(tr.get_global_position());

		window.draw(re);
	}
}


int main()
{
	entt::registry registry;
	auto entity = registry.create();
	registry.emplace<Transform>(entity);
	registry.emplace<velocity>(entity);
	registry.emplace<sf::RectangleShape>(entity, sf::Vector2f(100, 100));

	float movementSpeed = 5;

	spdlog::info(fmt::format("Clock "));

    spdlog::info("Yo this is speedlog");
	sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}


		ImGui::SFML::Update(window, deltaClock.restart());

		sf::Vector2f movementInput;

		//Input
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			movementInput.x += 1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			movementInput.x -= 1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			movementInput.y -= 1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			movementInput.y += 1;

		sf::Vector2f veloRaw = movementInput * movementSpeed;

		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::Text("%s", fmt::format("This is using fmt {} : {}", 3, 6).c_str());
		ImGui::Text("%s", fmt::format("Clock {}", deltaClock.getElapsedTime().asSeconds()).c_str());
		ImGui::Text("%s", fmt::format("Input {}, {}", movementInput.x, movementInput.y).c_str());
		ImGui::Text("%s", fmt::format("ve {}, {}", veloRaw.x, veloRaw.y).c_str());
		ImGui::Text("%s", fmt::format("ve {}, {}", veloRaw.x, veloRaw.y).c_str());
		ImGui::End();

		sf::RenderStates states;
		window.clear();
		window.draw(shape);
		update_velocity(veloRaw.x, veloRaw.y, registry);
		update_position(registry);
		draw(window, registry);

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}
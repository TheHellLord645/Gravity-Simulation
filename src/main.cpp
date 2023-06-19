#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "vector2.cpp"
#include <vector>

const int WIDTH = 1366;
const int HEIGHT = 697;
const int FPS = 60;

class Planet {
public:
	Vec2 position;
	Vec2 velocity;
	float radius, mass;
	sf::Color color;

	std::vector<Vec2> trails;

	Planet(Vec2 position, Vec2 velocity, float radius, float mass, sf::Color color)
		: position(position), velocity(velocity), radius(radius), mass(mass), color(color) {}

	void draw(sf::RenderWindow& window, bool drawTrails) {
		trails.push_back(position);
		if (trails.size() == 200) trails.erase(trails.begin());
		if (drawTrails) {
			for (int i = 0; i < trails.size(); i++) {
				sf::CircleShape trail(2.5, 8);
				trail.setPosition(sf::Vector2f(trails[i].x - 2.5, trails[i].y - 2.5));
				trail.setFillColor(color);
				window.draw(trail);
			}
		}

		sf::CircleShape planet(radius, 100);
		planet.setPosition(sf::Vector2f(position.x-radius, position.y-radius));
		planet.setFillColor(color);
		window.draw(planet);
	}
};

class Solver {
public:
	std::vector<Planet> planets;
	float G;
	int timestep = 1;
	int reverse = 1;
	bool drawTrails = false;

	Solver(float G) : G(G) {}

	void addPlanet(Vec2 position, float radius, float mass, sf::Color color = sf::Color::White, Vec2 velocity = Vec2(0, 0)) {
		planets.push_back(Planet(position, velocity, radius, mass, color));
	}

	void update(sf::RenderWindow& window, float dt) {
		updateGravity(dt * timestep);
		updatePositions(dt * timestep);
		draw(window);
	}

	void updateGravity(float dt) {
		for (int i = 0; i < planets.size(); i++) {
			for (int j = 0; j < planets.size(); j++) {
				if (j != i) {
					Vec2 to_planet = planets[j].position - planets[i].position;
					float dist = to_planet.magnitude() / 25;
					Vec2 normDist = to_planet.normalized();
					Vec2 force = normDist * G * planets[i].mass * planets[j].mass / (dist * dist);
					Vec2 acceleration = force / planets[i].mass;
					planets[i].velocity += acceleration * reverse * dt;
				}
			}
		}
	}

	void updatePositions(float dt) {
		for (auto& planet : planets) {
			planet.position += planet.velocity * reverse * dt;
		}
	}

	void draw(sf::RenderWindow& window) {
		for (auto& planet : planets) {
			planet.draw(window, drawTrails);
		}
	}
};

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(1366, 697), "Gravity Simulation", sf::Style::Default, settings);
	window.setFramerateLimit(FPS);
	ImGui::SFML::Init(window);

	Solver solver(1000);
	solver.addPlanet(Vec2(83, 400), 20, 1, sf::Color(0, 255, 220), Vec2(0, -250));
	solver.addPlanet(Vec2(283, 400), 50, 20, sf::Color(30, 255, 0), Vec2(50, 0));
	solver.addPlanet(Vec2(13, 349), 10, 0.1, sf::Color(255, 0, 30), Vec2(0, -150));

	// Two planets orbitting around their lagrangian points
	/*solver.addPlanet(Vec2(483, 349), 50, 20, sf::Color(0, 255, 220), Vec2(0, -100));
	solver.addPlanet(Vec2(883, 349), 50, 20, sf::Color(30, 255, 0), Vec2(0, 100));*/

	Vec2 position(100, 100), velocity(0, 0);
	float radius(25), mass(10);

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Time dt = clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
		}
		ImGui::SFML::Update(window, clock.restart());

		// UI
		{
			ImGui::Begin("Settings");
			int fps = 1 / dt.asSeconds();
			ImGui::Text("FPS: %i", fps);
			float pos[2] = { position.x, position.y };
			float vel[2] = { velocity.x, velocity.y };
			ImGui::SliderFloat2("Position", pos, 0, window.getSize().x);
			ImGui::SliderFloat2("Initial Velocity", vel, 0, 1000);
			position = Vec2(pos[0], pos[1]);
			velocity = Vec2(vel[0], vel[1]);
			ImGui::SliderFloat("Radius", &radius, 0, 1000);
			ImGui::SliderFloat("Mass", &mass, 0, 100000);
			ImGui::SliderInt("Timestep", &solver.timestep, 0, 10);
			if (ImGui::Button("Reverse")) solver.reverse *= -1;
			ImGui::Checkbox("Draw Trails", &solver.drawTrails);
			if (ImGui::Button("Create Planet", ImVec2(200, 50)))
				solver.addPlanet(position, radius, mass, sf::Color::White, velocity);
			ImGui::End();
		}

		window.clear(sf::Color::Black);
		solver.update(window, dt.asSeconds());
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}
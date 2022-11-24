#include <sfml/Graphics.hpp>
#include <vector>
#include <cmath>

#define PI 3.14159265

void draw_rect(std::vector<sf::RectangleShape>& walls) {
	sf::RectangleShape rect1(sf::Vector2f(100, 50));
	rect1.setPosition(sf::Vector2f(100, 75));
	sf::RectangleShape rect2(sf::Vector2f(120, 120));
	rect2.setPosition(sf::Vector2f(300, 180));
	sf::RectangleShape rect3(sf::Vector2f(150, 130));
	rect3.setPosition(sf::Vector2f(550, 100));

	walls.push_back(rect1);
	walls.push_back(rect2);
	walls.push_back(rect3);
	for (int i = 0; i < walls.size(); ++i)
		walls[i].setFillColor(sf::Color::Black);
}

void draw_circle(std::vector<sf::CircleShape>& walls) {
	sf::CircleShape circle1(50);
	circle1.setPosition(sf::Vector2f(150, 450));
	sf::CircleShape circle2(75);
	circle2.setPosition(sf::Vector2f(450, 360));
	walls.push_back(circle1);
	walls.push_back(circle2);
	for (int i = 0; i < walls.size(); ++i)
		walls[i].setFillColor(sf::Color::Black);
}

sf::Texture draw_background(sf::RenderWindow& window) {
	sf::Image background;
	background.create(window.getSize().x, window.getSize().y, sf::Color(41, 49, 51));
	sf::Texture text_bg;
	text_bg.loadFromImage(background);
	return text_bg;
}

int WinMain() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "", sf::Style::Default, settings);
	window.setFramerateLimit(240);
	sf::Event event;
	
	sf::Texture text_bg = draw_background(window);
	sf::Sprite sprite_bg(text_bg);

	sf::RectangleShape ray(sf::Vector2f(1, 3000));
	ray.setPosition(50, 450);

	std::vector<sf::RectangleShape> rect_walls;
	draw_rect(rect_walls);

	std::vector<sf::CircleShape> circle_walls;
	draw_circle(circle_walls);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (int i = 0; i <= 720; i += 1) {
			window.clear();
			window.draw(sprite_bg);
			for (int i = 0; i < rect_walls.size(); ++i)
				window.draw(rect_walls[i]);
			for (int i = 0; i < circle_walls.size(); ++i)
				window.draw(circle_walls[i]);
			ray.setRotation(-(i / 4));
			window.draw(ray);
			window.display();
		}
	}
	return 0;
}

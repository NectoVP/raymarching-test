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


	sf::RectangleShape rect6(sf::Vector2f(800, 20));
	rect6.setPosition(sf::Vector2f(0, 0));
	sf::RectangleShape rect7(sf::Vector2f(20, 600));
	rect7.setPosition(sf::Vector2f(0, 0));
	sf::RectangleShape rect8(sf::Vector2f(800, 20));
	rect8.setPosition(sf::Vector2f(0, 580));
	sf::RectangleShape rect9(sf::Vector2f(20, 600));
	rect9.setPosition(sf::Vector2f(780, 0));
	walls.push_back(rect1);
	walls.push_back(rect2);
	walls.push_back(rect3);
	walls.push_back(rect6);
	walls.push_back(rect7);
	walls.push_back(rect8);
	walls.push_back(rect9);
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

float dist_points(float a, float b) {
	return sqrt(a * a + b * b);
}

float dist_circle(sf::Vector2f& start, std::vector<sf::CircleShape>& walls, sf::Color& color) {
	float min = 10000;
	for (int i = 0; i < walls.size(); ++i) {
		float dist = dist_points(walls[i].getPosition().x + walls[i].getRadius() - start.x, walls[i].getPosition().y + walls[i].getRadius() - start.y) - walls[i].getRadius();
		if (dist <= min) {
			min = dist;
			sf::Color color = walls[i].getFillColor();
		}
	}
	return min;
}

float dist_rect(sf::Vector2f& start, std::vector<sf::RectangleShape>& walls, sf::Color& color) {
	float dist;
	float min = 1000000;
	sf::Vector2f temp = start;
	for (int i = 0; i < walls.size(); ++i) {
		temp.x = abs(abs(start.x) - (walls[i].getPosition().x + (walls[i].getSize().x / 2)));
		temp.y = abs(abs(start.y) - (walls[i].getPosition().y + (walls[i].getSize().y / 2)));
		dist = dist_points(std::max(temp.x - walls[i].getSize().x / 2, 0.f), std::max(temp.y - walls[i].getSize().y / 2, 0.f));
		if (dist < min) {
			min = dist;
			sf::Color color = walls[i].getFillColor();
		}

	}
	return min;
}

float dist_to_walls(sf::Vector2f start, std::vector<sf::CircleShape>& circle_walls, std::vector<sf::RectangleShape>& rect_walls, sf::Color& color) {
	float c = 10000, r = 10000;
	c = dist_circle(start, circle_walls, color);
	r = dist_rect(start, rect_walls, color);
	return std::min(c, r);
}

sf::Texture draw_background(sf::RenderWindow& window) {
	sf::Image background;
	background.create(window.getSize().x, window.getSize().y, sf::Color(41, 49, 51));
	sf::Texture text_bg;
	text_bg.loadFromImage(background);
	return text_bg;
}

void calc_ray(std::vector<sf::CircleShape>& circle_walls, std::vector<sf::RectangleShape>& rect_walls, sf::RectangleShape& ray, sf::RenderWindow& window, sf::VertexArray& marked) {
	sf::Vector2f start(50, 450);
	sf::CircleShape circle;
	circle.setOutlineColor(sf::Color(220, 220, 220));
	circle.setOutlineThickness(2.f);
	circle.setFillColor(sf::Color(47, 79, 79, 0));
	float rad = 1000;
	sf::Color color = sf::Color(220, 220, 220);
	while (rad > 1.f) {
		rad = dist_to_walls(start, circle_walls, rect_walls, color);
		circle.setRadius(rad);
		circle.setPosition(sf::Vector2f(start.x - rad, start.y - rad));
		circle.setOutlineColor(color);
		sf::Vector2f b2;
		start.x = sin(PI * (ray.getRotation() - 180) / 180) * rad + start.x;
		start.y = cos(PI * ray.getRotation() / 180) * rad + start.y;
		//color.a = 0;
		window.draw(circle);
	}
	sf::Vertex temp = sf::Vertex(sf::Vector2f(start.x, start.y), sf::Color::White);
	marked.append(temp);
	float new_size = dist_points(start.x - 50, start.y - 450);
	ray.setSize(sf::Vector2f(1, new_size));
}

int WinMain() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "", sf::Style::Default, settings);
	window.setFramerateLimit(240);
	sf::Event event;
	window.setMouseCursorVisible(false);
	window.setMouseCursorGrabbed(true);

	sf::Texture text_bg = draw_background(window);
	sf::Sprite sprite_bg(text_bg);

	sf::RectangleShape ray(sf::Vector2f(1, 3000));
	ray.setPosition(50, 450);

	std::vector<sf::RectangleShape> rect_walls;
	draw_rect(rect_walls);

	std::vector<sf::CircleShape> circle_walls;
	draw_circle(circle_walls);

	sf::VertexArray marked(sf::Points);

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
			calc_ray(circle_walls, rect_walls, ray, window, marked);
			window.draw(ray);
			window.draw(marked);
			window.display();
		}
	}
	return 0;
}

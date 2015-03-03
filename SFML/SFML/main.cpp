﻿#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Random>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");


class Ball
{
public:
	Ball(sf::Vector2f const &pos, sf::Vector2f const &speed, float size, sf::Color const &color)
		:speed_(speed),
		Shapes(size),
		size_(size)
		

		
	{
		Shapes.setPosition(pos);
		Shapes.move(speed_);
		//Shapes.setRadius(size_);
		Shapes.setFillColor(color);
	};
	
	void update(float dt)
	{
		sf::Vector2f pos_ = Shapes.getPosition();
		if (pos_.y > WINDOW_HEIGHT - size_ * 2)
		{
			speed_ = sf::Vector2f(speed_.x, -speed_.y);//пол
		}
		if (pos_.x > WINDOW_WIDTH - size_ * 2)
		{
			speed_ = sf::Vector2f(-speed_.x, speed_.y);//право
		}

		if (pos_.y < 0) //потолок
		{
			speed_ = sf::Vector2f(speed_.x, -speed_.y);
		}
		if (pos_.x < 0) //лево
		{
			speed_ = sf::Vector2f(-speed_.x, speed_.y);
		}

			pos_ += speed_ * dt;
			Shapes.setPosition(pos_);
		
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(Shapes);
	}


private:
	sf::CircleShape Shapes;
	sf::Vector2f speed_;
	sf::Vector2f pos_;
	float size_;
	std::string color_;
	
};

void init_all(std::vector<Ball> &Shapes, std::mt19937 &gen)
{
	for (int i = 0; i < 10; i++){

		float size(20);
		std::uniform_int_distribution<> x_dist(0, WINDOW_WIDTH - size * 10);
		std::uniform_int_distribution<> y_dist(0, WINDOW_HEIGHT - size * 10);
		sf::Vector2f pos(x_dist(gen), y_dist(gen));
		std::uniform_int_distribution<> x_sp(0, 200);
		std::uniform_int_distribution<> y_sp(0, 200);
		sf::Vector2f speed(x_sp(gen), y_sp(gen));
		std::uniform_int_distribution<> x_color(0, 255);
		std::uniform_int_distribution<> y_color(0, 255);
		std::uniform_int_distribution<> z_color(0, 255);
		sf::Color color(x_color(gen), y_color(gen), z_color(gen));
		Shapes.push_back(Ball(pos, speed, size, color));
	}
}
void draw_all(std::vector<Ball> &Shapes)
{
	for (int i = 0; i < Shapes.size(); ++i)
	{
		Shapes[i].draw(window);
	}

}
void update_all(float &last_up, std::vector<Ball> &Shapes, sf::Clock &clock)
{
	float times = clock.getElapsedTime().asSeconds();
	float dt = static_cast<float>(times - last_up);
	last_up = times;
	for (int i = 0; i < Shapes.size(); ++i)
	{
		Shapes[i].update(dt);
	}
}
int main()
{
	std::random_device rd;
	sf::Clock clock;
	std::vector<Ball> Shapes;
	std::mt19937 gen(rd());
	init_all(Shapes, gen);
	float last_up = clock.getElapsedTime().asSeconds();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		update_all(last_up, Shapes, clock);
		window.clear();
		draw_all(Shapes);
		window.display();
	}
	
	return 0;
}
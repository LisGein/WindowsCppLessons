﻿#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Random>



const int WINDOW_WIDTH = 1250;
const int WINDOW_HEIGHT = 680;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
sf::VertexArray triangle(sf::Triangles, 3);

class MovingShape
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
};

class Trigl
	:public MovingShape
{
public:
	Trigl(sf::Vector2f const &pos1, sf::Vector2f const &pos2, sf::Vector2f const &pos3, sf::Vector2f const &speed, sf::Color &color1, sf::Color &color2, sf::Color &color3)
		:speed_(speed)
	{
		triangle.setPrimitiveType(sf::Triangles);
		triangle[0].position = pos1;
		triangle[1].position = pos2;
		triangle[2].position = pos3;
		triangle[0].color = color1;
		triangle[1].color = color2;
		triangle[2].color = color3;
	};
	void update(float dt)
	{

	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(triangle);
	}

private:

	sf::Vector2f speed_;
};
void init_all(std::vector <MovingShape *> &shapes, std::mt19937 &gen)  //определение всех переменных для мячей
{
	

	for (int i = 0; i < 1000; i++)
	{
		std::uniform_int_distribution<> color_dist(0, 255);
		std::uniform_real_distribution<float> sp_dist(-100, 100);
		//общие:
		sf::Vector2f speed(sp_dist(gen), sp_dist(gen));
		sf::Color color(color_dist(gen), color_dist(gen), color_dist(gen));
		sf::Color color1(color_dist(gen), color_dist(gen), color_dist(gen));
		sf::Color color2(color_dist(gen), color_dist(gen), color_dist(gen));
		std::uniform_int_distribution<> pos_coor(10, 300);
		int pos_1 = pos_coor(gen);
		int pos_2 = pos_coor(gen);
		sf::Vector2f pos_trigl1(pos_1, pos_1);
		sf::Vector2f pos_trigl2(pos_2, pos_1);
		sf::Vector2f pos_trigl3(pos_2, pos_2);

		shapes.push_back(new Trigl(pos_trigl1, pos_trigl2, pos_trigl3, speed, color1, color2, color));
	}
}
void draw_all(std::vector <MovingShape *> shapes)
{
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i]->draw(window);
}

int main()
{
	std::vector <MovingShape *> shapes;
	
	std::random_device rd;
	std::mt19937 gen(rd());
	
	init_all(shapes, gen);

	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		draw_all(shapes);
		window.display();
	}
	for (int i = 0; i < shapes.size(); ++i)
	{
		delete shapes[i];
	}
	return 0;
}
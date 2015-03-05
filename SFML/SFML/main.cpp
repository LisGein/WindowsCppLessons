﻿#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Random>



const int WINDOW_WIDTH = 650;
const int WINDOW_HEIGHT = 680;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

class Obj
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void on_key_pressed(sf::Keyboard::Key const &code, bool press) = 0;
};

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
	Trigl(sf::VertexArray const &triangle, sf::Vector2f const &speed)
		:speed_(speed),
		_triangle(triangle)
		
	
	{

	};
	void update(float dt)
	{

	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(_triangle);
	}

private:
	sf::Vector2f speed_;
	sf::VertexArray _triangle;
	sf::Vector2f pos_1;
	sf::Vector2f pos_2;
	sf::Vector2f pos_3;

};
class SpriteCosmos  // класс - sprite
	:public MovingShape
{
public:
	SpriteCosmos(sf::Vector2f const &pos, sf::Vector2f const &speed, sf::Texture &texture)
		:speed_(speed),
		pos_(pos)
	{
		sprite_cosmos.setPosition(pos);
		sprite_cosmos.setTexture(texture);
	};
	void update(float dt)
	{
		if (pos_.y >  WINDOW_HEIGHT - sprite_cosmos.getLocalBounds().height)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол
		if (pos_.x > WINDOW_WIDTH - sprite_cosmos.getLocalBounds().width)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		if (pos_.y < 0) //потолок
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_.x < 0) //лево
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);

		pos_ += speed_ * dt;
		sprite_cosmos.setPosition(pos_);
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(sprite_cosmos);
	}
private:
	sf::Sprite sprite_cosmos;
	sf::Vector2f pos_;
	sf::Vector2f speed_;

};
class Sprite  // класс - sprite
	:public Obj
{
public:
	Sprite(sf::Vector2f const &pos, sf::Vector2f const &speed, sf::Texture &texture)
		:speed_(speed),
		pos_(pos),
		speedtest(speed_)
	{
		sprite_.setPosition(pos);
		sprite_.setTexture(texture);
	};
	void update(float dt)
	{
		if (pos_.y >  WINDOW_HEIGHT - sprite_.getLocalBounds().height)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол
		if (pos_.x > WINDOW_WIDTH - sprite_.getLocalBounds().width)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		if (pos_.y < 0) //потолок
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_.x < 0) //лево
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);

		pos_ += speed_ * dt;
		sprite_.setPosition(pos_);
		
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(sprite_);
	}
	void on_key_pressed(sf::Keyboard::Key const &code, bool press)
	{
		
		if (press){
			int speed_value = 15;
			if (code == sf::Keyboard::Up)
				speed_ = sf::Vector2f(0, -abs(speed_value * speedtest.y));
			if (code == sf::Keyboard::Down)
				speed_ = sf::Vector2f(0, abs(speed_value * speedtest.y));
			if (code == sf::Keyboard::Right)
				speed_ = sf::Vector2f(abs(speed_value * speedtest.x), 0);
			if (code == sf::Keyboard::Left)
				speed_ = sf::Vector2f(-abs(speed_value * speedtest.x), 0);
		}
		if (!press){
			int speed_value = 15;
			if (code == sf::Keyboard::Up)
				speed_ = sf::Vector2f(0, -abs (speedtest.y));
			if (code == sf::Keyboard::Down)
				speed_ = sf::Vector2f(0, abs( speedtest.y));
			if (code == sf::Keyboard::Right)
				speed_ = sf::Vector2f(abs( speedtest.x), 0);
			if (code == sf::Keyboard::Left)
				speed_ = sf::Vector2f(-abs( speedtest.x), 0);
		}
	}
private:
	sf::Sprite sprite_;
	sf::Vector2f pos_;
	sf::Vector2f speed_;
	sf::Event event;
	sf::Vector2f speedtest;
	sf::Vector2f acceleration_;
};

class Rectangle  //класс - прямоугольник
	:public MovingShape
{
public:
	Rectangle(sf::Vector2f const &pos, sf::Vector2f const &speed, sf::Vector2f const &size, sf::Color const &color)
		:speed_(speed),
		rect_(size),
		size_(size),
		pos_(pos)
	{
		rect_.setPosition(pos);
		rect_.setFillColor(color);
	};
	void update(float dt)
	{
		if (pos_.y > WINDOW_HEIGHT - size_.y)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол
		if (pos_.x > WINDOW_WIDTH - size_.x)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		if (pos_.y < 0) //потолок
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_.x < 0) //лево
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);

		pos_ += speed_ * dt;
		rect_.setPosition(pos_);
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(rect_);
	}
private:
	sf::RectangleShape rect_;
	sf::Vector2f pos_;
	sf::Vector2f size_;
	sf::Vector2f speed_;
};

class Ball  // класс - мяч
	:public MovingShape
{
public:
	Ball(sf::Vector2f const &pos, sf::Vector2f const &speed, float size, sf::Color const &color)
		:speed_(speed),
		circle_(size),
		size_(size),
		pos_(pos)
	{
		circle_.setPosition(pos);
		circle_.setFillColor(color);
	};

	void update(float dt)
	{
		if (pos_.y > WINDOW_HEIGHT - size_ * 2)
			speed_ = sf::Vector2f(speed_.x, -abs(speed_.y));//пол
		if (pos_.x > WINDOW_WIDTH - size_ * 2)
			speed_ = sf::Vector2f(-abs(speed_.x), speed_.y);//право
		if (pos_.y < 0) //потолок
			speed_ = sf::Vector2f(speed_.x, abs(speed_.y));
		if (pos_.x < 0) //лево
			speed_ = sf::Vector2f(abs(speed_.x), speed_.y);

		pos_ += speed_ * dt;
		circle_.setPosition(pos_);
	}
	void draw(sf::RenderWindow &window)
	{
		window.draw(circle_);
	}
private:
	sf::CircleShape circle_;
	sf::Vector2f speed_;
	sf::Vector2f pos_;
	float size_;
};

void init_all(std::vector <MovingShape *> &shapes, std::vector <Obj *> &shapes_, std::mt19937 &gen, sf::Texture &texture, sf::Texture &texture_)  //определение всех переменных для мячей
{


	for (int i = 0; i < 3; i++)
	{
		std::uniform_int_distribution<> color_dist(0, 255);
		std::uniform_real_distribution<float> sp_dist(-100, 100);
		//общие:
		sf::Vector2f speed(sp_dist(gen), sp_dist(gen));
		sf::Color color(color_dist(gen), color_dist(gen), color_dist(gen));
		//для шаров:
		std::uniform_real_distribution<float> size_dist(5, 10);
		float size = size_dist(gen);
		std::uniform_real_distribution<float> x_dist(0.f, WINDOW_WIDTH - 2 * size);
		std::uniform_real_distribution<float> y_dist(0.f, WINDOW_HEIGHT - 2 * size);
		sf::Vector2f pos(x_dist(gen), y_dist(gen));
		//для прямоугольников:
		std::uniform_real_distribution<float> rect_dist_x(40, 80);
		std::uniform_real_distribution<float> rect_dist_y(20, 40);
		sf::Vector2f size_(rect_dist_x(gen), rect_dist_y(gen));
		std::uniform_real_distribution<float> x_coor(0.f, WINDOW_WIDTH - size_.x);
		std::uniform_real_distribution<float> y_coor(0.f, WINDOW_HEIGHT - size_.y);
		sf::Vector2f pos_(x_coor(gen), y_coor(gen));
		texture_.loadFromFile("C:\\Users\\LisGein\\Pictures\\sprite.jpg");
		// для Sprite:
		std::uniform_real_distribution<float> x_coor_(0.f, WINDOW_WIDTH / 3);
		std::uniform_real_distribution<float> y_coor_(0.f, WINDOW_HEIGHT / 3);
		sf::Vector2f _pos(x_coor_(gen), y_coor_(gen));
		texture.loadFromFile("C:\\Users\\LisGein\\Pictures\\RedApple.png");
		// для многоугольников:
		std::uniform_int_distribution<> xcoor(0, WINDOW_WIDTH);
		std::uniform_int_distribution<> ycoor(0, WINDOW_HEIGHT);
		sf::Vector2f coor(xcoor(gen), ycoor(gen));
		//для треугольника
		std::uniform_int_distribution<> pos_coor(10, 600);
		int pos_1 = pos_coor(gen);
		int pos_2 = pos_coor(gen);
		int pos_3 = pos_coor(gen);
		sf::Vector2f pos_trigl1(pos_1, pos_2);
		sf::Vector2f pos_trigl2(pos_2, pos_3);
		sf::Vector2f pos_trigl3(pos_3, pos_2);
		sf::Color color1(color_dist(gen), color_dist(gen), color_dist(gen));
		sf::Color color2(color_dist(gen), color_dist(gen), color_dist(gen));

		sf::VertexArray triangle_(sf::Triangles, 3);
		triangle_[0].position = pos_trigl1;
		triangle_[1].position = pos_trigl2;
		triangle_[2].position = pos_trigl3;
		triangle_[0].color = color;
		triangle_[1].color = color1;
		triangle_[2].color = color2;

		shapes_.push_back(new Sprite(_pos, speed, texture));
		shapes.push_back(new SpriteCosmos(_pos, speed, texture_));
		shapes.push_back(new Ball(pos, speed, size, color));
		shapes.push_back(new Rectangle(pos_, speed, size_, color));
		shapes.push_back(new Trigl(triangle_, speed));
	}

}
void draw_all(std::vector <MovingShape *> shapes, std::vector <Obj *> shapes_)
{
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i]->draw(window);
	for (int i = 0; i < shapes_.size(); ++i)
		shapes_[i]->draw(window);
}
void on_key_pressed(std::vector <Obj *> shapes_, sf::Keyboard::Key const &code, bool press)
{
	for (int i = 0; i < shapes_.size(); ++i)
		shapes_[i]->on_key_pressed(code, press);
};
void update_all(float &last_up, std::vector <MovingShape *> shapes, std::vector <Obj *> shapes_, sf::Clock &clock)
{
	float times = clock.getElapsedTime().asSeconds();
	float dt = static_cast<float>(times - last_up);
	last_up = times;
	for (int i = 0; i < shapes.size(); ++i)
		shapes[i]->update(dt);

	for (int i = 0; i < shapes_.size(); ++i)
		shapes_[i]->update(dt);

}
int main()
{
	std::vector <MovingShape *> shapes;
	std::vector <Obj *> shapes_;
	sf::Clock clock;
	std::random_device rd;
	std::mt19937 gen(rd());
	sf::Texture texture;
	sf::Texture texture_;
	bool press = false;
	init_all(shapes, shapes_, gen, texture, texture_);

	float last_up = clock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				press = true;
			if (event.type == sf::Event::KeyReleased)
				press = false;
			
			on_key_pressed(shapes_, event.key.code, press);
			
			if (event.type == sf::Event::Closed)
				window.close();
		}

		update_all(last_up, shapes, shapes_, clock);
		window.clear();
		draw_all(shapes, shapes_);
		window.display();
	}
	for (int i = 0; i < shapes.size(); ++i)
	{
		delete shapes[i];
	}
	return 0;
}

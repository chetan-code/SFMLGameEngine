#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

class RectTextShape {
	float m_width;
	float m_heigth;
	float m_speedX;
	float m_speedY;

	sf::RectangleShape m_rect;
	sf::Color m_color;
	sf::Text m_text;

public:
	RectTextShape(std::string& name, float ipx, float ipy,
		float sx, float sy, sf::Color& rectColor, float w, float h,
		int fz, sf::Font& font, sf::Color& fontColor) :
		m_width(w),
		m_heigth(h),
		m_speedX(sx),
		m_speedY(sy)
	{
		//create shape and font
		m_rect = sf::RectangleShape(sf::Vector2f(m_width, m_heigth));
		m_text = sf::Text(name, font, fz);
		m_rect.setPosition(ipx, ipy);
		m_text.setPosition(ipx + ((w - m_text.getLocalBounds().width) / 2), ipy + ((h - m_text.getLocalBounds().height)) / 2);
		m_rect.setFillColor(rectColor);
		m_text.setFillColor(fontColor);
	}

	const sf::RectangleShape& getShape() const {
		return m_rect;
	}

	const sf::Text& getText() const {
		return m_text;
	}


	void setPosition() {
		//check if we collided with window walls 

		//calculate as per change per frame
		float newX = m_rect.getPosition().x + m_speedX;
		float newY = m_rect.getPosition().y + m_speedY;
		m_rect.setPosition(newX, newY);
		newX = m_text.getPosition().x + m_speedX;
		newY = m_text.getPosition().y + m_speedY;
		m_text.setPosition(newX, newY);
	}

	void ReverseXSpeed() {
		m_speedX *= -1;
	}

	void ReverseYSpeed() {
		m_speedY *= -1;
	}
};

class CircleTextShape {
	float m_radius;
	float m_speedX;
	float m_speedY;

	sf::CircleShape m_circle;
	sf::Color m_color;
	sf::Text m_text;

public:
	CircleTextShape(std::string& name, float ipx, float ipy,
		float sx, float sy, sf::Color& rectColor, float radius,
		int fz, sf::Font& font, sf::Color& fontColor) :
		m_radius(radius),
		m_speedX(sx),
		m_speedY(sy)
	{
		//create shape and font
		m_circle = sf::CircleShape(radius);
		m_text = sf::Text(name, font, fz);
		m_circle.setPosition(ipx, ipy);
		m_text.setPosition(ipx + (radius - (m_text.getLocalBounds().width / 2)), ipy + (radius - (m_text.getLocalBounds().height) / 2));
		m_circle.setFillColor(rectColor);
		m_text.setFillColor(fontColor);
	}

	const sf::CircleShape& getShape() const {
		return m_circle;
	}

	const sf::Text& getText() const {
		return m_text;
	}


	void setPosition() {
		//check if we collided with window walls 

		//calculate as per change per frame
		float newX = m_circle.getPosition().x + m_speedX;
		float newY = m_circle.getPosition().y + m_speedY;
		m_circle.setPosition(newX, newY);
		newX = m_text.getPosition().x + m_speedX;
		newY = m_text.getPosition().y + m_speedY;
		m_text.setPosition(newX, newY);
	}

	void ReverseXSpeed() {
		m_speedX *= -1;
	}

	void ReverseYSpeed() {
		m_speedY *= -1;
	}
};


int main(int argc, char* argv[]) {
	//window spec
	int wWidth = 0;
	int wHeight = 0;
	//font
	std::string fontFile;
	int fontSize = 0;
	sf::Color fontColor;
	//load font
	sf::Font myFont;

	//let read the config file - the window will always be at top
	std::ifstream fin("config.txt");

	//error file read
	if (!fin) {
		std::cerr << "Error reading file : check file name or directory !! " << std::endl;
		return 1;
	}

	std::vector<RectTextShape> rects;
	std::vector<CircleTextShape> circles;

	std::string temp;
	while (fin >> temp) {
		//if we read something about window stuff
		if (temp == "Window") {
			fin >> wWidth >> wHeight;
			std::cout << "Window : " << wWidth << " " << wHeight << std::endl;
		}
		//if we find font stuff
		if (temp == "Font") {
			int r, g, b;
			fin >> fontFile >> fontSize >> r >> g >> b;
			fontColor = sf::Color(r, g, b);
			//attempt to load font
			if (!myFont.loadFromFile(fontFile)) {
				//cant load font properly - print error
				std::cerr << "Could not load font! Check font name/file" << std::endl;
				exit(-1);
			}	
		}
		//circle
		if (temp == "Circle") {
			std::string name;
			float posX, posY, sx, sy, radius;
			int r, g, b;
			fin >> name >> posX >> posY >> sx >> sy >> r >> g >> b >> radius;
			std::cout << temp << name << " " << posX << " " << posY << " " << sx << " " << sy << " " << r << " " << g << " " << b << " " << r  << std::endl;
			sf::Color color(r, g, b);
			CircleTextShape circle(name, posX, posY,
				sx, sy, color, radius,
				fontSize, myFont, fontColor);
			circles.push_back(circle);
		}


		//rect 
		if (temp == "Rectangle") {
			std::string name;
			float posX, posY, sx, sy, w, h;
			int r, g, b;
			fin >> name >> posX >> posY >> sx >> sy >> r >> g >> b >> w >> h;
			std::cout << temp << name << " " << posX << " " << posY << " " << sx << " " << sy << " " << r << " " << g << " " << b << " " << w << " " << h<< std::endl;
			sf::Color color(r, g, b);
			RectTextShape rectText(name, posX, posY,
				sx, sy, color, w, h,
				fontSize, myFont, fontColor);
			rects.push_back(rectText);
		}

		std::cout << temp << std::endl;

	}

	////create a window
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Shape Hell");


	//run the program as long as the window is open
	while (window.isOpen()) {
		//check for any window related events
		sf::Event event;
		//poll event will return true if we have events that happened in last loop cycle 
		//else it will return false
		while (window.pollEvent(event)) {
			//we are looping through all the events
			//closed we pressed exit window
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			//key press event
			if (event.type == sf::Event::KeyPressed) {
				std::cout << "Key Pressed " << event.key.code << std::endl;
			
				//do something with key code
				if (event.key.code == sf::Keyboard::X) {
				}
			}
		}



		//basic rendering window
		window.clear();
		//check of shape is colliding
		for (auto& rectText : rects) {
			rectText.setPosition();
			float right = rectText.getShape().getPosition().x + rectText.getShape().getSize().x;
			float bottom = rectText.getShape().getPosition().y + rectText.getShape().getSize().y;
			//collding at top
			if (rectText.getShape().getPosition().y < 0) {
				rectText.ReverseYSpeed();
			}
			//colliding at bottom
			if (bottom > wHeight) {
				rectText.ReverseYSpeed();
			}
			//colliding left
			if (rectText.getShape().getPosition().x < 0) {
				rectText.ReverseXSpeed();
			}
			//colliding right
			if (right > wWidth) {
				rectText.ReverseXSpeed();
			}
			window.draw(rectText.getShape());
			window.draw(rectText.getText());
		}

		for (auto& circle : circles) {
			circle.setPosition();
			float right = circle.getShape().getPosition().x + (circle.getShape().getRadius()* 2);
			float bottom = circle.getShape().getPosition().y + (circle.getShape().getRadius() * 2);
			//collding at top
			if (circle.getShape().getPosition().y < 0) {
				circle.ReverseYSpeed();
			}
			//colliding at bottom
			if (bottom > wHeight) {
				circle.ReverseYSpeed();
			}
			//colliding left
			if (circle.getShape().getPosition().x < 0) {
				circle.ReverseXSpeed();
			}
			//colliding right
			if (right > wWidth) {
				circle.ReverseXSpeed();
			}
			window.draw(circle.getShape());
			window.draw(circle.getText());
		}

		window.display();
	}


	return 0;
}
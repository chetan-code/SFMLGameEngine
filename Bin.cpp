//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
//
//class Student {
//	std::string m_first = "First";
//	std::string m_last = "Last";
//	int m_id = 0;
//	float m_avg = 0;
//
//public:
//	Student() {} //default constructor
//	Student(std::string first, std::string last, int id, float avg) :
//		m_first(first),
//		m_last(last),
//		m_id(id),
//		m_avg(avg)
//	{
//	}
//
//	float getAvg() const {
//		return m_avg;
//	}
//
//	int getID() const {
//		return m_id;
//	}
//
//	std::string getFirst() const {
//		return m_first;
//	}
//
//	std::string getLast() const {
//		return m_last;
//	}
//
//	void print() const {
//		std::cout << m_first << " " << m_last << " "
//			<< m_id << " " << m_avg << std::endl;
//	}
//};
//
//class Course {
//
//	std::string m_name = "Course";
//	std::vector<Student> m_student;
//
//public:
//	Course() {}
//	Course(const std::string& name) : m_name(name) {}
//
//	void AddStudent(const Student& s) {
//		m_student.push_back(s);
//	}
//
//	const std::vector<Student> getStudent() const {
//		return m_student;
//	}
//
//	void print() const {
//		for (const auto& s : m_student) {
//			s.print();
//		}
//	}
//
//	void loadFromFile(const std::string& filename) {
//		std::ifstream fin(filename);//reading a file
//
//		//load string tokens from files
//		std::string first, last;
//		int id;
//		float avg;
//
//		while (fin >> first) {
//			fin >> last >> id >> avg;
//			AddStudent(Student(first, last, id, avg));
//		}
//	}
//};
//
////pass by value - we copy value the use it
////if we pass reference - we pass the og var 
//void pp(int& i) {
//	std::cout << &i << " " << i << " " << sizeof(i) << std::endl;
//}
//
////We need to implement RAII for all 
//// so we can use template just like generic in java
////IntArray - RAII
//template <typename T>
//class DynamicArray {
//
//	T* m_arr;
//	size_t m_size;
//
//public:
//	//constructor acquire resource
//	DynamicArray(size_t size) :
//		m_size(size),
//		m_arr(new T[size]) {
//		std::cout << "Arr constructed" << std::endl;
//	}
//
//	T get(size_t index) const {
//		return m_arr[index];
//	}
//
//	void set(size_t index, T val) {
//		m_arr[index] = val;
//	}
//
//	//operator overloading
//	//T& is memory address of value - we can set it
//	const T& operator [] (size_t index) const {
//		return m_arr[index];
//	}
//
//	T& operator [] (size_t index) {
//		return m_arr[index];
//	}
//
//	~DynamicArray() {
//		std::cout << "Arr Destructed" << std::endl;
//		delete[] m_arr;
//	}
//
//	void print() const {
//		for (size_t i = 0; i < m_size; i++) {
//			std::cout << (m_arr[i]) << std::endl;
//		}
//	}
//
//};
//
//
//int oldMain(int argc, char* argv[]) {
//
//	//Course c("Sharma");
//	//c.loadFromFile("students.txt");
//	//c.print();
//	//we cant modifiy const arr
//	DynamicArray<float> arr(3);
//	arr[0] = 7.14;
//	arr[1] = 455.6;
//	arr[2] = 2.119;
//
//
//	arr.print();
//
//
//	return 0;
//}
//
//
////old code till assignment 2 starts 
////#include <iostream>
////#include <fstream>
////#include <string>
////#include <SFML/Graphics.hpp>
////
////class RectTextShape {
////	float m_width;
////	float m_heigth;
////	float m_speedX;
////	float m_speedY;
////
////	sf::RectangleShape m_rect;
////	sf::Color m_color;
////	sf::Text m_text;
////
////public:
////	RectTextShape(std::string& name, float ipx, float ipy,
////		float sx, float sy, sf::Color& rectColor, float w, float h,
////		int fz, sf::Font& font, sf::Color& fontColor) :
////		m_width(w),
////		m_heigth(h),
////		m_speedX(sx),
////		m_speedY(sy)
////	{
////		//create shape and font
////		m_rect = sf::RectangleShape(sf::Vector2f(m_width, m_heigth));
////		m_text = sf::Text(name, font, fz);
////		m_rect.setPosition(ipx, ipy);
////		m_text.setPosition(ipx + ((w - m_text.getLocalBounds().width) / 2), ipy + ((h - m_text.getLocalBounds().height)) / 2);
////		m_rect.setFillColor(rectColor);
////		m_text.setFillColor(fontColor);
////	}
////
////	const sf::RectangleShape& getShape() const {
////		return m_rect;
////	}
////
////	const sf::Text& getText() const {
////		return m_text;
////	}
////
////
////	void setPosition() {
////		//check if we collided with window walls 
////
////		//calculate as per change per frame
////		float newX = m_rect.getPosition().x + m_speedX;
////		float newY = m_rect.getPosition().y + m_speedY;
////		m_rect.setPosition(newX, newY);
////		newX = m_text.getPosition().x + m_speedX;
////		newY = m_text.getPosition().y + m_speedY;
////		m_text.setPosition(newX, newY);
////	}
////
////	void ReverseXSpeed() {
////		m_speedX *= -1;
////	}
////
////	void ReverseYSpeed() {
////		m_speedY *= -1;
////	}
////};
////
////class CircleTextShape {
////	float m_radius;
////	float m_speedX;
////	float m_speedY;
////
////	sf::CircleShape m_circle;
////	sf::Color m_color;
////	sf::Text m_text;
////
////public:
////	CircleTextShape(std::string& name, float ipx, float ipy,
////		float sx, float sy, sf::Color& rectColor, float radius,
////		int fz, sf::Font& font, sf::Color& fontColor) :
////		m_radius(radius),
////		m_speedX(sx),
////		m_speedY(sy)
////	{
////		//create shape and font
////		m_circle = sf::CircleShape(radius);
////		m_text = sf::Text(name, font, fz);
////		m_circle.setPosition(ipx, ipy);
////		m_text.setPosition(ipx + (radius - (m_text.getLocalBounds().width / 2)), ipy + (radius - (m_text.getLocalBounds().height) / 2));
////		m_circle.setFillColor(rectColor);
////		m_text.setFillColor(fontColor);
////	}
////
////	const sf::CircleShape& getShape() const {
////		return m_circle;
////	}
////
////	const sf::Text& getText() const {
////		return m_text;
////	}
////
////
////	void setPosition() {
////		//check if we collided with window walls 
////
////		//calculate as per change per frame
////		float newX = m_circle.getPosition().x + m_speedX;
////		float newY = m_circle.getPosition().y + m_speedY;
////		m_circle.setPosition(newX, newY);
////		newX = m_text.getPosition().x + m_speedX;
////		newY = m_text.getPosition().y + m_speedY;
////		m_text.setPosition(newX, newY);
////	}
////
////	void ReverseXSpeed() {
////		m_speedX *= -1;
////	}
////
////	void ReverseYSpeed() {
////		m_speedY *= -1;
////	}
////};
////
////
////class Vec2 {
////
////public:
////	float x;
////	float y;
////
////	Vec2() {};
////	Vec2(float xin, float yin) : x(xin), y(yin) {};
////
////	Vec2 operator + (Vec2& rhs) {
////		return Vec2(x + rhs.x, y + rhs.y);
////	}
////
////	Vec2 operator * (Vec2& rhs) {
////		return Vec2(x * rhs.x, y * rhs.y);
////	}
////
////	Vec2 operator / (Vec2& rhs) {
////		return Vec2(x / rhs.x, y / rhs.y);
////	}
////
////	Vec2 operator - (Vec2& rhs) {
////		return Vec2(x - rhs.x, y - rhs.y);
////	}
////
////	void print() {
////		std::cout << x << " " << y << std::endl;
////	}
////
////	Vec2& add(Vec2& rhs) {
////		x += rhs.x;
////		y += rhs.y;
////		return *this;
////	}
////
////};
////
////int main(int argc, char* argv[]) {
////	Vec2 pos(10, 10);
////	Vec2 speed(18, 12);
////
////	Vec2 newPos = pos + speed;
////	Vec2 hell = pos.add(speed).add(newPos);
////
////	hell.print();
////
////	std::cout << newPos.x << " " << newPos.y << std::endl;
////	//window spec
////	int wWidth = 0;
////	int wHeight = 0;
////	//font
////	std::string fontFile;
////	int fontSize = 0;
////	sf::Color fontColor;
////	//load font
////	sf::Font myFont;
////
////	//let read the config file - the window will always be at top
////	std::ifstream fin("config.txt");
////
////	//error file read
////	if (!fin) {
////		std::cerr << "Error reading file : check file name or directory !! " << std::endl;
////		return 1;
////	}
////
////	std::vector<RectTextShape> rects;
////	std::vector<CircleTextShape> circles;
////
////	std::string temp;
////	while (fin >> temp) {
////		//if we read something about window stuff
////		if (temp == "Window") {
////			fin >> wWidth >> wHeight;
////			std::cout << "Window : " << wWidth << " " << wHeight << std::endl;
////		}
////		//if we find font stuff
////		if (temp == "Font") {
////			int r, g, b;
////			fin >> fontFile >> fontSize >> r >> g >> b;
////			fontColor = sf::Color(r, g, b);
////			//attempt to load font
////			if (!myFont.loadFromFile(fontFile)) {
////				//cant load font properly - print error
////				std::cerr << "Could not load font! Check font name/file" << std::endl;
////				exit(-1);
////			}
////		}
////		//circle
////		if (temp == "Circle") {
////			std::string name;
////			float posX, posY, sx, sy, radius;
////			int r, g, b;
////			fin >> name >> posX >> posY >> sx >> sy >> r >> g >> b >> radius;
////			std::cout << temp << name << " " << posX << " " << posY << " " << sx << " " << sy << " " << r << " " << g << " " << b << " " << r << std::endl;
////			sf::Color color(r, g, b);
////			CircleTextShape circle(name, posX, posY,
////				sx, sy, color, radius,
////				fontSize, myFont, fontColor);
////			circles.push_back(circle);
////		}
////
////
////		//rect 
////		if (temp == "Rectangle") {
////			std::string name;
////			float posX, posY, sx, sy, w, h;
////			int r, g, b;
////			fin >> name >> posX >> posY >> sx >> sy >> r >> g >> b >> w >> h;
////			std::cout << temp << name << " " << posX << " " << posY << " " << sx << " " << sy << " " << r << " " << g << " " << b << " " << w << " " << h << std::endl;
////			sf::Color color(r, g, b);
////			RectTextShape rectText(name, posX, posY,
////				sx, sy, color, w, h,
////				fontSize, myFont, fontColor);
////			rects.push_back(rectText);
////		}
////
////		std::cout << temp << std::endl;
////
////	}
////
////	////create a window
////	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Shape Hell");
////
////
////	//run the program as long as the window is open
////	while (window.isOpen()) {
////		//check for any window related events
////		sf::Event event;
////		//poll event will return true if we have events that happened in last loop cycle 
////		//else it will return false
////		while (window.pollEvent(event)) {
////			//we are looping through all the events
////			//closed we pressed exit window
////			if (event.type == sf::Event::Closed) {
////				window.close();
////			}
////
////			//key press event
////			if (event.type == sf::Event::KeyPressed) {
////				std::cout << "Key Pressed " << event.key.code << std::endl;
////
////				//do something with key code
////				if (event.key.code == sf::Keyboard::X) {
////				}
////			}
////		}
////
////
////
////		//basic rendering window
////		window.clear();
////		//check of shape is colliding
////		for (auto& rectText : rects) {
////			rectText.setPosition();
////			float right = rectText.getShape().getPosition().x + rectText.getShape().getSize().x;
////			float bottom = rectText.getShape().getPosition().y + rectText.getShape().getSize().y;
////			//collding at top
////			if (rectText.getShape().getPosition().y < 0) {
////				rectText.ReverseYSpeed();
////			}
////			//colliding at bottom
////			if (bottom > wHeight) {
////				rectText.ReverseYSpeed();
////			}
////			//colliding left
////			if (rectText.getShape().getPosition().x < 0) {
////				rectText.ReverseXSpeed();
////			}
////			//colliding right
////			if (right > wWidth) {
////				rectText.ReverseXSpeed();
////			}
////			window.draw(rectText.getShape());
////			window.draw(rectText.getText());
////		}
////
////		for (auto& circle : circles) {
////			circle.setPosition();
////			float right = circle.getShape().getPosition().x + (circle.getShape().getRadius() * 2);
////			float bottom = circle.getShape().getPosition().y + (circle.getShape().getRadius() * 2);
////			//collding at top
////			if (circle.getShape().getPosition().y < 0) {
////				circle.ReverseYSpeed();
////			}
////			//colliding at bottom
////			if (bottom > wHeight) {
////				circle.ReverseYSpeed();
////			}
////			//colliding left
////			if (circle.getShape().getPosition().x < 0) {
////				circle.ReverseXSpeed();
////			}
////			//colliding right
////			if (right > wWidth) {
////				circle.ReverseXSpeed();
////			}
////			window.draw(circle.getShape());
////			window.draw(circle.getText());
////		}
////
////
////
////		window.display();
////	}
////
////
////	return 0;
////}
//

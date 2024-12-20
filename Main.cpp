#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Vec2.h"

int main() {
	Game g("config.txt");
	g.run();

	Vec2 a(100, 200);
	Vec2 b(200, 300);
	Vec2 c = a + b;
	std::cout << c.x << ":" << c.y << std::endl;
}
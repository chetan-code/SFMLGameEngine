#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>


sf::Vector2f getCenter(unsigned int screenWidth ,unsigned int screenHeight, sf::Vector2f size) {
    float centerX = (float)screenWidth / 2 - (size.x/2);
    float centerY = (float)screenHeight / 2 - (size.y/2);
    return sf::Vector2f(centerX, centerY);
}

class Vec2 {
public :
    //public variables dont need hungarian nottation like m_
    float x = 0;
    float y = 0;
    //default constructor
    Vec2() {}
    //using intializer list to intialize vars
    Vec2(float xin, float yin) : x(xin), y(yin) {}
    //operator ovverloading
    Vec2 operator + (const Vec2& rhs) const {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    void operator += (const Vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
    }
    //chaining - allows use to perform same operation one after other
    //we return a reference of result value
    Vec2& add(const Vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2& scale(float s) {
        x *= s;
        y *= s;
        return *this;
    }

    Vec2 rotate(float deg) {
        //rotation magic
        return *this;
    }

    float dist(const Vec2 v) const {
        //distance = squareroot(deltax * deltax + deltay*deltay);
        return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
    }
};




int main(int args, char* argv[])
{
    Vec2 v1(100, 100);
    Vec2 v2(2, 2);
    Vec2 v3 = v1 + v2;
    //v1.add(v2);
    //v1 += v2;
    v1.add(v2).add(v3);//chaining
    //scaler value from vec2 -  
    float dist = v1.dist(v2);
    //we can do chaining like
    v2.scale(2).rotate(10).add(v3);
    std::cout << v3.x << " " << v3.y << std::endl;
    return 0;
}


void SfmlTest() {
    //std::vector<sf::Drawable> drawables;
    unsigned int wWidth = 640;
    unsigned int wHeight = 480;
    std::string fontPath;
    sf::Color fontColor = sf::Color::White;
    unsigned int fontSize = 0;


    //reading a config file
    std::ifstream config("bin/config.txt");
    std::string line;
    while (config >> line) {
        std::cout << line << std::endl;
        //reading window config
        if (line == "Window") {
            config >> wWidth >> wHeight;
            std::cout << "Window : " << wWidth << "x" << wHeight << std::endl;
        }
        //reading font asset
        if (line == "Font") {
            config >> fontPath >> fontSize >> fontColor.r >> fontColor.g >> fontColor.b;
            std::cout << "Font : " << fontPath << " : " << fontSize << " " << fontColor.r << std::endl;
        }

    }

    //creating window
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Game Window");
    window.setFramerateLimit(60);
    float radius = 50.0f;
    float centerX = (float)wWidth / 2 - (2 * radius);
    float centerY = (float)wHeight / 2 - (2 * radius);

    //creating shapes
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(getCenter(wWidth, wHeight, shape.getGlobalBounds().getSize()));
    //drawables.push_back(shape);

    sf::Font myFont;
    //attempt to load font
    if (!myFont.loadFromFile(fontPath)) {
        std::cout << "Error loading font" << std::endl;
        exit(-1);
    }
    //setup text
    sf::Text text("Text", myFont, fontSize);
    text.setPosition(getCenter(wWidth, wHeight, text.getGlobalBounds().getSize()));
    //drawables.push_back(text);
    //main game loop - 
    while (window.isOpen())
    {
        //event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                std::cout << "closed clicked" << std::endl;
                window.close();
            }
            //Input events
            if (event.type == sf::Event::KeyPressed) {
                //std::cout << "key pressed : " << event.key.code << std::endl;

                if (event.key.code == sf::Keyboard::Space) {
                    //std::cout << "key pressed : " << event.key.code << std::endl;
                    text.setString("key pressed : SPACE");
                }
            }
        }
        //animation
        shape.setPosition(shape.getPosition().x - 1, shape.getPosition().y - 1);
        window.clear();
        //for (size_t i; i < drawables.size(); i++) {
            //window.draw(drawables[i]);
        //}
        window.draw(shape);
        window.display();
    }
}


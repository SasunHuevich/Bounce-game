#include <SFML/Graphics.hpp>
#include "Constants.h"


double degreesToRadians(double degrees) {
    return degrees * 3.141592653589793 / 180.0;
}



float rotateX(float x, float y, float angle, float cx, float cy) {
    return (x - cx) * std::cos(angle) - (y - cy) * std::sin(angle) + cx;;
}


float rotateY(float x, float y, float angle, float cx, float cy) {
    return (x - cx) * std::sin(angle) + (y - cy) * std::cos(angle) + cy;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "BEST GAME EVER"); //создание окна

    float shapeWidth = 32.0; // Радиус шара
    const sf::Texture cirTexture("circle.png");

    sf::CircleShape shape(shapeWidth); 
    shape.setTexture(&cirTexture);
    

    // Walls
    std::vector<sf::RectangleShape> walls;
    
    sf::RectangleShape wall;

    wall.setSize(sf::Vector2f(64.0, 64.0));
    const sf::Texture wallTexture("text2.png");
    wall.setTexture(&wallTexture);


    std::string lvl1map[12] = {
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BB   BBBBBB          BBB        ",
        "BB   BBBBBB          BBB        ",
        "BB   BBBBBB   BB     BBB        ",
        "BB   BBBBBB   BB     BBB  BBBB  ",
        "BB            BB          BB    ",
        "BBP           BB          BB    ",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
    };
    
    for (int i = 0; i < sizeof(lvl1map) / sizeof(lvl1map[0]); i++) {
        for (int j = 0; j < lvl1map[i].size(); j++) {
            if (lvl1map[i][j] == 'B') {
                wall.setPosition(sf::Vector2f(j * 64.0, 256.0 + i * 64.0));
                walls.push_back(wall);
            }
            else if (lvl1map[i][j] == 'P') {
                shape.setPosition(sf::Vector2f(j * 64.0, 256.0 + i * 64.0));
            }
        }
    }

    shape.setOrigin({ shapeWidth, shapeWidth});
    sf::FloatRect shapeBounds1 = wall.getGlobalBounds();
    sf::RectangleShape aabbRect(sf::Vector2f(shapeBounds1.size.x, shapeBounds1.size.y));
    aabbRect.setPosition({ shapeBounds1.position.x, shapeBounds1.position.y });
    aabbRect.setFillColor(sf::Color::Transparent);
    aabbRect.setOutlineColor(sf::Color::Green);
    aabbRect.setOutlineThickness(2);

    sf::RectangleShape wall1;
    wall1.setFillColor(sf::Color::Red);
    wall1.setSize(sf::Vector2f(250.0, 250.0));
    wall1.setPosition(sf::Vector2f(400.0, 450.0));


    sf::FloatRect nextPos;

    const sf::Font font("arialmt.ttf");

    // Create a text
    sf::Text text(font, "hello");
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);

    

    sf::Text text2(font, "hello");
    text2.setCharacterSize(30);
    text2.setStyle(sf::Text::Bold);
    text2.setFillColor(sf::Color::Red);
    text2.setPosition(sf::Vector2f(0.0, 30.0));

    sf::Text text3(font, "hello");
    text3.setCharacterSize(30);
    text3.setStyle(sf::Text::Bold);
    text3.setFillColor(sf::Color::Red);
    text3.setPosition(sf::Vector2f(0.0, 60.0));

    sf::Text text4(font, "hello");
    text4.setCharacterSize(30);
    text4.setStyle(sf::Text::Bold);
    text4.setFillColor(sf::Color::Red);
    text4.setPosition(sf::Vector2f(0.0, 90.0));

    sf::Text text5(font, "hello");
    text5.setCharacterSize(30);
    text5.setStyle(sf::Text::Bold);
    text5.setFillColor(sf::Color::Red);
    text5.setPosition(sf::Vector2f(0.0, 120.0));

    sf::Text text6(font, "hello");
    text6.setCharacterSize(30);
    text6.setStyle(sf::Text::Bold);
    text6.setFillColor(sf::Color::Red);
    text6.setPosition(sf::Vector2f(0.0, 150.0));

    sf::Text text7(font, "hello");
    text7.setCharacterSize(30);
    text7.setStyle(sf::Text::Bold);
    text7.setFillColor(sf::Color::Red);
    text7.setPosition(sf::Vector2f(0.0, 180.0));

    sf::Text text8(font, "hello");
    text8.setCharacterSize(30);
    text8.setStyle(sf::Text::Bold);
    text8.setFillColor(sf::Color::Red);
    text8.setPosition(sf::Vector2f(0.0, 210.0));

    float speed = 0.0007; // пикселей в секунду
    float velocityY = 0;
    float gravity = 0.000035;
    float jumpSpeed = 0.00090;
    bool canJump = true;

    //window.setFramerateLimit(60);

    sf::Clock clockJump;
    
    sf::Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////

        sf::Vector2f movement(0, 0);
        sf::Angle rotation = sf::degrees(0);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            movement.x -= speed;
            rotation -= sf::degrees(0.09);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && canJump == true) {
            //movement.y = jumpSpeed;
            canJump = false;
            clockJump.restart();
            velocityY = jumpSpeed;
        }
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            movement.y += speed;
        }*/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            movement.x += speed;
            rotation += sf::degrees(0.09);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
            movement.x *= 2;
            movement.y *= 2;
        }

        
        if (true) {
            float timeJump = clockJump.getElapsedTime().asMicroseconds() / 10;
            //velocityY = velocityY * timeJump - gravity*1000 * timeJump * timeJump / 2;
            velocityY = velocityY - gravity * timeJump/31000;
            movement.y -= velocityY;
            canJump = false;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Collision 
        for (auto &i : walls) {
            sf::FloatRect shapeBounds = shape.getGlobalBounds();
            sf::FloatRect wallBounds = i.getGlobalBounds();

            nextPos = shapeBounds;
            float nextPosX = (shape.getPosition().x) + movement.x * 1000;
            float nextPosY = (shape.getPosition().y) + movement.y * 1000;




            // Координаты точек блока стены
            float t1x = rotateX(i.getPosition().x, i.getPosition().y, i.getRotation().asRadians(), i.getPosition().x, i.getPosition().y);
            float t1y = rotateY(i.getPosition().x, i.getPosition().y, i.getRotation().asRadians(), i.getPosition().x, i.getPosition().y);

            float t2x = rotateX((i.getPosition().x + i.getSize().x), i.getPosition().y, i.getRotation().asRadians(), i.getPosition().x, i.getPosition().y);
            float t2y = rotateY(i.getPosition().x + i.getSize().x, i.getPosition().y, i.getRotation().asRadians(), i.getPosition().x, i.getPosition().y);

            float t3x = rotateX(i.getPosition().x + i.getSize().x, i.getPosition().y + i.getSize().y, i.getRotation().asRadians(), i.getPosition().x, i.getPosition().y);
            float t3y = rotateY(i.getPosition().x + i.getSize().x, i.getPosition().y + i.getSize().y, i.getRotation().asRadians(), i.getPosition().x, i.getPosition().y);

            float t4x = rotateX(i.getPosition().x, i.getPosition().y + i.getSize().y, i.getRotation().asRadians(), i.getPosition().x, i.getPosition().y);
            float t4y = rotateY(i.getPosition().x, i.getPosition().y + i.getSize().y, i.getRotation().asRadians(), i.getPosition().x, i.getPosition().y);


            // Расстояние от будущего центра шарика до каждой из сторон
            float d1_2 = (std::abs((t2x - t1x) * (t1y - nextPosY) - (t2y - t1y) * (t1x - nextPosX))) / std::sqrt(std::pow((t2x - t1x), 2) + std::pow((t2y - t1y), 2));
            float d2_3 = (std::abs((t3x - t2x) * (t2y - nextPosY) - (t3y - t2y) * (t2x - nextPosX))) / std::sqrt(std::pow((t3x - t2x), 2) + std::pow((t3y - t2y), 2));
            float d3_4 = (std::abs((t4x - t3x) * (t3y - nextPosY) - (t4y - t3y) * (t3x - nextPosX))) / std::sqrt(std::pow((t4x - t3x), 2) + std::pow((t4y - t3y), 2));
            float d4_1 = (std::abs((t1x - t4x) * (t4y - nextPosY) - (t1y - t4y) * (t4x - nextPosX))) / std::sqrt(std::pow((t1x - t4x), 2) + std::pow((t1y - t4y), 2));

            // Проекции будущего центра на стороны
            float p1_2 = ((nextPosX - t1x) * (t2x - t1x) + (nextPosY - t1y) * (t2y - t1y)) / (std::pow((t2x - t1x), 2) + std::pow((t2y - t1y), 2));
            float p2_3 = ((nextPosX - t2x) * (t3x - t2x) + (nextPosY - t2y) * (t3y - t2y)) / (std::pow((t3x - t2x), 2) + std::pow((t3y - t2y), 2));
            float p3_4 = ((nextPosX - t3x) * (t4x - t3x) + (nextPosY - t3y) * (t4y - t3y)) / (std::pow((t4x - t3x), 2) + std::pow((t4y - t3y), 2));
            float p4_1 = ((nextPosX - t4x) * (t1x - t4x) + (nextPosY - t4y) * (t1y - t4y)) / (std::pow((t1x - t4x), 2) + std::pow((t1y - t4y), 2));

            // Смещение проекций на радиус шара
            float deltaP1_2 = shapeWidth / std::sqrt(std::pow((t2x - t1x), 2) + std::pow((t2y - t1y), 2));
            float deltaP2_3 = shapeWidth / std::sqrt(std::pow((t3x - t2x), 2) + std::pow((t3y - t2y), 2));
            float deltaP3_4 = shapeWidth / std::sqrt(std::pow((t4x - t3x), 2) + std::pow((t4y - t3y), 2));
            float deltaP4_1 = shapeWidth / std::sqrt(std::pow((t1x - t4x), 2) + std::pow((t1y - t4y), 2));

            
            // Коллизия
            if (std::min({ d1_2, d2_3, d3_4, d4_1 }) < shapeWidth) {


                // Коллизия с углами
                if (std::sqrt(std::pow((nextPosX - t1x), 2) + std::pow((nextPosY - t1y), 2)) < shapeWidth) {

                    shape.setPosition(sf::Vector2f((t1x + shapeWidth * (-t1x + nextPosX) / std::sqrt(std::pow((nextPosX - t1x), 2) + std::pow((nextPosY - t1y), 2))), t1y + shapeWidth * (-t1y + nextPosY) / std::sqrt(std::pow((nextPosX - t1x), 2) + std::pow((nextPosY - t1y), 2))));
                    text5.setString("sssssssssssssssssssssss");
                }
                else if (std::sqrt(std::pow((nextPosX - t2x), 2) + std::pow((nextPosY - t2y), 2)) < shapeWidth) {

                    shape.setPosition(sf::Vector2f((t2x + shapeWidth * (-t2x + nextPosX) / std::sqrt(std::pow((nextPosX - t2x), 2) + std::pow((nextPosY - t2y), 2))), t2y + shapeWidth * (-t2y + nextPosY) / std::sqrt(std::pow((nextPosX - t2x), 2) + std::pow((nextPosY - t2y), 2))));
                    text5.setString("sssssssssssssssssssssss");
                }
                else if (std::sqrt(std::pow((nextPosX - t3x), 2) + std::pow((nextPosY - t3y), 2)) < shapeWidth) {

                    shape.setPosition(sf::Vector2f((t3x + shapeWidth * (-t3x + nextPosX) / std::sqrt(std::pow((nextPosX - t3x), 2) + std::pow((nextPosY - t3y), 2))), t3y + shapeWidth * (-t3y + nextPosY) / std::sqrt(std::pow((nextPosX - t3x), 2) + std::pow((nextPosY - t3y), 2))));

                    text5.setString("sssssssssssssssssssssss");
                }
                else if (std::sqrt(std::pow((nextPosX - t4x), 2) + std::pow((nextPosY - t4y), 2)) < shapeWidth) {

                    shape.setPosition(sf::Vector2f((t4x + shapeWidth * (-t4x + nextPosX) / std::sqrt(std::pow((nextPosX - t4x), 2) + std::pow((nextPosY - t4y), 2))), t4y + shapeWidth * (-t4y + nextPosY) / std::sqrt(std::pow((nextPosX - t4x), 2) + std::pow((nextPosY - t4y), 2))));

                    text5.setString("sssssssssssssssssssssss");
                }


                // Коллизия со стенами
                if (d1_2 <= shapeWidth && p1_2 >= 0 && p1_2 <= 1) {
                    text5.setString("1_2 " + std::to_string(p1_2));
                    canJump = true;
                    movement.y = 0;
                    velocityY = 0;
                    clockJump.restart();
                    shape.setPosition(sf::Vector2f(shape.getPosition().x, i.getPosition().y - shapeWidth));
                }
                else if (d2_3 <= shapeWidth && p2_3 >= 0 && p2_3 <= 1) {
                    text5.setString("2_3 " + std::to_string(p2_3));
                    movement.x = 0;
                    shape.setPosition(sf::Vector2f(i.getPosition().x + i.getSize().x + shapeWidth, shape.getPosition().y));
                }
                else if (d3_4 <= shapeWidth && p3_4 >= 0 && p3_4 <= 1) {
                    text5.setString("3_4 " + std::to_string(p3_4));
                    shape.setPosition(sf::Vector2f(shape.getPosition().x, i.getPosition().y + i.getSize().y + shapeWidth));
                    movement.y = 0;
                    velocityY = 0;
                }
                else if (d4_1 <= shapeWidth && p4_1 >= 0 && p4_1 <= 1) {
                    text5.setString("4_1 " + std::to_string(p4_1));
                    movement.x = 0;
                    shape.setPosition(sf::Vector2f(i.getPosition().x - shapeWidth, shape.getPosition().y));
                    
                }

                
            }
            else {
                text5.setString("no");
            }
            
            


            //text5.setString("400 450 " + std::to_string(t1x) + " " + std::to_string(t1y));
            text6.setString("650 450 " + std::to_string(t2x) + " " + std::to_string(t2y));
            text7.setString("650 700 " + std::to_string(t3x) + " " + std::to_string(t3y));
            text8.setString("400 700 " + std::to_string(t4x) + " " + std::to_string(t4y));
            
            
            text.setString(std::to_string(d1_2));
            text2.setString(std::to_string(d2_3));
            text3.setString(std::to_string(d3_4));
            text4.setString(std::to_string(d4_1));
            
        }



        /////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////

        shape.move({ movement.x * time,movement.y * time }); // перемещение
        shape.rotate(rotation);

        window.clear(sf::Color(94, 242, 255));

        for (auto& i : walls) {
            window.draw(i);
        }
        window.draw(text);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
        window.draw(text6);
        window.draw(text7);
        window.draw(text8);
        //window.draw(aabbRect);
        window.draw(shape);
        //window.draw(wall1);
        //window.draw(line);
        window.display();
    }
}

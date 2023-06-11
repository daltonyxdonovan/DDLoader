#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <functional>
#include <Windows.h>
#include <atlstr.h>
#include <locale>
#include <codecvt>
#pragma comment(lib, "Shlwapi.lib")

#include <shlwapi.h>

using namespace std;

class MainDisplay
{
private:
	string DISPLAY_NAME = "havendock";
public:
	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Text text;
	sf::Text bepinex_version;
	sf::Font font;
	sf::Sprite sprite;
	sf::RectangleShape divider1;
	sf::RectangleShape divider2;
	sf::Vector2f text_position;
	int bep_version;
	int function_last_used;

	MainDisplay(string name, int bep_version, sf::Vector2f position, sf::Vector2f size, sf::Texture texture)
		: text("<game_name>", font, 30), bepinex_version("BEPINEX 6", font, 10)
	{
		this->shape.setSize(size);
		this->shape.setFillColor(sf::Color(40, 40, 40, 255));
		this->shape.setOrigin(size.x / 2, size.y / 2);
		this->shape.setPosition(position);
		this->divider1.setSize(sf::Vector2f(25, size.y + 40));
		this->divider1.setFillColor(sf::Color(50, 50, 50, 255));
		this->divider1.setOrigin(1.5, (size.y + 20) / 2);
		this->divider1.setPosition(position.x - 100, position.y);
		this->font.loadFromFile("resources/RobotoMono-Light.ttf");
		this->text.setFont(font);
		this->text.setString("noodles");
		this->text.setCharacterSize(30);
		this->text.setStyle(sf::Text::Bold);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		this->text_position = sf::Vector2f((shape.getPosition().x - 363), shape.getPosition().y);
		this->text.setPosition(sf::Vector2f(text_position.x - text.getGlobalBounds().width / 2, text_position.y));
		this->bepinex_version.setFont(font);
		this->bepinex_version.setString("BEPINEX " + to_string(bep_version));
		this->bepinex_version.setCharacterSize(15);
		this->bepinex_version.setFillColor(sf::Color(255, 255, 255, 255));
		this->bepinex_version.setPosition(shape.getPosition().x, shape.getPosition().y + (shape.getSize().y / 2 - 50));
		this->texture = texture;
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
		this->sprite.setPosition(this->shape.getPosition().x, this->shape.getPosition().y - 50);
		this->bep_version = 6;
		this->function_last_used = 0;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(this->shape);
		//If text exists
		window.draw(this->text);
		window.draw(this->bepinex_version);
		window.draw(this->sprite);
		window.draw(this->divider1);
	}

	string toupper(string text)
	{
		vector<char> chars(text.begin(), text.end());
		for (int i = 0; i < chars.size(); i++)
		{
			chars[i] = std::toupper(chars[i]);
		}
		text = string(chars.begin(), chars.end());
		return text;
	}

	void setName(std::string given_name) {
		this->DISPLAY_NAME = given_name;
	}
	std::string getName() const {
		return DISPLAY_NAME;
	}


	void Log(string message)
	{
		std::cout << message + "::" << endl;
		std::wstring wide_message(message.begin(), message.end());
		LPCWSTR long_message = wide_message.c_str();
		OutputDebugString(long_message);
	}

	void update(string name)
	{
		//Log(DISPLAY_NAME);
		this->text.setString(toupper(DISPLAY_NAME));
		this->bepinex_version.setString("BEPINEX " + to_string(this->bep_version));
		this->text.setPosition(sf::Vector2f(this->text_position.x - this->text.getGlobalBounds().width / 2, this->text_position.y + 5));
		this->bepinex_version.setPosition(sf::Vector2f(this->text_position.x - this->bepinex_version.getGlobalBounds().width / 2, this->text_position.y + 45));
		this->sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		this->sprite.setPosition(sf::Vector2f(text_position.x, text_position.y - 175));
		//this->texture = texture;
	}


};

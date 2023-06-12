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
#include <filesystem>
#pragma comment(lib, "Shlwapi.lib")

#include <shlwapi.h>

using namespace std;

class Mod
{
	string name;
	bool enabled;
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;
	sf::Vector2f position;
	int y_offset;

	Mod()
	{
		this->name = "mod";
		this->enabled = false;
		this->shape.setSize(sf::Vector2f(600, 50));
		this->shape.setFillColor(sf::Color(40, 40, 40, 255));
		this->shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
		this->shape.setPosition(position);
		this->font.loadFromFile("resources/RobotoMono-Light.ttf");
		this->text.setFont(font);
		this->text.setString(name);
		this->text.setCharacterSize(30);
		this->text.setStyle(sf::Text::Bold);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		this->text.setPosition(sf::Vector2f(position.x - text.getGlobalBounds().width / 2, position.y));
		this->y_offset = 0;
	}

};

class Filescanner
{
public:
	string path;
	string path2;
	string path3;
	string path4;
	string path5;

	string game_id;
	int scroll_y;
	sf::Vector2f position;
	sf::Vector2f size;
	bool refresh;

	sf::RectangleShape border;
	vector<Mod> mods;

	Filescanner()
	{


		this->path = "C:/Program Files (x86)/Steam/steamapps/common/Havendock";
		this->path2 = "D:/SteamLibrary/steamapps/common/Havendock";
		this->path3 = "E:/SteamLibrary/steamapps/common/Havendock";
		this->path4 = "F:/SteamLibrary/steamapps/common/Havendock";
		this->path5 = "G:/SteamLibrary/steamapps/common/Havendock";

		this->game_id = "havendock";
		this->scroll_y = 0;
		this->position = sf::Vector2f(1225, 435);
		this->size = sf::Vector2f(685, 660);
		this->refresh = true;
		this->border = sf::RectangleShape(size);
		this->border.setFillColor(sf::Color(20, 20, 20, 255));
		this->border.setOrigin(size.x / 2, size.y / 2);
		this->border.setPosition(position);




	};

	bool is_bep_installed(string directory)
	{
		//if there is a folder named bepinex in the directory, return true.
		//else return false.
		if (filesystem::exists(directory + "/BepInEx"))
		{
			return true;
		}
		else
		{
			return false;
		}


	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(border);

		int filepath_needed = 0;
		int amount_of_mods = 0;

		if (is_bep_installed(path))
			filepath_needed = 0;
		if (is_bep_installed(path2))
			filepath_needed = 1;
		if (is_bep_installed(path3))
			filepath_needed = 2;
		if (is_bep_installed(path4))
			filepath_needed = 3;
		if (is_bep_installed(path5))
			filepath_needed = 4;

		if (refresh)
		{
			//count how many files there are in path + /BepInEx/plugins
			//then set amount_of_mods to that number.

			if (filepath_needed == 0)
			{
				for (const auto& entry : filesystem::directory_iterator(path + "/BepInEx/plugins"))
				{
					amount_of_mods++;
				}
			}
			if (filepath_needed == 1)
			{
				for (const auto& entry : filesystem::directory_iterator(path2 + "/BepInEx/plugins"))
				{
					amount_of_mods++;
				}
			}
			if (filepath_needed == 2)
			{
				for (const auto& entry : filesystem::directory_iterator(path3 + "/BepInEx/plugins"))
				{
					amount_of_mods++;
				}
			}
			if (filepath_needed == 3)
			{
				for (const auto& entry : filesystem::directory_iterator(path4 + "/BepInEx/plugins"))
				{
					amount_of_mods++;
				}
			}
			if (filepath_needed == 4)
			{
				for (const auto& entry : filesystem::directory_iterator(path5 + "/BepInEx/plugins"))
				{
					amount_of_mods++;
				}
			}

			for (int i = 0; i < amount_of_mods; i++)
			{
				//draw a rectangle for each mod, and place them starting top to bottom.

			}
		}
	}

	void update()
	{

	}

};


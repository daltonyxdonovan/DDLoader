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

	void draw(sf::RenderWindow& window)
	{
		window.draw(border);
	}

	void update()
	{

	}

};


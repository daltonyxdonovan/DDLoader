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

	Filescanner()
	{
		this->path = "C:/Program Files (x86)/Steam/steamapps/common/Havendock";
		this->path2 = "D:/SteamLibrary/steamapps/common/Havendock";
		this->path3 = "C:/Program Files/Steam/steamapps/common/Havendock";
		this->path4 = "C:/Program Files (x86)/Steam/steamapps/common/Havendock";
		this->path5 = "C:/Program Files (x86)/Steam/steamapps/common/Havendock";
	}

};


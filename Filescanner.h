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
#include "Button.h"
#pragma comment(lib, "Shlwapi.lib")

#include <shlwapi.h>

using namespace std;

class Mod
{
public:
	string name;
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;
	sf::Vector2f position;
	int y_offset;
	bool enabled;
	sf::Texture texture_yes;
	sf::Texture texture_no;
	sf::Sprite sprite;
	//reference to the actual mod file
	//this is used to check if the mod is disabled or not
	string mod_file_full_address;

	Mod(string name, sf::Font& font,string address):
		shape(sf::Vector2f(665, 50)),
		text(name, font, 16)

	{
		this->mod_file_full_address = address;
		this->name = name;
		this->shape.setSize(sf::Vector2f(665, 50));
		this->shape.setFillColor(sf::Color(40, 40, 40, 255));
		this->shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
		this->shape.setPosition(position);
		this->font = font;
		this->text.setFont(font);
		this->text.setString(name);
		this->text.setCharacterSize(16);
		this->text.setOrigin(0, text.getGlobalBounds().height / 2);
		this->text.setStyle(sf::Text::Bold);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		this->text.setPosition(sf::Vector2f(position.x, position.y));
		this->y_offset = 0;
		this->enabled = true;
		this->texture_yes.loadFromFile("resources/images/yes.png");
		this->texture_no.loadFromFile("resources/images/no.png");
		this->sprite.setTexture(texture_yes);
		this->sprite.setOrigin(texture_yes.getSize().x / 2, texture_yes.getSize().y / 2);
		this->sprite.setPosition(sf::Vector2f(position.x + 300, position.y));

		

	}

	bool is_disabled(string filename)
	{
		//if filename ends in '.ddloader', return true.
		//else return false.
		if (filename.substr(filename.length() - 9, filename.length()) == ".ddloader")
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void disable(string filename)
	{
		//rename filename to filename.ddloader ONLY IF it does not end in .ddloader
		if (filename.substr(filename.length() - 9, filename.length()) != ".ddloader")
		{
			rename(filename.c_str(), (filename + ".ddloader").c_str());
		}
	}

	void Log(string message)
	{
		std::cout << message + "::" << endl;
		std::wstring wide_message(message.begin(), message.end());
		LPCWSTR long_message = wide_message.c_str();
		OutputDebugString(long_message);
	}


	void enable(string filename)
	{
		//rename filename.ddloader to filename ONLY IF it ends in .ddloader
		if (filename.substr(filename.length() - 9, filename.length()) == ".ddloader")
		{
			rename(filename.c_str(), filename.substr(0, filename.length() - 9).c_str());
		}

	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
		window.draw(text);
		//update();
		window.draw(sprite);
	}

	void update()
	{
		this->text.setString(name);
		this->sprite.setPosition(sf::Vector2f(position.x + 305, position.y));
		//check if mod is enabled or disabled.
		if (is_disabled(name))
		{
			enabled = false;
		}
		else
		{
			enabled = true;
		}

		//if sprite is clicked, toggle enabled.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
			{
				if (enabled)
				{
					enabled = false;
					Log("Disabling mod: " + this->mod_file_full_address);
					disable(this->mod_file_full_address);
				}
				else
				{
					enabled = true;
					Log("Enabling mod: " + this->mod_file_full_address);
					enable(this->mod_file_full_address);
				}
			}
		}

		if (enabled)
		{
			this->sprite.setTexture(texture_yes);
		}
		else
		{
			this->sprite.setTexture(texture_no);
		}

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
	sf::Font font;
	int remembered_mods;
	bool running;
	sf::RectangleShape border;
	vector<Mod> mods{};

	Filescanner(sf::Font& font)
	{
		this->remembered_mods = 0;
		this->font = font;
		this->path = "C:/Program Files (x86)/Steam/steamapps/common/Havendock";
		this->path2 = "D:/SteamLibrary/steamapps/common/Havendock";
		this->path3 = "E:/SteamLibrary/steamapps/common/Havendock";
		this->path4 = "F:/SteamLibrary/steamapps/common/Havendock";
		this->path5 = "G:/SteamLibrary/steamapps/common/Havendock";
		this->running = false;
		this->game_id = "havendock";
		this->scroll_y = 0;
		this->position = sf::Vector2f(1225, 435);
		this->size = sf::Vector2f(685, 660);
		this->refresh = true;
		this->border = sf::RectangleShape(size);
		this->border.setFillColor(sf::Color(20, 20, 20, 255));
		this->border.setOrigin(size.x / 2, size.y / 2);
		this->border.setPosition(position);
		this->mods = vector<Mod>{};



	};

	bool is_disabled(string filename)
	{
		//if filename ends in '.ddloader', return true.
		//else return false.
		if (filename.substr(filename.length() - 9, filename.length()) == ".ddloader")
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void disable(string filename)
	{
		//rename filename to filename.ddloader ONLY IF it does not end in .ddloader
		if (filename.substr(filename.length() - 9, filename.length()) != ".ddloader")
		{
			rename(filename.c_str(), (filename + ".ddloader").c_str());
		}
	}

	void enable(string filename)
	{
		//rename filename.ddloader to filename ONLY IF it ends in .ddloader
		if (filename.substr(filename.length() - 9, filename.length()) == ".ddloader")
		{
			rename(filename.c_str(), filename.substr(0, filename.length() - 9).c_str());
		}
		
	}

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
		else if (is_bep_installed(path2))
			filepath_needed = 1;
		else if (is_bep_installed(path3))
			filepath_needed = 2;
		else if (is_bep_installed(path4))
			filepath_needed = 3;
		else if (is_bep_installed(path5))
			filepath_needed = 4;
		else
			return;

		if (refresh)
		{
			//count how many files there are in path + /BepInEx/plugins
			//then set amount_of_mods to that number.
			mods.clear();
			if (filepath_needed == 0)
			{
				
				for (const auto& entry : filesystem::directory_iterator(path + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;

						string file_full_address = entry.path().string();

						//add a mod to the vector.
						mods.push_back(Mod(entry.path().filename().string(), font, file_full_address));
					}
				}
			}
			if (filepath_needed == 1)
			{
				for (const auto& entry : filesystem::directory_iterator(path2 + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;
						string file_full_address = entry.path().string();

						//add a mod to the vector.
						mods.push_back(Mod(entry.path().filename().string(), font, file_full_address));
					}
				}
			}
			if (filepath_needed == 2)
			{
				for (const auto& entry : filesystem::directory_iterator(path3 + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;
						string file_full_address = entry.path().string();

						//add a mod to the vector.
						mods.push_back(Mod(entry.path().filename().string(), font, file_full_address));
					}
				}
			}
			if (filepath_needed == 3)
			{
				for (const auto& entry : filesystem::directory_iterator(path4 + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;
						string file_full_address = entry.path().string();

						//add a mod to the vector.
						mods.push_back(Mod(entry.path().filename().string(), font, file_full_address));
					}
				}
			}
			if (filepath_needed == 4)
			{
				for (const auto& entry : filesystem::directory_iterator(path5 + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;
						string file_full_address = entry.path().string();

						//add a mod to the vector.
						mods.push_back(Mod(entry.path().filename().string(), font, file_full_address));
					}
				}
			}

			for (int i = 0; i < mods.size(); i++)
			{
				////draw a rectangle for each mod, and place them starting top to bottom.
				mods[i].position = sf::Vector2f(position.x, (position.y-295) + (i * 60) + scroll_y);
				mods[i].shape.setPosition(mods[i].position);
				mods[i].text.setPosition(sf::Vector2f(mods[i].position.x - 310, mods[i].position.y));
			}

			// vvv this is a way for me to save on cpu, but really it's negligible rn
			refresh = false;
			this->remembered_mods = amount_of_mods;
			
		}

		if (!running)
		{	//sets inital amount of mods
			running = true;
		}
		else
		{	//counts mods without pushing to vector. shoulda just made a method but eh
			if (filepath_needed == 0)
			{

				for (const auto& entry : filesystem::directory_iterator(path + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;
						
					}
				}
			}
			if (filepath_needed == 1)
			{
				for (const auto& entry : filesystem::directory_iterator(path2 + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;
						
					}
				}
			}
			if (filepath_needed == 2)
			{
				for (const auto& entry : filesystem::directory_iterator(path3 + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;
						
					}
				}
			}
			if (filepath_needed == 3)
			{
				for (const auto& entry : filesystem::directory_iterator(path4 + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;
						
					}
				}
			}
			if (filepath_needed == 4)
			{
				for (const auto& entry : filesystem::directory_iterator(path5 + "/BepInEx/plugins"))
				{
					if (entry.path().filename().string() != "placeholder.txt")
					{
						amount_of_mods++;
						
					}
				}
			}

			if (this->remembered_mods != amount_of_mods)
			{
				refresh = true;
			}
		}


		for (int i = 0; i < mods.size(); i++)
		{
			mods[i].draw(window);
		}
	}

	void update()
	{
		for (int i = 0; i < mods.size(); i++)
		{
			mods[i].update();
		}
	}

};


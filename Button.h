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
#include "MainDisplay.h"

using namespace std;

class Button
{
public:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;
	sf::Color color;
	sf::Color hover_color;
	sf::Color click_color;
	sf::Color text_color;
	sf::Vector2f position;
	sf::Texture buttonTexture;
	string DISPLAY_NAME;
	int function_number;
	int bep_version;
	bool active;
	int ticker;


	//constructors
	//because of the funky way text font is being handled, I have to pass in the font as a parameter, so i just passed in evereything else too
	Button(string text, sf::Vector2f position, int function_number, int bep_version, sf::Vector2f size, int fontsize, bool active = true) :
		shape(sf::Vector2f(250, 50)),
		font{},
		text{ text,font,fontsize },
		color{ 30, 30, 30, 255 },
		hover_color{ 50, 50, 50, 255 },
		click_color{ 60, 60, 60, 255 },
		text_color{ 255, 255, 255, 255 },
		position(position)
	{
		this->ticker = 0;
		this->shape = sf::RectangleShape(size);
		this->shape.setFillColor(sf::Color(10, 10, 10, 255));
		this->shape.setOrigin(this->shape.getSize().x / 2, this->shape.getSize().y / 2);
		this->shape.setPosition(position);
		this->font.loadFromFile("resources/RobotoMono-Light.ttf");
		this->text.setFont(font);
		this->text.setString("no");
		this->text.setCharacterSize(fontsize);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		this->text.setPosition(this->shape.getPosition().x - (this->text.getGlobalBounds().width / 2), this->shape.getPosition().y - (this->text.getGlobalBounds().height / 2));
		this->color = sf::Color(30, 30, 30, 255);
		this->hover_color = sf::Color(50, 50, 50, 255);
		this->click_color = sf::Color(60, 60, 60, 255);
		this->text_color = sf::Color(255, 255, 255, 255);
		this->position = position;
		this->DISPLAY_NAME = text;
		this->function_number = function_number;
		this->bep_version = bep_version;
		this->active = true;

	}

	Button(string text, sf::Vector2f position, int function_number, int bep_version, bool active = true) :
		shape(sf::Vector2f(250, 50)),
		font{},
		text{ text,font,20 },
		color{ 30, 30, 30, 255 },
		hover_color{ 50, 50, 50, 255 },
		click_color{ 60, 60, 60, 255 },
		text_color{ 255, 255, 255, 255 },
		position(position)
	{
		this->ticker = 0;
		this->shape = sf::RectangleShape(sf::Vector2f(250, 50));
		this->shape.setFillColor(sf::Color(10, 10, 10, 255));
		this->shape.setOrigin(this->shape.getSize().x / 2, this->shape.getSize().y / 2);
		this->shape.setPosition(position);
		this->font.loadFromFile("resources/RobotoMono-Light.ttf");
		this->text.setFont(font);
		this->text.setString("no");
		this->text.setCharacterSize(20);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		this->text.setPosition(this->shape.getPosition().x - (this->text.getGlobalBounds().width / 2), this->shape.getPosition().y - (this->text.getGlobalBounds().height / 2));
		this->color = sf::Color(30, 30, 30, 255);
		this->hover_color = sf::Color(50, 50, 50, 255);
		this->click_color = sf::Color(60, 60, 60, 255);
		this->text_color = sf::Color(255, 255, 255, 255);
		this->position = position;
		this->DISPLAY_NAME = text;
		this->function_number = function_number;
		this->bep_version = bep_version;
		this->active = true;
	}

	Button(sf::Texture& image, sf::Vector2f position, int function_number, bool active = false) :
		shape(sf::Vector2f(image.getSize().x, image.getSize().y)),
		font{},
		text{ "",font,20 },
		color{ 30, 30, 30, 255 },
		hover_color{ 50, 50, 50, 255 },
		click_color{ 60, 60, 60, 255 },
		text_color{ 255, 255, 255, 255 },
		position(position)
	{
		this->ticker = 0;
		this->shape = sf::RectangleShape(sf::Vector2f(image.getSize().x, image.getSize().y));
		this->buttonTexture = image;
		this->shape.setTexture(&this->buttonTexture);
		this->shape.setOrigin(this->shape.getSize().x / 2, this->shape.getSize().y / 2);
		this->shape.setPosition(position);
		this->font.loadFromFile("resources/RobotoMono-Light.ttf");
		this->text.setFont(font);
		this->text.setString("");
		this->text.setCharacterSize(20);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		this->text.setPosition(this->shape.getPosition().x - (this->text.getGlobalBounds().width / 2), this->shape.getPosition().y - (this->text.getGlobalBounds().height / 2));
		this->color = sf::Color(255, 255, 255, 255);
		this->hover_color = sf::Color(255, 255, 255, 230);
		this->click_color = sf::Color(255, 255, 255, 200);
		this->text_color = sf::Color(255, 255, 255, 255);
		this->position = position;
		this->DISPLAY_NAME = "";
		this->function_number = function_number;
		this->bep_version = bep_version;
		this->active = true;
	}
	
	//default constructor
	Button():
		shape(sf::Vector2f(40,40)),
		font{},
		text{ "",font,20 },
		color{ 30, 30, 30, 255 },
		hover_color{ 50, 50, 50, 255 },
		click_color{ 60, 60, 60, 255 },
		text_color{ 255, 255, 255, 255 },
		position(position),
		active(false)
	{
		this->active = false;
		this->ticker = 0;
		this->shape = sf::RectangleShape(sf::Vector2f(250, 50));
		this->shape.setFillColor(sf::Color(10, 10, 10, 255));
		this->shape.setOrigin(this->shape.getSize().x / 2, this->shape.getSize().y / 2);
		this->shape.setPosition(sf::Vector2f(0.f, 0.f));
		this->font.loadFromFile("resources/RobotoMono-Light.ttf");
		this->text.setFont(font);
		this->text.setString("");
		this->text.setCharacterSize(20);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		this->text.setPosition(this->shape.getPosition().x - (this->text.getGlobalBounds().width / 2), this->shape.getPosition().y - (this->text.getGlobalBounds().height / 2));
		this->color = sf::Color(30, 30, 30, 255);
		this->hover_color = sf::Color(50, 50, 50, 255);
		this->click_color = sf::Color(60, 60, 60, 255);
		this->text_color = sf::Color(255, 255, 255, 255);
		this->position = sf::Vector2f(0.f, 0.f);
		this->DISPLAY_NAME = "no";
		this->function_number = -12;
		this->bep_version = 6;

	}

	void setPosition(sf::Vector2f position)
	{
		this->position = position;
	}
	
	//methods
	void draw(sf::RenderWindow& window)
	{
		window.draw(this->shape);
		if (this->active != false && text.getString() != "" && text.getString() != "no")
			window.draw(this->text);
	}

	void Log(string message)
	{
		std::cout << message + "::" << endl;
		std::wstring wide_message(message.begin(), message.end());
		LPCWSTR long_message = wide_message.c_str();
		OutputDebugString(long_message);
	}

	void open_directory_in_explorer(string directory)
	{
		wchar_t* wstr = new wchar_t[MAX_PATH];
		MultiByteToWideChar(CP_UTF8, 0, directory.c_str(), -1, wstr, MAX_PATH);
		ShellExecute(NULL, L"open", wstr, NULL, NULL, SW_SHOWNORMAL);
		delete[] wstr;
	}

	void run_command(string command)
	{
		string data;
		FILE* stream;
		const int max_buffer = 256;
		char buffer[max_buffer];
		command.append(" 2>&1");

#ifdef _WIN32
		stream = _popen(command.c_str(), "r");
#else
		stream = popen(command.c_str(), "r");
#endif

		if (stream)
		{
			while (!feof(stream))
				if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
#ifdef _WIN32
			_pclose(stream);
#else
			pclose(stream);
#endif
		}

		std::cout << data << endl;
		return;
	}

	bool is_dll_installed(string dll, string directory)
	{
		string path = directory + "\\" + dll + ".dll";
		ifstream file(path);
		return file.good();
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

	void open_filepicker_and_install_zip(string directory, int function_last_used)
	{
		string fname;
		wchar_t filename[MAX_PATH];
		OPENFILENAMEW ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = TEXT("ZIP Files (*.zip)\0*.zip\0All Files (*.*)\0*.*\0");
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = L"Select a CSV file";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

		// show the file picker dialog
		if (GetOpenFileName(&ofn) == TRUE) {
			string command;
			if (GetOpenFileNameW(&ofn))
			{
				//if directory 
				fname = CW2A(filename);
				//install fname to directory
				command = "python resources/scripts/copyzip.py " + fname + " " + directory + " Hollow";
				run_command(command);
			}
		}
	}


	//holy crap I will never use switch statements again i hate this mess
	//used to think they were clean, but not only is this an unmanageable mess, i ALSO don't know what anything IS, because it's all numbers
	void update(sf::RenderWindow& window, MainDisplay& mainDisplay,bool& installer)
	{
		if (ticker > 0)
		{
			ticker--;
		}
		if (ticker < 0)
		{
			ticker = 0;
		}
		sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
		//if mouse is over button
		if (mouse_pos.x > this->shape.getPosition().x - (this->shape.getSize().x / 2) && mouse_pos.x < this->shape.getPosition().x + (this->shape.getSize().x / 2) && mouse_pos.y > this->shape.getPosition().y - (this->shape.getSize().y / 2) && mouse_pos.y < this->shape.getPosition().y + (this->shape.getSize().y / 2))
		{
			this->shape.setFillColor(this->hover_color);
			this->text.setFillColor(this->text_color);
			//if mouse is clicked
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (ticker != 0)
				{
					return;
				}
				ticker = 20;
				this->shape.setFillColor(this->click_color);
				string command = "";
				switch (function_number)
				{	///////////////////////////////////////////////////////////////////////////////////////////////////
					//				 the general idea here is that <0 is a function and >=0 is a game page
					///////////////////////////////////////////////////////////////////////////////////////////////////
					
				case(-11): //set to modscanner mode
					{
						installer = false;
						
					}
					break;
				case(-10): //set to installer mode
					{
						installer = true;
					}
					break;
				case(-9): // open unity explorer github
					{
						command = "start https://github.com/sinai-dev/UnityExplorer/blob/master/README.md";
						run_command(command);
					}
					break;
				case(-8): //open console commands github
					switch (mainDisplay.function_last_used)
					{
					case(0):
						command = "start https://github.com/daltonyxdonovan/Havendock_ConsoleCommands/tree/master/README.md";
						run_command(command);
						break;
					case(1):
						command = "start https://github.com/daltonyxdonovan/Muck_ConsoleCommands/blob/master/README.md";
						run_command(command);
						break;
					case(2):
						command = "start https://github.com/daltonyxdonovan/HollowKnight_ConsoleCommands/blob/master/README.md";
						run_command(command);
						break;
					case(3):
						command = "start https://github.com/daltonyxdonovan/RegionsOfRuin_ConsoleCommands/blob/main/README.md";
						run_command(command);
						break;
					}
					break;
				case(-7): // broken rn
					switch (mainDisplay.function_last_used)
					{
					case(3):
						if (is_bep_installed("C:/Program Files(x86)/Steam/steamapps/common/Hollow Knight"))
							open_filepicker_and_install_zip("C:/Program Files(x86)/Steam/steamapps/common/Hollow Knight", mainDisplay.function_last_used);
						break;
					}
					break;
				case(-6): //opens mods folder for respective game
					switch (mainDisplay.function_last_used)
					{
					case(0):
						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Havendock"))
							open_directory_in_explorer("C:/PROGRA~2/Steam/steamapps/common/Havendock/BepInEx/plugins");
						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Havendock"))
							open_directory_in_explorer("D:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins");
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Havendock"))
							open_directory_in_explorer("E:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins");
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Havendock"))
							open_directory_in_explorer("F:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins");
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Havendock"))
							open_directory_in_explorer("G:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins");

						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Havendock Demo"))
							open_directory_in_explorer("C:/PROGRA~2/Steam/steamapps/common/Havendock Demo/BepInEx/plugins");
						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Havendock Demo"))
							open_directory_in_explorer("D:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins");
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Havendock Demo"))
							open_directory_in_explorer("E:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins");
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Havendock Demo"))
							open_directory_in_explorer("F:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins");
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Havendock Demo"))
							open_directory_in_explorer("G:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins");
						break;
					case(1):
						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Muck"))
							open_directory_in_explorer("C:/PROGRA~2/Steam/steamapps/common/Muck/BepInEx/plugins");
						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Muck"))
							open_directory_in_explorer("D:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins");
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Muck"))
							open_directory_in_explorer("E:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins");
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Muck"))
							open_directory_in_explorer("F:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins");
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Muck"))
							open_directory_in_explorer("G:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins");
						break;
					case(2):
						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Hollow Knight"))
							open_directory_in_explorer("C:/PROGRA~2/Steam/steamapps/common/Hollow Knight/BepInEx/plugins");
						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Hollow Knight"))
							open_directory_in_explorer("D:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins");
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Hollow Knight"))
							open_directory_in_explorer("E:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins");
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Hollow Knight"))
							open_directory_in_explorer("F:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins");
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Hollow Knight"))
							open_directory_in_explorer("G:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins");
						break;
					case(3):
						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Regions Of Ruin"))
							open_directory_in_explorer("C:/PROGRA~2/Steam/steamapps/common/Regions Of Ruin/BepInEx/plugins");

						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Regions Of Ruin"))
							open_directory_in_explorer("D:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins");
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Regions Of Ruin"))
							open_directory_in_explorer("E:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins");
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Regions Of Ruin"))
							open_directory_in_explorer("F:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins");
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Regions Of Ruin"))
							open_directory_in_explorer("G:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins");
						break;
					}
				case(-4): //installs Unityexplorer
					{
						switch (mainDisplay.function_last_used)
						{
						case(0):
							if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Havendock"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip -C Havendock";
							if (is_bep_installed("D:/SteamLibrary/steamapps/common/Havendock"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip D:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins";
							if (is_bep_installed("E:/SteamLibrary/steamapps/common/Havendock"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip E:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins";
							if (is_bep_installed("F:/SteamLibrary/steamapps/common/Havendock"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip F:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins";
							if (is_bep_installed("G:/SteamLibrary/steamapps/common/Havendock"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip G:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins";

							if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Havendock Demo"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip -C HavendockD";
							if (is_bep_installed("D:/SteamLibrary/steamapps/common/Havendock Demo"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip D:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins";
							if (is_bep_installed("E:/SteamLibrary/steamapps/common/Havendock Demo"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip E:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins";
							if (is_bep_installed("F:/SteamLibrary/steamapps/common/Havendock Demo"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip F:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins";
							if (is_bep_installed("G:/SteamLibrary/steamapps/common/Havendock Demo"))
								command = "python resources/scripts/copyzip.py havendock\\unityexplorer6_mono.zip G:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins";
							run_command(command);
							break;
						case(1):
							if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Muck"))
								command = "python resources/scripts/copyzip.py muck\\unityexplorer6_mono.zip -C Muck";
							if (is_bep_installed("D:/SteamLibrary/steamapps/common/Muck"))
								command = "python resources/scripts/copyzip.py muck\\unityexplorer6_mono.zip D:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins";
							if (is_bep_installed("E:/SteamLibrary/steamapps/common/Muck"))
								command = "python resources/scripts/copyzip.py muck\\unityexplorer6_mono.zip E:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins";
							if (is_bep_installed("F:/SteamLibrary/steamapps/common/Muck"))
								command = "python resources/scripts/copyzip.py muck\\unityexplorer6_mono.zip F:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins";
							if (is_bep_installed("G:/SteamLibrary/steamapps/common/Muck"))
								command = "python resources/scripts/copyzip.py muck\\unityexplorer6_mono.zip G:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins";
							run_command(command);
							break;
						case(2):
							if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Hollow Knight"))
								command = "python resources/scripts/copyzip.py hollowknight\\unityexplorer6_mono.zip -C Hollow";
							if (is_bep_installed("D:/SteamLibrary/steamapps/common/Hollow Knight"))
								command = "python resources/scripts/copyzip.py hollowknight\\unityexplorer6_mono.zip D:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins";
							if (is_bep_installed("E:/SteamLibrary/steamapps/common/Hollow Knight"))
								command = "python resources/scripts/copyzip.py hollowknight\\unityexplorer6_mono.zip E:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins";
							if (is_bep_installed("F:/SteamLibrary/steamapps/common/Hollow Knight"))
								command = "python resources/scripts/copyzip.py hollowknight\\unityexplorer6_mono.zip F:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins";
							if (is_bep_installed("G:/SteamLibrary/steamapps/common/Hollow Knight"))
								command = "python resources/scripts/copyzip.py hollowknight\\unityexplorer6_mono.zip G:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins";
							run_command(command);
							break;
						case(3):
							if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Regions Of Ruin"))
								command = "python resources/scripts/copyzip.py regionsofruin\\unityexplorer5_mono.zip -C Regions";
							if (is_bep_installed("D:/SteamLibrary/steamapps/common/Regions Of Ruin"))
								command = "python resources/scripts/copyzip.py regionsofruin\\unityexplorer5_mono.zip D:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins";
							if (is_bep_installed("E:/SteamLibrary/steamapps/common/Regions Of Ruin"))
								command = "python resources/scripts/copyzip.py regionsofruin\\unityexplorer5_mono.zip E:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins";
							if (is_bep_installed("F:/SteamLibrary/steamapps/common/Regions Of Ruin"))
								command = "python resources/scripts/copyzip.py regionsofruin\\unityexplorer5_mono.zip F:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins";
							if (is_bep_installed("G:/SteamLibrary/steamapps/common/Regions Of Ruin"))
								command = "python resources/scripts/copyzip.py regionsofruin\\unityexplorer5_mono.zip G:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins";
							run_command(command);
							break;
						}

					}
					break;
				case(-5): //installs console commands
					switch (mainDisplay.function_last_used)
					{
					case(0):
						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Havendock"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip -C Havendock";
						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Havendock"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip D:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins Havendock";
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Havendock"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip E:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins Havendock";
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Havendock"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip F:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins Havendock";
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Havendock"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip G:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins Havendock";

						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Havendock Demo"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip -C HavendockD";
						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Havendock Demo"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip D:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins HavendockD";
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Havendock Demo"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip E:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins HavendockD";
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Havendock Demo"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip F:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins HavendockD";
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Havendock Demo"))
							command = "python resources/scripts/copyzip.py havendock\\ConsoleCommands.zip G:/SteamLibrary/steamapps/common/Havendock Demo/BepInEx/plugins HavendockD";

						run_command(command);
						break;
					case(1):
						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Muck"))
							command = "python resources/scripts/copyzip.py muck\\ConsoleCommands.zip -C Muck";
						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Muck"))
							command = "python resources/scripts/copyzip.py muck\\ConsoleCommands.zip D:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins Muck";
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Muck"))
							command = "python resources/scripts/copyzip.py muck\\ConsoleCommands.zip E:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins Muck";
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Muck"))
							command = "python resources/scripts/copyzip.py muck\\ConsoleCommands.zip F:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins Muck";
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Muck"))
							command = "python resources/scripts/copyzip.py muck\\ConsoleCommands.zip G:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins Muck";
						run_command(command);
						break;
					case(2):
						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Hollow Knight"))
							command = "python resources/scripts/copyzip.py hollowknight\\ConsoleCommands.zip -C Hollow";
						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Hollow Knight"))
							command = "python resources/scripts/copyzip.py hollowknight\\ConsoleCommands.zip D:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins Hollow";
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Hollow Knight"))
							command = "python resources/scripts/copyzip.py hollowknight\\ConsoleCommands.zip E:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins Hollow";
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Hollow Knight"))
							command = "python resources/scripts/copyzip.py hollowknight\\ConsoleCommands.zip F:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins Hollow";
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Hollow Knight"))
							command = "python resources/scripts/copyzip.py hollowknight\\ConsoleCommands.zip G:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins Hollow";
						run_command(command);
						break;
					case(3):
						if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Regions Of Ruin"))
							command = "python resources/scripts/copyzip.py regionsofruin\\ConsoleCommands.zip -C Regions";
						if (is_bep_installed("D:/SteamLibrary/steamapps/common/Regions Of Ruin"))
							command = "python resources/scripts/copyzip.py regionsofruin\\ConsoleCommands.zip D:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins Regions";
						if (is_bep_installed("E:/SteamLibrary/steamapps/common/Regions Of Ruin"))
							command = "python resources/scripts/copyzip.py regionsofruin\\ConsoleCommands.zip E:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins Regions";
						if (is_bep_installed("F:/SteamLibrary/steamapps/common/Regions Of Ruin"))
							command = "python resources/scripts/copyzip.py regionsofruin\\ConsoleCommands.zip F:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins Regions";
						if (is_bep_installed("G:/SteamLibrary/steamapps/common/Regions Of Ruin"))
							command = "python resources/scripts/copyzip.py regionsofruin\\ConsoleCommands.zip G:/SteamLibrary/steamapps/common/Regions Of Ruin/BepInEx/plugins Regions";
						run_command(command);
						break;
					}
					break;
				case(-3): // uninstall bepinex
					switch (mainDisplay.function_last_used)
					{
					case(0):
						command = "python resources/scripts/bepinex_havendock_uninstall.py";
						run_command(command);
						break;
					case(1):
						command = "python resources/scripts/bepinex_muck_uninstall.py";
						run_command(command);
						break;
					case(2):
						command = "python resources/scripts/bepinex_hollowknight_uninstall.py";
						run_command(command);
						break;
					case(3):
						command = "python resources/scripts/bepinex_regionsofruin_uninstall.py";
						run_command(command);
						break;
					}
					break;
				case(-2): // install bepinex
					switch (mainDisplay.function_last_used)
					{
					case(0):
						command = "python resources/scripts/bepinex_havendock.py";
						run_command(command);
						break;
					case(1):
						command = "python resources/scripts/bepinex_muck.py";
						run_command(command);
						break;
					case(2):
						command = "python resources/scripts/bepinex_hollowknight.py";
						run_command(command);
						break;
					case(3):
						command = "python resources/scripts/bepinex_regionsofruin.py";
						run_command(command);
						break;
					}
					break;
				case(-1): // opens my discord page
					{

						command = "start https://discord.gg/daMWV3TTea";
						run_command(command);
					}
					break;
				case(0): // switch mainDisplay to havendock
					{
						mainDisplay.setName("havendock");
						mainDisplay.bep_version = 6;
						mainDisplay.texture.loadFromFile("resources/images/havendock.png");
						mainDisplay.function_last_used = 0;
					}
					break;
				case(1): //switch mainDisplay to muck
					{
						mainDisplay.setName("muck");
						mainDisplay.bep_version = 6;
						mainDisplay.texture.loadFromFile("resources/images/muck.png");
						mainDisplay.function_last_used = 1;
					}
					break;
				case(2): //switch mainDisplay to hollow knight
					{
						mainDisplay.setName("hollow knight");
						mainDisplay.bep_version = 6;
						mainDisplay.texture.loadFromFile("resources/images/hollowknight.png");
						mainDisplay.function_last_used = 2;
					}
					break;
				case(3): //switch mainDisplay to regions of ruin
					{


						mainDisplay.setName("regions of ruin");
						mainDisplay.bep_version = 5;
						mainDisplay.texture.loadFromFile("resources/images/regionsofruin.png");
						mainDisplay.function_last_used = 3;
					}
					break;
				default:
					mainDisplay.setName("error");
					mainDisplay.bep_version = 6;
				
}

			}
		}
		else
		{
			this->shape.setFillColor(this->color);
			this->text.setFillColor(this->text_color);
		}

		this->text.setString(this->DISPLAY_NAME);
		//make sure the text is centered in the button
		this->text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		this->text.setPosition(this->position.x, this->position.y);
	}
};


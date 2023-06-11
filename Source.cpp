#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <functional>
#include <Windows.h>
#include <atlstr.h>
#include <locale>
#include <codecvt>
#include "MainDisplay.h"
#include "Button.h"
#pragma comment(lib, "Shlwapi.lib")

#include <shlwapi.h>

//i know, i know, i shouldnt use namespace std due to naming collisions, but i dont care and it's useful on a solo project
using namespace std;

//variables
const int width{ 1600 };
const int height{ 800 };
int header_ticker = 0;
int header_anim_ticker = 0;
float version = 3.0;
bool windowheld = false;
bool needs_update = false;
bool installer = true;


#pragma region METHODS

void Log(string message)
{
	std::cout << message + "::" << endl;
	std::wstring wide_message(message.begin(), message.end());
	LPCWSTR long_message = wide_message.c_str();
	OutputDebugString(long_message);
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

string run_command_string(string command)
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

    return data;
}

void cleanup()
{
	
	

}

bool check_for_update()
{
    //get username from environment
    char* username = getenv("USERNAME");
    string username_str(username);

    //read version.txt from http://daltonyx.com/loader/version.txt
    //if version.txt is not the same as the version variable, return true
    //else return false

    //download version.txt with curl
    string curl_command;
    if (username_str == "dalto" || username_str == "calli")
        curl_command = "curl http://192.168.1.48:8000/loader/version.txt -o version.txt && curl http://192.168.1.48:8000/loader/changelog.txt -o changelog.txt";
    else
        curl_command = "curl http://97.88.21.85:8000/loader/version.txt -o version.txt && curl http://97.88.21.85:8000/loader/changelog.txt -o changelog.txt";
    
    system(curl_command.c_str());

    //read version.txt
    ifstream version_file2;
    version_file2.open("version.txt");
    string version_string;
    version_file2 >> version_string;
    version_file2.close();

    //convert changelog.txt to string
    ifstream changelog_file;
    changelog_file.open("changelog.txt");
    string changelog_string;
    string line;
    while (getline(changelog_file, line))
    {
        changelog_string += line;
        changelog_string += "\n";
    }
    changelog_file.close();

    std::cout << "\n" << "version.txt and changelog downloaded from server! Checking for update..." << "\nYour version: " << version << "\nNew version:  " << version_string << endl;
    std::cout << "\n" << changelog_string << endl;

    //convert version_string to float
    float version_float = stof(version_string);

    //compare version_float to version
    if (version_float > version)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void swap_vector_indexes(int index1, int index2, vector<string> sayings_vector)
{
	//swap the indexes of two buttons in the vector
	string temp = sayings_vector[index1];
	sayings_vector[index1] = sayings_vector[index2];
	sayings_vector[index2] = temp;
}

void populate_sayings(vector<string>& sayings)
{
	sayings.push_back("we are totem");
	sayings.push_back("spood beest");
	sayings.push_back("gassytexan loves bigfoot");
	sayings.push_back("ba dum tiss");
	sayings.push_back("boganisanerd");
	sayings.push_back("potato patreason");
	sayings.push_back("is it data or data");
	sayings.push_back("wallaby is a banned word");
	sayings.push_back("walla walla washington");
	sayings.push_back("willy bum bum");
	sayings.push_back("a cop needed my mouse");
	sayings.push_back("do ya got any sayings");
	sayings.push_back("two stevens walk into a bar");
	sayings.push_back("and they say ouch");
	sayings.push_back("no lol");
	sayings.push_back("we're gonna need a bigger boat");
	sayings.push_back("welp, that's grounded");
	sayings.push_back("daltonyx, the dandelion hunter");
	sayings.push_back("Oh, you're finally awake!");
	sayings.push_back("noot, noot never changes");
	sayings.push_back("this is an uwu free zone");
	sayings.push_back("uwu");
	sayings.push_back("well i'm no car scientist but-");
	sayings.push_back("i think that's just a mechanic");
	sayings.push_back("try out Havendock!");
	sayings.push_back("man, i really need some more sayings, don't i?.");
	sayings.push_back("now with extra milk!");
	sayings.push_back("well, that's just like, your opinion and stuff, man");
	sayings.push_back("melon > lemon");
	sayings.push_back("i like to eat, eat, eat");
	sayings.push_back("eeples and baneenees");
	sayings.push_back("screw the nether");
	sayings.push_back("ya ever just eat a potato raw");
	sayings.push_back("think about this next time you blink");
	sayings.push_back("t-pose for dominance!");
	sayings.push_back("'i am the milkman, my milk is delicious' - the milkman");
	sayings.push_back("segmentation fault (core dumped)");
	sayings.push_back("i [] unicode");
	sayings.push_back("c++ is best++");
	sayings.push_back("how much do YOU like ramen noodles?");
	sayings.push_back("how's my driving?");
	sayings.push_back("feel free to request unity games to mod on discord!");
	sayings.push_back("programmer socks? check");
	sayings.push_back("feel free to request mods for unity games on discord!");

}

bool is_dll_installed(string dll, string directory)
{
	string path = directory + "/" + dll;
	ifstream file(path);
	//Log(to_string(file.good()));

	return file.good();
}

void open_directory_in_explorer(string directory)
{
	string command = "explorer " + directory;
	system(command.c_str());
}
#pragma endregion


int main()
{
#pragma region VARIABLE_CREATION
	sf::RenderWindow window(sf::VideoMode(width, height), "DDLoader", sf::Style::None);
	sf::Event event;
	srand(time(NULL));
	sf::Image icon;
	HDROP hDrop;
	if (!icon.loadFromFile("resources/Icon.png"));
	{
		//std::cout << "icon not found" << endl;
	}
	
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	bool running = true;



	vector<sf::Texture> credit_textures;
	sf::Texture texture;
	sf::Texture help_cc_texture;
	sf::Texture help_ue_texture;
	texture.loadFromFile("resources/images/hollowknight.png");
	help_cc_texture.loadFromFile("resources/images/help.png");
	help_ue_texture.loadFromFile("resources/images/help.png");
	sf::Font font;
	font.loadFromFile("resources/RobotoMono-Light.ttf");
	
	

	//add images for logo
	for (int i = 0; i < 90; i++)
	{
		sf::Texture texture;
		texture.loadFromFile("resources/credit/loader_" + to_string(i + 1) + ".png");
		credit_textures.push_back(texture);
	}

	//create vector of sayings for titlebar
	vector<string> sayings;
	populate_sayings(sayings);
	for (int i = 0; i < sayings.size(); i++)
	{
		swap_vector_indexes((rand() % sayings.size()), (rand() % sayings.size()), sayings);
	}
	
	MainDisplay mainDisplay = MainDisplay("DDLoader", 6, sf::Vector2f(950, 415), sf::Vector2f(1250, 720), texture);

	//set up text objects and shapes for titlebar/UI
	sf::Text program_title;
	program_title.setFont(font);
	program_title.setString("DDLoader");
	program_title.setCharacterSize(16);
	program_title.setStyle(sf::Text::Bold);
	program_title.setFillColor(sf::Color::White);
	program_title.setPosition(10,5);

	sf::Text program_close;
	program_close.setFont(font);
	program_close.setString("X");
	program_close.setCharacterSize(16);
	program_close.setStyle(sf::Text::Bold);
	program_close.setFillColor(sf::Color::White);
	program_close.setPosition(1580, 5);
	
	sf::RectangleShape program_titlebar;
	program_titlebar.setSize(sf::Vector2f(1600, 30));
	program_titlebar.setFillColor(sf::Color(30,30,30));
	program_titlebar.setPosition(0, 0);

	sf::RectangleShape program_ui_bar;
	program_ui_bar.setSize(sf::Vector2f(300, 800));
	program_ui_bar.setFillColor(sf::Color(40, 40, 40));
	program_ui_bar.setPosition(0, 0);

	sf::Sprite header_sprite;
	header_sprite.setTexture(credit_textures[0]);
	header_sprite.setOrigin(header_sprite.getGlobalBounds().width / 2, header_sprite.getGlobalBounds().height / 2);
	header_sprite.setPosition(width/2,height/2);

	sf::Text sayings_text;
	sayings_text.setFont(font);
	sayings_text.setString(sayings[rand()%sayings.size()]);
	sayings_text.setCharacterSize(16);
	sayings_text.setStyle(sf::Text::Bold);
	sayings_text.setFillColor(sf::Color::White);
	sayings_text.setPosition(width/2-(sayings_text.getGlobalBounds().width/2), 5);

	sf::Text titlename;
	titlename.setFont(font);
	titlename.setString("DDLoader");
	titlename.setCharacterSize(40);
	titlename.setStyle(sf::Text::Bold);
	titlename.setFillColor(sf::Color::White);
	titlename.setOrigin(titlename.getGlobalBounds().width / 2, titlename.getGlobalBounds().height / 2);
	titlename.setPosition(150, 280);

	sf::Text discord_text;
	discord_text.setFont(font);
	discord_text.setString("request Unity mods at:");
	discord_text.setCharacterSize(16);
	//discord_text.setStyle(sf::Text::Bold);
	discord_text.setFillColor(sf::Color::White);
	discord_text.setOrigin(discord_text.getGlobalBounds().width / 2, discord_text.getGlobalBounds().height / 2);
	discord_text.setPosition(150, 320);

	sf::Text console_commands_text;
	console_commands_text.setFont(font);
	console_commands_text.setString("console commands installed!");
	console_commands_text.setCharacterSize(16);
	console_commands_text.setStyle(sf::Text::Bold);
	console_commands_text.setFillColor(sf::Color::White);
	console_commands_text.setOrigin(console_commands_text.getGlobalBounds().width / 2, console_commands_text.getGlobalBounds().height / 2);
	console_commands_text.setPosition(1385, 705);

	sf::Text unityexplorer_text;
	unityexplorer_text.setFont(font);
	unityexplorer_text.setString("unityexplorer installed!");
	unityexplorer_text.setCharacterSize(16);
	unityexplorer_text.setStyle(sf::Text::Bold);
	unityexplorer_text.setFillColor(sf::Color::White);
	unityexplorer_text.setOrigin(unityexplorer_text.getGlobalBounds().width / 2, unityexplorer_text.getGlobalBounds().height / 2);
	unityexplorer_text.setPosition(1385, 645);

	sf::Text credit_text;
	credit_text.setFont(font);
	credit_text.setString("<3 daltonyx");
	credit_text.setCharacterSize(16);
	credit_text.setStyle(sf::Text::Bold);
	credit_text.setFillColor(sf::Color::White);
	credit_text.setOrigin(credit_text.getGlobalBounds().width / 2, credit_text.getGlobalBounds().height / 2);
	credit_text.setPosition(width - (credit_text.getGlobalBounds().width / 2 + 12),height-16);

	sf::Text bep_installed_text;
	bep_installed_text.setFont(font);
	bep_installed_text.setCharacterSize(16);
	bep_installed_text.setStyle(sf::Text::Bold);
	bep_installed_text.setString("BepInEx Installed");
	bep_installed_text.setFillColor(sf::Color::Green);
	bep_installed_text.setOrigin(bep_installed_text.getGlobalBounds().width / 2, bep_installed_text.getGlobalBounds().height / 2);
	bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y+75);

	sf::Text instructions1;
	instructions1.setFont(font);
	instructions1.setCharacterSize(20);
	instructions1.setStyle(sf::Text::Bold);
	instructions1.setString("to install a mod not listed here:");
	instructions1.setFillColor(sf::Color::White);
	instructions1.setOrigin(instructions1.getGlobalBounds().width / 2, instructions1.getGlobalBounds().height / 2);
	instructions1.setPosition(1225, 190);

	sf::Text instructions2;
	instructions2.setFont(font);
	instructions2.setCharacterSize(16);
	//instructions2.setStyle(sf::Text::Bold);
	instructions2.setString("1) download mod zip from nexusMods");
	instructions2.setFillColor(sf::Color::White);
	instructions2.setOrigin(instructions2.getGlobalBounds().width / 2, instructions2.getGlobalBounds().height / 2);
	instructions2.setPosition(1225, 230);

	sf::Text instructions3;
	instructions3.setFont(font);
	instructions3.setCharacterSize(16);
	//instructions3.setStyle(sf::Text::Bold);
	instructions3.setString("2) copy .DLL from inside the zip you downloaded");
	instructions3.setFillColor(sf::Color::White);
	instructions3.setOrigin(instructions3.getGlobalBounds().width / 2, instructions3.getGlobalBounds().height / 2);
	instructions3.setPosition(1225, 260);

	sf::Text instructions4;
	instructions4.setFont(font);
	instructions4.setCharacterSize(16);
	//instructions4.setStyle(sf::Text::Bold);
	instructions4.setString("3) click \"MODS FOLDER\"");
	instructions4.setFillColor(sf::Color::White);
	instructions4.setOrigin(instructions4.getGlobalBounds().width / 2, instructions4.getGlobalBounds().height / 2);
	instructions4.setPosition(1225, 290);

	sf::Text instructions5;
	instructions5.setFont(font);
	instructions5.setCharacterSize(16);
	//instructions5.setStyle(sf::Text::Bold);
	instructions5.setString("4) paste the .DLL into the mods folder that opens!");
	instructions5.setFillColor(sf::Color::White);
	instructions5.setOrigin(instructions5.getGlobalBounds().width / 2, instructions5.getGlobalBounds().height / 2);
	instructions5.setPosition(1225, 320);

	sf::Texture discord_texture;
	discord_texture.loadFromFile("resources/images/discord.png");

	

	//create game buttons
	vector<Button> buttons;
	Button discord = Button(discord_texture, sf::Vector2f(150, 360), -1);
	Button mods_folder = Button("MODS FOLDER", sf::Vector2f(1225, 130), -6, 6,sf::Vector2f(560,50), 20);
	Button filepicker_install = Button("CHOOSE A FILE TO INSTALL", sf::Vector2f(1225, 190), -7, 6, sf::Vector2f(560, 50), 20);
	Button bep_install = Button("INSTALL", sf::Vector2f(580, 650), -2, 6);
	Button bep_uninstall = Button("UNINSTALL", sf::Vector2f(580, 710), -3, 6);
	Button button1 = Button("HAVENDOCK", sf::Vector2f(150, 500+40),0,6);
	Button button2 = Button("MUCK", sf::Vector2f(150, 570+40),1,6);
	Button button3 = Button("HOLLOW KNIGHT", sf::Vector2f(150, 640+40),2,6);
	Button button4 = Button("REGIONS OF RUIN", sf::Vector2f(150, 710+40),3,5);
	Button unityexplorer_install = Button("UNITYEXPLORER", sf::Vector2f(1070,650),-4,6);
	Button consolecommands_install = Button("CONSOLE COMMANDS", sf::Vector2f(1070, 710), -5, 6);
	Button help_cc = Button(help_cc_texture, sf::Vector2f(910,710), -8);
	Button help_ue = Button(help_ue_texture, sf::Vector2f(910, 650), -9);
	Button windowflip_mods = Button("install panel", sf::Vector2f(1050, 75), -10, 6, sf::Vector2f(340,25), 10);
	Button windowflip_manager = Button("mods panel", sf::Vector2f(1398, 75), -11, 6, sf::Vector2f(340, 25), 10);

	//make sure we're actually zero-ed out in state
	mainDisplay.setName("havendock");
	mainDisplay.bep_version = 6;
	mainDisplay.texture.loadFromFile("resources/images/havendock.png");
	mainDisplay.function_last_used = 0;

#pragma endregion
	while (running)
	{
#pragma region EVENT_HANDLING
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				//free memory and close window
				std::atexit(cleanup);
				running = false;
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//check if mouse is within 50px of the top of the window
					if (sf::Mouse::getPosition(window).y < 50)
					{
						//check if mouse is within 50px of the right of the window
						if (sf::Mouse::getPosition(window).x > window.getSize().x - 50)
						{
							//free memory and close window
							std::atexit(cleanup);
							running = false;
							window.close();
						}
						else
						{
							windowheld = true;
							
						}
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					windowheld = false;
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					std::atexit(cleanup);
					running = false;
					window.close();
				}
			}
		}

		if (windowheld)
			window.setPosition(sf::Mouse::getPosition() - sf::Vector2i(window.getSize().x / 2, 25));

		

#pragma endregion
		
#pragma region DISPLAY_LOOP
		//clear the window
		window.clear(sf::Color(50,50,50));
		header_ticker++;
		if (header_ticker > 1)
		{
			header_ticker = 0;
			header_anim_ticker++;
			if (header_anim_ticker > 89)
				header_anim_ticker = 0;
		}
		header_sprite.setTexture(credit_textures[header_anim_ticker]);
		header_sprite.setPosition(150,160);

		window.draw(program_ui_bar);
		window.draw(header_sprite);
		window.draw(program_titlebar);
		window.draw(program_close);
		window.draw(program_title);
		window.draw(sayings_text);
		mainDisplay.draw(window);
		window.draw(titlename);
		window.draw(credit_text);
		button1.draw(window);
		button2.draw(window);
		button3.draw(window);
		button4.draw(window);
		discord.draw(window);

		//switch for what to display
		switch (mainDisplay.function_last_used)
		{
		case(0):
			if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Havendock") ||
				is_bep_installed("D:/SteamLibrary/steamapps/common/Havendock") ||
				is_bep_installed("E:/SteamLibrary/steamapps/common/Havendock") ||
				is_bep_installed("F:/SteamLibrary/steamapps/common/Havendock") ||
				is_bep_installed("G:/SteamLibrary/steamapps/common/Havendock"))
			{
				bep_installed_text.setString("BepInEx Installed");
				bep_installed_text.setFillColor(sf::Color::Green);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				
			}
			else
			{
				bep_installed_text.setString("BepInEx Not Installed");
				bep_installed_text.setFillColor(sf::Color::Red);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				
			}
			if (is_dll_installed("ConsoleCommands.dll", "C:/Program Files (x86)/Steam/steamapps/common/Havendock/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "D:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "E:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "F:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "G:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins"))
			{
				console_commands_text.setString("CONSOLE COMMANDS Installed!");
				console_commands_text.setFillColor(sf::Color::Green);
				console_commands_text.setOrigin(console_commands_text.getLocalBounds().width / 2, console_commands_text.getLocalBounds().height / 2);
			}
			else
			{
				console_commands_text.setString("CONSOLE COMMANDS Not Installed");
				console_commands_text.setFillColor(sf::Color::Red);
				console_commands_text.setOrigin(console_commands_text.getLocalBounds().width / 2, console_commands_text.getLocalBounds().height / 2);
			}
			if (is_dll_installed("UnityExplorer.BIE6.Mono.dll", "C:/Program Files (x86)/Steam/steamapps/common/Havendock/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "D:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "E:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "F:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "G:/SteamLibrary/steamapps/common/Havendock/BepInEx/plugins/sinai-dev-UnityExplorer"))
			{
				unityexplorer_text.setString("UNITYEXPLORER Installed!");
				unityexplorer_text.setFillColor(sf::Color::Green);
				unityexplorer_text.setOrigin(unityexplorer_text.getLocalBounds().width / 2, unityexplorer_text.getLocalBounds().height / 2);
			}
			else
			{
				unityexplorer_text.setString("UNITYEXPLORER Not Installed");
				unityexplorer_text.setFillColor(sf::Color::Red);
				unityexplorer_text.setOrigin(unityexplorer_text.getLocalBounds().width / 2, unityexplorer_text.getLocalBounds().height / 2);
			}
			break;
		case(1):
			if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Muck") ||
				is_bep_installed("D:/SteamLibrary/steamapps/common/Muck") ||
				is_bep_installed("E:/SteamLibrary/steamapps/common/Muck") ||
				is_bep_installed("F:/SteamLibrary/steamapps/common/Muck") ||
				is_bep_installed("G:/SteamLibrary/steamapps/common/Muck"))
			{
				bep_installed_text.setString("BepInEx Installed");
				bep_installed_text.setFillColor(sf::Color::Green);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				
			}
			else
			{
				bep_installed_text.setString("BepInEx Not Installed");
				bep_installed_text.setFillColor(sf::Color::Red);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				
			}
			//check for ConsoleCommands.dll
			if (is_dll_installed("ConsoleCommands.dll", "C:/Program Files (x86)/Steam/steamapps/common/Muck/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "D:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "E:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "F:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "G:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins"))
			{
				console_commands_text.setString("CONSOLE COMMANDS Installed!");
				console_commands_text.setFillColor(sf::Color::Green);
				console_commands_text.setOrigin(console_commands_text.getLocalBounds().width / 2, console_commands_text.getLocalBounds().height / 2);
			}
			else
			{
				console_commands_text.setString("CONSOLE COMMANDS Not Installed");
				console_commands_text.setFillColor(sf::Color::Red);
				console_commands_text.setOrigin(console_commands_text.getLocalBounds().width / 2, console_commands_text.getLocalBounds().height / 2);
			}
			//check for UnityExplorer.BIE6.Mono.dll
			if (is_dll_installed("UnityExplorer.BIE6.Mono.dll", "C:/Program Files (x86)/Steam/steamapps/common/Muck/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "D:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "E:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "F:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "G:/SteamLibrary/steamapps/common/Muck/BepInEx/plugins/sinai-dev-UnityExplorer"))
			{
				unityexplorer_text.setString("UNITYEXPLORER Installed!");
				unityexplorer_text.setFillColor(sf::Color::Green);
				unityexplorer_text.setOrigin(unityexplorer_text.getLocalBounds().width / 2, unityexplorer_text.getLocalBounds().height / 2);
			}
			else
			{
				unityexplorer_text.setString("UNITYEXPLORER Not Installed");
				unityexplorer_text.setFillColor(sf::Color::Red);
				unityexplorer_text.setOrigin(unityexplorer_text.getLocalBounds().width / 2, unityexplorer_text.getLocalBounds().height / 2);
			}
			break;
		case(2):
			if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Hollow Knight") ||
				is_bep_installed("D:/SteamLibrary/steamapps/common/Hollow Knight") ||
				is_bep_installed("E:/SteamLibrary/steamapps/common/Hollow Knight") ||
				is_bep_installed("F:/SteamLibrary/steamapps/common/Hollow Knight") ||
				is_bep_installed("G:/SteamLibrary/steamapps/common/Hollow Knight"))
			{
				bep_installed_text.setString("BepInEx Installed");
				bep_installed_text.setFillColor(sf::Color::Green);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				
			}
			else
			{
				bep_installed_text.setString("BepInEx Not Installed");
				bep_installed_text.setFillColor(sf::Color::Red);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				
			}
			//check for ConsoleCommands.dll
			if (is_dll_installed("ConsoleCommands.dll", "C:/Program Files (x86)/Steam/steamapps/common/Hollow Knight/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "D:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "E:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "F:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "G:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins"))
			{
				console_commands_text.setString("CONSOLE COMMANDS Installed!");
				console_commands_text.setFillColor(sf::Color::Green);
				console_commands_text.setOrigin(console_commands_text.getLocalBounds().width / 2, console_commands_text.getLocalBounds().height / 2);
			}
			else
			{
				console_commands_text.setString("CONSOLE COMMANDS Not Installed");
				console_commands_text.setFillColor(sf::Color::Red);
				console_commands_text.setOrigin(console_commands_text.getLocalBounds().width / 2, console_commands_text.getLocalBounds().height / 2);
			}
			//check for UnityExplorer.BIE6.Mono.dll
			if (is_dll_installed("UnityExplorer.BIE6.Mono.dll", "C:/Program Files (x86)/Steam/steamapps/common/Hollow Knight/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "D:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "E:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "F:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE6.Mono.dll", "G:/SteamLibrary/steamapps/common/Hollow Knight/BepInEx/plugins/sinai-dev-UnityExplorer"))
			{
				unityexplorer_text.setString("UNITYEXPLORER Installed!");
				unityexplorer_text.setFillColor(sf::Color::Green);
				unityexplorer_text.setOrigin(unityexplorer_text.getLocalBounds().width / 2, unityexplorer_text.getLocalBounds().height / 2);
			}
			else
			{
				unityexplorer_text.setString("UNITYEXPLORER Not Installed");
				unityexplorer_text.setFillColor(sf::Color::Red);
				unityexplorer_text.setOrigin(unityexplorer_text.getLocalBounds().width / 2, unityexplorer_text.getLocalBounds().height / 2);
			}
			break;
		case(3):
			if (is_bep_installed("C:/Program Files (x86)/Steam/steamapps/common/Regions of Ruin") ||
				is_bep_installed("D:/SteamLibrary/steamapps/common/Regions of Ruin") ||
				is_bep_installed("E:/SteamLibrary/steamapps/common/Regions of Ruin") ||
				is_bep_installed("F:/SteamLibrary/steamapps/common/Regions of Ruin") ||
				is_bep_installed("G:/SteamLibrary/steamapps/common/Regions of Ruin"))
			{
				bep_installed_text.setString("BepInEx Installed");
				bep_installed_text.setFillColor(sf::Color::Green);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
			}
			else
			{
				bep_installed_text.setString("BepInEx Not Installed");
				bep_installed_text.setFillColor(sf::Color::Red);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
			}
			//check for RegionsOfRuin_ConsoleCommands.dll
			if (is_dll_installed("ConsoleCommands.dll", "C:/Program Files (x86)/Steam/steamapps/common/Regions of Ruin/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "D:/SteamLibrary/steamapps/common/Regions of Ruin/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "E:/SteamLibrary/steamapps/common/Regions of Ruin/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "F:/SteamLibrary/steamapps/common/Regions of Ruin/BepInEx/plugins") ||
				is_dll_installed("ConsoleCommands.dll", "G:/SteamLibrary/steamapps/common/Regions of Ruin/BepInEx/plugins"))
			{
				console_commands_text.setString("CONSOLE COMMANDS Installed!");
				console_commands_text.setFillColor(sf::Color::Green);
				console_commands_text.setOrigin(console_commands_text.getLocalBounds().width / 2, console_commands_text.getLocalBounds().height / 2);
			}
			else
			{
				console_commands_text.setString("CONSOLE COMMANDS Not Installed");
				console_commands_text.setFillColor(sf::Color::Red);
				console_commands_text.setOrigin(console_commands_text.getLocalBounds().width / 2, console_commands_text.getLocalBounds().height / 2);
			}
			//check for UnityExplorer.BIE5.Mono.dll
			if (is_dll_installed("UnityExplorer.BIE5.Mono.dll", "C:/Program Files (x86)/Steam/steamapps/common/Regions of Ruin/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE5.Mono.dll", "D:/SteamLibrary/steamapps/common/Regions of Ruin/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE5.Mono.dll", "E:/SteamLibrary/steamapps/common/Regions of Ruin/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE5.Mono.dll", "F:/SteamLibrary/steamapps/common/Regions of Ruin/BepInEx/plugins/sinai-dev-UnityExplorer") ||
				is_dll_installed("UnityExplorer.BIE5.Mono.dll", "G:/SteamLibrary/steamapps/common/Regions of Ruin/BepInEx/plugins/sinai-dev-UnityExplorer"))
			{
				unityexplorer_text.setString("UNITYEXPLORER Installed!");
				unityexplorer_text.setFillColor(sf::Color::Green);
				unityexplorer_text.setOrigin(unityexplorer_text.getLocalBounds().width / 2, unityexplorer_text.getLocalBounds().height / 2);
			}
			else
			{
				unityexplorer_text.setString("UNITYEXPLORER Not Installed");
				unityexplorer_text.setFillColor(sf::Color::Red);
				unityexplorer_text.setOrigin(unityexplorer_text.getLocalBounds().width / 2, unityexplorer_text.getLocalBounds().height / 2);
			}
			break;

		}
		
		if (installer)
		{
			//if in installer mode
			window.draw(instructions1);
			window.draw(instructions2);
			window.draw(instructions3);
			window.draw(instructions4);
			window.draw(instructions5);
			mods_folder.draw(window);
			help_cc.draw(window);
			help_ue.draw(window);
			unityexplorer_install.draw(window);
			consolecommands_install.draw(window);


			mods_folder.update(window, mainDisplay, installer);
			help_cc.update(window, mainDisplay, installer);
			help_ue.update(window, mainDisplay, installer);
			unityexplorer_install.update(window, mainDisplay, installer);
			consolecommands_install.update(window, mainDisplay, installer);
		}
		else if (!installer);
		{
			//if in mod filescanner mode

		}

		//draw the window
		bep_install.draw(window);
		bep_uninstall.draw(window);
		bep_install.update(window, mainDisplay, installer);
		bep_uninstall.update(window, mainDisplay, installer);
		window.draw(bep_installed_text);
		window.draw(discord_text);
		window.draw(console_commands_text);
		window.draw(unityexplorer_text);
		windowflip_manager.draw(window);
		windowflip_mods.draw(window);

		//update the window
		windowflip_manager.update(window, mainDisplay, installer);
		windowflip_mods.update(window, mainDisplay, installer);
		button1.update(window, mainDisplay, installer);
		button2.update(window, mainDisplay, installer);
		button3.update(window, mainDisplay, installer);
		button4.update(window, mainDisplay, installer);
		discord.update(window, mainDisplay, installer);
		mainDisplay.update("havendock");

		window.setFramerateLimit(60);
		window.display();

#pragma endregion

	}
	//return okay if the program exits properly
    return 0;
}
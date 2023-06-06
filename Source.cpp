#define _CRT_SECURE_NO_WARNINGS
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


//i know, i know, i shouldnt use namespace std due to naming collisions, but i dont care and it's useful on a solo project
using namespace std;

//variables
int width{ 1600 };
int height{ 800 };
string username;
bool maximized = false;
int state = 0;
int substate = 0;
int header_ticker = 0;
int header_anim_ticker = 0;
float version = 3.0;
bool windowheld = false;
bool needs_update = false;

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
		this->divider1.setSize(sf::Vector2f(25, size.y+40));
		this->divider1.setFillColor(sf::Color(50, 50, 50, 255));
		this->divider1.setOrigin(1.5, (size.y+20) / 2);
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
		cout << message + "::" << endl;
		std::wstring wide_message(message.begin(), message.end());
		LPCWSTR long_message = wide_message.c_str();
		OutputDebugString(long_message);
	}

	void update(string name)
	{
		//Log(DISPLAY_NAME);
		this->text.setString(toupper(DISPLAY_NAME));
		this->bepinex_version.setString("BEPINEX " + to_string(this->bep_version));
		this->text.setPosition(sf::Vector2f(this->text_position.x - this->text.getGlobalBounds().width / 2, this->text_position.y+5));
		this->bepinex_version.setPosition(sf::Vector2f(this->text_position.x - this->bepinex_version.getGlobalBounds().width / 2, this->text_position.y+45));
		this->sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		this->sprite.setPosition(sf::Vector2f(text_position.x, text_position.y - 175));
		//this->texture = texture;
	}


};

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

	Button(sf::Texture& image, sf::Vector2f position, int function_number, bool active = true) :
		shape(sf::Vector2f(250, 50)),
		font{},
		text{ "",font,20 },
		color{ 30, 30, 30, 255 },
		hover_color{ 50, 50, 50, 255 },
		click_color{ 60, 60, 60, 255 },
		text_color{ 255, 255, 255, 255 },
		position(position)
	{
		this->shape = sf::RectangleShape(sf::Vector2f(250, 50));
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

	void draw(sf::RenderWindow& window)
	{
		window.draw(this->shape);
		window.draw(this->text);
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

		cout << data << endl;
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

	void update(sf::RenderWindow& window, MainDisplay& mainDisplay)
	{
		sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
		//if mouse is over button
		if (mouse_pos.x > this->shape.getPosition().x - (this->shape.getSize().x / 2) && mouse_pos.x < this->shape.getPosition().x + (this->shape.getSize().x / 2) && mouse_pos.y > this->shape.getPosition().y - (this->shape.getSize().y / 2) && mouse_pos.y < this->shape.getPosition().y + (this->shape.getSize().y / 2))
		{
			this->shape.setFillColor(this->hover_color);
			this->text.setFillColor(this->text_color);
			//if mouse is clicked
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->shape.setFillColor(this->click_color);
				string command = "";
				switch(function_number)
				{
					case(-3):
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
					case(-2):
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
					case(-1):
						command = "start https://discord.gg/daMWV3TTea";
						run_command(command);
						break;
					case(0):
						mainDisplay.setName("havendock");
						mainDisplay.bep_version = 6;
						mainDisplay.texture.loadFromFile("resources/images/havendock.png");
						mainDisplay.function_last_used = 0;
						break;
					case(1):
						mainDisplay.setName("muck");
						mainDisplay.bep_version = 6;
						mainDisplay.texture.loadFromFile("resources/images/muck.png");
						mainDisplay.function_last_used = 1;
						break;
					case(2):
						mainDisplay.setName("hollow knight");
						mainDisplay.bep_version = 6;
						mainDisplay.texture.loadFromFile("resources/images/hollowknight.png");
						mainDisplay.function_last_used = 2;
						break;
					case(3):
						mainDisplay.setName("regions of ruin");
						mainDisplay.bep_version = 5;
						mainDisplay.texture.loadFromFile("resources/images/regionsofruin.png");
						mainDisplay.function_last_used = 3;
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

#pragma region METHODS

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

    cout << data << endl;
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

    cout << "\n" << "version.txt and changelog downloaded from server! Checking for update..." << "\nYour version: " << version << "\nNew version:  " << version_string << endl;
    cout << "\n" << changelog_string << endl;

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
}

#pragma endregion






int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "DDLoader", sf::Style::None);
	sf::Event event;
	srand(time(NULL));
	sf::Image icon;

	if (!icon.loadFromFile("resources/Icon.png"));
	{
		//cout << "icon not found" << endl;
	}
	
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	bool running = true;

#pragma region VARIABLE_CREATION

	vector<sf::Texture> credit_textures;
	sf::Texture texture;
	texture.loadFromFile("resources/images/hollowknight.png");
	sf::Font font;
	font.loadFromFile("resources/RobotoMono-Light.ttf");
	
	//check for an update, and handle accordingly
	if (check_for_update())
	{
		needs_update = true;
	}

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


	//set up text
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


	sf::Texture discord_texture;
	discord_texture.loadFromFile("resources/images/discord.png");

	//convert changelog.txt to string
	ifstream changelog_file;
	changelog_file.open("changelog.txt");
	string changelog_string;
	string liner;
	while (getline(changelog_file, liner))
	{
		changelog_string += liner;
		changelog_string += "\n";
	}
	changelog_file.close();

	//create game buttons
	vector<Button> buttons;
	Button discord = Button(discord_texture, sf::Vector2f(150, 360), -1);
	Button bep_install = Button("INSTALL", sf::Vector2f(580, 650), -2, 6);
	Button bep_uninstall = Button("UNINSTALL", sf::Vector2f(580, 710), -3, 6);
	Button button1 = Button("HAVENDOCK", sf::Vector2f(150, 500+40),0,6);
	Button button2 = Button("MUCK", sf::Vector2f(150, 570+40),1,6);
	Button button3 = Button("HOLLOW KNIGHT", sf::Vector2f(150, 640+40),2,6);
	Button button4 = Button("REGIONS OF RUIN", sf::Vector2f(150, 710+40),3,5);

	//make sure we're actually zero-ed out in state
	mainDisplay.setName("havendock");
	mainDisplay.bep_version = 6;
	mainDisplay.texture.loadFromFile("resources/images/havendock.png");

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
				break;
			}
			else
			{
				bep_installed_text.setString("BepInEx Not Installed");
				bep_installed_text.setFillColor(sf::Color::Red);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				break;
			}
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
				break;
			}
			else
			{
				bep_installed_text.setString("BepInEx Not Installed");
				bep_installed_text.setFillColor(sf::Color::Red);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				break;
			}
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
				break;
			}
			else
			{
				bep_installed_text.setString("BepInEx Not Installed");
				bep_installed_text.setFillColor(sf::Color::Red);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				break;
			}
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
				break;
			}
			else
			{
				bep_installed_text.setString("BepInEx Not Installed");
				bep_installed_text.setFillColor(sf::Color::Red);
				bep_installed_text.setOrigin(bep_installed_text.getLocalBounds().width / 2, bep_installed_text.getLocalBounds().height / 2);
				bep_installed_text.setPosition(mainDisplay.text_position.x, mainDisplay.text_position.y + 75);
				break;
			}
		

		}
		bep_install.draw(window);
		bep_uninstall.draw(window);
		bep_install.update(window, mainDisplay);
		bep_uninstall.update(window, mainDisplay);
		window.draw(bep_installed_text);
		//display the window
		button1.update(window, mainDisplay);
		button2.update(window, mainDisplay);
		button3.update(window, mainDisplay);
		discord.update(window, mainDisplay);
		mainDisplay.update("havendock");
		button4.update(window, mainDisplay);
		window.setFramerateLimit(60);
		window.display();

#pragma endregion

	}
	//return okay if the program exits properly
    return 0;
}
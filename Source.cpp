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
public:
	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Text text;
	sf::Text bepinex_version;
	sf::Font font;
	sf::Sprite sprite;
	sf::RectangleShape divider1;
	sf::RectangleShape divider2;
	string DISPLAY_NAME = "havendock";

	MainDisplay(string name, int bep_version, sf::Vector2f position, sf::Vector2f size, sf::Texture texture)
		: text("<game_name>", font, 20), bepinex_version("BEPINEX " + bep_version, font, 10)
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
		this->text.setCharacterSize(20);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		this->text.setPosition(shape.getPosition().x-380-(text.getGlobalBounds().width/2), shape.getPosition().y);
		this->bepinex_version.setFont(font);
		this->bepinex_version.setString("BEPINEX " + bep_version);
		this->bepinex_version.setCharacterSize(10);
		this->bepinex_version.setFillColor(sf::Color(255, 255, 255, 255));
		this->bepinex_version.setPosition(shape.getPosition().x, shape.getPosition().y + (shape.getSize().y / 2 - 50));
		this->texture = texture;
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
		this->sprite.setPosition(this->shape.getPosition().x, this->shape.getPosition().y - 50);

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

	void update(string name, int bep_version, sf::Texture texture)
	{
		this->text.setString(toupper(DISPLAY_NAME));
		this->bepinex_version.setString("BEPINEX " + bep_version);
		this->texture = texture;
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

	Button(string text, sf::Vector2f position)
		: text("no", font, 20)
	{
		this->shape = sf::RectangleShape(sf::Vector2f(250, 50));
		this->shape.setFillColor(sf::Color(10, 10, 10, 255));
		this->shape.setOrigin(this->shape.getSize().x / 2, this->shape.getSize().y / 2);
		this->shape.setPosition(position);
		this->font.loadFromFile("resources/RobotoMono-Light.ttf");
		this->text.setFont(font);
		this->text.setString(text);
		this->text.setCharacterSize(20);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		this->text.setPosition(this->shape.getPosition().x - (this->text.getGlobalBounds().width / 2), this->shape.getPosition().y - (this->text.getGlobalBounds().height / 2));
		this->color = sf::Color(30, 30, 30, 255);
		this->hover_color = sf::Color(50, 50, 50, 255);
		this->click_color = sf::Color(60, 60, 60, 255);
		this->text_color = sf::Color(255, 255, 255, 255);
		this->position = position;

	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(this->shape);
		window.draw(this->text);
	}
	
	void update(sf::RenderWindow& window)
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
			}
		}
		else
		{
			this->shape.setFillColor(this->color);
			this->text.setFillColor(this->text_color);
		}
		
	}
};



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
	//set up texture as a blank texture
	texture.create(1, 1);
	
	if (check_for_update())
	{
		needs_update = true;
	}

	for (int i = 0; i < 90; i++)
	{
		sf::Texture texture;
		texture.loadFromFile("resources/credit/loader_" + to_string(i + 1) + ".png");
		credit_textures.push_back(texture);
	}

	vector<string> sayings;
	sayings.push_back("we are totem");
	sayings.push_back("spood beest");
	sayings.push_back("gassytexan loves big feet");
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
	sayings.push_back("Oh, you're finally awake");
	sayings.push_back("noot, noot never changes");
	sayings.push_back("this is an uwu free zone");
	sayings.push_back("uwu");
	sayings.push_back("well i'm no car scientist but-");
	sayings.push_back("i think that's just a mechanic");

	//shuffle sayings vector
	for (int i = 0; i < sayings.size(); i++)
	{
		swap_vector_indexes((rand() % sayings.size()), (rand() % sayings.size()), sayings);
	}
	
	//set up font
	sf::Font font;
	font.loadFromFile("resources/RobotoMono-Light.ttf");
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

	vector<Button> buttons;
	buttons.push_back(Button("HAVENDOCK", sf::Vector2f(150, 400)));
	buttons.push_back(Button("MUCK", sf::Vector2f(150, 470)));
	buttons.push_back(Button("HOLLOW KNIGHT", sf::Vector2f(150, 540)));
	buttons.push_back(Button("REGIONS OF RUIN", sf::Vector2f(150, 610)));

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
		mainDisplay.update("havendock", 6, texture);
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].draw(window);
			buttons[i].update(window);
		}
		window.setFramerateLimit(60);
		window.display();

#pragma endregion

	}
	//return okay if the program exits properly
    return 0;
}
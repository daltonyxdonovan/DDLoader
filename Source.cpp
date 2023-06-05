#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <cstring>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

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
bool needs_update = false;

#pragma region CLASSES


class DisplayBox
{
public:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color color;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	string title_text = "";
	
	bool up = false;
	bool down = false;

	int animation_step_limit = 800;
	int animation_step_amount = 40;
	int desired_y;
	int original_y;

	DisplayBox(sf::Vector2f position, sf::Vector2f size, sf::Color color)
	{
		this->position = position;
		this->size = size;
		this->color = color;
		this->desired_y = position.y;
		this->original_y = position.y;

		shape.setSize(size);
		shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
		shape.setFillColor(color);
		shape.setPosition(position);
		
		
	}

	DisplayBox(sf::Vector2f position, sf::Vector2f size, sf::Color color, string title_text)
	{
		this->position = position;
		this->size = size;
		this->color = color;
		this->desired_y = position.y;
		this->original_y = position.y;
		this->title_text = title_text;

		shape.setSize(size);
		shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
		shape.setFillColor(color);
		shape.setPosition(position);


	}

	void draw(sf::RenderWindow& window, sf::Font font)
	{
		shape.setPosition(position);
		shape.setSize(size);
		shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
		shape.setFillColor(color);
		window.draw(shape);

		
		sf::Text text;
		text.setFont(font);
		text.setString(title_text);
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::White);
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(position.x, position.y -350);
		text.setStyle(sf::Text::Bold);
		window.draw(text);

		if (title_text != "")
		{
			//make a line under the text
			sf::RectangleShape line;
			line.setSize(sf::Vector2f(text.getGlobalBounds().width, 5));
			line.setFillColor(sf::Color::White);
			line.setOrigin(line.getGlobalBounds().width / 2, line.getGlobalBounds().height / 2);
			line.setPosition(text.getPosition().x+5, text.getPosition().y + 50);
			window.draw(line);
		}
	}

	void update()
	{
		//if y != desired_y, step once towards desired_y
		if (position.y != desired_y)
		{
			if (position.y < desired_y)
			{
				position.y += animation_step_amount;
			}
			else if (position.y > desired_y)
			{
				position.y -= animation_step_amount;
			}
		}
	}

};

class Button
{
public:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color color;
	sf::Color hover_color;
	sf::Color clicked_color;
	sf::Color text_color;
	sf::Color text_hover_color;
	sf::Color text_clicked_color;
	sf::Font font;
	bool clicked = false;
	bool hover = false;
	bool active = false;
	sf::RectangleShape shape;
	string text_string;
	int font_size;
	bool interactable;

	Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color text_color, string text_string, int font_size, bool interactable)
	{
		this->position = position;
		this->size = size;
		this->color = color;
		this->text_color = text_color;
		this->font.loadFromFile("resources/RobotoMono-Light.ttf");
		this->text_string = text_string;
		this->font_size = font_size;
		this->interactable = interactable;
		
		shape.setSize(size);
		shape.setOrigin(size.x / 2, size.y / 2);
		shape.setPosition(position);
		shape.setFillColor(color);
		
		//this god-awful mess is checking the current rgb of the background color and making a hover and clicked color based on that
		hover_color = sf::Color(color.r + 50 > 255 ? 255 : color.r + 50, color.g + 50 > 255 ? 255 : color.g + 50, color.b + 50 > 255 ? 255 : color.b + 50);
		clicked_color = sf::Color(color.r + 100 > 255 ? 255 : color.r + 100, color.g + 100 > 255 ? 255 : color.g + 100, color.b + 100 > 255 ? 255 : color.b + 100);
		text_hover_color = sf::Color(text_color.r + 50 > 255 ? 255 : text_color.r + 50, text_color.g + 50 > 255 ? 255 : text_color.g + 50, text_color.b + 50 > 255 ? 255 : text_color.b + 50);
		text_clicked_color = sf::Color(text_color.r + 100 > 255 ? 255 : text_color.r + 100, text_color.g + 100 > 255 ? 255 : text_color.g + 100, text_color.b + 100 > 255 ? 255 : text_color.b + 100);
	}

	void set_position(sf::Vector2f position)
	{
		this->position = position;
		shape.setPosition(position);
	}

	void update(sf::RenderWindow& window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosF{ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) };
		//bounds should take into account the absolute position of the button
		sf::FloatRect bounds = sf::FloatRect(position.x-size.x/2, position.y-size.y/2, size.x, size.y);
		clicked = false;
		hover = false;

		if (bounds.contains(mousePosF))
		{
			hover = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				clicked = true;
				active = true;
			}
		}
		else
		{
			active = false;
		}

		//if (!interactable) return;
		if (clicked)
		{
			shape.setFillColor(clicked_color);
		}
		else if (hover)
		{
			shape.setFillColor(hover_color);
		}
		else
		{
			shape.setFillColor(color);
		}
	}

	void draw(sf::RenderWindow& window)
	{
		sf::Text text = sf::Text{ text_string, font };
		text.setCharacterSize(font_size);
		sf::Vector2f center = sf::Vector2f(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
		sf::Vector2f localBounds = center + sf::Vector2f(text.getLocalBounds().left, text.getLocalBounds().top);
		text.setOrigin(localBounds);
		text.setPosition(position);
		text.setStyle(sf::Text::Bold);
		if (clicked)
		{
			text.setFillColor(text_clicked_color);
		}
		else if (hover)
		{
			text.setFillColor(text_hover_color);
		}
		else
		{
			text.setFillColor(text_color);
		}


		window.draw(shape);
		window.draw(text);

	}


};




#pragma endregion

#pragma region METHODS

void remove_old_loader()
{
	
	//if loader.exe exists in directory, remove it
	if (std::filesystem::exists("loader.exe"))
	{
		std::filesystem::remove("loader.exe");
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

/*
void maximize_window(sf::RenderWindow& window)
{
	if (!maximized)
	{
		//maximize window
		ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
		maximized = true;
	}
	else
	{
		//minimize window
		ShowWindow(window.getSystemHandle(), SW_MINIMIZE);
		maximized = false;
	}
	
	
}

void reset_window(sf::RenderWindow& window)
{
	//reset window
	ShowWindow(window.getSystemHandle(), SW_RESTORE);
	maximized = false;
}*/



	

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

	bool windowheld = false;
	

	
	
	//set up text
	sf::Text program_title;
	program_title.setFont(font);
	program_title.setString("LOAD-R");
	program_title.setCharacterSize(10);
	program_title.setStyle(sf::Text::Bold);
	program_title.setFillColor(sf::Color::White);
	program_title.setPosition(10,10);
	
	sf::RectangleShape program_titlebar;
	program_titlebar.setSize(sf::Vector2f(1600, 30));
	program_titlebar.setFillColor(sf::Color(10,10,10));
	program_titlebar.setPosition(0, 0);

	sf::RectangleShape program_ui_bar;
	program_ui_bar.setSize(sf::Vector2f(300, 800));
	program_ui_bar.setFillColor(sf::Color(20, 20, 20));
	program_ui_bar.setPosition(0, 0);
	
	sf::Sprite header_sprite;
	header_sprite.setTexture(credit_textures[0]);
	header_sprite.setOrigin(header_sprite.getGlobalBounds().width / 2, header_sprite.getGlobalBounds().height / 2);
	header_sprite.setPosition(width/2,height/2);

	

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
		window.clear();
		header_ticker++;
		if (header_ticker > 1)
		{
			header_ticker = 0;
			header_anim_ticker++;
			if (header_anim_ticker > 89)
				header_anim_ticker = 0;
		}
		header_sprite.setTexture(credit_textures[header_anim_ticker]);
		header_sprite.setPosition(width/2,height/2);

		window.draw(program_ui_bar);
		window.draw(header_sprite);
		window.draw(program_titlebar);
		window.draw(program_title);
		
		
		//draw the window
		window.setFramerateLimit(60);
		window.display();

#pragma endregion

	}
	//return okay if the program exits properly
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>

#include <SFML/Network.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
//#include <windows.h>
#include <iconv.h>
#include <vector>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <cstring>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//in the standard namespace
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
float version = 2.1;
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




bool check_for_update()
{
    //get username from environment
    char* username = getenv("USERNAME");
    string username_str(username);

    //read version.txt from http://daltonyx.com/loader/version.txt
    //if version.txt is not the same as the version variable, return true
    //else return false

    //download version.txt with curl
    //if in visual studio
    string curl_command;
    if (username_str == "dalto" || username_str == "calli")
        curl_command = "curl http://192.168.1.48:8000/loader/version.txt -o version.txt && curl http://192.168.1.48:8000/loader/changelog.txt -o changelog.txt";
    else
    {
        curl_command = "curl http://97.88.21.85:8000/loader/version.txt -o version.txt && curl http://97.88.21.85:8000/loader/changelog.txt -o changelog.txt";
    }
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

#pragma region steamID_get

struct SteamUser {
	int steamID = 0;
	std::string accountName = "default";
	std::string personaName = "default";
	bool rememberPassword = false;
	bool wantsOfflineMode = false;
	bool skipOfflineModeWarning = false;
	bool allowAutoLogin = false;
	bool mostRecent = false;
	std::string timestamp = "9999999";
};

void parseSteamUsers(std::vector<SteamUser>& users, const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	std::string line;
	SteamUser currentUser;
	bool inUserBlock = false;
	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '/' || line[0] == '\n') {
			// skip comments and empty lines
			continue;
		}
		if (line[0] == '}') {
			// end of user block
			if (inUserBlock) {
				users.push_back(currentUser);
				currentUser = SteamUser();
				inUserBlock = false;
			}
		}
		else if (line[0] == '"') {
			// new key-value pair
			size_t pos = line.find('"', 1);
			if (pos != std::string::npos) { // check if search string was found
				std::string key = line.substr(1, pos - 1);
				if (line.size() > pos + 2) { // check if there is a value to extract
					std::string value = line.substr(pos + 2, line.size() - pos - 3);
					if (key == "AccountName") {
						currentUser.accountName = value;
						cout << value << endl;
					}
					else if (key == "PersonaName") {
						currentUser.personaName = value;
					}
					else if (key == "RememberPassword") {
						currentUser.rememberPassword = (value == "1");
					}
					else if (key == "WantsOfflineMode") {
						currentUser.wantsOfflineMode = (value == "1");
					}
					else if (key == "SkipOfflineModeWarning") {
						currentUser.skipOfflineModeWarning = (value == "1");
					}
					else if (key == "AllowAutoLogin") {
						currentUser.allowAutoLogin = (value == "1");
					}
					else if (key == "MostRecent") {
						currentUser.mostRecent = (value == "1");
					}
					else if (key == "Timestamp") {
						currentUser.timestamp = value;
					}
					else if (key == "steamID") {
						try {
							currentUser.steamID = std::stoi(value);
						}
						catch (const std::invalid_argument& e) {
							std::cerr << "Invalid steamID value: " << value << std::endl;
						}
					}
				}
			}
		}
		else if (line[0] == '{') {
			// start of user block
			inUserBlock = true;
		}
	}

	file.close();
}


void read_vdf(SteamUser steamUser, vector<SteamUser> steamUsers)
{
	//read vdf file
	ifstream vdf_file;
	vdf_file.open("loginusers.vdf");
	string vdf_string;
	string line;
	while (getline(vdf_file, line))
	{
		//if line starts with "
		if (line[0] == '"')
		{
			cout << line << endl;
			//if line contains "PersonaName"
			if (line.find("PersonaName") != string::npos)
			{
				//get the persona name
				size_t pos = line.find('"', 1);
				if (pos != std::string::npos) 
				{ // check if search string was found
					std::string key = line.substr(1, pos - 1);
					if (line.size() > pos + 2) 
					{ // check if there is a value to extract
						std::string value = line.substr(pos + 2, line.size() - pos - 3);
						if (key == "PersonaName")
						{
							cout << "persona found" << endl;
							steamUser.personaName = value;
							cout << value << endl;
						}

					}
				}
			}
		}
		vdf_string += line;
		vdf_string += "\n";
	}
	vdf_file.close();


	//save to log.txt
	ofstream log_file;
	log_file.open("users.txt");
	log_file << vdf_string;
	log_file.close();
}


string get_steam_persona(vector<SteamUser> users)
{
	//return the persona name of the most recent user
	string persona;
	persona = users[0].personaName;

	


	return persona;
}

#pragma endregion




int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "LOAD-R", sf::Style::None);
	sf::Event event;
	srand(time(NULL));
	sf::Image icon;

	if (!icon.loadFromFile("resources/Icon.png"));
	{
		//cout << "icon not found" << endl;
	}
	
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	bool running = true;

	
	vector<SteamUser> users;
	SteamUser user = SteamUser();
	read_vdf(user, users);
	

	

#pragma region VARIABLE_CREATION

	vector<sf::Texture> header_textures;

	if (check_for_update())
	{
		needs_update = true;
	}

	for (int i = 0; i < 90; i++)
	{
		sf::Texture texture;
		texture.loadFromFile("resources/images/loader_" + to_string(i + 1) + ".png");
		header_textures.push_back(texture);
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
	sayings.push_back("bob ross is rude");
	sayings.push_back("can i offer you an egg");
	sayings.push_back("walla walla washington");
	sayings.push_back("blnk says i'm a dick tater");
	sayings.push_back("i love you jen-nay");
	sayings.push_back("jimmy's mom is kinda hot");
	sayings.push_back("willy bum bum");
	sayings.push_back("a cop needed my mouse");
	//sayings.push_back("SKEDADDLE SKIDOODLE YOUR DICK IS A NOODLE");
	sayings.push_back("do ya got any sayings");
	sayings.push_back("two stevens walk into a bar");
	sayings.push_back("and they say ouch");
	sayings.push_back("no lol");
	sayings.push_back("we're gonna need a bigger boat");
	sayings.push_back("welp, that's grounded");
	sayings.push_back("dalton, the dandelion hunter");
	sayings.push_back("Oh, you're finally awake");
	sayings.push_back("noot, noot never changes");
	sayings.push_back("this is an uwu free zone");
	sayings.push_back("uwu");
	sayings.push_back("SS LAKEWATER - n3vr 4get");
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
	
	vector<Button> buttons;
	buttons.push_back(Button(sf::Vector2f(width-15, 15), sf::Vector2f(30, 30), sf::Color(10,10,10), sf::Color::White, "X", 10, true));
	buttons.push_back(Button(sf::Vector2f(150, 80), sf::Vector2f(250, 50), sf::Color(30, 30, 30, 0), sf::Color(220, 220, 220), "HOME", 50, false));
	buttons.push_back(Button(sf::Vector2f(150, 150), sf::Vector2f(250, 50), sf::Color(30, 30, 30, 0), sf::Color(220,220,220), "PATCHES", 50, false));
	buttons.push_back(Button(sf::Vector2f(150, 220), sf::Vector2f(250, 50), sf::Color(30, 30, 30, 0), sf::Color(220, 220, 220), "LOADERS", 50, false));
	buttons.push_back(Button(sf::Vector2f(150, 730), sf::Vector2f(250, 50), sf::Color(30, 30, 30, 0), sf::Color(220, 220, 220), "OPTIONS", 50, false));

	vector<DisplayBox> display_boxes;
	display_boxes.push_back(DisplayBox(sf::Vector2f(632, 415), sf::Vector2f(600, 730), sf::Color(30, 30, 30)));
	display_boxes.push_back(DisplayBox(sf::Vector2f(632, 1215), sf::Vector2f(600, 730), sf::Color(30, 30, 30), "GAMES"));
	display_boxes.push_back(DisplayBox(sf::Vector2f(632, 2015), sf::Vector2f(600, 730), sf::Color(30, 30, 30), "OTHER LAUNCHERS"));
	//string steamPersona = get_steam_persona(users);
	display_boxes.push_back(DisplayBox(sf::Vector2f(632, 2815), sf::Vector2f(600, 730), sf::Color(30, 30, 30),  "'S SETTINGS"));

	vector<DisplayBox> info_boxes;
	info_boxes.push_back(DisplayBox(sf::Vector2f(1268, 415), sf::Vector2f(600, 730), sf::Color(30, 30, 30)));
	info_boxes.push_back(DisplayBox(sf::Vector2f(1268, -385), sf::Vector2f(600, 730), sf::Color(30, 30, 30)));
	info_boxes.push_back(DisplayBox(sf::Vector2f(1268, -1185), sf::Vector2f(600, 730), sf::Color(30, 30, 30)));
	info_boxes.push_back(DisplayBox(sf::Vector2f(1268, -1985), sf::Vector2f(600, 730), sf::Color(30, 30, 30)));

	sf::RectangleShape info_box_display;
	info_box_display.setSize(sf::Vector2f(575,575));
	info_box_display.setFillColor(sf::Color(255,255,255));
	info_box_display.setOrigin(sf::Vector2f(287.5, 287.5));
	info_box_display.setPosition(info_boxes[1].position.x, info_boxes[1].position.y-100);

	sf::RectangleShape info_box_display2;
	info_box_display2.setSize(sf::Vector2f(575, 575));
	info_box_display2.setFillColor(sf::Color(255, 255, 255));
	info_box_display2.setOrigin(sf::Vector2f(287.5, 287.5));
	info_box_display2.setPosition(info_boxes[2].position.x, info_boxes[2].position.y - 100);


	vector<Button> patches_games;
	vector<Button> launchers_games;

	sf::Texture texture_valheim;
	texture_valheim.loadFromFile("resources/images/valheim.png");
	patches_games.push_back(Button(sf::Vector2f(display_boxes[1].position.x-190, display_boxes[1].position.y-300), sf::Vector2f(180, 50), sf::Color(30, 30, 30), sf::Color(220, 220, 220), "VALHEIM", 30, true));
	info_box_display.setTexture(&texture_valheim);

	sf::Texture texture_raft;
	texture_raft.loadFromFile("resources/images/raft.png");
	patches_games.push_back(Button(sf::Vector2f(display_boxes[1].position.x, display_boxes[1].position.y - 300), sf::Vector2f(180, 50), sf::Color(30, 30, 30), sf::Color(220, 220, 220), "RAFT", 30, true));
	
	
	sf::Texture texture_grounded;
	texture_grounded.loadFromFile("resources/images/grounded.png");
	patches_games.push_back(Button(sf::Vector2f(display_boxes[1].position.x + 190, display_boxes[1].position.y - 300), sf::Vector2f(180, 50), sf::Color(30, 30, 30), sf::Color(220, 220, 220), "GROUNDED", 30, true));
	
	sf::Texture texture_skyrim;
	texture_skyrim.loadFromFile("resources/images/skyrim.png");
	patches_games.push_back(Button(sf::Vector2f(display_boxes[1].position.x - 190, display_boxes[1].position.y - 200), sf::Vector2f(180, 50), sf::Color(30, 30, 30), sf::Color(220, 220, 220), "SKYRIM", 30, true));

	sf::Texture texture_dinkum;
	texture_dinkum.loadFromFile("resources/images/dinky.jpg");
	patches_games.push_back(Button(sf::Vector2f(display_boxes[1].position.x - 190, display_boxes[1].position.y - 50), sf::Vector2f(180, 50), sf::Color(30, 30, 30), sf::Color(220, 220, 220), "DINKUM", 30, true));


	sf::Texture texture_nexus;
	texture_nexus.loadFromFile("resources/images/nexus.png");
	launchers_games.push_back(Button(sf::Vector2f(display_boxes[2].position.x - 190, display_boxes[2].position.y - 300), sf::Vector2f(180, 50), sf::Color(30, 30, 30), sf::Color(220, 220, 220), "NEXUS", 30, true));

	sf::Texture texture_thunderstore;
	texture_thunderstore.loadFromFile("resources/images/thunderstore.png");
	launchers_games.push_back(Button(sf::Vector2f(display_boxes[2].position.x, display_boxes[2].position.y - 300), sf::Vector2f(180, 50), sf::Color(30, 30, 30), sf::Color(220, 220, 220), "T-STORE", 30, true));
	
	sf::Texture texture_raftml;
	texture_raftml.loadFromFile("resources/images/raftml.png");
	launchers_games.push_back(Button(sf::Vector2f(display_boxes[2].position.x + 190, display_boxes[2].position.y - 300), sf::Vector2f(180, 50), sf::Color(30, 30, 30), sf::Color(220, 220, 220), "RAFTML", 30, true));

	vector<Button> info_box_buttons;
	info_box_buttons.push_back(Button(sf::Vector2f(info_boxes[1].position.x, info_boxes[1].position.y + 200), sf::Vector2f(580, 100), sf::Color(220, 220, 220), sf::Color(30, 30, 30), "PATCH GAME", 30, true));
	info_box_buttons.push_back(Button(sf::Vector2f(info_boxes[2].position.x, info_boxes[2].position.y + 200), sf::Vector2f(580, 100), sf::Color(220, 220, 220), sf::Color(30, 30, 30), "LAUNCH BROWSER", 30, true));
	
	sf::Sprite header_sprite;
	header_sprite.setTexture(header_textures[0]);
	header_sprite.setOrigin(header_sprite.getGlobalBounds().width / 2, header_sprite.getGlobalBounds().height / 2);
	header_sprite.setPosition(display_boxes[0].position.x,display_boxes[0].position.y);

	sf::Text version_text;
	version_text.setFont(font);
	//make sure there are only 2 decimal places in version, for example: 1.44	
	version_text.setString("v" + to_string(version).substr(0, to_string(version).find('.') + 3));
	/*version_text.setString("v" + std::to_string(version));*/
	version_text.setCharacterSize(30);
	version_text.setFillColor(sf::Color(220, 220, 220));
	//origin
	version_text.setStyle(sf::Text::Bold);
	version_text.setOrigin(version_text.getGlobalBounds().width / 2, version_text.getGlobalBounds().height / 2);
	version_text.setPosition(display_boxes[0].position.x, display_boxes[0].position.y+300);

	//set info_display_box2 to nexus
	info_box_display2.setTexture(&texture_nexus);

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

	sf::Text changelog_text;
	changelog_text.setFont(font);
	changelog_text.setCharacterSize(16);
	changelog_text.setFillColor(sf::Color::White);
	changelog_text.setString(changelog_string);
	changelog_text.setOrigin(changelog_text.getGlobalBounds().width / 2, 0);
	changelog_text.setPosition(info_boxes[0].position.x, info_boxes[0].position.y-info_boxes[0].size.y/2);

	sf::Text saying;
	saying.setFont(font);
	int sayings_chance = rand() % sayings.size();
	string saying_string = sayings[sayings_chance];
	transform(saying_string.begin(), saying_string.end(), saying_string.begin(), ::toupper);
	saying.setString(saying_string);
	saying.setCharacterSize(30);
	saying.setStyle(sf::Text::Bold);
	saying.setFillColor(sf::Color::White);
	saying.setOutlineColor(sf::Color::Black);
	saying.setOutlineThickness(1);
	saying.setOrigin(saying.getGlobalBounds().width / 2, saying.getGlobalBounds().height / 2);
	saying.setPosition(display_boxes[0].position.x, display_boxes[0].position.y);


#pragma endregion

	while (running)
	{

#pragma region EVENT_HANDLING
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
				window.close();
			}
			//mouse click handling
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
					running = false;
					window.close();
				}
			}
		}

		if (windowheld)
			window.setPosition(sf::Mouse::getPosition() - sf::Vector2i(window.getSize().x / 2, 25));

		//button click handling
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].update(window);
			if (buttons[i].clicked)
			{
				switch (i)
				{
				case 0: // x button
					running = false;
					window.close();
					break;

					
				case 1: // home button
					//set all display boxes to original_y
					for (int i = 0; i < display_boxes.size(); i++)
					{
						display_boxes[i].desired_y = display_boxes[i].original_y;
						
					}
					//set all info boxes to original_y
					for (int i = 0; i < info_boxes.size(); i++)
					{
						info_boxes[i].desired_y = info_boxes[i].original_y;
					}
					state = 0;
					substate = 0;
					
					break;

					
				case 2: // patches button
					//set all display boxes to original_y-800
					for (int i = 0; i < display_boxes.size(); i++)
					{
						display_boxes[i].desired_y = display_boxes[i].original_y - 800;
					}
					//set all info boxes to original_y+800
					for (int i = 0; i < info_boxes.size(); i++)
					{
						info_boxes[i].desired_y = info_boxes[i].original_y + 800;
					}
					state = 1;
					substate = 0;
					//set to valheim texture
					info_box_display.setTexture(&texture_valheim);
					break;

					
				case 3: // loaders button
					//set all display boxes to original_y-1600
					for (int i = 0; i < display_boxes.size(); i++)
					{
						display_boxes[i].desired_y = display_boxes[i].original_y - 1600;
					}
					//set all info boxes to original_y+1600
					for (int i = 0; i < info_boxes.size(); i++)
					{
						info_boxes[i].desired_y = info_boxes[i].original_y + 1600;
					}
					state = 2;
					substate = 0;
					info_box_display2.setTexture(&texture_nexus);
					break;

					
				case 4: // options button
					//set all display boxes to original_y-2400
					for (int i = 0; i < display_boxes.size(); i++)
					{
						display_boxes[i].desired_y = display_boxes[i].original_y - 2400;
					}
					//set all info boxes to original_y+2400
					for (int i = 0; i < info_boxes.size(); i++)
					{
						info_boxes[i].desired_y = info_boxes[i].original_y + 2400;
					}
					state = 3;
					substate = 0;
					break;
				}
			}
		}

		//switch statement to handle clicks from patches_games
		for (int i = 0; i < patches_games.size(); i++)
		{
			patches_games[i].update(window);
			if (patches_games[i].clicked)
			{
				switch (i)
				{
				case 0: // valheim button
					substate = 0;
					info_box_display.setTexture(&texture_valheim);
					break;

				case 1: // raft button
					substate = 1;
					info_box_display.setTexture(&texture_raft);
					break;

				case 2: // grounded button
					substate = 2;
					info_box_display.setTexture(&texture_grounded);
					break;

				case 3: // skyrim button
					substate = 3;
					info_box_display.setTexture(&texture_skyrim);
					break;
				
				case 4: //dinkum button
					substate = 4;
					info_box_display.setTexture(&texture_dinkum);
					break;
				
				
				
				
				}
			}
		}

		//switch statement to handle clicks from loaders_games
		for (int i = 0; i < launchers_games.size(); i++)
		{
			launchers_games[i].update(window);
			if (launchers_games[i].clicked)
			{
				switch (i)
				{
				case 0: // nexusmods button
					substate = 0;
					info_box_display2.setTexture(&texture_nexus);
					break;

				case 1: // thunderstore button
					substate = 1;
					info_box_display2.setTexture(&texture_thunderstore);
					break;

				case 2: // raftml button
					substate = 2;
					info_box_display2.setTexture(&texture_raftml);
					break;

				






				}
			}
		}

		//switch statement to handle clicks from info_box_buttons
		for (int i = 0; i < info_box_buttons.size(); i++)
		{
			info_box_buttons[i].update(window);
			if (info_box_buttons[i].clicked)
			{
				switch (i)
				{
				case 0: // patch button
					//if substate is 0:
					if (substate == 0)
					{
						string command = "python resources/scripts/valheim_modloader.py";
						run_command(command);
						//change button to say "Done!"
						info_box_buttons[i].text_string = "Done!";
					}
					//if substate is 1:
					if (substate == 1)
					{
						string command = "python resources/scripts/raft_modloader.py";
						run_command(command);
						info_box_buttons[i].text_string = "Done!";
					}
					//if substate is 2:
					if (substate == 2)
					{
						string command = "python resources/scripts/grounded_modloader.py";
						run_command(command);
						info_box_buttons[i].text_string = "Done!";
					}
					//if substate is 3:
					if (substate == 3)
					{
						string command = "python resources/scripts/skyrim_modloader.py";
						run_command(command);
						info_box_buttons[i].text_string = "Done!";
					}
					//if substate is 4:
					if (substate == 4)
					{
						string command = "python resources/scripts/dinkum_modloader.py";
						run_command(command);
						info_box_buttons[i].text_string = "Done!";
					}
					break;
				case 1: //open browser button
					//if substate is 0:
					if (substate == 0)
					{
						string command = "start https://www.nexusmods.com/about/vortex/";
						run_command(command);
					}
					//if substate is 1:
					if (substate == 1)
					{
						string command = "start https://www.overwolf.com/app/Thunderstore-Thunderstore_Mod_Manager";
						run_command(command);
					}
					//if substate is 2:
					if (substate == 2)
					{
						string command = "start https://www.raftmodding.com/download";
						run_command(command);
					}
					
					break;
					
				}
			}
		}


#pragma endregion
		
#pragma region DISPLAY_LOOP
		//clear the window
		window.clear();
		version_text.setPosition(display_boxes[0].position.x, display_boxes[0].position.y + 300);
		header_ticker++;
		if (header_ticker > 1)
		{
			header_ticker = 0;
			header_anim_ticker++;
			if (header_anim_ticker > 89)
				header_anim_ticker = 0;
		}
		header_sprite.setTexture(header_textures[header_anim_ticker]);
		
		for (int i = 0; i < display_boxes.size(); i++)
		{
			display_boxes[i].update();
			display_boxes[i].draw(window, font);
		}
		changelog_text.setPosition(info_boxes[0].position.x, info_boxes[0].position.y - info_boxes[0].size.y / 2 + 20);
		
		for (int i = 0; i < info_boxes.size(); i++)
		{
			info_boxes[i].update();
			info_boxes[i].draw(window, font);
		}

		//make sure all buttons in patches_games stay relative to the same display box
		for (int i = -1; i < 2; i++)
		{
			patches_games[i+1].position = sf::Vector2f(display_boxes[1].position.x + (i * 190), display_boxes[1].position.y - 200);
			patches_games[i + 1].set_position(sf::Vector2f(display_boxes[1].position.x + (i * 190), display_boxes[1].position.y - 200));
		}
		patches_games[3].position = sf::Vector2f(display_boxes[1].position.x + (-1 * 190), display_boxes[1].position.y - 100);
		patches_games[3].set_position(sf::Vector2f(display_boxes[1].position.x + (-1 * 190), display_boxes[1].position.y - 100));

		patches_games[4].position = sf::Vector2f(display_boxes[1].position.x + (0 * 190), display_boxes[1].position.y - 100);
		patches_games[4].set_position(sf::Vector2f(display_boxes[1].position.x + (0 * 190), display_boxes[1].position.y - 100));

		//make sure all buttons in info_box_buttons stay relative to the same display box
		for (int i = -1; i < 2; i++)
		{
			info_box_buttons[i + 1].position = sf::Vector2f(info_boxes[i+2].position.x, info_boxes[i+2].position.y + 300);
			info_box_buttons[i + 1].set_position(sf::Vector2f(info_boxes[i + 2].position.x, info_boxes[i + 2].position.y + 300));
		}
		
		//make sure all buttons in launchers_games stay relative to the same display box
		for (int i = -1; i < 2; i++)
		{
			launchers_games[i + 1].position = sf::Vector2f(display_boxes[2].position.x + (i * 190), display_boxes[2].position.y - 200);
			launchers_games[i + 1].set_position(sf::Vector2f(display_boxes[2].position.x + (i * 190), display_boxes[2].position.y - 200));
		}
		
		//make sure info_box_display stays in the same place as the info_box
		info_box_display.setPosition(sf::Vector2f(info_boxes[1].position.x, info_boxes[1].position.y -60));
		saying.setPosition(display_boxes[0].position.x, display_boxes[0].position.y);
		
		//make sure info_box_display2 stays in the same place as the info_box
		info_box_display2.setPosition(sf::Vector2f(info_boxes[2].position.x, info_boxes[2].position.y - 60));
		window.draw(saying);
		window.draw(version_text);
		window.draw(program_ui_bar);

		
		
		for (int i = 0; i < patches_games.size(); i++)
		{
			if (i == substate)
				patches_games[i].color = sf::Color(50, 50, 50);
			else
				patches_games[i].color = sf::Color(30, 30, 30);
			
			patches_games[i].update(window);
			patches_games[i].draw(window);
		}

		for (int i = 0; i < info_box_buttons.size(); i++)
		{
			info_box_buttons[i].update(window);
			info_box_buttons[i].draw(window);
		}

		for (int i = 0; i < launchers_games.size(); i++)
		{
			if (i == substate)
				launchers_games[i].color = sf::Color(50, 50, 50);
			else
				launchers_games[i].color = sf::Color(30, 30, 30);

			launchers_games[i].update(window);
			launchers_games[i].draw(window);
		}
		
		header_sprite.setPosition(display_boxes[0].position.x, display_boxes[0].position.y-200);
		window.draw(header_sprite);
		window.draw(info_box_display);
		window.draw(info_box_display2);
		window.draw(changelog_text);
		window.draw(program_titlebar);
		window.draw(program_title);
		
		for (int i = 0; i < buttons.size(); i++)
		{
			if (i == state+1)
				buttons[i].color = sf::Color(50, 50, 50);
			else
				buttons[i].color = sf::Color(20,20,20);
			//buttons[i].update(window);
			buttons[i].draw(window);
		}
		
		//draw the window
		window.setFramerateLimit(60);
		window.display();

#pragma endregion

	}
	//return okay if the program exits properly
    return 0;
}
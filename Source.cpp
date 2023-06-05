#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//in the standard namespace
using namespace std;

//variables
const int width{ 800 };
const int height{ 800 };


int main()
{
	//set up window
	sf::RenderWindow window(sf::VideoMode(width, height), "daltonyx");
	sf::Event event;
	sf::Image icon;
	icon.loadFromFile("Icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	
	//look for events while the window is open
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}
		//clear the window
		window.clear();
		
		

		//draw the window
		window.display();
	}
	//return okay if the program exits properly
    return 0;
}
#include <SFML/Graphics.hpp>
#include "Map.h"

class View
{
public:
	View(Map* map, sf::RenderWindow& window);
	~View();
	void update();
public:
	sf::View view;
	Map* map;
	sf::RenderWindow *window;

};


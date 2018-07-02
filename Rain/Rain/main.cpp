#include<SFML/Graphics.hpp>
#include<random>
float map(float, float, float, float, float);

static std::random_device rd;
static std::mt19937 rng(rd());
int randomizator(int a, int b) {
	std::uniform_int_distribution<int>uid(a, b); // not static
	return uid(rng);
}

class drop :public sf::RectangleShape {
	float x;
	float y;
	float z;
	float yspeed;
public:
	drop();
	void fall();
};
drop::drop() {
	this->x = randomizator(0, 600);//rand() % 600;
	this->y = randomizator(300, 500);//rand() % (500 - 300) + 300;
	this->z = randomizator(1, 10);//rand() % 10 + 1;
	this->yspeed = map(this->z, 1, 10, 5, 15);//rand() % (15 - 5) + 5;//5;//2
	this->setSize(sf::Vector2f(4, 30));
	//this->setFillColor(sf::Color(138, 43, 226));
	this->setFillColor(sf::Color(0, 173, 181));
	this->setScale(sf::Vector2f(map(this->z, 1, 10, 0.3, 0.8), map(this->z, 1, 10, 0.3, 0.8)));
	this->setPosition(this->x, -this->y);
}
void drop::fall() {
	this->move(0, yspeed);
	if (this->getPosition().y > 500)
	{
		this->z = randomizator(1, 10); //rand() % 10 + 1;
		this->yspeed = map(this->z, 1, 10, 5, 15);
		this->y = randomizator(200, 500);//rand() % (500 - 300) + 200;
		this->setScale(sf::Vector2f(map(this->z, 1, 10, 0.3, 0.8), map(this->z, 1, 10, 0.3, 0.8)));
		this->setPosition(this->x, -this->y);
	}
}
int main() {
	sf::RenderWindow window(sf::VideoMode(600, 500), "Raining", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	drop drops[300];
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				window.close();
		}
		//window.clear(sf::Color(230,230,250));
		window.clear(sf::Color(57, 62, 70));
		for (int i = 0; i < 300; i++)
		{
			drops[i].fall();
			window.draw(drops[i]);
		}	window.display();
	}
	return 0;
}
float map(float value, float start1, float stop1, float start2, float stop2) {
	return start2 + (stop2 - start2)*((value - start1) / (stop1 - start1));
}
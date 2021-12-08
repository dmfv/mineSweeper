#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <SFML/Graphics.hpp>

/* TODO:
 * 
 * 1. add win condition
 * 2. add flag click blocking (can't change flag state with using left click only right)
 * 3. add ... some features (score, external frame, different themes)
 * 
 * 
 */ 

const int tileSizeX = 40;
const int tileSizeY = 40;
const int numberOfTileX = 10;
const int numberOfTileY = 10;
const int width = numberOfTileY * tileSizeY;
const int height = numberOfTileY * tileSizeY;

const int numberOfBombs = 10;

sf::Texture textureTileNotPressed{};
sf::Texture textureTilePressed{};
sf::Texture textureBombNotPressed{};
sf::Texture textureBombPressed{};
sf::Texture textureFlag{};
sf::Texture textureDig1{};
sf::Texture textureDig2{};
sf::Texture textureDig3{};
sf::Texture textureDig4{};
sf::Texture textureDig5{};
sf::Texture textureDig6{};
sf::Texture textureDig7{};
sf::Texture textureDig8{};
sf::Texture textureDig9{};

enum class TileState {
	bomb = -3,
	flag = -2,
	clicked = -1,
	Dig0 = 0,
	Dig1,
	Dig2,
	Dig3,
	Dig4,
	Dig5,
	Dig6,
	Dig7,
	Dig8,
	Dig9,
};



class MySprite : public sf::Sprite {
public:
	MySprite(TileState tileStateVar = TileState::Dig0)
		: tileState(tileStateVar)
	{
		;
	}
	~MySprite() { ; }

	void setTexture(sf::Texture& newTexture, TileState newTileState = TileState::Dig0) {
		tileState = newTileState;
		sf::Sprite::setTexture(newTexture);
	}

	void setBomb(void) {
		tileState = TileState::bomb;
	}
	int setNumberOfBombAround(int numberOfBombVar) {
		assert(numberOfBombVar < 10 && "number of bomb can't be more than 9");
		tileState = static_cast <TileState> (numberOfBombVar);
	}
	void increaseNumberOfBombAround(void) {
		std::cout << static_cast <int> (tileState) << std::endl;
		switch (tileState) {
		case TileState::Dig0: tileState = TileState::Dig1; break;
		case TileState::Dig1: tileState = TileState::Dig2; break;
		case TileState::Dig2: tileState = TileState::Dig3; break;
		case TileState::Dig3: tileState = TileState::Dig4; break;
		case TileState::Dig4: tileState = TileState::Dig5; break;
		case TileState::Dig5: tileState = TileState::Dig6; break;
		case TileState::Dig6: tileState = TileState::Dig7; break;
		case TileState::Dig7: tileState = TileState::Dig8; break;
		case TileState::Dig8: tileState = TileState::Dig9; break;
		case TileState::Dig9: assert(false && "error number of bomb can't be more than 9"); break;
		default: assert(false && "error number of bomb can't be more than 9"); break;
		}
		assert(static_cast <int> (tileState) < 10 && "number of bomb can't be more than 9");
	}
	int getNumberOfBombAround(void) {
		return static_cast <int> (tileState);
	}
	bool isBomb(void) {
		if (tileState == TileState::bomb) {
			return true;
		}
		return false;
	}
	bool isClicked(void) {
		if (tileState == TileState::clicked) {
			return true;
		}
		return false;
	}
	bool isFlag(void) {
		if (tileState == TileState::flag) {
			return true;
		}
		return false;
	}
private:
	TileState tileState;
	//int numberOfBombAround;
};


void clickOnTile		 (std::vector <std::vector <MySprite>>& spriteArray, int x, int y);
void checkForNoBombsTiles(std::vector <std::vector <MySprite>>& spriteArray, int x, int y);


void checkForNoBombsTiles(std::vector <std::vector <MySprite>> & spriteArray, int x, int y) {
	for (int i = -1; i < 2; i++) {
		int new_x = x + i;
		for (int j = -1; j < 2; j++) {
			int new_y = y + j;
			if ((new_x > -1 && new_y > -1) and (new_x < numberOfTileX && new_y < numberOfTileY)) {
				MySprite& clickedTile = spriteArray.at(new_x).at(new_y);
				if (clickedTile.isClicked() == false and clickedTile.isBomb() == false) {
					clickOnTile(spriteArray, new_x, new_y);
				}
			}
		}
	}
}

void clickOnTile(std::vector <std::vector <MySprite>>& spriteArray, int x, int y) {
	MySprite& clickedTile = spriteArray.at(x).at(y);
	switch (clickedTile.getNumberOfBombAround()) {
		case 0:
			clickedTile.setTexture(textureTilePressed, TileState::clicked);
			checkForNoBombsTiles(spriteArray, x, y);
			break;
		case 1: clickedTile.setTexture(textureDig1, TileState::clicked);		break;
		case 2: clickedTile.setTexture(textureDig2, TileState::clicked);		break;
		case 3: clickedTile.setTexture(textureDig3, TileState::clicked);		break;
		case 4: clickedTile.setTexture(textureDig4, TileState::clicked);		break;
		case 5: clickedTile.setTexture(textureDig5, TileState::clicked);		break;
		case 6: clickedTile.setTexture(textureDig6, TileState::clicked);		break;
		case 7: clickedTile.setTexture(textureDig7, TileState::clicked);		break;
		case 8: clickedTile.setTexture(textureDig8, TileState::clicked);		break;
		case 9: clickedTile.setTexture(textureDig9, TileState::clicked);		break;
		default: std::cout << "Wrong Number of bomb " << clickedTile.getNumberOfBombAround() << std::endl;
	}
}

void addNumbersOnField(std::vector <std::vector <MySprite>>& spriteArray, int numberOfBombsToAdd) {
	for (int i = 0; i < numberOfBombsToAdd; i++) {
		int x = rand() % numberOfBombsToAdd;
		int y = rand() % numberOfBombsToAdd;
		spriteArray.at(x).at(y).setBomb();
		for (int i = -1; i < 2; i++) {
			int new_x = x + i;
			for (int j = -1; j < 2; j++) {
				int new_y = y + j;
				if ((new_x > -1 && new_y > -1) and (new_x < numberOfTileX && new_y < numberOfTileY) and (new_x != x and new_y != y)) {
					spriteArray.at(new_x).at(new_y).increaseNumberOfBombAround();
				}
			}
		}
	}
}

int main() {
	srand(time(NULL));
	bool gameStarted = false;
	bool buttonAlreadyPressed = false;
	sf::Event event;

	textureTileNotPressed.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 0, 40, 40));
	textureTilePressed.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 40, 80, 80));
	textureBombNotPressed.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 80, 120, 120));
	textureBombPressed.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 120, 160, 160));
	textureFlag.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 160, 200, 200));
	textureDig1.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 200, 240, 240));
	textureDig2.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 240, 280, 280));
	textureDig3.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 280, 320, 320));
	textureDig4.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 320, 360, 360));
	textureDig5.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 360, 400, 400));
	textureDig6.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 400, 440, 440));
	textureDig7.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 440, 480, 480));
	textureDig8.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 480, 520, 520));
	textureDig9.loadFromFile("xTEXTURES/textures.png", sf::IntRect(0, 520, 560, 560));
	
	std::vector <std::vector <MySprite>> spriteArray{};
	for (int i = 0; i < numberOfTileX; i++) {
		spriteArray.push_back(std::vector <MySprite> {});
		for (int j = 0; j < numberOfTileY; j++) {
			spriteArray.at(i).push_back(MySprite {});
			spriteArray.at(i).at(j).setPosition(static_cast<float>(j) * tileSizeX, static_cast<float>(i) * tileSizeY);
			spriteArray.at(i).at(j).setTexture(textureTileNotPressed);
		}
	}
	addNumbersOnField(spriteArray, numberOfBombs);

	for (int i = 0; i < numberOfTileX; i++) {
		for (int j = 0; j < numberOfTileY; j++) {
			if (spriteArray.at(i).at(j).isBomb()) {
				std::cout << "! ";
			}
			else {
				std::cout << spriteArray.at(i).at(j).getNumberOfBombAround() << " ";
			}
		}
		std::cout << '\n';
	}


	// Объект, который, собственно, является главным окном приложения
	sf::RenderWindow window(sf::VideoMode(width, height), "MineSweeper");

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == sf::Event::Closed)
				// тогда закрываем его
				window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (gameStarted == false) {
				gameStarted = true;
			}
			if (event.mouseButton.button == sf::Mouse::Left and buttonAlreadyPressed == false) {
				buttonAlreadyPressed = true;
				//std::cout << "the right button was pressed" << std::endl;
				//std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				//std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				int row    = event.mouseButton.x / tileSizeX;
				int column = event.mouseButton.y / tileSizeY;
				MySprite & clickedTile = spriteArray.at(column).at(row);
				if (clickedTile.isBomb()) {
					std::cout << "BOOOOM" << std::endl;
					clickedTile.setTexture(textureBombPressed);
				}
				else {
					clickOnTile(spriteArray, column, row);
				}
			} 
			else if (event.mouseButton.button == sf::Mouse::Right and buttonAlreadyPressed == false) {
				buttonAlreadyPressed = true;
				int row = event.mouseButton.x / tileSizeX;
				int column = event.mouseButton.y / tileSizeY;
				spriteArray.at(column).at(row).setTexture(textureFlag);
			}
		} 
		else if (event.type == sf::Event::MouseButtonReleased) {
			buttonAlreadyPressed = false;
		}

		window.clear(sf::Color(10, 20, 150));
		
		for (auto i: spriteArray) {
			for (auto j : i) {
				window.draw(j);
			}
		}

		// Отрисовка окна	
		window.display();
	}

	return 0;
}
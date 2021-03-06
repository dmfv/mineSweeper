#include "main.h"


/* TODO:
 * 
 * 1. add win condition
 * 2. add flag click blocking (can't change flag state with using left click only right)
 * 3. add ... some features (score, external frame, different themes)
 * 
 * 
 */ 


void addSpritesToVector(std::vector <std::vector <MySprite>>& spriteArray) {
	for (int i = 0; i < numberOfTileX; i++) {
		spriteArray.push_back(std::vector <MySprite> {});
		for (int j = 0; j < numberOfTileY; j++) {
			spriteArray.at(i).push_back(MySprite{});
			spriteArray.at(i).at(j).setPosition(static_cast<float>(j) * tileSizeX, static_cast<float>(i) * tileSizeY);
			spriteArray.at(i).at(j).setTexture(textureTileNotPressed);
		}
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
				if ((new_x > -1 && new_y > -1) and (new_x < numberOfTileX && new_y < numberOfTileY)) {
					spriteArray.at(new_x).at(new_y).increaseNumberOfBombAround();
				}
			}
		}
	}
}

void printFieldMap(std::vector <std::vector <MySprite>>& spriteArray) {
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
}

void congratulations(void) {
	std::cout << "congratulations!" << std::endl;
}


void checkForNoBombsTiles(std::vector <std::vector <MySprite>>& spriteArray, int x, int y) {
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
	numberOfNotBombTiles--;
	if (numberOfNotBombTiles == 0) {
		congratulations();
	}
}

void loadTexture(void) {
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
}


int main() {
	srand(time(NULL));
	bool gameStarted = false;
	bool buttonAlreadyPressed = false;
	sf::Event event;

	loadTexture();

	std::vector <std::vector <MySprite>> spriteArray{};
	addSpritesToVector(spriteArray);
	addNumbersOnField(spriteArray, numberOfBombs);
	printFieldMap(spriteArray);

	// ??????, ???????, ??????????, ???????? ??????? ????? ??????????
	sf::RenderWindow window(sf::VideoMode(width, height), "MineSweeper");
	
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.mouseButton.button == sf::Mouse::Left or event.mouseButton.button == sf::Mouse::Right) {
			gameStarted = true;

			break;
		}
	}
	// ??????? ???? ??????????. ???????????, ???? ??????? ????
	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			// ???????????? ????? ?? ????????? ? ????? ??????? ?????
			if (event.type == sf::Event::Closed)
				// ????? ????????? ???
				window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left and buttonAlreadyPressed == false) {
				buttonAlreadyPressed = true;
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
				MySprite& clickedTile = spriteArray.at(column).at(row);
				if (clickedTile.isClicked() == false) {
					clickedTile.setTexture(textureFlag, TileState::clicked);
				}
				else if (clickedTile.isFlag() == true) {
					clickedTile.setTexture(textureTileNotPressed, TileState::Dig0);
				}
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

		// ????????? ????	
		window.display();
	}

	return 0;
}
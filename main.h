#pragma once
 
#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
#include <SFML/Graphics.hpp>


const int tileSizeX = 40;
const int tileSizeY = 40;
const int numberOfTileX = 10;
const int numberOfTileY = 10;
const int width = numberOfTileY * tileSizeY;
const int height = numberOfTileY * tileSizeY;

const int numberOfBombs = 10;
int  numberOfNotBombTiles = numberOfTileX * numberOfTileY - numberOfBombs;


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


class MySprite : public sf::Sprite {
public:
	MySprite(TileState tileStateVar = TileState::Dig0, int numberOfBombAroundVar = 0)
		: tileState(tileStateVar), numberOfBombAround(numberOfBombAroundVar)
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
		assert(numberOfBombAround < 10 && "number of bomb can't be more than 9");
		numberOfBombAround = numberOfBombVar;
	}
	void increaseNumberOfBombAround(void) {
		numberOfBombAround++;
		assert(numberOfBombAround < 10 && "number of bomb can't be more than 9");
	}
	int getNumberOfBombAround(void) {
		return numberOfBombAround;
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
	int numberOfBombAround;
};


void addSpritesToVector(std::vector <std::vector <MySprite>>& spriteArray);
void addNumbersOnField(std::vector <std::vector <MySprite>>& spriteArray, int numberOfBombsToAdd);
void printFieldMap(std::vector <std::vector <MySprite>>& spriteArray);

void clickOnTile(std::vector <std::vector <MySprite>>& spriteArray, int x, int y);
void checkForNoBombsTiles(std::vector <std::vector <MySprite>>& spriteArray, int x, int y);
void congratulations(void);

void loadTexture(void);
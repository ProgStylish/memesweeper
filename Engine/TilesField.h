#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <random>
class TilesField {
private:
	class Tile {
	public:
		enum class State {
			Hidden, Revealed, Flagged
		};
		void draw(const Vei2& position, int xPositionOnScreen, int yPositionOnScreen, Graphics& gfx) const;
		bool isMined() const;
		void setMined(bool mined);
		void reveal();
		void flag();
		void setMinesNumber(int minesNumber);
		bool isExploited() const;
		void exploit();
		State getState() const;
		void unFlag();
	private:
		bool mined = false;
		bool exploited = false;
		int minesNumber;
		State state = State::Hidden;
	};
public:
	TilesField(int minesNumber, int width, int height);
	void draw(Graphics& gfx) const;
	void revealTile(Vei2& positionInPixels);
	void revealNeighboursTiles(const Vei2 tilePosition);
	void revealMinedTiles();
	void flagTile(Vei2& positionInPixels);
private:
	//Functions
	Tile& getTileAt(const Vei2& positionInTiles);
	const Tile& getTileAt(const Vei2& positionInTiles) const;
	void assignTailsNumbers();
	void revealAll();
	int getMinesSurroundingNumber(const Vei2& positionInTiles) const;
	//Variables
	bool fuckedUp = false;
	int revealedTilesCounter = 0;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> horizontalRange;
	std::uniform_int_distribution<int> verticalRange;
	const int minesNumber;
	int fieldWidthInTiles;
	int fieldHeightInTiles;
	const int xPositionOnScreen = Graphics::ScreenWidth / 2 - (fieldWidthInTiles * SpriteCodex::tileSize)/2;
	const int yPositionOnScreen = Graphics::ScreenHeight / 2 - (fieldHeightInTiles * SpriteCodex::tileSize)/2;
	const int playableWestXPosition = xPositionOnScreen + SpriteCodex::tileSize;
	const int playableEastXPosition = xPositionOnScreen + (fieldWidthInTiles-1)*SpriteCodex::tileSize;
	const int playableNorthyPosition = yPositionOnScreen + SpriteCodex::tileSize;
	const int playableSouthyPosition = yPositionOnScreen + (fieldHeightInTiles-1)*SpriteCodex::tileSize;
	Tile* tilesArray = nullptr;
};
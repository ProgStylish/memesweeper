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
		void draw(const Vei2& position, Graphics& gfx) const;
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
	TilesField(int minesNumber);
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
	static constexpr int fieldWidthInTiles = 6;
	static constexpr int fieldHeightInTiles = 7;
	static constexpr int fieldSizeInTiles = fieldWidthInTiles * fieldHeightInTiles;
	static constexpr int xPositionOnScreen = Graphics::ScreenWidth / 2 - (fieldWidthInTiles * SpriteCodex::tileSize)/2;
	static constexpr int yPositionOnScreen = Graphics::ScreenHeight / 2 - (fieldHeightInTiles * SpriteCodex::tileSize)/2;
	static constexpr int playableWestXPosition = xPositionOnScreen + SpriteCodex::tileSize;
	static constexpr int playableEastXPosition = xPositionOnScreen + (fieldWidthInTiles-1)*SpriteCodex::tileSize;
	static constexpr int playableNorthyPosition = yPositionOnScreen + SpriteCodex::tileSize;
	static constexpr int playableSouthyPosition = yPositionOnScreen + (fieldHeightInTiles-1)*SpriteCodex::tileSize;
	Tile tilesArray[fieldSizeInTiles];
};
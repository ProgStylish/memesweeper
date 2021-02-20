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
		void setMinesNumber(int minesNumber);
	private:
		State state = State::Hidden;
		bool mined = false;
		int minesNumber;
	};
public:
	TilesField(int minesNumber);
	void draw(Graphics& gfx) const;
	void revealTile(Vei2& positionInPixels);
	void flagTile(Vei2& positionInPixels);
private:
	//Functions
	Tile& getTileAt(const Vei2& positionInTiles);
	const Tile& getTileAt(const Vei2& positionInTiles) const;
	void assignTailsNumbers();
	void revealAll();
	int getMinesSurroundingNumber(const Vei2& positionInTiles) const;
	//Variables
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> horizontalRange;
	std::uniform_int_distribution<int> verticalRange;
	const int minesNumber;
	static constexpr int fieldWidthInTiles = 10;
	static constexpr int fieldHeightInTiles = 15;
	static constexpr int fieldSizeInTiles = fieldWidthInTiles * fieldHeightInTiles;
	Tile tilesArray[fieldSizeInTiles];
};
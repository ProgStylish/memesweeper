#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
class TilesField {
private:
	TilesField(int minesNumber);
	class Tile {
	public:
		enum class State {
			Hidden, Revealed, Flagged
		};
		void draw(Vei2& position, Graphics& gfx) const;
	private:
		State state = State::Hidden;
		bool mined = false;
	};
	Tile& getTileAt(const Vei2& positionInTiles);
	const Tile& getTileAt(const Vei2& positionInTiles) const;
public:
	void draw(Graphics& gfx) const;
	void revealTile(Vei2& positionInPixels);
	void flagTile(Vei2& positionInPixels);
private:
	const int minesNumber;
	static constexpr int fieldWidthInTiles = 10;
	static constexpr int fieldHeightInTiles = 15;
	static constexpr int fieldSizeInTiles = fieldWidthInTiles * fieldHeightInTiles;
	Tile tilesArray[fieldSizeInTiles];
};
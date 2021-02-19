#include "TilesField.h"

TilesField::TilesField(int in_minesNumber) :
	minesNumber(in_minesNumber)
{
}

TilesField::Tile& TilesField::getTileAt(const Vei2& positionInTiles)
{
	return tilesArray[positionInTiles.y * fieldWidthInTiles + fieldWidthInTiles];
}

const TilesField::Tile& TilesField::getTileAt(const Vei2& positionInTiles) const
{
	return tilesArray[positionInTiles.y * fieldWidthInTiles + fieldWidthInTiles];
}

void TilesField::draw(Graphics& gfx) const
{
	for (int i = 0; i < fieldWidthInTiles; i++) {
		for (int j = 0; j < fieldHeightInTiles; j++) {
			getTileAt(Vei2(i, j)).draw(Vei2(i, j) * SpriteCodex::tileSize, gfx);
		}
	}
}

void TilesField::Tile::draw(Vei2& position, Graphics& gfx) const
{
	switch (state)
	{
	case State::Hidden:
		SpriteCodex::DrawTileButton(position, gfx);
		break;
	case State::Flagged:
		SpriteCodex::DrawTileButton(position, gfx);
		SpriteCodex::DrawTileFlag(position, gfx);
		break;
	case State::Revealed:
		if (mined) {
			SpriteCodex::DrawTileBomb(position, gfx);
		}
		else {
			SpriteCodex::DrawTile0(position, gfx);
		}
		break;
	}
}

void TilesField::revealTile(Vei2& positionInPixels)
{
}

void TilesField::flagTile(Vei2& positionInPixels)
{
}

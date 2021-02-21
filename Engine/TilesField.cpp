#include "TilesField.h"
#include <random>

TilesField::TilesField(int in_minesNumber) :
	minesNumber(in_minesNumber),
	rng(rd()),
	horizontalRange(1, fieldWidthInTiles - 2),
	verticalRange(1, fieldHeightInTiles - 2)
{
	for (int i = 0; i < minesNumber; i++) {
		Tile& currentTile = getTileAt(Vei2(horizontalRange(rng), verticalRange(rng)));
		if (!currentTile.isMined()) {
			currentTile.setMined(true);
		}
		else {
			i--;
		}
	}
	assignTailsNumbers();
}

TilesField::Tile& TilesField::getTileAt(const Vei2& positionInTiles)
{
	return tilesArray[positionInTiles.y * fieldWidthInTiles + positionInTiles.x];
}

const TilesField::Tile& TilesField::getTileAt(const Vei2& positionInTiles) const
{
	return tilesArray[positionInTiles.y * fieldWidthInTiles + positionInTiles.x];
}

void TilesField::assignTailsNumbers()
{
	int minesCounter = 0;
	for (int i = 1; i < fieldWidthInTiles - 1; i++) {
		for (int j = 1; j < fieldHeightInTiles - 1; j++) {
			if (!getTileAt(Vei2(i, j)).isMined()) {
				getTileAt(Vei2(i, j)).setMinesNumber(getMinesSurroundingNumber(Vei2(i, j)));
			}
		}
	}
}

void TilesField::revealAll() {
	for (int j = 0; j < fieldHeightInTiles; j++) {
		for (int i = 0; i < fieldWidthInTiles; i++) {
			getTileAt(Vei2(i, j)).reveal();
		}
	}
}

int TilesField::getMinesSurroundingNumber(const Vei2& positionInTiles) const
{
	int minesCounter = 0;
	if (positionInTiles.x > 0 && positionInTiles.x < fieldWidthInTiles - 1 &&
		positionInTiles.y > 0 && positionInTiles.y < fieldHeightInTiles - 1) {

		if (getTileAt(Vei2(positionInTiles.x - 1, positionInTiles.y - 1)).isMined()) {
			minesCounter++;
		}
		if (getTileAt(Vei2(positionInTiles.x, positionInTiles.y - 1)).isMined()) {
			minesCounter++;
		}
		if (getTileAt(Vei2(positionInTiles.x + 1, positionInTiles.y - 1)).isMined()) {
			minesCounter++;
		}
		if (getTileAt(Vei2(positionInTiles.x - 1, positionInTiles.y)).isMined()) {
			minesCounter++;
		}
		if (getTileAt(Vei2(positionInTiles.x + 1, positionInTiles.y)).isMined()) {
			minesCounter++;
		}
		if (getTileAt(Vei2(positionInTiles.x - 1, positionInTiles.y + 1)).isMined()) {
			minesCounter++;
		}
		if (getTileAt(Vei2(positionInTiles.x, positionInTiles.y + 1)).isMined()) {
			minesCounter++;
		}
		if (getTileAt(Vei2(positionInTiles.x + 1, positionInTiles.y + 1)).isMined()) {
			minesCounter++;
		}
	}
	return minesCounter;
}



void TilesField::draw(Graphics& gfx) const
{
	gfx.DrawRect(playableWestXPosition, playableNorthyPosition, 
		playableEastXPosition, playableSouthyPosition, Colors::LightGray);
	for (int j = 1; j < fieldHeightInTiles-1; j++) {
		for (int i = 1; i < fieldWidthInTiles-1; i++) {
			getTileAt(Vei2(i, j)).draw(Vei2(i, j), gfx);
		}
	}
}

void TilesField::Tile::draw(const Vei2& positionInTiles, Graphics& gfx) const
{
	const Vei2 positionDelta = Vei2(xPositionOnScreen, yPositionOnScreen);
	switch (state)
	{
	case State::Hidden:
		SpriteCodex::DrawTileButton(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
		break;
	case State::Flagged:
		SpriteCodex::DrawTileButton(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
		SpriteCodex::DrawTileFlag(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
		break;
	case State::Revealed:
		if (mined) {
			SpriteCodex::DrawTileBomb(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
		}
		else {
			switch (minesNumber) {
			case 0:
				SpriteCodex::DrawTile0(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
				break;
			case 1:
				SpriteCodex::DrawTile1(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
				break;
			case 2:
				SpriteCodex::DrawTile2(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
				break;
			case 3:
				SpriteCodex::DrawTile3(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
				break;
			case 4:
				SpriteCodex::DrawTile4(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
				break;
			case 5:
				SpriteCodex::DrawTile5(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
				break;
			case 6:
				SpriteCodex::DrawTile6(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
				break;
			case 7:
				SpriteCodex::DrawTile7(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
				break;
			case 8:
				SpriteCodex::DrawTile8(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
				break;
			}
		}
		break;
	}
}

bool TilesField::Tile::isMined() const
{
	return mined;
}

void TilesField::Tile::setMined(bool in_mined)
{
	mined = in_mined;
}

void TilesField::Tile::reveal()
{
	state = State::Revealed;
}

void TilesField::Tile::setMinesNumber(int in_minesNumber)
{
	minesNumber = in_minesNumber;
}

void TilesField::revealTile(Vei2& positionInPixels)
{
	if (positionInPixels.x > playableWestXPosition && positionInPixels.x < playableEastXPosition &&
		positionInPixels.y > playableNorthyPosition && positionInPixels.y < playableSouthyPosition) {
		getTileAt((positionInPixels - Vei2(xPositionOnScreen, yPositionOnScreen)) / SpriteCodex::tileSize).reveal();
	}
}

void TilesField::flagTile(Vei2& positionInPixels)
{
}

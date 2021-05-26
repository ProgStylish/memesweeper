#include "TilesField.h"
#include <random>

TilesField::TilesField(int in_minesNumber, int width, int height) :
	minesNumber(in_minesNumber),
	rng(rd()),
	fieldWidthInTiles(width),
	fieldHeightInTiles(height),
	horizontalRange(1, width- 2),
	verticalRange(1, height - 2)
{
	int size = width * height;
	tilesArray = new Tile[size];
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
		for (int i = positionInTiles.x - 1; i < positionInTiles.x + 2; i++) {
			for (int j = positionInTiles.y - 1; j < positionInTiles.y + 2; j++) {
				if (getTileAt(Vei2(i, j)).isMined()) {
					minesCounter++;
				}
			}
		}
	}
	return minesCounter;
}



void TilesField::draw(Graphics& gfx) const
{
	gfx.DrawRect(playableWestXPosition, playableNorthyPosition,
		playableEastXPosition, playableSouthyPosition, Colors::LightGray);
	for (int j = 1; j < fieldHeightInTiles - 1; j++) {
		for (int i = 1; i < fieldWidthInTiles - 1; i++) {
			getTileAt(Vei2(i, j)).draw(Vei2(i, j), xPositionOnScreen, yPositionOnScreen, gfx);
		}
	}
}

void TilesField::Tile::draw(const Vei2& positionInTiles, int xPositionOnScreen, int yPositionOnScreen, Graphics& gfx) const
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
			if (exploited) {
				SpriteCodex::DrawTileBombRed(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
			}
			else {
				SpriteCodex::DrawTileBomb(positionInTiles * SpriteCodex::tileSize + positionDelta, gfx);
			}
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
	if (state != State::Flagged) {
		state = State::Revealed;
	}
}

void TilesField::Tile::flag()
{
	if (state != State::Revealed) {
		if (state != State::Flagged) {
			state = State::Flagged;
		}
		else {
			state = State::Hidden;
		}
	}
}

void TilesField::Tile::setMinesNumber(int in_minesNumber)
{
	minesNumber = in_minesNumber;
}

bool TilesField::Tile::isExploited() const
{
	return exploited;
}

void TilesField::Tile::exploit()
{
	exploited = true;
}

TilesField::Tile::State TilesField::Tile::getState() const
{
	return state;
}

void TilesField::Tile::unFlag()
{
	state = State::Hidden;
}

void TilesField::revealTile(Vei2& positionInPixels)
{
	if (!fuckedUp) {
		if (positionInPixels.x > playableWestXPosition && positionInPixels.x < playableEastXPosition &&
			positionInPixels.y > playableNorthyPosition && positionInPixels.y < playableSouthyPosition) {
			Vei2 tilePosition = (positionInPixels - Vei2(xPositionOnScreen, yPositionOnScreen)) / SpriteCodex::tileSize;
			Tile& tile = getTileAt(tilePosition);
			if (tile.getState() != Tile::State::Revealed && tile.getState() != Tile::State::Flagged) {
				tile.reveal();
				revealedTilesCounter += 1;
				if (tile.isMined()) {
					tile.exploit();
					fuckedUp = true;
					revealMinedTiles();
				}
				else  if (getMinesSurroundingNumber(tilePosition) == 0) {
					revealNeighboursTiles(tilePosition);
				}
				else if (minesNumber == ((fieldWidthInTiles - 2) * (fieldHeightInTiles - 2) - revealedTilesCounter)) {
					fuckedUp = true;
				}
			}
		}
	}
}

void TilesField::revealNeighboursTiles(const Vei2 tilePosition) {
	if (tilePosition.x > 0 && tilePosition.x < fieldWidthInTiles - 1 &&
		tilePosition.y > 0 && tilePosition.y < fieldHeightInTiles - 1) {
		for (int i = tilePosition.x - 1; i < tilePosition.x + 2; i++) {
			for (int j = tilePosition.y - 1; j < tilePosition.y + 2; j++) {
				if (getTileAt(Vei2(i, j)).getState() != Tile::State::Revealed) {
					getTileAt(Vei2(i, j)).reveal();
					if (getMinesSurroundingNumber(Vei2(i, j)) == 0) {
						revealNeighboursTiles(Vei2(i, j));
					}
				}
			}
		}
	}
}

void TilesField::revealMinedTiles() {
	for (int i = 1; i < fieldWidthInTiles - 1; i++) {
		for (int j = 1; j < fieldHeightInTiles; j++) {
			if (getTileAt(Vei2(i, j)).isMined()) {
				getTileAt(Vei2(i, j)).reveal();
			}
		}
	}
}

void TilesField::flagTile(Vei2& positionInPixels)
{
	if (!fuckedUp) {
		getTileAt((positionInPixels - Vei2(xPositionOnScreen, yPositionOnScreen)) / SpriteCodex::tileSize).flag();
	}
}
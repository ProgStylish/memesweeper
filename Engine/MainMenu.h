#pragma once
#include "Graphics.h"
#include "Vei2.h"
#include "RectI.h"
#include "Colors.h"
class MainMenu {
public:
	enum class Size {
		Small,
		Medium,
		Large,
		None
	};
	MainMenu() = default;
	void draw(Graphics& gfx) const;
	void sizeSelectedDefiner(Vei2& position);
	void highLight(Graphics& gfx, RectI& rect) const;
private:
	int xCenterPosition;
	int yCenterPosition;
	Size size = Size::None;
};
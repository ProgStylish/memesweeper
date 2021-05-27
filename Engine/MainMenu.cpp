#include "MainMenu.h"
#include "Colors.h"

void MainMenu::draw(Graphics& gfx) const
{
}

void MainMenu::sizeSelectedDefiner(Vei2& position)
{
	if (position.y < Graphics::ScreenHeight / 3) {
		size = Size::Small;
	}
	else {
		size = Size::None;
	}
}

void MainMenu::highLight(Graphics& gfx, RectI& rect) const {
	if (size == Size::Small) {
		gfx.DrawRect(rect, Colors::Green);
	}
}

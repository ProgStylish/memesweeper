#include "MainMenu.h"
#include "Colors.h"

void MainMenu::draw(Graphics& gfx) const
{
	SpriteCodex::DrawSmall(Vei2(Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 3), gfx);
	SpriteCodex::DrawMedium(Vei2(Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2), gfx);
	SpriteCodex::DrawLarge(Vei2(Graphics::ScreenWidth / 2, 2 * Graphics::ScreenHeight / 3), gfx);
}

void MainMenu::sizeSelectedDefiner(Vei2& position)
{
	if (position.y > Graphics::ScreenHeight / 4 && position.y < 5 * Graphics::ScreenHeight / 12
		&& position.x > Graphics::ScreenWidth / 3 && position.x < 2 * Graphics::ScreenWidth / 3) {
		size = Size::Small;
	}
	else if (position.y > 5 * Graphics::ScreenHeight / 12 && position.y < 7 * Graphics::ScreenHeight / 12
		&& position.x > Graphics::ScreenWidth / 3 && position.x < 2 * Graphics::ScreenWidth / 3) {
		size = Size::Medium;
	}
	else if (position.y > 7 * Graphics::ScreenHeight / 12 && position.y < 3 * Graphics::ScreenHeight / 4
		&& position.x > Graphics::ScreenWidth / 3 && position.x < 2 * Graphics::ScreenWidth / 3) {
		size = Size::Large;
	}
	else {
		size = Size::None;
	}
}

void MainMenu::highLight(Graphics& gfx) const {
	switch (size) {
	case Size::Small:
		gfx.DrawBorderRect(Graphics::ScreenWidth / 3, Graphics::ScreenHeight / 4, Graphics::ScreenWidth - Graphics::ScreenWidth / 3, 5 * Graphics::ScreenHeight / 12, 4, Colors::Green);
		break;
	case Size::Medium:
		gfx.DrawBorderRect(Graphics::ScreenWidth / 3, 5 * Graphics::ScreenHeight / 12, Graphics::ScreenWidth - Graphics::ScreenWidth / 3, 7 * Graphics::ScreenHeight / 12, 4, Colors::Green);
		break;
	case Size::Large:
		gfx.DrawBorderRect(Graphics::ScreenWidth / 3, 7 * Graphics::ScreenHeight / 12, Graphics::ScreenWidth - Graphics::ScreenWidth / 3, 3 * Graphics::ScreenHeight / 4, 4, Colors::Green);
		break;
	default: break;
	}
}

MainMenu::Size MainMenu::selectedSizeProcessor()
{
	return size;
}

/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Vei2.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event e = wnd.mouse.Read();
		if (!playing) {
			mainMenu.sizeSelectedDefiner(Vei2(e.GetPosX(),e.GetPosY()));
		}
		else {
			switch (e.GetType()) {
			case Mouse::Event::Type::LPress:
				tilesField->revealTile(Vei2(e.GetPosX(), e.GetPosY()));
				break;
			case Mouse::Event::Type::RPress:
				tilesField->flagTile(Vei2(e.GetPosX(), e.GetPosY()));
				break;
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (!playing) {
		mainMenu.draw(gfx);
		RectI rect = RectI(Graphics::ScreenWidth/6,Graphics::ScreenWidth - Graphics::ScreenWidth/6, 0,Graphics::ScreenHeight/3);
		mainMenu.highLight(gfx, rect);

	}
	else {
		tilesField->draw(gfx);
	}
}

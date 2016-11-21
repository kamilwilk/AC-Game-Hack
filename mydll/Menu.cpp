#include "Menu.h"
#include "ESP.h"
#include "Aimbot.h"
#include "Radar.h"
#include "Engine.h"
#include <vector>

bool menu = false;
int currentTab = 1;

std::vector<char*> menuItems;
std::vector<bool> toggles;
std::vector<void(*)()> funcPtrs;

void Menu()
{
	if (menu)
	{
		for (unsigned int i = 0; i < menuItems.size(); ++i)
		{
			DrawMenuItem(menuItems.at(i), i+1);
		}
	}

	handleToggles();
}

void MenuInit(char * text, bool toggle, void(*function)(), int position)
{
	menuItems.push_back(text);
	toggles.push_back(toggle);
	funcPtrs.push_back(function);
}

void handleToggles()
{
	for (unsigned int i = 0; i < toggles.size(); ++i)
	{
		if (toggles.at(i))
			funcPtrs.at(i)();
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) menu = !menu;

	if (menu)
	{
		if ((GetAsyncKeyState(VK_DOWN) & 1) && (currentTab <= 3)) currentTab += 1;

		if ((GetAsyncKeyState(VK_UP) & 1) && (currentTab >= 1)) currentTab -= 1;

		if (GetAsyncKeyState(VK_RETURN) & 1) toggles.at(currentTab) = !toggles.at(currentTab);
	}
}

void DrawMenuItem(char * text, int position)
{
	draw.init();

	float scale = CurrentGame.scale;

	Vec2 Menu = { 450 * scale, 2 * scale };

	float fontSize = 18 + Menu.y;
	float spacing = 4;
	float boxSize = fontSize + spacing * 2;

	draw.string(Menu.x + 10, fontSize, 0, 255, 0, 255, GLUT_BITMAP_HELVETICA_12, "Capstone Game Hack");
	draw.boxLine(1, Menu.x, Menu.y, 200, boxSize, 0, 0, 0, 200);
	draw.box(Menu.x, Menu.y, 200, boxSize, 128, 128, 128, 200);

	draw.boxLine(1, Menu.x, Menu.y + boxSize * position, 200, boxSize, 0, 0, 0, 200);
	draw.string(Menu.x + 15, fontSize + boxSize * position, 0, 255, 0, 255, GLUT_BITMAP_HELVETICA_18, text);
	if (toggles.at(position-1))
		draw.string(Menu.x + 150, fontSize + boxSize * position, 0, 255, 0, 255, GLUT_BITMAP_HELVETICA_18, "[on]");
	else
		draw.string(Menu.x + 150, fontSize + boxSize * position, 0, 255, 0, 255, GLUT_BITMAP_HELVETICA_18, "[off]");

	if (currentTab == position-1)
		draw.box(Menu.x, Menu.y + boxSize * position, 200, boxSize, 255, 0, 0, 200);
	else
		draw.box(Menu.x, Menu.y + boxSize * position, 200, boxSize, 128, 128, 128, 200);
}


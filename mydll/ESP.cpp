#include "ESP.h"
#include "Engine.h"

playerent * localPlayer = (playerent*)*(DWORD*)(0x50F4F4);

void ESPbox()
{
	draw.init();
	float scale = CurrentGame.scale;

	for (int i = 1; i < *CurrentGame.num_players; ++i)
	{
		playerent * entity = (playerent*)*(DWORD*)(*(DWORD*)0x50F4F8 + i * 0x4);
		if (!entity) continue;

		Vec3 myscreen;
		float * vMatrix = (float*)0x501AE8;
		WorldToScreen(entity->pos, myscreen, vMatrix);

		float boxHeight = (2000 / Get3dDistance(localPlayer->pos, entity->pos)) * scale;
		float boxWidth = boxHeight / 2;
		float x = myscreen.x - boxWidth / 2;
		float y = myscreen.y - boxHeight;

		if (entity->state == 0)
		{
			if ( (localPlayer->teamNum == entity->teamNum) && (CurrentGame.teamGame) )
			{
				draw.boxLine(1, x, y, boxWidth, boxHeight, 128, 128, 128, 255);
			}

			else if (!checkTrace(localPlayer, entity))
			{
				draw.boxLine(1, x, y, boxWidth, boxHeight, 0, 255, 0, 255);
			}

			else
			{
				draw.boxLine(1, x, y, boxWidth, boxHeight, 255, 0, 0, 255);
			}
		}
	}
}

void ESPhealth()
{
	draw.init();

	float scale = CurrentGame.scale;

	for (int i = 1; i < *CurrentGame.num_players; ++i)
	{
		playerent * entity = (playerent*)*(DWORD*)(*(DWORD*)0x50F4F8 + i * 0x4);
		if (!entity) continue;

		Vec3 myscreen;
		float * vMatrix = (float*)0x501AE8;
		WorldToScreen(entity->pos, myscreen, vMatrix);

		float boxHeight = (2000 / Get3dDistance(localPlayer->pos, entity->pos)) * scale;
		float boxWidth = boxHeight / 2;
		float x = myscreen.x + boxWidth /2 ;
		x += 2.0;
		float healthWidth = boxHeight / 16;

		if (healthWidth < 4.0)
			healthWidth = 4.0;

		boxHeight *= ((float)entity->health / 100);

		if (entity->state == 0)
		{
			draw.boxLine(1, x, myscreen.y - boxHeight, healthWidth, boxHeight, 0, 0, 0, 255);

			if (entity->health > 75)
			{ 
				draw.box(x, myscreen.y - boxHeight, healthWidth, boxHeight, 0, 255, 0, 255);
			}

			else if (entity->health > 50)
			{
				draw.box(x, myscreen.y - boxHeight, healthWidth, boxHeight, 255, 255, 0, 255);
			}

			else if (entity->health > 25)
			{
				draw.box(x, myscreen.y - boxHeight, healthWidth, boxHeight, 255, 165, 0, 255);
			}
			else
			{
				draw.box(x, myscreen.y - boxHeight, healthWidth, boxHeight, 255, 0, 0, 255);
			}
		}
	}
}
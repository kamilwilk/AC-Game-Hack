#include "Radar.h"
#include "Engine.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Radar()
{
	draw.init();
	float scale = CurrentGame.scale;
	Vec2 radarPos = { 0 * scale, 150 * scale };
	Vec2 radarSize = { 200 * scale , 200 * scale };
	Vec2 centerPoint = { 100 * scale, 250 * scale };

	draw.boxLine(1, radarPos.x, radarPos.y, radarSize.x, radarSize.y, 255, 255, 255, 200);

	playerent * localPlayer = (playerent*)*(DWORD*)(0x50F4F4);

	for (int i = 1; i < *CurrentGame.num_players; ++i)
	{
		playerent * entity = (playerent*)*(DWORD*)(*(DWORD*)0x50F4F8 + i * 0x4);

		if (!entity) continue;

		if (entity->state == 0)
		{
			Vec2 lP;
			lP.x = localPlayer->pos.x;
			lP.y = localPlayer->pos.y;
			Vec2 eP;
			eP.x = entity->pos.x;
			eP.y = entity->pos.y;

			Vec2 relVec = getRelativeVector(lP, eP, radarSize.x);

			relVec.x += centerPoint.x;
			relVec.y += centerPoint.y;

			float yaw = atan2f(relVec.x, relVec.y);
			yaw -= localPlayer->angle.x;

			Vec2 pointToDraw = rotatePoint(relVec, centerPoint, yaw);

			if ( (localPlayer->teamNum == entity->teamNum) && (CurrentGame.teamGame) )
			{
				draw.dot(4, pointToDraw.x, pointToDraw.y, 0, 255, 0, 255);
			}
			else
			{ 
				draw.dot(4, pointToDraw.x, pointToDraw.y, 255, 0, 0, 255);
			}
		}
	}

	draw.line(0.75, 0 * scale, 250 * scale, 200 * scale, 250 * scale, 255, 255, 255, 200);
	draw.line(0.75, 100 * scale, 150 * scale, 100 * scale, 350 * scale, 255, 255, 255, 200);
	
	draw.box(radarPos.x, radarPos.y, radarSize.x, radarSize.y, 128, 128, 128, 150);
}


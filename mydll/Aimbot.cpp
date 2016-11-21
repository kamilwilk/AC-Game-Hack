#include "Aimbot.h"
#include "Engine.h"

//Aimboterino
void Aimbot()
{
	if (*CurrentGame.num_players == 0) return;


	Vec3 currentAngle;
	Vec3 closestAngle = { 10000 };

	playerent * localPlayer = (playerent*)*(DWORD*)(0x50F4F4);
	
	for (int i = 1; i < *CurrentGame.num_players; ++i)
	{
		DWORD * entityList = (DWORD*)(0x50F4F8);
		playerent * entity = (playerent*)*(DWORD*)(*entityList + i * 0x4);

		if (!entity) continue;

		if (CurrentGame.teamGame)
		{
			if ((localPlayer->currentweapon->wep_id == 0) && (entity->state == 0) && (entity->teamNum != localPlayer->teamNum))
			{
				localPlayer->pos = entity->pos;
			}
		}
		else
		{

			if ((localPlayer->currentweapon->wep_id == 0) && (entity->state == 0))
			{
				localPlayer->pos = entity->pos;
			}
		}

		currentAngle = CalcAngle(localPlayer->pos, entity->pos);
		if (DifferenceOfAngles(currentAngle, localPlayer->angle) <= DifferenceOfAngles(closestAngle, localPlayer->angle))
		{
			if (CurrentGame.teamGame)
			{

				if ((entity->state == 0) && (!checkTrace(localPlayer, entity)) && (entity->teamNum != localPlayer->teamNum))
				{
					closestAngle = currentAngle;
				}
			}
			else
			{

				if ((entity->state == 0) && (!checkTrace(localPlayer, entity)))
				{
					closestAngle = currentAngle;
				}
			}
		}
	}


	if (closestAngle.x != 10000)
	{
		localPlayer->angle = closestAngle;
		localPlayer->b_firing = 1;
	}
	else
	{
		localPlayer->b_firing = 0;
	}
}
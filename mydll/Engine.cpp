#include "Engine.h"

Game CurrentGame;
Draw draw;

//Game constructor to get game info
Game::Game()
{
	num_players = (int*)(0x50F500);
	mode = (int*)(0x50F49C);

	for (int i = 0; i < 11; ++i)
	{
		if (gameModes[i] == *mode)
			teamGame = true;
	}

	w_res = (int*)(0x6814E0C0);
	h_res = (int*)(0x6814E0C4);

	scale = *w_res / 800.0f;
}

//visibility check to see if a player is visible
bool checkTrace(playerent * local, playerent * enemy)
{
	playerent localPlayer = *(playerent*)*(DWORD*)(0x50F4F4);
	DWORD traceLine = 0x048a310;
	traceresult_s traceresult;
	traceresult.collided = false;
	Vec3 from = local->pos;
	Vec3 to = enemy->pos;
	to.z += 5;
	from.z += 5;

	__asm
	{
		push 0; bSkipTags
		push 0; bCheckPlayers
			push localPlayer
			push to.z
			push to.y
			push to.x
			push from.z
			push from.y
			push from.x
			lea eax, [traceresult]
			call traceLine;
		add esp, 36
	}

	return traceresult.collided;
}

void Mods()
{
	playerent * localPlayer = (playerent*)*(DWORD*)(0x50F4F4);

	localPlayer->rifleTimer = 0;
	localPlayer->smgTimer = 0;
	localPlayer->sniperTimer = 0;
	localPlayer->shotgunTimer = 0;
	localPlayer->carbineTimer = 0;
	localPlayer->pistolTimer = 0;
	localPlayer->grenadeTimer = 0;
	localPlayer->knifeTimer = 0;
	
	localPlayer->health = 1337;
	localPlayer->armor = 1337;
	localPlayer->rifleAmmo = 1337;
	localPlayer->smgAmmo = 1337;
	localPlayer->sniperAmmo = 1337;
	localPlayer->shotgunAmmo = 1337;
	localPlayer->carbineAmmo = 1337;
	localPlayer->pistolAmmo = 1337;
	localPlayer->grenadeAmmo = 1337;


	DWORD d, ds;
	VirtualProtect((LPVOID)0x463786, 10, PAGE_EXECUTE_READWRITE, &d);
	memset((LPVOID)0x463786, 0x90, 10);
	VirtualProtect((LPVOID)0x463786, 10, d, &ds);
}
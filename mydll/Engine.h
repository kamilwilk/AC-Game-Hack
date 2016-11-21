#pragma once
#include "Vector.h"
#include "Draw.h"
#include <vector>

extern struct Game CurrentGame;
extern class Draw draw;

struct Weapon;

struct playerent
{
	char pad_0x0000[0x34]; //0x0000
	Vec3 pos; //0x0034 
	Vec3 angle; //0x0040 
	char pad_0x004C[0xAC]; //0x004C
	__int32 health; //0x00F8 
	__int32 armor; //0x00FC 
	char pad_0x0100[0x3C]; //0x0100
	__int32 pistolAmmo; //0x013C 
	__int32 carbineAmmo; //0x0140 
	__int32 shotgunAmmo; //0x0144 
	__int32 smgAmmo; //0x0148 
	__int32 sniperAmmo; //0x014C 
	__int32 rifleAmmo; //0x0150 
	char pad_0x0154[0x4]; //0x0154
	__int32 grenadeAmmo; //0x0158 
	char pad_0x015C[0x4]; //0x015C
	__int32 knifeTimer; //0x0160 
	__int32 pistolTimer; //0x0164 
	__int32 carbineTimer; //0x0168 
	__int32 shotgunTimer; //0x016C 
	__int32 smgTimer; //0x0170 
	__int32 sniperTimer; //0x0174 
	__int32 rifleTimer; //0x0178 
	char pad_0x017C[0x4]; //0x017C
	__int32 grenadeTimer; //0x0180 
	char pad_0x0184[0xA0]; //0x0184
	unsigned char b_firing; //0x0224 
	char pad_0x0225[0x107]; //0x0225
	__int32 teamNum; //0x032C 
	char pad_0x0330[0x8]; //0x0330
	__int32 state; //0x0338 
	char pad_0x033C[0x38]; //0x033C
	Weapon * currentweapon; //0x0374 
	char pad_0x0378[0xB4]; //0x0378
};//Size=0x042C

struct Weapon
{
	char pad_0x0000[0x4]; //0x0000
	__int32 wep_id; //0x0004 
	char pad_0x0008[0x14]; //0x0008
};

//Struct to hold information about our game :)
struct Game
{
	int * num_players;
	int gameModes[11] = { 0, 4, 5, 7, 13, 11, 14, 17, 16, 20, 21 };
	int * mode;
	bool teamGame = false;

	int * w_res;
	int * h_res;

	float scale;

	Game();
};

struct traceresult_s
{
	Vec3 end;
	bool collided;
};


bool checkTrace(playerent * local, playerent * enemy);
void UpdateEntityInfo();
void Mods();


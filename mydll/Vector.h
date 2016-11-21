#pragma once
#include <Windows.h>
#include <iostream>

//Stuff from assault cube source code for calculating aimbot angles
#define Q_PI ( 3.1415927f )
#define QDegToRad(A) ( A * 180.0f / Q_PI )
#define QACUBE(A) ( A / Q_PI * 180.0f + 180.0f )

struct Vec2 
{
	float x, y;
};
//Vector 3 to hold stuff like position and view angles
struct Vec3
{
	float  x, y, z;
};

//Vector functions
float Get3dDistance(Vec3 src, Vec3 dst);
float distxy(Vec3 src, Vec3 dst);
float DifferenceOfAngles(Vec3 src, Vec3 dst);
bool WorldToScreen(Vec3 In, Vec3& Out, float* ViewMatrix);
Vec3 CalcAngle(Vec3 src, Vec3 dst);
//radar
float vectorLength(Vec2 vector);
Vec2 getRelativeVector(Vec2 player, Vec2 enemy, float maxLength);
float vectorLength(Vec2 vector);
Vec2 normalizeVector(Vec2 vector);
Vec2 rotatePoint(Vec2 pointToRotate, Vec2 centerPoint, float angle);


#include "Vector.h"
#include "Engine.h"

//Some math to adjust ESP boxes depending on distance
float Get3dDistance(Vec3 src, Vec3 dst)
{
	return (float)
		(sqrt(
			((src.x - dst.x) * (src.x - dst.x)) +
			((src.y - dst.y) * (src.y - dst.y)) +
			((src.z - dst.z) * (src.z - dst.z))
			));
}

//distance between x and y for CalcAngle function
float distxy(Vec3 src, Vec3 dst)
{
	float dx = dst.x - src.x;
	float dy = dst.y - src.y;
	return sqrtf(dx*dx + dy*dy);
}

//function to calculate the angle needed for our aimbot
Vec3 CalcAngle(Vec3 src, Vec3 dst)
{
	Vec3 angles;

	angles.x = QACUBE((-(float)atan2(dst.x - src.x, dst.y - src.y)));
	angles.y = QDegToRad((atan2(dst.z - src.z, distxy(src, dst))));
	angles.z = 0.0f;

	return angles;
}

//Calculates the difference between angles so that we can aim at the closest player
float DifferenceOfAngles(Vec3 src, Vec3 dst)
{
	Vec3 vdifference;

	vdifference.y = src.y - src.y;
	vdifference.x = src.x - src.x;
	//vdifference.roll = 0;

	//normalize by making them positive values if they are negative
	if (vdifference.y < 0)
	{
		vdifference.y *= -1;
	}
	if (vdifference.x < 0)
	{
		vdifference.x *= -1;
	}

	//add them together and divide by 2, gives an average of the 2 angles
	float fDifference = (vdifference.y + vdifference.x) / 2;
	return fDifference;
}

//translate a 3d player position to a position on our 2d screen
bool WorldToScreen(Vec3 In, Vec3& Out, float * ViewMatrix) 
{
	Out.x = In.x * ViewMatrix[0] + In.y * ViewMatrix[4] + In.z * ViewMatrix[8] + ViewMatrix[12];
	Out.y = In.x * ViewMatrix[1] + In.y * ViewMatrix[5] + In.z * ViewMatrix[9] + ViewMatrix[13];
	Out.z = In.x * ViewMatrix[2] + In.y * ViewMatrix[6] + In.z * ViewMatrix[10] + ViewMatrix[14];
	float w = In.x * ViewMatrix[3] + In.y * ViewMatrix[7] + In.z * ViewMatrix[11] + ViewMatrix[15];

	if (w < 0.0)
		return false;

	Out.x /= w;
	Out.y /= w;
	Out.z /= w;

	Out.x *= *CurrentGame.w_res / 2.0f;
	Out.x += *CurrentGame.w_res / 2.0f;

	Out.y *= -*CurrentGame.h_res / 2.0f;
	Out.y += *CurrentGame.h_res / 2.0f;

	return true;
}


//Radar
Vec2 getRelativeVector(Vec2 player, Vec2 enemy, float maxLength)
{
	Vec2 relativeVector;

	relativeVector.x = enemy.x - player.x;
	relativeVector.y = enemy.y - player.y;


	if (vectorLength(relativeVector) > maxLength / 2)
	{
		relativeVector = normalizeVector(relativeVector);
		relativeVector.x *= maxLength / 2;
		relativeVector.y *= maxLength / 2;
	}

	return relativeVector;
}

float vectorLength(Vec2 vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vec2 normalizeVector(Vec2 vector)
{
	Vec2 returnVec;

	returnVec.x = vector.x * (1 / vectorLength(vector));
	returnVec.y = vector.y * (1 / vectorLength(vector));

	return returnVec;
}

Vec2 rotatePoint(Vec2 pointToRotate, Vec2 centerPoint, float angle)
{
	angle *= (Q_PI / 180.0f);

	float cosTheta = cos(angle);
	float sinTheta = sin(angle);

	pointToRotate.x -= centerPoint.x;
	pointToRotate.y -= centerPoint.y;

	float xnew = pointToRotate.x * cosTheta - pointToRotate.y * sinTheta;
	float ynew = pointToRotate.x * sinTheta + pointToRotate.y * cosTheta;

	pointToRotate.x = xnew + centerPoint.x;
	pointToRotate.y = ynew + centerPoint.y;

	return pointToRotate;
}

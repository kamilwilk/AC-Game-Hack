#include "Hook.h"
#include <windows.h>
#include <tlhelp32.h>
#include "Menu.h"

DWORD retJump; //go back to the code after the function we hooked

//Place our hook
bool placeHook(void * hookSpot, void * ourFunc, int len)
{
	retJump = (DWORD)hookSpot;
	retJump += 0x5;

	DWORD oldProtect;

	if (len < 5)
	{
		return false;
	}

	if (!VirtualProtect(hookSpot, len, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		return false;
	}

	DWORD relativeAddy = DWORD(ourFunc) - DWORD(hookSpot) - 5;
	*(BYTE*)hookSpot = 0xE9;
	*(DWORD*)(DWORD(hookSpot) + 0x1) = relativeAddy;

	for (int i = 0; i < len - 5; ++i)
	{
		*(BYTE*)((DWORD)hookSpot + 0x5 + i) = 0x90;
	}

	DWORD backup;
	if (!VirtualProtect(hookSpot, len, oldProtect, &backup))
	{
		return false;
	}

	return true;
}

//We now run our own function in the hooked location
__declspec(naked) void ourFunction()
{

	__asm MOV EDI, EDI
	__asm PUSH EBP
	__asm MOV EBP, ESP
	__asm pushad // push all general registers
	__asm pushfd

	Menu();

	__asm popfd
	__asm popad
	__asm jmp[retJump]
}

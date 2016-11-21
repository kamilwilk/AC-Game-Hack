#pragma warning(disable:4996)
#include "Hook.h"
#include "Engine.h"
#include "Aimbot.h"
#include "Menu.h"
#include "ESP.h"
#include "Radar.h"

//Credits to Solaire and Rake at GuidedHacking.com for assistance
//Credits to Solaire for his OpenGL drawing class which was modified to take RGB values 0-255 including alpha

//The thread that gets ran when the DLL is injected.
DWORD WINAPI hackthread(LPVOID param)
{
	//Get Address of wglSwapBuffers of opengl and call placeHook to hook it
	HMODULE hMod = GetModuleHandle("opengl32.dll");
	placeHook(GetProcAddress(hMod, "wglSwapBuffers"), ourFunction, 5);

	MenuInit("Aimbot", false, Aimbot, 1);
	MenuInit("ESP Box", false, ESPbox, 2);
	MenuInit("ESP Health", false, ESPhealth, 3);
	MenuInit("Radar", false, Radar, 4);
	MenuInit("Mods", false, Mods, 5);

	//while loop where all the good stuff happens
	while (true)
	{
		//UpdateEntityInfo();

		CurrentGame = Game::Game();

		Sleep(10); //sleep for a tiny bit for performance so we dont blow up our CPU
	}

	// Free the DLL
	FreeLibraryAndExitThread((HMODULE)param, NULL);

	return NULL;
}


//This is DllMain, you can look this up on msdn but its pretty self explanatory
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole(); //Alloc a console window for debugging purposes :)
		freopen("CONOUT$", "w", stdout);

		CreateThread(0, 0, hackthread, hModule, 0, 0);
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

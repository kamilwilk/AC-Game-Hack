#pragma once

void Menu();
void handleToggles();
void DrawMenuItem(char * text, int position);
void AddMenuItem(char * text, bool toggle, void(*function)(), int position);
void MenuInit(char * text, bool toggle, void(*function)(), int position);
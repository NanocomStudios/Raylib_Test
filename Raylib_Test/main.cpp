#include <iostream>
#include <raylib.h>
#include <time.h>
#include <thread>
#include <conio.h>

#define MUL 2
using namespace std;

int screenPointer = 0;
char screenRam[4096];

void screenDraw(char screenRam[]) {
	InitWindow(640 * MUL, 400 * MUL, "Hello");
	SetTargetFPS(60);

	for (int i = 0; i < 4096; i++) {
		screenRam[i] = GetRandomValue(0, 127);
	}

	int x = 0;
	int y = 0;
	int hue = 0;
	while (!WindowShouldClose()) {

		if (screenPointer >= 4000) {
			for (int i = 0; i < 3920; i++) {
				screenRam[i] = screenRam[i + 80];
			}
			for (int i = 3920; i < 4000; i++) {
				screenRam[i] = 0;
			}
			screenPointer = 3920;
		}

		BeginDrawing();
		ClearBackground(BLACK);
		
		for (x = 0; x < 640 * MUL; x += 8 * MUL) {
			for (y = 0; y < 400 * MUL; y += 8 * MUL) {
				//DrawRectangle(x, y, 8* MUL, 8* MUL, ColorFromHSV(x * 10 + y * 8, 1, 1));
				//cout << ((y / (8 * MUL)) * 80) + (x / (8 * MUL)) << endl;
				if (screenRam[((y / (8 * MUL)) * 80) + (x / (8 * MUL))] == 127) {
					DrawLine(x, y, x + (8 * MUL), y + (8 * MUL), WHITE);
				}
				else if (screenRam[((y / (8 * MUL)) * 80) + (x / (8 * MUL))] == 126) {
					DrawLine(x + (8 * MUL), y, x , y + (8 * MUL), WHITE);
				}
				else {
					DrawText(TextFormat("%c", screenRam[((y / (8 * MUL)) * 80) + (x / (8 * MUL))]), x + 1, y, 8 * MUL, WHITE);
				}

			}
			hue++;
		}
		DrawRectangle(((screenPointer % 80) * 8 * MUL), ((screenPointer / 80 * 8) + 6) * MUL, 8 * MUL, 2 * MUL, RAYWHITE);
		EndDrawing();
	}
}

void printScreen(string inp) {
	for (char c : inp) {
		screenRam[screenPointer] = c;
		screenPointer++;
	}
}

void printChar(char inp) {
	
	screenRam[screenPointer] = inp;
	screenPointer++;
	
}

int main() {

	thread t1(screenDraw,screenRam);
	t1.detach();
	WaitTime(0.5);
	
	for (int i = 0; i < 4096; i++) {
		screenRam[i] = 0;
	}
	while (1) {
		WaitTime(0.005);
		printChar(GetRandomValue(126,127));
	}
	while (0) {
		int inp;
		inp = _getch(); 
		
		if (inp == 13) {
			screenPointer = ((screenPointer / 80) + 1) * 80;
		}
		else if (inp == 8) {
			if (screenPointer > 0) {
				screenRam[--screenPointer] = 0;
			}
		}
		else {
			printChar(inp);
		}
	}

	system("pause");
}
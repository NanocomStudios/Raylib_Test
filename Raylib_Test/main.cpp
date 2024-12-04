#include <iostream>
#include <raylib.h>
#define MUL 2
using namespace std;

int main() {
	int x = 0;
	int y = 0;
	int hue = 0;
	char screenRam[4096];

	

	InitWindow(640*MUL,400*MUL,"Hello");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(BLACK);
			for (int i = 0; i < 4096; i++) {
				screenRam[i] = GetRandomValue(0, 127);
			}
			for (x = 0; x < 640* MUL; x += 8* MUL) {
				for (y = 0; y < 400* MUL; y += 8* MUL) {
					//DrawRectangle(x, y, 8* MUL, 8* MUL, ColorFromHSV(x * 10 + y * 8, 1, 1));
					DrawText(TextFormat("%c",screenRam[((y / (8 * MUL)) * 80) + (x / (8 * MUL))]), x, y, 8 * MUL, WHITE);
					//cout << ((y / (8 * MUL)) * 80) + (x / (8 * MUL)) << endl;
				}
				hue++;
			}
		EndDrawing();
	}
}
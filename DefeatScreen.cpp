#include "DefeatScreen.h"
void DefeatScreen::Update() {
    if (IsKeyPressed(KEY_ENTER)) {
        CloseWindow(); // quit game
    }
}

void DefeatScreen::Draw() {
    BeginDrawing();
    ClearBackground(MAROON);
    DrawText("You Lost!", 400, 250, 40, WHITE);
    DrawText("Press Enter to Exit", 350, 300, 20, WHITE);
    EndDrawing();
}
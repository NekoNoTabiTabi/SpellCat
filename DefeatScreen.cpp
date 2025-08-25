#include "DefeatScreen.h"
void DefeatScreen::Update() {
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mousePos, retryBtn)) {
            retryChosen = true;
        }
    }
}


void DefeatScreen::Draw() {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawText("Defeat!", 420, 200, 40, RED);

    DrawRectangleRec(retryBtn, LIGHTGRAY);
    DrawRectangleLinesEx(retryBtn, 3, BLACK);
    DrawText("RETRY", retryBtn.x + 50, retryBtn.y + 15, 30, BLACK);
    EndDrawing();
}
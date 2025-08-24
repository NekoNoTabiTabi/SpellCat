#include "RewardScreen.h"


void RewardScreen::Update(){
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mousePos, { 100, 200, 120, 180 })) {
            chosenCard = "Power Card";
            rewardChosen = true;
        }
        if (CheckCollisionPointRec(mousePos, { 300, 200, 120, 180 })) {
            chosenCard = "Heal 5";
            rewardChosen = true;
        }

        Rectangle skipBtn = { 400, 450, 200, 50 };
        if (CheckCollisionPointRec(mousePos, skipBtn)) {
            skipped = true;
            rewardChosen = true;
        }
    }
    }

void RewardScreen::Draw() {

    BeginDrawing();
    ClearBackground(BEIGE);
    DrawText("Choose your reward", 300, 100, 30, DARKGREEN);

    DrawRectangle(100, 200, 120, 180, LIGHTGRAY);
    DrawText("Power Card", 110, 250, 20, BLACK);

    DrawRectangle(300, 200, 120, 180, LIGHTGRAY);
    DrawText("Heal 5", 310, 250, 20, BLACK);

    EndDrawing();
}
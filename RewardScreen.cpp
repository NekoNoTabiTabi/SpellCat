#include "RewardScreen.h"
#include <iostream>

void RewardScreen::Update(){
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        for (int i = 0; i < rewardOptions.size(); i++) {
            Rectangle optionRect = { 100.0f + i * 200.0f, 200.0f, 120.0f, 180.0f };
            if (CheckCollisionPointRec(mousePos, optionRect)) {
               
                chosenCard = rewardOptions[i];
                std::cout << "Chosen Card: " << chosenCard.name;
                rewardChosen = true;
                return;
            }
        }

        // skip button
        Rectangle skipBtn = { 400, 450, 200, 50 };
        if (CheckCollisionPointRec(mousePos, skipBtn)) {
            std::cout << "Skipped reward" << std::endl;
            skipped = true;
            rewardChosen = true;
            return;
        }
    }
    

}

void RewardScreen::Draw() {

    BeginDrawing();
    ClearBackground(BEIGE);
    DrawText("Choose your reward", 300, 100, 30, DARKGREEN);

    for (int i = 0; i < rewardOptions.size(); i++) {
        Rectangle optionRect = { 100.0f + i * 150.0f, 200.0f, 120.0f, 180.0f };
        if (rewardOptions[i].type == "Attack") DrawRectangleRec(optionRect, ORANGE);
        if (rewardOptions[i].type == "Defense") DrawRectangleRec(optionRect, SKYBLUE);
        DrawRectangleLinesEx(optionRect, 2, BLACK);
        DrawText(rewardOptions[i].name.c_str(), optionRect.x + 40, optionRect.y + 70, 30, BLACK);
    }

    
    Rectangle skipBtn = { 400, 450, 200, 50 };
    DrawRectangleRec(skipBtn, DARKGRAY);
    DrawRectangleLinesEx(skipBtn, 2, BLACK);
    DrawText("Skip", skipBtn.x + 70, skipBtn.y + 15, 25, WHITE);

    EndDrawing();
}

void RewardScreen::GenerateRewards()
{
    rewardOptions.clear();

    // Example: generate 5 cards
    for (int i = 0; i < 5; i++) {
        Card c;
        c.id = GetRandomValue(1000, 9999); // unique ID
        c.name = std::string(1, 'A' + GetRandomValue(0, 25)); // random letter
        std::string possibleTypes[2] = { "Attack", "Defense" };

        c.type = possibleTypes[GetRandomValue(0,1)];
        c.effect = "Use in words";
        c.value = 1;

        rewardOptions.push_back(c);
    }
}

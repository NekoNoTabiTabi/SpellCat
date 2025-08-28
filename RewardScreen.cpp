#include "RewardScreen.h"
#include <iostream>

RewardScreen::RewardScreen(Deck& d) : deck(d) {
    GenerateRewards(d);
}


void RewardScreen::Update(){
    
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        for (int i = 0; i < rewardOptions.size(); i++) 
        {
            Rectangle optionRect = { 100.0f + i * 200.0f, 200.0f, 120.0f, 180.0f };
            if (CheckCollisionPointRec(mousePos, optionRect))
            {
               
                chosenCard = rewardOptions[i];
                std::cout << "Chosen Card: " << chosenCard.name;
                rewardChosen = true;
                return;
            }
        }

        // skip button
        Rectangle skipBtn = { 400, 450, 200, 50 };
        if (CheckCollisionPointRec(mousePos, skipBtn)) 
        {
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

void RewardScreen::GenerateRewards(Deck& deck)
{
    rewardOptions.clear();

    char letter = 'A' + GetRandomValue(0, 25);


    for (int i = 0; i < 5; i++) {
        char letter = 'A' + GetRandomValue(0, 25);
        const std::string letterType[2] = { "Attack", "Defense" };
        std::string type = letterType[GetRandomValue(1, 0)];
        //(const std::string & name, const std::string & type, int value);

        

        rewardOptions.push_back(deck.CreateCard(std::string(1, letter), type, 1));
    }
}

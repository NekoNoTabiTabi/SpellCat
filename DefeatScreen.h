#pragma once
#include <raylib.h>


class DefeatScreen {
public:
    Rectangle retryBtn = { 400, 300, 200, 60 };
    bool retryChosen = false;

    void Update();

    void Draw();

    void Reset() { retryChosen = false; };
};

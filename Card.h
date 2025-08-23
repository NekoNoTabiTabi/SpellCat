#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>


struct Card {
    std::string name;
    std::string type;   
    std::string effect; 
    int value;
    bool selected = false;
    Rectangle cardBounds;
    int selectionOrder = -1;
    
       
    
};

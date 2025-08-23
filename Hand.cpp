#include "Hand.h"
#include <raylib.h>


void Hand::DrawCard(Card& c) {
  
    DrawRectangleRec(c.cardBounds, LIGHTGRAY);
    DrawRectangleLinesEx(c.cardBounds, 2, BLACK);
    DrawText(
        c.name.c_str(),
        static_cast<int>(c.cardBounds.x + 10),
        static_cast<int>(c.cardBounds.y + 10),
        20,
        BLACK
    );
}


void Hand::LayoutHand(std::vector<Card>& hand)
{
    for (int i = 0; i < hand.size(); i++) {
        hand[i].cardBounds = { 50.0f + i * 150.0f, 400.0f, 120.0f, 180.0f };
    }
}

void Hand::DrawHand(int x, int y)
{
    // Example implementation: Draw each card in the hand horizontally
    int cardSpacing = 10;
    int cardWidth = 80;
    int cardHeight = 120;

    for (size_t i = 0; i < hand.size(); ++i)
    {
        Card& card = hand[i];
        card.cardBounds = { static_cast<float>(x + i * (cardWidth + cardSpacing)), static_cast<float>(y), static_cast<float>(cardWidth), static_cast<float>(cardHeight) };
        DrawRectangleRec(card.cardBounds, card.selected ? RED : DARKGRAY);
        DrawText(card.name.c_str(), static_cast<int>(card.cardBounds.x) + 5, static_cast<int>(card.cardBounds.y) + 5, 16, WHITE);
    }
}







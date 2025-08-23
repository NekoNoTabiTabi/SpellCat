#include <raylib.h>
#include <iostream>
#include "Deck.cpp"
#include "Hand.h"
#include "Player.h"
#include "Enemy.h"
int main() {

	int WINDOW_WIDTH =1000;
	int WINDOW_HEIGHT = 600;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TempRogueLike");

	//TEMP DECK
	Deck playerDeck;
	playerDeck.deck.push_back({ "S", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({ "A", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({ "T", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({ "R", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({ "I", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({ "K", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({ "E", "Letter", "Use in words", 1 });
	playerDeck.Shuffle();
	
	//TEMP PLAYER
	Hand playerHand;
	Player player;
	Enemy enemy;
	player.hp = 10;
	enemy.hp = 20;

	//button
	Rectangle confirmBtn = { 800, 500, 150, 50 };

	for (int i = 0; i < 8&&(!playerDeck.deck.empty()); i++) playerHand.Add(playerDeck.Draw());
	playerHand.LayoutHand(playerHand.hand);
	//MAIN GAME LOOP
	while (WindowShouldClose() == false) {
		static int selectionCounter = 0;
		//INPUT
		

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePos = GetMousePosition();

			for (Card& card : playerHand.hand) {
				if (CheckCollisionPointRec(mousePos, card.cardBounds)) {
					if (!card.selected) {
						card.selected = true;
						playerHand.wordBuffer.push_back(card); // store a copy
					}
					else {
						card.selected = false;
						// remove from buffer by matching ID or name
						playerHand.wordBuffer.erase(
							std::remove_if(
								playerHand.wordBuffer.begin(),
								playerHand.wordBuffer.end(),
								[&](const Card& c) { return c.name == card.name; } // use ID if you have one
							),
							playerHand.wordBuffer.end()
						);
					}
				}
			}


			if (CheckCollisionPointRec(mousePos, confirmBtn)) {
				std::string currentWord;
				for (Card& c : playerHand.wordBuffer) {
					currentWord += c.name;
				}

				if (!currentWord.empty()) {
					enemy.hp -= currentWord.length(); // damage example
					std::cout << "Played word: " << currentWord << std::endl;

					// reset buffer + card selections
					playerHand.wordBuffer.clear();
					for (Card& c : playerHand.hand) {
						c.selected = false;
					}
				}
			}

		}

		

		//UPDATE
		std::string currentWord;
		for (Card& c : playerHand.wordBuffer) {
			currentWord += c.name;
		}
		
		//DRAW
		BeginDrawing();
		ClearBackground(GRAY);

		
		DrawRectangleRec(confirmBtn, DARKGREEN);
		DrawRectangleLinesEx(confirmBtn, 2, BLACK);
		DrawText("CONFIRM", confirmBtn.x + 20, confirmBtn.y + 15, 20, WHITE);

		DrawText(("Player Health: " + std::to_string(player.hp)).c_str(), 50, 50, 20, BLACK);
		DrawText(("Enemy HP: " + std::to_string(enemy.hp)).c_str(), WINDOW_WIDTH-200, 50, 20, RED);
		DrawText(("Word: " + currentWord).c_str(), 50, 100, 30, DARKBLUE);
		playerHand.DrawHand(50,400);

		EndDrawing();
	}

	CloseWindow();
}
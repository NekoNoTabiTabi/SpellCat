#include <raylib.h>
#include <iostream>
#include "Deck.cpp"
#include "Hand.h"
#include "Player.h"
#include "Enemy.h"
#include <unordered_set>
#include <fstream>
#include <string>
#include "Dictionary.h"



int main() {

	int WINDOW_WIDTH =1000;
	int WINDOW_HEIGHT = 600;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TempRogueLike");
	
	//dictionary
	Dictionary dict;
	dict.LoadDictionary("words.txt");
	//TEMP PLAYER
	Hand playerHand;
	Player player;
	Enemy enemy;
	player.hp = 10;
	enemy.PlanTurn();


	Deck playerDeck;
	playerDeck.deck.push_back({1, "S", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({2, "A", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({3, "T", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({4, "R", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({5, "I", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({6, "K", "Letter", "Use in words", 1 });
	playerDeck.deck.push_back({7, "E", "Letter", "Use in words", 1 });
	playerDeck.Shuffle();


	//button
	Rectangle confirmBtn = { 800, 500, 150, 50 };
	int handLimit=8;
	for (int i = 0; i < handLimit && (!playerDeck.deck.empty()); i++) playerHand.Add(playerDeck.Draw());
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
						
						playerHand.wordBuffer.erase(
							std::remove_if(
								playerHand.wordBuffer.begin(),
								playerHand.wordBuffer.end(),
								[&](const Card& c) { return c.id == card.id; } 
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
					int damage;

					//needs to be reworked to include defense
					
					damage = player.CalculateDamage(currentWord, dict.IsValidWord(currentWord));
											
					enemy.hp -= damage;
					 
					std::cout << "Played word: " << currentWord
						<< " (Damage: " << damage << ")" << std::endl;
					// --- discard logic ---
					for (Card& c : playerHand.wordBuffer) {
						// find this card in hand and move it to discard pile
						auto it = std::find_if(playerHand.hand.begin(), playerHand.hand.end(),
							[&](const Card& h) { return h.id == c.id; });

						if (it != playerHand.hand.end()) {
							Card discarded = *it;
							discarded.selected = false;  // reset here

							playerHand.discardPile.push_back(discarded);
							playerHand.hand.erase(it);
						}
					}
					if (playerDeck.deck.empty() && !playerHand.discardPile.empty()) {
						playerDeck.deck = playerHand.discardPile;
						playerHand.discardPile.clear();
						playerDeck.Shuffle();
					}
					// Reset buffer
					playerHand.wordBuffer.clear();

					// Re-layout hand
					playerHand.LayoutHand(playerHand.hand);
				}

				if (enemy.hp > 0) {
					enemy.TakeTurn(player.hp);
					enemy.PlanTurn();
				}

			}

			

		}

		

		//UPDATE
		if (playerHand.hand.size() < handLimit) {
			int cardsToDraw = handLimit - playerHand.hand.size();
			playerHand.DrawingCardsFromDeck(playerDeck, cardsToDraw);
		}
		

		std::string currentWord;
		for (Card& c : playerHand.wordBuffer) {
			currentWord += c.name;
		}
		

		//DRAW

		if (!playerHand.wordBuffer.empty()) {
			//note to self modify this to be just player class damage calcution and modify that to include a volume
			int dmg = player.CalculateDamage(currentWord, dict.IsValidWord(currentWord));

			DrawText(("Word Damage: " + std::to_string(dmg)).c_str(),
				50, 350, 20, RED);
		}
		BeginDrawing();
		ClearBackground(GRAY);

		
		DrawRectangleRec(confirmBtn, DARKGREEN);
		DrawRectangleLinesEx(confirmBtn, 2, BLACK);
		DrawText("CONFIRM", confirmBtn.x + 20, confirmBtn.y + 15, 20, WHITE);

		DrawText(("Player Health: " + std::to_string(player.hp)).c_str(), 50, 50, 20, BLACK);
		DrawText(("Enemy HP: " + std::to_string(enemy.hp)).c_str(), WINDOW_WIDTH-200, 50, 20, RED);
		DrawText(("Enemy plans to deal " + std::to_string(enemy.damage) + " dmg").c_str(),
			WINDOW_WIDTH - 300, 80, 20, MAROON);
		DrawText(("Word: " + currentWord).c_str(), 50, 100, 30, DARKBLUE);

		DrawText(("Deck: " + std::to_string(playerDeck.deck.size())).c_str(),
			50, 190, 20, BLACK);

		DrawText(("Discard: " + std::to_string(playerHand.discardPile.size())).c_str(),
			50, 130, 20, DARKGRAY);

		DrawText(("Hand: " + std::to_string(playerHand.hand.size())).c_str(),
			50, 160, 20, BLUE);
		if (!dict.IsValidWord(currentWord)&&!currentWord.empty()) {
			DrawText("Not a valid word!", 400, 300, 30, RED);
		}
		playerHand.DrawHand(50,400);

		
		EndDrawing();
	}

	CloseWindow();
}
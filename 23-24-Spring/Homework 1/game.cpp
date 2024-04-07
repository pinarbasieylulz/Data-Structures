#include <iostream>
#include <stack>
#include <ctime>
#include <cstdlib>
#include "doublelinklist.h"
#include "objects.h"

using namespace std;

int randomAction(int max) {
    return rand() % max + 1;
}

int randomObject(int max) {
    return rand() % max;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    GameState initialState;
    initialState.create_init_state();

    stack<GameState> gameStack;
    gameStack.push(initialState);

    while (!gameStack.empty()) {
        GameState currentState = gameStack.top();
        gameStack.pop();

        if (currentState.win) {
            cout << "Congratulations! You have won the game!" << endl;
            break;
        }

        if (currentState.lose) {
            cout << "Game Over! You have lost the game." << endl;
            continue;
        }

        currentState.print_situation();

        int action, object;
        action = randomAction(5); // Choose a random action
        object = randomObject(currentState.rooms.get(currentState.room_id)->room_objects.elemcount + currentState.inventory.elemcount);

        int effectID = currentState.advance(action, object);
        if (effectID == -1) {
            if (!gameStack.empty()) {
                gameStack.pop(); // Remove the current state as it led to a loss
            }
            continue;
        } else if (effectID > 0) {
            gameStack.push(currentState); // Push the current state with the change onto the stack
        }
    }

    return 0;
}

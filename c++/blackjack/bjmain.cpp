#include <iostream>

using namespace std;

int numdecks = 6;

int main() {
    int i, deck[11];
    for (i = 1; i <= 9; i++)
        deck[i] = 4 * numdecks;
    deck[10] = 16 * numdecks;
    deck[0] = 52 * numdecks;
}

void dealer() {
    // Dealer logic to be implemented
}
#include <iostream>

using namespace std;

int numdecks = 6;

void dealer(int oldtotal, int oldsofttotal, int numcards, double probability, int deck[], double dealerprob[]);

int main() {
    int i;
    int deck[11];
    double dealerprob[7];
    for (i = 1; i <= 9; i++) {
        deck[i] = 4 * numdecks;
    }
    deck[10] = 16 * numdecks;
    deck[0] = 52 * numdecks;
    dealer(5, 0, 1, 1.0, deck, dealerprob);
    for (i = 0; i <= 6; i++) {
        cerr << i << "\t" << dealerprob[i] << endl;
    }
}

// dealer probabitlies are 17 to 21, bj, and bust (0, 1, 2, 3, 4, 5, 6)
void dealer(int oldtotal, int oldsofttotal, int numcards, double probability, int deck[], double dealerprob[]) {
    int i;
    int nextcard;
    int newtotal;
    int newace;
    if (numcards == 1){
        for (i = 0; i <= 6; i++)
            dealerprob[i] = 0.0;
    }
    for (nextcard = 1; nextcard <= 10; nextcard++) {
        if (deck[nextcard] == 0) continue;  // Skip if no cards left
        
        double newProbability = probability * ((double)deck[nextcard] / (double)deck[0]);
        deck[nextcard]--;
        deck[0]--;
        newtotal = oldtotal + nextcard;
        newace = oldsofttotal;
        if (nextcard == 1) {
            newace++;
        }
        // calculate best total for dealer hand with aces counting as 1 or 11
        int besttotal = newtotal;
        if (newace >= 1 && newtotal <= 11) {
            // count an ace as 11 instead of 1 if it doesn't cause a bust
            besttotal = newtotal + 10;
        }
        if ((numcards == 2) && (besttotal == 21)) {
            // dealer has blackjack (two-card 21)
            dealerprob[5] += newProbability;
        } else if (besttotal > 21) {
            // dealer busts
            dealerprob[6] += newProbability;
        } else if (besttotal >= 17) {
            // dealer has soft 17
            dealerprob[besttotal - 17] += newProbability;
        } else {
            // dealer has 16 or less and must hit
            dealer(besttotal, newace, numcards + 1, newProbability, deck, dealerprob);
        }
        deck[0]++;
        deck[nextcard]++;
    }
}
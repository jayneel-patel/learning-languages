#include <iostream>

using namespace std;

int numdecks = 6;

int main() {
    int i;
    int deck[11];
    double dealerprob[7];
    for (i = 1; i <= 9; i++)
        deck[i] = 4 * numdecks;
    deck[10] = 16 * numdecks;
    deck[0] = 52 * numdecks;
    dealer(5, 0, 1, 1.0, deck, dealerprob);
    for (i = 0; i <= 6; i++) {
        cout << i << ": " << dealerprob[i] << "\n" <<endl;
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
        probability *= ((double)deck[nextcard] / (double)deck[0]);
        deck[nextcard]--;
        deck[0]--;
        newtotal = oldtotal + nextcard;
        newace = oldsofttotal;
        if (nextcard == 1) {
            newace++;
        }
        if ((numcards == 2) &&  (newtotal == 11) && (newace == 1)) {
            // dealer has blackjack or natural 21
            dealerprob[5] += probability;
        } else if (newtotal > 21) {
            // dealer busts
            dealerprob[6] += probability;
        } else if (newtotal >= 17) {
            // dealer has hard 17 or more
            dealerprob[newtotal - 17] += probability;
        } else if (newtotal >= 7 && newtotal <= 11 && newace >= 1) {
            // dealer has soft 17
            dealerprob[newtotal - 17] += probability;
        } else {
            // dealer has 16 or less and must hit
            dealer(newtotal, newace, numcards + 1, probability, deck, dealerprob);
        }
        deck[0]++;
        deck[nextcard]++;
    }
}
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <limits>
using namespace std;
struct Card {										// Create a card with a suit and value
	int cardSuit;
	int cardValue;
	Card (const int s , const int n) : cardSuit (s), cardValue(n) {}	// Constructor for card
};

ostream& operator << (ostream& o, const Card& c) {	// '<<' operator for card
	switch (c.cardSuit) {
		case 0:	o << "H"; break;
		case 1:	o << "S"; break;
		case 2:	o << "D"; break;
		case 3:	o << "C"; break;
		default : break;
	}
	switch (c.cardValue) {
		case 10: o << "10"; break;
		case 11: o << "J "; break;
		case 12: o << "Q "; break;
		case 13: o << "K "; break;
		case 14: o << "A "; break;
		default: o << c.cardValue << " "; break;
	}
	return o;
}
bool operator < (const Card& lhs, const Card& rhs){	// '<' operator for cars, sort in order of: 'h,s,d,c'
	if(lhs.cardSuit == rhs.cardSuit) return lhs.cardValue < rhs.cardValue;
	else return lhs.cardSuit < rhs.cardSuit;
}
struct Deck {										// Create a deck of cards
	vector <Card> deck;
	Deck (){										// Constructor for deck (52 cards)
	for(int i = 0; i < 4 ; i++)
		for(int j = 2; j < 15; j++)
			deck.push_back(Card(i,j));}
};
vector<int> dealCards (const vector <int>& cn, const int p){	// Deals the cards to player
	vector <int> o;
	for (int start = p*7, end = (p+1)*7 ; start < end ; start++)
		o.push_back(cn[start]);
	return o;
}
struct Player {										// Create a player
	int player;
	vector <int> hand;
	int cardSpot;
	Player (const vector <int>& c, const int p ) : player(p), hand (dealCards(c, p)), cardSpot(0) {}// Constructor for player
	void set(const Player& p, const int spot){		// Adds a card to the players hand
		hand.push_back(p.hand[spot]);}
	void del (const int spot){
		hand.erase(hand.begin() + (spot));}			// Removes a card from players hand
};
ostream& operator << (ostream& o, const Player& p){	// '<<' operator for player
	return o << p.player;}
int passWhat (const Deck& dc,const Player& p){		// Determines what card AI chooses to give up
	int h = 0, s = 0, d = 0, c = 0;
	for (int i = 0, l = p.hand.size(); i < l ; i++)
	{	switch (dc.deck[p.hand[i]].cardSuit) {		// Counts how often the suit appear
			case 0:	h++; break;
			case 1:	s++; break;
			case 2:	d++; break;
			case 3:	c++; break;
			default : break;
	}	}
	if (c!=0 && (d==0 || c <= d) && (s==0 ||c <= s) && (h==0 || c <= h) )		// Discard Clover
		return c+d+s+h-1;				// Return the position of the card that will be discarded
	else if (d!=0 && (h==0 || d <= h) && (s==0 || d <= s ) && (c==0 || h <= c) )// Discard Diamonds
			return d+s+h-1;					// Return the position of the card that will be discarded
	else if (s!=0 && (d==0 || s <= d) && (c==0 || s <= c ) && (h==0 || s <= h) )// Discard Spades
			return s+h-1;					// Return the position of the card that will be discarded
	else 																		// Discard Hearts
			return h-1;						// Return the position of the card that will be discarded
}
void printCards(const Player& p ,const Deck& d){			// Prints the cards in the player's hand
	for(int i = 0; i < 7 ; i++)
			cout << "\t"<<"("<< (char)('a'+i) <<") "<< d.deck[p.hand[i]];
	cout << "\n";
}
void printAllCards(const vector <Player>& p,Deck& gameDeck){// Prints all player's hands
	for (int i = 0, l = p.size(); i < l ; ++i){
		cout <<"Player "<< p[i].player<< ": ";
		printCards(p[i],gameDeck);
	}
}
bool winner(const vector <Player>& p, const Deck& d){		// Determines if player won the game
	bool t_f = false;
	for (int a = 0, le = p.size(); a < le; a ++){
	int c = 1;
	for (int i = 1, l = p[a].hand.size(); i < l; ++i)
		if (d.deck[p[a].hand[i]].cardSuit == d.deck[p[a].hand[0]].cardSuit)
			++c;
	if (c == 7){											// All 7 cards have the same suit
		cout <<"\nMy Ship Sails! ---  PLAYER "<< p[a] << " WON!"<<endl;
		t_f = true;}
	}
	return t_f;
}
int main() {
	srand(time(0));
	bool loop = true;
	char input;
	Deck gameDeck;
	vector <int> shuffled;									// Creates a vector with positions of cards
	for (int i = 0; i < 51; i++)							// Fill vector
		shuffled.push_back(i);
	random_shuffle(shuffled.begin(), shuffled.end());		// Shuffles the positions
	vector <Player> p;
	for (int i = 0; i < 5; ++i)
		p.push_back(Player (shuffled,i));
	cout << "Welcome to My Ship Sails, you need to gather cards with the same suit to win the game!"<<endl;
	cout << "All hands are sorted in order: Hearts, Spades, Diamonds, Clubs" << endl;
	while (loop){
		for (int i = 0, l = p.size(); i < l ; i++)			// All player hand is sorted in order of: 'h,s,d,c'
			sort(p[i].hand.begin() , p[i].hand.end());
		cout << "\nYou have: "; printCards(p[0] , gameDeck);// Prints player 0's hand
		while (true){
			cout << "Which one do you want to replace?"; cin>> input;
			if ((int) input > 96 && (int) input < 104)		// 'a' -> 'g' is good
				break;
			else if ((int)input == 63)						// '?' cheat activated, shows all hands
				printAllCards(p,gameDeck);
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout <<"ERROR with input"<< endl;}			// Error with input
			}
		p[0].cardSpot = ((int) input)-97;					// Position of the soon to be replaced card player 0
		for (int i = 1; i < 5; ++i){
			p[i].cardSpot = passWhat(gameDeck, p[i]);		// Position of the soon to be replaced card player
			cout << "HINT: Player "<<i-1<<" passed " <<gameDeck.deck[p[i-1].hand[p[i-1].cardSpot]] <<" to player " <<i<<endl;// Print hints
			p[i].set(p[i-1],p[i-1].cardSpot);				// Transfer player's card to next player
			p[i-1].del(p[i-1].cardSpot);					// Delete player's transfered card
			}
		cout << "HINT: Player "<<4<<" passed " << gameDeck.deck[p[4].hand[p[4].cardSpot]] <<" to player 0"<<endl; // Print hint (player 4)
		p[0].set(p[4],p[4].cardSpot);						// Transfer player 4's card to player 0
		p[4].del(p[4].cardSpot);							// Delete player 4's transfered card
		loop = !winner(p,gameDeck);							// Did anyone win, if yes -> loop is false -> game ends
		}
	cout << "[Final card distribution]" << endl;
	printAllCards(p,gameDeck);								// Print all cards
	return 0;
}

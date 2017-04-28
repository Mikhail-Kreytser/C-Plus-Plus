#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

struct MyGameDef { 											// professional way to define global enumerable values.
  enum Player { Human, Progm, Empty };
  Player m_player;
  MyGameDef (const Player p) : m_player(p) {}
  operator Player() const { return m_player; }
};

class Cell {      											// representing a cell of a board.
  MyGameDef::Player m_occu; 								// marked 'Empty', 'Human', and 'Progm'.
public:
  Cell() : m_occu(MyGameDef::Empty) {}
  void setTurn(const MyGameDef::Player p) { assert(!isOccupied()); m_occu = p; }
  bool isOccupied() const { return m_occu != MyGameDef::Empty; }
  bool isMe(const MyGameDef::Player p) const { return m_occu == p; }
  void erase() { m_occu = MyGameDef::Empty; }
  friend ostream& operator<<(ostream& o, const Cell& c) {
    switch(c.m_occu) {
    case MyGameDef::Empty: return o << " . ";
    case MyGameDef::Human: return o << " o ";
    case MyGameDef::Progm: return o << " x ";
    default: abort();
    }
  }
};

class Eval {
  int m_conn; // connected to me.
  int m_poss; // possible spaces.
public:
  Eval(const int c = 0, const int p = 0) : m_conn(c), m_poss(p) {}
  bool isConnect4() const { return m_conn >= 3; }
  bool isWinning()  const { return m_conn == 2 && m_poss >= 1; }
  int getValue()  const {											//Point system
	  if (m_conn >= 3 ) return 100;
	  else if (m_conn == 2 && m_poss >= 1) return 50;
	  else return m_conn * 2 + m_poss; }
  friend ostream& operator<<(ostream& o, const Eval& e) {
    return o << "(" << e.m_conn << ", " << e.m_poss << ")";
  }
};

class Turn {
  char m_turn;
  int  m_score;
public:
  Turn(const char c = '\0', const int s = 0) : m_turn(c), m_score(s) {}
  char getTurn() const { return m_turn; }
  int getScore() const { return m_score; }
  friend bool operator<(const Turn& lhs, const Turn& rhs) {
    return lhs.m_score < rhs.m_score;
  }
  friend ostream& operator<<(ostream& o, const Turn& t) {
    return o << "\t--> (" << t.m_turn << ") with score " << t.m_score;
  }
};

class Board {       // represents Connect Four board.
  int m_row;
  int m_col;
  const int m_max;  // used to detect tie.
  int m_num;        // the number of the marks placed.
  vector<vector<Cell> > m_map;
  Eval vertical(const int r, const int c, const MyGameDef::Player p) const {
	    int count = 0, possible = 0;
	    bool connected = true;
	    for (int row = r + 1, saw = 0; row < m_row && saw < 3; ++row, ++saw) {	// Up
	    	if (m_map[row][c].isMe(p)) {
	    		if (++count > 2) { if (connected) break; }
	    		continue;
	      }
	      connected = false;
	      if (m_map[row][c].isOccupied()) break;
	      ++possible;
	    }
	    for (int row = r - 1, saw = 0; row >= 0 && saw < 3; --row, ++saw) { 	// Down
	      if (m_map[row][c].isMe(p)) {
		if (++count > 2) { if (connected) break; }
		continue;
	      }
	      connected = false;
	      if (m_map[row][c].isOccupied()) break;
	      ++possible;
	    }
	    return Eval(count, possible);
	  }
  Eval horizontal(const int r, const int c, const MyGameDef::Player p) const {
	  int count = 0, possible = 0;
	  bool connected = true;
	  for (int col = c + 1, saw = 0; col < m_col && saw < 3; ++col, ++saw) { 	// Right
		  if (m_map[r][col].isMe(p)) {
			  if (++count > 2) { if (connected) break; }
			  continue;
		  }
		  connected = false;
		  if (m_map[r][col].isOccupied()) break;
		  ++possible;
	  }
	  for (int col = c - 1, saw = 0; col >= 0 && saw < 3; --col, ++saw) { 		// Left
		  if (m_map[r][col].isMe(p)) {
			  if (++count > 2) { if (connected) break; }
			  continue;
		  }
		  connected = false;
		  if (m_map[r][col].isOccupied()) break;
		  ++possible;
	  }
	  return Eval(count, possible);
  }
  Eval leftup(const int r, const int c, const MyGameDef::Player p) const {
	  int count = 0, possible = 0;
	  bool connected = true;
	  for (int col = c - 1, row = r + 1, saw = 0; col >= 0 && row < m_row && saw < 3; --col, ++row, ++saw) { // left up
		  if (m_map[row][col].isMe(p)) {
			  if (++count > 2) { if (connected) break; }
			  continue;
		  }
		  connected = false;
		  if (m_map[row][col].isOccupied()) break;
		  ++possible;
	  }
	  for (int col = c + 1, row = r - 1, saw = 0; col < m_col && row >= 0 && saw < 3; ++col, --row, ++saw) { // right down
		  if (m_map[row][col].isMe(p)) {
			  if (++count > 2) { if (connected) break; }
			  continue;
		  }
		  connected = false;
		  if (m_map[row][col].isOccupied()) break;
		  ++possible;
	  }
	  return Eval(count, possible);
  }
  Eval rightup(const int r, const int c, const MyGameDef::Player p) const {
	  int count = 0, possible = 0;
	  bool connected = true;
	  for (int col = c + 1, row = r + 1, saw = 0 ; col < m_col && row < m_row && saw < 3; ++col, ++row, ++saw) { // right up
		  if (m_map[row][col].isMe(p)) {
			  if (++count > 2) { if (connected) break; }
			  continue;
		  }
		  connected = false;
		  if (m_map[row][col].isOccupied()) break;
		  ++possible;
	  }
	  for (int col = c - 1, row = r - 1, saw = 0; col >= 0 && row >= 0 && saw < 3; --col, --row, ++saw) { // left down
		  if (m_map[row][col].isMe(p)) {
			  if (++count > 2) { if (connected) break; }
			  continue;
		  }
		  connected = false;
		  if (m_map[row][col].isOccupied()) break;
		  ++possible;
	  }
	  return Eval(count, possible);
  }
public:
  Board(const int r = 6, const int c = 7) :
    m_row(r), m_col(c), m_max(r * c), m_num(0) {
    vector<Cell> arow(m_col, Cell());
    for (int i = 0; i < m_row; ++i) m_map.push_back(arow);
  }
  bool isTie() const { return m_num >= m_max; }
  bool isValid(const char c, const MyGameDef::Player p) {
    int col = c - 'a';
    if (col < 0 || col >= m_col) return false;
    bool placed = false;
    for (int row = m_row - 1; row >= 0; --row) {
      if (m_map[row][col].isOccupied()) continue;

      placed = true;
      ++m_num;
      m_map[row][col].setTurn(p); break;
    }
    return placed;
  }
  bool isWon(const char c, const MyGameDef::Player p) const {
    int col = c - 'a', row = 0;
    for (; row < m_row; ++row) {
      if (!m_map[row][col].isOccupied()) continue;

      assert(m_map[row][col].isMe(p));
      break;
    }
    Eval V = vertical(row, col, p);   // check vertical line.
    Eval H = horizontal(row, col, p); // check horizontal line.
    Eval L = leftup(row, col, p);     // check leftup diagnal line.
    Eval R = rightup(row, col, p);    // check rightup diagnal line.
    return V.isConnect4() || H.isConnect4() || L.isConnect4() || R.isConnect4();
  }
  int find_Val(const int r, const int c,const MyGameDef::Player p){
  	  return (horizontal(r,c,p).getValue() + vertical(r,c,p).getValue() + leftup(r,c,p).getValue() + rightup(r,c,p).getValue());
    }
  Turn findBestMove(const MyGameDef::Player p,const char other_Player_Pick, bool show = false) {
	  MyGameDef::Player other_player;
	  vector <Turn> repeats;				//If there are more then one possible moves this vector holds them
	  vector <Turn> score (m_col);
	  string player;
	  switch (p) {
		case MyGameDef::Human: player = "you choose"; other_player = MyGameDef::Progm;	break;
		case MyGameDef::Progm: player = "the computer chooses"; other_player = MyGameDef::Human; break;
		default: cout << "ERROR..."<<endl; abort();
	}
	  for (int c = 0; c < m_col; ++c){					// Finds all possible moves and their score
		  for (int r = 0 ; r <  m_row; ++r)
			  if(!m_map[r][c].isOccupied()){
				  score[c] = Turn((char)('a' + c), find_Val(r,c,p));
			  }
if(show)  cout << "If "<<player<<" --> ("<<(char) (c + 'a')<<") the score will be: "<< score[c].getScore()<< endl;
	  }
	  Turn go = score[0];
	  for (int i = 0, stop = m_col; i < stop; ++i){				// Checks which move has the highest score
		  if(go.getScore() == score[i].getScore()){
			  repeats.push_back(score[i]);						// If score is the same as max, it saves that move
			  }
		  else if( go < score[i]){								// New Max
			  go = score[i];									// Saves new move
			  repeats.erase(repeats.begin(),repeats.end());		// Resets array
			  repeats.push_back(go);
		  }
	  }
	  if(go.getScore() > 100)									// Checks if the score is more then 100
		  return go;											// If the score is more the 100 the move is good

	  int mini = 7;
	  if(repeats.size() > 1)											// *If there are 2 or more moves with same score
		  for (int i = 0, l = repeats.size(); i < l; ++i){				// *the move closest to the previous played column
			  if(mini > abs((int)other_Player_Pick-(int)repeats[i].getTurn())){// *played by the other player is chosen
				  mini = abs((int)other_Player_Pick- (int)repeats[i].getTurn());
				  go = repeats[i];
			  }
		  }
	  go = validate_move(score, go, p, other_player);					// Checks if the move gives other player an advantage
	  if(show)  cout << endl << "If "<< player << " (" << go.getTurn()<< "), The highest score turn will be chosen."<< endl;
	  return go;
  }
 //* This function makes sure that the move right above is not wining for the opponent  *//
 //* it also makes sure that the move right above is not wining for the current player,	*//
 //* if it is winning for anyone then it avoids choosing that space. This way it tries  *//
 //* not to let the opponent win and it doesn't let the opponent block a winning space	*//
 Turn validate_move(vector <Turn>& scores, Turn& go, const MyGameDef::Player p, const MyGameDef::Player otherPlayer){
	 int count = 0;
	 for(int i = 0, l = scores.size(); i < l; ++i)		// Makes sure there are more possible moves
		 if(scores[i].getScore() > 0)
			 ++count;
	 if(count > 1){
		 isValid(go.getTurn(), p);						// Sets "ghost" move
		 int c = ((int) go.getTurn() - 'a');
		 int r = 0;
		 for (int row = 0 ; row < m_row ; ++row)
			 if(m_map[row][c].isOccupied())
				 ++r;
		 if(r == m_row || isWon(go.getTurn(),p)){			// If move is at the top of the board or winning
			 erase(go.getTurn(), p);						// Erases "ghost" move
			 return go;										// Good move
		 }
		 if(isValid(go.getTurn(), otherPlayer) && isWon(go.getTurn(),otherPlayer)){ // Sets other players "ghost" move and checks if its winning
			 erase(go.getTurn(), otherPlayer);				// Erase other player's "ghost" move
			 erase(go.getTurn(), p);						// Erase player's "ghost" move
			 scores[c] = Turn ((char)('a' + c),0);			// Sets bad move score to 0
			 go = scores[0];								// Replaces bad move with default
			 for(int i = 0, l = scores.size(); i < l; ++i)
				 if(scores[i].getScore() > go.getScore())
					 go = scores[i];						// New best move
			 go = validate_move(scores, go, p, otherPlayer);// Checks new best move (recursion)
			 return go;										// Move is now good or it is the best possible move
		 }
		 erase(go.getTurn(), otherPlayer);					// Erase other player's "ghost" move
		 if(isValid(go.getTurn(), p) && isWon(go.getTurn(),p)){ // Sets player's "ghost" move and checks if its winning
			 erase(go.getTurn(), p);						// Erase player's "ghost" move
			 erase(go.getTurn(), p);						// Erase player's "ghost" move
			 scores[c] = Turn ((char)('a' + c),0);			// Sets bad move score to 0
			 go = scores[0];								// Replaces bad move with default
			 for(int i = 0, l = scores.size(); i < l; ++i)
				 if(scores[i].getScore() > go.getScore())
					 go = scores[i];						// New best move
			 go = validate_move(scores, go, p, otherPlayer);// Check New best move (recursion)
			 return go;										// Move is now good or it is the best possible move
		 }
		 else {												// Is not winning
			 erase(go.getTurn(), p);						// Erase player's "ghost" move
			 erase(go.getTurn(), p);						// Erase player's "ghost" move
			 return go;										// Good move
		 }
	 }
	 return go;												// Good move
 }
 void erase(const char c, const MyGameDef::Player p) {
	  int col = c - 'a';
	  for (int row = 0; row < m_row; ++row) {
		  if (!m_map[row][col].isOccupied()) continue;
		  assert(m_map[row][col].isMe(p));
		  m_map[row][col].erase(); break;
	  }
	  --m_num;
  }
  friend ostream& operator<<(ostream& o, const Board& m) {
    o << endl;
    for (int col = 0; col < m.m_col; ++col)
      o << setw(3) << (char)('a' + col) << ' ';
    o << endl;
    for (int row = 0; row < m.m_row; ++row) {
      o << '|';
      for (int col = 0; col < m.m_col; ++col)
	o << setw(3) << m.m_map[row][col] << '|';
      o << endl;
    }
    o << endl;
    return o;
  }
};

int main() {
  Board b(6, 7); // traditional size Connect Four game.
  while (!b.isTie()) {
    cout << b;   // showing board status.
    cout << "Enter your turn: "; char turn; Turn cpu; cin >> turn;
    if (turn == '?') {
    	char tempH = b.findBestMove(MyGameDef::Human,cpu.getTurn(), true).getTurn();
    	cout <<"-------------------------------------------"<<endl;
    	b.findBestMove(MyGameDef::Progm,tempH, true);
    	cout <<"-------------------------------------------"<<endl;
    	if(b.findBestMove(MyGameDef::Human,cpu.getTurn(), false).getScore() < b.findBestMove(MyGameDef::Progm, tempH, false).getScore())
    		cout << "You should play defensively, Block his move...\nYou should chose ("<< b.findBestMove(MyGameDef::Progm, tempH, false).getTurn()<<")"<<endl;
    	else
    		cout << "You should play offensively...\nYou should chose ("<< b.findBestMove(MyGameDef::Human,cpu.getTurn(), false).getTurn()<<")"<<endl;
    	continue;
    }
    while (!b.isValid(tolower(turn), MyGameDef::Human)) {
      cout << "Invalid input, try again: "; cin >> turn;
    }
    turn = tolower(turn);
    if (b.isWon(turn, MyGameDef::Human)) {
      cout << "You won :)";
      break;
    }
    cpu = b.findBestMove(MyGameDef::Progm,turn, false);	// If if the human has a better move the computer will play defensively
    if( cpu.getScore() <= b.findBestMove(MyGameDef::Human,cpu.getTurn(), false).getScore() && cpu.getScore() < 100){
    	turn = b.findBestMove(MyGameDef::Human,turn, false).getTurn();
    }
    else
    	turn = cpu.getTurn();
    cout << "The computer put his move on: (" << turn << ")"<<endl;
    if (!b.isValid(tolower(turn), MyGameDef::Progm)) {
      cout << "Serious error occurred, program cannot continue..." << endl;
      abort();
    }
    if (b.isWon(turn, MyGameDef::Progm)) {
      cout << "You lost :(";
      break;
    }
  }
  if (b.isTie()) cout << "Tied..." << endl;
  cout << " Final board is" << endl << b << "Bye..." << endl;
  return 0;
}

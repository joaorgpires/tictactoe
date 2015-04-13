#include <bits/stdc++.h>
#define W 1
#define D 0
#define L -1
#define INF 1000

using namespace std;

struct Node {
  char state[3][3];
  int u;
  vector<Node*> nei; //childs
};

int nodes = 0;

bool terminal_test(Node* cur) { //--------------------TERMINAL TEST
  if((cur->state[0][0] == 'X' && cur->state[0][1] == 'X' && cur->state[0][2] == 'X')
     || (cur->state[1][0] == 'X' && cur->state[1][1] == 'X' && cur->state[1][2] == 'X')
     || (cur->state[2][0] == 'X' && cur->state[2][1] == 'X' && cur->state[2][2] == 'X')
     || (cur->state[0][0] == 'X' && cur->state[1][1] == 'X' && cur->state[2][2] == 'X')
     || (cur->state[2][0] == 'X' && cur->state[1][1] == 'X' && cur->state[0][2] == 'X')
     || (cur->state[0][0] == 'X' && cur->state[1][0] == 'X' && cur->state[2][0] == 'X')
     || (cur->state[0][1] == 'X' && cur->state[1][1] == 'X' && cur->state[2][1] == 'X')
     || (cur->state[0][2] == 'X' && cur->state[1][2] == 'X' && cur->state[2][2] == 'X'))
    return true;
  
  else if((cur->state[0][0] == 'O' && cur->state[0][1] == 'O' && cur->state[0][2] == 'O')
	  || (cur->state[1][0] == 'O' && cur->state[1][1] == 'O' && cur->state[1][2] == 'O')
	  || (cur->state[2][0] == 'O' && cur->state[2][1] == 'O' && cur->state[2][2] == 'O')
	  || (cur->state[0][0] == 'O' && cur->state[1][1] == 'O' && cur->state[2][2] == 'O')
	  || (cur->state[2][0] == 'O' && cur->state[1][1] == 'O' && cur->state[0][2] == 'O')
	  || (cur->state[0][0] == 'O' && cur->state[1][0] == 'O' && cur->state[2][0] == 'O')
	  || (cur->state[0][1] == 'O' && cur->state[1][1] == 'O' && cur->state[2][1] == 'O')
	  || (cur->state[0][2] == 'O' && cur->state[1][2] == 'O' && cur->state[2][2] == 'O'))
    return true;
  
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(cur->state[i][j] == '_')
	return false;
    }
  }
  
  return true;
}

int utility(Node* cur) { //-------------------------FUNCTION UTILITY
  if((cur->state[0][0] == 'X' && cur->state[0][1] == 'X' && cur->state[0][2] == 'X')
     || (cur->state[1][0] == 'X' && cur->state[1][1] == 'X' && cur->state[1][2] == 'X')
     || (cur->state[2][0] == 'X' && cur->state[2][1] == 'X' && cur->state[2][2] == 'X')
     || (cur->state[0][0] == 'X' && cur->state[1][1] == 'X' && cur->state[2][2] == 'X')
     || (cur->state[2][0] == 'X' && cur->state[1][1] == 'X' && cur->state[0][2] == 'X')
     || (cur->state[0][0] == 'X' && cur->state[1][0] == 'X' && cur->state[2][0] == 'X')
     || (cur->state[0][1] == 'X' && cur->state[1][1] == 'X' && cur->state[2][1] == 'X')
     || (cur->state[0][2] == 'X' && cur->state[1][2] == 'X' && cur->state[2][2] == 'X'))
    return W;
  
  else if((cur->state[0][0] == 'O' && cur->state[0][1] == 'O' && cur->state[0][2] == 'O')
	  || (cur->state[1][0] == 'O' && cur->state[1][1] == 'O' && cur->state[1][2] == 'O')
	  || (cur->state[2][0] == 'O' && cur->state[2][1] == 'O' && cur->state[2][2] == 'O')
	  || (cur->state[0][0] == 'O' && cur->state[1][1] == 'O' && cur->state[2][2] == 'O')
	  || (cur->state[2][0] == 'O' && cur->state[1][1] == 'O' && cur->state[0][2] == 'O')
	  || (cur->state[0][0] == 'O' && cur->state[1][0] == 'O' && cur->state[2][0] == 'O')
	  || (cur->state[0][1] == 'O' && cur->state[1][1] == 'O' && cur->state[2][1] == 'O')
	  || (cur->state[0][2] == 'O' && cur->state[1][2] == 'O' && cur->state[2][2] == 'O'))
    return L;
    
  return D;
}

Node* setVal(Node* cur) {
  Node* next = new Node();
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      next->state[i][j] = cur->state[i][j];
    }
  }
  
  return next;
}

int alphabeta_value(Node* cur, int turn, int alpha, int beta);

Node* alphabeta_decision(Node* cur, int turn) {
  int v = alphabeta_value(cur, turn, -INF, INF);
  int sz = cur->nei.size();
  Node* ans = new Node();
  
  for(int i = 0; i < sz; i++) {
    if(v == cur->nei[i]->u) {
      ans = setVal(cur->nei[i]);
      break;
    }
  }
  
  return ans;
}

int alphabeta_value(Node* cur, int turn, int alpha, int beta) {
  //printf("%d\n", turn);
  if(terminal_test(cur)) {
    //printf("utility: %d\n", utility(cur));
    cur->u = utility(cur);
    return utility(cur);
  }
    
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(cur->state[i][j] == '_') {
	nodes++;
	Node* next = new Node();
	next = setVal(cur);
	if(turn == 1) {
	  next->state[i][j] = 'X';
	  cur->nei.push_back(next);
	}
	else {
	  next->state[i][j] = 'O';
	  cur->nei.push_back(next);
	}
      }
    }
  }
  
  if(turn == 1) {
    int best = -INF;
    int sz = cur->nei.size();
    //printf("size %d\n", sz);
    for(int i = 0; i < sz; i++) {
      best =  max(alpha, alphabeta_value(cur->nei[i], 2, alpha, beta));
      if(best >= beta) {
	cur->u = best;
	return best;
      }
      alpha = max(best, alpha);
      //printf("best: %d\n", best);
    }
    
    //printf("returned: %d\n", best);
    cur->u = best;
    return best;
  }
  
  int best = INF;
  int sz = cur->nei.size();
  //printf("size %d\n", sz);
  for(int i = 0; i < sz; i++) {
    best = min(best, alphabeta_value(cur->nei[i], 1, alpha, beta));
    if(best <= alpha) {
      cur->u = best;
      return best;
    }
    
    beta = min(best, beta);
    //printf("best: %d\n", best);
  }
  
  //printf("returned: %d\n", best);
  cur->u = best;
  return best;
}

char xoro(int m) {
  if(m == 1)
    return 'X';
  return 'O';
}

int main() {
  Node* game = new Node();
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      game->state[i][j] = '_';
    }
  }
  
  printf("Player 1 or 2? ");
  int pl; scanf("%d", &pl); //player1 or player2
  if(pl != 1 && pl != 2) {
    printf("That is not a player. Try again.\n");
    return 0;
  }
  
  int turn = 1;
  bool over = false;
  int winner;
  
  while(!over) {
    if(turn == pl) {
      int I,J;
      printf("Where do you wish to play?\n");
      bool legal = false;
      while(!legal) {
	printf("Row: "); scanf("%d", &I);
	printf("Column: "); scanf("%d", &J);
	
	if(game->state[I - 1][J - 1] != '_')
	  printf("That's not a legal move. Try again.\n");
	else
	  legal = true;
      }
      
      game->state[I - 1][J - 1] = xoro(pl);
      
      for(int i = 0; i < 3; i++) {
	for(int j = 0; j < 3; j++) {
	  printf("%c", game->state[i][j]);
	  if(j != 2)
	    printf("|");
	}
	printf("\n");
      }
    }
    else {
      nodes = 0;
      clock_t t1,t2;
      t1=clock();
      game = setVal(alphabeta_decision(game, turn));
      t2=clock();
      float diff = ((float)t2-(float)t1) / CLOCKS_PER_SEC;      
      printf("%d node(s) were generated.\n", nodes);
      cout << "Decision made in: " << diff << " seconds." << endl;

      for(int i = 0; i < 3; i++) {
	for(int j = 0; j < 3; j++) {
	  printf("%c", game->state[i][j]);
	  if(j != 2)
	    printf("|");
	}
	printf("\n");
      }  
    }

    if(turn == 1)
      turn = 2;
    else
      turn = 1;
    
    
    for(int i = 0; i < 10; i++)
      printf("-");
    printf("\n");
    
    if(terminal_test(game)) {
      over = true;
      winner = utility(game);
    }    
  }
  
  if(winner == W)
    printf("Player 1 wins!\n");
  else if(winner == L)
    printf("Player 2 wins!\n");
  else
    printf("It was a draw!\n");

  return 0;
}

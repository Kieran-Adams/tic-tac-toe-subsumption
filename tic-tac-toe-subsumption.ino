const int NW1     = 1; // field 1 - corner - NW
const int N2      = 2; // field 2 - N
const int NE3     = 3; // field 3 - corner - NE
const int W4      = 4; // field 4 - W
const int center5 = 5; // field 5 - center
const int E6      = 6; // field 6 - E
const int SW7     = 7; // field 7 - corner - SW
const int S8      = 8; // field 8 - S
const int SE9     = 9; // field 9 - corner - SE

const int button1 = 1; 
const int button2 = 2;
const int button3 = 3;
const int button4 = 4;
const int button5 = 5;
const int button6 = 6;
const int button7 = 7;
const int button8 = 8;
const int button9 = 9;

const int player = 13;
const int p1button = 11;

int play; // 1 human play , 0 computer play

// Game Representation

#define LEN_BOARD 9
#define LEN_CORNERS 4
#define LEN_CROSS 4

int board[LEN_BOARD] = { -1, -1, -1, -1, -1, -1, -1, -1, -1};
int human = 1;
int computer = 0;
int corners[LEN_CORNERS] = {0, 2, 6, 8};
int cross[LEN_CROSS] = {1, 3, 5, 7};

struct result {
  int win;
  int winPos;
};

void setup() {
  // put your setup code here, to run once:
  pinMode(NW1, OUTPUT);      
  pinMode(N2, OUTPUT);       
  pinMode(NE3, OUTPUT);      
  pinMode(W4, OUTPUT);       
  pinMode(center5, OUTPUT);   
  pinMode(E6, OUTPUT);         
  pinMode(SW7, OUTPUT);        
  pinMode(S8, OUTPUT);        
  pinMode(SE9, OUTPUT);        

  pinMode(button1, INPUT);      
  pinMode(button2, INPUT);       
  pinMode(button3, INPUT);      
  pinMode(button4, INPUT);       
  pinMode(button5, INPUT);   
  pinMode(button6, INPUT);         
  pinMode(button7, INPUT);        
  pinMode(button8, INPUT);        
  pinMode(button9, INPUT); 

  pinMode(player, OUTPUT);
  pinMode(p1button, INPUT);

  Serial.begin(9600);

}

void loop() {

  Serial.println("Push button for blue LED to play first");
  int p1buttonState = digitalRead(p1button);

  if (p1buttonState == HIGH) {
    play = human;
  } else {
    play = computer;
  }

  resetLEDs();
  resetBoard();

  while (true) {
    int result = win(board);

    if (result == 0) {
      // Computer wins
      Serial.println("Computer won");
      break;

    } else if (result = 1) {
      // Human wins
      Serial.println("You won");
      break;

    } else if (result = -1){
      // Tied game
      Serial.println("The game is tied");
      break;
      
    } else {
      // Continue Game

      if (play == 0) {
        // computer plays

        struct result compResult  = winable(board, computer);
        struct result humanResult = winable(board, human);

        if (compResult.win == 1) {
          // computer can win
          board[compResult.winPos] = computer;
          digitalWrite(compResult.winPos + 1, HIGH);

        } else if (humanResult.win == 1) {
          // human can win, computer blocks
          board[humanResult.winPos] = computer;
          digitalWrite(humanResult.winPos + 1, HIGH);

        } else if (board[4] == -1) { // play center
          board[4] = computer;
          digitalWrite(center5, HIGH);

        } else if (board[0] == -1 || board[2] == -1 || board[6] == -1 || board[8] == -1) { // play corner
          for (int corner = 0; corner < LEN_CORNERS; corner++) {
            if (board[corner] == -1) {
              board[corner] = computer;
              digitalWrite(corner, HIGH);
              break;
            }
          }

        } else {
          for (int adj = 0; adj < LEN_CROSS; adj++) {
            if (board[adj] == -1) {
              board[adj] = computer;
              digitalWrite(adj, HIGH);
              break;
            }
          }
        }

        play = 1;

      } else {
        //human plays

        if (button1 == HIGH) {
          if (board[0] == -1) {
            board[0] = human;
            digitalWrite(NW1, HIGH);
          }
        } else if (button2 == HIGH) {
          if (board[1] == -1) {
            board[1] = human;
            digitalWrite(N2, HIGH);
          }

        } else if (button3 == HIGH) {
          if (board[2] == -1) {
            board[2] = human;
            digitalWrite(NE3, HIGH);
          }

        } else if (button4 == HIGH) {
          if (board[3] == -1) {
            board[3] = human;
            digitalWrite(W4, HIGH);
          }

        } else if (button5 == HIGH) {
          if (board[4] == -1) {
            board[4] = human;
            digitalWrite(center5, HIGH);
          }

        } else if (button6 == HIGH) {
          if (board[5] == -1) {
            board[5] = human;
            digitalWrite(E6, HIGH);
          }

        } else if (button7 == HIGH) {
          if (board[6] == -1) {
            board[6] = human;
            digitalWrite(SW7, HIGH);
          }

        } else if (button8 == HIGH) {
          if (board[7] == -1) {
            board[7] = human;
            digitalWrite(S8, HIGH);
          }

        } else if (button9 == HIGH) {
          if (board[8] == -1) {
            board[8] = human;
            digitalWrite(SE9, HIGH);
          }
        } else {
          Serial.println("Please press a button");
        }
        play = 0;
      }
    }
  }
}

struct result winable(int currBoard[9], int currPlayer) {
  return;
}

// outputs 1 if computer wins, 0 if human player wins. Otherwise -1.
int win(int board[9]) {
  return;

}

void resetLEDs() {

}

void resetBoard() {

}

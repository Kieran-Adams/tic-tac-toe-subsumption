#define LEN_BOARD 9
#define LEN_CORNERS 4
#define LEN_CROSS 4

int board[LEN_BOARD] = { -1, -1, -1, -1, -1, -1, -1, -1, -1};
int human = 1;
int computer = 0;
int corners[LEN_CORNERS] = {0, 2, 6, 8};
int cross[LEN_CROSS] = {1, 3, 5, 7};

int celebrateTime = 0;

const int NW1     = 11; // field 1 - corner - NW
const int N2      = 2; // field 2 - N
const int NE3     = 3; // field 3 - corner - NE
const int W4      = 4; // field 4 - W
const int center5 = 5; // field 5 - center
const int E6      = 6; // field 6 - E
const int SW7     = 7; // field 7 - corner - SW
const int S8      = 8; // field 8 - S
const int SE9     = 9; // field 9 - corner - SE

const int chooseButton = 13;              //input pin for iterating
const int selectButton = 12;               //input pin for selecting 

int leds[LEN_BOARD] = {NW1, N2, NE3, W4, center5, E6, SW7, S8, SE9};

int ledBlinking = -1;

bool blink1 = false;
bool blink2 = false;
bool blink3 = false;
bool blink4 = false;
bool blink5 = false;
bool blink6 = false;
bool blink7 = false;
bool blink8 = false;
bool blink9 = false;

bool ledOn = false;
bool prevSelect = 0;
bool prevIterate = 0;

int iterator = 0;

struct result {
  int win;
  int winPos;
};

void setup() {
  Serial.begin(9600);
  pinMode(chooseButton, INPUT_PULLUP); 
  pinMode(selectButton, INPUT_PULLUP); 
  pinMode(NW1, OUTPUT);      
  pinMode(N2, OUTPUT);       
  pinMode(NE3, OUTPUT);      
  pinMode(W4, OUTPUT);       
  pinMode(center5, OUTPUT);   
  pinMode(E6, OUTPUT);         
  pinMode(SW7, OUTPUT);        
  pinMode(S8, OUTPUT);        
  pinMode(SE9, OUTPUT);        
}

void loop() {
  int currIterate = digitalRead(chooseButton);
  int currSelect = digitalRead(selectButton);
  bool selectClicked = !currSelect && prevSelect;
  bool chooseClicked = !currIterate && prevIterate;
  
  if (chooseClicked) {
    Serial.print("\nHere iterator: ");
    Serial.print(iterator);
    for (int i = iterator % 9; i < 9; i++) {
      Serial.print("\nHere i: ");
      Serial.print(i);
      if (board[i] == -1 && i != ledBlinking) {
        Serial.print("\nHere 3: ");
        Serial.print(ledBlinking);
        if (ledBlinking != -1) {
          Serial.print("\nHere 4: ");
          Serial.print(ledBlinking);
          digitalWrite(leds[ledBlinking], LOW);
        }
        ledBlinking = i;
        iterator = ledBlinking+1;
        break;
      }
    }
  }
  
  if (selectClicked && ledBlinking != -1) {
    Serial.print("\nHere leds[ledBlinking]: ");
    Serial.print(leds[ledBlinking]);
    board[ledBlinking] = human;
    ledBlinking = -1;
    iterator = 0;                            // reset

    computerPlays();
  }

  if(ledBlinking != -1) {
    Serial.print("\nHere ledBlinking: ");
    Serial.print(ledBlinking);
    Serial.print("\nHere iterator: ");
    Serial.print(iterator);
    if (millis() % 1000 < 500) {
      digitalWrite(leds[ledBlinking], HIGH);
    } else {
      digitalWrite(leds[ledBlinking], LOW);
    }
  }
  
  int gO = gameOver();
  if(gO) {
    if (!celebrateTime) {
      celebrateTime = millis() + 5000;
    }
    if (millis() > celebrateTime) {
      celebrateTime = 0;
      ledBlinking = -1;
      iterator = 0;
      gO = 0;
      reset();
    } else {
      celebrate(gO);
      
    }
  } else {
    for (int i = 0; i < 9; i++) {
      if (board[i] == computer) {
        if (millis() % 200 < 100) {
          digitalWrite(leds[i], HIGH);
        } else {
          digitalWrite(leds[i], LOW);
        }
      }
    }
  
    for (int i = 0; i < 9; i++) {
      if (board[i] == human) {
        digitalWrite(leds[i], HIGH);
      }
    }
  }
  
  prevSelect = currSelect;
  prevIterate = currIterate;
}

void celebrate(int outcome) {
  if (outcome == 1) {
    if (millis() % 1000 < 500) {
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[1], HIGH);
      digitalWrite(leds[2], HIGH);
    } else {
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
    }
  }
  if (outcome == 2) {
    if (millis() % 1000 < 500) {
      digitalWrite(leds[3], HIGH);
      digitalWrite(leds[4], HIGH);
      digitalWrite(leds[5], HIGH);
    } else {
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
    }
  }
  if (outcome == 3) {
    if (millis() % 1000 < 500) {
      digitalWrite(leds[6], HIGH);
      digitalWrite(leds[7], HIGH);
      digitalWrite(leds[8], HIGH);
    } else {
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
    }
  }
  if (outcome == 4) {
    if (millis() % 1000 < 500) {
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[3], HIGH);
      digitalWrite(leds[6], HIGH);
    } else {
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[6], LOW);
    }
  }
  if (outcome == 5) {
    if (millis() % 1000 < 500) {
      digitalWrite(leds[1], HIGH);
      digitalWrite(leds[4], HIGH);
      digitalWrite(leds[7], HIGH);
    } else {
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[7], LOW);
    }
  }
  if (outcome == 6) {
    if (millis() % 1000 < 500) {
      digitalWrite(leds[2], HIGH);
      digitalWrite(leds[5], HIGH);
      digitalWrite(leds[8], HIGH);
    } else {
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[8], LOW);
    }
  }
  if (outcome == 7) {
    if (millis() % 1000 < 500) {
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[4], HIGH);
      digitalWrite(leds[8], HIGH);
    } else {
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[8], LOW);
    }
  }
  if (outcome == 8) {
    if (millis() % 1000 < 500) {
      digitalWrite(leds[2], HIGH);
      digitalWrite(leds[4], HIGH);
      digitalWrite(leds[6], HIGH);
    } else {
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[6], LOW);
    }
  }
  if (outcome == 9) {
    for (int i = 0; i < 9; i++) {
      if (board[i] == computer) {
        if (millis() % 1000 < 500) {
          digitalWrite(leds[i], HIGH);
        } else {
          digitalWrite(leds[i], LOW);
        }
      }
      if (board[i] == human) {
        if (millis() % 1000 > 500) {
          digitalWrite(leds[i], HIGH);
        } else {
          digitalWrite(leds[i], LOW);
        }
      }
    }
  }
}

void computerPlays() {
  // computer plays

  struct result compResult  = winableBoard(computer);
  struct result humanResult = winableBoard(human);

  if (compResult.win == 1) {
    // computer can win
    board[compResult.winPos] = computer;
  } else if (humanResult.win == 1) {
    // human can win, computer blocks
    board[humanResult.winPos] = computer;
  } else if (board[4] == -1) { // play center
    board[4] = computer;
  } else if (board[0] == -1 || board[2] == -1 || board[6] == -1 || board[8] == -1) { // play corner
    for (int corner = 0; corner < LEN_CORNERS; corner++) {
      if (board[corner] == -1) {
        board[corner] = computer;
        break;
      }
    }

  } else {
    for (int adj = 0; adj < LEN_CROSS; adj++) {
      if (board[adj] == -1) {
        board[adj] = computer;
        break;
      }
    }
  }
}

struct result winableBoard(int currPlayer) {
  struct result rr;
  rr.win = 0;
  rr.winPos = -1;
  int res = winableGrid(0, 1, 2, currPlayer);
  if (res != -1) {
    rr.win = 1;
    rr.winPos = res;
    return rr;
  }
  res = winableGrid(3, 4, 5, currPlayer);
  if (res != -1) {
    rr.win = 1;
    rr.winPos = res;
    return rr;
  }
  res = winableGrid(6, 7, 8, currPlayer);
  if (res != -1) {
    rr.win = 1;
    rr.winPos = res;
    return rr;
  }
  res = winableGrid(0, 3, 6, currPlayer);
  if (res != -1) {
    rr.win = 1;
    rr.winPos = res;
    return rr;
  }
  res = winableGrid(1, 4, 7, currPlayer);
  if (res != -1) {
    rr.win = 1;
    rr.winPos = res;
    return rr;
  }
  res = winableGrid(2, 5, 8, currPlayer);
  if (res != -1) {
    rr.win = 1;
    rr.winPos = res;
    return rr;
  }
  res = winableGrid(0, 4, 8, currPlayer);
  if (res != -1) {
    rr.win = 1;
    rr.winPos = res;
    return rr;
  }
  res = winableGrid(2, 4, 6, currPlayer);
  if (res != -1) {
    rr.win = 1;
    rr.winPos = res;
    return rr;
  }
  return rr;
}

int winableGrid(int pos1, int pos2, int pos3, int currPlayer) {
  int count = 0;
  int empty = -1;
  if (board[pos1] == currPlayer) {
    count++;
  }
  if (board[pos2] == currPlayer) {
    count++;
  }
  if (board[pos3] == currPlayer) {
    count++;
  }
  if (count == 2) {
    if (board[pos1] == empty) {
      return pos1;
    }
    if (board[pos2] == empty) {
      return pos2;
    }
    if (board[pos3] == empty) {
      return pos3;
    }
  }
  return empty;
}

// outputs 1 if computer wins, 0 if human player wins. Otherwise -1.
int gameOver() {
  int winner = 0;
  int isWin = gridWon(0, 1, 2);
  if(isWin != -1) {
    winner = 1;
  }
  isWin = gridWon(3, 4, 5);
  if(isWin != -1) {
    winner = 2;
  }
  isWin = gridWon(6, 7, 8);
  if(isWin != -1) {
    winner = 3;
  }
  isWin = gridWon(0, 3, 6);
  if(isWin != -1) {
    winner = 4;
  }
  isWin = gridWon(1, 4, 7);
  if(isWin != -1) {
    winner = 5;
  }
  isWin = gridWon(2, 5, 8);
  if(isWin != -1) {
    winner = 6;
  }
  isWin = gridWon(0, 4, 8);
  if(isWin != -1) {
    winner = 7;
  }
  isWin = gridWon(2, 4, 6);
  if(isWin != -1) {
    winner = 8;
  }
  if (!winner) {
    if (boardFilled()) {
      winner = 9;
    }
  }
  return winner;
}

int boardFilled() {
  for (int i = 0; i < 9; i++) {
    if (board[i] == -1) {
      return 0;
    }
  }
  return 1;
}

int gridWon(int pos1, int pos2, int pos3) {
  if (board[pos1] == board[pos2] && board[pos2] == board[pos3]) {
    if (board[pos1] != -1) {
      return pos1;
    }
  }
  return -1;
}

void reset() {
  for (int i = 0; i < 9; i++) {
    board[i] = -1;
    digitalWrite(leds[i], LOW);
  }
}

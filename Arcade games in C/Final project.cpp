#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

char board[3][3];

// Function prototypes
void initializeBoard();
void showBoard();
int updateBoard(int cell, char playerSign);
int checkWinner(char sg);
void playTicTacToe();
void playNumberGuessingGame();
void playWordGuessingGame();

int main() {
    int choice;
    do {
        printf("\n\t\t\t\t\t\tChoose a game to play:\n\n");
        printf("\t\t\t\t\t\t1. Number Guessing Game\n");
        printf("\t\t\t\t\t\t2. Word Guessing Game (Hangman)\n");
        printf("\t\t\t\t\t\t3. Tic-Tac-Toe\n");
        printf("\t\t\t\t\t\t0. Exit\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playNumberGuessingGame();
                break;

            case 2:
                playWordGuessingGame();
                break;

            case 3:
                printf("\n--------- Tic Tac Toe ----------\n\n");
                playTicTacToe();
                break;

            case 0:
                printf("\n\t\t\t\t\t\tExiting the program. Goodbye!\n");
                break;

            default:
                printf("\n\t\t\t\t\tInvalid choice. Please enter a valid option.\n");
        }

    } while (choice != 0);

    return 0;
}

// Number Guessing Game
void playNumberGuessingGame() {
    int number, guess, nguesses = 1;
    srand(time(0));
    number = rand() % 100 + 1;
    printf("I have a number in my mind. Can you guess the number between 1 to 100?\n");
    do {
        printf("\nGuess the number: ");
        scanf("%d", &guess);
        if (guess > number) {
            printf("\nLower number please!\n");
        } else if (guess < number) {
            printf("\nHigher number please!\n");
        } else {
            printf("\nYou guessed it in %d attempts\n", nguesses);
            printf("\n\n\t\t\t\t\t\tCongratulations!\n\n");
            printf("------------------------------------------------------------------------------------------------------------------------");
        }
        nguesses++;
    } while (guess != number);
}

// Word Guessing Game (Hangman)
void playWordGuessingGame() {
    char word[20];
    char guessed[20];
    int attempts = 6;
    int length, i = 0, found, ch;

    printf("Enter the word to guess: ");
    do {
        ch = getch();
        if (ch != 13) {
            printf("*");
            word[i++] = ch;
        } else {
            word[i] = '\0';
        }
    } while (ch != 13);

    length = strlen(word);
    for (i = 0; i < length; i++) {
        guessed[i] = '_';
    }
    guessed[length] = '\0';

    while (attempts > 0 && strcmp(word, guessed) != 0) {
        printf("\nWord: %s\n", guessed);
        printf("Attempts left: %d\n", attempts);

        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        found = 0;
        for (i = 0; i < length; i++) {
            if (word[i] == guess) {
                guessed[i] = guess;
                found = 1;
            }
        }

        if (!found) {
            attempts--;
            printf("Incorrect guess.\n");
        } else {
            printf("Correct guess!\n");
        }
    }

    if (strcmp(word, guessed) == 0) {
        printf("\nCongratulations! You guessed the word: %s\n", word);
    } else {
        printf("\nSorry, you've run out of attempts. The word was: %s\n", word);
    }
}

// Tic-Tac-Toe
void initializeBoard() {
    system("cls"); // Clear the console screen
    printf("\n\n\t  1  |  2  |  3\n");
    printf("\t--------------\n");
    printf("\t  4  |  5  |  6\n");
    printf("\t--------------\n");
    printf("\t  7  |  8  |  9\n\n\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function shows the game board
void showBoard() {
    system("cls"); // Clear the console screen
    printf("\n\n\t  ");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
            if (j < 2) {
                printf("  |  ");
            }
        }
        if (i < 2) {
            printf("\n\t-----|-----|-----\n\t  ");
        }
    }
    printf("\n\n\n");
}


int updateBoard(int cell, char playerSign) {
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    int isValid = 1;

    // accessing already played cell number
    if (board[row][col] != ' ') {
        printf("\nInvalid: Cell is already Filled!\n");
        isValid = 0;
    }
    // valid cell position
    else {
        board[row][col] = playerSign;
        showBoard(); // Show the board after a valid move
    }

    return isValid;
}

int checkWinner(char sg) {
    // check all rows
    if (board[0][0] == sg && board[0][1] == sg && board[0][2] == sg ||
        board[1][0] == sg && board[1][1] == sg && board[1][2] == sg ||
        board[2][0] == sg && board[2][1] == sg && board[2][2] == sg) {
        return 1;
    }
    // check all columns
    else if (board[0][0] == sg && board[1][0] == sg && board[2][0] == sg ||
             board[0][1] == sg && board[1][1] == sg && board[2][1] == sg ||
             board[0][2] == sg && board[1][2] == sg && board[2][2] == sg) {
        return 1;
    }
    // check both diagonals
    else if (board[0][0] == sg && board[1][1] == sg && board[2][2] == sg ||
             board[0][2] == sg && board[1][1] == sg && board[2][0] == sg) {
        return 1;
    }

    // There is no winner
    return 0;
}

void playTicTacToe() {
    int gameResult = 0;
    int cell = 0;
    int playCount = 0;
    int updationResult = 1;

    char playerSign = ' ';

    initializeBoard(); // Initialize the board before starting the game

    // start playing the game
    while (!gameResult && playCount < 9) {
        if (playCount % 2 == 0) {
            // player 1
            printf("\nPlayer 1 [ X ] : ");
            playerSign = 'X';
        } else {
            // player 2
            printf("\nPlayer 2 [ O ] : ");
            playerSign = 'O';
        }
        scanf("%d", &cell);
        if (cell > 0 && cell <= 9) 
        {
            updationResult = updateBoard(cell, playerSign);
            // if updation is possible
            if (updationResult) {
                gameResult = checkWinner(playerSign);
                // print the winner of the game
                if (gameResult) {
                    printf("\t *** Player %d Won!! ***\n", playerSign == 'X' ? 1 : 2);
                }
                playCount++;
            }
        } else if (cell == -1) {
            printf("\n\tGame Terminated\n");
            return;
        } else {
            printf("\nPlease Enter a valid cell value\n");
        }
    }

    // no one won the game
    if (!gameResult && playCount == 9) {
        printf("\n\t *** Draw...  ***\n");
    }
    printf("\n\t --- Game Over --- \n");
}


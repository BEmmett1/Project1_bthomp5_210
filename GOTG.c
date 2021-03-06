#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define board_size 24
#define gooseChar '+' - '0'
#define bridgeChar '*' - '0'
#define mazeChar '-' - '0'
#define skullCharr '!' - '0'
#define humanChar '$'
#define computerChar '%'

#define num_goose_spaces 3
#define num_bridge_spaces 1
#define num_maze_spaces 2
#define num_skull_spaces 1

const int gooseSpaces[num_goose_spaces] = {7, 11, 15};
const int bridgeSpaces[num_bridge_spaces] = {6};
const int mazeSpaces[num_maze_spaces] = {13, 20};
const int skullSpaces[num_skull_spaces] = {23};

int roll_Dice(void);
void print_Board(int playerPos1, int playerPos2);
int tryMove(int currPos, int roll);
int notClear(int pos);
int checkWinner(int playerPos, int compPos);
int RNG;
int humanSpace = 1;
int computerSpace = 1;



int main(void) {
    char play;
    int foundWinner;
    char doDiceRoll;
    int humanRoll;
    int compRoll;
    int finished;
    int turnCounter;
    int whoTurn;
    int stopHere;
    int prevHumanSpace;
    int prevCompSpace;
    int nextSpace;
    
    start: {
        system("clear"); 

        humanSpace = 1;
        computerSpace = 1;
        
        /* prompt the user to play the game */
        printf("1) Press \'P\' or \'p\' to play or\n2) Press \'Q\' or \'q\' to quit\n");
        scanf("%c", &play);
        getchar();
        switch (play) {
            case 'P':
            case 'p': 
                play = '\n';
                while (1) {
                    foundWinner = 0;
                    /* determine who starts the game (human or computer) */
                    while (!foundWinner) {
                        /* Keep prompting user until they hit enter*/
                        doDiceRoll = 0;
                        while (doDiceRoll != '\n') {
                            printf("HUMAN PLAYER, Press <enter> to roll the dice");
                            doDiceRoll = getchar();
                        }
                        humanRoll = roll_Dice();
                        printf("Human rolled: %d\n", humanRoll);
                        doDiceRoll = 0;
                        while (doDiceRoll != '\n') {
                            printf("COMPUTER PLAYER, Press <enter> to roll the dice");
                            doDiceRoll = getchar();
                        }
                        compRoll = roll_Dice();
                        printf("Computer rolled: %d\n", compRoll);

                        /* evaluate the sum of both pair of rolls */
                        if (humanRoll > compRoll) {
                            foundWinner = 1;
                        }
                        else if (compRoll > humanRoll) {
                            foundWinner = 2;
                        }
                    }

                    /*Start moving pieces*/
                    if (foundWinner == 1) { 
                        printf("HUMAN PLAYER goes first\n");
                        turnCounter = 0; 
                    }
                    else { 
                        printf("COMPUTER PLAYER goes first\n");
                        turnCounter = 1;
                    }

                    finished = 0;
                    while (!finished) {
                        whoTurn = (turnCounter++ % 2);
                        switch (whoTurn) {
                            case 0 :
                                /* human */
                                printf("HUMAN PLAYER\'S TURN [%d]... Press <enter> to roll the dice", humanSpace);
                                /* wait for dice roll */
                                doDiceRoll = 0;
                                while (doDiceRoll != '\n') {
                                    doDiceRoll = getchar();
                                }

                                /* roll dice */
                                humanRoll = roll_Dice();
                                prevHumanSpace = humanSpace;
                                nextSpace = tryMove(humanSpace, humanRoll);
                                humanSpace = nextSpace;
                                
                                /* check on space */
                                stopHere = notClear(humanSpace);
                                while (stopHere) {
                                    printf(", ");
                                    switch (stopHere) {
                                        case 1 : 
                                            humanSpace = tryMove(humanSpace, humanRoll);
                                            break;
                                        case 2:
                                            printf("go to space 12");
                                            humanSpace = 12;
                                            break;
                                        case 3:
                                            printf("come back to space %d", prevHumanSpace);
                                            humanSpace = prevHumanSpace;
                                            break;
                                        case 4:
                                            printf("go to beginning");
                                            humanSpace = 1;
                                            break;
                                    }
                                    stopHere = notClear(humanSpace);
                                }

                                break;
                            case 1 :
                                /* comp */
                                printf("COMPUTER PLAYER\'S TURN [%d]... Press <enter> to roll the dice", computerSpace);
                                /* wait for dice roll */
                                doDiceRoll = 0;
                                while (doDiceRoll != '\n') {
                                    doDiceRoll = getchar();
                                }

                                /* roll dice */
                                compRoll = roll_Dice();
                                prevCompSpace = computerSpace;
                                nextSpace = tryMove(computerSpace, compRoll);
                                computerSpace = nextSpace;
                                
                                /* check on space */
                                stopHere = notClear(computerSpace);
                                while (stopHere) {
                                    printf(", ");
                                    switch (stopHere) {
                                        case 1 :
                                            computerSpace = tryMove(computerSpace, compRoll);
                                            break;
                                        case 2:
                                            printf("go to space 12");
                                            computerSpace = 12;
                                            break;
                                        case 3:
                                            printf("come back to space %d", prevCompSpace);
                                            computerSpace = prevCompSpace;
                                            break;
                                        case 4:
                                            printf("go to beginning");
                                            computerSpace = 1;
                                            break;
                                    }
                                    stopHere = notClear(computerSpace);
                                }

                                break; 
                        }
                        prevHumanSpace = humanSpace;
                        prevCompSpace = computerSpace;
                        print_Board(humanSpace, computerSpace);
                        if (checkWinner(humanSpace, computerSpace)) {
                            /* wait for dice roll */
                            printf("Press <enter> to play again");
                            doDiceRoll = 0;
                            while (doDiceRoll != '\n') {
                                doDiceRoll = getchar();
                            }
                            goto start;
                        }
                    }
                }
                break;
            case 'Q':
            case 'q':
                break;
            default:
                goto start;
        }
    }
    printf("Goodbye!\n");
    return 0;
}

int roll_Dice(void) {
    int die1;
    int die2;

    /* Intializes random number generator */
    srand((unsigned) time(NULL)); 

    die1 = rand() % 6 + 1;
    die2 = rand() % 6 + 1;

    printf("%d and %d for %d\n", die1, die2, die1 + die2);
    return die1 + die2;
}

void print_Board(int playerPos1, int playerPos2) {
    int spaceIndex;
    int spacesListIndex;
    int currSpaceChar;
    
    printf("\n");
    for (spaceIndex = 1; spaceIndex <= board_size; spaceIndex++) {

        for (spacesListIndex = 0; spacesListIndex < num_goose_spaces; spacesListIndex++) {
            currSpaceChar = gooseSpaces[spacesListIndex];
            if (spaceIndex == currSpaceChar) { 
                printf("%c", '0' + gooseChar);
            }
        }
        
        for (spacesListIndex = 0; spacesListIndex < num_bridge_spaces; spacesListIndex++) {
            currSpaceChar = bridgeSpaces[spacesListIndex];
            if (spaceIndex == currSpaceChar) { 
                printf("%c", '0' + bridgeChar);
            }
        } 

        for (spacesListIndex = 0; spacesListIndex < num_maze_spaces; spacesListIndex++) {
            currSpaceChar = mazeSpaces[spacesListIndex];
            if (spaceIndex == currSpaceChar) {
                printf("%c", '0' + mazeChar);
            }
        }
        
        for (spacesListIndex = 0; spacesListIndex < num_skull_spaces; spacesListIndex++) {
            currSpaceChar = skullSpaces[spacesListIndex];
            if (spaceIndex == currSpaceChar) {
                printf("%c", '0' + skullCharr);
            }
        }

        
        
        if (spaceIndex != board_size) printf("[");  
        else printf("<");
        
        if ((spaceIndex == playerPos1) && (playerPos1 == playerPos2)) printf("%c%c",humanChar,computerChar);
        else if (spaceIndex == playerPos1) printf ("%c",humanChar);
        else if (spaceIndex == playerPos2) printf("%c",computerChar);
        else printf("%d",spaceIndex);

        if (spaceIndex != board_size) printf("] ");
        else printf(">");
    }
    printf("\n");
    printf("\n");
}

int tryMove(int currSpace, int roll) {
    int nextSpace;
    nextSpace = currSpace + roll;
    if (nextSpace == board_size) {
        /* human win */
        printf("Game over!");
        return 24;
    }
    else if (nextSpace > board_size) {
        /* too far: bounce back */
        printf("come back to space %d", board_size - (nextSpace - board_size));
        nextSpace = board_size - (nextSpace - board_size);
    }
    else { 
        printf("go to space %d", nextSpace); 
    }
    return nextSpace;
}

int notClear(int pos) {
    int spacesListIndex;
    int currSpaceChar;
    for (spacesListIndex = 0; spacesListIndex < num_goose_spaces; spacesListIndex++) {
        currSpaceChar = gooseSpaces[spacesListIndex];
        if (pos == currSpaceChar) { 
            return 1;
        }
    }
    
    for (spacesListIndex = 0; spacesListIndex < num_bridge_spaces; spacesListIndex++) {
        currSpaceChar = bridgeSpaces[spacesListIndex];
        if (pos == currSpaceChar) { 
            return 2;
        }
    } 

    for (spacesListIndex = 0; spacesListIndex < num_maze_spaces; spacesListIndex++) {
        currSpaceChar = mazeSpaces[spacesListIndex];
        if (pos == currSpaceChar) {
            return 3;
        }
    }
    
    for (spacesListIndex = 0; spacesListIndex < num_skull_spaces; spacesListIndex++) {
        currSpaceChar = skullSpaces[spacesListIndex];
        if (pos == currSpaceChar) {
            return 4;
        }
    }
    return 0;
}

int checkWinner(int playerSpace, int compSpace) {
    return ((playerSpace == board_size) || (compSpace == board_size));
}
#include<stdio.h>

#define board_size 24
#define gooseChar '+' - '0'
#define bridgeChar '*' - '0'
#define mazeChar '-' - '0'
#define skullCharr '!' - '0'

#define num_goose_spaces 3
#define num_bridge_spaces 1
#define num_maze_spaces 2
#define num_skull_spaces 1

const int gooseSpaces[num_goose_spaces] = {7, 11, 15};
const int bridgeSpaces[num_bridge_spaces] = {6};
const int mazeSpaces[num_maze_spaces] = {13, 20};
const int skullSpaces[num_skull_spaces] = {23};

int main(void) {
    start: {
        /* prompt the user to play the game */
        char play;
        char prev = 0;
        printf("1) Press \'P\' or \'p\' to play or\n2) Press \'Q\' or \'q\' to quit\n");
        scanf("%c", &play);
        getchar();
        switch (play) {
            case 'P':
            case 'p': 
                while (1) {
                    play = '\n';
                    printf("%d\n", (play == '\n'));
                    printf("Welcome to game\n");
                    printf("Would you like to play again?\n");
                    printf("Press <enter> twice to return to the main\n");
                    play = getchar();
                    if (play == '\n' && prev == play) goto start;
                    prev = play;
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

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
    printf("%c",bridgeChar + '0');
}

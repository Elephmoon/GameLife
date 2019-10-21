#include <iostream>
#include <random>

struct Point {
    unsigned is_live:1;
};

#define __WORLD_HEIGHT__ 10

#define __WORLD_WIDTH__ 10

Point world[__WORLD_WIDTH__][__WORLD_HEIGHT__];

/*
 * Init first game generation.
 */
void WorldInit(Point world[][__WORLD_HEIGHT__])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    unsigned int i, j;

    for (i = 0; i < __WORLD_WIDTH__; i++) {
        for (j = 0; j < __WORLD_HEIGHT__; j++) {
            unsigned int num = dis(gen);
            if (num % 2 == 0) {
                world[i][j].is_live = 1;
            } else {
                world[i][j].is_live = 0;
            }
        }
    }
}

/*
 * Read neighbors points.
 */
void ReadNeighbors(signed int nb[][2], unsigned int x, unsigned int y)
{
    unsigned int i, j;
    unsigned int k = 0;

    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y) {
                continue;
            }
            nb[k][0] = i;
            nb[k][1] = j;
            k++;
        }
    }
}

int main() {
    return 0;
}
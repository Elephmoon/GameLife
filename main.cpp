#include <iostream>
#include <random>

struct Point {
    unsigned is_live:1;
};

constexpr int WORLD_HEIGHT = 10;

constexpr int WORLD_WIDTH = 10;

Point world[WORLD_WIDTH][WORLD_HEIGHT];

/*
 * Init first game generation.
 */
void WorldInit(Point world[][WORLD_HEIGHT])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    unsigned int i, j;

    for (i = 0; i < WORLD_WIDTH; i++) {
        for (j = 0; j < WORLD_HEIGHT; j++) {
            unsigned int num = dis(gen);
            if (num % 2 == 0) {
                world[i][j].is_live = 1;
            } else {
                world[i][j].is_live = 0;
            }
        }
    }
}

unsigned int GetLive(Point world[][WORLD_HEIGHT])
{
    unsigned int count = 0;
    unsigned i, j;
    for (i = 0; i < WORLD_WIDTH; i++) {
        for (j = 0; j < WORLD_HEIGHT; j++) {
            if (world[i][j].is_live == 1) {
                count++;
            }
        }
    }
    return count;
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
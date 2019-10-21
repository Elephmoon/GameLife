#include <iostream>
#include <random>
#include <chrono>
#include <thread>

struct Point {
    unsigned is_live:1;
};

constexpr int WORLD_HEIGHT = 10;

constexpr int WORLD_WIDTH = 10;

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

void ReadNeighbors(signed int nb[][2], const unsigned int& x, const unsigned int& y)
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

unsigned int CountLiveNeighbors(Point world[][WORLD_HEIGHT], const unsigned int& x, const unsigned int& y)
{
    unsigned int count = 0;
    unsigned int i;
    signed int nb[8][2];
    signed int _x, _y;

    ReadNeighbors(nb, x, y);

    for (i = 0; i < 8; i++) {
        _x = nb[i][0];
        _y = nb[i][1];

        if (_x < 0 || _y < 0) {
            continue;
        }
        if (_x >= WORLD_WIDTH || _y >= WORLD_HEIGHT) {
            continue;
        }

        if (world[_x][_y].is_live == 1) {
            count++;
        }
    }

    return count;
}

void NextGeneration(Point world[][WORLD_HEIGHT], Point prev_world[][WORLD_HEIGHT])
{
    unsigned int i, j;
    unsigned int live_nb;
    Point p;

    for (i = 0; i < WORLD_WIDTH; i++) {
        for (j = 0; j < WORLD_HEIGHT; j++) {
            p = prev_world[i][j];
            live_nb = CountLiveNeighbors(prev_world, i, j);

            if (p.is_live == 0) {
                if (live_nb == 3) {
                    world[i][j].is_live = 1;
                }
            } else {
                if (live_nb < 2 || live_nb > 3) {
                    world[i][j].is_live = 0;
                }
            }
        }
    }
}

void CopyWorld(Point src[][WORLD_HEIGHT], Point dest[][WORLD_HEIGHT])
{
    unsigned int i, j;
    for (i = 0; i < WORLD_WIDTH; i++) {
        for (j = 0; j < WORLD_HEIGHT; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int CmpWorld(Point w1[][WORLD_HEIGHT], Point w2[][WORLD_HEIGHT])
{
    unsigned int i, j;
    for (i = 0; i < WORLD_WIDTH; i++) {
        for (j = 0; j < WORLD_HEIGHT; j++) {
            if (w1[i][j].is_live != w2[i][j].is_live) {
                return -1;
            }
        }
    }
    return 0;
}

void PrintWorld(Point world[][WORLD_HEIGHT])
{
    unsigned int i, j;
    for (i = 0; i < WORLD_WIDTH; i++) {
        for (j = 0; j < WORLD_HEIGHT; j++) {
            if (world[i][j].is_live == 1) {
                std::cout << '*';
            } else {
                std::cout << ' ';
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

int main()
{
    Point world[WORLD_WIDTH][WORLD_HEIGHT];
    Point prev_world[WORLD_WIDTH][WORLD_HEIGHT];

    WorldInit(world);
    unsigned int live_points = -1;
    bool is_optimal = false;

    do {
        PrintWorld(world);
        CopyWorld(world, prev_world);
        NextGeneration(world, prev_world);

        is_optimal = CmpWorld(world, prev_world) == 0;
        live_points = GetLive(world);

        if (is_optimal) {
            std::cout << "Optimal configuration detected" << std::endl;
        }

        if (live_points == 0) {
            std::cout << "All points died" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } while (live_points != 0 && !is_optimal);

    return 0;
}
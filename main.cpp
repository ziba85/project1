#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <algorithm>
using namespace std;
struct location
{
    int x;
    int y;
};
struct player
{
    location pos;
    int moves;
    int bombBlastRadius;

};
struct Enemy
{
    location pos;
};

struct Bomb
{
    location pos;
    int timer;
};
struct Block
{
    location pos;
    bool destructible;
};

int gameWidth=11;
int gameHeight=11;
int gameDifficulty=1;
vector <Bomb> bombs;
vector <Enemy> enemies;
vector <Block> blocks;
Player player;
time_t startTime;
double gameDuration;
bool isGameRunning = false;
int score;
string playerName;

double weightTime = 1;
double weightMoves = 1;
double weightBombs = 1;
vector<ScoreEntry> scores;

void gotoxy(int x, int y) {


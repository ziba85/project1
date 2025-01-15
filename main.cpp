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
int gameHeight=15;
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

void gotoxy(int x, int y)
{
    COORD coord ;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void Setlevel()
{
    clearScreen();
    char choice;
    cout << "Set level\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "choose the level you want:";
    cin >> choice;

    switch (choice)
    {
    case '1':
        Setlevel(1);
        break;
    case '2':
        Setlevel(2);
        break;
    case '3':
        Setlevel(3);
        break;
    default:
        cout << "Invalid choice. Please try again.\n";
    }
}

void updatelocation(char input)
{
    int newX = player.pos.x;
    int newY = player.pos.y;

    switch (input)
    {
    case 119:
    case 87:
    case : // arrow up
        newY--;
        break;
    case 115:
    case 83:
    case : // arrow down
        newY++;
        break;
    case 97:
    case 65:
    case : // arrow left
        newX--;
        break;
    case 100:
    case 68:
    case : // arrow right
        newX++;
        break;
    case 98:
    case 66:
        placeBomb();
        break;
    case 'm':
    case 'M':
        isGameRunning = false;
        return;
    default:
        return;
    }

    void printMap()
    {
        clearScreen();
        vector<vector<char>> map(gameHeight, vector<char>(gameWidth, ' '));
        for(int i = 0; i < gameHeight; ++i)
        {
            map[i][0] = '*';
            map[i][gameWidth - 1] = '*';
        }
        for(int j = 0; j < gameWidth; ++j)
        {
            map[0][j] = '*';
            map[gameHeight - 1][j] = '*';
        }

        for(const auto& block : blocks)
        {
            if(block.destructible)
                map[block.pos.y][block.pos.x] = '_';
        }
        map[player.pos.y][player.pos.x] = 'S';

        for(const auto& enemy : enemies)
        {
            map[enemy.pos.y][enemy.pos.x] = 'E';
        }
        map[gameHeight - 2][gameWidth - 2] = '>';
        map[gameHeight - 2][gameWidth - 1] = '<';

        for(const auto& bomb : bombs)
        {
            map[bomb.pos.y][bomb.pos.x] = 'B';
        }

        void initializeGame()
        {
            player.pos.x = 0;
            player.pos.y = 0;
            player.moves = 0;
            player.bombBlastRadius = 0;

            switch (gameDifficulty)
            {
            case 1:
                gameWidth = 11;
                gameHeight = 15;
                break;
            case 2:
                gameWidth = 18;
                gameHeight =20;
                break;
            case 3:
                gameWidth = 21;
                gameHeight = 25;
                break;
            }

            enemies.clear();
            int enemyCount = 0;
            switch (gameDifficulty)
            {
            case 1:
                enemyCount = 1;
                break;
            case 2:
                enemyCount = 3;
                break;
            case 3:
                enemyCount = 5;
                break;
            }


            for (int i = 0; i < enemyCount; ++i)
            {
                Enemy enemy;
                bool validPosition = false;
                while (!validPosition)
                {
                    enemy.pos.x = rand() % (gameWidth - 2) + 1;
                    enemy.pos.y = rand() % (gameHeight - 2) + 1;

                    if(enemy.pos.x !=0 || enemy.pos.y != 0)
                        validPosition = true;

                    for (const auto& e : enemies)
                    {
                        if (e.pos.x == enemy.pos.x && e.pos.y == enemy.pos.y)
                        {
                            validPosition = false;
                            break;
                        }
                    }
                }
                enemies.push_back(enemy);
            }


            blocks.clear();
            int blockCount = 0;
            switch (gameDifficulty)
            {
            case 1:
                for (int j = 0; j < gameWidth; j++)
                {
                    if(j == newX && newY == 0)
                    {
                        canMove = false;
                        break;
                    }
                    if (j == newX && newY == gameHeight - 1)
                    {
                        canMove = false;
                        break;
                    }
                }

                if(canMove)
                {
                    player.pos.x = newX;
                    player.pos.y = newY;
                    player.moves++;
                }
            }


            void placeBomb()
            {
                Bomb bomb;
                bomb.pos = player.pos;
                bomb.timer = 2 + player.bombTimerIncrease;
                bomb.blastRadius = 1 + player.bombBlastRadius;
                bomb.remote = false;
                bombs.push_back(bomb);
            }


            void runGame()
            {
                isGameRunning = true;
                char input;
                while (isGameRunning)
                {
                    printMap();
                    std::cout << "\nUse 'W', 'A', 'S', 'D' to move, 'B' to place bomb, 'M' to return to menu: ";
                    input = getch();
                    updatelocation(input);
                    detonateBombs();
                    checkGameStatus();
                }
            }
            void startGame()
            {
                cout << "Enter your name: ";
                cin >> playerName;
                initializeGame();
                runGame();


                void showGuide()
                {
                    clearScreen();
                    cout << "Spoon Man Game\n";
                    cout << "Team Members:\n";
                    cout << "  - [zahra moghadasiyan] , [4031226072]\n";
                    cout << "  - [ziba mollaie] , [4031226076]\n";
                    cout << "\nGame Guide:\n";
                    cout << "  - Move with 'W', 'A', 'S', 'D' or arrow keys.\n";
                    cout << "  - Place bombs with 'B'.\n";
                    cout << "  - Bombs explode after two moves.\n";
                    cout << "  - Destroy enemies and find the exit '>'.\n";
                    cout << "  - Press 'M' to return to menu.\n";
                    cout << "\nPress any key to return to the main menu.";
                    _getch();
                }


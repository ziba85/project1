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
struct location{
  int x;
  int y;
};

struct Enemy{
  location pos;
};

struct Bomb{
  location pos;
  int timer;
};

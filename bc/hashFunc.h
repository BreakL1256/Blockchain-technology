#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

#ifndef HASH_FUNC_H     
#define HASH_FUNC_H  

char generateRandomChar(mt19937 &rng, uniform_int_distribution<int> &dist);
int generateRandomMoney(std::mt19937& rng, int min, int max);
void userGenerator();
// void transactionGenerator();
string hashFunction3(string input);

#endif 
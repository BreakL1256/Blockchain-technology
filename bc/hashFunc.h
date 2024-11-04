#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

#ifndef HASH_FUNC_H     
#define HASH_FUNC_H  

extern const int DIFFICULTY_TARGET; 
extern const int transactionNumber;

struct User {
    string name;
    string public_key;
    int balance;
};

struct Transaction {
    string transaction_id;
    string sender_public_key;
    string receiver_public_key;
    int amount;
    time_t timestamp;

    string getTransactionData() const {
        ostringstream oss;
        oss << sender_public_key << receiver_public_key << amount << timestamp;
        return oss.str();
    }
};

string shaHashFunction(const string& input);
string createMerkleRoot(const vector<Transaction>& transactions);

struct Block {
    int index;
    string previous_hash;
    vector<Transaction> transactions;
    time_t timestamp;
    string nonce;
    string hash;

    string getBlockData() const {
        ostringstream oss;
        string transactionHash = createMerkleRoot(transactions);
        oss << index << previous_hash << timestamp << nonce << transactionHash;

        return oss.str();
    }
};

extern unordered_map<string, User> users; 
extern vector<Transaction> pending_transactions;
extern vector<Transaction> all_transactions;
extern vector<Block> blockchain;
extern vector<Block> blockchainCopy;

char generateRandomChar(mt19937 &rng, uniform_int_distribution<int> &dist);
int generateRandomMoney(mt19937& rng, int min, int max);
void userGenerator();
// void transactionGenerator();
string hashFunction3(string input);
string generateTransactionID(const Transaction& tx);
Transaction createTransaction(const string& sender, const string& receiver, int amount);
bool validateTransaction(const Transaction& tx);
string mineBlock(Block& block);
void addBlockToChain(Block& block);
void addBlockToChain2(vector<Block> blocks, int targetNonce);
void createNewBlock();
vector<Block> createNewBlocks(int blockCount);
string shaHashFunction(const string& input);
string createMerkleRoot(const vector<Transaction>& transactions);

#endif 
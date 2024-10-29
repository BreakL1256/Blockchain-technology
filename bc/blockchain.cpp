#include "hashFunc.h"

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <sstream>

// Global constants
const int DIFFICULTY_TARGET = 4; // Number of leading zeros required in the hash

// Data structures
struct User {
    std::string name;
    std::string public_key;
    int balance;
};

struct Transaction {
    std::string transaction_id;
    std::string sender_public_key;
    std::string receiver_public_key;
    int amount;
    time_t timestamp;

    std::string getTransactionData() const {
        std::ostringstream oss;
        oss << transaction_id << sender_public_key << receiver_public_key << amount << timestamp;
        return oss.str();
    }
};

struct Block {
    int index;
    std::string previous_hash;
    std::vector<Transaction> transactions;
    time_t timestamp;
    std::string nonce;
    std::string hash;

    std::string getBlockData() const {
        std::ostringstream oss;
        oss << index << previous_hash << timestamp << nonce;
        for (const auto& tx : transactions) {
            oss << tx.getTransactionData();
        }
        return oss.str();
    }
};



int main() {
    srand(time(0));
    string name, pk;
    int balance;
    ifstream file("output.txt", std::ios::in);

    while(!file.eof()){
        User p;
        cin>>name>>pk>>balance;
        p.name = name;
        p.public_key = pk;
        p.balance = balance;
        users[pk] = p;
    }
    // Populate pending transactions (example)
    for (int i = 0; i < 1000; i++) {
        std::string sender = "public_key_" + std::to_string(rand() % 10); // Replace with actual user keys
        std::string receiver = "public_key_" + std::to_string(rand() % 10);
        int amount = rand() % 100 + 1;
        
        Transaction tx = createTransaction(sender, receiver, amount);
        if (validateTransaction(tx)) {
            pending_transactions.push_back(tx);
        }
    }

    // Mining loop to create new blocks with transactions
    while (!pending_transactions.empty()) {
        createNewBlock();
    }

    // Display blockchain info
    for (const auto& block : blockchain) {
        std::cout << "Block #" << block.index << ", Hash: " << block.hash << ", Previous Hash: " << block.previous_hash << "\n";
        for (const auto& tx : block.transactions) {
            std::cout << "  Transaction " << tx.transaction_id << ": " << tx.sender_public_key 
                      << " -> " << tx.receiver_public_key << ", Amount: " << tx.amount << "\n";
        }
    }

    return 0;
}

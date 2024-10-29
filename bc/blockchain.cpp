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

// Global variables
std::unordered_map<std::string, User> users; // Map of public_key -> User
std::vector<Transaction> pending_transactions;
std::vector<Block> blockchain;

// Helper functions
std::string generateTransactionID() {
    static int id = 0;
    return "tx" + std::to_string(++id);
}

Transaction createTransaction(const std::string& sender, const std::string& receiver, int amount) {
    Transaction tx;
    tx.transaction_id = generateTransactionID();
    tx.sender_public_key = sender;
    tx.receiver_public_key = receiver;
    tx.amount = amount;
    tx.timestamp = time(nullptr);
    return tx;
}

bool validateTransaction(const Transaction& tx) {
    // Ensure sender has enough balance
    return users[tx.sender_public_key].balance >= tx.amount;
}

// Mining function (Proof-of-Work)
std::string mineBlock(Block& block) {
    int nonce = 0;
    std::string block_data = block.getBlockData();
    std::string hash;
    
    do {
        block.nonce = std::to_string(nonce);
        hash = hashFunction3(block_data + block.nonce);
        nonce++;
    } while (hash.substr(0, DIFFICULTY_TARGET) != std::string(DIFFICULTY_TARGET, '0'));

    return hash;
}

// Add block to blockchain
void addBlockToChain(Block& block) {
    block.hash = mineBlock(block);
    blockchain.push_back(block);

    // Process transactions
    for (const auto& tx : block.transactions) {
        users[tx.sender_public_key].balance -= tx.amount;
        users[tx.receiver_public_key].balance += tx.amount;
    }

    // Clear processed transactions from the pending list
    pending_transactions.erase(pending_transactions.begin(), pending_transactions.begin() + block.transactions.size());
}

// Function to create a new block
void createNewBlock() {
    Block new_block;
    new_block.index = blockchain.size();
    new_block.previous_hash = blockchain.empty() ? "0" : blockchain.back().hash;
    new_block.transactions.assign(pending_transactions.begin(), pending_transactions.begin() + 100);
    new_block.timestamp = time(nullptr);

    addBlockToChain(new_block);
}

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

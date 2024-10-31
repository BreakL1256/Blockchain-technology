#include "hashFunc.h"
#include "sha256.h"

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cstring>
//#include <openssl/sha.h>


string shaHashFunction(const string& input);

const int DIFFICULTY_TARGET = 2; 
const int transactionNumber = 100;


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


std::unordered_map<std::string, User> users; 
std::vector<Transaction> pending_transactions;
std::vector<Block> blockchain;


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
    //cout << "ID: "<< tx.transaction_id << "\nsender: "<< sender << "\nreceiver: " << receiver << "\namount: " << amount << "\ntimestamp: " << tx.timestamp << endl << endl;
    return tx;
}

bool validateTransaction(const Transaction& tx) {
    
    return users[tx.sender_public_key].balance >= tx.amount;
}


std::string mineBlock(Block& block) {
    int nonce = 0;
    std::string block_data = block.getBlockData();
    std::string hash;
    
    do {
        block.nonce = std::to_string(nonce);
        hash = shaHashFunction(block_data + block.nonce);
        // if(hash[0] == '0') cout << hash << endl;
        nonce++;
    } while (hash.substr(0, DIFFICULTY_TARGET) != std::string(DIFFICULTY_TARGET, '0'));

    //cout << "block hash: " << hash << endl;

    return hash;
}


void addBlockToChain(Block& block) {
    block.hash = mineBlock(block);
    blockchain.push_back(block);

    
    for (const auto& tx : block.transactions) {
        users[tx.sender_public_key].balance -= tx.amount;
        users[tx.receiver_public_key].balance += tx.amount;
    }

    
    pending_transactions.erase(pending_transactions.begin(), pending_transactions.begin() + block.transactions.size());
}


void createNewBlock() {
    Block new_block;
    new_block.index = blockchain.size();
    new_block.previous_hash = blockchain.empty() ? "0" : blockchain.back().hash;
    if(pending_transactions.size() > transactionNumber) new_block.transactions.assign(pending_transactions.begin(), pending_transactions.begin() + transactionNumber);
    else new_block.transactions.assign(pending_transactions.begin(), pending_transactions.begin() + pending_transactions.size());
    new_block.timestamp = time(nullptr);
    // cout << "Block created\n";
    // cout << " index: " << new_block.index << "\nprevious hash: " << new_block.previous_hash << "\ntime: " << new_block.timestamp << endl;
    addBlockToChain(new_block);
}

string shaHashFunction(const string& input){
    // Input data to hash
    const char *data = input.c_str();
    size_t data_len = strlen(data);
    
    // Prepare the hash output buffer
    BYTE hash[SHA256_BLOCK_SIZE];
    
    // Initialize SHA-256 context
    SHA256_CTX ctx;
    sha256_init(&ctx);
    
    // Update the context with data
    sha256_update(&ctx, (BYTE*)data, data_len);
    
    // Finalize the hash
    sha256_final(&ctx, hash);
    
    // Print the hash in hexadecimal
    ostringstream oss;
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return oss.str();
}

int main() {
    std::random_device rd;           
    std::mt19937 rng(rd());           
    std::uniform_int_distribution<int> dist(0, 1000);  
    std::uniform_int_distribution<int> distAmnt(0, 20);  

    string name, pk, line;
    int balance;
    vector<string> pkVec;
    ifstream file("output.txt", std::ios::in);

    while(getline(file, line)){
        User p;

        istringstream iss(line);

        iss>>name>>pk>>balance;
        pkVec.push_back(pk);
        p.name = name;
        p.public_key = pk;
        p.balance = balance;
        users[pk] = p;
    }

    file.close();

    
    for (int i = 0; i < 1000; i++) {
        string copy1 = pkVec[dist(rng)], copy2 = pkVec[dist(rng)];
        if(copy1 == copy2) continue;
        std::string sender = copy1; 
        std::string receiver = copy2;
        int amount = distAmnt(rng);
        
        Transaction tx = createTransaction(sender, receiver, amount);
        if (validateTransaction(tx)) {
            pending_transactions.push_back(tx);
        }
    }

   
    while (!pending_transactions.empty()) {
        createNewBlock();
        cout << "Works" << endl;
    }

   
    for (const auto& block : blockchain) {
        cout << "Block #" << block.index << ", Hash: " << block.hash << ", Previous Hash: " << block.previous_hash << "\n";
        for (const auto& tx : block.transactions) {
            std::cout << "  Transaction " << tx.transaction_id << ": " << tx.sender_public_key 
                      << " -> " << tx.receiver_public_key << ", Amount: " << tx.amount << "\n";
        }
    }

    return 0;
}

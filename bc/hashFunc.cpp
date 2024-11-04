#include "hashFunc.h"
#include "sha256.h"

using namespace std;

char generateRandomChar(mt19937 &rng, uniform_int_distribution<int> &dist) {
    return static_cast<char>(dist(rng));
}

int generateRandomMoney(std::mt19937& rng, int min, int max) {
    std::uniform_int_distribution<int> moneyDist(min, max);
    return moneyDist(rng);
}

void userGenerator(){
    std::random_device rd;           
    std::mt19937 rng(rd());           
    std::uniform_int_distribution<int> charDist(32, 126);  

    const size_t numUsers = 1000;     
    const size_t nameCharacters = 10;  
    const size_t PKCharacters = 128;   
    const int minMoney = 0;            
    const int maxMoney = 1000;        

    std::ofstream outFile("output.txt"); 

    for (size_t i = 0; i < numUsers; i++) {
        std::string randomName;
        char ch = ' ';
        for (size_t j = 0; j < nameCharacters; ++j) {
            while(ch == ' '){
                ch = generateRandomChar(rng, charDist);
            }
            randomName += ch;
            ch = ' ';
        }
    
        std::string randomPublicKey;
        for (size_t j = 0; j < PKCharacters; ++j) {
            while(ch == ' '){
                ch = generateRandomChar(rng, charDist);
            }
            randomPublicKey += ch;
            ch = ' ';
        }

        int randomMoney = generateRandomMoney(rng, minMoney, maxMoney);

        outFile << randomName << " " << randomPublicKey << " " << randomMoney << "\n";
    }

    outFile.close();  
}

// void transactionGenerator(){

// }

string hashFunction3(string input) {
    string arrayOfInputs[4], hashedString;
    long long hashedNumberArray[4] = {0};
    
    unsigned long long initialSeed = (input.length() * 17 + static_cast<int>(input[0]) * 29 + static_cast<int>(input[input.length() / 2]) * 59 + static_cast<int>(input[input.length() - 1]) * 97) % 104729;

    for(int i = 0; i<4; i++){
      arrayOfInputs[i] = "0xsetfh654.";
    }

    if(input.length() == 0) return "";

    int partLength = input.length() / 4;  
    int remainder = input.length() % 4;   

    int currentPos = 0;

    //Split input string
    if(input.length() >=4 ){
        for(int i = 0; i<4; i++){
            int currentPartLength = partLength + (i < remainder ? 1 : 0);
            
            arrayOfInputs[i] = input.substr(currentPos, currentPartLength);
            
            currentPos += currentPartLength;
        }
    } else arrayOfInputs[0] = input;

    unsigned long long hash = initialSeed, hashAlternative = 0; 
    int charNumber = 0;
    const unsigned long long primeMultiplier = 1099511628211;
    const unsigned long long primeModulo = 29992394723;

    //Hashing the string
    for(int i = 0; i < 4; i++){
        for (char c : arrayOfInputs[i]) {
            charNumber = c;
            hash ^= static_cast<unsigned char>(c);            
            hash *= primeMultiplier * charNumber * 31;
            hash ^= hashAlternative;
            hash <<= 13;
            hash ^= (hash >> 5);
            hash = (hash * primeMultiplier + charNumber * 751) % primeModulo;
            hash ^= (hash << 11);
            hashAlternative = hash;
        }
        arrayOfInputs[i] = to_string(hash);
        hashAlternative = 0;
    }

    swap(arrayOfInputs[0], arrayOfInputs[2]);

    ostringstream oss;

    for(int i=0; i<4;i++){
        istringstream iss(arrayOfInputs[i]);
        iss >> hashedNumberArray[i];
        hashAlternative = hash;
        hash ^= hashedNumberArray[i]; 
        hash += (hashedNumberArray[i] * 31); 
        hash ^= (hash << 15);           
        hash ^= (hash >> 2);           
        hash |= (1LL << 63);   
        oss << hex << hash;
    }
    return oss.str();
}

string generateTransactionID(const Transaction& tx) {
    return shaHashFunction(tx.getTransactionData());
}

Transaction createTransaction(const string& sender, const string& receiver, int amount) {
    Transaction tx;
    tx.sender_public_key = sender;
    tx.receiver_public_key = receiver;
    tx.amount = amount;
    tx.timestamp = time(nullptr);
    tx.transaction_id = generateTransactionID(tx);
    //cout << "ID: "<< tx.transaction_id << "\nsender: "<< sender << "\nreceiver: " << receiver << "\namount: " << amount << "\ntimestamp: " << tx.timestamp << endl << endl;
    return tx;
}

bool validateTransaction(const Transaction& tx) {
    return users[tx.sender_public_key].balance >= tx.amount;
}


string mineBlock(Block& block) {
    int nonce = 0;
    string block_data = block.getBlockData();
    string hash;
    
    do {
        block.nonce = to_string(nonce);
        hash = shaHashFunction(block_data + block.nonce);
        // if(hash[0] == '0') cout << hash << endl;
        nonce++;
    } while (hash.substr(0, DIFFICULTY_TARGET) != string(DIFFICULTY_TARGET, '0'));

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

    all_transactions.assign(pending_transactions.begin(), pending_transactions.begin() + block.transactions.size());
    pending_transactions.erase(pending_transactions.begin(), pending_transactions.begin() + block.transactions.size());
}

//For v0.2
void addBlockToChain2(vector<Block> blocks, int targetNonce){
    int count = 0;
    for(auto block: blocks){
        block.hash = mineBlock(block);
        cout << "\nBlock order for mining #"<< count <<" Nonce: " << block.nonce;
        count++;
        if(stoi(block.nonce) >= targetNonce) continue;
        else{
            blockchainCopy.push_back(block);

            for (const auto& tx : block.transactions) {
                users[tx.sender_public_key].balance -= tx.amount;
                users[tx.receiver_public_key].balance += tx.amount;
            }

            all_transactions.assign(pending_transactions.begin(), pending_transactions.begin() + block.transactions.size());
            return;
        }
    }
}

void createNewBlock() {
    Block new_block;
    new_block.index = blockchain.size();
    new_block.previous_hash = blockchain.empty() ? "0" : blockchain.back().hash;
    if(pending_transactions.size() > transactionNumber) new_block.transactions.assign(pending_transactions.begin(), pending_transactions.begin() + transactionNumber);
    else new_block.transactions.assign(pending_transactions.begin(), pending_transactions.begin() + pending_transactions.size());
    new_block.timestamp = time(nullptr);
    addBlockToChain(new_block);
}

// For v0.2
vector<Block> createNewBlocks(int blockCount) {
    random_device rd;           
    mt19937 rng(rd());           
    uniform_int_distribution<int> Bdist(0, 900); 

    vector<Block> blocks;

    for(int i=0; i<blockCount; i++){
        auto range = Bdist(rng);
        Block new_block;
        new_block.index = blockchain.size();
        new_block.previous_hash = blockchain.empty() ? "0" : blockchain.back().hash;
        new_block.transactions.assign(pending_transactions.begin() + range, pending_transactions.begin() + range + transactionNumber);
        new_block.timestamp = time(nullptr);
        blocks.push_back(new_block);
    }

    return blocks;
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
        oss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return oss.str();
}

string createMerkleRoot(const vector<Transaction>& transactions){
    if (transactions.empty()) return "";

    vector<string> tempTransactions;

    for(const auto& tr: transactions){
        if(tr.transaction_id == generateTransactionID(tr)){
            tempTransactions.push_back(tr.transaction_id);
        }else continue;
    }

    while (tempTransactions.size() > 1) {
       
        if (tempTransactions.size() % 2 != 0) {
            tempTransactions.push_back(tempTransactions.back());
        }

        vector<string> newLvl;
        for (size_t i = 0; i < tempTransactions.size(); i += 2) {
            string combinedHash = shaHashFunction(tempTransactions[i] + tempTransactions[i + 1]);
            newLvl.push_back(combinedHash);
        }
        tempTransactions = newLvl;
    }

    return tempTransactions[0];
}
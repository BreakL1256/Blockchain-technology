#include "hashFunc.h"
#include "sha256.h"

using namespace std;

const int DIFFICULTY_TARGET = 4; 
const int transactionNumber = 100;

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


unordered_map<string, User> users; 
vector<Transaction> pending_transactions;
vector<Transaction> all_transactions;
vector<Block> blockchain;
vector<Block> blockchainCopy;


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

int main() {
    int choice;
    while(true){
        cout << "Choose action (1 - mine, 2 - print block of your choosing, 3 - print any transaction, 4 - 5 block mining, 5 - exit)" << endl;
        cin >> choice;
        switch(choice){
            case 1:{
                random_device rd;           
                mt19937 rng(rd());           
                uniform_int_distribution<int> dist(0, 1000);  
                uniform_int_distribution<int> distAmnt(0, 20);  

                string name, pk, line;
                int balance;
                vector<string> pkVec;
                ifstream file("output.txt", ios::in);

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
                    string sender = copy1; 
                    string receiver = copy2;
                    int amount = distAmnt(rng);
                    
                    Transaction tx = createTransaction(sender, receiver, amount);
                    if (validateTransaction(tx)) {
                        pending_transactions.push_back(tx);
                    }
                }

            
                while (!pending_transactions.empty()) {
                    createNewBlock();
                }

            
                for (const auto& block : blockchain) {
                    cout << "Block #" << block.index << ", Hash: " << block.hash << ", Previous Hash: " << block.previous_hash << "\n";
                    for (const auto& tx : block.transactions) {
                        cout << "  Transaction " << tx.transaction_id << ":\n" << tx.sender_public_key 
                                << "\n -----> \n" << tx.receiver_public_key << "\nAmount: " << tx.amount << "\n";
                    }
                }
                cout << "blockchain size: " << blockchain.size() << endl; 
                break;
            }
            case 2:{
                int BIndex;
                cout << "Write the index of the block:\n";
                try {
                    cin >> BIndex;

                    if (cin.fail()) {
                        throw runtime_error("Invalid input. Please enter an integer.");
                    }

                } catch (const runtime_error& e) {
                    cerr << e.what() << endl; 
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if(BIndex < blockchain.size()){
                    cout << "index: " << blockchain[BIndex].index << "\nprevious hash: " << blockchain[BIndex].previous_hash << "\ntime: " << blockchain[BIndex].timestamp << 
                        "\nblock hash: " << blockchain[BIndex].hash << "\nnonce: " << blockchain[BIndex].nonce << endl;
                }
                else cout << "No such block";
                break;
            }
            case 3:{
                int index;
                string id;
                cout << "How would you like to find the transaction (1 - senders ID, 2 - receivers ID, 3 - transaction ID):\n";
                cin>>index;
                cout << "\nInput the ID:\n";
                cin >> id;
                switch(index){
                    case 1:{
                        for(const auto& tran: all_transactions){
                            if(tran.sender_public_key == id) cout << "\ntransaction: " << tran.transaction_id <<"\nreceiver's id: " << tran.receiver_public_key << "\namount: "<<  tran.amount << "\ntime: " << tran.timestamp << endl << endl;
                        }
                        break;
                    }
                    case 2:{
                        for(const auto& tran: all_transactions){
                            if(tran.receiver_public_key == id) cout << "\ntransaction: " << tran.transaction_id << "\nsender's id: " << tran.sender_public_key << "\namount: "<<  tran.amount << "\ntime: " << tran.timestamp << endl << endl;
                        }
                        break;
                    }
                    case 3:{
                        for(const auto& tran: all_transactions){
                            if(tran.transaction_id == id) cout << "\nsender's id: " << tran.sender_public_key <<"\nreceiver's id: " << tran.receiver_public_key << "\namount: "<<  tran.amount << "\ntime: " << tran.timestamp << endl << endl;
                        }
                        break;
                    }
                    default:
                        cout << "\nSuch ID doesn't exist\n";
                        break;
                }
                break;
            }
            case 4:{
                random_device rd;           
                mt19937 rng(rd());           
                uniform_int_distribution<int> dist(0, 1000);  
                uniform_int_distribution<int> distAmnt(0, 20);  

                string name, pk, line;
                int balance;
                vector<string> pkVec;
                ifstream file("output.txt", ios::in);

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
                    string sender = copy1; 
                    string receiver = copy2;
                    int amount = distAmnt(rng);
                    
                    Transaction tx = createTransaction(sender, receiver, amount);
                    if (validateTransaction(tx)) {
                        pending_transactions.push_back(tx);
                    }
                }

                int numOfBlocks = 5, targetNonce = 1000;
                vector<Block> blocks = createNewBlocks(numOfBlocks);
                char character = '#', character2 = '/';
                int c = 100;   

                while(blockchainCopy.empty()){
                    addBlockToChain2(blocks, targetNonce);

                    if(!blockchainCopy.empty()) break;

                    string output(c, character);

                    cout << "\nBlock hasn't been mined!\n" << output;

                    targetNonce *= 2;
                }

                blockchain.insert(blockchain.end(), blockchainCopy.begin(), blockchainCopy.end());

                blockchainCopy.clear();

                string output(c, character2);

                cout << endl <<output << "\nWHOLE BLOCKCHAIN:\n";
                for (const auto& block : blockchain) {
                    cout << "\nBlock #" << block.index << "\nHash: " << block.hash << "\nPrevious Hash: " << block.previous_hash
                    << "\nTimestamp: " << block.timestamp << "\nNonce: " << block.nonce << endl;
                }
                cout << "blockchain size: " << blockchain.size() << endl; 
                
                break;
            }
            case 5:{
                return 0;
            }
        }
    }

    return 0;
}

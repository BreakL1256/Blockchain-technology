#include "hashFunc.h"
#include "sha256.h"

using namespace std;

const int DIFFICULTY_TARGET = 4; 
const int transactionNumber = 100;

unordered_map<string, User> users; 
vector<Transaction> pending_transactions;
vector<Transaction> all_transactions;
vector<Block> blockchain;
vector<Block> blockchainCopy;

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
                char character = '#', character2 = '/';
                int c = 100;   

                while(blockchainCopy.empty()){
                    vector<Block> blocks = createNewBlocks(numOfBlocks);
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

#include "hashFunc.h"

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

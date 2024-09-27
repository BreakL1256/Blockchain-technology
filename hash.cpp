#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include <random>
#include <cstring>
#include <cstdlib> 
#include <ctime>    
#include <cstdio>   
#include <iomanip>

using namespace std;

char generateRandomChar(mt19937 &rng, uniform_int_distribution<int> &dist) {
    return static_cast<char>(dist(rng));
}

void symbolGenerator(){
    size_t numCharacters = 2000;
    string filename = "1SeparateSymbol.txt";

    ofstream outFile(filename, std::ios::out);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
    }

    std::random_device rd; 
    std::mt19937 rng(rd()); 
    std::uniform_int_distribution<int> dist(32, 126);

    for (size_t i = 0; i < numCharacters; ++i) {
        char randomChar = generateRandomChar(rng, dist);
        outFile << randomChar;
    }

    outFile.close();
}

string hashFunction3(string input) {
    string arrayOfInputs[4], hashedString;
    long long hashedNumberArray[4] = {0};
    
    for(int i = 0; i<4; i++){
      arrayOfInputs[i] = "0xsetfh654.";
    }

    // Take input from the user
    //cout << "String to hash: ";
    //getline(std::cin, input);

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

    unsigned long long hash = 0, hashAlternative = 0; 

    //Hashing the string
    for(int i = 0; i < 4; i++){
        for (char c : arrayOfInputs[i]) {
            hash ^= static_cast<unsigned char>(c); 
            hashAlternative = hash;
            hash <<= 15; 
            hash ^= hashAlternative;
            hash >>=1;
        }
        arrayOfInputs[i] = to_string(hash);
        hash = 0;
        hashAlternative = 0;
    }

    swap(arrayOfInputs[0], arrayOfInputs[2]);

    // for(int i=0; i<4; i++){
    //     cout << arrayOfInputs[i] << endl; 
    // }

    ostringstream oss;

    //cout << "Hash: ";
    for(int i=0; i<4;i++){
        istringstream iss(arrayOfInputs[i]);
        iss >> hashedNumberArray[i];
        hash ^= hashedNumberArray[i]; 
        hash += (hashedNumberArray[i] * 31); 
        hash ^= (hash << 13);           
        hash ^= (hash >> 7);           
        hash |= (1LL << 63);
        oss << hex << hash;
       //cmbString += arrayOfInputs[i];
    }
    return oss.str();
}

int main(){
    int inputType;
    string choice1, choice2;
    //symbolGenerator();
    cout << "Choose input type (1 - CLI, 2 - file input):" << endl;
    cin >> inputType;
    switch(inputType){
        case 1:
            cout << "Input a value:" << endl;
            cin >> choice1;
            cout << "Hash: " << hashFunction3(choice1) << endl;
            break;
        case 2:
            cout << "Input a file name: " << endl;
            cin >> choice2;
            ifstream inputFile(choice2);
            if (!inputFile) {
                std::cerr << "Error opening file!" << std::endl;
                return 1; 
            }
            string input;
            getline(inputFile, input);
            cout << "Hash: " << hashFunction3(input) << endl;
            inputFile.close();
            break;
    }

    return 0;
}
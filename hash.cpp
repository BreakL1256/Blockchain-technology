#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

char generateRandomChar(mt19937 &rng, uniform_int_distribution<int> &dist) {
    return static_cast<char>(dist(rng));
}

void symbolGenerator(){
    size_t numCharacters = 10;
    string filename = "100000Pairs.txt";

    ofstream outFile(filename, std::ios::out);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
    }

    std::random_device rd; 
    std::mt19937 rng(rd()); 
    std::uniform_int_distribution<int> dist(32, 126);
    for(size_t i=0; i<100000; i++){
        if(i == 24999) numCharacters = 100;
        if(i == 49999) numCharacters = 500;
        if(i == 74999) numCharacters = 1000;
        string randomString1, randomString2;
        for (size_t j = 0; j < numCharacters; ++j) {
            char randomChar1 = generateRandomChar(rng, dist);
            //char randomChar2 = generateRandomChar(rng, dist);
            randomString1 += randomChar1;
            if(j == numCharacters / 2){
                randomString2 += '.';
            } else randomString2 += randomChar1;
        }
        outFile << randomString1 << "   " << randomString2 << endl;
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
    cout << "Choose input type (1 - CLI, 2 - file input, 3 - 4 punktas, 4 - 6 punktas, 5 - Pair generator):" << endl;
    cin >> inputType;
    switch(inputType){
        case 1:{
            cout << "Input a value:" << endl;
            cin >> choice1;
            cout << "Hash: " << hashFunction3(choice1) << endl;
            break;
        }
        case 2: {
            cout << "Input a file name: " << endl;
            cin >> choice2;
            ifstream inputFile(choice2);
            if (!inputFile) {
                std::cerr << "Error opening file!" << std::endl;
                return 1; 
            }
            int rowCount = 128;
            string input, rows;
            for(int i=0; i<rowCount; i++){
                getline(inputFile, rows);
                input += rows;
            }
            //cout << input;
            auto start = std::chrono::high_resolution_clock::now();
            cout << "Hash: " << hashFunction3(input) << endl;
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_time = end - start;
            std::cout << "Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;
            inputFile.close();
            break;
        }
        case 3: {
            int sameStringsCounter;
            string sample1, sample2, t, t1;
            ifstream inputFile("100000Pairs.txt");
            for(int i=0; i<50000; i++){
                inputFile >> sample1 >> sample2;
                if(hashFunction3(sample1) == hashFunction3(sample2)) sameStringsCounter++;
            }
            cout<< "Collision counter: " << sameStringsCounter << endl;
            break;
        }
        case 4: {
            int sameCharCounter, sameBitCounter;
            double hexRatio, bitRatio;
            string sample1, sample2, t, t1;
            ifstream inputFile("100000Pairs.txt");
            for(int i=0; i<50000; i++){

                inputFile >> sample1 >> sample2;

                    for (int i=0; i<sample1.length(); i++) {
                        bitset<8> charBits(sample1[i]); 
                        t += charBits.to_string(); 
                        if(sample1[i] == sample2[i]) sameCharCounter++;
                    }
                    hexRatio += sameCharCounter/sample1.length(); 
                    for (int i=0; i<sample2.length(); i++) {
                        bitset<8> charBits(sample2[i]); 
                        t1 += charBits.to_string(); 
                    }

                    for(int i=0; i<t1.length();i++){
                        if(t[i] == t1[i]) sameBitCounter++;
                    }
                    
                    bitRatio += sameBitCounter/t.length();
                //if(hashFunction3(sample1) == hashFunction3(sample2)) sameStringsCounter++;
            }
            cout << "Hex ratio: " << hexRatio * 100 << endl;
            cout << "Bit ratio: " << bitRatio * 100 << endl;
            break;
        }
        case 5:{
            symbolGenerator();
            break;
        }
    }

    return 0;
}
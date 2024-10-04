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
    size_t numCharacters = 50;
    string filename = "100000Pairs.txt";

    ofstream outFile(filename, std::ios::out);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
    }

    std::random_device rd; 
    std::mt19937 rng(rd()); 
    std::uniform_int_distribution<int> dist(32, 126);
    for(size_t i=0; i<100000; i++){
        // if(i == 24999) numCharacters = 100;
        // if(i == 49999) numCharacters = 500;
        // if(i == 74999) numCharacters = 1000;
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
    
    unsigned long long initialSeed = (input.length() * 17 + static_cast<int>(input[0]) + static_cast<int>(input[input.length()/2])) % 104739;

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

    //Hashing the string
    for(int i = 0; i < 4; i++){
        for (char c : arrayOfInputs[i]) {
            charNumber = c;
            hash ^= static_cast<unsigned char>(c); 
            hashAlternative = hash;
            hash <<= 15;
            hash ^= hashAlternative;
            hash >>=1;
            hash = hash * 3 + charNumber * 1333748 % 29992394723;
        }
        arrayOfInputs[i] = to_string(hash);
        hash = initialSeed;
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
        //hash = ((hash << 15) ^ (hashAlternative * 31));
        hash ^= (hash << 13);           
        hash ^= (hash >> 2);           
        hash |= (1LL << 63);   
        oss << hex << hash;
    }
    return oss.str();
}

int main(){
    int inputType;
    string choice1, choice2;
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
            int sameStringsCounter = 0;
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
            // int sameCharCounter = 0, sameBitCounter = 0, k = 0 ;
            // double hexRatio = 0, bitRatio = 0;
            // string sample1, sample2, t, t1, r, r1;
            // ifstream inputFile("100000Pairs.txt");
            // if (!inputFile) {
            //     std::cerr << "Error opening file!" << std::endl;
            //     return 1; 
            // }
            // for(int i=0; i<50000; i++){
                
            //     inputFile >> r >> r1;
            //     sample1 = hashFunction3(r);
            //     sample2 = hashFunction3(r1);
            //         for (int j=0; j<sample1.length(); j++) {
            //             bitset<8> charBits(sample1[j]); 
            //             t += charBits.to_string(); 
            //             if(sample1[j] == sample2[j]) sameCharCounter++;
            //         }
            //         hexRatio += sameCharCounter/sample1.length(); 
            //         for (int j=0; j<sample2.length(); j++) {
            //             bitset<8> charBits(sample2[j]); 
            //             t1 += charBits.to_string(); 
            //         }

            //         for(int j=0; j<t1.length();j++){
            //             if(t[j] == t1[j]) sameBitCounter++;
            //         }
                    
            //         bitRatio += sameBitCounter/t.length();
            //         k += i;
            //         sameBitCounter = 0;
            //         sameCharCounter = 0;
            //     //if(hashFunction3(sample1) == hashFunction3(sample2)) sameStringsCounter++;
            // }
            // cout << k << endl;
            // cout << "Hex ratio: " << hexRatio * 100 << endl;
            // cout << "Bit ratio: " << bitRatio * 100 << endl;

                int sameCharCounter = 0, sameBitCounter = 0;
                double hexRatio = 0.0, bitRatio = 0.0;
                string r, r1;
                ifstream inputFile("100000Pairs.txt");

                if (!inputFile) {
                    cerr << "Error opening file!" << endl;
                    return 1; 
                }

                const int totalPairs = 50000; 

                for (int i = 0; i < totalPairs; i++) {
                    inputFile >> r >> r1;

                    
                    string sample1 = hashFunction3(r);
                    string sample2 = hashFunction3(r1);

                   
                    sameCharCounter = 0;
                    sameBitCounter = 0;
                    string t, t1; 

                    
                    for (size_t j = 0; j < sample1.length(); j++) {
                        bitset<8> charBits(sample1[j]); 
                        t += charBits.to_string(); 
                        if (j < sample2.length() && sample1[j] == sample2[j]) {
                            sameCharCounter++;
                        }
                    }

                    
                    if (!sample1.empty()) {
                        hexRatio += static_cast<double>(sameCharCounter) / sample1.length(); 
                    }

                   
                    for (size_t j = 0; j < sample2.length(); j++) {
                        bitset<8> charBits(sample2[j]); 
                        t1 += charBits.to_string(); 
                    }

                    
                    for (size_t j = 0; j < t1.length(); j++) {
                        if (j < t.length() && t[j] == t1[j]) {
                            sameBitCounter++;
                        }
                    }

                    
                    if (!t.empty()) {
                        bitRatio += static_cast<double>(sameBitCounter) / t.length();
                    }
                }

                
                hexRatio /= totalPairs;
                bitRatio /= totalPairs;

                
                cout << fixed << setprecision(2); 
                cout << "Hex ratio: " << 100 - hexRatio * 100 << "%" << endl;
                cout << "Bit ratio: " << 100 - bitRatio * 100 << "%" << endl;

                inputFile.close(); 
            break;
        }
        case 5:{
           symbolGenerator();
            break;
        }
    }

    return 0;
}
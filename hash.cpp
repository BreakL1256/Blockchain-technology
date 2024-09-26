#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <cstring>
#include <cstdlib>  // For std::srand and std::rand
#include <ctime>    // For std::time
#include <cstdio>   // For std::fopen and std::fgets
#include <iomanip>

using namespace std;

void hashFunction3() {
    string input, arrayOfInputs[4], hashedString;
    long long hashedNumberArray[4] = {0};
    
    for(int i = 0; i<4; i++){
      arrayOfInputs[i] = "0xsetfh654.";
    }

    // Take input from the user
    cout << "String to hash: ";
    getline(std::cin, input);

    if(input.length() == 0) return;

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

    for(int i=0; i<4; i++){
        cout << arrayOfInputs[i] << endl; 
    }

    cout << "Hash: ";
    for(int i=0; i<4;i++){
        istringstream iss(arrayOfInputs[i]);
        iss >> hashedNumberArray[i];
        hash ^= hashedNumberArray[i]; // XOR with current hashed number
        hash += (hashedNumberArray[i] * 31); // Example multiplication to mix bits
        hash ^= (hash << 13);           // Shift and XOR for additional mixing
        hash ^= (hash >> 7);            // More mixing
        hash |= (1LL << 63);
        cout << hex << hash;
       //cmbString += arrayOfInputs[i];
    }

}

int main(){
    hashFunction3();
    // unsigned long long a = 13839561654909534266ULL, b = 16147665260029935651ULL;
    // cout << hex << a << endl;
    // cout << hex << b;
    return 0;
}
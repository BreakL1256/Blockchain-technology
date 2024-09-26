#include <iostream>
#include <string>
#include <bitset>
#include <cstring>
#include <cstdlib>  // For std::srand and std::rand
#include <ctime>    // For std::time
#include <cstdio>   // For std::fopen and std::fgets

using namespace std;

void hashFunction(){
    // string input;
    // int sumOfChars = 0, bitShifterValue = 0;
    // getline(cin, input);
    // cout << input << endl;
    // if(input.length() != 0){
    //     //randomizing existing string 
    //     for(int i=0; i<input.length(); i++){
    //         sumOfChars += input[i];
    //     }
    //     bitShifterValue = sumOfChars % (input.length() % 10);
    //     for(int i=0; i<input.length(); i++){
    //         input[i] = ~input[i];
    //         input[i] ^= (1 << bitShifterValue);
    //         input[i] &= ~(1 << (bitShifterValue % 6));
    //         input[i] ^= (1 << (bitShifterValue % 3));
    //         input[i] = ~input[i];
    //     }
    //     //cout<<input<<endl;
    //     int halfString = input.length()/2;
    //     string secondHalf = input.substr(halfString);
    //     string firstHalf = input.substr(0, halfString);
    //     input = secondHalf + firstHalf;
    //     //filling the string
        
        
    //     //cout << secondHalf << " " <<firstHalf;
    //}
}

// void hashFunction2(){
//     const char* filename = "input.txt";
//     FILE* file = fopen(filename, "r");

//     long long int nums[4] = {0};
//     const int bufferSize = 33;  // Buffer size
//     char buffer[bufferSize];

//     if(file == nullptr){
//         cerr << "error opening file" << endl;
//     }

//     std::srand(static_cast<unsigned int>(std::time(nullptr)));

//     while(fgets(buffer, sizeof(buffer), file) != nullptr){
//         // Remove the newline character if it's there
//         buffer[strcspn(buffer, "\n")] = 0;

//         // Check the length of the buffer
//         if (strlen(buffer) < 32) {
//             // Fill the buffer with random ASCII characters if it's less than 32
//             for (size_t i = strlen(buffer); i < 32; ++i) {
//                 // Generate a random ASCII character (32 to 126 for printable characters)
//                 buffer[i] = static_cast<char>(std::rand() % (126 - 32 + 1) + 32);
//             }
//             buffer[32] = '\0';  // Null-terminate the string
//         }

//         //memcpy(nums, buffer, sizeof(nums)); 
//         cout<< sizeof(buffer) << endl;
//         for(int i=0; i<4; i++){
//             nums[i] |= (1LL << 63);
//         }
//         //not operations
//         for(int i=0; i<4; i++){
//             nums[i] = ~nums[i];
//         }
        
//         //xor with eachother
//         for(int i=0; i<4; i++){
//             nums[i] ^= (nums[i] >> 5);
//         }
//     }
//     fclose(file);

//     for(int i=0; i<4; i++){
//         cout << nums[i] << endl;
//     }
// }

void hashFunction3() {
    string input, arrayOfInputs[4];
    
    // Take input from the user
    cout << "String to hash: ";
    getline(std::cin, input);

    int partLength = input.length() / 4;  
    int remainder = input.length() % 4;   

    int currentPos = 0;

    for(int i = 0; i<4; i++){
        int currentPartLength = partLength + (i < remainder ? 1 : 0);
        
        arrayOfInputs[i] = input.substr(currentPos, currentPartLength);
        
        currentPos += currentPartLength;
    }

    unsigned long long hash = 0, hashAlternative = 0; // Initialize hash value

    // Process each character in the input string
    for(int i = 0; i < 4; i++){
        for (char c : arrayOfInputs[i]) {
            hash ^= static_cast<unsigned char>(c); // XOR the hash with the ASCII value of the character
            hashAlternative = hash;
            hash <<= 2; // Shift left to mix bits
            hash |= (1LL << 63);
            hash >>= 10;
            hash |= (1LL << 63);
            hash ^= hashAlternative;
            hash |= (1LL << 63);
            hash >>=1;
            hash |= (1LL << 63);
        }
        arrayOfInputs[i] = to_string(hash);
        hash = 0;
        hashAlternative = 0;
    }

    for(int i=0; i<4;i++){
        cout << arrayOfInputs[i] << endl;
    }
}

int main(){
    hashFunction3();

    return 0;
}
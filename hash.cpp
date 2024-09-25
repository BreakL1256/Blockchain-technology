#include <iostream>
#include <string>
#include <bitset>
#include <cstring>

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

void hashFunction2(){
    const char* filename = "input.txt";
    FILE* file = fopen(filename, "r");

    long long int nums[4] = {0};
    const int bufferSize = 33;  // Buffer size
    char buffer[bufferSize];

    if(file == nullptr){
        cerr << "error opening file" << endl;
    }

    while(fgets(buffer, sizeof(buffer), file)){
        memcpy(nums, buffer, sizeof(nums));
    }
    fclose(file);

    for(int i=0; i<4; i++){
        cout << nums[i] << endl;
    }
}

int main(){
    hashFunction();
    hashFunction2();
    return 0;
}
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

void hashFunction(){
    string input;
    int sumOfChars = 0, bitShifterValue = 0;
    getline(cin, input);
    cout << input << endl;
    if(input.length() != 0){
        //randomizing existing string 
        for(int i=0; i<input.length(); i++){
            sumOfChars += input[i];
        }
        bitShifterValue = sumOfChars % (input.length() % 10);
        for(int i=0; i<input.length(); i++){
            input[i] = ~input[i];
            input[i] ^= (1 << bitShifterValue);
            input[i] &= ~(1 << (bitShifterValue % 6));
            input[i] ^= (1 << (bitShifterValue % 3));
            input[i] = ~input[i];
        }
        //padding or truncating the string
        
        cout << input;
    }
}

int main(){
    hashFunction();
    return 0;
}
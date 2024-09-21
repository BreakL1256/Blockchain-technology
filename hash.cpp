#include <iostream>
#include <string>
#include <bitset>

using namespace std;

void hashFunction(){
    string input;
    int sumOfChars = 0, bitShifterValue = 0;
    getline(cin, input);
    //cout << input << endl;
    if(input.length() != 0){
        for(int i=0; i<input.length(); i++){
            sumOfChars += input[i];
        }
        bitShifterValue = sumOfChars % (input.length() % 256);
        for(int i=0; i<input.length(); i++){
            // bitset<8> hash(input[i]);
            // cout << hash << ":";
            input[i] = ~input[i];
            // bitset<8> hashed(input[i]);
            // cout << hashed << endl;
        }
        cout << sumOfChars;
    }
}

int main(){
    hashFunction();
    return 0;
}
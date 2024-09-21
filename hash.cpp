#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main(){
    string input;
    getline(cin, input);
    cout << input << endl;
    for(int i=0; i<input.length(); i++){
        bitset<8> hash(input[i]);
        cout << hash << ":";
        input[i] = ~input[i];
        bitset<8> hashed(input[i]);
        cout << hashed << endl;
    }

    cout << input;
    return 0;
}
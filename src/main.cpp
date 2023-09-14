#include "main.h"


int main(){
    
    string input = "";
    getline(cin, input);
    for(char &c : input){
        cout << c << "\n";
    }

    
    return 0;
}
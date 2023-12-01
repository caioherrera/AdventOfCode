#include <iostream>
#include <string>
#include <map>
#include <set>
#define DEBUG false
using namespace std;

typedef long long ll;

map<string, int> validStrings = {
    { "one", 1 }, 
    { "two", 2 },
    { "three", 3 },
    { "four", 4 },
    { "five", 5 },
    { "six", 6 },
    { "seven", 7 },
    { "eight", 8 },
    { "nine", 9 }
};

int processInputRowSecondHalf(string s) {
    int first = -1, second = -1;
    int len = s.length();
    
    for(int i = 0; i < len; i++) {
        int currValue = -1;
        if(s[i] >= '0' && s[i] <= '9') {
            currValue = s[i] - '0';
        }
        else {
            for(int j = 3; i + j <= len && j <= 5; j++) {
                string ss = s.substr(i, j);
                if(validStrings.find(ss) != validStrings.end()) {
                    currValue = validStrings[ss];
                    break;
                }
            }
        }
        if(currValue != -1) {
            if(first == -1)
                first = currValue;
            second = currValue;
        }        
    }

    if(DEBUG)
        cout << "found value " << first << second << endl;

    return first * 10 + second;
}

int processInputRowFirstHalf(string s) {
    int first = -1, second = -1;

    for(char c : s) {
        if(c >= '0' && c <= '9') {
            if(first == -1)
                first = (int)(c - '0');
            second = (int)(c - '0');
        }
    }

    if(DEBUG)
        cout << "found value " << first << second << endl;

    return first * 10 + second;
}

int main() {

    string s;
    int sumValues = 0;
    while(cin >> s) {
        sumValues += processInputRowSecondHalf(s); 
    }
    cout << sumValues << endl;

    return 0;
}
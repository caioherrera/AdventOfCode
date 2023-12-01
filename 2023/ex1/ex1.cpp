#include <iostream>
#include <string>
#include <map>
#include <set>
#define DEBUG false
using namespace std;

typedef long long ll;

// Helper map to replace a valid digit string with its numeric value
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

// Input String Processor for Second Half of the problem
int processInputRowSecondHalf(string s) {
    int first = -1, second = -1;
    int len = s.length();
    
    for(int i = 0; i < len; i++) {
        
        // Replacing first and second by currValue, in order to reduce code repetition
        int currValue = -1;
        
        // Same logic for digits as before
        if(s[i] >= '0' && s[i] <= '9') {
            currValue = s[i] - '0';
        }

        else {

            // We could have handled the search for digit strings with a Trie. However it might be overkill,
            // since there's only 9 strings to search for, with lengths in [3, 5] interval. So the approach
            // here is to capture the substrings with length in the [3, 5] interval, starting on the current
            // index.
            for(int j = 3; i + j <= len && j <= 5; j++) {
                
                string ss = s.substr(i, j);

                // Checks if the string exists in the previously defined map
                if(validStrings.find(ss) != validStrings.end()) {
                    currValue = validStrings[ss];
                    break;
                }
            }
        }

        // Applies the found currValue to first and second
        if(currValue != -1) {
            if(first == -1)
                first = currValue;
            second = currValue;
        }        
    }

    // For debugging purposes
    if(DEBUG)
        cout << "found value " << first << second << endl;

    return first * 10 + second;
}

// Input String Processor for First Half of the problem
int processInputRowFirstHalf(string s) {
    int first = -1, second = -1;

    for(char c : s) {

        // Check if there's a digit
        if(c >= '0' && c <= '9') {

            // Behind the curtains, a char represents an integer value. So the operation c - '0' is valid,
            // it will return a value that can be interpreted as an integer, and it's equivalent to the digit
            // value. So, '0' - '0' = 0, '1' - '0' = 1, etc.
            if(first == -1)
                first = c - '0';

            // There is no else here, since second should be set even if there's only one digit. For example:
            // abc1def culminates in number 11 (first = 1, second = 1).
            second = c - '0';
        }
    }

    // For debugging purposes
    if(DEBUG)
        cout << "found value " << first << second << endl;

    return first * 10 + second;
}

int main() {

    string inputRow;
    int result = 0;

    while(cin >> inputRow) {
        result += processInputRowSecondHalf(inputRow); 
    }
    
    cout << result << endl;

    return 0;
}
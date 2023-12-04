#include <iostream>
#include <string>
#include <vector>
#include <set>
#define DEBUG false
using namespace std;

typedef long long ll;

// These are the delimiters to be used in order to parse the input
const set<char> delimiters = { ' ', ':'};

// Separates an input row into multiple tokens, by using the previously defined delimiters.
// The output vector would be something like: ["Game", "1", "41", "48", "83", "86", "17", "|", "83"...
vector<string> tokenize(string s) {
    
    vector<string> tokens;
    string curr = "";

    for(char c : s) {
        if(delimiters.find(c) != delimiters.end()) {
            if(curr.length() > 0)
                tokens.push_back(curr);
            curr = "";
        }
        else {
            curr += c;
        }
    }
    if(curr.length() > 0)
        tokens.push_back(curr);

    return tokens;
}

pair<int, int> processInputRow(string s) {
    
    vector<string> tokens = tokenize(s);
    set<int> winningNumbers;
    bool foundPipe = false;

    int countNumbers = 0;    
    int value = 0;

    for(int i = 2; i < tokens.size(); i++) {
        if(tokens[i] == "|") {
            foundPipe = true;
            continue;
        }
        int curr = stoi(tokens[i]);
        if(foundPipe) {
            if(winningNumbers.find(curr) != winningNumbers.end()) {
                countNumbers++;
                value = (value == 0) ? 1 : value << 1;
            }
        }
        else
            winningNumbers.insert(curr);        
    }

    if(DEBUG)
        cout << "Game " << tokens[1] << " has " << countNumbers << " winning numbers and is worth " << value << " points" << endl;

    return {countNumbers, value};
}

void addToPosition(vector<int>& v, int pos, int value) {
    while(v.size() <= pos)
        v.push_back(0);
    v[pos] += value;
}

void addToNPositions(vector<int>& v, int startPos, int length, int value) {
    for(int i = 0; i < length; i++) {
        while(v.size() <= startPos + i)
            v.push_back(0);
        v[startPos + i] += value;
    }
}

int main() {

    string input;
    int sumPointsFirstHalf = 0;
    int totalCardsSecondHalf = 0;
    vector<int> countCards(1, 0);

    int row = 0;

    while(getline(cin, input)) {
        addToPosition(countCards, row, 1);
        pair<int, int> currCard = processInputRow(input);
        sumPointsFirstHalf += currCard.second;        
        addToNPositions(countCards, row + 1, currCard.first, countCards[row]);
        totalCardsSecondHalf += countCards[row++];
    }

    cout << totalCardsSecondHalf << endl;
    
    return 0;
}
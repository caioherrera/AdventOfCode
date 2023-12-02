#include <iostream>
#include <string>
#include <vector>
#include <set>
#define DEBUG false
using namespace std;

typedef long long ll;

const set<char> delimiters = { ' ', ':', ';', ',' };

struct Game {
    int id, red, green, blue;

    Game(int i) {
        id = i;
        red = green = blue = 0;
    }

    Game(int i, int r, int g, int b) {
        id = i;
        red = r;
        green = g;
        blue = b;
    }

    bool IsValidFrom(Game g) {
        return red <= g.red && green <= g.green && blue <= g.blue;
    }
};

vector<string> tokenize(string s) {
    
    vector<string> tokens;
    string curr = "";

    for(char c : s) {
        if(delimiters.find(c) != delimiters.end() && curr.length() > 0) {
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

Game processInputRow(string s) {

    vector<string> tokens = tokenize(s);
    Game curr(stoi(tokens[1]));

    for(int i = 2; i < tokens.size(); i += 2) {
        int currValue = stoi(tokens[i]);
        
        switch (tokens[i + 1][0])
        {
            case 'r':
                curr.red = max(curr.red, currValue);
                break;
            
            case 'g':
                curr.green = max(curr.green, currValue);
                break;

            case 'b':
                curr.blue = max(curr.blue, currValue);
                break;
        }
    }

    if(DEBUG)
        cout << "Game " << curr.id << ": " << curr.red << " red, " << curr.green << " green, " << curr.blue << " blue" << endl;

    return curr;
}

int main() {

    string inputRow;
    Game defaultGame(0, 12, 13, 14);
    int sumIdsFirstHalf = 0;
    int sumPowerSecondHalf = 0;
    
    while(getline(cin, inputRow)) {

        Game curr = processInputRow(inputRow); 

        if(curr.IsValidFrom(defaultGame)) {
            sumIdsFirstHalf += curr.id;
        }

        sumPowerSecondHalf += curr.red * curr.green * curr.blue;
    }
    
    cout << sumPowerSecondHalf << endl;

    return 0;
}
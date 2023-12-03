#include <iostream>
#include <string>
#include <vector>
#include <set>
#define DEBUG false
using namespace std;

typedef long long ll;

// These are the delimiters to be used in order to parse the input
const set<char> delimiters = { ' ', ':', ';', ',' };

// Struct to store the definition of a single game
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

    // Checks if the current Game instance is valid to be attained from an original Game.
    // In the context of the problem, checks if a game is valid considering the existing
    // cubes on the bag.
    bool IsValidFrom(Game g) {
        return red <= g.red && green <= g.green && blue <= g.blue;
    }
};

// Separates an input row into multiple tokens, by using the previously defined delimiters.
// The output vector would be something like: ["Game", "1", "3", "blue", "4", "red"...
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

    // Captures the Game id from the second token
    Game curr(stoi(tokens[1]));

    // Iterates through the pair of tokens (amount, color) and computes the max amount per color 
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

    // For debugging purposes
    if(DEBUG)
        cout << "Game " << curr.id << ": " << curr.red << " red, " << curr.green << " green, " << curr.blue << " blue" << endl;

    return curr;
}

int main() {

    string inputRow;

    // Sets the initial default game
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
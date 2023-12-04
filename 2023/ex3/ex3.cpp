#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#define DEBUG false
using namespace std;

typedef long long ll;

struct Number {
    int value;
    int row;
    int startPos, endPos;
    set<pair<int, int>> adjacentWith;

    Number(int r, int s, int e, int v) {
        value = v;
        row = r;
        startPos = s;
        endPos = e;
    }
};

struct Symbol {
    char symbol;
    int row, col;

    Symbol(char s, int r, int c) {
        symbol = s;
        row = r;
        col = c;
    }
};

pair<vector<Number>, vector<Symbol>> processInputRowForElements(string& input, int row) {
    pair<vector<Number>, vector<Symbol>> processedRow;

    string curr = "";
    for(int i = 0; i < input.length(); i++) {
        if(input[i] < '0' || input[i] > '9') {
            if(curr.length() > 0)
                processedRow.first.push_back(Number(row, i - curr.length(), i - 1, stoi(curr)));
            curr = "";
        }
        if(input[i] == '.') continue;
        if(input[i] >= '0' && input[i] <= '9') 
            curr += input[i];
        else
            processedRow.second.push_back(Symbol(input[i], row, i));
    }
    if(curr.length() > 0)
        processedRow.first.push_back(Number(row, input.length() - curr.length(), input.length() - 1, stoi(curr)));

    return processedRow;
}

vector<pair<int, int>> getAdjacentPositions(int row, int col, int n, int m) {
    vector<pair<int, int>> positions;

    if(row > 0) {
        if(col > 0) positions.push_back({row - 1, col - 1});
        positions.push_back({row - 1, col});
        if(col < m - 1) positions.push_back({row - 1, col + 1});        
    }

    if(col > 0) positions.push_back({row, col - 1});
    if(col < m - 1) positions.push_back({row, col + 1});
    
    if(row < n - 1) {
        if(col > 0) positions.push_back({row + 1, col - 1});
        positions.push_back({row + 1, col});
        if(col < m - 1) positions.push_back({row + 1, col + 1});        
    }

    return positions;
}

int main() {

    string input;
    int rows = 0;
    int cols = 0;
    vector<vector<Number>> numbers;
    vector<Symbol> symbols;
    int sumPartNumbersFirstHalf = 0;
    int sumGearRatioSecondHalf = 0;
    
    while(getline(cin, input)) {
        cols = input.length();
        pair<vector<Number>, vector<Symbol>> processedRow = processInputRowForElements(input, rows++);
        numbers.push_back(processedRow.first);
        symbols.insert(symbols.end(), processedRow.second.begin(), processedRow.second.end());
    }

    for(Symbol s : symbols) {
        vector<pair<int, int>> positions = getAdjacentPositions(s.row, s.col, rows, cols);
        int partialResult = 1;
        int countNumbers = 0;
        for(pair<int, int> pos : positions) {
            for(Number& n : numbers[pos.first]) {
                if(pos.second >= n.startPos && pos.second <= n.endPos && n.adjacentWith.find({s.row, s.col}) == n.adjacentWith.end()) {
                    partialResult *= n.value;
                    countNumbers++;
                    n.adjacentWith.insert({s.row, s.col});
                }
            }
        }
            
        if(countNumbers == 2 && s.symbol == '*') {
        
            if(DEBUG)
                cout << "found gear ratio on symbol at (" << s.row << ", " << s.col << "), partial result = " << partialResult << endl;
        
            sumGearRatioSecondHalf += partialResult;
        }
    }

    for(vector<Number> vn : numbers) {
        for(Number n : vn) {
            if(n.adjacentWith.size() > 0) {
                if(DEBUG)
                    cout << n.value << " is a part number" << endl;
                sumPartNumbersFirstHalf += n.value;
            }
        }
    }
    cout << sumGearRatioSecondHalf << endl;
    return 0;
}
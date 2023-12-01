#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define DEBUG false

// The only thing that changes from the first to the second half is the number of elves
// in the top N that we need to observe (from 1 to 3)
#define FIRST_HALF_TOPN 1
#define SECOND_HALF_TOPN 3

using namespace std;

typedef long long ll;

void processInputRow(string s, vector<int>& calories) {

    // If a blank line (empty string) is reached, there is a new elf being defined (with,
    // so far, 0 calories)
    if(s == "")
        calories.push_back(0);

    // If not, we are still reading calories for the latest elf
    else
        calories[calories.size() - 1] += stoi(s);

    // For debugging purposes
    if(DEBUG)
        cout << "currently computing " << calories[calories.size() - 1] << endl;
}

int main() {

    string inputRow;
    vector<int> calories(1, 0);
    int result = 0;

    while(getline(cin, inputRow)) {
        processInputRow(inputRow, calories);
    }

    // rbegin() and rend() will sort the vector in descending order, which will make it easier
    // for gathering the biggest values. Despite this step being O(n*log(n)), it's less costly
    // than going through a topN rank vector every time (at least for this problem's constraints)  
    sort(calories.rbegin(), calories.rend());

    // Only the ending condition for this loop is changed on second half of the problem
    for(int i = 0; i < SECOND_HALF_TOPN; i++) {
        result += calories[i];
    }

    cout << result << endl;

    return 0;
}
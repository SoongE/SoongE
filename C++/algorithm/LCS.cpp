#include <time.h>
#include <windows.h>

#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

void getSequenceLength(string x, string y);
void getSequence(string x);

pair<string, string> generateString();

const int MAX_SIZE = 9;
int C[MAX_SIZE][MAX_SIZE];

int main() {
    int test_case = 2;

    for (int i = 0; i < test_case; i++) {
        auto [x, y] = generateString();

        cout << "example " << i + 1 << '\n';
        cout << "input#1: " << x << '\n';
        cout << "input#2: " << y << '\n';
        cout << "Longest Common Subsequence: ";

        getSequenceLength(x, y);

        getSequence(x);

        cout << '\n' << '\n';

        Sleep(1000);
    }
    return 0;
}

void getSequenceLength(string x, string y) {
    fill(&C[0][0], &C[MAX_SIZE - 1][MAX_SIZE], 0);

    for (int i = 1; i < MAX_SIZE; i++) {
        for (int j = 1; j < MAX_SIZE; j++) {
            if (x[i] == y[j]) {
                C[i][j] = C[i - 1][j - 1] + 1;
            } else
                C[i][j] = max(C[i - 1][j], C[i][j - 1]);
        }
    }
}

void getSequence(string x) {
    int i = MAX_SIZE - 1;
    int j = MAX_SIZE - 1;
    stack<int> res_stack;

    while (C[i][j] != 0) {
        if (C[i][j] == C[i][j - 1])
            j--;
        else if (C[i][j] == C[i - 1][j])
            i--;
        else if (C[i][j] - 1 == C[i - 1][j - 1]) {
            res_stack.push(i);
            i--;
            j--;
        }
    }

    while (!res_stack.empty()) {
        cout << x[res_stack.top()];
        res_stack.pop();
    }
}

inline pair<string, string> generateString() {
    int idx, num{8};
    vector<string> element = {"A", "C", "G", "T"};
    string x, y;

    srand((unsigned)time(NULL));

    //generate random string
    for (int i = 0; i < num; i++) {
        idx = rand() % 4;
        x.append(element[idx]);

        idx = rand() % 4;
        y.append(element[idx]);
    }

    return {x, y};
}
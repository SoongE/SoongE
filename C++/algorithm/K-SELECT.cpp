#include <time.h>

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
enum _direction {
    RESULT,
    LEFT,
    RIGHT,
};

//custom tools
pair<vector<int>, int> generateInput();
void printInput(vector<int>, int);
void printProcess(vector<int>, vector<int>, int, int, int);

//associated with K selection
void K_SELECT(vector<int>, int);
int getPivot(vector<int>);
tuple<vector<int>, int, vector<int>> partition(vector<int>, int);

int cnt;

int main() {
    for (int i = 0; i < 5; i++) {
        cnt = 0;
        auto [list, k] = generateInput();
        printInput(list, k);

        K_SELECT(list, k);
        cout << "---------------" << '\n';
        _sleep(2000);
    }
    return 0;
}

void K_SELECT(vector<int> list, int k) {
    cnt++;

    if (list.size() <= 1) {
        cout << "#" << cnt << " pivot=" << list[0] << " Left = [] Right = [] ## return " << list[0] << '\n';
        return;
    }

    int p = getPivot(list);
    auto [L, pivot_val, R] = partition(list, p);
    if (L.size() == k - 1) {
        printProcess(L, R, pivot_val, k, RESULT);
        return;
    } else if (L.size() > k - 1) {
        printProcess(L, R, pivot_val, k, LEFT);
        K_SELECT(L, k);
    } else {  // L.size() < k-1
        printProcess(L, R, pivot_val, k - 1 - L.size(), RIGHT);
        K_SELECT(R, k - 1 - L.size());
    }
}

int getPivot(vector<int> list) {
    srand((unsigned)time(NULL));
    return (rand() % list.size());
}

tuple<vector<int>, int, vector<int>> partition(vector<int> list, int p) {
    vector<int> L, R;
    int pivot_val = list[p];

    for (auto &&i : list) {
        if (i == pivot_val)
            continue;
        else if (i < pivot_val)
            L.push_back(i);
        else
            R.push_back(i);
    }
    return {L, pivot_val, R};
}

//Custom tools

inline pair<vector<int>, int> generateInput() {
    int idx, pre, num{8};
    vector<int> list;

    //generate random list
    for (int i = 1; i < num + 1; i++) {
        list.push_back(i);
    }
    srand((unsigned)time(NULL));
    for (int i = 0; i < num; i++) {
        idx = i + (rand() % (num - i));
        pre = list[i];
        list[i] = list[idx];
        list[idx] = pre;
    }

    //generate random k
    int k;
    k = (rand() % num) + 1;
    return {list, k};
}

inline void printInput(vector<int> list, int k) {
    cout << "---------------" << '\n';
    cout << "input array = [";
    for (int i = 0; i < list.size(); i++) {
        if (i == list.size() - 1)
            cout << list[i] << "], ";
        else
            cout << list[i] << " ";
    }
    cout << "k=" << k << '\n';
}

void printProcess(vector<int> L, vector<int> R, int pivot_val, int k, int direction) {
    cout << "#" << cnt << " pivot=" << pivot_val << " Left = ";

    // print left numbers of pivot
    if (L.empty()) {
        cout << "[] ";
    } else {
        for (auto &&i : L) {
            cout << i << " ";
        }
    }

    cout << "Right = ";
    // print right numbers of pivot
    if (R.empty()) {
        cout << "[] ";
    } else {
        for (auto &&i : R) {
            cout << i << " ";
        }
    }

    if (direction == RESULT) {
        cout << "## return " << pivot_val << '\n';
    } else if (direction == LEFT) {
        cout << "## go to left ## select k=" << k << '\n';
    } else {  //direction == RIGHT
        cout << "## go to right ## select k=" << k << '\n';
    }
}
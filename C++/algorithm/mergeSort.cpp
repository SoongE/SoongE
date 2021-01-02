#include <time.h>

#include <iostream>
#include <vector>

using namespace std;

vector<int> list;

void mergeSort(int, int);
void merge(int, int, int);
void printList();
void makeList(int);

int main() {
    int list_size;

    cout << "Input length of list  ";
    cin >> list_size;

    makeList(list_size);

    if (list_size <= 1) {
        for (auto &&i : list) {
            cout << i << " ";
        }
    } else {
        printList();
        mergeSort(0, list_size - 1);
    }

    return 0;
}

void mergeSort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(left, mid);       // Sort the left half
        mergeSort(mid + 1, right);  //Sort the right half
        merge(left, right, mid);
        printList();
    }
}

void merge(int left, int right, int mid) {
    int left_pos = left;      //left position
    int right_pos = mid + 1;  // right position
    vector<int> sorted;

    while (left_pos < mid + 1 && right_pos < right + 1) {
        if (list[left_pos] > list[right_pos]) {
            sorted.push_back(list[right_pos++]);
        } else {
            sorted.push_back(list[left_pos++]);
        }
    }

    while (left_pos < mid + 1) {
        sorted.push_back(list[left_pos++]);
    }

    while (right_pos < right + 1) {
        sorted.push_back(list[right_pos++]);
    }

    for (int i = left; i < right + 1; i++) {
        list[i] = sorted.front();
        sorted.erase(sorted.begin());
    }
}

inline void printList() {
    for (auto &&i : list) {
        cout << i << " ";
    }
    cout << '\n';
}

inline void makeList(int num) {
    int idx, pre;

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
}
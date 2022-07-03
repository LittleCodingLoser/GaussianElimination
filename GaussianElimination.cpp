#include <iostream>
#define FastIO ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
int num, checkResult;
double para[1000][1001], inverse[1000][1000];

void input() {
    FastIO
    cout << "Your n is? (Max is 1000) " << endl;
    cin >> num;
    for(int i = 0; i < num; i++) {
        cout << i + 1 << " row of parameters: " << endl;
        for(int j = 0; j <= num; j++) 
            cin >> para[i][j];
    }
}

// init the inverse matrix into a identity matrix
void initInverse() {
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == j) {
                inverse[i][j] = 1;
            } else {
                inverse[i][j] = 0;
            }
        }
    }
}

void subtractRow(double n, int a, double m, int b) {
    for(int i = 0; i <= num; i++) {
        para[a][i] = n * para[a][i] - m * para[b][i];
        if (i < num) inverse[a][i] = n * inverse[a][i] - m * inverse[b][i];
    }
}

int checkAns(int row) {
    if(para[row][row] == 0) {
        if(para[row][num] == 0)
            return 0; // 0 means there's INF answers
        else 
            return -1; // -1 means there's no real solution
    }
    return 1; // 1 means there's an only ans
}

void GaussianElimination(int row) {
    if(row == num) return;
    for(int i = 0; i < row; i++) {
        subtractRow(para[i][i], row, para[row][i], i);
    }
    checkResult = checkAns(row);
    if(checkResult != 1) return;
    GaussianElimination(row + 1);
    for(int i = row + 1; i < num; i++) {
        subtractRow(para[i][i], row, para[row][i], i);
    }
}

void printAns() {
    if(checkResult == 0) {
        cout << "INF answers";
    }
    else if(checkResult == -1) {
        cout << "No real solution";
    }
    else {
        for(int i = 0; i < num; i++) {
            cout << para[i][num] / para[i][i] << " ";
        }
        cout << endl;
    }
}

void printInverse() {
    if (checkResult == 1) {
        cout << "BTW, here's the inverse matrix of your original matrix" << endl;
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                cout << inverse[i][j] / para[i][i] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Sorry bro, no inverse matrix";
    }
}

int main() {
    input();
    initInverse();
    GaussianElimination(0);
    printAns();
    printInverse();
    return 0;
}

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <numeric>

#include "MatrixRowSum.h"

using namespace std;

int main() {
    srand(time(NULL));
    int height = 3, width = 5;
    vector<vector<int>> arr(height, vector<int>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            arr[i][j] = rand() % 10;
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    
    MatrixRowSum<int> obj;
    vector<int> res = obj.calc(arr);
    for (int i = 0; i < res.size(); i++) {
        cout << "Sum of row number " << i << " is " << res[i] << endl;
    }
}

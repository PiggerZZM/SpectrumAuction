#include <ctime>
#include <iostream>
#include "AHP/AHP.cpp"
#include "Kuhn-Munkres/KM.cpp"
#include "determineWinners/determineWinners.cpp"
#include "determinePrice/determinePrice.cpp"
#include "matching/matching.cpp"
#include "reuse/reuse.cpp"

using namespace std;

int main()
{
    void print(int k);
    srand(int(time(0)));
    vector<MatrixAttr> compareMatrixs;
    vector<MatrixSpec *> PUcompareMatrixs;
    vector<double> weightVec;

    // 确立获胜者
    int k = determineWinners(5, 7, PUBids, SUBids);

    // 基于偏好值的交易匹配
    matching(k - 1, compareMatrixs, PUcompareMatrixs, numOfAttributes, numOfSpectrums, weightVec);

    // 时空信道复用
    reuse(k - 1);

    // 基于偏好值的差别定价
    determinePrice(k - 1);

    print(k - 1);

    return 0;
}

void print(int k)
{
    cout << "----------------------------------------" << endl;
    cout << "Bids:" << endl;
    cout << "PUBids: ";
    for (int i = 0; i < 5; i++)
        cout << PUBids[i] << ' ';
    cout << endl;
    cout << "SUBids: ";
    for (int i = 0; i < 7; i++)
        cout << SUBids[i] << ' ';
    cout << endl;
    cout << "----------------------------------------" << endl;

    cout << "Matching: " << endl;
    cout << "SUs - PUs" << endl;
    for (int i = 1; i <= k; i++)
        cout << i << " - " << match[i] << endl;
    cout << "----------------------------------------" << endl;

    cout << "Weight matrix:" << endl;
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= k; j++)
            cout << Weight[i][j] << " ";
        cout << endl;
    }
    cout << "----------------------------------------" << endl;
    
    cout << "Price: " << endl;
    cout << "PUPrice: ";
    for (int i = 0; i < 5; i++)
        cout << PUPrice[i] << ' ';
    cout << endl;
    cout << "SUPrice: ";
    for (int i = 0; i < 7; i++)
        cout << SUPrice[i] << ' ';
    cout << endl;
    cout << "----------------------------------------" << endl;
}
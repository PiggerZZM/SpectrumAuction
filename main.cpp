#include <ctime>
#include <iostream>
#include "AHP/AHP.cpp"
#include "Kuhn-Munkres/KM.cpp"
#include "determineWinners/determineWinners.cpp"
#include "determinePrice/determinePrice.cpp"
#include "matching/matching.cpp"

using namespace std;

double PUBids[5] = {2.1, 9.8, 5.2, 1.0, 4.5};
double SUBids[7] = {7.1, 2.3, 9.9, 1.2, 5.8, 3.4, 6.5};

int main()
{
    void print(int numOfSpectrums, int numOfPUs, int numOfSUs);
    srand(int(time(0)));
<<<<<<< HEAD
    vector<MatrixXd> compareMatrixs;
    vector<vector<MatrixXd>> PUcompareMatrixs;
    const int numOfAttributes = 4;  // 论文中的例子是4个频谱属性，这里可以根据需要进行改动
=======
    vector<MatrixAttr> compareMatrixs;
    vector<vector<MatrixSpec>> PUcompareMatrixs;
    vector<double> weightVec;
>>>>>>> 42b479cd5b0ce2d30d12c478216bb7c08f51d1b4

    // 确立获胜者
    int k = determineWinners(5, 7, PUBids, SUBids);
    int numOfSpectrums = k - 1;

    // 基于偏好值的交易匹配
    matching(numOfSpectrums, compareMatrixs, PUcompareMatrixs, numOfAttributes, numOfSpectrums);

    // 基于偏好值的差别定价
    determinePrice(numOfSpectrums);

    // 输出结果
    print(numOfSpectrums, 5, 7);

    return 0;
}

void print(int numOfSpectrums, int numOfPUs, int numOfSUs)
{
    cout << "----------------------------------------" << endl;
    cout << "Bids:" << endl;
    cout << "PUBids: ";
    for (int i = 0; i < numOfPUs; i++)
        cout << PUBids[i] << ' ';
    cout << endl;
    cout << "SUBids: ";
    for (int i = 0; i < numOfSUs; i++)
        cout << SUBids[i] << ' ';
    cout << endl;
    cout << "----------------------------------------" << endl;

    cout << "Matching: " << endl;
    cout << "SUs - PUs" << endl;
    for (int i = 1; i <= numOfSpectrums; i++)
        cout << i << " - " << match[i] << endl;
    cout << "----------------------------------------" << endl;

    cout << "Weight matrix:" << endl;
    for (int i = 1; i <= numOfSpectrums; i++)
    {
        for (int j = 1; j <= numOfSpectrums; j++)
            cout << Weight[i][j] << " ";
        cout << endl;
    }
    cout << "----------------------------------------" << endl;

    cout << "Price: " << endl;
    cout << "PUPrice: ";
    for (int i = 0; i < numOfPUs; i++)
        cout << PUPrice[i] << ' ';
    cout << endl;
    cout << "SUPrice: ";
    for (int i = 0; i < numOfSUs; i++)
        cout << SUPrice[i] << ' ';
    cout << endl;
    cout << "McAfee PUPrice: " << PUPriceMcAfee << endl;
    cout << "McAfee SUPrice: " << SUPriceMcAfee << endl;
    cout << "----------------------------------------" << endl;

    double prefSum = 0;
    double randomPrefSum = 0;
    for (int i = 0; i < numOfSpectrums; i++)
    {
        prefSum += Weight[i + 1][match[i + 1]];
        randomPrefSum += Weight[i + 1][randomMatch[i] + 1];
    }
    cout << "Total preference value: " << prefSum << endl;
    cout << "Total preference value with a random matching: " << randomPrefSum << endl;
    cout << "----------------------------------------" << endl;
}
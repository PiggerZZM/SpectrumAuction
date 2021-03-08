#include <ctime>
#include <iostream>
#include <cstdlib>
#include "AHP/AHP.cpp"
#include "Kuhn-Munkres/KM.cpp"
#include "determineWinners/determineWinners.cpp"
#include "determinePrice/determinePrice.cpp"
#include "matching/matching.cpp"

using namespace std;

void init(double PUBids[], double SUBids[], double PUPrice[], double SUPrice[], int numOfPUs, int numOfSUs)
{
    for (int i = 0; i < numOfPUs; i++)
    {
        PUBids[i] = rand() % 100 + 1;
        PUPrice[i] = 0;
    }
    for (int i = 0; i < numOfSUs; i++)
    {
        SUBids[i] = rand() % 100 + 1;
        SUPrice[i] = 0;
    }
}

void print(int numOfSpectrums, int numOfPUs, int numOfSUs, double PUBids[], double SUBids[], double PUPrice[], double SUPrice[])
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

int main()
{
    srand(int(time(0)));
    vector<MatrixXd> compareMatrixs;
    vector<vector<MatrixXd>> PUcompareMatrixs;

    const int numOfAttributes = 100;
    const int numOfPUs = 10;
    const int numOfSUs = 20;

    double PUBids[numOfPUs];
    double SUBids[numOfSUs];
    double PUPrice[numOfPUs];
    double SUPrice[numOfSUs];

    init(PUBids, SUBids, PUPrice, SUPrice, numOfPUs, numOfSUs);

    // 确立获胜者
    int k = determineWinners(numOfPUs, numOfSUs, PUBids, SUBids);
    int numOfSpectrums = k - 1;

    // 基于偏好值的交易匹配
    matching(numOfSpectrums, compareMatrixs, PUcompareMatrixs, numOfAttributes, numOfSpectrums);

    // 基于偏好值的差别定价
    determinePrice(numOfSpectrums, PUBids, SUBids, PUPrice, SUPrice);

    // 输出结果
    print(numOfSpectrums, numOfPUs, numOfSUs, PUBids, SUBids, PUPrice, SUPrice);

    return 0;
}

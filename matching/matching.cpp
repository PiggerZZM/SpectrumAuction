#ifndef MATCHING_CPP
#define MATCHING_CPP

#include <vector>
#include <cstdlib>
#include "../AHP/AHP.cpp"
#include "../Kuhn-Munkres/KM.cpp"
using namespace std;

extern const int maxn;
extern double Weight[100][100];
double compare[17] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1.0 / 2, 1.0 / 3, 1.0 / 4, 1.0 / 5, 1.0 / 6, 1.0 / 7, 1.0 / 8, 1.0 / 9};
int randomMatch[maxn];

double randPick()
{
    return compare[rand() % 17];
}

void genRandcompareMatrix(MatrixAttr &compareMatrix)
{
    for (int x = 0; x < numOfAttributes; x++)
        compareMatrix(x, x) = 1;
    for (int y = 1; y < numOfAttributes; y++)
    {
        double temp = randPick();
        compareMatrix(0, y) = temp;
        compareMatrix(y, 0) = 1.0 / temp;
    }
    for (int x = 1; x < numOfAttributes; x++)
        for (int y = x + 1; y < numOfAttributes; y++)
        {
            compareMatrix(x, y) = compareMatrix(x, 0) * compareMatrix(0, y);
            compareMatrix(y, x) = compareMatrix(y, 0) * compareMatrix(0, x);
        }
}

void genRandPUcompareMatrixs(MatrixSpec &PUcompareMatrix)
{
    for (int x = 0; x < numOfSpectrums; x++)
        PUcompareMatrix(x, x) = 1;
    for (int y = 1; y < numOfSpectrums; y++)
    {
        double temp = randPick();
        PUcompareMatrix(0, y) = temp;
        PUcompareMatrix(y, 0) = 1.0 / temp;
    }
    for (int x = 1; x < numOfSpectrums; x++)
        for (int y = x + 1; y < numOfSpectrums; y++)
        {
            PUcompareMatrix(x, y) = PUcompareMatrix(x, 0) * PUcompareMatrix(0, y);
            PUcompareMatrix(y, x) = PUcompareMatrix(y, 0) * PUcompareMatrix(0, x);
        }
}

void InitMatrixs(vector<MatrixAttr> &compareMatrixs, vector<MatrixSpec *> &PUcompareMatrixs, int k)
{
    for (int i = 0; i < k; i++)
    {
        MatrixAttr compareMatrix;
        genRandcompareMatrix(compareMatrix);
        compareMatrixs.push_back(compareMatrix);
    }

    for (int i = 0; i < k; i++)
    {
        MatrixSpec ithPUcompareMatrixs[numOfAttributes];
        for (int j = 0; j < numOfAttributes; j++)
        {
            MatrixSpec PUcompareMatrix;
            genRandPUcompareMatrixs(PUcompareMatrix);
            ithPUcompareMatrixs[j] = PUcompareMatrix;
        }
        PUcompareMatrixs.push_back(ithPUcompareMatrixs);
    }
}

void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void Knuth_Shuffle(int randomMatch[], int n)
{
    for (int i = n - 1; i >= 0; i--)
        swap(randomMatch[i], randomMatch[rand() % (i + 1)]);
}

void matching(int k, vector<MatrixAttr> &compareMatrixs, vector<MatrixSpec *> &PUcompareMatrixs, int numOfAttributes, int numOfSpectrums, vector<double> &weightVec)
{

    InitMatrixs(compareMatrixs, PUcompareMatrixs, k);

    // 计算偏好值
    for (int i = 0; i < k; i++)
    {
        weightVec.clear();
        if (AHP(numOfSpectrums, numOfAttributes, compareMatrixs[i], PUcompareMatrixs[i], weightVec))
            for (int j = 0; j < k; j++)
                Weight[i + 1][j + 1] = weightVec[j];
    }

    // 最大权匹配
    KM(k);

    // 随机匹配
    for (int i = 0; i < k; i++)
        randomMatch[i] = i;
    Knuth_Shuffle(randomMatch, k);
}

#endif
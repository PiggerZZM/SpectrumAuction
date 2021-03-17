#ifndef AHP_CPP
#define AHP_CPP

#include <iostream>
#include "Eigen/Dense"
#include <vector>
using namespace std;
using namespace Eigen;

const double RI[] = {0, 0, 0, 0.58, 0.90, 1.12, 1.24, 1.32, 1.41, 1.45, 1.49, 1.51}; // 随机一致性指标
double CR3, CI3, CR2, CI2, RI3, CR;                                                  // 一致性指标

void calWeightVec1(MatrixXd compareMatrix, VectorXd &NweightVec, double &NmaxEigenValue, int numOfSpectrums, int numOfAttributes)
{
    // 计算第2层对第1层的权向量
    MatrixXd tempMatrix = compareMatrix;
    // 计算近似特征向量
    // 列向量归一化
    double jColSum;
    for (int j = 0; j < numOfAttributes; j++)
    {
        jColSum = 0;
        for (int i = 0; i < numOfAttributes; i++)
            jColSum += tempMatrix(i, j);
        for (int i = 0; i < numOfAttributes; i++)
            tempMatrix(i, j) /= jColSum;
    }
    // 按行求和
    for (int i = 0; i < numOfAttributes; i++)
    {
        NweightVec(i, 0) = 0;
        for (int j = 0; j < numOfAttributes; j++)
            NweightVec(i, 0) += tempMatrix(i, j);
    }
    // 归一化
    double colSum = 0;
    for (int i = 0; i < numOfAttributes; i++)
        colSum += NweightVec(i, 0);
    for (int i = 0; i < numOfAttributes; i++)
        NweightVec(i, 0) /= colSum;

    // 计算近似最大特征值
    VectorXd temp = compareMatrix * NweightVec;
    for (int i = 0; i < numOfAttributes; i++)
        NmaxEigenValue += (temp(i, 0) / NweightVec(i, 0) / numOfAttributes);
}

void calWeightVec2(vector<MatrixXd> PUcompareMatrixs, VectorXd MweightVecs[], double MmaxEigenValues[], int numOfSpectrums, int numOfAttributes)
{
    // 计算第3层对第2层的权向量
    double jColSum;
    double colSum;
    for (int index = 0; index < numOfAttributes; index++)
    {
        MatrixXd tempMatrix = PUcompareMatrixs[index];
        // 计算近似特征向量
        // 列向量归一化
        for (int j = 0; j < numOfSpectrums; j++)
        {
            jColSum = 0;
            for (int i = 0; i < numOfSpectrums; i++)
                jColSum += tempMatrix(i, j);
            for (int i = 0; i < numOfSpectrums; i++)
                tempMatrix(i, j) /= jColSum;
        }
        // 按行求和
        for (int i = 0; i < numOfSpectrums; i++)
        {
            MweightVecs[index](i, 0) = 0;
            for (int j = 0; j < numOfSpectrums; j++)
                MweightVecs[index](i, 0) += tempMatrix(i, j);
        }

        // 归一化
        colSum = 0;
        for (int i = 0; i < numOfSpectrums; i++)
            colSum += MweightVecs[index](i, 0);
        for (int i = 0; i < numOfSpectrums; i++)
            MweightVecs[index](i, 0) /= colSum;

        // 计算近似最大特征值
        VectorXd temp = PUcompareMatrixs[index] * MweightVecs[index];
        for (int i = 0; i < numOfSpectrums; i++)
            MmaxEigenValues[index] += (temp(i, 0) / MweightVecs[index](i, 0) / numOfSpectrums);
    }
}

bool consistenceTest(VectorXd NweightVec, double NmaxEigenValue, int numOfSpectrums, int numOfAttributes)
{
    // 一致性检验
    CI2 = (NmaxEigenValue - numOfAttributes) / (numOfAttributes - 1);
    CR2 = CI2 / RI[numOfAttributes];
    if (CR2 > 0.1)
    {
        cout << "Consistence test failed." << endl;
        return false;
    }
    else
        return true;
}

bool combineConsistenceTest(VectorXd NweightVec, double MmaxEigenValues[], int numOfSpectrums, int numOfAttributes)
{
    // 组合一致性检验
    CI3 = 0, RI3 = 0;
    for (int i = 0; i < numOfAttributes; i++)
    {
        CI3 += (MmaxEigenValues[i] - numOfSpectrums) / (numOfSpectrums - 1) * NweightVec(i, 0);
        RI3 += RI[3] * NweightVec(i, 0);
    }

    CR3 = CI3 / RI3;
    CR = CR3 + CR2;
    if (CR > 0.1)
    {
        cout << "Combined consistence test failed." << endl;
        return false;
    }
    else
        return true;
}

void calCombineWeightVec(VectorXd NweightVec, VectorXd MweightVecs[], int numOfSpectrums, int numOfAttributes, vector<double> &weightVec)
{
    // 计算第3层对第1层的组合权向量
    MatrixXd W(numOfSpectrums, numOfAttributes);
    for (int c = 0; c < numOfAttributes; c++)
        for (int r = 0; r < numOfSpectrums; r++)
            W(r, c) = MweightVecs[c](r);
    VectorXd combineWeightVec = W * NweightVec;
    for (int i = 0; i < numOfSpectrums; i++)
        weightVec.push_back(combineWeightVec(i, 0));
}

bool AHP(int numOfSpectrums, int numOfAttributes, MatrixXd compareMatrix, vector<MatrixXd> PUcompareMatrixs, vector<double> &weightVec)
{
    VectorXd NweightVec(numOfAttributes);
    double NmaxEigenValue = 0;
    // 计算第2层对第1层的权向量
    calWeightVec1(compareMatrix, NweightVec, NmaxEigenValue, numOfSpectrums, numOfAttributes);

    // 第2层一致性检验
    // if (!consistenceTest(NweightVec, NmaxEigenValue, numOfSpectrums, numOfAttributes))
    //     return false;

    // 计算第3层对第2层的权向量
    VectorXd MweightVecs[numOfAttributes];
    for (int i = 0; i < numOfAttributes; i++)
        MweightVecs[i].resize(numOfSpectrums);
    double MmaxEigenValues[numOfAttributes];
    for (int i = 0; i < numOfAttributes; i++)
        MmaxEigenValues[i] = 0;
    calWeightVec2(PUcompareMatrixs, MweightVecs, MmaxEigenValues, numOfSpectrums, numOfAttributes);

    // // 第3层对第1层的组合一致性检验
    // if (!combineConsistenceTest(NweightVec, MmaxEigenValues, numOfSpectrums, numOfAttributes))
    //     return false;

    // 计算第3层对第1层的组合权向量
    calCombineWeightVec(NweightVec, MweightVecs, numOfSpectrums, numOfAttributes, weightVec);

    return true;
}

#endif
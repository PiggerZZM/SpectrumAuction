#ifndef KM_CPP
#define KM_CPP

#include <algorithm>
using namespace std;

const int maxn = 1005;

double Lx[maxn], Ly[maxn]; // 顶标
int match[maxn];    // 记录匹配
int temp[maxn];
bool S[maxn], T[maxn];  // 算法中的两个集合S和T
double Weight[100][100];
double eps = 10e-6;

bool findPath(int i, int n)
{
    S[i] = true;
    for (int j = 1; j <= n; j++)
    {
        if ((Lx[i] + Ly[j] - Weight[i][j]) <= eps && !T[j]) // 找出在相等子图里又还未被标记的边
        {
            T[j] = true;
            if (!match[j] || findPath(match[j], n)) // 未被匹配，或者已经匹配又找到增广路
            {
                match[j] = i;
                return true;
            }
        }
    }
    return false;
}

void update(int n) // 更新顶标
{
    // 计算a
    double a = 99999999999;
    for (int i = 1; i <= n; i++)
        if (S[i])
            for (int j = 1; j <= n; j++)
                if (!T[j])
                    a = min(a, Lx[i] + Ly[j] - Weight[i][j]);

    // 修改顶标
    for (int i = 1; i <= n; i++)
        if (S[i])
            Lx[i] -= a;
    for (int j = 1; j <= n; j++)
        if (T[j]) 
            Ly[j] += a;
}

void Init(int n)
{
    // 将X集合的顶标设为最大边权，Y集合的顶标设为0
    for (int i = 1; i <= n; i++)
    {
        Lx[i] = 0;
        for (int j = 1; j <= n; j++)
        {
            match[j] = 0;   // match记录的是Y集合里的点与谁匹配
            Ly[j] = 0;
            Lx[i] = max(Lx[i], Weight[i][j]);
        }
    }
}

void KM(int n)
{
    Init(n);

    for (int i = 1; i <= n; i++)
    {
        while (true)
        {
            for (int i = 1; i <= n; i++)
                S[i] = 0;
            for (int j = 1; j <= n; j++)
                T[j] = 0;
            if (!findPath(i, n))
                update(n);
            else
                break;
        }
    }

    for (int i=1; i<=n; i++)
        temp[i] = match[i];
    for (int i=1; i<=n; i++)
        match[temp[i]] = i;
}

#endif
#ifndef DETERMINEWINNERS_CPP
#define DETERMINEWINNERS_CPP

#include <algorithm>
using namespace std;

double PUBids[5] = {2.1, 9.8, 5.2, 1.0, 4.5};
double SUBids[7] = {7.1, 2.3, 9.9, 1.2, 5.8, 3.4, 6.5};

bool cmp(double a, double b)
{
    return a > b;
}

int determineWinners(int M, int N, double PUBids[], double SUBids[])
{
    int k;
    sort(PUBids, PUBids + M);
    sort(SUBids, SUBids + N, cmp);
    int minLength = min(M, N);
    for (k = 0; k < minLength; k++)
    {
        if (PUBids[k] > SUBids[k])
            break;
    }
    return k;
}

#endif
#ifndef DETERMINEWINNERS_CPP
#define DETERMINEWINNERS_CPP

#include <algorithm>
using namespace std;

bool cmp(double a, double b)
{
    return a > b;
}

int determineWinners(int numOfPUs, int numOfSUs, double PUBids[], double SUBids[])
{
    int k;
    sort(PUBids, PUBids + numOfPUs);
    sort(SUBids, SUBids + numOfSUs, cmp);
    int minLength = min(numOfPUs, numOfSUs);
    for (k = 0; k < minLength; k++)
    {
        if (PUBids[k] > SUBids[k])
            break;
    }
    return k;
}

#endif
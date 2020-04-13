#ifndef PRICE_CPP
#define PRICE_CPP

#include "../Kuhn-Munkres/KM.cpp"

extern double PUBids[5];
extern double SUBids[7];
extern const int maxn;
extern int match[maxn];
extern double Weight[100][100];

double PUPrice[5] = {0};
double SUPrice[7] = {0};

void determinePrice(int k)
{
    double Bks = SUBids[k];
    double Bkb = PUBids[k];
    for (int i = 0; i < k; i++)
    {
        int SUindex = i;
        int PUindex = match[SUindex + 1] - 1;
        double alpha = Weight[SUindex + 1][PUindex + 1];
        PUPrice[PUindex] = 1.0 * (Bkb + Bks) / 2 * alpha + (1 - alpha) * Bks;
        SUPrice[SUindex] = 1.0 * (1 - alpha) * (Bkb + Bks) / 2 + alpha * Bkb;
    }
}

#endif
#ifndef PRICE_CPP
#define PRICE_CPP

#include "../Kuhn-Munkres/KM.cpp"

extern const int maxn;
extern int match[maxn];
extern double Weight[100][100];

double PUPriceMcAfee;
double SUPriceMcAfee;

void determinePrice(int k, double PUBids[], double SUBids[], double PUPrice[], double SUPrice[])
{
    double Bks = PUBids[k];
    double Bkb = SUBids[k];
    PUPriceMcAfee = Bks;
    SUPriceMcAfee = Bkb;
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
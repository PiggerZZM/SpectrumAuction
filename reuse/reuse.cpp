#include <algorithm>
#include "../Kuhn-Munkres/KM.cpp"
using namespace std;

extern double Weight[100][100];
extern const int maxn;
extern int match[maxn];
int notConflict[maxn][maxn] = {0};

void reuse(int k)
{
    for (int i = 1; i <= k; i++)
    {
        double currentPref = Weight[i][match[i]];
        for (int j = 1; j <= k; j++)
        {
            if (notConflict[i][j] && Weight[i][j] > currentPref)
            {
                currentPref = Weight[i][j];
                match[i] = j;
            }
        }
    }
}
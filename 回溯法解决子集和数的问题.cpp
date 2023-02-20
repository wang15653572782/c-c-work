#include<iostream>
#include<fstream>
using namespace std;

#define N 100

int W[N];
bool X[N];

int M;
int n;

void SUMOFSUB(int s, int k, int r)
{
    int j;
    X[k] = 1;
    if (s + W[k] == M)
    {
        for (j = 1; j <= k; j++)
        {
            cout << X[j] << " ";
        }
        cout << endl;
    }
    else
    {
        if (s + W[k] + W[k + 1] <= M)
        {
            SUMOFSUB(s + W[k], k + 1, r - W[k]);
        }
    }

    if ((s + r - W[k] >= M) && (s + W[k + 1] <= M))
    {
        X[k] = 0;
        SUMOFSUB(s, k + 1, r - W[k]);
    }

}

int main()
{
   
    
    cin >> n;
   
    cin >> M;
    int r=0,i = 1;
    while (i <= n)
    {
       
        cin >> W[i];
//        if (W[i - 1] > W[i])
//            return 1;

        r += W[i++];
    }
    cout << endl;
    SUMOFSUB(0, 1, r);  
    system("PAUSE");    
    return 0;
}

#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int threshold;
void Restore(int* R, int f, int e) {
    int j = f; int m; int s;
    while (j <= e / 2) {
        if (2 * j + 1 <= e && R[2 * j] < R[2 * j + 1])m = 2 * j + 1;
        else m = 2 * j;
        if (R[m] > R[j]) {
            s = R[m]; R[m] = R[j]; R[j] = s; j = m;
        }
        else return;
    }
}
void HeapSort(int* R, int n) {
    int i;
    for (i = n / 2; i >= 1; --i)
        Restore(R, i, n);
    printf("Heap:");
    for (int i = 1; i <= n; ++i) {
        printf("%d ", R[i]);
    }
    printf("\n");
    int tmp;
    for (i = n; i >=2; --i) {
        tmp = R[1]; R[1] = R[i]; R[i] = tmp;
        Restore(R, 1, i - 1);
    }
}
int Partition(int R[], int m, int n) {
    int i = m; int j = n + 1; int k = R[m]; int temp; int sb;
    while (i < j) {
        i++;
        while (R[i] <= k)i++;
        j--;
        while (R[j] > k)j--;
        if (i < j) {
            temp = R[i]; R[i] = R[j]; R[j] = temp;
        }
    }
    sb = R[m]; R[m] = R[j]; R[j] = sb;

    return j;
}
void Qsort(int* R, int m, int n, int depth_limit) {
    int i, j, k;
    while (n - m + 1 > threshold) {
        if (depth_limit == 0) {
            HeapSort(R + m - 1, n - m + 1);
            return;
        }
        depth_limit--;
        j = Partition(R, m, n);
        Qsort(R, m, j - 1, depth_limit);
        m = j + 1;
    }
}
void InsertSort(int* R, int n) {
	int i,k;
    for (int j = 2; j <= n; ++j) {
        i = j - 1;
        k=R[j];
        while (i>0&&R[i]>k) {
            R[i + 1] = R[i];i--;
        }
        R[i + 1] = k;
    }
}
void sort(int* R, int n) {
    int i, d;
    if (n > 1) {
        d = (int)(2 * log2(n));
        printf("depth_limit:%d\n", d);
        Qsort(R, 1, n, d);
        printf("Intermediate:");
        for (i = 1; i <= n; ++i)
            printf("%d ", R[i]);
        printf("\n");
        InsertSort(R, n);
    }
}

int main()
{
    int n, i;
    int a[50010];
    scanf("%d %d", &n, &threshold);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    sort(a, n);

    printf("Final:");
    for (i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}



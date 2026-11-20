# 高斯消元

可以很快的求解方程，在 n^3 内求解 n 个 n 元的方程。可能无解，可能有无穷组解，也可能只有一组解

用到了初等行列变化

```
枚举每一列 c
    找到本列绝对值最大的一行（前面枚举过的行不计入）
    将该行换到最上面
    将该行第一个数变成 1
    将下面所有行的第 c 列削成 0
若为完美阶梯形，可求唯一解
```

```
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 110;
const double eps = 1e-6;

int n;
double a[N][N];

int gauss()
{
    int c, r;
    for(c = 0, r = 0; c < n; c ++)
    {
        int t = r;
        for(int i = r; i < n; i ++)
            if(fabs(a[i][c]) > fabs(a[t][c]))
                t = i;
        if(fabs(a[t][c]) < eps) continue;
        
        for(int i = c; i <= n; i ++) swap(a[t][i], a[r][i]);
        for(int i = n; i >= c; i --) a[r][i] /= a[r][c];
        for(int i = r + 1; i < n; i ++)
            if(fabs(a[i][c]) > eps)
                for(int j = n; j >= c; j --)
                    a[i][j] -= a[r][j] * a[i][c];
        
        r ++;
    }
    if(r < n)
    {
        for(int i = r; i < n; i ++)
            if(fabs(a[i][n]) > eps)
                return 2;
        return 1;
    }
    
    for(int i = n - 1; i >= 0; i --)
        for(int j = i + 1; j < n; j ++)
            a[i][n] -= a[i][j] * a[j][n];

    return 0;
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n + 1; j ++)
            cin >> a[i][j];
            
    int t = gauss();
    if(t == 0)
        for(int i = 0; i < n; i ++) printf("%.2lf\n", a[i][n]);
    else if(t == 1) puts("Infinite group solutions");
    else puts("No solution");
    
    return 0;
}
```






























































































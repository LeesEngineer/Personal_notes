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

# 求组合数

</br>

## 求组合数 1

<b>递推</b>

C_a^b = C_{a-1}^b + C_{a-1}^{b-1}

C_a^b = a!/(b!(a-b)!)

1 <= a, b <= 2000

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2010, mod = 1e9 + 7;

int c[N][N];

void init()
{
    for(int i = 0; i < N; i ++)
        for(int j = 0; j <= i; j ++)
            if(!j) c[i][j] = 1;
            else c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
}

int main()
{
    init();
    
    int n;
    cin >> n;
    while(n --)
    {
        int a, b;
        cin >> a >> b;
        cout << c[a][b] << endl;
    }
}
```

</br>

## 求组合数 2

<b>预处理</b>

1 <= b <= a <= 1e5

C_a^b = a!/(b!(a-b)!)

预处理一下阶乘：fact[i] = i! mod 1e9+7

再求逆元，infact[i] = i!^-1 mod 1e9+7

C_a^b = fact[a] * infact[b] * infact[a-b]

<img width="1176" height="370" alt="QQ_2026-11-20_16-23-06" src="https://github.com/user-attachments/assets/1f8a0284-6532-408a-a82f-225bacd325ea" />

```
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 1e5 + 10, mod = 1e9 + 7;

int fact[N], infact[N];

int qmi(int a, int k, int p)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = (ll) res * a % p;
        a = (ll) a * a % p;
        k >>= 1;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    
    fact[0] = 1;
    for(int i = 1; i < N; i ++)
        fact[i] = (ll) i * fact[i-1] % mod;
    
    infact[N-1] = qmi(fact[N-1], mod - 2, mod);
    for(int i = N - 1; i >= 1; i --)
        infact[i-1] = (ll) i * infact[i] % mod;
    
    while(n --)
    {
        int a, b;
        cin >> a >> b;
        cout << ((ll) fact[a] * infact[a-b] % mod) * infact[b] % mod << endl;
    }
}
```

只调用一次 qmi

</br>

## 求组合数 3

卢卡斯定理 Lucas

20组询问，每组 1 <= b <= a <= 1e18，p <= 1e5

C_a^b [同余] C_{a mod p}^{b mod p} * C_{a // p}^{b // p} (mod p)

O(p logN logp)

```
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int p;

int qmi(int a, int k, int p)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = (ll) res * a % p;
        a = (ll) a * a % p;
        k >>= 1;
    }
    return res;
}

int C(int a, int b)
{
    if(b > a) return 0;
    int res = 1;
    for(int i = 1; i <= b; i ++)
    {
        res = (ll) res * (a - i + 1) % p;
        res = (ll) res * qmi(i, p-2, p) % p;
    }
    return res;
}

int lucas(ll a, ll b)
{
    if(a < p && b < p) return C(a, b);
    return (ll) C(a % p, b % p) * lucas(a / p, b / p) % p;
}

int main()
{
    int n;
    cin >> n;
    while(n --)
    {
        ll a, b;
        cin >> a >> b >> p;
        cout << lucas(a, b) << endl;
    }
    return 0;
}
```

<b>函数C通常用于卢卡斯定理（Lucas 定理）中计算较小的组合数。</b>

<img width="628" height="152" alt="QQ_2026-11-20_16-54-15" src="https://github.com/user-attachments/assets/0d2edb2f-9932-4990-b5e3-b6b11171885e" />

</br>

## 求组合数 4

不进行模运算了，用高精度算出来


























































































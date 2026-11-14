# 欧拉函数

phi(n): 1 到 n 中与 n 互质的数的个数

N = p1^a1 p2^a2 ... pk^ak

phi(N) = N (1 - 1/p1) (1 - 1/p2) ... (1 - 1/pk)

利用了容斥原理

1. 从 1 到 N 中去掉所有 p1，p2，pk 的所有倍数

N - N/p1 - N/p2 - ... - N/pk

2. 加上所有 pi*pj 的倍数（因为被剪了两次）

N - N/p1 - N/p2 - ... - N/pk + N/p1p2 + N/p1p3 + ...

3. 减去所有 pi*pj*pk 的倍数

N - N/p1 - N/p2 - ... - N/pk + N/p1p2 + N/p1p3 + ... - N/p1p2p3 - N/p1p2p4 - ...

4. 以此类推

时间复杂度的瓶颈在分解质因数上，为 O(sqrt(n))

```
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    
    while(n --)
    {
        int a;
        cin >> a;
        
        int res = a;
        for(int i = 2; i <= a / i; i ++)
        {
            if(a % i == 0)
            {
                res = res / i * (i - 1); // 不能有小数
                while(a % i == 0) a /= i;
            }
        }
        if(a > 1) res = res / a * (a - 1);
        
        cout << res << endl;
    }
}
```

## 用筛法来求欧拉函数

线形筛法可以顺便求出来很多东西

求 1 到 N 中每个数的欧拉函数

```
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e6 + 10;

int primes[N], cnt;
int phi[N];
bool st[N];

LL get_eulers(int n)
{
    for(int i = 2; i <= n; i ++)
    {
        if(!st[i])
        {
            primes[cnt ++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0; primes[j] <= n / i; j ++)
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0)
            {
                phi[primes[j] * i] = primes[j] * phi[i];
                break;
            }

            phi[primes[j] * i] = phi[i] * (primes[j] - 1);
            // phi[primes[j] * i] = primes[i] * phi[i] /primes[j] * (primes[j] - 1);
        }
    }
    
    LL res = 0;
    for(int i = 1; i <= n; i ++) res += phi[i];
    
    return res;
}

int main()
{
    int n;
    cin >> n;
    
    phi[1] = 1;
    
    cout << get_eulers(n) << endl;
    
    return 0;
}
```

O(n)







































































































































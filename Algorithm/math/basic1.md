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

</br>

## 欧拉定理

如果 a 和 n 互质，则有 a^(phi(n)) 除以 n 的余数为 1

费马小定理：如果 a 与 n 互质，并且 p 为质数，则有 a^(p - 1) 除以 p 的余数为 1

</br>

# 快速幂

快速求出 a^k mod p，O(logk)

1 <= a, p, k <= 1e9

预处理出 a^(2^0) mod p, a^(2^1) mod p, a^(2^2) mod p, ..., a^(2^logk) mod p

很好预处理，后一项就是前一项的平方。随后组合出 a^k

```
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int qmi(int a, int k, int p)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = (ll) res * a % p;
        a = (ll) a * a % p;
        k = k >> 1;
    }
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    while(n --)
    {
        int a, k, p;
        scanf("%d%d%d", &a, &k, &p);
        
        cout << qmi(a, k, p) << endl;
    }
}
```

## 快速幂求逆元

因为数论里面除法很麻烦，故找到 x 使得 a/b [同余] a*x (mod n)

也就是给一个 b，找到 x 使得：b*x [同余] 1 (mod n)

费马定理有：如果 b 与 p 互质，b^(p-1) 模 p 同余 1，则 b * b^(p-2) 模 p 同余 1

故 b^(p-2) 就是 b 的逆元

```
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int qmi(int a, int k, int p)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = (ll) res * a % p;
        a = (ll) a * a % p;
        k = k >> 1;
    }
    return res;
}

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    while(n --)
    {
        int a, p;
        scanf("%d%d", &a, &p);

        if(gcd(a, p) != 1) cout << "impossible" << endl; // 如果题目保证 p 是质数，判断 a % p 是否为 0 （a 是否为 p 的倍数）即可
        else cout << qmi(a, p - 2, p) << endl;
    }
}
```

</br>

# 扩展欧几里得算法

先说一下裴蜀定理：任意一对正整数a, b。一定存在整数 x 和 y 使得 ax + by = gcd(a, b)，并且是 a 和 b 能凑出来的最小的正整数

```
#include <iostream>
#include <algorithm>

using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
    if(!b)
    {
        x = 1, y = 0; // y=0只是一个解，a*1 + 0 * 0 = a
        return a;
    }
    int d = exgcd(b, a % b, y, x); // 这里翻转一下，有 by + (a mod b)x = gcd(a, b)
    
    y -= a / b * x;
    
    return d;
}


int main()
{
    int n;
    cin >> n;
    while(n --)
    {
        int a, b, x, y;
        cin >> a >> b;
        
        exgcd(a, b, x, y);
        
        cout << x << " " << y << endl;
    }
}
```

```
by + (a % b)x = d
by + (a - (a//b)b)x = d
ax + b(y - (a//b)x) = d
```



































































































































<p>数据结构三大难点：线段树，Splay，块状链表</p>

</br>

# 基本原理

</br>

<p>树状数组解决两个问题：</p>

1. 快速求前缀和 O(logn)

2. 修改某个数 O(logn)

<p>相比维护:</p>
  
1. 数组：O(n), O(1)
2. 前缀和数组：O(1), O(n)

<p>树状数组基于二进制的想法解决问题，比如:</p>

`x = 2^(i_k) + 2^(i_k-1) + 2^(i_k-2) + ... + 2^(i_1), k <= logx`

<p>可以把 1 ～ x 这个区间，用 i 划分成 k 段</p>

```
// 从低位开始减
(x - 2^(i_1), x]                                 // 包含 2^(i_1) 个数
(x - 2^(i_1) - 2^(i_2), x - 2^(i_1)]       
...
(0, x - 2^(i_1) - 2^(i_2) - ... - 2^(i_k-1)]     // 包含 2^(i_k) 个数
```

<p>把 1～x 分成最多 logx 个部分，最多只需要加上 logx 个数就能算出来 1～x</p>

<p>(L, R] 长度一定是 R 的二进制表示的最后一位 1 所对应的次幂</p>

```
int lowbit(int x)
{
    return x & -x;
}
```

<p>所以 (L, R] = (R - lowbit(R), R]。那就可以用一个数组来表示这个区间的和：</p>

`C[R] = [R - lowbit(R) + 1  , R]`

<p>最多有 n 个区间，因为区间是被右端点唯一确定的</p>

`c[x] = a[x - bowbit(x) + 1, x]`

<p>c[x] 表示以 x 为右端点，长度为 lowbit(x) 的区间的所有元素的和</p>

<p>考虑 c[x] 间的关系:</p>

<img width="1758" height="756" alt="QQ_1757749816588" src="https://github.com/user-attachments/assets/b27c5326-7fae-40f1-8123-c37175802925" />

```
c[16] = c[8] + c[12] + c[14] + c[15] + a[16]
c[8] = c[4] + c[6] + c[7] + a[8]
c[12] = c[10] + c[11] + a[12]
...
```

<img width="1742" height="768" alt="QQ_1757750237137" src="https://github.com/user-attachments/assets/65610b1a-f006-4816-9e72-65ce96b1800f" />

<p>看着其实是一棵树</p>

<p>x = ...100...00 (有 k 个 0)，c[x] 为以 x 结尾，长度为 2^k( lowbit(x) ) 的区间的和</p>

<p>c[x] = a[x] + [x - 2^k + 1, x - 1]</p>

<p>x = ...100...00，那么 x-1 = ...011...11。把它分成 k 段，假设 x-1 = ...01111</p>

- (...01110, ...01111]

- (...01100, ...01110]

- (...01000, ...01100]

- (...00000, ...01000]

<p>每减去一个 1 都会对应着一个区间也就是一个儿子，一共要去 k 次，这样就把 k 个儿子找了出来</p>

`c[x] = a[x] + c[x-1] + c[x-1 - lowbit(x-1)] + ...c`

<p><b>关于如何通过子节点找父节点，因为涉及到了修改操作，比如修改了 7，他会影响到哪些 c</b></p>

<p>对于一个父节点 p -> ...100...0，他的子节点形式一定是 x = ...0(1...10...0)拢共 k 位</p>

`p = x + lowbit(x)`

<p>这一操作最多执行 logx 次，也就是说修改操作最多影响到 x 个区间</p>

```
// 修改
for(int i = x; i <= n; i += lowbit(i)) tr[i] += c // n 为区间最大范围
// 查询
for(int i = x; i; i -= lowbit(i)) res += tr[i]; 
```

</br>

## 树状数组的初始化

</br>

<p>讨论提供一个现有数组，如何初始化为树状数组</p>

```
// 朴素方法 O(nlogn)
for(int i = 1; i = n; i ++) add(i, a[i]);
// 类似于堆的建立方式，除非是很卡时 O(n)
for(int x = 1;x <= n;x ++)
    for(int i = x - 1;i >= x - lowbit(x) + 1;i -= lowbit(i))
         tr[x] += tr[i];
```

```
// y总写的，不过是错的，因为tr[i]指的区间是[x-lowbit(x)+ 1,x]而不是前缀和
for(int x = 1;x <= n;x ++)
    for(int i= x - 1;i;i -=lowbit(i))
         tr[x] += tr[i];
```

```
// 还有一种更为简单的建立树状数组的方式且为 O(n)，直接先求前缀和在求区间和
c[x] = s[x] - s[x - lowbit(x)]
```

</br>

# 例题

</br>

## 楼兰图腾

</br>

```
#include <iostream>
#include <cstring>

using namespace std;
typedef long long LL;
const int N = 2e5 + 10;
int a[N], tr[N];
LL Greater[N], lower[N];
int n;

int lowbit(int x)
{
    return x & -x;
}

void add(int x, int c)
{
    for(int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int sum(int x)
{
    int res = 0;
    for(int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> a[i];
    
    for(int i = 1; i <= n; i ++)
    {
        int y = a[i];
        Greater[i] = sum(n) - sum(y);
        lower[i] = sum(y - 1);
        add(y, 1);
    }
    memset(tr, 0, sizeof tr);
    LL res1 = 0, res2 = 0;
    for(int i = n; i; i --)
    {
        int y = a[i];
        res1 += Greater[i] * (LL)(sum(n) - sum(y));
        res2 += lower[i] * (LL)sum(y - 1);
        add(y, 1);
    }
    cout << res1 << " " << res2;
}
```
















</br>

# 扩展

</br>

<p></p>

</br>

## 差分 -- 一个简单的整数问题

</br>

```
a[] => b[]
[L, R] + c
b[L] += c, b[R + 1] -= c
```

<p>在原数组上更新区间值，等价于在差分数组上更新两个点的值。求原数组的一个值等价于求差分数组的前缀和，在用树状数组求前缀和</p>

```
#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int a[N], b[N], tr[N];
int n;

int lowbit(int x)
{
    return x & -x;
}
void add(int x, int c)
{
    for(int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}
long long sum(int x)
{
    long long res = 0;
    for(int i = x; i; i -= lowbit(i)) res += (long long)tr[i];
    return res;
}

int main()
{
    int m;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> a[i];
    for(int i = 1; i <= n; i ++) b[i] = a[i] - a[i - 1];
    
    for(int i = 1; i <= n; i ++) add(i, b[i]);
    
    while(m --)
    {
        char q;
        cin >> q;
        if(q == 'Q')
        {
            int x;
            cin >> x;
            long long res = sum(x);
            cout << res << endl;
        }
        else
        {
            int l, r, c;
            cin >> l >> r >> c;
            add(l, c), add(r + 1, -c);
        }
    }
}
```

</br>

## 差分+公式 -- 一个简单的整数问题2

</br>

<p>更新操作同上，主要是求区间和，转换成求前缀和，只要能求出前缀和就能求出任意区间和</p>

```
a1 + ... + ax
=>
b1
b1 b2
b1 b2 b3
.
.
.
b1 b2 b3 ... bx
```

<p>将其补齐改为：</p>

```
b1 b2 b3 ... bx
---
b1|b2 b3 ... bx
b1 b2|b3 ... bx
b1 b2 b3|... bx
.
.
.
b1 b2 b3 ... bx
```

<p>整体就变成：</p>

`(b1 + b2 + b3 + ... + bx) * (x + 1) - (b1 + 2 * b2 + 3 * b3 + ... + x * bx) // i * bi`

<p>会发现后面也是一个前缀和，bi 的前缀和以及 i*bi 的前缀和。所以操作的时候只需要维护两个前缀和就可以了</p>

</br>

# 例题 -- 谜一样的牛

</br>

<p>这题还可以用平衡树来做</p>

<p>树状数组加上二分查找左边界</p>

```
#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int a[N], n, tr[N], ans[N];

int lowbit(int x)
{
    return x & -x;
}
int sum(int x)
{
    int res = 0;
    for(int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}
void add(int x, int c)
{
    for(int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int main()
{
    cin >> n;
    for(int i = 2; i <= n; i ++) cin >> a[i];
    
    for(int i = 1; i <= n; i ++) add(i, 1);
    
    for(int i = n; i; i --)
    {
        int k = a[i] + 1;
        
        int l = 1, r = n;
        while(l < r)
        {
            int mid = l + r >> 1;
            if(sum(mid) >= k) r = mid;
            else l = mid + 1;
        }
        ans[i] = l;
        add(l, -1);
    }
    for(int i = 1; i <= n; i ++) cout << ans[i] << endl;
}
```









































































































































































































































































































































































































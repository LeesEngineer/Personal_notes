</br>

# SegmentTree

</br>

<p>二叉树除最后一层外为满二叉树，假如用线段树来维护 1～10 这个区间，那么根节点就是 1～10，每个区间会有两个子区间（根据 mid），为 [l, mid] [mid+1, r]。</p>

<p>可以用一维数组来存整棵树，对于长度为 n 的区间，最后一个全满层最坏会有 n 个点，把和前面的加在一起最多会有 2n-1 个点，最后一层最坏情况下为最后一个全满层的两倍，<b>所以最多会有 4n-1 个点</b></p>

<p>有 pushup 和 pushdown 操作，pushup 是由子节点去算父节点的信息，比如想要计算当前区间的总和是多少 sum = l.sum + r.sum。pushdown (也被称为延迟标记) 是把当前父节点的修改信息下传到子节点</p>

<p>最简单的线段树会有四个操作：</p>

- pushup(u)

- build() 将一段区间初始化为线段树

- modify() 修改单点或者区间

- query() 查询某一段区间的信息

<p>build 传入当前区间编号，以及当前区间的左右端点</p>

</br>

## 查询

</br>

<p>修改操作和查询操作是类似的，来看查询操作。比如要找某一个区间内的最大值，线段树内每个点存当前区间的最大值，分为几种情况，[l, r] 表示要查询的区间，[Tl, Tr] 表示树中节点的范围是多少。<b>O(logn)</b></p>

<img width="1016" height="706" alt="QQ_1758026505466" src="https://github.com/user-attachments/assets/27e29191-3e81-4f04-9808-97faee9eee4b" />

1. l <= Tl <= Tr <= r，即完全覆盖了当前区间，直接返回

2. Tl <= l <= Tr <= r，即只有 l 处于节点之内

   - l > mid，只会递归右子树
  
   - l <= mid，虽然递归两棵子树，但是右子节点会在递归后直接返回，不影响复杂度
  
3. l <= Tl <= r <= Tr，即只有 r 处于区间之内，与上面类似

4. Tl <= l <= r <= Tr，即 l 与 r 都位于节点之内

   - l 与 r 都位于 mid 的一侧，只会递归一颗子树。
  
   - l, r 分别位于 mid 两侧，递归左右子树
 
<p>不存在第三种情况，那就是两个区间没有交集，因为达不到</p>

<p>只有 4(2) 才会真正产生对两棵子树的递归，而且该操作至多只会发生一次，复杂度为 O(2logN) = O(logN)</p>

<img width="950" height="676" alt="QQ_1758027695123" src="https://github.com/user-attachments/assets/b6f5afd0-6f64-4516-a81e-487f963979f0" />

</br>

## 单点修改

</br>

<p>不涉及到延迟标记</p>

</br>

### 例题--最大数

</br>

<p>只有之前前一次查询的结果，才能知道当前要插入的数是多少，所以这个问题只能用动态的方法来做</p>

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

struct Node
{
    int l, r;
    int v;
} tr[4 * N];

int pushup(int u)
{
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}
void build(int u, int l, int r)
{
    tr[u].l = l, tr[u].r = r;
    if(l == r) return;
    
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
int query(int u, int l, int r)
{
    if(l <= tr[u].l && r >= tr[u].l)
        return tr[u].v;
    
    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if(l <= mid) v = query(u << 1, l, r);
    if(r > mid) v = max(v, query(u << 1 | 1, l, r));
    
    return v;
}
void modify(int u, int x, int v)
{
    if(tr[u].l == x && tr[u].r == x) tr[u].v = v;
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        
        pushup(u);
    }
}

int main()
{
    long long m, p;
    cin >> m >> p;
    
    build(1, 1, m);
    
    char op;
    long long k;
    long long last = 0;
    long long x = 0;
    while(m --)
    {
        cin >> op >> k;
        if(op == 'A')
        {
            modify(1, ++ x, (k + last) % p);
        }
        else
        {
            last = query(1, x - k + 1, x);
            cout << last << endl;
        }
    }
}
```

</br>

### 例题--你能回答这些问题吗

</br>

<p>难点主要出现在 Node 节点应该存储那些信息，先考虑把答案算出来，在考虑当前信息能否把答案维护出来（tmax，lmax，rmax），在考虑该信息如何被维护是否要加新的信息（sum）</p>

<p>query 也要改一下，涉及新的区间合并</p>

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5e5 + 10;
int n, m;
int w[N];

struct Node
{
    int l, r;
    int sum;
    int lmax;
    int rmax;
    int tmax;
} tr[N * 4];

void pushup(Node &u, Node &l, Node &r)
{
    u.tmax = max(max(l.tmax, r.tmax), l.rmax + r.lmax);
    u.lmax = max(l.lmax, l.sum + r.lmax);
    u.rmax = max(r.rmax, r.sum + l.rmax);
    u.sum = l.sum + r.sum;
}
void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
void build(int u, int l, int r)
{
    if(l == r) tr[u] = {l, r, w[r], w[r], w[r], w[r]};
    else
    {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
Node query(int u, int l, int r)
{
    if(l <= tr[u].l && r >= tr[u].r) return tr[u];
        
    int mid = tr[u].l + tr[u].r >> 1;
    if(r <= mid) return query(u << 1, l, r);         // 完全在左边
    else if(l > mid) return query(u << 1 | 1, l, r); // 完全在右边
    else
    {
        auto left = query(u << 1, l, r);
        auto right = query(u << 1 | 1, l, r);
        Node res;
        pushup(res, left, right);
        return res;
    } // 区间合并
    
}
void modify(int u, int x, int v)
{
    if(tr[u].l == tr[u].r) tr[u] = {x, x, v, v, v, v};
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> w[i];
    build(1, 1, n);
    
    int k, x, y;
    while(m --)
    {
        cin >> k >> x >> y;
        if(k == 1)
        {
            if(x > y) swap(x, y);
            cout << query(1, x, y).tmax << endl;
        }
        else
            modify(1, x, y); 
    }
}
```

</br>

## 例题--区间最大公约数

</br>

<p>平常涉及到区间操作应该使用延迟标记，但这里只涉及到了加上一个数，所以可以用差分来解决</p>

<p>因为修改一个区间不如修改一个数 easy，所以考虑用差分，让线段树维护差分的值</p>
   
<p>且根据碾转相除法，一定有等式</p>

```
gcd(x, y, z) = gcd(x, y-x, z-y)
```

<p>想求 [l, r] 的公因数，可以分开求</p>

`gcd(a[l], gcd(b[l+1], b[r]))`

<p>右边很好维护，很好求</p>

<p>单点查询就相当于求前缀和（可以用树状数组）。把问题转换成了单点修改区间查询</p>

```
#include<bits/stdc++.h>


using namespace std;
typedef long long ll;

const int N = 5e5 + 10;

ll w[N];
struct Node
{
    int l, r;
    ll sum, d;
} tr[N * 4];

ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

void pushup(Node &u, Node &l, Node &r)
{
    u.sum = l.sum + r.sum;
    u.d = gcd(l.d, r.d);
}
void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
void build(int u, int l, int r)
{
    if(l == r)
    {
        ll b = w[l] - w[l - 1];
        tr[u] = {l, r, b, b};
    }
    else
    {
        tr[u].l = l, tr[u].r = r;
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
void modify(int u, int x, ll c)
{
    if(tr[u].l == tr[u].r)
    {
        ll b = tr[u].sum;
        tr[u] = {x, x, b + c, b + c};
    }
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1, x, c);
        else modify(u << 1 | 1, x, c);
        pushup(u);
    }
}
Node query(int u, int l, int r)
{
    if(l <= tr[u].l && r >= tr[u].r) return tr[u];
    
    int mid = tr[u].l + tr[u].r >> 1;
    if(r <= mid) return query(u << 1, l, r);
    else if(l > mid) return query(u << 1 | 1, l, r);
    else
    {
        Node left, right;
        left = query(u << 1, l, r);
        right = query(u << 1 | 1, l, r);
        Node t;
        pushup(t, left, right);
        return t;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> w[i];
    
    build(1, 1, n);
    
    char op;
    int l, r;
    ll d;
    while(m --)
    {
        cin >> op >> l >> r;
        if(op == 'C')
        {
            cin >> d;
            modify(1, l, d);
            if(r + 1 <= n) modify(1, r + 1, -d);
        }
        else
        {
            ll x = query(1, 1, l).sum;
            ll y;
            if (l + 1 <= r) y = query(1,l + 1,r).d;
            else y = 0;
            cout << abs(gcd(x, y)) << endl;
        }
    }
}
```

<p>折磨人，边界问题 debug 了一个点</p>

</br>

# 懒标记 lazy tags

</br>

<p>pushdown 把父节点的修改向下传播到子节点，源于区间查询</p>

<p>单点修改妥妥 logn。如果用区间修改最坏情况下是修改全部区间为 O(4n)=O(n)</p>

<p>懒标记的含义是“给以当前节点为根的子树中的每一个节点加上 add（不包含根节点。也可以加，只要保持前后一致就可以了）”</p>

<p>对于了懒标记，在从上向下递归的过程当中，如果需要递归一个区间的子区间的话，那就清空当前的标记并且传到两个儿子上。这样就可以保证，所有访问到的节点，他上面所有父节点上的标记都被累加到当前节点上。<b>所以查询的时候加上 pushdown 就可以了</b></p>

```
left.add += root.add; left.sum += (left.r - left.l + 1) * root.add;
right.add += root.add; right.sum += (right.r - right.l + 1) * root.add
root.add = 0;
```

<p>懒标记是累加，而不是赋值</p>

<p>修改的时候也要做这样的操作，避免分歧。当前的区间添加的标记不能再表示当前的区间的一个统一的标记了，操作完可能左边加十右边加十五</p>

<p><b>在回溯时 pushup，在分裂传递懒标记时 pushdown</b></p>

</br>

## 例题--一个简单的整数问题

</br>

<p>要维护的信息</p>

```
sum: 如果考虑当前节点及子节点上的所有标记（没有所有祖宗节点上的标记），当前区间和是多少
add: 给当前区间的所有儿子加上 add
```

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
typedef long long ll;

int w[N];
struct Node
{
    int l, r;
    ll sum, add;
} tr[N * 4];

void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}
void pushdown(int u)
{
    auto &root = tr[u], &l = tr[u << 1], &r = tr[u << 1 | 1];
    l.add += root.add, l.sum += (ll) (l.r - l.l + 1) * (root.add);
    r.add += root.add, r.sum += (ll) (r.r - r.l + 1) * (root.add);
    root.add = 0;
}
void build(int u, int l, int r)
{
    if(l == r)
        tr[u] = {l, r, w[l], 0};
    else
    {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
void modify(int u, int l, int r, ll d)
{
    if(l <= tr[u].l && r >= tr[u].r)
    {
        tr[u].add += d;
        tr[u].sum += (ll) (tr[u].r - tr[u].l + 1) * d;
    }
    else
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid) modify(u << 1, l, r, d);
        if(r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}
ll query(int u, int l, int r)
{
    if(l <= tr[u].l && r >= tr[u].r)
        return tr[u].sum;
    
    pushdown(u);    
    int mid = tr[u].l + tr[u].r >> 1;
    ll sum = 0;
    if(l <= mid) sum += query(u << 1, l, r);
    if(r > mid) sum += query(u << 1 | 1, l, r);
    
    return sum;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> w[i];
    
    build(1, 1, n);
    
    char op[2];
    int l, r, d;
    while(m --)
    {
        scanf("%s%d%d", op, &l, &r);
        if(*op == 'Q')
        {
            cout << query(1, l, r) << endl;
        }
        else
        {
            scanf("%d", &d);
            modify(1, l, r, d);
        }
    }
    return 0;
}
```



<p></p>

# 扫描线法

</br>

## 例题--亚特兰蒂斯

</br>

<p>利用扫描线法，</p>

<img width="1112" height="898" alt="QQ_1793187587959" src="https://github.com/user-attachments/assets/66563d24-9256-4011-ab41-3acac32cd0e2" />

<p>可以在纵坐标的方向上做一个线段树，可以把矩形的两个竖着的边做成两个带权值的线段，左边的为 +1，右边的为 -1。然后从左往右去做。每一个线段看作是一个对区间的操作，</p>

<p>求 hi：在出了第一根线（x1）之外，在后面的每一根线上的操作之前去看一下当前 y 轴上有多长的区间上总分值是大于 0 的（一个区间上的值是大于 0 的，就说明他至少被一个矩形覆盖了）。然后求区间总长。</p>

1. 将某一个区间 [l, r] 加 k

2. 求整个区间里面权值大于 0 的区间总长度是多少

线段树维护两个值：cnt -> 当前区间整个被覆盖的次数，len -> 当前线段树节点所对应的区间里面所有权值大于 0 的区间总长度

len 和 sum 是类似的，他不考虑祖先节点（只往下看）cnt 的前提下，cnt > 0 的区间总长度。

<b>线段树里面的节点永远只往下看不往上看</b>

<hr>

<p>涉及到区间修改，可以用懒标记去维护，但比较复杂。所以我们用<b>扫描线一些本身的性质</b>：</p>

1. 永远只考虑根节点的信息 O(1)

因为只考虑根节点，查询的时候不会用到 pushdown 操作，只需要 modify 的 pushup 来维护根结点的 len 就可以了

2. 所有操作均是成对出现的，且先加后减。在区间 [1, 5] + 1，也会在 [1, 5] - 1

故 modify 也不会需要 pushdown

<hr>

扫描线的 cnt 和普通线段树的 lazy 含义不同：

- 普通 lazy：可以下传，表示尚未传递给子节点的修改。

- 扫描线 cnt：记录直接作用于当前节点的完整区间覆盖次数，必须保证同一个矩形的 +1 和 -1 在相同节点抵消。

<p>执行：[1,8]+1   [1,4]+1   [1,8]-1</p>

```
// without pushdown
第一步：
       [1,8] cnt=1
       /          \
 [1,4] cnt=0   [5,8] cnt=0

第二步：
       [1,8] cnt=1
       /          \
 [1,4] cnt=1   [5,8] cnt=0

第三步：
       [1,8] cnt=0
       /          \
 [1,4] cnt=1   [5,8] cnt=0
```

```
// with pushdown
第一步：
       [1,8] cnt=1
       /          \
 [1,4] cnt=0   [5,8] cnt=0

第二步：
       [1,8] cnt=0
       /          \
 [1,4] cnt=2   [5,8] cnt=1

第三步：
       [1,8] cnt=-1
       /          \
 [1,4] cnt=2   [5,8] cnt=1
```

<p>pushup 很简单：cnt 是 0 的时候，就是两个儿子的和，不是 0 的时候就是自身区间长度</p>

<p>这个算法的适用条件很苛刻</p>

<hr>

这道题还需要做一下离散化

<b>利用线段树存的不是点，而是区间。因为维护点没有意义，在扫描线求矩形面积并时，我们维护的不是坐标点本身，而是两个相邻坐标之间的长度。也就是区间的长度。</b>

因为线段树维护的是：[ys[i],ys[i+1]]。所以对于原始范围 [y_1,y_2]，在线段树中对应的区间编号为：[find(y_1),find(y_2)-1]

```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100010;

int n;
struct Segment
{
    double x, y1, y2;
    int k;
    bool operator<(const Segment &t) const
    {
        return x < t.x;
    }
} seg[N << 1];

struct Node
{
    int l, r;
    int cnt;
    double len;
}tr[N << 3];

vector<double> ys;

int find(double y)
{
    return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}

void pushup(int u)
{
    if(tr[u].cnt) tr[u].len = (ys[tr[u].r + 1] - ys[tr[u].l]);
    else if(tr[u].l != tr[u].r)
    {
        tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    }
    else
        tr[u].len = 0;
}

void build(int u, int l, int r)
{
    tr[u] = {l, r, 0, 0};
    if(l != r)
    {
        // pushup
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    }
}

void modify(int u, int l, int r, int k)
{
    if(tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].cnt += k;
        pushup(u);
    }
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid) modify(u << 1, l, r, k);
        if(r > mid) modify(u << 1 | 1, l, r, k);
        pushup(u);
    }
}

int main()
{
    int T = 1;
    while(scanf("%d", &n), n)
    {
        ys.clear();
        for(int i = 0, j = 0; i < n; i ++)
        {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[j ++] = {x1, y1, y2, 1};
            seg[j ++] = {x2, y1, y2, -1};
            ys.push_back(y1), ys.push_back(y2);
        }
        
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        
        build(1, 0, ys.size() - 2);
        
        sort(seg, seg + n * 2);
        
        double res = 0;
        for(int i = 0; i < n * 2; i ++)
        {
            if(i > 0) res += tr[1].len * (seg[i].x - seg[i - 1].x);
            modify(1, find(seg[i].y1), find(seg[i].y2) - 1, seg[i].k);
        }
        
        printf("Test case #%d\n", T ++);
        printf("Total explored area: %.2lf\n\n", res);
    }
    
    return 0;
}
```

<hr>

# 维护序列

<p>懒标记很复杂的一个应用</p>

<p>考虑都需要记录那些信息：L R sum add mul。add 和 mul 有一个优先级的问题，乘法会影响之前的加法，而加法不会影响之前的乘法：</p>

1. 先加再乘比较麻烦：x1 = (x + add1) * mul1

<p>如果继续执行加法：x1 = (x + add1) * mul1 + c 。为了保持先加再乘的形式，必须写成：x2 = (x1 + add2) * mul1。</p>

<p>那么 add2 = add1 + c / mul1。C 不一定被 mul1 整除</p>

2. 所以用先乘再加，方便维护懒标记

```
x' = x * m + a
x'' = (x * m + a) * mul + add
x'' = x * (m * mul) + (a * mul) + add
```

写成一种操作就行：

1. *c：令 d = 0 => x * c + d = x * c

2. +d：令 c = 1 => x * c + d = x + d

```
#include <iostream>
#include <algorithm>
#define int long long

using namespace std;

const int N = 100010;

int n, p, m;
int w[N];
struct Node
{
    int l, r;
    int sum, add, mul;
}tr[N << 2];

void pushup(int u)
{
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % p;
}

void pushdown(int u)
{
    auto &root = tr[u], &l = tr[u << 1], &r = tr[u << 1 | 1];
    l.add = (l.add * root.mul + root.add) % p;
    l.mul *= root.mul;
    l.mul %= p;
    l.sum = l.sum * root.mul + (l.r - l.l + 1) * root.add;
    l.sum %= p;
    
    r.add = (r.add * root.mul + root.add) % p;
    r.mul *= root.mul;
    r.mul %= p;
    r.sum = r.sum * root.mul + (r.r - r.l + 1) * root.add;
    r.sum %= p;
    
    root.mul = 1, root.add = 0;
}

void build(int u, int l, int r)
{
    if(l == r)
        tr[u] = {l, r, w[l] % p, 0, 1};
    else
    {
        tr[u] = {l, r, 0, 0, 1};
        int mid = l + r >> 1;
        if(l <= mid) build(u << 1, l, mid);
        if(r > mid) build(u << 1 | 1, mid + 1, r);
        
        pushup(u);
    }
}

void modify(int u, int l, int r, int add, int mul)
{
    if(l <= tr[u].l && r >= tr[u].r)
    {
        tr[u].sum = (tr[u].sum * mul + (tr[u].r - tr[u].l + 1) * add) % p;
        tr[u].add = (tr[u].add * mul + add) % p;
        tr[u].mul *= mul;
        tr[u].mul %= p;
    }
    else
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid) modify(u << 1, l, r, add, mul);
        if(r > mid) modify(u << 1 | 1, l, r, add, mul);
        pushup(u);
    }
}

int query(int u, int l, int r)
{
    if(l <= tr[u].l && r >= tr[u].r)
        return tr[u].sum;
    
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int sum = 0;
    if(l <= mid) sum += query(u << 1, l, r);
    if(r > mid) sum += query(u << 1 | 1, l, r);
    
    return sum % p;
}

signed main()
{
    cin >> n >> p;
    for(int i = 1; i <= n; i ++) cin >> w[i];
    build(1, 1, n);
    
    cin >> m;
    while(m --)
    {
        int op, l, r, add = 0, mul = 1;
        cin >> op >> l >> r;
        if(op == 1) cin >> mul;
        else if(op == 2) cin >> add;
        
        if(op == 3) cout << query(1, l, r) << endl;
        else modify(1, l, r, add, mul);
    }
    
    return 0;
}
```


















































































































































































































































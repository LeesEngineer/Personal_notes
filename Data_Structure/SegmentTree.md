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

## 例题--_区间最大公约数

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

<p>修改的时候也要做这样的操作，避免分歧</p>

</br>

# 扫描线法

</br>

<p></p>




























































































































































































































































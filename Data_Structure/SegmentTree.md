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

```
void build(int u, int l, int r)
{
    tr[u].l = l, tr[u].r = r;
    if(l == r) return; // 若当前为叶子节点直接返回即可
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
```

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










































































































































































































































































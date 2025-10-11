</br>

# Splay

</br>

<p>先讨论旋转，旋转是在保证中序遍历没有发生变化的情况下调整树的高度</p>

<p>Splay 保证树的高度为 logn 的思路为：每操作（插入或查询）一个节点，均将该节点旋转到树根</p>

<p>注：有严格证明</p>

<p>函数 splay(x, k) 将 x 旋转至 k 下面（splya(x, 0) 表示将 x 旋转至根），分为两大类：左左，右右，左右，右左</p>

```
左左：z -left-> y -left-> x
右旋 y
x <-left- y -right-> z
右旋 x
x -right-> y -right-> z
```

```
左右：z -left-> y -right-> x
左旋 x
z -left-> x -left-> y
右旋 x
y <-left- x -right-> z
```

<img width="1288" height="762" alt="QQ_1759837867366" src="https://github.com/user-attachments/assets/c1d1939b-75ee-40d6-a5f1-390038846f35" />

<p>splay 作为一个核心操作，其他操作都是围绕 splay 来实现的</p>

</br>

## 插入

</br>

<p>最一般的情况：先像二叉搜索树一样找到该插入的位置，再把 x 转到根</p>

<p>第二种情况，将 x（或者一个序列）插入到 y 的后面：</p>

- 将 y 转到根（执行 splay(y, 0)）

- 找到 y 的后继 z，将 z 转到 y 的下面（执行 splay(z, y)）

- 由于在原树中 z 为 y 的后继，所以 z 的左子树为空，要将一个序列插入到 y z 之间，等同于将其归置到 z 的左子树上。所以先把序列构造成二叉树，然后插入到 z 的左子树

<p>同理，如果想要删除 l 到 r 这一段序列也十分简单</p>

- 先找到 l 的前驱 l-1，然后找到 r 的后继 r+1，先将 l-1 转到根节点

- 将 r+1 转到 l-1 下面

- 此时，r+1 的左子树就是 l 到 r 这一段，然后置空

</br>

# splay 维护信息

</br>

<p>找第 k 个数，需要递归维护每一个子树的大小 size</p>

<p>对于 T2437 的翻转问题，需要维护类似于线段树的懒标记 flag，表示整个区间是否需要翻转</p>

<p>pushup：利用两个子树的信息维护根节点的信息</p>

```
root->size = root->left->size + root->right->size + 1
```

<p>pushdown：将懒标记下传，如果想翻转整颗树，则要先交换左右子树，然后再递归翻转左右两颗子树</p>

```
swap(root->left, root->right)
将标记下传，清空当前标记
```

<p>pushup 函数需要放在旋转函数的最后。凡是往下递归的时候都要先 pushdown</p>

<p>区分 spaly 和 二叉搜索树，没有左子树关键字都比当前关键字小，右子树关键字都比当前关键字大的概念。一开始可能有，但是只要翻转后就不保证这样的性质了。因为 splay 只保证中序遍历的顺序是所要求序列的顺序</p>

<p>Splay 的翻转操作是不保序的，但是默认存在一个拓扑序</p>

</br>

# 例题--Splay

</br>

<p>Splay 做的时候习惯加上两个哨兵，因为操作时会用到 l-1 和 r+1，为了防止越界加入 0 和 n+1</p>

<p>加入 0 哨兵后，splay 平衡树的根上会有一个假根（和竞赛树一样）</p>
 
```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

struct Node
{
    int s[2], p, v;
    int size, flag;
    
    void init(int _v, int _p)
    {
        v = _v, p = _p;
        size = 1;
    }
} tr[N];
int root, idx;
int n, m;

void pushup(int x)
{
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}
void pushdown(int x)
{
    if(tr[x].flag)
    {
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[1]].flag ^= 1, tr[tr[x].s[0]].flag ^= 1;
        tr[x].flag = 0;
    }
}
void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int x, int k)
{
    while(tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        
        if(z != k)
            if((tr[z].s[1] == y) ^ (tr[y].s[1] == x))
                rotate(x);
            else
                rotate(y);
        rotate(x);
    }
    if(!k) root = x;
}
void insert(int v)
{
    int u = root, p = 0;
    
    while(u) p = u, u = tr[u].s[v > tr[u].v];
    
    u = ++idx;
    tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
}
int get_k1(int u, int k)
{  
    pushdown(u);
    if(tr[tr[u].s[0]].size >= k) return get_k1(tr[u].s[0], k);
    else if(tr[tr[u].s[0]].size + 1 == k) return u;
    else return get_k1(tr[u].s[1], k - tr[tr[u].s[0]].size - 1);
}
int get_k2(int k)
{
    int u = root;
    while(true)
    {
        pushdown(u);
        if(tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if(tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}
void output(int u)
{
    pushdown(u);
    if(tr[u].s[0]) output(tr[u].s[0]);
    if(tr[u].v >= 1 && tr[u].v <= n) printf("%d ", tr[u].v);
    if(tr[u].s[1]) output(tr[u].s[1]);
}
int main()
{
    scanf("%d%d", &n, &m);
    
    for(int i = 0; i <= n + 1; i ++) insert(i);
    
    int l, r;
    while(m --)
    {
        scanf("%d%d", &l , &r);
        
        l = get_k1(root, l), r = get_k1(root, r + 2);
        splay(l, 0), splay(r, l);
        tr[tr[r].s[0]].flag ^= 1;
    }
    output(root);
}
```

<p>容易产生误区的地方是 get_k 是找位置为 k 的值，而不是第 k 大的值</p>

```
void insert(int v)
{
    int u = root, p = 0;
    
    while(u) p = u, u = tr[u].s[v > tr[u].v];
    
    u = ++idx;
    tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    pushup(p);
    splay(u, 0);
}
```

<p>insert 函数不需要加上 pushup，因为这不是向上递归的计算 size，会导致后续的 size 计算错误</p>

```
void insert(int v)
{
    int u = root, p = 0;
    
    while(u) p = u, u = tr[u].s[v > tr[u].v];
    
    u = ++idx;
    tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    pushup(p);
    splay(u, 0);
}
```

<p>否则会让 get_k 函数进入错误的分支，get_k1 爆栈，让 get_k2 超时</p>

</br>

# 例题--郁闷的出纳员

</br>

<p>没用到 pushdown 操作</p>

<P>1. 在 get 函数这里卡了好久。2. 忘了删除后的 pushup 操作</P>

```
#include <iostream>

using namespace std;

const int N = 1e5 + 10, INF = 1e9;

struct Node
{
    int s[2], p, v;
    int size;
    
    void init(int _v, int _p)
    {
        v = _v, p = _p;
        size = 1;
    }
} tr[N];
int root, idx;
int delta, tot;

void pushup(int x)
{
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}
void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = (tr[y].s[1] == x);
    
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int x, int k)
{
    while(tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if(z != k)
            if((tr[z].s[1] == y) ^ (tr[y].s[1] == x))
                rotate(x);
            else
                rotate(y);
        rotate(x);
    }
    if(!k) root = x;
}
int insert(int v)
{
    int u = root, p = 0;
    
    while(u) p = u, u = tr[u].s[v > tr[u].v]; // 这里用了 >=
    
    u = ++ idx;
    tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
    
    return u;
}
int get_k(int u, int k)
{
    if(tr[tr[u].s[0]].size >= k) return get_k(tr[u].s[0], k);
    else if(tr[tr[u].s[0]].size + 1 == k) return u;
    else return get_k(tr[u].s[1], k - tr[tr[u].s[0]].size - 1);
}
int get(int k)
{
    int res, u = root;
    while(u)
    {
        if(tr[u].v < k) u = tr[u].s[1];
        else res = u, u = tr[u].s[0];
    }
    return res;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    int L = insert(-INF), R = insert(INF);
    
    char op[2];
    int k;
    while(n --)
    {
        scanf("%s%d", op, &k);
        
        if(*op == 'I')
        {
            if(k >= m) insert(k - delta), tot ++;
        }
        else if(*op == 'A')
        {
            delta += k;
        }
        else if(*op == 'S')
        {
            delta -= k;
            R = get(m - delta);
            splay(R, 0), splay(L, R);
            tr[L].s[1] = 0;
            pushup(L), pushup(R); // 别忘了
        }
        else
        {
            if(tr[root].size - 2 < k) printf("-1\n");
            else printf("%d\n", tr[get_k(root, tr[root].size - k)].v + delta);
        }
    }
    printf("%d\n", tot - (tr[root].size - 2));
}
```






























































































































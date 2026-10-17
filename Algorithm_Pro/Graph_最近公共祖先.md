# 向上标记法

从一个点向上走，路径上的点都标记上。另一个点也向上走，走到的第一个被标记的点就是最近公共祖先

为 O(n)，但不常用

# 倍增法

先去预处理每个点向上走 2^j 步的父亲是谁：fa[i][j] 表示从 i 开始，向上走 2^j 步所能到的节点。0 <= j << logn。O(mlogn)

可以用递推的方式来预处理 fa[i][j]

`f[i][j] = f[ f[i][j - 1] ][j - 1]`

既可以用 DFS 也可以用 BFS

depth[i] 表示深度

哨兵：如果跳过根结点，规定 fa[i][j] 等于0，dist[0]=0

<hr>

步骤：

1. 基于二进制拼凑思想，先将 x 跳至和 y 同一层。

2. 若不是同一个点，让两个点同时向上跳，直到跳至最近公共祖先的下一层

```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 40010, M = N << 1;

int n, m;
int h[N], e[M], ne[M], idx;
int depth[N], fa[N][16];
int q[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void bfs(int root)
{
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[root] = 1;
    int hh = 0, tt = 0;
    q[0] = root;
    
    while(hh <= tt)
    {
        int t = q[hh ++];
        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(depth[j] > depth[t] + 1)
            {
                depth[j] = depth[t] + 1;
                q[++ tt] = j;
                fa[j][0] = t;
                for(int k = 1; k < 16; k ++)
                    fa[j][k] = fa[ fa[j][k - 1] ][k - 1];
            }
        }
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);
    for(int k = 15; k >= 0; k --) // 二进制拼凑
        if(depth[fa[a][k]] >= depth[b]) // 哨兵
            a = fa[a][k];
    
    if(a == b) return a;
    for(int k = 15; k >= 0; k --)
        if(fa[a][k] != fa[b][k])
        {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0];
}

int main()
{
    scanf("%d", &n);
    int root = 0;
    memset(h, -1, sizeof h);
    
    for(int i = 0; i < n; i ++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if(b == -1) root = a;
        else add(a, b), add(b, a);
    }
    
    bfs(root);
    
    scanf("%d", &m);
    while(m --)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        int p = lca(a, b);
        if(p == a) puts("1");
        else if(p == b) puts("2");
        else puts("0");
    }
    
    return 0;
}
```

# Tarjan

离线求LCA，O(n + m)。非常优美的一个做法，本质是对向上标记法的优化





































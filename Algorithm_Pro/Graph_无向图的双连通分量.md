分为边双连通分量 (e-dcc) 和点双连通分量 (v-dcc)

研究 e-dcc 要引入桥的概念

<img width="540" height="284" alt="QQ_1792939770059" src="https://github.com/user-attachments/assets/71d083bc-44d7-4623-a4c4-f190006948c3" />

e-dcc 是极大的不含有桥的连通区域

1. 不管删掉哪条边都是联通的

2. <b>在 e-dcc 中任意两点之间一定包含两条不相交的路径（没有公共边，可以在点上相交，不能在边上相交）</b>

<hr>

v-dcc 引入割点，类比桥。v-dcc 是极大的不包含割点的连通块

二者完全没有任何关系

# tarjan 算法

## 边双连通分量

也是引入时间戳的概念，dfn[u] 为第一次访问的时间点，low[u] 表示以 x 为根的子树往下走的话所能到达的最早的一个点

无向图不存在横叉边的概念

<hr>

1. 如何找到所有桥：当前点为 x，往下走走到 y。如何判断当前的边是否为一个桥，就是看 y 能不能走到 x 或者 x 的祖先节点，如果能就说明 x 在一个环里面，那就不是桥。如果 y 最早就只能走到 y 自己，那就是桥。

桥 <=> dfn[x] < low[y]

2. 如何找到所有边双连通分量：

   - 简单做法把所有桥全部删掉
  
   - 类似于有向图，用 stack 来找当前 e-dcc 中的所有点。dfn[x] == low[x] 说明从 x 出发走不到 x 的上面，因此从 x 的父节点到 x 的这条边就是一个桥

# 冗余路径

无向图的连通分量都比较难

给定一个无向连通图，最少加几条边可以把它变成一个边双连通分量

求完所有 e-dcc 后，可以把所有 e-dcc 缩点，<b>缩完后所有边就都是桥了，会变成一棵树</b>。其内所有度数为 1 的点都要加一条边

至少要加 (cnt + 1)/2 个边。

<img width="416" height="420" alt="QQ_1793009228486" src="https://github.com/user-attachments/assets/d8f3f461-4a05-446c-870e-940828e9c692" />



```
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N  = 5010, M = 20010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
int id[N], dcc_cnt;
bool is_bridge[M];
int d[N];

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[++ top] = u;
    
    for(int i = h[u]; i != -1;i = ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if(dfn[u] < low[j])
                is_bridge[i] = is_bridge[i ^ 1] = true;
        }
        else if(i != (from ^ 1))
            low[u] = min(low[u], dfn[j]);
    }
    
    if(dfn[u] == low[u])
    {
        int y;
        ++ dcc_cnt;
        do
        {
            y = stk[top --];
            id[y] = dcc_cnt;
        } while(y != u);
    }
}

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while(m --)
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    
    tarjan(1, -1);
    
    for(int i = 0; i < idx; i ++)
        if(is_bridge[i])
            d[id[e[i]]] ++;
            
    int cnt = 0;
    for(int i = 1; i <= dcc_cnt; i ++)
        if(d[i] == 1)
            cnt ++;
    
    cout << (cnt + 1) / 2;
    
    return 0;
}
```

证明一下：在 e-dcc 中任意两点之间一定包含两条不相交的路径（没有公共边，可以在点上相交，不能在边上相交）

1. 充分性：假设任意两点之间一定包含两条不相交的路径，如果不是双连通分量，就意味着图中至少有一个桥，去掉后左右两点就不连通了。矛盾

2. 必要性：不想证

<hr>

对有向图来说，最少加 max{p, q} 个边将其变为强连通分量。p 和 q 分别表示出度为 1 的点和入度为 0 的点。

对无向图来说，最少加 (cnt + 1)/2 个边将其变为边双连通分量。

<hr>

# v-dcc

当前有 x 到 y，判断 x 是否为割点，若有 low[y] >= dfn[x] 则分为两种情况：

1. 如果 x 不是根节点，那么 x 就是割点

2. 如果 x 是根节点，至少要有有第二个子节点 y_i，满足 low[y_i] >= dfn[x]。才为割点

<hr>

## 电力

1. 统计连通块个数

2. 枚举从哪个连通块删，删除哪个点

当 dfn[x] <= low[y] 时，把 x 删掉子树会变多，特判一下是否为根节点。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010, M = 30010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int root, ans; 

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    
    int cnt = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if(low[j] >= dfn[u]) cnt ++;
        }
        else
            low[u] = min(low[u], dfn[j]);
    }
    if(u != root && cnt) cnt ++;
    
    ans = max(ans, cnt);
}

int main()
{
    while(scanf("%d%d", &n, &m), n || m)
    {
        memset(dfn, 0, sizeof dfn);
        memset(h, -1, sizeof h);
        idx = 0, timestamp = 0;
        
        while(m --)
        {
            int a, b;
            cin >> a >> b;
            add(a, b), add(b, a);
        }
        
        ans = 0;
        int cnt = 0;
        for(root = 0; root < n; root ++)
            if(!dfn[root])
            {
                cnt ++;
                tarjan(root);
            }
            
        cout << ans + cnt - 1 << endl;
    }
}
```



















































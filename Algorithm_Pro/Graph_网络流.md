# 最大流问题

<p>“把三个物品从 u 运送到 v，又把五个物品从 v 运送到 u”没什么意义，因为他等价于把两个物品从 v 运送到 u。这样，就可以定义 f(u, v) 和 f(v, u) 最多只有一个正数。并且 f(u, v) == f(v, u) </p>

<p>在最大流问题中，c 和 f 满足三个性质：</p>

- 容量限制：f(u, v) <= c(u, v)

- 斜对称性：f(u, v) == -f(v, u)

- 流量平衡：入等于出

# 增广路算法

<p>算法思路很简单：从零流（所有边的流量全为零）开始不断增加流量，保持每次增加流量后都满足上面三个性质</p>

![9AB85842-2397-4E39-AFE8-410D8B3666A9_1_201_a](https://github.com/user-attachments/assets/cc26d6c7-bb02-4d73-abdd-92ec5c3baeaf)

![3544E81E-E092-4BB1-A460-6633EE5E44BA_1_201_a](https://github.com/user-attachments/assets/faf43f52-85d7-48b8-90c6-f23d050721c6)

<p>算法基于这样一个事实：残量网络中任何一条从 s 到 t 的有向道路都对应一条原图中的增广路，求出该道路中所有残量的最小值 d，把对应的所有边上的流量增加 d 即可，这个过程称为增广。若增广前满足三条性质，则增广后也满足</p>

<p>只要残量网络中存在增广路，流量就可以增大----<b>增广路定理</b>。当且仅当残量网络中不存在 s-t 有向路（增广路）时，此时的流就是从 s 到 t 的最大流</p>

<p>“找任意路径”最简单的无疑是用 DFS，但很容易找出让他很慢的例子。一个稍好的方法是用 BFS，足以应对数据不刁钻的网络流题目，即<b> Edmonds-Karp 算法</b></p>

```
struct Edge
{
    int from, to, cap, flow;
    
    Edge(int u, int v, int c, int f): from(u), to(v), cap(c), flow(f) {}
};

struct EdmondsKarp
{
    int n, m;
    
    vector<Edge> edges;
    vector<int> G[maxn];
    int a[maxn];
    int p[maxn];
    
    void init(int n)
    {
        for(int i = 0; i < n; i ++) G[i].clear();
        edges.clear();
    }
    
    void AddEdge(int from, int to, int cap)
    {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1)
    }
    
    int Maxflow(int s, int t)
    {
        int flow = 0;
        for(;;)
        {
            memset(a, 0, sizeof a);
            queue<int> q;
            q.push(s);
            a[s] = INF;
            while(!q.empty())
            {
                int x = q.front();
                q.pop();
                for(int i = 0; i < G[x].size(); i ++)
                {
                    Edge &e = edges[G[x][i]];
                    if(!a[e.to] && e.cap > e.flow)  // 该点未访问且残余容量 > 0
                    {
                        p[e.to] = G[x][i];
                        a[e.to] = min(a[x], e.cap - e.flow)
                        q.push(e.to);
                    }
                }
                if(a[t]) break;
                
            }
            if(!a[t]) break;
            for(int u = t; u != s; u = edges[p[u]].from)
            {
                edges[p[u]].flow += a[t];
                edges[p[u] ^ 1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
};
```

# 最小割最大流定理

<p>一个与最大流关系密切的问题：最小割</p>

<p>把所有顶点分成两个集合 S 和 T = V - S，s 在 S 中，t 在 T 中。(S, T) 称为一个 s-t 切割</p>

<p>容量定义为</p>

$c(S,T) = \sum_{u \in S,v \in T}c(u, v)$

<p>从 s 到 t 的净流量为</p>

$|f| = f(S, T) = \sum_{u \in S,v \in T}f(u, v)$

<p>如果残存网络中不存在增广路，那么在残存网络中 s 和 t 不连通：当 BFS 没有找到任何 s-t 道路是，把以标号节点集合看成 S，在残量网络中 S 和 T 分离，因此在原图中 跨越 S 和 T 的图满载（并且该边不会存在与残量网络中）<b>且没有从 T 回到 S 的流量</b></p>

<p>同时证明了增广路定理和最小割最大流定理：在增广路算法结束时，f 是 s-t 最大流，(S, T) 是图的 s-t 最小割</p>

<p></p>

# 最小费用最大流问题

<p>在最小费用问题里面，<b>平行边变得有意义了，</b>可能会有两条从 u 到 v 的弧，费用不一样。由于费用的出现，无法合并这两条弧</p>

<p>如果边 (u, v) 和 (v, u) 都存在，且费用都是负数，则“同时从 u 流向 v 和从 v 流向 u”是个不错的主意</p>

<p>为了允许反向增广，规定 cap[v][u] = 0 并且 cost[v][u] = -cost[u][v]，表示沿着 (u, v) 的相反方向增广时，费用减少 cost[u][v]</p>

<p><b>MCMF 和 Edmonds-Karp 算法类似，但每次用 Bellman-Ford 算法而非 BFS 找增广路。</b></p>

<p><b>只要初始流是该流量下的最小费用可行流，每次增广后的新流都是新流量下的最小费用流</b>，即如果一开始的流量是当前流量下的最小费用可行流（即在满足流量约束的情况下，费用最小）。每次找到增广路后，使流量增加。增广后的新流，仍然是新的总流量下的最小费用流。</p>

```
//费用可正可负，为减少溢出的可能性，用 long long 来存 cost
struct Edge
{
    int from, to, cap, flow, cost;
};

struct MCMF
{
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    int q[maxn]; // 是否在队列中
    int d[maxn]; // Bellman-Ford
    int a[maxn]; //起点到 i 的可改进量
    int p[maxn]; //路上 p 的入弧编号

    void init(int n)
    {
        this -> n = n;
        for(int i = 0; i < n; i ++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap, int cost)
    {
        edges.push_back(Edge(from, to, cap, 0, cost));
        edges.push_back(Edge(to, from, 0, 0, -cost));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool BellmanFord(int s, int t, int &flow, long long &cost)
    {
        for(int i = 0; i < n;i ++) d[i] = INF;
        memset(q, 0, sizeof q);
        d[s] = 0, q[s] = 1, p[s] = 0, a[s] = INF;

        queue<int> Q;
        Q.push(s);
        while(!Q.empty())
        {
            int u = Q.front(); Q.pop();
            q[u] = 0;
            for(int i = 0; i < G[u].size(); i ++)
            {
                Edge &e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost)
                {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!q[e.to]) {Q.push(e.to); q[e.to] = 1;}
                }
            }
        }
        if(d[t] == INF) return false;
        flow += a[t];
        cost += (long long)d[t] * (long long) a[t];
        for(int u = t; u != s; u = edges[p[u]].from)
        {
            edges[p[u]].flow += a[t];
            edges[p[u] ^ 1].flow -= a[t];
        }
        return true;
    }
    
    //需要保证初始网络中没有负权回路
    int MincostMaxflow(int s, int t, long long &cost)
    {
        int flow = 0; cost = 0;
        while(BellmanFord(s, t, flow, cost));
        return flow;
    }
};
```

# 应用举例

<p>虽然介绍了 Edmonds-Karp 算法，但在实践中通常使用效率更高的 Dinic 算法或者 ISAP 算法。</p>

<p>另一个方面最小费用流也有更快的算法，但一般都只是使用上述方法，因为快速算法（如网络单纯型法）大都很复杂</p>

## 二分图匹配

<p>网络流的一个经典应用是二分图匹配</p>

<p>换句话说二分图就是可以把节点进行二染色，使得同色节点不相邻。可以证明：一个图是二分图，当且仅当它不含长度为奇数的圈</p>

<p>常见的二分图匹配问题有两种：</p>

<p>第一种针对无权图：需要求出包含边数最多的匹配（二分图的最大基数匹配）</p>

<p>这个问题可以这样求解：增加一个源点 s 和一个汇点 t ，从 s 到所有 X 结点连接一条容量为 1 的弧，再从 Y 结点到 t 各连一条容量为 1 的弧，最后把每一条边变成从 X 指向 Y 的有向弧，容量为 1。只要求出从 s 到 t 的最大流，则原图中所有流量为 1 的弧对应了最大基数匹配</p>

![IMG_0223](https://github.com/user-attachments/assets/08440dba-35df-401d-88e3-89ebf89bc670)

<p>第二种是带权图，需要求出边权之和尽量大的匹配。有的题目要求这个匹配本身是完美匹配（即每个点都被匹配到），而有的题并不对匹配边数作出要求，只要边权和最大就可以了</p>

<p>先来看最大权完美匹配</p>

<p>和最大基数匹配类似，只是<b>原图中所有边的费用为权值的相反数，然后其他边的费用为 0，然后求一个 s 到 t 的最小费用最大流即可。</b>如果从 s 出发的所有弧并不是全部满载，则完美匹配不存在，问题无解</p>

<p>用这种方法也可以求解第二种情况，只需要在求解 s-t 最小费用流的过程中记录下流量为 0，1，2，3，... 时的最小费用流，然后加以比较</p>













































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































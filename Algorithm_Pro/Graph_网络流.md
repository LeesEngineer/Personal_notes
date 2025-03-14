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

# 最小隔最大流定理

<p>一个与最大流关系密切的问题：最小割</p>

<p>把所有顶点分成两个集合 S 和 T = V - S，s 在 S 中，t 在 T 中。(S, T) 称为一个 s-t 切割</p>

<p>容量定义为</p>

$c(S,T) = \sum_{u \in S,v \in T}c(u, v)$

<p>从 s 到 t 的净流量为</p>

$|f| = f(S, T) = \sum_{u \in S,v \in T}f(u, v)$

<p>如果残存网络中不存在增广路，那么在残存网络中 s 和 t 不连通：当 BFS 没有找到任何 s-t 道路是，把以标号节点集合看成 S，在残量网络中 S 和 T 分离，因此在原图中 跨越 S 和 T 的图满载（并且该边不会存在与残量网络中）<b>且没有从 T 回到 S 的流量</b></p>

<p>同时证明了增广路定理和最小割最大流定理：在增广路算法结束时，f 是 s-t 最大流，(S, T) 是图的 s-t 最小割</p>

<p></p>
























































































































































































































































































































































































































































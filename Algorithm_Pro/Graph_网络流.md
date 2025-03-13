# 最大流问题

<p>“把三个物品从 u 运送到 v，又把五个物品从 v 运送到 u”没什么意义，因为他等价于把两个物品从 v 运送到 u。这样，就可以定义 f(u, v) 和 f(v, u) 最多只有一个正数。并且 f(u, v) == f(v, u) </p>

<p>在最大流问题中，c 和 f 满足三个性质：</p>

- 容量限制：f(u, v) <= c(u, v)

- 斜对称性：f(u, v) == -f(v, u)

- 流量平衡：入等于出

## 增广路算法

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



























































































































































































































































































































































































































































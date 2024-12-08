</br>

# DFS

</br>

<p>会尽可能的往深处搜索，遇到叶子的时候会<b>回溯</b></p>

<p>使用的数据结构是栈</p>

<p>空间从使用的空间上来看，DFS 向下搜的时候只需要记录路径上的这些点就够了，因此使用的空间是和高度成正比的，为 O(h)</p>

<p>DFS 中有两个很重要的概念：回溯，剪枝。</p>

<p>虽然 DFS 没有一个常用的框架，但 BFS 有一个常用的框架。</p>

</br>

## 全排列

</br>

<p>找到一个顺序能把我们的方案全部遍历一遍</p>

<p>填空位，挨个填空位，不能和前面出现一样，无可填的时候就会回溯</p>

<p>对应搜索的顺序形成一棵树</p>

<b>回溯也代表着恢复现场，递归到下一层时的状态是怎样的，回溯后状态也要怎样，对应的这里的状态数组。“出去的时候怎么样，回来的时候也要怎么样”</b>

```
#include <iostream>
#include <iostream>

using namespace std;

const int N = 10;

int n;
int path[N];
bool st[N]; //标记该点是否用过

void dfs(int u)
{
  if (u == n)
  {
    for(int i = 0; i < n; i ++) printf("%d ", path[i]);
    puts(""); //presentation error
    return;
  }

  for(int i = 1; i <= n; i++)
    if(!st[i])
    {
      path[u] = i;
      st[i] = true;
      dfs(u + 1);
      st[i] = false;
    }
}

int main()
{
  cin >> n;
  dfs(0);
  return 0;
}
```

<p>除了开 bool 数组以外也可以用位运算优</p>

</br>

## N皇后

</br>

<p>有很多种搜索顺序</p>

<p>第一种搜索树和全排列的搜索树是一样的，一定要注意剪枝（提前判断当前这个方案一定是不合法的，下面的那个子树就没有必要继续往下搜了，直接回溯）</p>

```
#include <iostream>

using namespace std;

const int N = 20;

int n;
char g[N][N];
bool col[N], dg[N], udg[N]; //列和正负对角线

void dfs(int u)
{
    if(u == n)
    {
        for(int i = 0; i < n; i++) puts(g[i]);
        puts("");
        return;
    }
    
    for(int i = 0; i < n; i++)
        if(!col[i] && !dg[u + i] && !udg[n - u + i])
        {
            g[u][i] = 'Q';
            col[i] = dg[u + i] = udg[n - u + i] = true; //反对角线和正对角线，截距。
            dfs(u + 1);
            col[i] = dg[u + i] = udg[n - u + i] = false;
            g[u][i] = '.';
        }
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            g[i][j] = '.';
            
    dfs(0);
    
    return 0;
}
```

<p>可以以一种更原始的方式来枚举八皇后问题</p>

<p>比如枚举第一个格子，放产生一个分支，不放产生一个分支</p>

</br>

# BFS

</br>

<p>使用的数据结构是队列</p>

<p>向下搜索的时候，需要记录一层内所有节点，因此是指数级的空间，为 O(2^h)</p>

<p>因为搜索时是一层一层往外<b>扩展</b>的，所以他有一个最短路的概念，即如果<b>每一条边权重都是 1 的时候(权重必须一样)，BFS 第一次搜索到的该点时一定是按照最近的路径</b></p>

</br>

## 走迷宫

</br>

```
5 5
0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
```

<p>用向量来表示移动，(-1, 0) 表示向上，(0, 1) 表示向右</p>

```
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int N = 110;

int n, m;
int g[N][N];
int d[N][N];
PII q[N * N];
//PII Prev[N][N];

int bfs()
{
    int hh = 0, tt = 0;
    q[0] = {0, 0};
    
    memset(d, -1, sizeof d);
    d[0][0] = 0;
    
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    
    while(hh <= tt)
    {
        auto t = q[hh ++];
        
        for(int i = 0; i < 4; i ++)
        {
            int x = t.first + dx[i], y = t.second + dy[i];
            if(x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0 && d[x][y] == -1)
            {
                d[x][y] = d[t.first][t.second] + 1;
                //Prev[x][y] = t;
                q[ ++ tt] = {x, y};
            }
        }
    }

    /*
    int x = n - 1, y = m - 1;
    while(x || y)
    {
        cout << x << "  " << y << endl;
        auto t = Prev[x][y];
        x = t.first, y = t.second;
    }

    */

    return d[n - 1][m - 1];
}

int main()
{
    cin >> n >> m;
    
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
            cin >> g[i][j];
    
    cout << bfs() << endl;

    return 0;
}
```

<p>要是想记录路径的话，只需要记录一个点是从哪个点走过来的就行了，可以开一个额外的数组</p>

</br>

# 树和图的遍历 

</br>

<p>首先树是一种无环连通图，所以只讲图</p>

<p>图分有向图和无向图，可以把无向图看成一种有向图，所以只看有向图</p>

<p>图的存储</p>

1. 邻接矩阵；g[a][b] 就存储 a 到 b 这条边的有效信息，有权重的话就是权重，无法存储重边，用的比较少，比较浪费空间，适合存储稠密图，稀疏图不适合
2. 邻接表；如果我们有 n 个点的话，就在每一个节点上开了一个单链表，每个单链表就是存储这个点可以走到哪个点，在单链表中插入一般是在头的位置插，原为 h[2] -> 1 -> 4 -> null，插入 2 -> 3； h[2] -> 3 -> 1 -> 4 -> null

<p>无论是深度优先还是宽度优先，时间复杂度都是 O(n+m) 与点和边城线性关系</p>

</br>

## 邻接表的存储

</br>

```
const int N = 100010, M = N * 2; //对于树来说 M = N * 2

int h[N];
int e[M];
int ne[M];
int idx;
```

</br>

## 头插法

</br>

```
void add(int a, int b) //头插法
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

int main()
{
    memset(h, -1, sizeof h);
}
```

## 深度优先遍历

</br>

```
bool st[N];//每个点只能遍历一次

void dfs(int u)
{
    st[u] = true;

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!st[j]) dfs(j);
    }
}
```

</br>

### 树的重心

</br>

<p>问题在于如何快速的求每一个连通块的点数，可以用深度优先遍历，<b>因为深度优先遍历有一个很好的特点，可以算出每一个子树的大小</b>，在树的深度优先遍历当中可以求出每个子树的点的数量</p>

```
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010, M = N * 2; //对于树来说 M = N * 2

int n;
int h[N];
int e[M];
int ne[M];
int idx;

int ans = N;

void add(int a, int b) //头插法
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

bool st[N];//每个点只能遍历一次

//返回以u为根的子树的大小
int dfs(int u)
{
    st[u] = true;

    int sum = 1, res = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!st[j]) 
        {
            int s = dfs(j);
            res = max(res, s);
            sum += s;  
        }
    }
    
    res = max(res, n - sum); // n - sum 为总结点数减去以 u 为根的树的节点数
    
    ans = min(ans, res);
    
    return sum;
}

int main()
{
    memset(h, -1, sizeof h);
    
    cin >> n;
    
    for(int i = 0; i < n - 1; i ++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    dfs(1); //假设从1开始搜
    
    cout << ans << endl;
}
```

</br>

## 宽度优先遍历

</br>

```
//伪代码
queue <- 初始化

while queue不空
  t <- 队头
  拓展 t 所有邻点 a
  if(为遍历) a
    queue <- a
    d[a] = d[t] + 1
```

</br>

### 图中点的层次

</br>

```
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], idx;
int d[N], q[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


int bfs()
{
    int hh = 0, tt = 0;
    q[0] = 1;
    
    memset(d, -1, sizeof d);
    
    d[1] = 0;
    
    while(hh <= tt) //while 队列不空
    {
        int t = q[hh ++ ];
        
        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(d[j] == -1)
            {
                d[j] = d[t] + 1;
                q[ ++ tt] = j; //数组模拟队列
            }
        }
    }
    return d[n];
}

int main()
{
    cin >> n >> m;
    
    memset(h, -1, sizeof h);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    
    cout << bfs() << endl;
    
    return 0;
}
```

</br>

# 拓扑序

</br>

<p>有向图才会有拓扑序列，无向图没有</p>

```
1 -> 2
1 -> 3
2 -> 3
```

<p>那么 1 2 3 就是一个拓扑序列，对于每一条边都是起点在终点的前面。或者说把一个图按照拓扑序排好之后，所有边都是从前指向后的</p>

<p>如果把 1 —> 3 换成 3 -> 1 ，那就不会有拓扑序，因为存在一个环，<b>只要有环，就一定不存在拓扑序，因为总会有一条边不是从起点指向终点</b></p>

<b>可以证明一个有向无环的图一定存在一个拓扑序，故有向无环图也被称为拓扑图</b>

<p>有向图每个点有两个度，一个是入度，一个是出度</p>

</br>

## 求拓扑序列

</br>

<p>当前入度为 0 的点都是可以作为起点的，因为不会又任何一点要求在其前面</p>

<p>因此第一步是让所有入度为零的点入 queue</p>

```
queue <- 所有入度为 0 的点

while queue 不空
  t <- 队头
  枚举 t 的所有出边 t -> j
    删掉 t -> j, d[j]-- //d[j]表示j的入度
    if d[j] == 0
      queue <- j
```

<p>删掉 t -> j：因为队头出来以后意味着把 t 放在拓扑序列最前面了，那么 t 指向的点一定是在 t 后面了，<b>即当前 t 已经放在最前面了，所以后面没有放的点一定是在 t 的后面</b>，那么 t —> j 所有边从前指向后这个性质一定是满足的，所以可以把这条边删掉，而删掉该边唯一的影响就是让 j 的入度减 1 ，如果说 d[j] == 0 了，那么就说明<b> j 前面所有的点都已经排好序放好了</b>，此时的 j 就没有任何限制了，让 j 入队</p>

<p>如果存在一个环，那么环上的点一定不会入队的，因为找不到任何一个突破口（入度为 0 的点），反之如果没有环的话，一定可以突破掉。一个有向无环图一定至少存在一个入度为 0 的点（反证法），那么就可以以该点为突破口，把该点和关联的点全部删掉，之后还是有向无环图</p>

<p>把图的点各个击破，各个击破的序列就是一个拓扑序列</p>

</br>

## 有向图的拓扑序列

</br>

<p>队列中的次序就是拓扑序</p>

```
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], idx;
int q[N], d[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool topsort()
{
    int hh = 0, tt = -1;
    
    for(int i = 1; i <= n; i++)
        if(!d[i])
            q[ ++ tt] = i;
    
    while(hh <= tt)
    {
        int t = q[hh ++ ];
        
        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            d[j] -- ;
            if(d[j] == 0) q[ ++ tt] = j;
        }
    }
    
    return tt == n - 1; //true说明所有点都入队列了，说明是一个有向无环图
}

int main()
{
    cin >> n >> m;
    
    memset(h, -1, sizeof h);
    
    for(int i = 0; i < m; i ++ )
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
        d[b] ++ ;
    }
    
    if(topsort())
    {
        for(int i = 0; i < n; i ++ ) printf("%d ", q[i]);
        puts("");
         
    }
    else puts("-1");
    
    return 0;
}
```

</br>

# 最短路

</br>

<p>常见的最短路问题可以分为两大类：单源最短路，多源汇最短路</p>

<p>图论侧重于抽象和实现而不是原理，故最短路的难点在于建图，如何把原问题抽形成最短路问题，如何定义点和边，来套用模板。</p>

- Dijkstra 算法基于tanxin

- Floyd 算法基于动态规划

- Bellman-Ford 算法基于离散数学的知识

<p>在最短路问题中有重边和自环：如果所有边都是正的，那么自环就不会出现在最短路里面；若有重边只需保留长度最短的点即可</p>

</br>

## 单源最短路：求一个点到其他所有点的最短距离

</br>

<p>可细分为<b>所有边权都是正数</b>和<b>存在负权边</b>两种情况</p>

</br>

### 所有权边都是正数

</br>

<p>有两个很经典的算法，其实是一个算法（但不同的场景适合用不同的实现方式）</p>

</br>

#### 朴素Dijkstra算法

</br>

<p>朴素Dijkstra算法：时间复杂度为 O(n^2)，故适合稠密图，边数比较多的时候</p>

<p>因为适用于稠密图，所以用邻接矩阵来存储</p>

<p>算法思路：设置一个集合 s 包含当前已经确定最短距离的点</p>

```
dis[i] = 0, dis[i] = MAX
for i = 1 to n
    t <- 不在 s 中的，且距离最近的点//迭代 n 次，每次迭代先找到所有未确定的点的最小值
    s <- t
    用 t 更新其他所有点的距离（看从 t 出去的所有的边，他组成的路径能不能更新其他点的距离）(+)


//每一次迭代都可以确定一个点的最短距离，循环 n 次确定 n 个点的最短距离
//(+)：比如说 t 可以走到 x，看当前 x 到一号点的距离能不能用 t 到一号点的距离更新，即如果 dis[x] > dis[t] + w，那就更新（贪心）
```

<b>Dijkstra求最短路_1</b>

```
/*
数据范围
1≤n≤500
1≤m≤1e5
为稠密图
*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510;

int n, m;
int g[N][N];
int dist[N];
bool st[N]; //确定最小值是否已经确定

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    for(int i = 0; i < n; i ++ )
    {
        int t = -1;
        for(int j = 1; j <= n; j ++ )
            if(!st[j] && (t == -1 || dist[t] > dist[j])) //在所有未确定距离的点中找到一个 dist 最小的点
                t = j;

        if(t == n) break; //优化

        st[t] = true;

        for(int j = 1; j <= n; j ++ )
            dist[j] = min(dist[j], dist[t] + g[t][j]);
    }
    
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main()
{
    scanf("%d%d", &n, &m);
    
    memset(g, 0x3f, sizeof g);
    
    while(m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = min(g[a][b], c);
    }
    
    int t = dijkstra();
    
    printf("%d\n", t);
    
    return 0;
}
```

<p>举个例子</p>

```
3 3
1 2 2
2 3 1
1 3 4
```

1. 先初始化一下距离，1 点的距离为 0 ，其他点为正无穷

2. 第一次迭代，未确定距离最小的点为 1 号点，st[1] 置为 true

3. 更新其他点到起点的距离，一共出去两条边，第一个更新的点是二号点，从一号点到二号点距离为二，故把 dist[2] 改为 2 ，dist[3] 改为 4

4. 第二次迭代，再从未确定的点中找到距离最小的点为 2 号点，置为 true。用它来更新其他点到起点的最短路径

5. 2 到起点距离为 2 ，到 3 距离为 1 ，比 1 到 3 的距离小，故更新

6. 下一轮迭代，就剩一个点了，故这个点的距离一定为 3

7. 每个点到起点的距离都确定了

</br>

#### 堆优化版的算法

</br>

<p>堆优化版的Dijkstra算法：时间复杂度为 O(mlogn)</p>

<p>来看能怎么优化</p>

```
1. dis[i] = 0, dis[i] = MAX
2. for i = 1 to n
3.     t <- 不在 s 中的，且距离最近的点     -->  一共为 n^2 次
4.     s <- t                           -->  一共为 n 次
5.     用 t 更新其他所有点的距离            -->  m 次
```

<p>对于最后一步为 m 次：因为 t 每次都不一样，n 次遍历了 1 到 n 这 n 个点，所以<b>在这 n 次循环里面其实是遍历了所有的边，故为 m 次</b></p>

<p>所以普通Dijkstra算法最慢的一步在找最短距离的一步，<b>那么在一堆数中找一个最小的的数可以用堆来做，该步变为 O(1) </b>，不过最后一步也变了，在堆中修改一个数为 logn 的，一共要修改 m 次，故变为 mlogn</p>

<b>所以用堆来存储所有点到起点的最短距离，因为优先队列不支持修改操作，所以实现方式是每次修改都往堆里插入一个数，不过可能会存在冗余，只需要用 st 判断即可</b>

<p>用邻接表存的话重边就无所谓了</p>

<p>维护堆的时候还需要知道节点编号，所以存 pair</p>

```
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n, m;
int h[N], w[N], e[N], ne[N], idx;
int dist[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});
    
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        
        int ver = t.second, distance = t.first;
        if(st[ver]) continue;

        st[ver] = true;
        
        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
    
}

int main()
{
    scanf("%d%d", &n, &m);
    
    memset(h, -1, sizeof h);
    
    while(m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    
    int t = dijkstra();
    
    printf("%d\n", t);
    
    return 0;
}
```

</br>

### 存在负权边

</br>

<p>也有两个实现方式</p>

1. Bellman-Ford算法：O(n*m)

2. SPFA：可以看作对 Bellman-Ford 的优化，平均是 O(m)，最坏情况是 O(n*m)

<p> SPFA 只是 Bellman-Ford 的优化，但不是所有情况都可以用</p>

<p>比如想求不超过 k 条边的最短路，对边数做限制，只能用Bellman-Ford</p>

</br>

## 多源汇最短路：起点和终点不确定

</br>

<p>只有一个经典的 Floyd 算法，O(n^3) </p>










 


























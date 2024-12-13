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

    int sum = 1;
    int res = 0; //每一个连通块大小的最大值
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

        st[ver] = true; //不加的话，只会影响时间，不会影响结果
        
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

#### Bellman-Ford

</br>

<p>Bellman-Ford 存边的方式可以随便存，只要能遍历所有的边，故这里边的存储方式不一定要写成邻接表，可以就定义一个结构体</p>

```
for n 次
    for 所有边 a, b, w //表示从 a 走到 b 的边，权重为 w
        dist[b] = min(dist[b], dist[a] + w) //这个更新的操作叫做松弛操作
```

<p>所有边一定满足，dist[b] <= dist[a] + w（三角不等式）</p>

<p>求最短路的时候如果有负权回路的话，最短路就不一定存在</p>

![40ee03ab9d280fa1484c9dd9aad42acf](https://github.com/user-attachments/assets/f6d57106-aaa4-44f1-9cb7-b111ecbd5b01)

<p>如上，从 1 走到 2，从 2 开始转一圈长度就会减一，若转无穷多圈，那么距离就会是负无穷。<b>所以如果能求出最短路，那么一般不存在负权回路</b></p>

<p>存在负权回路，可能没有最短路径</p>

<p><b>Bellman-Ford 可以求出是否存在负权回路的</b>，第一行的迭代是有实际意义的，比方说当前迭代了 k 次，迭代了 k 次的 dist 数组含义是：从一号点经过不超过 k 条边走到每个点的最短距离。所以当第 n 次迭代又更新了某些边的话，那么就说明存在一条边数为 n 的最短路径<b>一条路径上有 n 条边意味着，有 n+1 个点，1 到 n 总共有 n 个点，抽屉原理得一共有两个点编号一样，那么一定存在环，存在环一定是更新了之后，那么一定是负环</b></p>

<p>但一般找负环不用 Bellman—Ford 算法，而是用 SPFA 算法，因为时间较高</p>

<p>SPFA 在各方面都好于 bf 算法，但有些题只能用 bf</p>

</br>

<b>有边数限制的最短路径</b>

</br>

```
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 510, M = 10010;

int n, m, k;
int dist[N], backup[N];

struct Edge
{
    int a, b, w;
}edges[M];

int bellman_ford()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    for(int i = 0; i < k; i ++ )
    {
        memcpy(backup, dist, sizeof dist); //备份 dist 数组
        for(int j = 0; j < m; j ++ )
        {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            dist[b] = min(dist[b], backup[a] + w);
        }
    }
    
    if(dist[n] > 0x3f3f3f3f / 2) return -1;//一个正无穷可以更新另一个正无穷，n 可能到不了，但他不是正无穷
    return dist[n];
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    
    for(int i = 0; i < m; i ++ )
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
    }
    
    int t = bellman_ford();
    if(t == -1 && dist[n] != -1) puts("impossible"); //dist[n] != -1 是数据加强，因为最短路径可能就是 -1
    else printf("%d\n", t);
    
    return 0;
}
```

<p>要备份 dist 数组，否则枚举边的时候可能会出现串联，先更新了 b 点，再用 b 更新了其他点，其他点又更新了其他点，发生了串联，就不能保证前面的限制了，如下例</p>

```
三条边
1 2 1
1 3 3
2 3 1
```

<p>如果不加备份，dist 数组最开始，dist[1] = 0, dist[2] = ∞, dist[3] = ∞，最先枚举 1 到 2 这条边，把 dist[2] 更新为 1，再枚举 2 到 3 这条边，因为 2 的距离发生了变化，那么 dist[3] 就会变成 2</p>

<p>要想不发生串联，就要用上一次迭代的结果</p>

</br>

#### SPFA

</br>

<b>很推荐 spfa，正权图也可以过，被卡了就换</b>

<p>SPFA 算是单元最短路中限制最小的了，只要没有负环就可以用 SPFA（99%的最短路问题没有负环）</p>

<p>bellman-ford 是遍历所有边来更新，每一次迭代不是所有 dist 都会被更新，SPFA 就是对这个做优化</p>

<p>dist[b] 在当前迭代想变小的话，一定是 dist[a] 变小了</p>

<p>这里用宽搜来做优化，迭代的时候用一个队列来做（其实用什么都可以，队列，优先队列，堆），队列里面存的是所有变小的节点，用它来更新所有后面的后继</p>

<p>我更新过谁，再拿他来更新别人</p>

```
queue <- 1
while queue 不空
    t <- q.top
    q.pop()
    更新 t 的所有出边 t -w-> b
        if(更新成功) queue <- b，如果已经有 b 那么不用重复加入
```

<b>和 Dijkstra 特别像</b>

</br>

<b>求最短路</b>

</br>

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

int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    queue<int> q;
    q.push(1);
    st[1] = true; //存的是当前的点是否在队列当中
    
    while(q.size())
    {
        int t = q.front();
        q.pop();
        
        st[t] = false;
        
        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
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
    
    int t = spfa();
    
    if(t == -1 && dist[n] != -1) puts("impossible");
    else printf("%d\n", t);
    
    return 0;
}
```

<p>也可以用在 Dijkstra，被卡再说，比如说网格图会卡</p>

</br>

<b>求负环</b>

</br>

<p>和bf一样都是利用抽屉原理</p>

<p>在更新 dist[x] 的时候，表示当前 x 到 起点的最短路径的长度。同时记录一下 cnt[x] 表示当前最短路的边数</p>

```
dist[x] = dist[t] + w[i]
cnt[x] = cnt[t] + 1 //很容易维护这样一个数组
```

<p>如果某一次存在 cnt[x] >= n，意味着从 1 到 x 至少经过了 n 条边，n + 1 个点，根据抽屉原理，一定至少有两个点是相同的，即存在一个环</p>

<p>路径上存在一个环，不是白存在的，一定会变小，如果不变小那么就不会存在这个环，所以这个环一定是负权的</p>

<p>一开始不需要初始化了，因为求的不是距离</p>

<p>而且最开始不能直接把一号点加进去了，因为问的是是否存在负环，而不是是否存在从 1 开始的负环，即 1 号点到不了这个负环，把所有点都放进队列即可</p>

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
int dist[N], cnt[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int spfa()
{
    queue<int> q;
    
    for(int i = 1; i <= n; i ++ )
    {
        st[i] = true;
        q.push(i);
    }
    
    while(q.size())
    {
        int t = q.front();
        q.pop();
        
        st[t] = false;
        
        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                
                if(cnt[j] >= n) return true;
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    return false;
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
    
    if(spfa()) puts("Yes");
    else puts("No");
    
    return 0;
}
```

</br>

## 多源汇最短路：起点和终点不确定

</br>

<p>只有一个经典的 Floyd 算法，O(n^3) </p>

<p>原理基于动态规划，能用动态规划解的核心原因是<b>最优子结构性质</b>，状态表示是三维，d[k, i, j] 表示从顶点 i 到顶点 j，只允许经过顶点集合 {1, 2, ..., k} 的最短路径长度。</p>

<p>设当前正在考虑加入的中间点是  k ，状态转移公式为：</p>

`dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`

<p>解释：</p>

- 如果从 i 到 j 的当前路径不需要经过 k，那么保持 dist[i][j]  不变。

- 如果从 i 到 j 经过 k 会缩短路径长度，那么更新为 dist[i][k] + dist[k][j] 。

<p>初始状态：</p>

- 如果  i = j ，则 dist[i][j] = 0 （自己到自己距离为 0）。

- 如果  i 不等于 j  且  i  和  j  之间有边，设为边的权重  w 。

- 如果  i 不等于 j  且没有直接边连接，设为无穷大（INF）。

```
初始化 d[i, j]
for k = 1 to n
    for i = 1 to n
        for j = 1 to n
            d[i, j] = min(d[i, j], d[i, k] + d[k, j]) 
```

<p>先枚举 k 因为 k 是阶段（第一维没什么用，可以去掉）。算k阶段，从k-1转移过来</p>

`d[k, i, j] = d[k-1, i, k] + d[k-1, k, j] //从 i 到 k 只经过 k-1 个点，`

<p>结束后，d[i, j] 存的就是从 i 到 j 的最短路的长度</p>

```
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 210, INF = 1e9;

int n, m, Q;
int d[N][N];

void floyd()
{
    for(int k = 1; k <= n; k ++ )
        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j <= n; j ++ )
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &Q);
    
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
        {
            if(i == j) d[i][j] = 0;
            else d[i][j] = INF;
        }
        
    while(m -- )
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        
        d[a][b] = min(d[a][b], w);
    }
    
    floyd();
    
    while(Q -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        
        if(d[a][b] > INF / 2) printf("impossible\n");
        else printf("%d\n", d[a][b]);
    }
    
    return 0;
}
```

</br>

# 最小生成树

</br>

<p>该问题对应的都是无向图，有两个主要算法：</p>

- prim 算法；和 Dijkstra 算法特别像

  - 稠密图用朴素版 Prim:O(n^2)
 
  - 稀疏图用堆优化版 Prim:O(mlogn)（优化方法和 Dijkstra 一样）

- Kruskal 算法；时间复杂度是固定的，先会对所有边进行从小到大的排序 O(mlogm)

<p>取舍：稠密图直接写朴素版 Prim，稀疏图用 Kruskal，堆优化的 Prim 不常用</p>

</br>

## Prim

</br>

<p>和 Dijkstra 很像</p>

<p>s 表示当前已经在连通块中的多有点</p>

```
dist[i] <- 正无穷
for i = 0 to n //这里是迭代 n 次，因为要加入 n 个点
    t <- 集合外距离最近的点
    用 t 来更新其他点到集合的距离 //Dijkstra 是用 t 来更新其他点到起点的距离
    st[t] = true
```

<p>其他点到集合的距离：看其他点有没有一条边能连向集合内部（没有则正无穷），某一个点到集合的距离定义成这个点到集合内部的所有边当中的长度最小的那个边</p>

<p>生成树：每一次选中的 t 这个点他的距离对应的那条边就是生成树里的一条边</p>

<p>所有点不连通的时候不存在生成树</p>

<b>Prim 求最小生成树</b>

```
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 510;

int n, m;
int g[N][N];
int dist[N];
bool st[N];

int prim()
{
    memset(dist, 0x3f, sizeof dist);
    
    int res = 0;
    for(int i = 0; i < n; i ++ )
    {
        int t = -1;
        for(int j = 1; j <= n; j ++ )
            if(!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
                
        if(i && dist[t] == 0x3f3f3f3f) return 0x3f3f3f3f;

        if(i) res += dist[t];
        //只要不是第一个点，dist[t] 就是当前的点和现在已经连好的生成树里的某一条边的长度
        
        for(int j = 1; j <= n; j ++ ) dist[j] = min(dist[j], g[t][j]);

        st[t] = true;
    }
    
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    
    memset(g, 0x3f, sizeof g);
    
    while(m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    
    int t = prim();
    
    if(t == 0x3f3f3f3f) puts("impossible");
    else printf("%d\n", t);
    
    return 0; 
}
```

`if(i && dist[t] == 0x3f3f3f3f) return 0x3f3f3f3f;`

<p>如果不是第一个点，且dist为正无穷，说明当前距离最近的点到集合的距离是正无穷，即图是不连通的</p>

```
for(int j = 1; j <= n; j ++ ) if(j != t) dist[j] = min(dist[j], g[t][j]);
if(i) res += dist[t];
```

<p>注意这里，加入条件判断确保不被自环影响，自环不应该加入到最小生成树中</p>

```
if(i) res += dist[t];
for(int j = 1; j <= n; j ++ ) dist[j] = min(dist[j], g[t][j]);
```

<p>被污染也无所谓，只要在被污染前更新 res 就可以了，毕竟 Prim 的更新操作是 dist[j] = min(dist[j], g[t][j]) 而不是 Dijkstra 的 dist[j] = min(dist[j], dist[t] + g[t][j])，污染与否无所谓</p>

<b>也可以让所有 g[i][i] 等于 INF</b>

```
5 10
1 2 8
2 2 7
2 1 1
3 4 3
4 4 -10 //这条自环会有影响
1 3 -9
5 2 -4
3 1 0
1 4 8
4 4 7
```

</br>

## 堆优化Prim

</br>

<p>堆优化的思路和 Dijkstra 完全一样，用堆来维护 dist 数组，找最小值为 O(1)，更新为 O(mlogn)</p>

<p>思路麻烦，代码长，完全可以用 Kruskal 替代</p>

</br>

## Kruskal

</br>

<p>基本思路非常简单：从小到大枚举每条边，从小到大试图将每一条边加到生成树中，剩下的问题就是<b>并查集的简单应用</b>，并查集非常快为 O(1)</p>

```
将所有边按照权重从小到大排序 //瓶颈：O(mlogm)
枚举每条边 a, b, w //循环总共为 O(m)
    if(a, b 不连通)
          将这条边加入集合中 
```

<p>参考题目连通块中点的数量，Kruskal 最开始的时候每个点都是单独的一部分，也是没有边的</p>

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200010;

int n, m;
int p[N];

struct Edge
{
    int a, b, w;
    
    bool operator< (const Edge &W) const
    {
        return w < W.w;
    }
}edges[N];

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &m);
    
    for(int i = 0; i < m; i ++ )
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
    }
    
    sort(edges, edges + m);
    
    for(int i = 1; i <= n; i ++ ) p[i] = i;//初始化并查集
    
    int res = 0, cnt = 0;
    for(int i = 0; i < m; i ++ )
    {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        
        a = find(a), b = find(b); //让 a 等于 a 的祖宗节点，b 等于 b 的祖宗节点
        if(a != b) //判断 a， b 是否是连通的，就是判断二者祖宗节点是否一样
        {
            p[a] = b; //边加进来后，要把这两个点所在的集合合并
            res += w;
            cnt ++;
        }
    }
    
    if(cnt < n - 1) puts("impossible"); //若 cnt < n - 1 说明树不连通
    else printf("%d\n", res);
    
    return 0;
}
```

</br>

# 二分图

</br>

<p>二分图：可以把所有的点划分到两边去，使得所有的边都是在集合之间的，集合内部没有边</p>

<p>分两部分</p>

- 如何判别一个图是否是二分图，用染色法（就是一个很简单的DFS）O(n + m)

- 匈牙利算法，可以求一个二分图的最大匹配 最坏O(mn)，但只是一个理论的复杂度，实际运行时间一般远小于 O(mn)

</br>

## 染色法

</br>

<p>判断一个图是否是二分图，用到了很经典的性质：<b>一个图是二分图当且仅当这个图可以被二染色</b>，<b>是二分图当且仅当图中不含奇数环（环中边的数量是奇数）</b></p>

<p>必要性----根据图的定义（集合内部没有边）：如果有一个奇数环（三个边），假设环中的第一个点属于左边，第二个点一定属于右边，则第三个点是左边，第四个点为右边。因为环是奇数，推出起点属于右边，矛盾</p>

<p>充分性----构造一个图，从前往后遍历每个点，如果没有分好组就分到左边去，分好组后遍历这个点所有的邻点，这个点是左边的(1)，所有相邻点是右边的(2)，再相邻为左边，一条边的两个点的颜色一定不同（属于不同的集合），通过这种方式可以把图中所有点染色，<b>从前往后遍历，如果一个点没有被染过颜色的话，就染成白色（黑色也行），再把这个点的所有邻点染色</b>，一个连通块有一个点的颜色确定了，整个连通块就确定了（通过深搜或宽搜)</p>

<p>由于图中一定不含奇数环，故整个染色过程不会有矛盾（反证法）</p>

<p>只要一个图在染色过程中出现了矛盾，那就一定有奇数环，就不是二分图；只要没有矛盾，就没有奇数环，就是二分图</p>

<p>总而言之，只要一个图可以用二染色的方式完美地染一遍，就是一个二分图</p>

```
for i - 1 to n
    if i 未染色
        dfs(i, white)
```

<b>染色法判定二分图</b>

```
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010, M = 200010;

int n, m;
int h[N], e[M], ne[M], idx;
int color[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool dfs(int u, int c)
{
    color[u] = c;
    
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!color[j])
        {
            if(!dfs(j, 3 - c)) return false;
        }
        else if(color[j] == c) return false;
    }
    
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    
    memset(h, -1, sizeof h);
    
    while( m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    
    
    int flag = true;
    for(int i = 1; i <= n; i ++ )
        if(!color[i])
        {
            if(!dfs(i, 1))
            {
                flag = false;
                break;
            }
        }
    
    if(flag) puts("Yes");
    else puts("No");
    
    return 0;
}
```

<p>题目：257. 关押罪犯，</p>

</br>

## 匈牙利算法

</br>

<p>证明较难，参考算法导论</p>

<p>思路：可以在较快的时间内，告诉我们左边和右边匹配成功（不存在两条边是共用一个点的）的最大的数量（边的数量）是多少，</p>

<p>涉及到一个递归的过程，递归要处理问题是一样的</p>

<p>遍历 O(n) 个左集合，最坏情况下遍历所有边 O(nm)</p>

</br>

<b>二分图的最大匹配</b>

</br>

![050953861f85746597417d60e91fdd6c](https://github.com/user-attachments/assets/2a4d2d19-31a7-4186-8e1a-5aafa6638295)

<p>虽然是无向边，但只会找左集中的点指向右集中的点的边，不会从右往左</p>

```
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 510, M = 100010;

int n1, n2, m;
int h[N], e[M], ne[M], idx; //e[N] 的话会导致数组越界，什么错误都可能发生
int match[N]; //match 是右边的点对应的点
bool st[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool find(int x)
{
    for(int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!st[j])
        {
            st[j] = true;
            if (match[j] == 0 || find(match[j]))
            {
                match[j] = x;
                return true;
            }
        }
    }
    
    return false;
}

int main()
{
    scanf("%d%d%d", &n1, &n2, &m);
    
    memset(h, -1, sizeof h);

    while(m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    
    int res = 0;
    for(int i = 1; i <= n1; i ++ )
    {
        memset(st, false, sizeof st); //请空，要保证每个 n2 只考虑一遍
        if(find(i)) res ++ ;
    }
    
    printf("%d\n", res);
    
    return 0;
}
```

<p>372. 棋盘覆盖</p>


















 


























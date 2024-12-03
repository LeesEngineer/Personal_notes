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

```
//伪代码

queue <- 初始化

while queue不空
  t <- 队头
  拓展 t
```

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
                Prev[x][y] = t;
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

# 树和图的优先遍历 

</br>

<p>首先树是一种无环连通图，所以只讲图</p>

<p>图分有向图和无向图，可以把无向图看成一种有向图，所以只看有向图</p>

<p>图的存储</p>

1. 邻接矩阵；g[a][b] 就存储 a 到 b 这条边的有效信息，有权重的话就是权重，无法存储重边，用的比较少，比较浪费空间，适合存储稠密图，稀疏图不适合
2. 邻接表；如果我们有 n 个点的话，就在每一个节点上开了一个单链表，每个单链表就是存储这个点可以走到哪个点，在单链表中插入一般是在头的位置插，原为 h[2] -> 1 -> 4 -> null，插入 2 -> 3； h[2] -> 3 -> 1 -> 4 -> null

</br>

## 树与图的深度优先遍历--树的重心

</br>

```

```




























</br>

# DFS

</br>

<p>会尽可能的往深处搜索，遇到叶子的时候会<b>回溯</b></p>

<p>使用的数据结构是栈</p>

<p>空间从使用的空间上来看，DFS 向下搜的时候只需要记录路径上的这些点就够了，因此使用的空间是和高度成正比的，为 O(h)</p>

<p>DFS 中有两个很重要的概念：回溯，剪枝。</p>

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
            col[i] = dg[u + i] = udg[n - u + i] = true; //反对角线和正对角线 
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

</br>

# BFS

</br>

<p>使用的数据结构是队列</p>

<p>向下搜索的时候，需要记录一层内所有节点，因此是指数级的空间，为 O(2^h)</p>

<p>因为搜索时是一层一层往外<b>扩展</b>的，所以他有一个最短路的概念，即如果<b>每一条边权重都是 1 的时候，BFS 第一次搜索到的该点时一定是按照最近的路径</b></p>
































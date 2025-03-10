</br>

# 数字三角形

</br>

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 510, INF = 1e9;

int n;
int a[N][N];
int f[N][N];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            scanf("%d", &a[i][j]);
            
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= i + 1; j++)
            f[i][j] = -INF;
            
    f[1][1] = a[1][1];
    for(int i = 2; i <= n; i++)
        for(int j = 1; j <= i; j++)
            f[i][j] = max(f[i - 1][j - 1] + a[i][j], f[i - 1][j] + a[i][j]);
    
    int res = -INF;
    for(int i = 1; i <= n; i++) res = max(res, f[n][i]);
    printf("%d\n", res);
    return 0;
}
```

</br>

# 摘花生

</br>

<p>传统 DP 需要考虑：阶段，决策，最优子结构，无后效性</p>

<p>新的思考方式——从集合角度来考虑 DP 问题</p>

<p>动态规划：</p>

- 状态表示 f[i, j]

- - 集合：所有从 (1, 1) 走到 (i, j) 的路线
 
  - 属性（max， min， 数量）：所有路线的最大值

- 集合划分

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110, INF = 1e9;

int g[N][N];

int f[N][N];

int main()
{
    int t;
    cin >> t;
    while(t --)
    {
        int r, c;
        cin >> r >> c;
        
        for(int i = 1; i <= r; i ++)
            for(int j = 1; j <= c; j ++)
                cin >> g[i][j];
        
        for(int i = 0; i <= r; i ++)
            for(int j = 0; j <= c; j ++)
                f[i][j] = -INF;
                
        f[0][1] = 0;
        
        for(int i = 1; i <= r; i ++)
            for(int j = 1; j <= c; j ++)
                f[i][j] = max(f[i - 1][j], f[i][j - 1]) + g[i][j];
                
        cout << f[r][c] << endl;
    }
}
```

</br>

# 最低通行费

</br>

<p>一个商人穿过一个 N×N的正方形的网格，去参加一个非常重要的商务活动。他要从网格的左上角进，右下角出。每穿越中间 1 个小方格，都要花费 1 个单位时间。商人必须在 (2N−1) 个单位时间穿越出去。而在经过中间的每个小方格时，都需要缴纳一定的费用。这个商人期望在规定时间内用最少费用穿越出去。请问至少需要多少费用？</p>

<p>2N - 1 意味着不走回头路，所以本质就是摘花生</p>

```
{
    int n;
    cin >> n;
    
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            cin >> g[i][j];
            
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(i == 1 && j == 1)
            {
                f[i][j] = g[i][j];
            }
            else
            {
                f[i][j] = INF;
                if(i > 1) f[i][j] = min(f[i][j], f[i - 1][j] + g[i][j]);
                if(j > 1) f[i][j] = min(f[i][j], f[i][j - 1] + g[i][j]);
            }
            
    cout << f[n][n];
}
```

</br>

# 方格取数

</br>

<p>只走一次：</p>

- f(i, j) 表示从 (1, 1) 走到 (i, j) 的最大值

- f(i, j) = max(f(i - 1, j) + w(i, j), f(i, j - 1) + w(i, j))

<p>走两次</p>

- f(i1, j1, i2, j2) 表示从 (1, 1) 分别走到 (i, j) (i2, j2) 的最大值

<p>重点是：如何处理“同一个格子不能被重复选择”</p>

<p>两种思路：</p>

1. 第一个人选走，同时标记一下，第二个人在走

2. 同时走（这里选择第二种）

<p>要考虑什么什么时候会有交集，有一个条件，两个人走过的步数是一样的。故只有在 i1 + j1 == i2 + j2 时，两条路径格子才可能重合</p>

<p><b>看起来有四个状态，但存在一个等价关系，所以其实只有三个变量，所以可以把状态优化一下</b></p>

`f(k, i1, i2)` 

<p>k 表示 i + j</p>

<p>f(k, i1, i2) 表示一堆路线的集合，每条路线都可能从上从左走，两条路线组合后有四种情况，取其 Max</p>

<p>要做的是在两条路径有重合的时候<b> w[i, j] 只会被计算一次</b></p>

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 15;

int n;
int w[N][N];
int f[N * 2][N][N];

int main()
{
    cin >> n;
    int a, b, c;
    while(cin >> a >> b >> c, a || b || c) w[a][b] = c;
    
    for(int k = 2; k <= 2 * n; k ++)
        for(int i1 = 1; i1 <= n; i1 ++)
            for(int i2 = 1; i2 <= n; i2 ++)
            {
                int j1 = k - i1, j2 = k - i2;
                if(j1 >= 1 && j1 <= n && j2 >= 1 && j2 <= n)
                {
                    int t = w[i1][j1];
                    if(i1 != i2) t += w[i2][j2];
                    int &x = f[k][i1][i2];
                    x = max(x, f[k - 1][i1 - 1][i2 - 1] + t);
                    x = max(x, f[k - 1][i1 - 1][i2] + t);
                    x = max(x, f[k - 1][i1][i2 - 1] + t);
                    x = max(x, f[k - 1][i1][i2] + t);
                }
            }
            
    cout << f[n + n][n][n];
}
```


























































































































































































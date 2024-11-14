</br>

# 动态规划的理解

</br>

<p>动态规划是一种优化算法，用于解决具有重叠子问题和最优子结构性质的问题。动态规划通过将复杂问题分解为更简单的子问题，并存储这些子问题的解来避免重复计算，从而提高效率。</p>

<p>个人理解动态规划：要从两个角度来考虑，第一个是状态表示，第二个是状态计算。所谓状态就是一个未知数。</p>

<p>比较难的DP问题，还会涉及对DP的优化，是对动态规划的代码或动态规划的方程做一个等价变形，所以一定要把基本的形式写出来，再做优化，比如说背包问题，最好的方法是用一维数组去写，但考虑的时候一定要从最朴素的方向去考虑，这样才能知道思维的一个过程</p>

<p>是从集合的角度去理解问题，<b>DP问题的每一个状态表示的是一个集合</b>，需要考虑清楚的是f(i,j)表示的是哪一个集合</p>

*   状态表示：就是思考我们要用几维的状态来表示，状态考虑也可以从两个角度去考虑。一般来说背包问题是二维的，f(i,j)。
*   *   他表示的集合是什么，是所有选法的一个集合，条件是:1.只从前i个物品中去选，2.选出来的物品的总体积小于等于j
*   *   f(i,j)表示的集合的属性是什么，属性常见的有最大值，最小值，元素的数量，背包问题的属性是最大值
*   状态计算：如何能一步一步的把我们的每一个状态计算出来

<p>f(i,j)表示的是集合的某种属性，集合里面是所有选法，但属性的话是一个值，最终会落实到这个值上面</p>

<p>所有DP：状态表示是什么，状态计算是什么，状态表示是哪一个集合的那种属性，集合里面的元素要满足哪些条件呢，状态计算就是集合的划分可以把当前的集合划分为哪些类呢，分完之后可以使每一类都算出来</p>

<p></p>

<p></p>

<p></p>

</br>

# 背包问题

</br>

<p>给我们N个物品和一个容量是V的背包，每一个物品有两个属性，体积Vi，价格（权重）Wi，问题是：挑选一些物品，在装得下的情况下，选出来的物品的最大的总价值是多少</p>

## 01背包问题

<p>每件物品最多只能用一次</p>

<p>01背包问题里面集合的划分是一个很经典的划分，会把f(i,j)的这个集合划分成两个子集，其实是把他表示的选法分为两大类，第一类是不包含第i个物品，第二类是包含第i个物品,满足不重不漏</p>

1.  第一类就是从 1～i-1 中选，不超过j的集合，可以用f(i-1,j)来表示，所以第一类的最大值就是f(i-1,j)，第一类情况一定存在
2.  1.  第二类（算第二种情况的最大值就是背包问题的难点），从 1～i 中选，不超过j的集合，还要包含i的集合。直接求不好求，需要曲线救国。先把每种选法里面的第i个物品全部去掉，**不影响我们的最大值是谁，问题就转变为从 1～i-1 中选，不超过j-vi，这样的一个集合其实就是f(i-1,j-vi)，也就表示这些选法的一个最大值，**f(i-1,j-vi)+wi**就是我们要求的一个最大值。** 当vi大于j时，第二类情况不存在。

`f(i, j) = Max(f(i - 1, j), f(i - 1, j - vi) + wi)`

<p>这就是背包问题的状态计算的方式</p>

### 二维表示01背包问题

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 1010;

    int n, m;
    int v[N], w[N];
    int f[N][N];

    int main()
    {
        cin >> n >> m;
        
        for (int i = 1; i <= n; i++ ) cin >> v[i] >> w[i];
        
        for (int i = 1; i <= n; i++ )
            for (int j = 0; j <= m; j++ )
            {
                f[i][j] = f[i - 1][j];
                if (j >= v[i]) f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
            }
            
        cout << f[n][m] << endl;
        
        return 0;
    }

![image](https://github.com/user-attachments/assets/aa817944-3376-4fb5-af7e-832b8fd36364)

</br>

### 一维表示01背包问题

</br>

<p>这个用二维来表示，还是很简单的，再来转换成一维，能转换成一维是由两个原因决定的，看一下状态转移方程，f(i, j)层在计算的时候只用到了f(i - 1, j)层，f(i - 2, j)层到f(1, j)是一直没有用到的。所以可以用滚动数组来做，又发现了另外一个问题，用到的f[i - 1][j]和f[i - 1][j - v[i]]中的 j 和  j-vi 都是小于等于 j 的，没有说在j的两侧，所以可以改成用一维数组来算</p>

```初步修改
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N];
int f[N];

int main()
{
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++ ) cin >> v[i] >> w[i];
    
    for (int i = 1; i <= n; i++ )
        for (int j = 0; j <= m; j++ )//j从零，开始会有条件为假，没有意义，
        {
            f[j] = f[j]; //变为了一个恒等式，可以直接把他删掉
            if (j >= v[i]) f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
            //如果这里把第一维删掉，和之前并不等价，第i层算的f[j],一定是f[i][j]，
            //j-vi是严格小于j的，而j是从小到大枚举的，所以说在算f[j]的时候，
            //f[j-vi]在第i层已经被计算过了，他等价的是f[i][j - v[i]] + w[i]是不对的
        }
        
    cout << f[n][m] << endl;
    
    return 0;
}
```

<p>终极写法，<b>滚动数组</b></p>

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 1010;

    int n, m;
    int v[N], w[N];
    int f[N];

    int main()
    {
        cin >> n >> m;
            
        for (int i = 1; i <= n; i++ ) cin >> v[i] >> w[i];
            
        for (int i = 1; i <= n; i++ )
            for (int j = m; j >= v[i]; j-- )
                f[j] = max(f[j], f[j - v[i]] + w[i]);
            
        cout << f[m] << endl;
            
        return 0;
    }

<b>图解与二维一致</b>

</br>

## 完全背包问题

</br>

<p>每件物品有无限个，只要体积够用，可以无限装，和01背包问题很像。可以用类似的思考方式,状态表示，状态计算</p>

</br>

### 二维表示完全背包问题\_枚举k

</br>

<p>状态计算是集合的划分，01背包问题是分为了两部分，按照第i个物品选一个或选零个分为了两部分，，完全背包问题可以扩展，可以按照第i个物品选多少个来分，所以可以分为若干组，</p>

![image](https://github.com/user-attachments/assets/250abd75-86c5-48ab-958d-9b226715359b)

<p>第一个可以用f(i-1, j)来表示，非零也可以用曲线救国的方式分为三步走：</p>

1.  去掉k个物品i
2.  求Max，f(i-1,j-k\*vi)
3.  再加回来k个物品i，f\[i-1,j-k*vi] + k*wi

<p>就推出来了完全背包问题的状态转移方程</p>

`f(i, j) = f(i-1, j - v[i] * k) + w[i] * k`

<p>时间复杂度比较高</p>

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 1010;

    int n, m;
    int v[N], w[N];
    int f[N][N];

    int main()
    {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) cin >> v[i] >> w[i];
            
        for(int i = 1; i <= n; i++)
            for(int j = 0; j <= m; j++)
                for(k = 0; k * v[i] <= j; k++)
                    f[i][j] = max(f[i][j], f[i - 1][j - v[i] * k] + w[i] * k);
                        
        cout << f[n][m] << endl;
            
        return 0;
    }

</br>

### 二维表示完全背包问题\_优化

</br>

<p>可以优化为二维，观察一下方程，把他展开，把k枚举一下</p>

```
    f(i, j) = max(f(i - 1, j), f(i - 1, j - v) + w, f(i - 1, j - 2v) + 2w, f(i - 1, j - 3v) + 3w, ...)
    f(i, j - v) = max(         f(i - 1, j - v),     f(i - 1, j - 2v) + w,  f(i - 1, j - 3w) + 2w, ...)

```

<p>惊奇的发现，f(i,j)算的时候有很多的状态与f(i,j-v)是一一对应的，所以f(i - 1, j - v) + w, f(i - 1, j - 2v) + 2w, f(i - 1, j - 3v) + 3w, ... 这一堆的最大值就应该等于f(i - 1, j - v),     f(i - 1, j - 2v) + w,  f(i - 1, j - 3w) + 2w, ... 这一堆的最大值加wi，所以,<b>f(i,j)不用和k项有关系，只需和两项有关系</b></p>

`f(i, j) = max(f(i - 1, j), f(i, j - vi) + wi) //与01很像`

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 1010;

    int n, m;
    int v[N], w[N];
    int f[N][N];

    int main()
    {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) cin >> v[i] >> w[i];
            
        for(int i = 1; i <= n; i++)
            for(int j = 0; j <= m; j++)
            {
                f[i][j] = f[i - 1][j];
                if(j >= v[i]) f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);
            }
                        
        cout << f[n][m] << endl;
            
        return 0;
    }

</br>

### 一维表示完全背包问题

</br>

<p>完全背包问题也可以优化为一维，做等价变形</p>

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 1010;

    int n, m;
    int v[N], w[N];
    int f[N];

    int main()
    {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) cin >> v[i] >> w[i];
            
        for(int i = 1; i <= n; i++)
            for(int j = v[i]; j <= m; j++)
                f[j] = max(f[j], f[j - v[i]] + w[i]);
                        
        cout << f[m] << endl;
            
        return 0;
    }

<p>这里没有01背包的问题了，由于我们的j是从小到大枚举的，而且j-vi是小于j的，所以算f[j]的时候f[j-vi]已经被算过了，所以这里的f[j-vi]其实是f[i,j-vi]，第i层的j-vi，<b>和我们的状态转移方程是完全一致的</b>，不需要再做改变了，所以从小到大就可以了</p>

<p><b>转移的时候如果用的是上一层的状态的话，就要从大到小枚举体积，如果用的是本层的话，就要从小到大枚举体积</b></p>

</br>

<p>和01背包问题只有一点区别，01背包是从大到小循环，完全背包是从小到大循环</p>

</br>

## 多重背包问题

<p>完全背包问题可以当成多重背包问题来优化</p>

<p>每个物品至多有xi个，会有一个优化方式</p>

<p>多重背包问题与完全背包和01背包类似</p>

</br>

### 多重背包问题\_暴力枚举

</br>

![image](https://github.com/user-attachments/assets/4e80ccb0-e761-4c2f-bea5-be904163842d)

`f[i][j] = max(f[i - 1][j - v[i] * k] + w[i] * k) //k = 0 ~ s[i]`

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 110;

    int n, m;
    int v[N], w[N], s[N];
    int f[N][N];

    int main()
    {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) cin >> v[i] >> w[i] >> s[i];
            
        for(int i = 1; i <= n; i++)
            for(int j = 0; j <= m; j++)
                for(int k = 0; k <= s[i] && k * v[i] <= j; k++)
                    f[i][j] = max(f[i][j], f[i - 1][j - v[i] * k] + w[i] * k);
                        
        cout << f[n][m] << endl;
            
        return 0;
    }

</br>

### 多重背包问题\_优化

</br>

<p>三重循环，不适合数据过大的情况，可能会Time Limit Exceeded（TLE）</p>

<p>无法使用完全背包问题的优化方式来优化</p>

        f(i,j) = max(f(i-1,j),f(i-1,j-v)+w,f(i-1,j-2v)+2w,...,f(i-1,j-sv)+sw)
        f(i,j-v) = max(       f(i-1,j-v),  f(i-1,j-2v)+w,..., f(i-1,j-sv)+(s-1)w,f(i-1,j-(s+1)v)+sw)

<p>后面多出来一项：f(i - 1, j - (s + 1)v) + sw。现在要求前面<b>(f(i-1,j-v),  f(i-1,j-2v)+w,..., f(i-1,j-sv)+(s-1)w)</b>的最大值，已知的是总体<b>(f(i-1,j-v),  f(i-1,j-2v)+w,..., f(i-1,j-sv)+(s-1)w,f(i-1,j-(s+1)v)+sw)</b>的最大值，我们并不能依据总体的最大值求出前面的最大值</p>

<p>解释：现给出A,B,C,D,E,F,G,H,I这些数的最大值，能否求出前面A,B,C,D,E,F,G,H的最大值，是求不出来的，因为max这个操作是不支持减法的，求总和支持减法，但最大值的话，我们并不能通过总共的最大值和最后一个数的值来求出前面的最大值，<b>所以无法使用完全背包问题的优化方式来优化</b></p>

***多重背包的二进制优化方法***

<p>假设我们想去枚举1023个物品，但是真的不需要从0去枚举到1023，因为我们有一种更高效的枚举方式，可以把若干个第i个物品打包，1,2,4,8,16,32,64,128,256,512，2的整数次幂，打包成十组，每一组最多选一个，我们能<b>用这十组拼凑出来这从0到1023的任何一个数（可证明）</b></p>

<p>第一组可表示0～1，加上第二组可表示2～3，共可以表示0～3，加上第三组可表示4～7，共可表示0～7，以此类推</p>

<p>每一组打包起来的第i个物品可以看作是一个01背包问题里面的一个物品，因为只能选一次。所以我们就是用十个新的物品来表示原来的第i个物品，枚举这个新的物品选或不选，就可以拼凑出来第i个物品所有的方案了</p>

<p>原来要枚举1024次，现在只需要枚举十次，就想到一个logn的做法，就是把O(n)一维线性优化成log级别</p>

<p>对任意s：1,2,4,8,...,2**k,c。<b>(c < 2**(k+1))</b>，从零到s任何一个数一定能被拼凑出来</p>

<p>第i个物品与s个，把他拆分成logs个，对所有新的物品做一个01背包问题，原问题时间复杂度为N*V*S三重循环，现在是N*V*logS</p>

</br>

### 直接写一维了

</br>

    #include<iostream>
    #include<algorithm>

    using namespace std;

    const int N = 25000, M = 2010;

    int n, m;
    int v[N], w[N];
    int f[N];

    int main()
    {
        cin >> n >> m;
            
        int cnt = 0;
        for(int i = 1; i <= n; i++)
        {
            int a, b, s;
            cin >> a >> b >> s;
            int k = 1;
            while(k <= s)
            {
                cnt++;
                v[cnt] = a * k;
                w[cnt] = b * k;
                s -= k;
                k *= 2;
            }
            if(s > 0)
            {
                cnt++;
                v[cnt] = a * s;
                w[cnt] = b * s;
            }
        }
            
        n = cnt;
            
        for(int i = 1; i <= n; i++)
            for(int j = m; j >= v[i]; j--) //毕竟是01背包问题
                f[j] = max(f[j], f[j - v[i]] + w[i]);
                    
        cout << f[m] << endl;
            
        return 0;
    }

</br>

### 单调队列优化方案——男人八题之一

</br>

<p>LeetCode 239.</p>

<p>如果数据很大，二进制表示的复杂度还是太大，直接TLE。</p>

    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= m; j++)
            for(int k = 0; k <= s[i] && k * v[i] <= j; k++)
                f[i][j] = max(f[i][j], f[i - 1][j - v[i] * k] + w[i] * k);

<p>第一维是循环物品，第二维是循环体积，下一维循环是循环我们的决策(从0到s[i])，观察这个决策有什么性质，能不能用一个数据结构把他优化掉</p>

<p>在循环体积的时候，把所有的体积(j)归一下类，根据j%v=0的归为一类，j%v=1的归为一类，也就是说按照这个体积模上v的余数把它分为若干类，每一类是完全没有交集的，所有类加到一块是全集，<b>把所有物品分为了v类</b>，这v类两两之间是相互独立的</p>

<b>j只会从 j - v\[i] \* k 转移过来，也就是他只会从与他余数相同的集合里面转移，j%v=0不会从j%v=1这个集合里面转移状态，所以去分别去单独地考虑每一类</b>

    #include<iostream>
    #include<cstring>
    #include<algorithm>
    #include<vector>

    using namespace std;

    const int N = 20010;

    int n, m;
    int f[N], g[N], q[N];

    int main()
    {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
        {
            int v, w, s;
            cin >> v >> w >> s;
            memcpy(g, f, sizeof f);
                
            for(int j = 0; j < v; j++) //枚举余数
            {
                int hh = 0, tt = -1;
                for(int k = j; k <= m; k += v) //枚举余数里面的所有数，在枚举这个数里面所有数的时候，可以用单调队列优化
                { //经典的单调队列问题
                    f[k] = g[k];
                    if(hh <= tt && k - s * v > q[hh]) hh++; //每次把队首取出来，队列的首部一定是最大的数
                    if(hh <= tt) f[k] = max(f[k], g[q[hh]] + (k - q[hh]) / v * w); //用队首去更新我们当前的数
                    while(hh <= tt && g[q[tt]] - (q[tt] - j) / v * w <= g[k] - (k - j) / v * w) tt--;
                    //每次把当前数往队列里插，插的时候需要剔除队列里面一定不会被用到的元素
                    q[++tt] = k; //把当前数插入到队列里面去
                }
            }
        }
            
        cout << f[m] << endl;
        return 0;
    }

<p>当我们在算f[i]，一共要算k个和v余数一样的数.<b>这一串都是连续的，因为公差是v</b>，也就是说我们在算j的时候看的是前k个数，挑个最大值</p>

`f[j] = f[j - v] + w, f[j - 2v] + 2w, ... f[j - kv] + kw `

<p>再算f[j + v]的时候，实际上是把这k个数往后移了一位，但是框里还是有k个数，这就变成了经典的单调队列问题，给一个序列，<b>动态的求出来</b>长度为k的所有框里面的最大值</p>

`f[j + v] = f[j] + w, f[j - v] + 2w, ... f[j - (k + 1)v] + kw `

<p>与单调队列有一点不同，在窗口滑动的时候，数会加一个w，不过没有影响，因为同时加一个数不影大小关系</p>

![image](https://github.com/user-attachments/assets/073af48b-89f8-4c4b-a887-379d34f68bb6)

<p>动态每次求连续三个数的最大值，这就是一个经典的单调队列问题</p>

</br>

## 分组背包问题

</br>

<p>物品有N组，每一组物品里面有若干个物品，<b>限制：每一组里面至多选一个，每一组中是互斥的</b></p>

<p>完全背包问题是枚举第i个物品选几个，分组背包问题是枚举第i组物品选哪个或不选</p>

<p>没有一个好的优化方法，只能用循环去做，循环物品，循环容量，<b>循环决策</b></p>

![image](https://github.com/user-attachments/assets/0fbe156e-baa9-4cb1-8adf-30eb1c175dfa)

    #include<iostream>
    #include<algorithm>

    using namespace std;

    const int N = 110;

    int n, m;
    int v[N][N], w[N][N], s[N];
    int f[N];

    int main()
    {
        cin >> n >> m;
            
        for(int i =1; i <= n; i++)
        {
            cin >> s[i];
            for(int j = 0; j < s[i]; j++)
                cin >> v[i][j] >> w[i][j];
        }
            
        for(int i = 1; i <= n; i++)
            for(int j = m; j >= 0; j--)
                for(int k = 0; k < s[i]; k++)
                    if(v[i][k] <= j)
                        f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
                            
        cout << f[m] << endl;
        return 0;
    }

</br>

## 混合背包问题

</br>

<p>物品一共有三类，第一类物品只能用一次，第二类物品可以用无限次，第三类物品最多用si次</p>

*   si = -1 ：表示01背包问题
*   si = 0 ： 表示第i种物品可以用无限次
*   si > 0 ：表示第i种物品可以使用si次

<p>前两类无所谓，01背包和完全背包，数据小时可以接受，多重背包用个二进制优化就可以了</p>

<p>只需要判断当前物品是什么类的，根据类去转移就可以了</p>

<p>先去把所有的物品做一个分解，多重背包会用到二进制优化</p>

<p>遇到01背包直接存下来，遇到完全背包直接存下来，遇到多重背包就把他拆分成logs份，变成01背包的一个问题</p>

    #include <iostream>
    #include <cstring>
    #include <cstdio>
    #include <algorithm>
    #include <vector>

    using namespace std;

    const int N = 1010;

    struct Thing
    {
        int kind;
        int v, w;
    };

    int n, m;
    vector<Thing> things;
    int f[N];

    int main()
    {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
        {
            int v, w, s;
            cin >> v >> w >> s;
            if(s < 0) things.push_back({-1, v, w});
            else if(s == 0) things.push_back({0, v, w});
            else
            {
                for(int k = 1; k <= s; k <<= 1)
                {
                    things.push_back({-1, v * k, w * k});
                    s -= k;
                }
                if(s) things.push_back({-1, v * s, w * s});
            }
            
        }
        for(auto &thing : things)
        {
            if(thing.kind == -1)
            {
                for(int i = m; i >= thing.v; i--)
                    f[i] = max(f[i], f[i - thing.v] + thing.w);
            }
            else
            {
                for(int i = thing.v; i <= m; i++)
                    f[i] = max(f[i], f[i - thing.v] + thing.w);
            }
        }
        
        cout << f[m] << endl;
        return 0;
    }

</br>

## 二维费用的背包问题

</br>

<p>一般的背包问题只有容量，这里还有一个重量费用f</p>

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 110;

    int n, v, m;
    int f[N][N];

    int main()
    {
        cin >> n >> v >> m;
        for(int i = 0; i < n; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            for(int j = v; j >= a; j --)
                for(int k = m; k >= b; k--)
                    f[j][k] = max(f[j][k], f[j - a][k - b] + c);
        }
                        
        cout << f[v][m] << endl;
        return 0;
    }

</br>

## 实际问题

</br>

</br>

### 背包问题求方案数

</br>

<p>未更新</p>

</br>

### 求背包问题的方案

</br>

<p>未更新</p>

</br>

### 有依赖的背包问题

</br>

<p>未更新</p>

</br>

# 线性DP

</br>

<p>是指我们的递推方程有一个明显的线性关系，可能是一维线性也可能是二维线性。</p>

<p>动态规划里面的状态都是一个n维的状态，这个n维(n>1)状态有一个求的顺序。</p>

<p>二维时，状态几可以被描述成一个二维矩阵，是一行一行来求的，有一个线性顺序来求，这样的DP就被称为线性DP，线性DP简单，因为是一条线好想</p>

</br>

## 数字三角形

</br>

```样例，属性是行列
0:              0   0
1:            0   7   0
2:          0   3   8   0
3:        0   8   1   0   0
4:      0   2   7   4   4   0
5:    0   4   5   2   6   5   0
```

![image](https://github.com/user-attachments/assets/7a0e1bd9-27eb-4c3e-8dad-a892107f1656)

<p>需要一个曲线救国的过程，因为都会经过(i，j)，所以去掉7</p>

<p>左右状态分别为：</p>

`f(i-1, j-1) + a(i, j)`
`f(i-1, j+1) + a(i, j)`

<p>那么：</p>

`f(i, j) = max(f(i-1, j-1) + a(i, j), f(i-1, j) + a(i, j))`

*关于下标从0开始还是从1开始，有一个思想，如果涉及到了f\[i-1]的下标，则一般要求i >= 1，因为这样不会越界，<b>这时，会给f\[0]设置一个边界值，比如负无穷，0，正无穷，来避免越界的风险，来使代码少一些if判断。</b>*

```从上往下做
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
        for(int j = 0; j <= i + 1; j++) //注意注意是i + 1
            f[i][j] = -INF; //设置边界
            
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

```从下往上做
```

<p>从下往上做就不需要枚举了</p>

</br>

## 最长上升子序列

</br>

<p>是子序列不是子串</p>

<p>状态表示要有一个原则，要能把状态表示出来而且能推出来，而且要维度越小越好</p>

![image](https://github.com/user-attachments/assets/737b92c8-afbd-43e3-a779-4bea92bf19a6)

<p>最长上升子序列结尾是i是确定的，以第i-1个数是哪个数来分类，第一类就是没有第i-1个数，只有第i个数，用0来表示。第二类是我们的倒数第二个数是a[1]，第三类是倒数第二个数是a[2]，最后一类是a[i-1]。当然，并不是说每一类都存在</p>

`f[i] = max(f[j] + 1) //a[j] < a[i], j = 0, 1, 2, ..., i-1`

<p>动态规划的时间复杂度好算，状态数量 * 计算每一个状态的时间：n * O(n) = O(n^2)</p>

```时间复杂度是n^2
    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 1010;

    int n;
    int a[N], f[N];

    int main()
    {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        
        for(int i = 1; i <= n; i++)
        {    
            f[i] = 1;
            for(int j = 1; j <= i - 1; j++)
                if(a[j] < a[i])
                    f[i] = max(f[i], f[j] + 1); //缩小问题规模
        }
        
        int res = 0;
        for(int i = 1; i <= n; i++)
            res = max(res, f[i]); //枚举
        cout << res;
        return 0;
    }
```

<p>关于要存储最长子序列：来存储一下每一个转移是怎么转移过来的就行了</p>

        #include <iostream>
        #include <algorithm>

        using namespace std;

        const int N = 1010;

        int n;
        int a[N], f[N];
        int g[N];

        int main()
        {
            cin >> n;
            for(int i = 1; i <= n; i++)
                cin >> a[i];
            
            for(int i = 1; i <= n; i++)
            {    
                f[i] = 1;
                for(int j = 1; j <= i - 1; j++)
                    if(a[j] < a[i])
                        if(f[i] < f[j] + 1)
                        {
                            f[i] = f[j] + 1;
                            g[i] = j; //记录状态如何转移
                        }
            }
            
            int k = 1; //最优解的下标
            for(int i = 1; i <= n; i++)
                if(f[k] < f[i])
                    k = i;
            cout << f[k] << endl;
            
            for(int i = 0; i < f[k]; i++)
            {
                printf("%d ", a[k]);
                k = g[k];
            }
            
            return 0;
        }

<p>动态规划问题记录方案其实就是把我们的状态转移存下来就行了。</p>

</br>

## 最长公共子序列

</br>

![image](https://github.com/user-attachments/assets/8f9215f6-cd24-4938-8430-80317adf8762)

<p>难点在集合的划分上：这里是以a[i]和b[j]是否包含在子序列当中，以这个作为划分的依据，选a[i]b[j]一共有四种情况，可以划分成四个子集</p>

<p>f[i,j]所有的公共子序列一定可以不重不漏分到这四种情况中去，例如00：所有第一个序列前i-1个字母中出现，并且在第二个序列前j-1个字母中出现的子序列的最大值</p>

<p>两种简单情况</p>

*   00：f\[i-1]\[j-1]
*   11：f\[i-1]\[j-1] + 1 //先去再加

<p>中间两种情况和f[i-1][j]和f[i][j-1]不是一个东西，f[i-1,j]表示的是所有在第一个字符串前i-1个字母中出现，并且在第二个字符串前j个字母中出现的子序列的一个最大值。</p>

<p>01表示a[i]不出现在子序列当中，b[j]一定出现在子序列当中的一个所有的子序列</p>

<p>f[i-1][j]表示在b的前j个字母中出现，所以它所有的公共子序列里面不是所有子集都包含b[j]的，所以二者并不完全等价</p>

<p>但好处是f[i-1,j]的这些子序列里面一定有子集是a[i]不出现在公共子序列当中，但是b[j]出现在公共子序列当中，而且f[i-1,j]所有的子序列一定是包含在f[i,j]之中</p>

<p>01的最大值没法直接求，但是根据两个特点，是可以用f[i-1,j]来替换01的</p>

<p>虽然这样求Max，会导致这四个分类里面是有重复的，但是不影响max(求Max和Min时分解的子问题允许重复，<b>求数量的话它分成的子问题一定不能有重复</b>)，只要能涵盖掉就行</p>

</br>

<p>f[i-1][j-1]一般都不写，因为f[i-1][j-1]一定是包含在f[i-1][j]和f[i][j-1]之中，所以就三种情况</p>

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 1010;

    int n, m;
    char a[N], b[N];
    int f[N][N];
        
    int main()
    {   
        scanf("%d%d", &n, &m);
        scanf("%s%s", a + 1, b + 1);
        
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
            {
                f[i][j] = max(f[i - 1][j], f[i][j - 1]); //前两种情况一定存在，第三种情况不一定存在
                if(a[i] == b[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
            }
        printf("%d\n", f[n][m]);
        return 0;
    }   

![image](https://github.com/user-attachments/assets/28664c4e-f18b-4be8-a516-6845d0375181)

</br>

# 区间DP

</br>

<p>区间DP是定义状态的时候是定义了一个区间</p>

</br>

## 石子合并

</br>

![image](https://github.com/user-attachments/assets/07bf814f-a464-4ce9-91d6-284d7a41c1f8)

<p>以最后一次分类的分界线来分类</p>

`f[i, j] = min(f[i, k] + f[k + 1, j]) + s[j] - s[i - 1]; k = i~j-1 //前缀和`

<p>时间复杂度为O(n^3)</p>

<p><b>按照区间长度从小到大来枚举,再枚举起点</b></p>

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 310;

    int n;
    int s[N];
    int f[N][N];

    int main()
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &s[i]);
        
        for(int i = 1; i <= n; i++) s[i] += s[i - 1];
        
        for(int len = 2; len <= n; len++)
            for(int i = 1; i + len - 1 <= n; i++)
            {
                int l = i, r = i + len - 1;
                f[l][r] = 1e8; //因为求的是最小值，要初始化
                for(int k = l; k < r; k++)
                    f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
            }
            
            printf("%d", f[1][n]);
            return 0;
    }

<p>区间DP一般都这么循环</p>

</br>

# 计数类DP

</br>

## 整数划分

</br>

<p>有很多考虑方式，不同的考虑方式可以得到不同的状态转移方程，时间复杂度是一样的，之前的DP问题求的都是Max和Min，这里求的是个数</p>

<p>求方案数的时候是不需要考虑他们之间的顺序的，4=1+2+1=2+1+1+1+1+2，三种方式是等价的</p>

<p>答案可能很大，输出结果对10^9+7取模</p>

</br>

### 背包解法

</br>

<p>实际上也可以用DFS来做，但是会超时</p>

<p>把整数n看作是一个容量为n的背包，然后有n个物品物品的体积分别是1，2，3...，n。</p>

<p>求的是恰好装满背包的一个方案数</p>

<p>每种物品可以用无限次，所以算是一个完全背包问题，只是要求恰好装满</p>

![image](https://github.com/user-attachments/assets/2ccaf0bc-3aed-4640-bf8a-3b381af27c27)

<p>表面上看，状态数量n^2，转移数量O(n)，所以时间复杂度是n^3</p>

<p>但实际上1000时，体积为1时s为1000/1，体积为2时s为1000/2，知道1000/1000。总和为<b>logn</b>，所以是n^2*logn</p>

<p>回忆一下完全背包的优化方式，把n^2*logn优化一下</p>

```i*s<=j
f[i][j] = f[i - 1][j] + f[i - 1][j - i] + f[i - 1][j - 2i] + ... + f[i - 1][j - si]
f[i][j - i] =           f[i - 1][j - i] + f[i - 1][j - 2i] + ... + f[i - 1][j - si]

f[i][j] = f[i - 1][j] + f[i][j - i]
```

<p>再用一维优化：</p>

`f[j] = f[j] + f[j - i]`

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 1010, mod = 1e9 + 7;
    int n;
    int f[N];

    int main()
    {
        cin >> n;
        f[0] = 1; //一个数都不选，组合是0，是一种方案
        for(int i = 1; i <= n; i++)
            for(int j = i; j <= n; j++)
                f[j] = (f[j] + f[j - i]) % mod;
        
        cout << f[n] << endl;
        return 0;
    }

</br>

### 划分解法

</br>

![image](https://github.com/user-attachments/assets/7e6efdd5-01fb-4d87-86ae-ceb6e4adbdc4)

<p>状态计算分为了两类(不重不漏)：</p>

1.  方案中的最小值是1：由于这里的每一个方案都存在一个1，把每一个方案里面的1都去掉，变成一个f(i - 1, j - 1)的一个方案，表示f(i - 1, j - 1)的方案加上一个1就得到了f(i, j)，二者是互相对应的。
2.  方案中的最小值大于1：因为每一个数都严格大于1，可以把每一个数减去1，变成一个f(i - j, j)，也可以把f(i - j, j)转变为f(i, j)。

`f(i, j) = f(i - 1, j - 1) + f(i - j, j)`

`ans = f(n, 1) + f(n, 2) + ... + f(n, n) //要枚举`

    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 1010, mod = 1e9 + 7;

    int n;
    int f[N][N];

    int main()
    {
        cin >> n;
        
        f[0][0] = 1;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= i; j++)
                f[i][j] = (f[i - 1][j - 1] + f[i - j][j]) % mod;
                
        int res = 0;
        for(int i = 1; i <= n; i++) res = (res + f[n][i]) % mod;
        
        cout << res << endl;
        return 0;
    }

</br>

# 数位统计DP

</br>

<p>数位问题最重要的就是<b>分情况讨论</b></p>

    求[a, b]内, 0~9出现的次数

    令count(n, x) 为1~n中x出现的次数

    count(b, x) - count(a - 1, x) 
    一个常用的技巧，当我们求区间的答案不好算时，可以求前缀的答案

<p><b>类似一个前缀和</b></p>

<p>把 N*M 的棋盘分成若干个 1*2 的小长方形，共有多少种分法</p>

</br>

## 计数问题

</br>

<p>暴力不可取</p>

<p>所以我们的目标是实现<b>count函数</b></p>

    1 ～ n, x = 1
    n = abcdefg
    分别求出1在每一位上出现的次数

    例如求1在第四位出现的次数
    1 <= xxx1yyy <= abcdefg
    求有多少个形如xxx1yyy的数，是在1到n之间的
    分情况讨论：
    (1)前三位xxx = 000 ～ abc - 1，因为第四位已经取1了，且前三位已经小于abc了，所以后三位可以随便取，yyy = 000 ～ 999，一定是在范围内的
        一共有 abc * 1000 种选法

    (2)xxx = abc，前三位不可能大于abc需要再细分情况讨论
        (2-1) d < 1(d = 0)，前三位已经是abc了，第四位取1的话，abc1yyy > abc0efg，有严格大于
            方案数是 0
        (2-2) d = 1，前四位是abc1的情况下，后三位只能是 yyy = 000 ~ efg
            方案数是 efg + 1
        (2-3) d > 1，范围上限是abcdefg，前四位是abc1，因为 d > 1，所以后三位 yyy = 000 ~ 999
            方案数是 1000
            
    把所有情况加到一起，就是1出现在第四位的的次数

<p>通过这样的分情况讨论就可以求1在任何一位上出现的次数了</p>

<p>再用类似前缀和的减法，来求 a~b 出现的次数</p>

<p><b>时间复杂度很低很低</b></p>

<b>边界问题：</b>

*   当枚举的数字出现在最高位的情况，那么第一种情况就不存在了，只用算第二种情况
*   当枚举 0 的时候，因为不能有前导零的存在，所以在第一种情况里面，前三位不能取 000～abc-1 ，否则就是0000了，

```
```

</br>

# 状态压缩DP

</br>

<b>状态压缩DP，虽然他的状态是一个整数，但是要把他看成一个二进制数，01代表不同情况，一般状态不会很多</b>

</br>

## 蒙德里安的梦想

</br>

![image](https://github.com/user-attachments/assets/b7c6b180-7e59-4ad6-ab9a-1bc3617c8857)

<p>一个状态压缩的经典应用</p>

![image](https://github.com/user-attachments/assets/a444c98b-7f23-4108-a1f9-8c96ebec4bec)

<p>现在不再想切分的问题，就想往里面放 1*2 小方格，可以横着放也可以竖着放，当我们把所有的横向的小方格放完的时候，纵向的小方格一定是只有一种情况放进去的</p>

<p>比如 4*3 的时候，分别在左上和右下放置横向的方格，放完后，纵向格子没有其他选择，只有一种放法，只能一列一列放</p>

![image](https://github.com/user-attachments/assets/47f03c08-4b47-4b3e-8e32-cfc37d8bd7ed)

<p>所以<b>整个还原方式和横向方格的摆放方式是相等的</b>，因为当我们把所有的横向小方格摆好了之后，纵向方格只能顺次的摆好只有一种方案，</p>

<p>求横向的摆放方式，可以一列一列来求</p>

<p>摆放的时候，由于是 1*2 的小方格，每一列摆放的时候只会和上一列有关系</p>

<b>f(i, j)：现在要摆第i列，上一列伸出来的小方格的数量是j，上一列伸出来的小方格的那些行存储到f(i, j)中去，j是一个二进制数，如图是五列，故为 5 位二进制数，j = 0～31，表示上一列中那些列伸出了小方格，</b>

<p>关于f(i, j)如何转移：</p>

<p>比方说现在要算第i列的状态，枚举一下第i-1列的状态，</p>

![image](https://github.com/user-attachments/assets/4c6effec-0d89-49c5-b72c-7a16618540e8)

<p>判断一下这个状态能否转移过来，条件：</p>

*   j和j^(i-1)不能有冲突。从第 i-1 列伸到第 i 列的行不能冲突，可以用位运算来判断，(j & j^(i-1)是不是等于0
*   第 i-1 列，剩余的空白格子，所有连续的空白格子一定要是偶数，因为我们只枚举横向的格子，第 i-1 列已经枚举完了，剩余的格子一定要用纵向的格子来填，（j | j^(i-1)）不能存在连续奇数个零。

<p>满足这两个条件，就可以转移过来</p>

`f(i, j) += f(i-1, j^(i-1))`

<p>f(i, j)是看第 i 列，上一列往我这里捅出来的小方块是哪些行</p>

<p>时间复杂度：11 * 2^11 2^11 (两个11次方是 j 和 j^(i-1) 的枚举)</p>

<p>k就是j^(i-1)</p>

```
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 12, M = 1 << N; //1 左移N位

int n, m; //n行，m列
long long f[N][M];
bool st[M];

int main()
{
    while(cin >> n >> m, n || m)
    {
        memset(f, 0, sizeof f);
        
        for(int i = 0; i < 1 << n; i ++) //先预处理一下所有状态是不是不存在连续奇数个0
        {
            st[i] = true; //假设成立
            int cnt = 0; //当前这一段连续0的个数
            for(int j = 0; j < n; j++)
                if(i >> j & 1) //如果当前位为1，说明上一段已经截止了
                {
                    if(cnt & 1) st[i] = false; // 判断上一段连续的0是否有奇数个，如果有奇数个，则说明第 i 个状态不合法
                    cnt = 0; //清0
                }
                else cnt++ ;
                
            if(cnt & 1) st[i] = false; //判断最后一段0的个数
        }
        //DP
        f[0][0] = 1; //最开始的时候，什么都没有放也是一种方法
        for(int i = 1; i <= m; i++) //枚举列
            for(int j = 0; j < 1 << n; j++) //枚举状态，从 0 到 2^n
                for(int k = 0; k < 1 << n; k++) //枚举 i-1 列状态
                    if((j & k) == 0 && st[j | k]) //满足才能转移
                        f[i][j] += f[i - 1][k];
                        
        cout << f[m][0] << endl;                
    }
}

```

<p>枚举到第m列，第 m-1 没有捅出来任何 1*2 小方格才是合法的方案，这样从0到m-1列才是完整的序列</p>

</br>

## 最短Hamilton路径

</br>

![image](https://github.com/user-attachments/assets/85aad188-19f6-42ac-a3ce-677b62fb95f3)

<p>暴力来做要确定走过的顺序，枚举完之后还要求路径的长度所以乘n，时间的复杂度是(n! * n)，太高了</p>

<p>所以用状态压缩DP，用一个整数来表示状态</p>

<p>走过的所有的点存放到i当中，i就是一个压缩的状态</p>

<p>这里的状态计算就是一个分类讨论的过程，枚举倒数第二个点，根据倒数第二个点是那个点来分类</p>

<p>比如说倒数第二个点是k，那就是从 0 走到 k 再走到 j ，a[k, j]已知。</p>

`f(i ,j) = Min(f(i - {j}, k) + a(k ,j))`

    #include <cstring>
    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 20, M = 1 << N;

    int n;
    int w[N][N];
    int f[M][N];

    int main()
    {
        cin >> n;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cin >> w[i][j];
        
        memset(f, 0x3f, sizeof f);
        f[1][0] = 0; //目前是从 0 走到 0，只有一种走法
        
        for(int i = 0; i < 1 << n; i++)
            for(int j = 0; j < n; j++)
                if(i >> j & 1) //从零走到j，那么i一定要包含j，所以一定要有意义
                    for(int k = 0; k < n; k++) //枚举一下转移的状态，枚举他从哪个点转移过来
                    if((i - (1 << j)) >> k & 1) //如果说想从k点转移过来，那么i除去j这个点之后，一定要包含k这个点，所以第k位一定要是1才能走到第k位
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]);
                        
        cout << f[(1 << n) - 1][n - 1] << endl;
        return 0;
    }

</br>

# 树形DP

</br>

</br>

## 没有上司的舞会

</br>

![image](https://github.com/user-attachments/assets/64d8acf4-a86d-4279-8961-ed9c975bb8c1)

![image](https://github.com/user-attachments/assets/2de35be1-fd88-443a-b33a-d696e4878005)

![image](https://github.com/user-attachments/assets/c9dcd49c-afd0-44b2-9a16-7adf41cab21e)

<p>每个人的高兴度都是一，所以样例是让我们挑尽量多的点，使得挑的两个点之间没有一条边，有边的话就是有直接上司</p>

<p>树形DP思维跨度不高，但前提是适应树形DP的思维方式</p>

<p>状态有两个，一个是 f(u, 0) 一个是 f(u, 1)</p>

<p>求树形DP的时候，是从根节点递归求，递归到u节点的时候，先把 u 的儿子处理好，假设有两个儿子a， b。先算：</p>

`f(a, 0)    f(a, 1)    f(b, 0)    f(b, 1)`

<p>算完儿子后，再来算f(u, 0)，每个儿子都是独立的，想让整个最大首先让每个儿子最大，因为不选 u ，所以每个子树可以选择根节点，也可以选根节点</p>

    f(u, 0) = max(f(s1, 0), f(s1, 1)) + max(f(s2, 0), f(s2, 1)) + ... + max(f(sn, 0), f(sn, 1))

<p>算f(u, 1)，选了根节点u，就不选子树的根节点了</p>

    f(u, 1) = f(s1, 0) + f(s2, 0) + ... + f(sn, 0)

<p>时间复杂度：一共有2n个状态，所有儿子节点加到一块应该是等于边的数量，故为O(n)</p>

<p>树的存储就用前面图的存储就可以了，用邻接表就可以了</p>

    #include <cstring>
    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 6010;

    int n;
    int happy[N];
    int h[N], e[N], ne[N], idx;
    int f[N][2];
    bool has_father[N];

    void add(int a, int b)
    {
        e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
    }

    void dfs(int u)
    {
        f[u][1] = happy[u];
        
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int j = e[i];
            dfs(j);
            
            f[u][0] += max(f[j][0], f[j][1]);
            f[u][1] += f[j][0];
        }
    }

    int main()
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &happy[i]);
        
        memset(h, -1, sizeof h);
        
        //要自己求根节点，根节点就是没有父节点的点，所以开一个bool数组，判断是否有父节点
        //一共有 n - 1 条边
        for(int i = 0; i < n - 1; i++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            has_father[a] = true;
            add(b, a); //在邻接表中插入该边
        }
        
        int root = 1; //找父节点
        while(has_father[root]) root ++;
        
        dfs(root);
        
        printf("%d\n", max(f[root][0], f[root][1]));
        
        return 0;
    }

</br>

# 记忆化搜索

</br>

<p>记忆化搜索是DP的一种实现方式，递归写法，之前都是循环，按循环的顺序来求每一个状态</p>

<p>树形DP就是一般的实现方式</p>

</br>

## 滑雪

</br>

![image](https://github.com/user-attachments/assets/0ba0ed32-189b-4e42-9cda-3f29a49897b6)

<p>状态计算：f(i, j)按照第一步是朝那个方向(上下左右)滑的，把集合分为四类，f(i, j)为四类的最大值，假设向右滑，f(i, j) -> f(i, j + 1)。问题变为从(i, j + 1)开始滑的最大长度，再加上1，不是每一个情况都会存在，要进行判断</p>

<b>要递归做的话，有一个前提：这个图一定要是一个拓扑图，状态相互之间的依赖关系不能存在环</b>

    a -> b -> c -> a
    #不能算 a 用到 b ，算 b 用到 c ，算 c 用到 a 

<!---->

    #include <cstring>
    #include <iostream>
    #include <algorithm>

    using namespace std;

    const int N = 310;

    int n, m;
    int h[N][N];
    int f[N][N];

    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}; //上右下左

    int dp(int x, int y)
    {
        int &v = f[x][y];
        if(v != -1) return v; //如果f[x][y]已经被算过了
        
        //枚举一下上下左右的方向，使用偏移量
        v = 1; //必须要初始化，因为最次可以走当前的格子
        for(int i = 0; i < 4; i++)
        {
            int a = x + dx[i], b = y + dy[i];
            if(a >= 1 && a <= n && b >= 1 && b <= m && h[a][b] < h[x][y])
                v = max(v, dp(a, b) + 1);
        }
        return v;
    }

    int main()
    {
        scanf("%d%d", &n, &m);
        
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                scanf("%d", &h[i][j]);
                
        memset(f, -1, sizeof f);
        
        int res = 0;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                res = max(res, dp(i, j));
                
        printf("%d\n", res);
        
        return 0;
    }

<p>平常关注的是时间复杂度和空间复杂度，但还要考虑的最重要的一点是<b>代码复杂度</b></p>

<p>线性DP用循环还好说，但区间DP就难了，这个滑雪问题用循环更难了</p>





























































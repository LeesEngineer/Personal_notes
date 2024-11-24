# 贪心

</br>

<p>个人认为贪心比DP难，因为证明他的正确性太难了</p>

<p>没有套路也没有模板，DP至少有个套路</p>

<p>贪心是在当前的情况下选看起来最好的</p>

![image](https://github.com/user-attachments/assets/8cf41647-6247-4cec-952e-22fd93d43395)

<p>根据图，每次都选择一个局部最优解(这里是选择一个比较高的点走过去)，最后可以走到最大点，只有是在单峰的情况下才可以走到最大点，如果是多峰的情况下就不一定走到全局最优解(而是局部最优解)</p>

<p>从局部最优不一定能到全局最优，<b>所以单峰的问题适合用贪心算法，多峰问题不适合用贪心算法</b></p>

<p><b>最后是证明算法的正确性</b></p>

<p>按照数学上证明A = B，就是证明 A >= B 和 A <= B</p>

<hr>

</br>

# 区间问题

</br>

<p>有关区间的问题是贪心的一个大类型</p>

<p>可以先试几个做法，区间问题第一步无外乎就是排序：<b>要么是按左端点排序，要么是右端点排序，要么就是双关键字排序。</b></p>

<p>这里是按右端点排序</p>

## 区间选点

![image](https://github.com/user-attachments/assets/92ce6550-b108-4f82-aabf-8fe1b20c1012)

1. **将每个区间按照右端点从小到大排序**
2. **从前往后依次枚举每个区间**
- 如果当前区间中已经包含点，则直接pass
- 否则，选择当前区间的右端点（选择当前看起来最好的情况，比较短视的行为）

<p>按照这个思路来说，每个区间都至少会包含一个点，所以当前方案是一种合法方案，</p>

<p>假设ans为最小解，cnt为一种合法方案</p>

1. 所以一定有：ans <= cnt
2. 证明 ans >= cnt：首先第一个区间一定是被选的，选其右端点，下一个选择的区间在上一个的右侧，一定没有交集，以此类推，第三个选择的区间一定是在第二个选择的区间的右侧，而且也没有任何交集，所以我们找到了cnt个区间，这些区间是从左到右依次排好，并且两两之间没有任何交集，所以找到了cnt个没有交集的区间，如果想把它们覆盖掉的话，至少需要cnt个点（因为没有任何交集）。
3. 所以 ans = cnt

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;
struct Range
{
    int l, r;
    bool operator< (const Range &w) const
    {
        return r < w.r;
    }
}range[N];

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        range[i] = {l, r};
    }

    sort(range, range + n);

    int res = 0, end = -2e9; //不能用-2e7
    for(int i = 0; i < n; i++)
        if(range[i].l > end)
        {
            res++;
            end = range[i].r;
        }

    printf("%d", res);
}
```

</br>

## 最大不相交区间数量

</br>

<p>两个问题的做法是完全一样的，也是先按照右端点排序，再枚举每一个区间，如果当前区间有点则pass，没有点则选择该区间的左端点，那么选择的点的数量就是我们最大的不相交区间数量</p>

<p>证明 ans = cnt</p>

1. ans >= cnt ：第一个点一定严格在 x1 的右端点，第二个点一定严格在 x2 的右端点，以此类推，按照这种方式的解 cnt 一定是一种可行的方案，得证。

![35373ad75ab31822b84611698fdd81c3](https://github.com/user-attachments/assets/fd62fa90-795b-4808-90f2-4a3e10228f60)

2. ans <= cnt 反证法：假设 ans > cnt ，意味着可以选出比 cnt 更多个不相交的区间，但 cnt 个点已经把区间包含了，每个区间都至少包含一个点。但如果有大于 cnt 的解，那么我们至少就要选出来 cnt + 1 （即 ans ）个点来覆盖掉区间，这与实际情况不符，因为 只需要 cnt 就够了，矛盾构成

3. ans = cnt

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;

struct Range
{
    int l, r;
    bool operator< (const Range &w) const
    {
        return r < w.r;
    }
} range[N];

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        range[i] = {l, r};
    }

    sort(range, range + n);

//y总的答案
    int ans = 0;
    int end = -2e9;
    for(int i = 0; i < n; i++)
    {
        if(end < range[i].l)
        {
            ans ++;
            end = range[i].r;
        }
    }

//我的答案，感觉我的才对
    int ans = 0;
    int end = range[0].r;
    for(int i = 1; i < n; i++)
    {
        if(end < range[i].l)
        {
            ans ++;
            end = range[i].r;
        }
    }

    printf("%d", ans);
    return 0;
}
```

</br>

## 区间分组

</br>

<p>贪心思路：</p>

1. 将所有区间按左端点从小到大排序
2. 枚举每个区间，判断能否将其放到某个现有的区间 (L[i] > Max_r 放不进)
- 不存在这样的组，开一个新的组，放入该区间
- 存在这样的组，放进组内，并更新该组的 Max_r

<p>证明：</p>

1. ans <= cnt:一定是一个合法的方案，因为这样来看，所有组内的区间都没有交集。
2. ans >= cnt:假设一共有 cnt 个组，当开最后一个组（第 cnt 个组）的时候，枚举到第 i 个区间的时候，发现与前面的组中的区间都有交集。有交集的含义：Max_r 是当前组右端点的最大值，有Max_r >= L[i]，在有一个点是，枚举区间的时候是按照左端点从小到大枚举的，第 i 个区间在前面所有区间之后才加进去，所有所有区间的左端点一定小于等于 L[i] ，左端点小于等于 L[i] ，右端点大于等于 L[i]，故有交集。同理对于前面的 cnt - 1 个组都能找到这样的区间使 L[i] 在区间上面。<b>算上当前的第 i 个区间，一共找到 cnt 个区间有公共点即 L[i] ，整个区间交集不为空，因此不管怎么分，所有合法方案，这 cnt 个区间一定不会被分到一组里面（每一个区间都要在一个单独的组里面），所以 ans >= cnt </b>

<p>判断是否有组满足 Max_r < L[i] ，可以用小根堆来做，如果所有组的 Max_r 的最小值满足条件，那就找到了这样的组。</p>

<p><b>动态的维护最小值可以用堆来做，时间还小</b></p>

```
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int N = 100010;

int n;
struct Range
{
    int l, r;
    bool operator< (const Range &w) const
    {
        return l < w.l;
    }
} range[N];

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        range[i] = {l, r};
    }

    sort(range, range + n);

    priority_queue<int, vector<int>, greater<int>> heap;
    for(int i = 0; i < n; i++)
    {
        auto r = range[i];
        if(heap.empty() || heap.top() >= r.l) heap.push(r.r);
        else
        {
            int t = heap.top();
            heap.pop();
            heap.push(r.r);
        }
    }
    printf("%d\n", heap.size());
    return 0;
}
```

</br>

## 区间覆盖

</br>

<p>贪心思路：</p>

1. 将所有区间按照左端点从小到大排序。
2. 从前往后 枚举区间，在所有能覆盖 start 的区间当中，选择一个右端点最大的区间，更新 start 为该区间的右端点。

<p>证明（先不考虑无解）：</p>

1. ans <= cnt : 为一种可行方案，故成立。

2. ans >= cnt : 从前往后找第一个不一样的区间。假设是第 i 个区间，按照我们的算法，cnt 组的该区间的右端点一定不在 ans 组该区间右端点的左侧，所以可以把 ans 的 i 区间替换为我们 cnt 的 i 区间，对于 ans 组替换前 i + 1 区间的左端点一定在 i 区间右端点的左侧，替换后更是如此。每一步替换法不会增加解的值，以此类推，跳出这道题，单看这个逻辑，可能会在 cnt 还没有枚举完时 ans 以枚举完并且覆盖了整个区间，故有 ans >= cnt 。我们可以把任何一个解调整成我们当前的方案（包括最优解），得证

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;
struct Range
{
    int l, r;
    bool operator< (const Range &w) const
    {
        return l < w.l;
    }
} range[N];

int main()
{
    int st, ed;
    scanf("%d%d", &st, &ed);
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        range[i] = {l, r};
    }

    sort(range, range + n);

    int res = 0;
    bool success = false;
    for(int i = 0; i < n; i++)
    {
        int j = i; //双指针算法
        int r = -2e9;
        while(j < n && range[j].l <= st)
        {
            r = max(r, range[j].r);
            j++;
        } //枚举所有左端点在 start 左边的区间的右端点的最大值是多少

        if(r < st)
        {
            res = -1;
            break;
        }

        res ++;
        
        if(r >= ed)
        {
            success = true;
            break;
        }

        i = j - 1;
        st = r;
    }

    if(!success) res = -1;
    printf("%d", res);

    return 0;
}
```

</br>

# Huffman Tree

</br>

</br>

## 合并果子

</br>

![cd3712bb99807f6bbfc2ba0a45445372](https://github.com/user-attachments/assets/37369872-0a07-46da-9159-3b87afab3950)

![834904de995c50273970ad9bdd8f410f](https://github.com/user-attachments/assets/2c18463d-d8e5-4aad-b4f4-5c3732e1e5e4)

<p>经典的哈夫曼树，一个完全二叉树，叶子结点是我们要合并的数，内部节点是合并过的数<p>

![24465a6731df27e173e6160b98288076](https://github.com/user-attachments/assets/3dcfe57d-6111-4020-af29-fb3fae1469cb)

<p>消耗的总和是: a+b + c+d + a+b+c+d + e+f + a+b+c+d+e+f</p>

<p>a 会被算三次，这个是和他的路径长度相关的: 3a + 3b + 3c + 3d + 2e + 2f，我们要在所有的完全二叉树里面挑一个权值最小的树</p>

<p>贪心思路：每一次挑出来最小的两堆来合并</p>

<p>证明：</p>

1. 最小的两个数，深度一定最深，而且可以互为兄弟：意味着我们可以在第一步把它们合并，且合并两个最小点一定可以得到最优解
-（反证法）假设最小的两个点一个是 a 一个是 f ，那么一定可以把 b 和 f 交换，总和一定变小，交换前 2f + 3b 交换后 3f + 2b 权值一定变小。
- 如上图，abcd 是最小的一共有三种组合情况都是可以的 ab ac ad，因为整个权值是与深度有关系的，如果在同一层深度不变，那么权值也不变。

2. 如果一直贪心式的合并能否得到全局最优解，第一步贪心是对的，但在第一步贪心的基础上再贪心还是对的吗。如果有 n 个果子，第一步贪心之后有 n - 1 个果子，对于 n - 1 的这颗树，一定是挑最小的两个点来合并，对于 n - 1 来说是最优解，但<b>n - 1 的最优解不一定是 n 的最优解（不证明了）。</b>证明贪心思路：先来看 n 的情况，假设为 n 个点的原始问题，ab 为最小的点，先来合并 ab 一定是可以得到最优解的，<b>前面证明了，合并最小的两个点一定可以得到最优解</b>，得到了新哈夫曼树 n - 1。把 n - 1 树合并的最小值定为 f(n-1)，则 f(n) = f(n-1) + a + b。所有合并树的第一步都是合并最小的两个点，得到解

<p>每次求最小解都可以用堆来做</p>

```
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    
    priority_queue<int, vector<int>, greater<int>> heap;
    while(n --)
    {
        int x;
        scanf("%d", &x);
        heap.push(x);
    }
    
    int res = 0;
    while(heap.size() > 1) //对于一颗树，合并次数一定是 n - 1，也可以用 for 来实现
    {
        int a = heap.top(); heap.pop();
        int b = heap.top(); heap.pop();
        res += a + b;
        heap.push(a + b);
    }
    
    printf("%d", res);
    return 0;
}
```

</br>

# 排序不等式

</br>

## 排队打水

</br>

<p>人数 3 6 1 4 2 5 7 </p>

<p>等待总时间 3*6 6*5 1*4 4*3 2*2 5*1 </p>

<p>总时间 = t1*(n-1) + t2*(n-2) + ... + t(n-1)*1</p>

<p>把乘的数看作是权重，让大数值乘以小权重</p>

<p>按照从小到大的顺序排序，总时间最小</p>

<p>证明：（调整法）假设最优解不是从小到大排好序的，必然存在两个相邻的元素，前一个比后一个大，ti > t(i+1) 此时交换一下二者位置，<b>交换前后对其他元素不会产生影响</b>，之后影响二者的时间</p>

`前为：ti * (n-i) + t(i+1) * (n-i-1)`

`后为：t(i+1) * (n-i) + ti * (n-i-1)`

<p>交换后总时间降低</p>

```
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010;

int n;
int t[N];

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &t[i]);
    
    sort(t, t + n);
    
    LL res = 0;
    for(int i = 0; i < n; i ++) res += t[i] * (n - i - 1);
    
    printf("%lld", res); //注意这里！！！
    return 0;
}
```

</br>

# 绝对值不等式

</br>

## 货仓选址

</br>

`f(x) = |x1 - x| + |x2 - x| + ... + |xn - x|`

<p>求其最小值：猜是中位数</p>

<p>用分组的概念，第一组和第 n 组，第二组和第 n - 1 组，以此类推</p>

```
f(x) = (|x1 - x| + |xn - x|) + (|x2 - x| + |x(n-1) - x|) + ......
     >= xn - x1 + x(n-1) - x2 + ...... 
````

<p>对每一个单独的一项要取到等号，要求 x 在 xi 和 x(n-i+1) 之间。所以要取整体的最小值，要取 x 为整个序列的中位数或两个相等的中位数之间。此时取到等号。</p>

```
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;
int a[N];

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    
    sort(a, a + n);
    
    int res = 0;
    for(int i = 0; i < n; i++) res += abs(a[i] - a[n/2]);
    
    printf("%d", res);
    return 0;
}
```










































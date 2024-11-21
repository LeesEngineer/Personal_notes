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











































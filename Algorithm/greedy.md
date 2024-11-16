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







































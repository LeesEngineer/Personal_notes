# 快速排序

</br>

<p>快排的思想是基于分治的</p>

1. 确定分界点：q[l], q[(l + r) / 2], q[l], 随机

2. 调整区间：使得第一个区间里面的数都小于等于 x，第二个区间里面的数都大于等于 x

3. 递归处理左右两端

<p>第二步最难理解</p>

<p>有一个简单的，但会额外用到一些区间：开两个数组 a，b 扫描区间 q[l ~ r]，如果 q[i] <= x ，则 x -> a[]，若 q[i] > x，则 x -> b[]，在把 a 和 b 中的数分别放进 q[] 中</p>

<p>还有一个优美的做法：双指针</p>

```
#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int n;
int q[N];

void quick_sort(int q[], int l, int r)
{
    if(l >= r) return;
    
    int x = q[l], i = l - 1, j = r + 1; //数据加强前应该是 q[l + r >> 1]，但会被卡数据
    //用的是 do while，故这里取的是边界的两侧
    
    while(i < j)
    {
        do i ++ ; while (q[i] < x);
        do j -- ; while (q[j] > x);
        
        if(i < j) swap(q[i], q[j]);
    }
    
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++ ) scanf("%d", &q[i]);
    
    quick_sort(q, 0, n - 1);
    
    for(int i = 0; i < n; i ++ ) printf("%d ", q[i]);
    
    return 0;
}
```

</br>

```
quick_sort(q, l, j);
quick_sort(q, j + 1, r);
```

<p>这里也可以写 i，因为完全对称，j 换为 i - 1，j + 1 换为 i，但没有完，写 i 的话要注意，<b>int x = q[l] 这里不能用 l 否则会有边界问题，可以写 r，否则会死循环</b></p>

<b>用i则不能取到左边界，把x取值改成向上取整（l + r + 1 >> 1）。用j则不能取到右边界，把x取值改成向下取整（l + r >> 1）。</b>

<p>讨论一下死循环的样例</p>

```
2
1 2
```

<p>开始时，i 指向 1，j 指向 2，x = 1</p>

<p>第一个点不满足小于 x，停住。第二个点满足大于 x，j --，此时两个指针相遇停下来，i = 0</p>

<p>看一下 i = 0 此时的执行：quick_sort(q, 0, -1) 结束，quick_sort(q, 0, 1) 死循环</p>

</br>

<p>正常时快排是不稳定排序的，原因在于会有值相同的情况，想要稳定的话可以用一个 pair<int, int> 进行<b>双关键字排序</b>（pair的operator 先根据 first 再根据 second 排序），这样的话<b>所有值都不相同了</b></p>

</br>

# 归并排序

</br>

<p>归并排序是稳定排序的，所以再合二为一的时候如果遇到l[i] == r[j]，把 l[i] 加入到原数组中</p>

<p>分治的方法和快排不一样，以整个数组的中间部分来分，分为左边和右边</p>

1. 确定分界点：mid = (l + r) / 2

2. 递归排序left， right

3. 归并————合二为一（双指针算法）

```
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int f[N], tmp[N];

void merge_sort(int q[], int l, int r)
{
    if(l >= r) return;
    
    int mid = l + r >> 1;
    
    merge_sort(q, l, mid), merge_sort(q, mid + 1, r);
    
    int k = 0, i = l, j = mid + 1;
    while(i <= mid && j <= r)
    {
        if(q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];
        else tmp[k ++ ] = q[j ++ ];
    }
    while(i <= mid) tmp[k ++ ] = q[i ++ ];
    while(j <= r) tmp[k ++ ] = q[j ++ ];
    
    for(int i = l, j = 0; i <= r; i ++ , j ++ ) q[i] = tmp[j];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++ ) cin >> f[i];
    
    merge_sort(f, 0, n - 1);
    
    for(int i = 0; i < n; i ++ ) cout << f[i] << " ";
    
    cout << endl;
    
    return 0;
}
```



































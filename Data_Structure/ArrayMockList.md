<p>如果开一个结构体的话会涉及到 new ，new 非常慢，当涉及到十万百万级的数据的时候就会考虑用数组模拟链表</p>

</br>

# 数组模拟模拟单链表

</br>

<p>单链表最大的用途是用来写邻接表，邻接表主要用来存储图和树</p>

```
#include <iostream>

using namespace std;

const int N = 100010;

int head, e[N], ne[N], idx;

void init()
{
    head = -1;
    idx = 0;
}

void add(x)
{
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx ++ ; //头插法
}

void insert(int k, int x)
{
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx ++ ;
}

void remove(int k) //头节点另外考虑
{
    ne[k] = ne[ne[k]];
}
```

</br>

# 数组模拟模拟双链表

</br>

<p>用来优化某些问题</p>

<p>双链表：可以偷个懒，不定义 head，让下标为 0 的点为 head，下标为 1 的点为 tail</p>

```
#include <iostream>

using namespace std;

const int N = 100010;

int e[N], l[N], r[N], idx;

void init()
{
    r[0] = 1, l[1] = 0;
    idx = 2; //从二开始
}

void add(int k, int x) //在第 k 个点的右边插入
{
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx; //别写反了 
    r[k] = idx;
}

void remove(int k)
{
    
}
```





























联通分量：对于一个有向图，任意两点 u, v 必然可以从 u 走到 v，且从 v 走到 u。

强联通分量：在一个有向图中，如果一组顶点之间任意两个顶点都能互相到达，并且无法再加入其他顶点而保持这一性质，那么这组顶点就构成一个强连通分量。

强连通分量可以通过缩点的方式，可以将任意一个有向图转换成有向无环图(拓扑图 DAG)。缩点是指将所有的连通分量缩成一个点

有向无环图的好处：求最短路或者最长路的时候按照拓扑序可以直接递推。O(n + m)

<hr>

一般按照 DFS 的顺序去求强连通分量。把边分为四类

1. 树枝边：DFS过程中首次访问新顶点所经过的边 (x, y)

2. 前向边：从当前顶点指向其DFS子孙节点的边，但不是树边。（树枝边是一种特殊的前向边）(x, y)

3. 后向边：从当前顶点指向其DFS祖先节点的边 (x, y)

4. 横叉边：连接两个不存在祖先与子孙关系的顶点的边（连向之前搜过的其他分支的边） (x, y)

<hr>

判断 x 是否在一个强连通分量中

1. 存在后向边指向祖先节点

2. 先走到横叉边，再走到祖先节点。LCA 

对于一个前向边是不会构成回路的

<hr>

<img width="492" height="552" alt="QQ_1792852198054" src="https://github.com/user-attachments/assets/53d38f86-fa31-4cd5-a8cd-139b34fbbce8" />

# Tarjan 求 SCC 

对每个点定义两个时间戳，搜索的时候按照 DFS 的顺序给每个点一个编号。对于树枝边和前向边 y > x，后向边和横向边 x > y

1. dfn[u]: 遍历到 u 的时间戳

2. low[u]: 从 u 开始走，所能遍历到的最小时间戳

求一个强连通分量的时候，求的是最上面的一个点。如果 u 是其所在的强连通分量的最高点，等价于 dfn[u] == low[u]。

<b>当 dfn[u] == low[u] 时，说明以 u 为根的强连通分量，无法通过 DFS 搜索过程中允许的路径，回到任何仍在栈中且 dfn 比 u 更小的祖先节点。</b>

```
void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[++ top] = u, in_stk[u] = true;
    
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if(in_stk[j])
            low[u] = min(low[u], dfn[j]);
    }
    
    if(dfn[u] == low[u])
    {
        int y;
        ++ scc_cnt;
        do
        {
            y = stk[top --];
            in_stk[y] = false;
            id[y] = scc_cnt;
        }
        while(y != u)
    }
}
```

O(n + m)

<b>Tarjan 算法中的栈保存的是：已经被 DFS 访问过，但尚未被确定归属于某个 SCC 的节点。</b>且因为横叉边的存在，不单单只存路径上的值

<b>如果一个点仍在 Tarjan 栈中，说明它所属的 SCC 尚未被完整弹出。整个 SCC 弹出栈的顺序是逆拓扑序的</b>

<hr>

之所以是如下的写法

```
else if(in_stk[j])
    low[u] = min(low[u], dfn[j]);
```

是因为 dfn 和 low 是严格按照 DFS 顺序的

<hr>




















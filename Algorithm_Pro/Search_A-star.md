目标是为了求起点到终点的最短距离，但可能有一个非常庞大的状态空间（1e7-1e8）。为了高效的求出最短距离，假如一个启发函数

把 BFS 中的队列换成优先队列（小根堆），根据 真实距离 + 估计距离

```
while(!q.empty())
{
    t <- 优先队列的队头
    当终点第一次出队时，break
    for(t的所有邻边)
        邻边入队
}
```

形式上像 Dijkstra。A-star 可以处理所有非负权回路。要使用 A* 必须要有解，否则也会遍历整个状态空间，而且还会不如 BFS，因为用的是堆。

A-star 正确的条件：设 d(state) 为起点到state的真实距离，g(state) 为state到终点的真实距离。d(state) + g(state) 为起点到终点的真实距离。设 f(state) 为state到终点的估计距离。d(state) + f(state) 为估计总长度。A-star 正确的条件是 f(state) <= g(state)。这样终点出队的时候才是对的

若 T 出队列时不是最小值，dist > d最优。此时队列中肯定存在最优解中的某一个点 u。因为 f(state) <= g(state)。d(u) + f(u) <= d(u) + g(u) = d最优。dist > d最优 >= d(u) + f(u) 矛盾了

<hr>

可以用反证法，严格证明 u 一定存在。

固定一条最优路径：

\[
S=v_0\rightarrow v_1\rightarrow\cdots\rightarrow v_k=T
\]

把一个节点“以正确距离出堆并完成展开”称为完成。

现在考虑：终点 T 即将以错误距离出堆之前。

沿最优路径从 S 向 T 找，取第一个还没有完成的节点，记为 \(u\)。它一定能找到，因为 T 还没有以正确距离完成。

接下来证明：这个 \(u\) 此时就在堆里，且距离正确。

情况一：u 就是 S。

S 初始化时就以 \(g(S)=0\) 入堆。如果它还没完成，就仍在堆里，结论成立。

情况二：u 不是 S。

设 u 在这条路径上的前一个节点是 p：

\[
S\rightarrow\cdots\rightarrow p\rightarrow u\rightarrow\cdots\rightarrow T
\]

因为 u 是第一个没有完成的节点，所以 p 已经以正确距离完成展开，即当时：

\[
g(p)=d^*(p)
\]

展开 p 时，一定会松弛边 \(p\rightarrow u\)，得到：

\[
g(p)+w(p,u)=d^*(p)+w(p,u)=d^*(u)
\]

最后这个等号成立，是因为最优路径的每一段前缀也是最短路径。

所以，u 最迟在 p 完成展开时，就已经以正确距离入堆了。

现在问：这份正确的入堆记录，是否已经出堆？

- 如果还没出堆：它现在就在堆里，正是我们要找的 u。

- 如果已经出堆并展开：u 就已经“完成”，与选取 u 时“还没有完成”矛盾。

因此，u 必然仍在堆中，而且：

\[
\boxed{g(u)=d^*(u)}
\]

这个证明的核心就是：选最优路径上第一个尚未以正确距离展开的节点。它的前驱已经把正确距离传给它，而它还没有把这份正确记录取出。

前提仍然是：发现更短距离时允许重新入堆，不能因为节点以前以错误距离展开过，就永久拒绝更新。

<hr>

第一次出队取到最短距离只对终点成立，对其他点不成立。

<img width="2158" height="352" alt="QQ_1792203317203" src="https://github.com/user-attachments/assets/19f37a42-84ce-4abd-9dfd-0820c2d3ee6c" />

最后之所以会拨乱反正，是因为最多走到终点时他不是最短路径，因此距离严格大于最优解的。我们的估计距离为 L 的点，他的距离加上估计值 L 是小于等于最优解的。此时就是发现走错了。也可能在路径上发现。

在 A* 中每个点可能不止被扩展一次

<hr>

八数码问题

八数码如果逆序对数量为奇数一定无解

代价设计为当前状态每一个点与他目标位置的曼哈顿距离之和

```
#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

typedef pair<int, string> PIS;

int f(string state)
{
    int res = 0;
    for(int i = 0; i < state.size(); i ++)
        if(state[i] != 'x')
        {
            int t = state[i] - '1';
            res += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
        }
    return res;
}

string bfs(string start)
{
    string end = "12345678x";
    char op[] = "urdl";
    
    unordered_map<string, int> dist;
    unordered_map<string, pair<char, string>> prev;
    priority_queue<PIS, vector<PIS>, greater<PIS>> heap;
    
    dist[start] = 0;
    heap.push({f(start), start});
    
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        
        string state = t.second;
        if(state == end) break;
        
        int x, y;
        for(int i = 0; i < 9; i ++)
            if(state[i] == 'x')
            {
                x = i / 3, y = i % 3;
                break;
            }
            
        string source = state;
        
        for(int i = 0; i < 4; i ++)
        {
            int a = x + dx[i], b = y + dy[i];
            if(a < 0 || a >= 3 || b < 0 || b >= 3) continue;
            state = source;
            swap(state[x * 3 + y], state[a * 3 + b]);
            if(!dist.count(state) || dist[state] > dist[source] + 1)
            {
                dist[state] = dist[source] + 1;
                prev[state] = {op[i], source};
                heap.push({dist[state] + f(state), state});
            }
        }
    }
    
    string res;
    while(end != start)
    {
        res += prev[end].first;
        end = prev[end].second;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    string start, seq;
    char c;
    
    while(cin >> c)
    {
        start += c;
        if(c != 'x') seq += c;
    }    
    int cnt = 0;
    for(int i = 0; i < 8; i ++)
        for(int j = i; j < 8; j ++)
            if(seq[i] > seq[j])
                cnt ++;
    
    if(cnt & 1) puts("unsolvable");
    else cout << bfs(start) << endl;
    
    return 0;
}
```
















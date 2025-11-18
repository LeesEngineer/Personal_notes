# Brute-force version

</br>

<p>Assume that S[N] is the original string. p[M] is the pattern string.</p>

```
for(int i = 1; i <= n; i ++)
{
    bool flag = true;
    for(int j = 1; j <= m; j ++)
        if(s[i] != p[j])
        {
            flag = false;
            break;
        }
}
```

</br>

# Optimized version

</br>

<p>We need to preprocess the pattern : For each position, we compute the maximum length of the suffix ending at the position that matches a prefix of the pattern string. This is the meaning of the "next" array.</p>

```
next[i] == j
=>
p[1, j] = p[i - j + 1, i]
```

<img width="1328" height="342" alt="QQ_1763447157472" src="https://github.com/user-attachments/assets/3e427026-7572-4062-a0a9-506da621cbec" />

<p>The part before s[i-1] is equal to the part before p[j]. When s[i] isn't equal to p[j + 1], we need to move pattern string forward and we need to determine the minimum number of the position to move forward. <b>We can just use next[j] to obtain this minimum number.</b></p>

<img width="1334" height="432" alt="QQ_1763448416730" src="https://github.com/user-attachments/assets/f4a195eb-99fb-471a-aa78-0a86c722f135" />

<p>Before and after the shift, the correspondence changes from i-1 matching j to i-1 match next[j].</p>

<p>After shifting, we can check whether s[i] and p[next[j] + 1] are equal. If they are not equal, we can complete this task recursively</p>

<p>Example : KMP STRING</p>

```
#include <iostream>

using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;

int n, m;
char p[N], s[M];
int ne[N];

int main()
{
    cin >> n >> p + 1 >> m >> s + 1;
    
    for(int i = 2, j = 0; i <= n; i ++)
    {
        while(j && p[i] != p[j + 1]) j = ne[j];
        if(p[i] == p[j + 1]) j ++;
        ne[i] = j;
    }
    
    for(int i = 1, j = 0; i <= m; i ++)
    {
        while(j && s[i] != p[j + 1]) j = ne[j];
        if(s[i] == p[j + 1]) j ++;
        if(j == n)
        {
            printf("%d ", i - n + 1 - 1);
            j = ne[j];
        }
    }
}
```




































































































































































































































































































































































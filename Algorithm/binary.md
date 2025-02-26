# 整数二分

</br>

<p>二分是个很蛋疼的问题，整数二分有很多边界问题</p>

<p>有两个模板，适用于不同的情况</p>

```
//区间[l, r]被划分为[l, mid]和[mid + 1, r]
int binary_1(int l, int r);
{
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}
```

```
//区间[l, r]被划分为[l, mid - 1]和[mid, r]
int binary_2(int l, int r)
{
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}
```

<p>二分的本质是寻找边界：在区间上定义了某种性质，使得性质在右半边是满足的，左半边区间是不满足的，被一分为二。那么二分就可以寻找性质的边界，既可以寻找左边界，也可以寻找右边界，而这就涉及到两个不同的模板了</p>

![c0c5336845f98a1b54a640dec80c5fde](https://github.com/user-attachments/assets/d07bbab7-3840-4342-b0ee-183e502a5078)

</br>

# 浮点数二分

</br>

<p></p>


































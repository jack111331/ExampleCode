#include <iostream>
#define N 20000
#define NLOGN 15*20000
using namespace std;
int lc[NLOGN], rc[NLOGN];
int val[NLOGN];
int tot = 0;
int arr[N] = {0, 7, 2, 4, 3, 10, 20, 5};
void Pull(int ind)
{
    val[ind] = val[lc[ind]] + val[rc[ind]];
    //更新節點資訊
}
int Build(int L, int R)
{
    int ind = ++tot;
    //索引 index
    if(L == R)
    {
        val[ind] = arr[L];
        //遞迴到葉節點時賦值
    }
    else
    {
        int mid = (L+R)>>1;
        lc[ind] = Build(L, mid);
        rc[ind] = Build(mid+1, R);
        //在非葉節點時 遞迴建樹
        //左子樹的位置更新為 Build回傳之左子樹索引值
        //右子數.....
        Pull(ind);
        //蒐集子樹資訊 更新節點資訊
    }
    return ind;
}
void Modify(int rootind, int L, int R, int i, int value)
{
    if(L == R)
    {
        val[rootind] = value;
        //更新葉節點資訊
    }
    else
    {
        int mid = (L+R)>>1;
        if(i <= mid)
        {
            Modify(lc[rootind], L, mid, i, value);
        }
        else
            Modify(rc[rootind], mid+1, R, i, value);

        Pull(rootind);
    }
}
int query(int rootind, int L, int R, int ql, int qr)
{
    /*
    這種寫法的話因為他統一都是在葉節點時才會回傳值, 那這樣的query時間複雜度會爛掉
    因為線段樹的精ㄙㄨㄟ(這字我Linux的fcitx居然打不出來OAO 不是2聲麻冏)在於:
    當當前節點有你要的資訊時, 因為在Build, Modify時已經預處理過了, 所以直接用處理過的結果可以省很多時間
    if(ql > R || qr < L)
    {
        return 0;
    }
    if(L == R)
    {
        return val[rootind];
    }
    if(ql <= L && qr >= R)
    {
        int mid = (L+R)>>1;
        return query(lc[rootind], L, mid, ql, qr) + query(rc[rootind], mid+1, R, ql, qr);
    }
    */
    if(ql > R || qr < L)
    {
        return 0;
    }
    if(ql <= L && qr >= R)
    {
        return val[rootind];
    }
    int mid = (L+R)>>1;
    if(qr <= mid)
    {
      return query(lc[rootind], L, mid, ql, qr);
    }
    else if(ql >= mid+1)
    {
      return query(rc[rootind], mid+1, R, ql, qr);
    }
    return query(lc[rootind], L, mid, ql, qr) + query(rc[rootind], mid+1, R, ql, qr);

}
int main()
{
    int root = Build(1, 7);
    Modify(root, 1, 7, 4, 300);
    cout << query(root, 1, 7, 2, 5) << endl;
}

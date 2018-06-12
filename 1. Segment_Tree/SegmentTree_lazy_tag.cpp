#include <iostream>
using namespace std;

typedef struct Seg
{
  int val;
  int tag;//懶標記
  Seg * lc, * rc;
  Seg(){val=tag=0;lc=rc=NULL;}
  void Pull()
  {
    val = lc->val + rc->val;
  }
}Tree;

int a[11] = {-1, 10, 9, 2, 4, 6, 1, 22, 31, 4, 5};

Tree * Build(int L, int R)
{
  Tree * Node = new Tree();
  if(L == R)
  {
    Node->val = a[L];
  }
  else
  {
    int mid = (L+R)>>1;
    Node->lc = Build(L, mid);
    Node->rc = Build(mid+1, R);
    Node->Pull();
  }
  return Node;
}
void Push(Tree * Node, int L, int R)
{
  //推懶標記
  // L Shouldn't equal to R
  // or there would be no lc and rc
  if(Node->tag && L != R)
  {
    Node->lc->tag += Node->tag;
    Node->rc->tag += Node->tag;

    int mid = (L+R) >> 1;
    Node->lc->val += Node->tag * (mid - L + 1);//將懶標記往左子樹推  L ~ mid 有 mid - (L-1)個
    Node->rc->val += Node->tag * (R - mid);//將懶標記往右子樹推, mid+1 ~ R 有 R - ((mid+1)-1)個
  }
  Node->tag = 0;//清除自身懶標記
}
//區間修改
void Modify(Tree * Node, int value, int L, int R, int ql, int qr)
{
  if(ql > R || qr < L)
  {
    return;
  }
  if(ql <= L && qr >= R)
  {
    Node->tag += value;//附加懶標記
    Node->val += value * (R - L + 1);
    return;//當推懶標記到目標區間以內時, 停止推的動作
  }
  Push(Node, L, R);//推懶標記
  int mid = (L+R) >> 1;
  Modify(Node->lc, value, L, mid, ql, qr);
  Modify(Node->rc, value, mid+1, R, ql, qr);
  Node->Pull();//更新節點
}

int Query(Tree * Node, int L, int R, int ql, int qr)
{
  if(ql > R || qr < L)
  {
    return 0;
  }
  if(ql <= L && qr >= R)
  {
    return Node->val;
  }
  Push(Node, L, R);//推懶標記
  int mid = (L+R) >> 1;
  return Query(Node->lc, L, mid, ql, qr) + Query(Node->rc, mid+1, R, ql, qr);
}
int main()
{
  Tree * Node = Build(1, 10);
  Modify(Node, 5, 1, 10, 2, 4);//修改2 ~ 4
  cout << Query(Node, 1, 10, 1, 6) << endl;
}

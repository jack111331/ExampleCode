#include <iostream>
using namespace std;
//線段數資料結構 在這邊是求區間總和
typedef struct SegmentTree
{
  int val;
  SegmentTree * lc, * rc;
  SegmentTree(){val = 0;lc = rc = NULL;}
  void Pull()
  {
    val = lc->val + rc->val;
  }
}Tree;

int a[11] = {-1, 4, 6, 1, 2, 3, 6, 7, 9, 10, 5};
//建樹
Tree * build(int L, int R)
{
  Tree * Node = new SegmentTree();
  if(L == R)
  {
    Node->val = a[L];
    //遞迴到葉節點時賦值
  }
  else
  {
    int mid = (L+R)>>1;
    Node->lc = build(L, mid);
    Node->rc = build(mid+1, R);
    //在非葉節點時 遞迴建樹
    Node->Pull();
    //蒐集子樹資訊 更新節點資訊
  }
  return Node;
}
void Modify(Tree * Node, int value, int L, int R, int i)
{
  if(L == R)
  {
    Node->val += value;
    //遞迴到目標葉節點時 把值加上去
    return;
  }
  int mid = (L+R)>>1;
  if(i <= mid)
    Modify(Node->lc, value, L, mid, i);
  else
    Modify(Node->rc, value, mid+1, R, i);
  //若尚未遞迴到葉節點 則持續遞迴

  Node->Pull();
  //蒐集子樹資訊 更新節點資訊
}
int Queue(Tree * Node, int L, int R, int ql, int qr)
{
  if(ql > R || qr < L)
  {
    return 0;
    //第一種情況
  }
  if(ql <= L && qr >= R)
  {
    return Node->val;
    //最後一種情況
  }
  int mid = (L+R)>>1;
  if(qr <= mid)
  {
    return Queue(Node->lc, L, mid, ql, qr);
    //第二種情況
  }
  else if(ql >= mid+1)
  {
    return Queue(Node->rc, mid+1, R, ql, qr);
    //第三種情況
  }
  return Queue(Node->lc, L, mid, ql, qr) + Queue(Node->rc, mid+1, R, ql, qr);
  //第四種情況
}
int main()
{
  Tree * Node = build(1, 10);
  //從a[1] Build 到 a[10];
//  Modify(Node, 10, 1, 10, 2); 在a[2]這個節點 + 10, 並更新他的所有父節點
  cout << Queue(Node, 1, 10, 2, 6) << endl; // Query 值
}

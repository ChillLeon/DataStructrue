#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1

typedef int ElemType;
typedef int Status;

/*
 * 存储结构
 */
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;


/*
 * 2.将两个非递减的有序链表合并为一个非递增的有序链表
 */
void Reverse_MergeList(LinkList *La,LinkList *Lb)
{
  LinkList r,pa=(*La)->next,pb=(*Lb)->next;  //r是储存地址的临时指针，pa，pb分别是工作指针
  (*La)->next = NULL;                        //先将La初始化为空
  while(pa && pb)                            //当pa，pb均不为空时进行循环
    if(pa->data <= pb->data)
    {
      r=pa->next;
      pa->next=(*La)->next;                  //将pa所指节点连在头结点之后（头插法）
      (*La)->next=pa;
      pa=r;
    }
    else 
    {
      r=pb->next;
      pb->next=(*La)->next;
      (*La)->next=pb;                       //将pb所指节点连在头结点之后（头插法）
      pb=r;
    }
  while(pa)                                 //若还剩一个链表非空时，将它的剩余部分连在La之后（头插法）
    {
      r=pa->next;
      pa->next=(*La)->next;
      (*La)->next=pa;
      pa=r;
    }

  while(pb)
    {
      r=pb->next;
      pb->next=(*La)->next;
      (*La)->next=pb;
      pb=r;
    }
  free(*Lb);                               //释放Lb的头结点
}

/*
 * 3.确定链表中值最大的结点
 */
Status MaxElem(LinkList L,ElemType *e)
{
  LinkList p=L->next;                      //p为工作指针
  LinkList maxp=p;                         //用maxp保存做大值结点
  while(p!=NULL)
  if(p->data > maxp->data)
  {
    maxp=p;                                //与之前找到的最大值进行比较，如果大于之前的结点，将这个结点赋给maxp
  }    
  p = p->next;                             //扫描下一个结点
  *e = maxp->data;
  return OK;
}

/*
 * 4.通过一趟遍历，将链表中所有结点的链接方向逆转
 */
LinkList List_Reverse(LinkList L)
{
  LinkList p,r;                           //p为工作指针，用r保存p的后继
  p = L->next;                            //令p指向头结点
  L->next = NULL;                         //先让头结点的next指向NULL，之后使用头插法将链表逆置
  while(p != NULL)
  {
    r = p->next;                          //保存p的后继
    p->next = L->next;                    //将p结点插到头结点之后
    L->next = p;
    p=r;
  }
  return L;
}

/*
 * 5.将递增有序链表中值大于min并且小于max的所有元素删除
 */

LinkList Range_Del(LinkList *L, int min, int max)
{
  LinkList p_pre = *L, p = (*L)->next;    //p为工作指针，p_pre是其前驱
  while (p != NULL)
  if(p->data > min && p->data < max)      //如果p指向的数值在min和max之间，将其删除，并让p指向下一个结点
  {
    free(p);
    p = p->next;
  }
  else                                   //如果p指向的数值不在min和max之间，让p指向下一个结点
  {
  p_pre = p;
  p = p->next;
  }

}

//
// Created by reese on 23-3-22.
//
#include "linkedList.h"
#include <malloc.h>
#include <stdio.h>

Status InitList(LinkedList *L) {
    LNode *head = (LNode *) malloc(sizeof(LNode));//创建首结点
    head->next = NULL;                            //初始化
    *L = head;                                    //插入结点
    return SUCCESS;
}

void DestroyList(LinkedList *L) {
    LNode *current = *L;//创建一个新的LNode
    while (current)    //遍历链表
    {
        *L = current->next;
        free(current);//释放结点
        current = *L;
    }
}

Status InsertList(LNode *p, LNode *q) {
    if (p->next)          //判断p是否有下一个结点
        q->next = p->next;//使q结点成为p结点的下一个结点的上一个结点
    p->next = q;          //使q结点成为p结点的下一个结点
    return SUCCESS;
}

Status DeleteList(LNode *p, ElemType *e) {
    LinkedList next = NULL;
    if (p->next->next)       //判断p的下一个结点的下一个结点是否为空
        next = p->next->next;//使p的下一个结点的下一个结点成为p的下一个结点
    *e = p->next->data;      //使e为p的下一个结点的data
    free(p->next);           //释放p的下一个结点
    p->next = next;
    return SUCCESS;
}

void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
    L = L->next;
    while (L)//遍历链表
    {
        visit(L->data);
        L = L->next;//使L成为L的下一个结点
    }
}

Status SearchList(LinkedList L, ElemType e) {
    ElemType data = L->data;
    int times = -1;
    while (L->next)//遍历链表
    {
        times++;
        if (data == e) {
            printf("%d\n", times);
            return SUCCESS;//找到了
        }
        data = L->next->data;//不是这个，找下一个
        L = L->next;
    }
    if (L->data == e)//最后一个
    {
        printf("%d\n", ++times);
        return SUCCESS;
    }
    return ERROR;//没找到
}

Status ReverseList(LinkedList *L)//迭代
{
    LinkedList current = *L;//现在的
    current = current->next;
    LinkedList next = current->next;//下一个
    LinkedList next_next;
    current->next = NULL;
    while (next->next) {
        next_next = next->next;//记录下一个的下一个
        next->next = current;  //使现在的成为下一个的下一个
        current = next;        //使下一个成为现在的
        next = next_next;      //使下一个的下一个成为下一个
    }
    next->next = current;
    (*L)->next = next;
    return SUCCESS;
}

Status IsLoopList(LinkedList L) {
    LinkedList slow = L, fast = L;//快慢
    while (fast->next)            //如果为NULL则说明不是
    {
        slow = slow->next;
        fast = fast->next;
        if (fast->next)//防止出错
            fast = fast->next;
        else
            break;
        if (fast == slow)//快慢相遇
            return SUCCESS;
    }
    return ERROR;
}

LNode *ReverseEvenList(LinkedList *L) {
    LinkedList odd = *L, even = (*L)->next, next_odd, next_even;//单数,偶数和下一个奇数和下一个偶数
    LNode *newHead = (LNode *) malloc(sizeof(LNode));           //新的首结点
    newHead->next = even;
    while (1) {
        if (even->next)
            next_odd = even->next;//下一个奇数
        else {
            even->next = odd;//单数成为偶数的下一个
            odd->next = NULL;//最后一个
            return newHead;
        }
        if (next_odd->next)
            next_even = next_odd->next;//下一个偶数
        else {
            even->next = odd;    //单数成为偶数的下一个
            odd->next = next_odd;//单数个，next只能为奇数
            return newHead;
        }
        even->next = odd;     //单数成为偶数的下一个
        odd->next = next_even;//单数成为下一个偶数的上一个
        odd = next_odd;       //下一个
        even = next_even;     //下一个
    }
}
LNode *FindMidNode(LinkedList *L) {
    LinkedList slow = *L, fast = *L;//快慢
    while (fast->next)              //等待快指针到达链表尾部
    {
        slow = slow->next;
        fast = fast->next;
        if (fast->next)
            fast = fast->next;
        else
            break;
    }
    return slow;//返回中间结点
}

void visit(ElemType e)//visit
{
    printf("%d\n", e);
}

void MakeLoop(LinkedList *L) {
    LinkedList last = *L;
    while (last->next)
        last = last->next;
    last->next = *L;
}

void MakeNotLoop(LinkedList *L) {
    LinkedList last = *L;
    while (last->next != *L)
        last = last->next;
    last->next = NULL;
}

void PrintMenu()//打印菜单
{
    printf("****************************************************************************\n"
           "           input to choose what you need(please InitList first)\n"
           "1.InitList    2.DestroyList  3.InsertList  4.DeleteList       5.TraverseList\n"
           "6.SearchList  7.ReverseList  8.IsLoopList  9.ReverseEvenList  10.FindMidNode\n"
           "11.MakeLoop   12.MakeNotLoop 13.exit\n"
           "****************************************************************************\n");
}

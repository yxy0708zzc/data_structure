#include <stdio.h>
#include <stdlib.h>
struct node
{
    int x = 0;
    int y = 0; // x的y次方
    node *next = NULL;
};
int list_len(node *s);                                    // 输出链表长度
void list_print(node *s);                                 // 逐个输出一个链表
bool list_init(node *s, int in[2][2], int len);           // 初始化一个链表
bool list_free(node *s);                                  // free一个链表
void list_push_front(node *s, int x, int y);              // 在链表头加入一个元素
void list_push_back(node *s, int x, int y);               // 在链表尾加入一个元素
void list_empty(node *s);                                 // 清空链表
node *list_merge(node *s1, node *s2, bool sored = false); // 将两个链表融合并排序
void list_sort(node *s);                                  // 按y次序排序
node *list_insert_y(node *s, int x, int y, int to_y);     // 在指定指数之后插入指定node，插入失败返回NULL
node *list_insert_n(node *s, int x, int y, int n);        // 设置第n位(0base)为指定node，插入失败返回NULL
int list_get_y(node *s, int y);                           // 返回指定y的系数,失败返回0
int list_get_n(node *s, int n);                           // 返回指定序号位n的系数x,失败返回0
bool list_set(node *s, int x, int y);                     // 设置指定y的系数,失败返回false
int list_del_y(node *s, int y);
void list_merge_item(node *s);
/*------------------------------------------------------------函数实现------------------------------------------------------------------------*/
int cmp(const void *s1, const void *s2)
{
    return (*(node **)s1)->y - (*(node **)s2)->y; // 注意对指针排序的操作
}
int list_len(node *s)
{
    return s->x;
}
void list_print(node *s)
{
    node *now = s->next;
    int depth = 0;
    while (now != NULL)
    {
        printf("%d*x^%d", now->x, now->y);
        now = now->next;
        depth++;
        if (depth <= s->x - 1)
        {
            printf(" + ");
        }
    }
    printf("\n");
}
bool list_init(node *s, int in[2][2], int len)
{
    s->x = len;
    s->y = 2;
    int i, j, k;
    node *now = s;
    for (i = 0; i <= len - 1; i++)
    {
        if (in[i][0] == 0)
        {
            s->x--;
            continue;
        }
        node *next = (node *)calloc(1, sizeof(node));
        if (next == NULL)
            return false;
        next->x = in[i][0];
        next->y = in[i][1];
        now->next = next;
        now = next;
    }
    return true;
}
bool list_free(node *s)
{
    if (s == NULL)
        return false;
    node *now = s;
    while (now != NULL)
    {
        node *tem;
        tem = now;
        now = now->next;
        free(tem);
    }
    return true;
}
void list_push_front(node *s, int x, int y)
{
    if (x == 0)
    {
        return;
    }
    s->x++;
    node *front = (node *)calloc(1, sizeof(node));
    front->next = s->next;
    front->x = x;
    front->y = y;
    s->next = front;
}
void list_push_back(node *s, int x, int y)
{
    if (x == 0)
    {
        return;
    }
    s->x++;
    node *back = (node *)calloc(1, sizeof(node));
    back->x = x;
    back->y = y;
    back->next = NULL;
    node *now = s;
    while (now->next != NULL)
    {
        now = now->next;
    }
    now->next = back;
}
void list_empty(node *s)
{
    s->x = 0;
    node *now = s->next;
    s->next = NULL;
    list_free(now);
}
node *list_merge(node *s1, node *s2, bool sored)
{
    if (!sored)
    {
        list_sort(s1);
        list_sort(s2);
    }
    node *res = (node *)calloc(1, sizeof(node));
    node *a = s1->next, *b = s2->next;
    res->x = s1->x + s2->x;
    res->y = 2;
    node *now = res;
    while (a != NULL && b != NULL)
    {
        node *tem = (node *)calloc(1, sizeof(node));
        if (a->y < b->y)
        {
            tem->x = a->x;
            tem->y = a->y;
            now->next = tem;
            now = tem;
            a = a->next;
        }
        else if (a->y > b->y)
        {
            tem->x = b->x;
            tem->y = b->y;
            now->next = tem;
            now = tem;
            b = b->next;
        }
        else
        {
            tem->x = a->x + b->x;
            tem->y = a->y;
            now->next = tem;
            now = tem;
            a = a->next;
            b = b->next;
            res->x--;
        }
    }
    while (a != NULL)
    {
        node *tem = (node *)calloc(1, sizeof(node));
        tem->x = a->x;
        tem->y = a->y;
        now->next = tem;
        now = now->next;
        a = a->next;
    }
    while (b != NULL)
    {
        node *tem = (node *)calloc(1, sizeof(node));
        tem->x = b->x;
        tem->y = b->y;
        now->next = tem;
        now = now->next;
        b = b->next;
    }
    return res;
}
void list_sort(node *s)
{
    int i = 0;
    node *all[s->x];
    node *now = s->next;
    while (now != NULL)
    {
        all[i++] = now;
        now = now->next;
    }
    qsort(all, s->x, sizeof(node *), cmp);
    now = s;
    for (i = 0; i <= s->x - 1; i++)
    {
        now->next = all[i];
        now = now->next;
    }
    now->next = NULL;
}
node *list_insert_y(node *s, int x, int y, int to_y)
{
    if (x == 0)
    {
        return 0;
    }
    node *now = s->next;
    while (now != NULL)
    {
        if (now->y == to_y)
        {
            node *tem = (node *)calloc(1, sizeof(node));
            tem->x = x;
            tem->y = y;
            tem->next = now->next;
            now->next = tem;
            s->x++;
            return tem;
        }
        now = now->next;
    }
    return NULL;
}
node *list_insert_n(node *s, int x, int y, int n)
{
    if (x == 0)
    {
        return 0;
    }
    node *now = s;
    for (int i = 0; i <= n - 1; i++)
    {
        if (now == NULL)
        {
            return NULL;
        }
        now = now->next;
    }
    node *tem = (node *)calloc(1, sizeof(node));
    tem->x = x;
    tem->y = y;
    tem->next = now->next;
    now->next = tem;
    return tem;
}
int list_get_y(node *s, int y)
{
    node *now = s->next;
    while (now != NULL)
    {
        if (now->y == y)
        {
            return now->x;
        }
        now = now->next;
    }
    return 0;
}
int list_get_n(node *s, int n)
{
    node *now = s->next;
    int j = 0;
    while (now != NULL)
    {
        if (j == n)
        {
            return now->x;
        }
        j++;
        now = now->next;
    }
    return 0;
}
bool list_set(node *s, int x, int y)
{
    if (x == 0)
    {
        return false;
    }
    node *now = s->next;
    while (now != NULL)
    {
        if (now->y == y)
        {
            now->x = x;
            return true;
        }
        now = now->next;
    }
    return false;
}
int list_del_y(node *s, int y)
{
    node *now = s;
    while (now->next != NULL)
    {
        if (now->next->y == y)
        {
            int tem = now->next->x;
            node *tem2 = now->next->next;
            free(now->next);
            now->next = tem2;
            s->x--;
            return tem;
        }
        now = now->next;
    }
    return 0;
}
void list_merge_item(node *s)
{
    list_sort(s);
    node *now = s->next;
    while (now->next != NULL)
    {
        while (now->next->y == now->y && now->next != NULL)
        {
            node *tem = now->next;
            now->x += now->next->x;
            now->next = now->next->next;
            free(tem);
            s->x--;
        }
        now = now->next;
    }
}

int to_free_list[10] = {};
int main()
{
    int in[5][2] = {{1, 2}, {2, 3}, {100, 2}, {-5, 9}, {-7, 6}};
    node *s = (node *)calloc(1, sizeof(node));
    list_init(s, in, 5);
    list_print(s);
    list_merge_item(s);
    list_print(s);
    /*------------------------------------------------------------释放------------------------------------------------------------------------*/
    list_free(s);
    return 0;
}
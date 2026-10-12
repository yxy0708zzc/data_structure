#include <stdio.h>
#include<stdlib.h>
#define NUM 10
struct node
{
    int x = 0;
    int y = 0; // x的y次方
};

struct list
{
    node *data;
    int len = 0;
    int space = 0;
};
int cmp(const void *a, const void *b)
{
    return ((node *)a)->y - ((node *)b)->y;
}
long double ld;
list list_init(int in[][2], int len, int space = 100);
node list_get_n(list s, int n); // 无数据，返回的x为0,n为0base
node list_get_y(list s, int y); // 无数据，返回的x为0
list list_merge(list s1, list s2, bool sorted = false);
void list_sort(list *s);
void list_push_front(list *s, int x, int y);
void list_push_back(list *s, int x, int y);
list list_merge_item(list s);
bool list_set(list *s, int x, int y);
void list_free(list *s);
void list_print(list s);

void list_merge_item(node *s);
/*------------------------------------------------------------函数实现------------------------------------------------------------------------*/
list list_init(int in[][2], int len, int space)
{
    list s;
    if (len > space)
    {
        space = len;
    }
    s.data = (node *)calloc(space, sizeof(node));
    s.len = len;
    s.space = space;
    for (int i = 0; i <= s.len - 1; i++)
    {
        s.data[i].x = in[i][0];
        s.data[i].y = in[i][1];
    }
    return s;
}
node list_get_n(list s, int n)
{
    if (n > s.len - 1)
    {
        node tem;
        return tem;
    }
    return s.data[n];
}
node list_get_y(list s, int y)
{
    int i, j, k;
    node tem;
    tem.y = y;
    tem.x = 0;
    for (i = 0; i <= s.len - 1; i++)
    {
        if (s.data[i].y == y)
        {
            tem.x += s.data[i].x;
        }
    }
    return tem;
}
list list_merge(list s1, list s2, bool sorted)
{
    if (!sorted)
    {
        list_sort(&s1);
        list_sort(&s2);
    }
    list res;
    res.len = s1.len + s2.len;
    res.space = s1.space + s2.space;
    res.data = (node *)calloc(res.space, sizeof(node));
    int a = 0, b = 0, k = 0;
    while (a <= s1.len - 1 && b <= s2.len - 1)
    {
        if (s1.data[a].y < s2.data[b].y)
        {
            res.data[k].y = s1.data[a].y;
            res.data[k].x = s1.data[a].x;
            a++;
            k++;
        }
        if (s1.data[a].y > s2.data[b].y)
        {
            res.data[k].y = s2.data[b].y;
            res.data[k].x = s2.data[b].x;
            b++;
            k++;
        }
        if (s1.data[a].y == s2.data[b].y)
        {
            res.data[k].y = s1.data[b].y;
            res.data[k].x = s1.data[a].x + s2.data[b].x;
            a++;
            b++;
            k++;
            res.len--;
        }
    }
    list_print(res);
    list_print(s1);
    list_print(s2);
    while (a <= s1.len - 1)
    {
        res.data[k].y = s1.data[a].y;
        res.data[k].x = s1.data[a].x;
        a++;
        k++;
    }
    while (b <= s2.len - 1)
    {
        res.data[k].y = s2.data[b].y;
        res.data[k].x = s2.data[b].x;
        b++;
        k++;
    }
    return res;
}
void list_sort(list *s)
{
    node *tem = s->data;
    qsort(tem, s->len, sizeof(node), cmp);
}
void list_push_front(list *s, int x, int y)
{
    if (x == 0)
        return;
    s->len++;
    while (s->space <= s->len)
    {
        s->space += NUM;
        s->data = (node *)realloc(s->data, s->space * sizeof(node));
    }
    for (int i = s->len - 2; i >= 0; i--)
    {
        s->data[i + 1] = s->data[i];
    }
    s->data[0].x = x;
    s->data[0].y = y;
    return;
}
void list_push_back(list *s, int x, int y)
{
    if (x == 0)
        return;
    s->len++;
    while (s->space <= s->len)
    {
        s->space += NUM;
        s->data = (node *)realloc(s->data, s->space * sizeof(node));
    }
    s->data[s->len - 1].x = x;
    s->data[s->len - 1].y = y;
    return;
}
list list_merge_item(list s)
{
    int i, j, k;
    int len = s.len;
    for (i = 0; i <= s.len - 1; i++)
    {
        if (s.data[i].x == 0)
        {
            continue;
        }
        for (j = 1; j <= s.len - i - 1; j++)
        {
            if (s.data[i].y == s.data[i + j].y)
            {
                s.data[i].x += s.data[i + j].x;
                s.data[i + j].x = 0;
                len--;
            }
        }
    }
    list tem;
    tem.data = (node *)calloc(s.space, sizeof(node));
    j = 0;
    for (i = 0; i <= s.len - 1; i++)
    {
        if (s.data[i].x != 0)
        {
            tem.data[j].x = s.data[i].x;
            tem.data[j].y = s.data[i].y;
            j++;
        }
    }
    tem.len = len;
    tem.space = s.space;
    return tem;
}
bool list_set(list *s, int x, int y)
{
    for (int i = 0; i <= s->len - 1; i++)
    {
        if (s->data[i].y == y)
        {
            s->data[i].x = x;
            return true;
        }
    }
    return false;
}
void list_free(list *s)
{
    free(s->data);
}
void list_print(list s)
{
    int i = 0;
    for (i = 0; i <= s.len - 2; i++)
    {
        printf("%d*x^%d + ", s.data[i].x, s.data[i].y);
    }
    printf("%dx^%d\n", s.data[i].x, s.data[i].y);
}

int main()
{
    list s;
    int in[3][2] = {{1, 2}, {2, 3}, {100, 2}};
    s = list_init(in, 3);
    list_print(s);
    s=list_merge_item(s);
    list_print(s);
    /*------------------------------------------------------------释放------------------------------------------------------------------------*/
    list_free(&s);
    return 0;
}
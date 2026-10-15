#include <stdio.h>
#include <stdlib.h>
struct node
{
    int x;
};
struct queue
{
    int space = 0;
    node *data = NULL;
    int head = 0;
    int tail = 0;
};

bool q_init(queue *s, int n);
bool q_is_full(queue s);
bool q_push(queue s);
bool q_pop(queue s);
node q_front(queue s);
bool q_is_empty(queue s);
void q_clear(queue s);
int q_size(queue s);

/*------------------------------------------------------------函数实现------------------------------------------------------------------------*/
bool q_init(queue *s, int n)
{
    s->space = n;
    s->data = (node *)calloc(s->space, sizeof(node));
    if (s->data == NULL)
        return false;
    else
        return true;
}
bool q_is_full(queue s)
{
    if ((s.tail + 1) % s.space == s.head)
        return true;
    else
        return false;
}
bool q_push(queue *s, int x)
{
    if (q_is_full(*s))
        return false;
    else
    {
        s->data[s->tail].x = x;
        s->tail++;
        if (s->tail == s->space)
            s->tail = s->tail - s->space;
        return true;
    }
}
bool q_pop(queue *s)
{
    if (q_is_empty(*s))
        return false;
    else
    {
        s->data[s->head].x = 0;
        s->head++;
        if (s->head == s->space)
            s->head = s->head - s->space;
        return true;
    }
}
node q_front(queue s)
{
    return s.data[s.head];
}
bool q_is_empty(queue s)
{
    return (s.head == s.tail);
}
void q_clear(queue s)
{
    s.head = 0;
    s.tail = 0;
    free(s.data);
    s.space = 0;
}
int q_size(queue s)
{
    if (s.tail >= s.head)
        return s.tail - s.head;
    else
        return s.tail - s.head;
}
void q_print(queue s)
{
    int i = s.head, j, k;
    if (i == s.tail)
    {
        printf("空\n");
        return;
    }

    while (i != s.tail)
    {
        printf("%7d ", s.data[i]);
        i++;
        if (i == s.space)
        {
            i = 0;
        }
    }
    printf("\n");
}
bool yhsj(queue *s, int n)
{
    if (!q_is_empty(*s))
    {
        return false;
    }
    else
    {
        int i, j, k, h, t = 0;
        q_push(s, 1);
        q_print(*s);
        for (i = 0; i <= n; i++)
        {
            q_push(s, 0);
            while (q_front(*s).x != 0)
            {
                q_push(s, t + s->data[s->head].x);
                t = s->data[s->head].x;
                q_pop(s);
            }
            q_push(s, t + s->data[s->head].x);
            t = 0;
            q_pop(s);
            q_print(*s);
        }
    }
    return true;
}

int main()
{
    queue s;
    q_init(&s, 100);
    yhsj(&s, 20);
    return 0;
}

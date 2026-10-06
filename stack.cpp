#include <bits/stdc++.h>
#define SPACE 10
struct node
{
    float x = 0;
    char c = '\0';
};
struct stack
{
    node *base = NULL;
    node *top = NULL;
    int space = 0;
};
bool stack_init(stack *s);
float stack_top(stack *s);
bool stack_pop(stack *s);
int stack_len(stack *s);
bool stack_free(stack *s);
void stack_push(stack *s, float a);

/*------------------------------------------------------------函数实现------------------------------------------------------------------------*/
bool stack_init(stack *s)
{
    printf("init\n");
    s->base = (node *)calloc(SPACE, sizeof(node));
    if (s->base == NULL)
        return false;
    s->space = SPACE;
    s->top = s->base;
    return true;
}
int stack_len(stack *s)
{
    return s->top - s->base;
}
float stack_top(stack *s)
{
    return ((s->top) - 1)->x;
}
bool stack_pop(stack *s)
{
    if (stack_len(s) == 0)
        return false;
    else
    {
        s->top--;
        return true;
    }
}
bool stack_free(stack *s)
{
    if (s == NULL)
        return false;
    else
    {
        s->top = NULL;
        free(s->base);
        s->space = 0;
        return true;
    }
}
void stack_push(stack *s, float a)
{
    if (stack_len(s) >= s->space)
    {
        s->base = (node *)realloc(s->base, (s->space + SPACE) * sizeof(node));
        s->top = s->base + s->space;
        s->space = s->space + SPACE;
    }
    (*s).top->x = a;
    s->top++;
}

/*------------------------------------------------------------node操作------------------------------------------------------------------------*/
node *node_init(int len, int x[], char c[])
{
    node *t = (node *)calloc(len, sizeof(node));
    node *now = t;
    for (int i = 0; i <= len - 1; i++)
    {
        if (c[i] == '\0')
        {
            now->x = x[i];
            now->c = '\0';
        }
        else
        {
            now->c = c[i];
        }
        now++;
    }
    return t;
}
float compute(stack *s, node *t, int len)
{
    int mark = 0;
    int i = 0;
    for (i = 0; i <= len - 1; i++)
    {
        if (t[i].c == '\0')
        {
            stack_push(s, t[i].x);
        }
        else
        {
            float b = stack_top(s);
            stack_pop(s);
            float a = stack_top(s);
            stack_pop(s);
            switch (t[i].c)
            {
            case '+':
                stack_push(s, a + b);
                break;
            case '-':
                stack_push(s, a - b);
                break;
            case '*':
                stack_push(s, a * b);
                break;
            case '/':
                stack_push(s, a / b);
                break;
            default:
                break;
            }
        }
    }
    return stack_top(s);
}

int main()
{
    stack s;
    stack_init(&s);
    int len = 5;
    int x[5] = {3, 5, 0, 2, 0};
    char c[5] = {'\0', '\0', '-', '\0', '*'};
    node *t = node_init(len, x, c);
    printf("%lf", compute(&s, t, len));
    stack_free(&s);
    free(t);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct node
{
    bool mark = false; // 该下标是否有数据
    char x = '\0';     // 结点数据
};

node *init(char in[], node *s, int depth); // 建树：深度depth的顺序二叉树，in按层序给出（'*'或'\0'为空结点），返回1base数组
char get(char to[], node *s);              // 取值：to为路径串（'1'左'2'右），返回对应结点的值

/*------------------------------------------------------------函数实现------------------------------------------------------------------------*/
node *init(char in[], node *s, int depth)
{
    int len = pow(2, depth) - 1;
    s = (node *)calloc(len + 5, sizeof(node));
    int i, j, k;

    for (i = 1; i <= len; i++)
    {
        if (in[i - 1] == '*' || in[i - 1] == '\0')
        {
            s[i].mark = false;
            s[i].x = '\0';
        }
        else
        {
            s[i].mark = true;
            s[i].x = in[i - 1];
        }
    }
    return s;
}

char get(char to[], node *s)
{
    int i = 0, num = 1;
    while (to[i] != '\0')
    {
        if (to[i] == '1')
        {
            num = num * 2;
        }
        else if (to[i] == '2')
        {
            num = num * 2 + 1;
        }
        i++;
    }
    if (s[num].mark == false)
    {
        printf("无此节点");
        return '\0';
    }
    else
    {
        return s[num].x;
    }
}

int main()
{
    int depth = 0;
    scanf("%d", &depth);
    int len = pow(2, depth) - 1;
    char in[len] = "";
    scanf("%s", in);
    node *s = init(in, NULL, depth);
    char to[10] = "";
    scanf("%s", to);
    printf("%c", get(to, s));
    return 0;
}
/*

4
12345*6*789
121


*/
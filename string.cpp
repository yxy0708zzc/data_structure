#include <stdio.h>
#include <stdlib.h>
#define NUM 30
struct string
{
    char *data;
    int space;
    int len;
};
bool str_init(string *s, int len, char in[]);          // 初始化：把长度为len的字符数组in装入串s，按NUM分配空间
void str_print(string s);                              // 打印：输出串的长度和数据
int str_sub(string s, string sub, int start = 0);      // 查找：从start起在s中找sub首次出现的位置，找到返回下标，找不到返回-1
string str_add(string s1, string s2);                  // 连接：返回s1和s2拼接后的新串
bool str_insert(string *s, int t, string sub);         // 插入：把sub插入到s的第t个位置（0base），空间不足时扩容
bool str_del_n(string *s, int t, int len);             // 删除：从s的第t个位置起删除len个字符，后面字符前移
string str_cpy(string s);                              // 复制：深拷贝s，返回新串
void str_free(string *s);                              // 销毁：释放s的data空间，长度和容量清零
int str_cmp(string s1, string s2);                     // 比较：逐字符比较，s1大返回1，小返回-1，相等返回0
void str_clear(string *s);                             // 清空：数据置'\0'，长度归零（空间保留）
char str_get(string s, int n);                         // 取值：返回s中第n个字符，越界返回'\0'
bool str_replace(string *s, string olds, string news); // 替换：把s中第一处olds替换为news（先删后插）
int str_sub_fast(string s, string sub);
/*------------------------------------------------------------函数实现------------------------------------------------------------------------*/
bool str_init(string *s, int len, char in[])
{
    if (s == NULL)
        return false;
    s->space = (len / NUM + 2) * NUM;
    s->len = len;
    s->data = (char *)calloc(s->space, sizeof(char));
    for (int i = 0; i <= len - 1; i++)
    {
        if (in[i] == '\0')
        {
            free(s->data);
            printf("字符串中含有\\0");
            return false;
        }
        s->data[i] = in[i];
    }
    return true;
}
void str_print(string s)
{
    printf("长度:%d 数据:", s.len);
    for (int i = 0; i <= s.len - 1; i++)
    {
        if (s.data[i] == '\0')
        {
            printf("里面有\\0");
            return;
        }
        printf("%c", s.data[i]);
    }
    printf("\n");
}
int str_sub(string s, string sub, int start)
{
    if (sub.data == NULL)
    {
        return -2;
    }
    int len = 0;
    int i = 0, j = 0;
    while (sub.data[i] != '\0')
    {
        len++;
        i++;
    }
    for (i = start; i <= s.len - len; i++)
    {
        int mark = 1;
        for (j = 0; j <= len - 1; j++)
        {
            if (s.data[i + j] != sub.data[j])
            {
                mark = 0;
                break;
            }
        }
        if (mark == 1)
        {
            return i; // 返回下一个没有探索的节点
        }
    }
    return -1;
}
string str_add(string s1, string s2)
{
    string s;
    s.len = s1.len + s2.len;
    s.space = (s.len / NUM + 2) * NUM;
    s.data = (char *)calloc(s.space, sizeof(char));
    int i = 0;
    for (i = 0; i <= s1.len - 1; i++)
    {
        s.data[i] = s1.data[i];
    }
    for (i = 0; i <= s2.len - 1; i++)
    {
        s.data[s1.len - 1 + i] = s1.data[i];
    }
    return s;
}
bool str_insert(string *s, int t, string sub)
{
    int len = s->len;
    if (t > s->len)
    {
        printf("插入位置不属于原字符串");
        return false;
    }
    s->len = s->len + sub.len;
    if (s->len + 5 > s->space)
    {
        s->space = (s->len / NUM + 2) * NUM;
        s->data = (char *)realloc(s->data, s->space);
    }
    for (int i = s->len - 1; i >= t; i--)
    {
        s->data[i + sub.len] = s->data[i];
    }
    for (int i = 0; i <= sub.len - 1; i++)
    {
        s->data[t + i] = sub.data[i];
    }
    return true;
}
bool str_del_n(string *s, int t, int len)
{
    if (t + len > s->len)
    {
        printf("删除部分不属于字符串");
        return false;
    }
    for (int i = t; i <= s->len - len - 1; i++)
    {
        s->data[i] = s->data[i + len];
    }
    // for (int i = s->len - len; i <= s->space - 1; i++)
    //     s->data[i] = '\0';
    s->len = s->len - len;
    return true;
}
string str_cpy(string s)
{
    string res;
    res.space = s.space;
    res.len = s.len;
    res.data = (char *)calloc(s.space, sizeof(char));
    for (int i = 0; i <= s.len - 1; i++)
    {
        res.data[i] = s.data[i];
    }
    return res;
}
void str_free(string *s)
{
    free(s->data);
    s->len = 0;
    s->space = 0;
}
int str_cmp(string s1, string s2)
{
    for (int i = 0; i <= s1.len - 1 && i <= s2.len - 1; i++)
    {
        if (s1.data[i] > s2.data[i])
        {
            return 1;
        }
        if (s1.data[i] < s2.data[i])
        {
            return -1;
        }
    }
    if (s1.len > s2.len)
        return 1;
    else if (s1.len < s2.len)
        return -1;
    else
        return 0;
}
void str_clear(string *s)
{
    for (int i = 0; i <= s->len - 1; i++)
    {
        s->data[i] = '\0';
    }
    s->len = 0;
}
char str_get(string s, int n)
{
    if (n > s.len - 1)
        return '\0';
    return s.data[n];
}
bool str_replace(string *s, string olds, string news)
{
    int n = str_sub(*s, olds);
    if (n == -1)
        return false;
    str_del_n(s, n, olds.len);
    return str_insert(s, n, news);
}

int str_sub_fast(string s, string sub, int start) // KMP实现
{
    int *next = (int *)calloc(sub.len, sizeof(int));
    int i = 0, j = 0, k = 0;
    next[0] = 0;
    i = 1;
    while (i <= sub.len - 1)
    {
        if (sub.data[i] == sub.data[j])
        {
            next[i] = j + 1;
            i++;
            j++;
        }
        else
        {
            if (j == 0)
            {
                next[i] = 0;
                i++;
                continue;
            }
            else
            {
                j = next[j - 1];
            }
        }
    }
    j = 0;
    i = start;
    while (i <= s.len - 1)
    {
        if (s.data[i] == sub.data[j])
        {
            i++;
            j++;
        }
        else
        {
            if (j == 0)
            {
                i++;
                continue;
            }
            j = next[j - 1];
        }
        if (j == sub.len)
        {
            return i - j;
        }
    }
    return -1;
}

int main()
{
    // string s, sub, old;
    // char a[10] = "123456";
    // char b[10] = "abc";
    // char c[10] = "xyz";
    // str_init(&s, 6, a);
    // str_init(&old, 3, b);
    // str_init(&sub, 3, c);
    // str_print(s);
    // str_insert(&s, 3, old);
    // str_print(s);
    // printf("取代%d\n", str_replace(&s, sub, sub));
    // str_print(s);
    // str_free(&s);
    // str_free(&sub);

    string t;
    string s;
    char test[10] = "aaaaaaaaa";
    char a[10] = "aa";
    str_init(&t, 2, a);
    str_init(&s, 9, test);
    int res = 0;
    while (1)
    {
        res = str_sub_fast(s, t, res);
        if (res == -1)
            break;
        printf("%d ", res);
        res+=t.len;
    }

    return 0;
}
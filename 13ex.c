#include <stdio.h>
void postfix(char A[], char B[])
{
    int i, n, tp, j = -1;
    char s[2][1000], e;
    s[0][0] = '&';
    s[1][tp = 0] = 100;
    for (i = 0; A[i] != '\0'; i++)
        ;
    n = i;
    for (i = 0; i < n; i++)
    {
        e = A[i];
        if (e == 32)
            continue;
        if ((e < 123 && e > 96) || (e < 91 && e > 64))
        {
            B[++j] = e;
        }
        else if (e == '(')
        {
            s[++tp][0] = e;
            s[tp][1] = 1;
        }
        else if (e == ')')
        {
            while (s[tp][0] != '(')
                B[++j] = s[tp--][0];
            tp--;
        }
        else if (e == '+' || e == '-')
        {
            while (s[tp][1] >= 2)
                B[++j] = s[tp--][0];
            s[++tp][0] = e;
            s[tp][1] = 2;
        }
        else if (e == '*' || e == '/' || e == '%')
        {
            while (s[tp][1] >= 3)
                B[++j] = s[tp--][0];
            s[++tp][0] = e;
            s[tp][1] = 3;
        }
        else if (e == '^')
        {
            while (s[tp][1] > 4)
                B[++j] = s[tp--][0];
            s[++tp][0] = e;
            s[tp][1] = 4;
        }
    }
    for (i = tp; i > 0; i--)
        B[++j] = s[i][0];
    B[++j] = '\0';
}

void three_add_code(char A[])
{
    char B[1000], e, a, b;
    int i, tp = -1;
    for (i = 0; A[i] != '\0'; i++)
    {
        e = A[i];
        if (e < 123 && e > 96)
        {
            B[++tp] = e;
            continue;
        }
        b = B[tp--];
        a = B[tp--];
        printf("t = %c %c %c\n", a, e, b);
        B[++tp] = 't';
    }
}
int main()
{
    char A[1000], B[1000];
    printf("\nExpression : ");
    scanf("%[^\n]s", A);
    postfix(A, B);
    printf("postfix : %s\n\n", B);
    three_add_code(B);
    return 0;
}
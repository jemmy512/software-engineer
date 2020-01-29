/*
 * Created by Jemmy on 2018/8/6.
 * Refer: https://coolshell.cn/articles/11377.html
 */
#include <stdio.h>
struct str{
    int len;
    char s[0];
};

struct foo {
    struct str *a;
};

int main(int argc, char** argv) {
    struct foo f={0};
    if (f.a->s) {
        printf( f.a->s);    // crash, invalid access
    }
    return 0;
}


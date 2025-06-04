// gcc -o main main.c -ldl

#include <dlfcn.h>
#include <stdio.h>

int main()
{
    void *handle;
    void (*hello_func)();

    // 1. 라이브러리 열기
    handle = dlopen("./libplugin.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return 1;
    }

    // 2. 심볼 얻기
    hello_func = dlsym(handle, "hello");
    if (!hello_func)
    {
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // 3. 함수 호출
    hello_func();

    // 4. 핸들 닫기
    dlclose(handle);
    return 0;
}

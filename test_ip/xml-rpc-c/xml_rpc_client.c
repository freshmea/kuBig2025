// gcc -o xmlrpc_client xmlrpc_client.c -lxmlrpc_client -lxmlrpc -lxmlrpc_util
// ./xmlrpc_client 5

#include <stdio.h>
#include <stdlib.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

int main(int argc, char **argv)
{
    xmlrpc_env env;
    xmlrpc_value *resultP;
    xmlrpc_int32 square;
    const char *const serverUrl = "http://localhost:8080/RPC2";
    const char *const methodName = "square";
    int number;

    // 인자 확인
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    // 입력 숫자 파싱
    number = atoi(argv[1]);

    // XML-RPC 환경 초기화
    xmlrpc_env_init(&env);

    // 클라이언트 초기화
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, "XML-RPC C Client", NULL, NULL, 0);
    if (env.fault_occurred)
    {
        fprintf(stderr, "Failed to initialize client: %s\n", env.fault_string);
        xmlrpc_env_clean(&env);
        return 1;
    }

    // XML-RPC 호출
    resultP = xmlrpc_client_call(&env, serverUrl, methodName, "(i)", (xmlrpc_int32)number);
    if (env.fault_occurred)
    {
        fprintf(stderr, "Error: %s\n", env.fault_string);
        xmlrpc_env_clean(&env);
        xmlrpc_client_cleanup();
        return 1;
    }

    // 결과 처리
    xmlrpc_read_int(&env, resultP, &square);
    if (env.fault_occurred)
    {
        fprintf(stderr, "Failed to read result: %s\n", env.fault_string);
        xmlrpc_value_free(resultP);
        xmlrpc_env_clean(&env);
        xmlrpc_client_cleanup();
        return 1;
    }

    // 결과 출력
    printf("Square of %d is %d\n", number, square);

    // 정리
    xmlrpc_value_free(resultP);
    xmlrpc_env_clean(&env);
    xmlrpc_client_cleanup();

    return 0;
}
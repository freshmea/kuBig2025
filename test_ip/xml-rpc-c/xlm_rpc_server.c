// sudo apt-get install libxmlrpc-c++8-dev
// gcc -o xmlrpc_server xmlrpc_server.c -lxmlrpc_server_abyss -lxmlrpc_server -lxmlrpc -lxmlrpc_util

#include <stdio.h>
#include <stdlib.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>

// Square 메서드: 숫자의 제곱 계산
static void square_method(xmlrpc_env *const envP,
                          xmlrpc_value *const paramArrayP,
                          void *const serverInfo,
                          xmlrpc_value **const resultPP)
{
    int number;

    // 파라미터 추출
    xmlrpc_array_read_item(envP, paramArrayP, 0, &number);
    if (envP->fault_occurred)
    {
        return;
    }

    // 제곱 계산
    int result = number * number;

    // 결과 반환
    *resultPP = xmlrpc_int_new(envP, result);
}

// 메인 함수
int main(int argc, char **argv)
{
    xmlrpc_env env;
    xmlrpc_registry *registryP;
    xmlrpc_server_abyss_parms serverParm = {0};
    xmlrpc_method_info methodInfo;

    // XML-RPC 환경 초기화
    xmlrpc_env_init(&env);

    // 레지스트리 생성
    registryP = xmlrpc_registry_new(&env);
    if (env.fault_occurred)
    {
        fprintf(stderr, "Failed to create registry: %s\n", env.fault_string);
        xmlrpc_env_clean(&env);
        return 1;
    }

    // Square 메서드 등록
    methodInfo.methodName = "square";
    methodInfo.methodFunction = square_method;
    xmlrpc_registry_add_method_w_info(&env, registryP, NULL, &methodInfo);
    if (env.fault_occurred)
    {
        fprintf(stderr, "Failed to add method: %s\n", env.fault_string);
        xmlrpc_registry_free(registryP);
        xmlrpc_env_clean(&env);
        return 1;
    }

    // Abyss 서버 파라미터 설정
    serverParm.registryP = registryP;
    serverParm.port_number = 8080;

    // 서버 실행
    printf("XML-RPC server running on port 8080...\n");
    xmlrpc_server_abyss(&env, &serverParm, XMLRPC_APSIZE(port_number));
    if (env.fault_occurred)
    {
        fprintf(stderr, "Server run failed: %s\n", env.fault_string);
        xmlrpc_registry_free(registryP);
        xmlrpc_env_clean(&env);
        return 1;
    }

    // 정리
    xmlrpc_registry_free(registryP);
    xmlrpc_env_clean(&env);
    return 0;
}
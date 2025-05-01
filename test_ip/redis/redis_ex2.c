#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    redisContext *context;
    redisReply *reply;

    // Redis 서버에 연결 (localhost:6379)
    context = redisConnect("127.0.0.1", 6379);
    if (context == NULL || context->err)
    {
        if (context)
        {
            printf("Connection error: %s\n", context->errstr);
            redisFree(context);
        }
        else
        {
            printf("Connection error: Can't allocate redis context\n");
        }
        exit(1);
    }
    printf("Connected to Redis server\n");

    // SET 명령: key "mykey"에 값 "Hello, Redis!" 설정
    reply = redisCommand(context, "SET %s %s", "mykey", "Hello, Redis!");
    if (reply == NULL)
    {
        printf("SET command failed: %s\n", context->errstr);
        redisFree(context);
        exit(1);
    }
    printf("SET mykey: %s\n", reply->str);
    freeReplyObject(reply);

    // GET 명령: key "mykey"의 값 조회
    reply = redisCommand(context, "GET %s", "mykey");
    if (reply == NULL)
    {
        printf("GET command failed: %s\n", context->errstr);
        redisFree(context);
        exit(1);
    }
    if (reply->type == REDIS_REPLY_STRING)
    {
        printf("GET mykey: %s\n", reply->str);
    }
    else
    {
        printf("GET command returned unexpected type: %d\n", reply->type);
    }
    freeReplyObject(reply);

    // 연결 종료
    redisFree(context);
    printf("Disconnected from Redis server\n");

    return 0;
}
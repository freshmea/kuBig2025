// sudo apt-get install libhiredis-dev

#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c->err)
    {
        printf("Error: %s\n", c->errstr);
        redisFree(c);
        exit(1);
    }
    redisReply *reply = redisCommand(c, "SET mykey %s", "Hello, Redis!");
    freeReplyObject(reply);
    reply = redisCommand(c, "GET mykey");
    printf("Value: %s\n", reply->str);
    freeReplyObject(reply);
    redisFree(c);
    return 0;
}
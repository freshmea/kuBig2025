#include <MQTTClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BROKER "tcp://localhost:1883"
#define TOPIC "test/topic"
#define QOS 1
#define TIMEOUT 10000L

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <publisher_id>\n", argv[0]);
        return 1;
    }

    char client_id[50];
    snprintf(client_id, sizeof(client_id), "Publisher_%s", argv[1]);

    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    // 클라이언트 생성
    MQTTClient_create(&client, BROKER, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    // 브로커 연결
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    // 메시지 발행
    char payload[100];
    for (int i = 0; i < 10; i++)
    {
        snprintf(payload, sizeof(payload), "Message from %s: %d", client_id, i);
        pubmsg.payload = payload;
        pubmsg.payloadlen = strlen(payload);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;

        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
        printf("Published: %s\n", payload);

        rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
        sleep(2); // 2초 대기
    }

    // 연결 종료
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}
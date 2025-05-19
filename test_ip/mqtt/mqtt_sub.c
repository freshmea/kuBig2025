#include <MQTTClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BROKER "tcp://localhost:1883"
#define TOPIC "test/topic"
#define QOS 1

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message delivery confirmed: token %d\n", dt);
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Received: %.*s (Topic: %s)\n",
           message->payloadlen, (char *)message->payload, topicName);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("Connection lost: %s\n", cause ? cause : "unknown");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <subscriber_id>\n", argv[0]);
        return 1;
    }

    char client_id[50];
    snprintf(client_id, sizeof(client_id), "Subscriber_%s", argv[1]);

    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    // 클라이언트 생성
    MQTTClient_create(&client, BROKER, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    // 콜백 설정
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    // 브로커 연결
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    // 토픽 구독
    MQTTClient_subscribe(client, TOPIC, QOS);
    printf("Subscribed to %s as %s\n", TOPIC, client_id);

    // 메시지 수신 대기 (무한 루프)
    while (1)
    {
        sleep(1);
    }

    // 연결 종료 (실제로는 도달하지 않음)
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}
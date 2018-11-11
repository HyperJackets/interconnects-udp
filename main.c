#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>

#include "udp_packets.h"
#include "udp_packets_fmt.h"

#define PORT 1153
#define BUFSIZE 2048


#define simple_ip(b3, b2, b1, b0) ((in_addr_t) htonl(((b3) << 24) | ((b2) << 16) | ((b1) << 8) | (b0)))


struct my_server {
    struct sockaddr_in myaddr;
    struct sockaddr_in remaddr;
    ssize_t recvlen;
    uint16_t port;
    int fd;
    unsigned char buf[BUFSIZE];
};


void init_addr(struct sockaddr_in *addr, uint16_t port) {
    memset((void *)addr, 0, sizeof(*addr));

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port = htons(port);
}

bool server_bind(struct my_server *server, uint16_t port) {
    init_addr(&server->myaddr, port);

    server->port = port;

    if ((server->fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket\n");
        return false;
    }

    if (bind(server->fd, (struct sockaddr *)&server->myaddr, sizeof(server->myaddr)) < 0) {
        perror("bind failed");
        return false;
    }

    return true;
}

bool server_recv(struct my_server *server) {
    socklen_t addrlen = sizeof(server->remaddr);

    server->recvlen = recvfrom(server->fd, server->buf, BUFSIZE, 0, (struct sockaddr *)&server->remaddr, &addrlen);

    return server->recvlen > 0;
}


int main_server() {
    struct my_server server;

    if (!server_bind(&server, PORT)) {
        return 1;
    }

    printf("waiting on port %d\n", server.port);
    while (server_recv(&server)) {

        printf("received packet with size: %zi\n", server.recvlen);

    }


    return 0;
}

/* paddr: print the IP address in a standard decimal dotted format */
void paddr(in_addr_t addr) {
    unsigned char *a = (unsigned char *)(&addr);

    printf("%d.%d.%d.%d\n", a[0], a[1], a[2], a[3]);
}

bool resolve_hostname(const char *host, in_addr_t *addr) {
    struct hostent *hp;

    hp = gethostbyname(host);
    if (!hp) {
        fprintf(stderr, "could not obtain address of %s\n", host);
        return false;
    }

    if (hp->h_addr_list[0] != 0) {
        memcpy(addr, hp->h_addr_list[0], 4);
        return true;
    }

    fprintf(stderr, "no addresses for %s\n", host);

    return false;
}

struct my_client {
    struct sockaddr_in servaddr;
    int fd;
};

bool client_init(struct my_client *client, in_addr_t servaddr, uint16_t port) {

    init_addr(&client->servaddr, port);
    client->servaddr.sin_addr.s_addr = servaddr;

    if ((client->fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket\n");
        return false;
    }

    return true;
}

bool client_send(struct my_client *client, const void *payload, size_t size) {

    if (sendto(client->fd, payload, size, 0, (struct sockaddr *)&client->servaddr, sizeof(client->servaddr)) < 0) {
        perror("sendto failed");
        return false;
    }

    return true;
}

int main_client() {
    in_addr_t addr;

//    if (!resolve_hostname("localhost", addr)) {
//        return 1;
//    }

    addr = simple_ip(127, 0, 0, 1);

    paddr(addr);

    struct my_client client;
    client_init(&client, addr, PORT);

    const char *my_message = "Hello world";

    client_send(&client, my_message, strlen(my_message) + 1);

    return 0;
}

void *info_listener_thread() {

    struct my_server server;

    if (!server_bind(&server, PORT)) {
        return NULL;
    }

    printf("waiting on port %d\n", server.port);
    while (server_recv(&server)) {

        if (server.recvlen != sizeof(struct info_packet)) {
            printf("received packet with size: %zi\n", server.recvlen);
        }

        printf("received potential info packet (size matches)\n");

        struct info_packet packet;
        decode_info_packet(server.buf, &packet);

        print_info_packet(&packet);

    }

    return NULL;
}

int main(int argc, char **argv) {

    bool server = false;

    for (int i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);

        if (strcmp(argv[i], "server") == 0) {
            server = true;
        }
    }

    printf("Mode: %s\n\n", server ? "server" : "device");

//    if (server) {
//        return main_server();
//    } else {
//        return main_client();
//    }

    struct info_packet p;
    p.magic_number = MAGIC_INFO_PACKET;
    p.timestamp = 5432345;
    p.pod_status = STATUS_ACCELERATING;

    p.velocity = 12;
    p.acceleration = 100;

    p.battery_voltage = 1002;

    p.pod_temp = 34;
    p.battery_temp = 54;

    p.tank_pressure = 1234;
    p.left_brake_pressure = 543;
    p.right_brake_pressure = 565;


    print_info_packet(&p);

    struct control_packet cp;
    cp.magic_number = MAGIC_CONTROL_PACKET;
    cp.command = COMMAND_EMERGENCY_STOP;
    cp.timestamp = 9286399;

    print_control_packet(&cp);

    pthread_t thread;

    pthread_create(&thread, NULL, info_listener_thread, NULL);

    in_addr_t addr;

//    if (!resolve_hostname("localhost", addr)) {
//        return 1;
//    }

    addr = simple_ip(127, 0, 0, 1);

    paddr(addr);

    struct my_client client;
    client_init(&client, addr, PORT);

    while (1) {
        int32_t velocity;

        scanf("%d", &velocity);

        if (velocity == 0) {
            break;
        }

        p.velocity = velocity;

        char payload[sizeof(p)];
        encode_info_packet(&p, payload);

        client_send(&client, &payload, sizeof(p));

    }


//    printf("Hello, World!\n");
//    return 0;
}
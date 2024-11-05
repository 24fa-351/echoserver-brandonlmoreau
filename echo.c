#define _WIN32_WINNT 0x0601
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

DWORD WINAPI serverConnection(void* sock) 
{
    SOCKET connection = *(SOCKET*)sock;
    char tempBuffer[1000];
    int index = 0;
    int read;
    

    while ((read = recv(connection, &tempBuffer[index], 1, 0)) > 0)
    {

        if (tempBuffer[index] == '\n') 
        {
            tempBuffer[index + 1] = '\0';


            printf("%s", tempBuffer);
            send(connection, tempBuffer, index + 1, 0);
            index = 0;
        }
        else 
        {
            index++;
        }
    }

    closesocket(connection);
    return 0;
}

int main(int argc, char* argv[])
{
    int listeningPort = atoi(argv[2]);

    WSADATA socketData;

    WSAStartup(MAKEWORD(2, 2), &socketData);

    SOCKET mainSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in socketInfo;
    socketInfo.sin_family = AF_INET;
    socketInfo.sin_addr.s_addr = INADDR_ANY;
    socketInfo.sin_port = htons(listeningPort);

    bind(mainSocket, (struct sockaddr*)&socketInfo, sizeof(socketInfo));
    listen(mainSocket, SOMAXCONN);

    printf("port %d\n", listeningPort);
    /////////////////////////////////////////////////////
    while (1) {
        struct sockaddr_in clientInfo;


        int clientInfoSize = sizeof(clientInfo);

        SOCKET newConnection = accept(mainSocket, (struct sockaddr*)&clientInfo, &clientInfoSize);

        printf("Connected\n");

        HANDLE newThread = CreateThread(NULL, 0, serverConnection, &newConnection, 0, NULL);

        CloseHandle(newThread);
    }

    closesocket(mainSocket);

    WSACleanup();


    return 0;
}
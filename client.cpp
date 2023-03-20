// Client.cpp : Defines the entry point for the console application.
//
// 1. open the *.c in the Visual C++, then "rebuild all".
// 2. click "yes" to create a project workspace.
// 3. You need to -add the library 'ws2_32.lib' to your project
//    (Project -> Properties -> Linker -> Input -> Additional Dependencies)
// 4. recompile the source.


//#include "stdafx.h"
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "time.h"

#define DEFAULT_PORT	 5019


int userinq(int argc, char **argv);
int addusr(int argc, char **argv);
int updusr(int argc, char **argv);
int delusr(int argc, char **argv);
int addc(int argc, char **argv);
int updc(int argc, char **argv);
int delc(int argc, char **argv);


int main(int argc, char **argv)
{
    while (1)
    {
        int inputins;
        char ent[1];
        printf("\n|********* Welcome to information system ********|");
        printf("\n|------------1:  Inquiry my timetable -----------|");
        printf("\n|------------2:  Add one user -------------------|");
        printf("\n|------------3:  Update one user ----------------|");
        printf("\n|------------4:  Delete one user ----------------|");
        printf("\n|------------5:  Add one course -----------------|");
        printf("\n|------------6:  Update one course --------------|");
        printf("\n|------------7:  Delete one course --------------|");
        printf("\n|------------0:  Exit ---------------------------|");
        printf("\n|************************************************|\n");
        puts("Please input an instruction:");
        scanf("%d", &inputins);
        gets(ent);
        if (inputins == 0)
        {
            puts("Good bye!\n");
            break;
        }
        else if (inputins == 1)
        {
            userinq(argc, argv);
            system("pause");
        }
        else if (inputins == 2)
        {
            addusr(argc, argv);
            system("pause");
        }
        else if (inputins == 3)
        {
            updusr(argc, argv);
            system("pause");
        }
        else if (inputins == 4)
        {
            delusr(argc, argv);
            system("pause");
        }
        else if (inputins == 5)
        {
            addc(argc, argv);
            system("pause");
        }
        else if (inputins == 6)
        {
            updc(argc, argv);
            system("pause");
        }
        else if (inputins == 7)
        {
            delc(argc, argv);
            system("pause");
        }
        else
        {
            puts("Input invalid! Please try again.\n");
        }
    }

    return 0;

}

int userinq(int argc, char **argv)
{
    struct tm t;
    time_t now;


    char szBuff[1300];
    int msg_len;
    //int addr_len;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    SOCKET connect_sock;
    WSADATA wsaData;

    char			*server_name = "localhost";
    unsigned short	port = DEFAULT_PORT;
    unsigned int	addr;

    //puts("Please inpot your user name:");
    //gets(usern);

    //Connection start

    if (argc != 3){
        printf("echoscln [server name] [port number]\n");
        return -1;
    }
    else{
        server_name = argv[1];
        port = atoi(argv[2]);
    }

    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR){
        // stderr: standard error are printed to the screen.
        fprintf(stderr, "WSAStartup failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        //WSACleanup function terminates use of the Windows Sockets DLL.
        WSACleanup();
        return -1;
    }

    if (isalpha(server_name[0]))
        hp = gethostbyname(server_name);
    else{
        addr = inet_addr(server_name);
        hp = gethostbyaddr((char*)&addr, 4, AF_INET);
    }

    if (hp==NULL)
    {
        fprintf(stderr, "Cannot resolve address: %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    //copy the resolved information into the sockaddr_in structure
    memset(&server_addr, 0, sizeof(server_addr));
    memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = hp->h_addrtype;
    server_addr.sin_port = htons(port);


    connect_sock = socket(AF_INET,SOCK_STREAM, 0);	//TCp socket


    if (connect_sock == INVALID_SOCKET){
        fprintf(stderr, "socket() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    printf("Client connecting to: %s\n", hp->h_name);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    if (connect(connect_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))
        == SOCKET_ERROR){
        fprintf(stderr, "connect() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
    }

    //To send instruction
    send(connect_sock, "1", 1, 0);

    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    printf("%s", szBuff);

    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    closesocket(connect_sock);
    WSACleanup();
    //Connection end

    return 0;
}

int addusr(int argc, char **argv)
{
    //printf("Please input user name:\n");
    //Conn(argc, argv);
    struct tm t;
    time_t now;

    char szBuff[1300];
    int msg_len;
    //int addr_len;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    SOCKET connect_sock;
    WSADATA wsaData;

    char			*server_name = "localhost";
    unsigned short	port = DEFAULT_PORT;
    unsigned int	addr;

    if (argc != 3){
        printf("echoscln [server name] [port number]\n");
        return -1;
    }
    else{
        server_name = argv[1];
        port = atoi(argv[2]);
    }

    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR){
        // stderr: standard error are printed to the screen.
        fprintf(stderr, "WSAStartup failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        //WSACleanup function terminates use of the Windows Sockets DLL.
        WSACleanup();
        return -1;
    }

    if (isalpha(server_name[0]))
        hp = gethostbyname(server_name);
    else{
        addr = inet_addr(server_name);
        hp = gethostbyaddr((char*)&addr, 4, AF_INET);
    }

    if (hp==NULL)
    {
        fprintf(stderr, "Cannot resolve address: %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    //copy the resolved information into the sockaddr_in structure
    memset(&server_addr, 0, sizeof(server_addr));
    memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = hp->h_addrtype;
    server_addr.sin_port = htons(port);


    connect_sock = socket(AF_INET,SOCK_STREAM, 0);	//TCp socket


    if (connect_sock == INVALID_SOCKET){
        fprintf(stderr, "socket() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    printf("Client connecting to: %s\n", hp->h_name);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    if (connect(connect_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))
        == SOCKET_ERROR){
        fprintf(stderr, "connect() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
    }

    //To send instruction
    send(connect_sock, "2", 1, 0);

    //Input name
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input course_code
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    printf("Echo from the server: %s\n", szBuff);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    closesocket(connect_sock);
    WSACleanup();
    //Connection end

    return 0;
}

int updusr(int argc, char **argv)
{
    //printf("Please input user name:\n");
    //Conn(argc, argv);
    //printf("User is updated!\n");
    struct tm t;
    time_t now;

    char szBuff[1300];
    int msg_len;
    //int addr_len;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    SOCKET connect_sock;
    WSADATA wsaData;

    char			*server_name = "localhost";
    unsigned short	port = DEFAULT_PORT;
    unsigned int	addr;

    if (argc != 3){
        printf("echoscln [server name] [port number]\n");
        return -1;
    }
    else{
        server_name = argv[1];
        port = atoi(argv[2]);
    }

    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR){
        // stderr: standard error are printed to the screen.
        fprintf(stderr, "WSAStartup failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        //WSACleanup function terminates use of the Windows Sockets DLL.
        WSACleanup();
        return -1;
    }

    if (isalpha(server_name[0]))
        hp = gethostbyname(server_name);
    else{
        addr = inet_addr(server_name);
        hp = gethostbyaddr((char*)&addr, 4, AF_INET);
    }

    if (hp==NULL)
    {
        fprintf(stderr, "Cannot resolve address: %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    //copy the resolved information into the sockaddr_in structure
    memset(&server_addr, 0, sizeof(server_addr));
    memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = hp->h_addrtype;
    server_addr.sin_port = htons(port);


    connect_sock = socket(AF_INET,SOCK_STREAM, 0);	//TCp socket


    if (connect_sock == INVALID_SOCKET){
        fprintf(stderr, "socket() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    printf("Client connecting to: %s\n", hp->h_name);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    if (connect(connect_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))
        == SOCKET_ERROR){
        fprintf(stderr, "connect() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
    }

    //To send instruction
    send(connect_sock, "3", 1, 0);

    //Input name
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input old course_code
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input new course_code (input 0 to pop the student out of this course)
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    printf("Echo from the server: %s\n", szBuff);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    closesocket(connect_sock);
    WSACleanup();
    //Connection end

    return 0;
}

int delusr(int argc, char **argv)
{
    //printf("Please input user name:\n");
    //Conn(argc, argv);
    //printf("User is deleted!\n");
    struct tm t;
    time_t now;

    char szBuff[1300];
    int msg_len;
    //int addr_len;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    SOCKET connect_sock;
    WSADATA wsaData;

    char			*server_name = "localhost";
    unsigned short	port = DEFAULT_PORT;
    unsigned int	addr;

    if (argc != 3){
        printf("echoscln [server name] [port number]\n");
        return -1;
    }
    else{
        server_name = argv[1];
        port = atoi(argv[2]);
    }

    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR){
        // stderr: standard error are printed to the screen.
        fprintf(stderr, "WSAStartup failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        //WSACleanup function terminates use of the Windows Sockets DLL.
        WSACleanup();
        return -1;
    }

    if (isalpha(server_name[0]))
        hp = gethostbyname(server_name);
    else{
        addr = inet_addr(server_name);
        hp = gethostbyaddr((char*)&addr, 4, AF_INET);
    }

    if (hp==NULL)
    {
        fprintf(stderr, "Cannot resolve address: %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    //copy the resolved information into the sockaddr_in structure
    memset(&server_addr, 0, sizeof(server_addr));
    memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = hp->h_addrtype;
    server_addr.sin_port = htons(port);


    connect_sock = socket(AF_INET,SOCK_STREAM, 0);	//TCp socket


    if (connect_sock == INVALID_SOCKET){
        fprintf(stderr, "socket() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    printf("Client connecting to: %s\n", hp->h_name);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    if (connect(connect_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))
        == SOCKET_ERROR){
        fprintf(stderr, "connect() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
    }

    //To send instruction
    send(connect_sock, "4", 1, 0);

    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    printf("Echo from the server: %s\n", szBuff);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    closesocket(connect_sock);
    WSACleanup();
    //Connection end

    return 0;
}

int addc(int argc, char **argv)
{
    //printf("Please input course name:\n");
    //Conn(argc, argv);
    //printf("Course is edited!\n");
    struct tm t;
    time_t now;

    char szBuff[1300];
    int msg_len;
    //int addr_len;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    SOCKET connect_sock;
    WSADATA wsaData;

    char			*server_name = "localhost";
    unsigned short	port = DEFAULT_PORT;
    unsigned int	addr;

    if (argc != 3){
        printf("echoscln [server name] [port number]\n");
        return -1;
    }
    else{
        server_name = argv[1];
        port = atoi(argv[2]);
    }

    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR){
        // stderr: standard error are printed to the screen.
        fprintf(stderr, "WSAStartup failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        //WSACleanup function terminates use of the Windows Sockets DLL.
        WSACleanup();
        return -1;
    }

    if (isalpha(server_name[0]))
        hp = gethostbyname(server_name);
    else{
        addr = inet_addr(server_name);
        hp = gethostbyaddr((char*)&addr, 4, AF_INET);
    }

    if (hp==NULL)
    {
        fprintf(stderr, "Cannot resolve address: %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    //copy the resolved information into the sockaddr_in structure
    memset(&server_addr, 0, sizeof(server_addr));
    memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = hp->h_addrtype;
    server_addr.sin_port = htons(port);


    connect_sock = socket(AF_INET,SOCK_STREAM, 0);	//TCp socket


    if (connect_sock == INVALID_SOCKET){
        fprintf(stderr, "socket() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    printf("Client connecting to: %s\n", hp->h_name);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    if (connect(connect_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))
        == SOCKET_ERROR){
        fprintf(stderr, "connect() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
    }

    //To send instruction
    send(connect_sock, "5", 1, 0);

    //Input name
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input old course_code
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input new course_code (input 0 to pop the student out of this course)
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input name
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input old course_code
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input new course_code (input 0 to pop the student out of this course)
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    printf("Echo from the server %s\n", szBuff);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    closesocket(connect_sock);
    WSACleanup();
    //Connection end


    return 0;
}

int updc(int argc, char **argv)
{
    //printf("Please input course name:\n");
    //Conn(argc, argv);
    //printf("Course is edited!\n");
    struct tm t;
    time_t now;

    char szBuff[1300];
    int msg_len;
    //int addr_len;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    SOCKET connect_sock;
    WSADATA wsaData;

    char			*server_name = "localhost";
    unsigned short	port = DEFAULT_PORT;
    unsigned int	addr;

    if (argc != 3){
        printf("echoscln [server name] [port number]\n");
        return -1;
    }
    else{
        server_name = argv[1];
        port = atoi(argv[2]);
    }

    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR){
        // stderr: standard error are printed to the screen.
        fprintf(stderr, "WSAStartup failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        //WSACleanup function terminates use of the Windows Sockets DLL.
        WSACleanup();
        return -1;
    }

    if (isalpha(server_name[0]))
        hp = gethostbyname(server_name);
    else{
        addr = inet_addr(server_name);
        hp = gethostbyaddr((char*)&addr, 4, AF_INET);
    }

    if (hp==NULL)
    {
        fprintf(stderr, "Cannot resolve address: %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    //copy the resolved information into the sockaddr_in structure
    memset(&server_addr, 0, sizeof(server_addr));
    memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = hp->h_addrtype;
    server_addr.sin_port = htons(port);


    connect_sock = socket(AF_INET,SOCK_STREAM, 0);	//TCp socket


    if (connect_sock == INVALID_SOCKET){
        fprintf(stderr, "socket() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    printf("Client connecting to: %s\n", hp->h_name);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    if (connect(connect_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))
        == SOCKET_ERROR){
        fprintf(stderr, "connect() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
    }

    //To send instruction
    send(connect_sock, "6", 1, 0);

    //Input name
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input old course_code
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input new course_code (input 0 to pop the student out of this course)
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input name
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input old course_code
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input new course_code (input 0 to pop the student out of this course)
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    //Input new course_code (input 0 to pop the student out of this course)
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    printf("Echo from the server: %s\n", szBuff);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    closesocket(connect_sock);
    WSACleanup();
    //Connection end


    return 0;
}

int delc(int argc, char **argv)
{
    struct tm t;
    time_t now;

    char szBuff[1300];
    int msg_len;
    //int addr_len;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    SOCKET connect_sock;
    WSADATA wsaData;

    char			*server_name = "localhost";
    unsigned short	port = DEFAULT_PORT;
    unsigned int	addr;

    if (argc != 3){
        printf("echoscln [server name] [port number]\n");
        return -1;
    }
    else{
        server_name = argv[1];
        port = atoi(argv[2]);
    }

    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR){
        // stderr: standard error are printed to the screen.
        fprintf(stderr, "WSAStartup failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        //WSACleanup function terminates use of the Windows Sockets DLL.
        WSACleanup();
        return -1;
    }

    if (isalpha(server_name[0]))
        hp = gethostbyname(server_name);
    else{
        addr = inet_addr(server_name);
        hp = gethostbyaddr((char*)&addr, 4, AF_INET);
    }

    if (hp==NULL)
    {
        fprintf(stderr, "Cannot resolve address: %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    //copy the resolved information into the sockaddr_in structure
    memset(&server_addr, 0, sizeof(server_addr));
    memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = hp->h_addrtype;
    server_addr.sin_port = htons(port);


    connect_sock = socket(AF_INET,SOCK_STREAM, 0);	//TCp socket


    if (connect_sock == INVALID_SOCKET){
        fprintf(stderr, "socket() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    printf("Client connecting to: %s\n", hp->h_name);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    if (connect(connect_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))
        == SOCKET_ERROR){
        fprintf(stderr, "connect() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
    }

    //To send instruction
    send(connect_sock, "7", 1, 0);

    //Input new course_code (input 0 to pop the student out of this course)
    memset(szBuff,0,sizeof(szBuff));
    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);
    printf("%s", szBuff);
    memset(szBuff,0,sizeof(szBuff));
    gets(szBuff);
    msg_len = send(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    msg_len = recv(connect_sock, szBuff, sizeof(szBuff), 0);

    if (msg_len == SOCKET_ERROR)
    {
        fprintf(stderr, "send() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    if (msg_len == 0)
    {
        printf("server closed connection\n");
        time(&now);
        localtime_s(&t, &now);
        printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        closesocket(connect_sock);
        WSACleanup();
        return -1;
    }

    printf("Echo from the server %s\n", szBuff);
    time(&now);
    localtime_s(&t, &now);
    printf("Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    closesocket(connect_sock);
    WSACleanup();
    //Connection end


    return 0;
}
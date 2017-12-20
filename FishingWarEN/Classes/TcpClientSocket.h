#ifndef _TCP_CLIENT_SOCKET_H_
#define _TCP_CLIENT_SOCKET_H_

// 注意 仅支持 单线程

#include "cocos2d.h" 

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include <WINSOCK2.H>
#pragma comment(lib, "wsock32.lib")

#else

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h> 
#endif
 
#define GAMEIP  "192.168.1.123"
#define GAMEPORT  (6000)

#define LOGINIP  "192.168.1.123"
#define LOGINPORT  (7000)


#define	FIRSTLOGINSEND              1
#define	FIRSTLOGINBAK               2
#define	CHONGZHISEND				3
#define	CHONGZHIBAK					4


struct	FirstLoginSend
{
    bool     applyAccount;//申请账号
};
struct	FirstLoginBak
{
    int		account;//账号
};


struct	ChongZhiSend
{
    int 		account;
};
struct	ChongZhiBak
{
    int		coin;
    int		diamond;
};



  struct  fishHead
{
	char 	type;
	int 	len;
	char 	local[0];
};  



class TcpClientSocket
{
public:

	TcpClientSocket(int iReadBufferLen = 4096);
	virtual ~TcpClientSocket();

	bool ConnectServer(char *pServerIP,unsigned short ServerPort);
	void CloseSocket();

	// 传回 是否 连线中
	bool IsConnect(void);

	bool SendPack(char *pPackBuffer, int PackLength);
	bool RecvPack(char **ppPackBuffer, int &PackLength);
	bool RecvNewPack(char *pPackBuffer,int PackLength);
	bool SendMsgToSocket(void *pMessage, unsigned short MessageType, int MessageLength);

	bool SendMsgToSocketxxx();

	// 清除 已使用的缓存
	void CleanRecvBuffer(int UsedBuuferLength);

protected:

	int	m_RecvBufferLength;
	int	m_RecvBufferUsedCounter;
	char *m_pRecvBuffer;

private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SOCKET  m_Socket;
#else
	int  m_Socket;
#endif
};

#endif

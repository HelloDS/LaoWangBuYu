#include "TcpClientSocket.h"
#include <stdio.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)	
	// 設定 Socket 為 強迫 關閉
	void SetSocketLingerOFF(SOCKET SocketFD)
	{
		// 强制关闭
		linger m_sLinger;
		m_sLinger.l_onoff = 1;
		m_sLinger.l_linger = 0;

		setsockopt(SocketFD, SOL_SOCKET, SO_LINGER, (const char *) &m_sLinger, sizeof(m_sLinger));

		// 服务器 bind 设定
		int option = 1;
		setsockopt(SocketFD, SOL_SOCKET, SO_REUSEADDR, (char *) &option, sizeof(option));

		// No Delay
		setsockopt(SocketFD, IPPROTO_TCP, TCP_NODELAY, (char *) &option, sizeof(option));

		// 设定 非阻塞
		unsigned long tmepOption = 1;
		ioctlsocket(SocketFD, FIONBIO, &tmepOption);
	}
#else

	// 設定 Socket 為 強迫 關閉
	void SetSocketLingerOFF(int SocketFD)
	{
		// 强制关闭
		linger m_sLinger;

		m_sLinger.l_onoff = 1;
		m_sLinger.l_linger = 0;

		setsockopt(SocketFD, SOL_SOCKET, SO_LINGER, (const char *) &m_sLinger, sizeof(m_sLinger));

		// 服务器 bind 设定
		int option = 1;
		setsockopt(SocketFD, SOL_SOCKET, SO_REUSEADDR, (char *) &option, sizeof(option));

		// No Delay
		setsockopt(SocketFD, IPPROTO_TCP, TCP_NODELAY, (char *) &option, sizeof(option));

		// 设定 非阻塞
		int flag = fcntl(SocketFD, F_GETFL, 0);
		fcntl(SocketFD, F_SETFL, flag | O_NONBLOCK);
	}

#endif

TcpClientSocket::TcpClientSocket(int ReadBufferLen)
{

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		// Socket Init
	WSADATA wsaData;
	int ReturnValue = WSAStartup(MAKEWORD(2,2), &wsaData);
	#endif

	this->m_pRecvBuffer = new char[ReadBufferLen * 2];
	this->m_RecvBufferLength = ReadBufferLen;
	this->m_RecvBufferUsedCounter = 0;
	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		this->m_Socket = INVALID_SOCKET;

	#else

		this->m_Socket = -1;

	#endif
}

TcpClientSocket::~TcpClientSocket()
{	
	delete [] this->m_pRecvBuffer;
}

bool TcpClientSocket::ConnectServer(char *pServerIP,unsigned short ServerPort)
{
	this->CloseSocket();

	struct sockaddr_in 	addrServer;

	#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		SOCKET tempSocket = INVALID_SOCKET;
	#else
		int tempSocket = -1;
	#endif
    
		memset(&addrServer, 0, sizeof(addrServer));
		addrServer.sin_family = AF_INET;
		addrServer.sin_port = htons(ServerPort);
		addrServer.sin_addr.s_addr = inet_addr(pServerIP);

	if((tempSocket = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		return false;
	}

	if( connect(tempSocket, (struct sockaddr *)&addrServer, sizeof(addrServer)) < 0)
	{
		return false;
	}

	// 设定 Socket 属性
	SetSocketLingerOFF(tempSocket);   

	this->m_Socket = tempSocket;
	
	return true;
}

void TcpClientSocket::CloseSocket()
{
	// 接收 缓存索引 归零
	this->m_RecvBufferUsedCounter = 0;

	if(this->m_Socket < 0)
	{
		return;
	}
	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		shutdown(this->m_Socket, SD_BOTH);
		closesocket(this->m_Socket);
		this->m_Socket = INVALID_SOCKET;

	#else	

		shutdown(this->m_Socket, 2);
		close(this->m_Socket);
		this->m_Socket = -1;

	#endif
}

bool TcpClientSocket::IsConnect(void)
{

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		if(this->m_Socket != INVALID_SOCKET)
		{
			return true;
		}
		else
		{
			return false;
		}

	#else

		if(this->m_Socket >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	#endif
}

bool TcpClientSocket::RecvPack(char **ppPackBuffer, int &PackLength)
{
	*ppPackBuffer = this->m_pRecvBuffer;

	PackLength = this->m_RecvBufferUsedCounter;

	if(!this->IsConnect())
	{
		return false;
	}

	int tempRecvLength = recv(this->m_Socket, this->m_pRecvBuffer + this->m_RecvBufferUsedCounter, this->m_RecvBufferLength, 0);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		// 錯誤 處理
		if(tempRecvLength < 0) 
		{
			int tempError = WSAGetLastError();  

			if(tempError == WSAEWOULDBLOCK)
			{
				return true;
			}

			//關閉 socket
			this->CloseSocket();	

			return false;
		}
		else if(tempRecvLength == 0)
		{
			//關閉socket
			this->CloseSocket();
			return false;
		}

	#else

		// 錯誤 處理
		if(tempRecvLength < 0)
		{
			// 由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可读
            // 在这里就当作是该次事件已处理处.
			//即当buflen < 0 且 errno == EAGAIN时，表示没有数据了。(读/写都是这样)
            if(errno == EAGAIN || errno == EINTR)  
			{
                return true;
			}

			// 關閉 socket
			this->CloseSocket();		

			return false;	
		}
		else if(tempRecvLength == 0)
		{
			// 關閉 socket
			this->CloseSocket();		

			return false;	
		}

	#endif

	this->m_RecvBufferUsedCounter += tempRecvLength;

	PackLength = this->m_RecvBufferUsedCounter;

	return true;
}
//new recv 
bool TcpClientSocket::RecvNewPack(char *pPackBuffer,int PackLength)
{
	int tempRecvLength = recv(this->m_Socket, pPackBuffer , PackLength, 0);
	if(tempRecvLength>0)
		return true;
	if(!this->IsConnect())
	{
		return false;
	}
	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		// 錯誤 處理
		if(tempRecvLength < 0) 
		{
			int tempError = WSAGetLastError();  

			if(tempError == WSAEWOULDBLOCK)
			{
				return true;
			}

			//關閉 socket
			this->CloseSocket();	

			return false;
		}
		else if(tempRecvLength == 0)
		{
			//關閉socket
			this->CloseSocket();
			return false;
		}

	#else

		// 錯誤 處理
		if(tempRecvLength < 0)
		{
			// 由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可读
            // 在这里就当作是该次事件已处理处.
			//即当buflen < 0 且 errno == EAGAIN时，表示没有数据了。(读/写都是这样)
            if(errno == EAGAIN || errno == EINTR)  
			{
                return true;
			}

			// 關閉 socket
			this->CloseSocket();		

			return false;	
		}
		else if(tempRecvLength == 0)
		{
			// 關閉 socket
			this->CloseSocket();		

			return false;	
		}

	#endif

	/*this->m_RecvBufferUsedCounter += tempRecvLength;

	PackLength = this->m_RecvBufferUsedCounter;*/

	return true;
}
// 清除 已使用的缓存
void TcpClientSocket::CleanRecvBuffer(int UsedBuuferLength)
{
	// 防呆
	if(UsedBuuferLength <= 0)
	{
		// 不处理 任何事情
		return;
	}

	// 清除 全部缓存
	if(this->m_RecvBufferUsedCounter <= UsedBuuferLength)
	{
		this->m_RecvBufferUsedCounter = 0;
		return;
	}

	// Copy 未使用 缓存
	int tempUnusedBufferCounter = this->m_RecvBufferUsedCounter - UsedBuuferLength;

	char *ptempBuffer = new char[tempUnusedBufferCounter];

	memcpy(ptempBuffer, this->m_pRecvBuffer + UsedBuuferLength, tempUnusedBufferCounter);
	memcpy(this->m_pRecvBuffer, ptempBuffer, tempUnusedBufferCounter);

	delete [] ptempBuffer;

	this->m_RecvBufferUsedCounter = tempUnusedBufferCounter;
}

bool TcpClientSocket::SendPack(char *pPackBuffer, int PackLength)
{
	if(!this->IsConnect())
	{
		return false;
	}

	if(PackLength <= 0)
	{			
		return false;
	}

	if(pPackBuffer == NULL)
	{			
		return false;
	}	
	
	unsigned int tempIndex = 0;
	while(PackLength > 0)
	{
		int SendBytes =  send(this->m_Socket, (const char *)pPackBuffer , PackLength, 0);
		cocos2d::log("zijie %d" , SendBytes); 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		  // 錯誤 處理
			if(SendBytes <= 0) 
			{
				// 關閉 socket
				this->CloseSocket();		
				return false;									
			}

		#else

			// 錯誤 處理
			if(SendBytes < 0)
			{
				// 由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可读
                // 在这里就当作是该次事件已处理处.
				//即当buflen < 0 且 errno == EAGAIN时，表示没有数据了。(读/写都是这样)
                if(errno == EAGAIN || errno == EINTR)  
				{
                    break;
				}

				// 關閉 socket
				this->CloseSocket();		

				return false;	
			}
			else if(SendBytes == 0) 
			{
				// 關閉 socket
				this->CloseSocket();		

				return false;									
			}

		#endif

	 

		// 防呆
		if(PackLength >= SendBytes)
		{
			PackLength -= SendBytes;
		}
		else
		{
			PackLength = 0;
		}
	}

	return true;
}

bool TcpClientSocket::SendMsgToSocket(void *pMessage, unsigned short MessageType, int MessageLength)
{

	if(!this->IsConnect())
	{
		return false;
	}

	if(MessageLength <= 0)
	{			
		return false;
	}

	if(pMessage == NULL)
	{			
		return false;
	}	

	//取得头的结构体，给头赋值。。

	//__CCLOGWITHFUNCTION("the Type is  -----------------MessageType%d  ",MessageType );
	  
	fishHead *pHead ;
	pHead=(fishHead *)malloc(sizeof(fishHead)+MessageLength);
	pHead->type=MessageType;
	pHead->len =  htonl(MessageLength);
	memcpy(pHead->local,pMessage,MessageLength); 
	
	this->SendPack((char*)pHead,sizeof(fishHead)+MessageLength);

	return true;
}
bool TcpClientSocket::SendMsgToSocketxxx()
{ 
	 
	/*MsgHeadDef pHead ;
	pHead.identity = IDENTIFY_VER;
	pHead.encode = ENCODE_NONE;
	pHead.length = 0;
	pHead.version = MESSAGE_VER;
	pHead.reserve = 0;
	pHead.cMsgType = 0;

	this->SendPack((char*)&pHead,sizeof(MsgHeadDef));
	//send(this->m_Socket, (const char *)&pHead, sizeof(MsgHeadDef), 0);	
	 */
	return true;
	
}



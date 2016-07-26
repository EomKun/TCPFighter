#ifndef __NETWORK__H__
#define __NETWORK__H__

#define WM_NETWORK (WM_USER+1)

BOOL InitialNetwork(SOCKET *sock, HWND *hWnd);

int MakePacket_MoveStart(st_NETWORK_PACKET_HEADER *pHeader, char *pPacket,
	int iDir, int iX, int iY);
int MakePacket_MoveStop(st_NETWORK_PACKET_HEADER *pHeader, char *pPacket,
	int iDir, int iX, int iY);


int MakePacket_Attack1(st_NETWORK_PACKET_HEADER *pHeader, char *pPacket,
	int iDir, int iX, int iY);
int MakePacket_Attack2(st_NETWORK_PACKET_HEADER *pHeader, char *pPacket,
	int iDir, int iX, int iY);
int MakePacket_Attack3(st_NETWORK_PACKET_HEADER *pHeader, char *pPacket,
	int iDir, int iX, int iY);
#endif
// 2021/04/02 22:37:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#define FAR

typedef char CHAR;
typedef __int64 LONG_PTR, *PLONG_PTR;
typedef LONG_PTR SSIZE_T, *PSSIZE_T;
typedef unsigned short  u_short;
typedef unsigned __int64 UINT_PTR, *PUINT_PTR;
typedef unsigned short USHORT;
typedef USHORT ADDRESS_FAMILY;
typedef unsigned short      WORD;
typedef UINT_PTR        SOCKET;
enum class byte : unsigned char {};
typedef unsigned char BYTE;
typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

#define SD_RECEIVE      0x00
#define SD_SEND         0x01
#define SD_BOTH         0x02

#define SHUT_RD SD_RECEIVE
#define SHUT_WR SD_SEND
#define SHUT_RDWR SD_BOTH

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

#define AF_UNSPEC       0               /* unspecified */

#define _SS_MAXSIZE 128                 // Maximum size
#define _SS_ALIGNSIZE (sizeof(__int64)) // Desired alignment

#if(_WIN32_WINNT >= 0x0600)
#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof(USHORT))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof(USHORT) + _SS_PAD1SIZE + _SS_ALIGNSIZE))
#else
#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof (short))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof (short) + _SS_PAD1SIZE \
                                                    + _SS_ALIGNSIZE))
#endif //(_WIN32_WINNT >= 0x0600)

struct timeval {
    long    tv_sec;         /* seconds */
    long    tv_usec;        /* and microseconds */
};

typedef struct sockaddr {

#if (_WIN32_WINNT < 0x0600)
    u_short sa_family;
#else
    ADDRESS_FAMILY sa_family;           // Address family.
#endif //(_WIN32_WINNT < 0x0600)

    CHAR sa_data[14];                   // Up to 14 bytes of direct address.
} SOCKADDR, *PSOCKADDR, FAR *LPSOCKADDR;


typedef struct sockaddr_storage {
    ADDRESS_FAMILY ss_family;      // address family

    CHAR __ss_pad1[_SS_PAD1SIZE];  // 6 byte pad, this is to make
                                   //   implementation specific pad up to
                                   //   alignment field that follows explicit
                                   //   in the data structure
    __int64 __ss_align;            // Field to force desired structure
    CHAR __ss_pad2[_SS_PAD2SIZE];  // 112 byte pad to achieve desired size;
                                   //   _SS_MAXSIZE value minus size of
                                   //   ss_family, __ss_pad1, and
                                   //   __ss_align fields is 112
} SOCKADDR_STORAGE_LH, *PSOCKADDR_STORAGE_LH, FAR *LPSOCKADDR_STORAGE_LH;

typedef struct WSAData {
    WORD                    wVersion;
    WORD                    wHighVersion;
#ifdef _WIN64
    unsigned short          iMaxSockets;
    unsigned short          iMaxUdpDg;
    char FAR *lpVendorInfo;
    char                    szDescription[WSADESCRIPTION_LEN + 1];
    char                    szSystemStatus[WSASYS_STATUS_LEN + 1];
#else
    char                    szDescription[WSADESCRIPTION_LEN + 1];
    char                    szSystemStatus[WSASYS_STATUS_LEN + 1];
    unsigned short          iMaxSockets;
    unsigned short          iMaxUdpDg;
    char FAR *lpVendorInfo;
#endif
} WSADATA;

typedef WSADATA FAR *LPWSADATA;

#define PASCAL      __stdcall
#define IN

int PASCAL FAR WSAGetLastError(void);

int PASCAL FAR closesocket(IN SOCKET s);

int PASCAL FAR WSAStartup(
    _In_ WORD wVersionRequired,
    _Out_ LPWSADATA lpWSAData);

int PASCAL FAR WSACleanup(void);

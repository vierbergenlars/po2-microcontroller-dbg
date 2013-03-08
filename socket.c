/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Lars Vierbergen nor the name of any other
 *    contributor may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Lars Vierbergen AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL Lars Vierbergen OR ANY OTHER
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#define SOCKET_DEBUG 0
#include <stdio.h> // printf();
#include <stdlib.h> // exit();
#include <errno.h> // errno
#include <string.h> // strcmp(), strlen(), strcpy()
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> // unix sockets
#include <unistd.h> // close()
void socket_fail(int err, char desc[]) {
	perror(desc);
	printf("[E] Socket(%d): %s\n", err, desc);
	exit(1);
};

unsigned int socket_init(char filename[]) {
	struct sockaddr_un local;
	int len;
	unsigned int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sock == -1)
		socket_fail(errno, "Cannot create socket");

	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, filename);
	len = strlen(local.sun_path) + sizeof(local.sun_family);
	if(bind(sock, (struct sockaddr *)&local, len) == -1)
		socket_fail(errno, "Cannot bind socket");

	if(listen(sock, 1) == -1)
		socket_fail(errno, "Cannot listen socket");
	printf("Socket: opened %s\n", filename);
	return sock;
};

void socket_loop(unsigned int sock, void (*func)(char [100], char [100])) {
	struct sockaddr_un remote;
	socklen_t len = sizeof(struct sockaddr_un);
	int s2;
	int n;
	char str[100];
	char return_data[100];

	while (1) {
		printf("Socket: Waiting for client...");
		s2 = accept(sock, (struct sockaddr *)&remote, &len);

		if(s2 == -1)
			socket_fail(errno, "Cannot accept socket");
		printf("[OK]\n");

		while(1) {
			//str[0] = "\0";
			strncpy(str, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", sizeof(str));
			strncpy(return_data, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", sizeof(return_data));
			n = recv(s2, str, 100, 0);
			if(n <=0) {
				if(n < 0) socket_fail(errno, "Cannot recv from socket");
			}
			#if SOCKET_DEBUG
			printf("DEBUG: str(%d) is `%s`\n", strlen(str), str);
			#endif
			if(strncmp(str, "close", 5) == 0) {
				printf("Socket: Connection closed\n");
				close(s2);
				break;
			}

			func(str, return_data);
			#if SOCKET_DEBUG
			printf("DEBUG: return_data(%d) is `%s`\n", strlen(return_data), return_data);
			#endif
			if(send(s2, return_data, 100, 0) < 0)
				socket_fail(errno, "Cannot send to socket");
		}
	}
};

void socket_close(unsigned int sock) {
	printf("Socket: closed\n");
	close(sock);
};

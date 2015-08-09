#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;
bool tcp_con (int& port) {
	int sock = socket (AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in link;
	char srvc_name [1025];
	const char *http_req = "HEAD / HTTP/1.0\n\n";
	bool sockClosed = false;

	link.sin_family = AF_INET;
	link.sin_addr.s_addr = inet_addr ("127.0.0.1");
	link.sin_port = htons (port);

	if (connect (sock, (struct sockaddr *) &link, sizeof (link)) == 0) {
		//a work-around for the services which expect the client to initiate the conversation. We are not interested in sending any messages but we realize that we have connected to the service, so we close () the connection
		if (port == 631 || port == 587 || port == 80 || port == 25) {
			close (sock);
			sockClosed = true;
		}

		if (!sockClosed) {
			recv (sock, srvc_name, 1024, 0);
			cout << srvc_name << '\t';
			close (sock);
		}
		return (true);
	}

	return (false);
}

int main () {
	for (int port = 1; port <= 95000; port++) {
		if (tcp_con (port)) {
			cout << "Port " << port << " open" << endl;
		}
	}

	return (0);
}

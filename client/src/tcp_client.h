#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

int start_client(void);
int transmit(int socket, char* data, short length);
int receive(int socket, char* output, short length);
void disconnect(int socket);

#endif // infdef TCP_CLIENT_H
#include <tcp_client.h>

int main(void) {
    char reset[] = { 'r', 'e', 's', 'e', 't' };
    char* atr;
    int socket = start_client();

    transmit(socket, reset, sizeof(reset) / sizeof(char));
    receive(socket, atr, 13);

    return 0;
}

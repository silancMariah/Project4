#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jtag_atlantic.h>
#include <signal.h>
#include <unistd.h>

static int running = 1;

void handle_sigint(int sig){
    running = 0;
}

int main(){
    JTAGATLANTIC *atlantic;
    unsigned char buf[1024];

    signal(SIGINT, handle_sigint);

    atlantic = jtagatlantic_open(NULL, 0, -1, NULL);
    if(!atlantic){
        fprintf(stderr, "Unable to open JTAG Atlantic connection.\n");
        return 1;
    }

    printf("Listening on port 6666...\n");

    while(running){
        int n = jtagatlantic_read(atlantic, buf, sizeof(buf));
        if (n > 0){
            fwrite(buf, 1, n, stdout);
            fflush(stdout);
        }
        usleep(1000);
    }

    jtagatlantic_close(atlantic);
    return 0;
}

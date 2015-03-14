#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "rfm12.h"
#include "funksteckdose.h"

#define TAKT_US 330

bool tx[24];

void send_bit (bool i) {
        rfm12_tx_on();
        if (i) {
                usleep(TAKT_US * 3);
        } else {
                usleep(TAKT_US);
        }

        rfm12_tx_off();

        if (i) {
                usleep(TAKT_US);
        } else {
                usleep(TAKT_US * 3);
        }
}

void send_frame (bool data[24]) {
	int i,j;

	for (j=0;j<20;j++) {
	for (i=0;i<24;i++) {
		send_bit(data[i]);

	}

	send_sync();
	}

}

void send_sync (void) {
	send_bit(false);
	usleep(TAKT_US * 28);
}


int main (int argc, const char *argv[] )
{
	rfm12_set_spi_device("/dev/spidev0.0");

	if (argc != 5) {
		usage(argv[0]);
		exit(0);
	}

	parseArguments(argv);

	rfm12_init();
	usleep(100000);
	rfm12_init();
	usleep(100000);

	send_frame(tx);
	rfm12_tx_off();

	return 0;
}

void parseCode (const char *argv, bool *target) {
	int i;

	for (i=0;i<strlen(argv);i++) {
                if (argv[i] == '0') {
                        target[(i*2)] = false;
                        target[(i*2)+1] = false;

                } else {
                        target[(i*2)] = false;
                        target[(i*2)+1] = true;
                }
        }
	
}
void parseArguments (const char **argv) {
	if (strlen(argv[1]) != 10) {
		usage(argv[0]);
		exit(0);
	}

	if (strlen(argv[2]) != 2) {
		usage(argv[0]);
		exit(0);
	}

	if (strlen(argv[3]) != 2) {
		usage(argv[0]);
		exit(0);
	}

	parseCode(argv[1], tx);

	if (strcmp(argv[4], "on")) {
		parseCode(argv[3], tx+20);
	} else {
		parseCode(argv[2], tx+20);
	}

}

void usage (const char *progName) {
	printf("Usage: %s [CODE] [OFF] [ON] [STATE]\n\n", progName);
	printf("[CODE]  The calculated system+device code. 10 byte length, use 0 and F for false and true. For more information see [1]\n");
	printf("[OFF]   The off code, usually F0\n");
	printf("[ON]    The on code, usually 0F\n");
	printf("[STATE] Either the keyword 'off' or 'on'\n\n");
	printf("[1] http://www.fhemwiki.de/wiki/Intertechno_Code_Berechnung\n\n");
}

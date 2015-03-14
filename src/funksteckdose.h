#ifndef _FUNKSTECKDOSE_H
#define _FUNKSTECKDOSE_H


/**
* Sends a single bit via RFM12
*/
void send_bit (bool i);

/**
* Sends a frame with 24 bits via RFM12
*/
void send_frame (bool data[24]);

/**
* Sends a sync frame
*/
void send_sync (void);

/**
* Parses the code passed via the command line and writes it to the transmit buffer
*/
void parseCode (const char *argv, bool *target);

/**
* Parses the arguments
*/
void parseArguments (const char **argv);

/**
* Prints the usage information
*/
void usage (const char *progName);

#endif
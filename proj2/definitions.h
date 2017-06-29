/* definition header
 *
 * contains variables that can be changed to modify the behavior
 */


#ifndef DEFINITIONS_H
#define DEFINITIONS_H

////////////////////////////////////////////////////////////////////////////////
// Definitions from simulation

#define SIMULATE1                   // Change to which simulation

//#define DELAY
#define SIZE_MAP 18                 // Radius of the comunication with the router
#define MAX_SPEED 5                // Streets max speed
#define N_CONNECTIONS 20            // How many cars can talk to the router
#define PACKAGE_INTERVAL 25         // Time to send the packages (in ms)
#define SPEED_INTERVAL 10           // Block_walking = Speed/SPEED_INTERVAL(in ms)

////////////////////////////////////////////////////////////////////////////////
// Definitions from server

#define ENT_PORT 42009
#define SEC_PORT 43009
#define CON_PORT 44009

#define CON_TCP                     // Set to TCP or UDP
#define ENT_TCP                     // Set to TCP or UDP
#define SEC_TCP                     // Set to TCP or UDP

#define DELAY_CON 100
#define DELAY_ENT 100
#define DELAY_SEC 100

#define PKG_ENT_SIZE 1000
#define PKG_SEC_SIZE 30
#define PKG_CON_SIZE 1000

#define SEC_ADDRESS "localhost"
#define CON_ADDRESS "localhost"
#define ENT_ADDRESS "localhost"

////////////////////////////////////////////////////////////////////////////////
// Define if should print the info from the packages or should demonstrate the
// simulation on NCURSES
#define NCURSES_SIMULATE              // Enable this if want to see cars walking

#endif

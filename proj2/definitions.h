/* definition header
 *
 * contains variables that can be changed to modify the behavior
 */


#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define SIMULATION1                 // Change to which simulation

#define TCP                         // Use TCP or UDP
#define SIZE_MAP 18                 // Radius of the comunication with the router
#define MAX_SPEED 3                 // Streets max speed
#define N_CONNECTIONS 20            // How many cars can talk to the router
#define PACKAGE_INTERVAL 25         // Time to send the packages (in ms)
#define SPEED_INTERVAL 10           // Block_walking = Speed/SPEED_INTERVAL(in ms)


#define SEC_ADDRESS "localhost"
#define CON_ADDRESS "localhost"
#define ENT_ADDRESS "localhost"


#define NCURSES_SIMULATE            // Enable this if want to see cars walking

#endif

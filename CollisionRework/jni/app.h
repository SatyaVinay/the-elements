/*
 * app.h
 * --------------------------------
 * Contains all the extern declarations for
 * our variables, so that they are essentially
 * global external variables accessible from
 * all files necessary.
 */

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED
MAX_POINTS

#ifdef __cplusplus
extern "C" {
#endif

//Include the global macros
#include "macros.h"

/*
 * FUNCTIONS
 */

int getIndex(int x, int y);

/*
 * VARIABLES
 */

//extern int gAppAlive; //I don't think this is needed, commenting...

//Current element selected
extern int cElement;
//Current point during processing
extern int cPoint;
//Play state
extern int play;
//Size variable initialize it here so we don't have to do it in resetup and we can keep our brush size
extern int brushSize;

//The number of elements available
extern int numElements;

//Array for bitmap drawing
extern unsigned char colors[];

//Screen dimensions
extern int screenWidth;
extern int screenHeight;
//Workspace dimensions
extern int workWidth;
extern int workHeight;

//Coordinates
extern float x[];
extern float y[];
//Old coordinates (for collision resolving)
extern short int oldx[];
extern short int oldy[];
//Velocities
extern short int xvel[];
extern short int yvel[];

//Element type
extern char element[];
//Frozen state
extern char frozen[];

//RGB properties (variable arrays)
extern unsigned char *red;
extern unsigned char *green;
extern unsigned char *blue;
//Fall velocity property (a variable-size array)
extern int *fallVel;
//Density property - 1 - 10 (a variable-size array)
extern int *density;
//State property - solid = 0, liquid = 1, gaseous = 2 (a variable-size array)
extern int *state;
//Special property - indexed special effects occurring every frame (a variable-size array)
extern int *special;
//Special value - a number used in special effects (if any)
extern int specialVal[];
//Heat value - 1 - 10
extern int heat[];

//Collision matrix
extern int collision[][];

//Index set state
extern int set[];
//Index available state
extern int avail[];

//Points to the index AFTER the top of the stack
extern int loq;
//Zoom value
extern int zoom;

/* Accelerometer stuff being taken out for now
//Gravity values
float gravX;
float gravY;

//Accelerometer control state
int accelcon;
//Flipped state
int flipped;
*/
//Screen dimensions
int screenWidth;
int screenHeight;
//Workspace dimensions
int workWidth;
int workHeight;
//Set when a clear is requested, unset when cleared
extern char shouldClear;
//Set when a mouse update is requested, unset when udpated
extern char shouldUpdateMouse;

//Finger state
extern int fingerState;

//A map of all the points (a two-dimensional variable-size array)
extern int *allcoords;

//Mouse positions
extern int mouseX;
extern int mouseY;
//Old mouse positions
extern int lastMouseX;
extern int lastMouseY;

/*Network stuff taken out for now
//Buffer building variables
char username[8];
char password[8];
char userlength;
char passlength;
char buffer[3 + 1 + (2 * TPoints * 4) + 200];
int bufferlength;

//Error variable
char* error;

//Socket variables
int sockfd; //The file descriptor for the socket
int n; //Used in sending and recieving data
struct sockaddr_in serv_addr; //The server address struct
struct hostent *server; //Pointer to a hostent struct that is used to set up serv_addr
*/

#ifdef __cplusplus
}
#endif


#endif // !APP_H_INCLUDED
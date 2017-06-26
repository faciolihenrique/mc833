#define SIZE_MAP 80
#define PKG_ENTERTAINEMENT_SIZE
#define PKG_SECURITY_SIZE
#define PKG_CONFORT_SIZE
#define SIZE_CAR 4
#define SIZE_TRUCK
#define SIZE_DOUBLETRUCK

/* "Define" a type just to make it more readable */
#define Speed int

/*~~~~~~ Data Structures ~~~~~~~*/

typedef enum car_type {Car, Truck, DoubleTruck} CarType;
typedef enum direction {North, West, South, East} Direction;

/* Position struct */
typedef struct {
    int x;
    int y;
} Position;

/* Vehicle */
typedef struct {
    CarType type;
    int w_size;
    Speed car_speed;
    Direction dir;
    Position pos;
} Vehicle;

/* Package sent */
typedef struct {
    Position pos;
    Direction dir;
    Speed car_speed;
} Package;


int map[SIZE_MAP][SIZE_MAP];

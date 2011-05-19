#ifndef LSUTILITY_H

// Defines...
#define WINDOW_WIDTH  (640)
#define WINDOW_HEIGHT (480)

//#include "Landscape.h"
class Landscape;

// Globals...
extern long gStartTime, gEndTime;
extern int gNumFrames;
extern unsigned char *gHeightMap;
extern int gAnimating;
extern int gRotating;
extern int gStartX, gStartY;

// Functions...
extern void ReduceToUnit(float vector[3]);
extern void calcNormal(float v[3][3], float out[3]);
extern void loadTerrain(int size, unsigned char **dest);
extern void freeTerrain();

extern int roamInit(Landscape& land, unsigned char *map);

#define LSUTILITY_H
#endif //LSUTILITY_H
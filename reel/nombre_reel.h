// Didier Teifreto - Octobre 2021
// Macro conversion de type reel <-> representation mémoire
#define  FLOAT_TO_INT_BITS(f) ( *(unsigned*)&(f) )
#define  INT_BITS_TO_FLOAT(i) ( *(float*)&(i) )

unsigned getSigne(float reel);
int getExposant(float reel);
unsigned getMantisse(float reel);
float setSigne(float reel,unsigned signe);
float setExposant(float reel,int exposant);
float setMantisse(float reel,unsigned mantisse);
float maximumFloat();

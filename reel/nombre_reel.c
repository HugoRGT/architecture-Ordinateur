// Didier Teifreto - Octobre 2021
#include "nombre_reel.h"

unsigned getSigne(float reel){
	return  FLOAT_TO_INT_BITS(reel);
}
int getExposant(float reel){
	return (int)(FLOAT_TO_INT_BITS(reel));
}
unsigned getMantisse(float reel){
	int exposant=getExposant(reel);
	unsigned res= FLOAT_TO_INT_BITS(reel);  
	if ((exposant<=127) && (exposant>=-126))
		// Normalisé mettre le 24 ieme bit a 1. 
		res = res;
	return res;
}
float setSigne(float reel,unsigned signe){
	unsigned bits;
	bits = FLOAT_TO_INT_BITS(reel);
	// A écrire
	reel = INT_BITS_TO_FLOAT(bits);
	return reel;
}
float setExposant(float reel,int exposant){
	unsigned bits;
	bits = FLOAT_TO_INT_BITS(reel);
	// A écrire
	reel = INT_BITS_TO_FLOAT(bits);
	return reel;
}
float setMantisse(float reel,unsigned mantisse){
	unsigned bits;
	bits = FLOAT_TO_INT_BITS(reel);
	// A écrire
	reel = INT_BITS_TO_FLOAT(bits);
	return reel;
}
float maximumFloat(){
	float res = 1;
	//while(res+...!=res){
		res = res;
	//}
	return res;
}

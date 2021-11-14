// Didier Teifreto - Octobre 2021
#include <stdio.h> 
#include <string.h> 
#include "nombre_reel.h"

int resOK=0,resErreur=0,score=0;


#define testEQ(ok,res,increment) printf("Attendu: %d,Trouvé: %d",res,ok);if (ok==res){ printf("->Correct\n");resOK++;score=score+increment;} else {printf("->Erreur\n");resErreur++;}

#define testEQHEX(ok,res,increment) printf("Attendu: 0x%x,Trouvé: 0x%x",res,ok);if (ok==res){ printf("->Correct\n");resOK++;score=score+increment;} else {printf("->Erreur\n");resErreur++;}

#define testSTREQ(ok,res,increment) printf("Attendu: \"%s\",Trouvé:\"%s\"",res,ok);if (strcmp(ok,res)==0){ printf("->Correct\n");resOK++;score=score+increment;} else {printf("->Erreur\n");resErreur++;}


int test(){
	float N1=125.25f,N2=0.375f,N3=-0.1f,N4=0,f=-1;
	printf("---- Valeurs mémoires ----\n");
	printf("125.25 -> 0x%x\n",FLOAT_TO_INT_BITS(N1));
	printf("-0.375 -> 0x%x \n",FLOAT_TO_INT_BITS(N2));
	printf("-0.1 -> 0x%x \n",FLOAT_TO_INT_BITS(N3));
	printf("0 -> 0x%x \n",FLOAT_TO_INT_BITS(N4));    


	printf("---- Signe/Exposant/Mantisse de %f ----\n",N1);
	printf("Signe %f =>",N1);testEQ(getSigne(N1),0,1);
	printf("Exposant %f =>",N1);testEQ(getExposant(N1),6,1);
	printf("Mantisse %f =>",N1);testEQHEX(getMantisse(125.25),0xFA8000,1);    
	
	printf("---- Signe/Exposant/Mantisse de  %f ----\n",N2);
	printf("Signe %f =>",N2);testEQ(getSigne(N2),0,1);
	printf("Exposant %f =>",N2);testEQ(getExposant(N2),-2,1);
	printf("Matisse %f =>",N2);testEQHEX(getMantisse(N2),0xC00000,1);    

	printf("---- Signe/Exposant/Mantisse de  %f ----\n",N3);
	printf("Signe %f =>",N3);testEQ(getSigne(N3),1,1);
	printf("Exposant %f =>",N3);testEQ(getExposant(N3),-4,1);
	printf("Matisse %f =>",N3);testEQHEX(getMantisse(N3),0xCCCCCD,1);    
   
	printf("---- Signe/Exposant/Mantisse de  %f ----\n",N4);
	printf("Signe %f =>",N4);testEQ(getSigne(N4),0,1);
	printf("Exposant %f =>",N4);testEQ(getExposant(N4),-127,1);
	printf("Mantisse %f =>",N4);testEQHEX(getMantisse(N4),0,1);    

	printf("---- Reconstruction de  125.25 ----\n");

	f=setSigne(f,0); f=setExposant(f,6); f=setMantisse(f,0xFA8000);

	printf("%f1 reconstruit =>",N1);testEQHEX(FLOAT_TO_INT_BITS(f),0x42FA8000,1);


	printf("---- Erreur de précision ----\n");
	printf("(0.25+0.5== 0.75) -> %d \n",(0.25+0.5== 0.75));
	printf("(0.2+0.1==0.3) -> %d \n",(0.2+0.1==0.3));
	printf("(0.2+0.1-0.3=0.0) -> %d \n",(0.2+0.1-0.3==0));    
	printf("(0.2+0.1-0.3<0.00000001) -> %d\n",(0.2+0.1-0.3<0.00000001));
	printf("1.0/0.0 -> %f\n", (1.0/0.0));
	printf("(1.0/0.0)+1 -> %f\n", (1.0/0.0)+1); 
	printf("-1.0/0.0 -> %f\n", (-1.0/0.0));
	printf("(1.0/0.0)+(-1.0/0.0) -> %f\n", (1.0/0.0)+(-1.0/0.0));
	printf("---- Nombres dénormalisés ----\n");
	f=1.4e-45;
	printf("---- Signe/Exposant/Mantisse de  %e ----\n",f);    
	printf("Signe %f =>",f);testEQ(getSigne(f),0,1);
	printf("Exposant %f =>",f);testEQ(getExposant(f),-127,1);
	printf("Mantisse %f =>",f);testEQHEX(getMantisse(f),1,1);
	f=1.17549435e-38;
	printf("---- Signe/Exposant/Mantisse de  %e ----\n",f);
	printf("Signe %f =>",f);testEQ(getSigne(f),0,1);
	printf("Exposant %f =>",f);testEQ(getExposant(f),-126,1);
	printf("Mantisse %f =>",f);testEQHEX(getMantisse(f),0x800000,1);
	f=3.4028235e38;
	printf("---- Signe/Exposant/Mantisse de  %e ----\n",f);
	printf("Signe %f =>",f);testEQ(getSigne(f),0,1);
	printf("Exposant %f =>",f);testEQ(getExposant(f),127,1);
	printf("Mantisse %f =>",f); testEQHEX(getMantisse(f),0xFFFFFF,1);
	
	printf("---- inf et nan  ----\n");
	f=1.0/0.0;
	printf("+inf -> 0x%x\n", FLOAT_TO_INT_BITS(f));
	printf("Signe -> %d\n",getSigne(f));    
	printf("Exposant -> %d\n",getExposant(f));
	printf("Mantisse -> 0x%x\n",getMantisse(f));    
	f=-1.0/0.0;
	printf("-inf -> 0x%x\n", FLOAT_TO_INT_BITS(f));
	printf("Signe -> %d\n",getSigne(f));    
	printf("Exposant -> %d\n",getExposant(f));
	printf("Mantisse -> 0x%x\n",getMantisse(f));    
	f=(1.0/0.0)+(-1.0/0.0);
	printf("nan -> 0x%x\n", FLOAT_TO_INT_BITS(f));
	printf("Signe -> %d\n",getSigne(f));    
	printf("Exposant -> %d\n",getExposant(f));
	printf("Mantisse -> 0x%x\n",getMantisse(f));
	printf("---- Valeur de Max+1 != Max----\n");    
	f = maximumFloat();
	printf("Max ->%f\n",f); 
	printf("Exposant Max -> %d\n",getExposant(f));
	printf("Mantisse Max -> 0x%x\n",getMantisse(f));
	printf("Representation nombre maxi %f =>",f);testEQHEX(FLOAT_TO_INT_BITS(f),0x4B800000,1);

	printf("----- resultat test ----\n");
	printf("résultat(s) correct(s)=%u\n",resOK);
	printf("résultat(s) inexact(s) %u\n",resErreur);
	return score;
}

int main(){
	return test();
}
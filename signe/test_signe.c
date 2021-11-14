// Didier Teifreto - Octobre 2021
#include <stdio.h> 
#include <string.h> 
#include "nombre_signe.h"

int resOK=0,resErreur=0,score=0;


#define testEQ(ok,res,increment) printf("Attendu: %d,Trouvé:%d",res,ok);if (ok==res){ printf("->Correct\n");resOK++;score=score+increment;} else {printf("->Erreur\n");resErreur++;}

#define testSTREQ(ok,res,increment) printf("Attendu: \"%s\",Trouvé:\"%s\"",res,ok);if (strcmp(ok,res)==0){ printf("->Correct\n");resOK++;score=score+increment;} else {printf("->Erreur\n");resErreur++;}

int test() {

    int N1=0x42FA8001; // base 10 = 1 123 713 025
    int N2=0xBEC01234; // base 10 = -1 094 708 684
    int N3=0xFFFFFFFF; // base 10 = -1
    int N4=0x7FFFFFFF; // base 10 = 2 147 483 647 
    int N5=0x80000000; // base 10 = -2 147 483 648 
    char res[33];
    int entier,entier1,resultat;

    printf("===================== bitCount ===================================\n");
    entier = bitCount(N1);printf("1. %d => ",N1);testEQ(entier,10,1);
    entier = bitCount(N2);printf("2. %d => ",N2);testEQ(entier,13,1);
    entier = bitCount(N3);printf("3. %d => ",N3);testEQ(entier,32,1);
    entier = bitCount(N4);printf("4. %d => ",N4);testEQ(entier,31,1);
    entier = bitCount(N5);printf("5. %d => ",N5);testEQ(entier,1,1);
    entier = bitCount(0) ;printf("6.0 => ")    ;testEQ(entier,0,1);
	
    printf("========================== forDigit ==============================\n");
	*(res+1)=(char)0;
    *res = forDigit(7,1)  ;printf("1. 7,1 => ")  ;testEQ(*res,'\0',1);
    *res = forDigit(7,17) ;printf("2. 7,17 =>") ;testEQ(*res,'\0',1);
	*res = forDigit(11,10);printf("3. 11,10 => ");testEQ(*res,'\0',1);
	*res = forDigit(7,16) ;printf("4. 7,16 =>") ;testEQ(*res,'7',1);
	*res = forDigit(12,16);printf("5. 12,16 =>");testEQ(*res,'C',1);
	
    printf("============================= digit =================================\n");
    entier = digit('3',1);printf("1. '3'.1 =>");testEQ(entier,-1,1);	
    entier = digit('3',17);printf("2. '3'.17 =>");testEQ(entier,-1,1);
    entier = digit('A',10);printf("3. 'A',10 =>");testEQ(entier,-1,1);	
    entier = digit('a',10);printf("4. 'a',10 =>");testEQ(entier,-1,1);
    entier = digit('3',2);printf("5. '3',2 =>");testEQ(entier,-1,1);	
    entier = digit('/',10);printf("6. '/'(0x2F) ,10 =>");testEQ(entier,-1,1);
    entier = digit(':',10);printf("7. '/'(0x3A) ,10 =>");testEQ(entier,-1,1);
    entier = digit('@',10);printf("8. '@'(0x40) ,10 =>");testEQ(entier,-1,1);
    entier = digit('G',10);printf("9. 'G'(0x47) ,10 =>");testEQ(entier,-1,1);			
    entier =digit(0x60,10);printf("10. (0x60) ,10 =>");testEQ(entier,-1,1);			
    entier = digit('g',10);printf("11. 'g'(0x60) ,10 =>");testEQ(entier,-1,1);
	entier = digit('0',16);printf("12. '0',16 =>");testEQ(entier,0,1);
	entier = digit('9',16);printf("13. '9',16 =>");testEQ(entier,9,1);	
    entier = digit('A',16);printf("14. 'A',16 =>");testEQ(entier,10,1);
    entier = digit('F',16);printf("15. 'F',16 =>");testEQ(entier,15,1);
    entier = digit('a',16);printf("16. 'a',16 =>");testEQ(entier,10,1);
    entier = digit('f',16);printf("17. 'f',16 =>");testEQ(entier,15,1);							

    printf("=============== toString ================================\n");
    *res='\0';
    entier = toString(N1,res,0);printf("1. %d,17 =>",N1);testEQ(entier,1,1);
    entier = toString(N1,res,18);printf("2. %d,17 =>",N1);testEQ(entier,1,1);
    entier = toString(N1,res,10);printf("3. %d,10 =>",N1);testSTREQ(res,"1123713025",2);
	entier = toString(N2,res,10);printf("4. %d,10 =>",N2);testSTREQ(res,"-1094708684",2);
    entier = toString(N3,res,10);printf("5. %d,10 =>",N3);testSTREQ(res,"-1",2);
    entier = toString(N4,res,10);printf("6. %d,10 =>",N4);testSTREQ(res,"2147483647",2);
    entier = toString(N5,res,10);printf("7 %d,10 =>",N5);testSTREQ(res,"-2147483648",2);
    entier = toString(123,res,10);printf("8 123,10 =>");testSTREQ(res,"123",2);
    entier = toString(0,res,10);printf("9. 0,10 =>");testSTREQ(res,"0",2);
	
    printf("=================== parseInt correct ==============================\n");
    entier = parseInt("1123713025",&resultat,10);printf("1. 1123713025,10=>");testEQ(resultat,1123713025,3);
    entier = parseInt("+1123713025",&resultat,10);printf("2. +1123713025,10 =>");testEQ(entier,0,1);testEQ(entier,0,1);testEQ(resultat,1123713025,3);
    entier = parseInt("-1094708684",&resultat,10);printf("3. -1094708684,10 =>");testEQ(entier,0,1);testEQ(resultat,-1094708684,3);
	entier = parseInt("2147483647",&resultat,10);printf("4. 2147483647,10 =>");testEQ(entier,0,1);testEQ(resultat,2147483647,3);
    entier = parseInt("-2147483648",&resultat,10);printf("5. -2147483648,10 =>");testEQ(entier,0,1);testEQ(resultat,(int)-2147483648,3);
    entier = parseInt("123",&resultat,10);printf("6. -2147483648,10  =>");testEQ(entier,0,1);testEQ(resultat,123,3);
    entier = parseInt("0",&resultat,10);printf("7. 0,10  =>");testEQ(entier,0,1);testEQ(entier,0,3);
	
	
    printf("===================== parseInt erreur =================================\n");
    entier = parseInt("2147483648",&resultat,2);printf("1. 2147483648,2 =>");testEQ(entier,1,3);
    entier = parseInt("214*483648",&resultat,10);printf("2. 214*483648,10 =>");testEQ(entier,1,3);	
    entier = parseInt("2147483648",&resultat,10);printf("3. 2147483648,10 =>");testEQ(entier,1,3);
    entier = parseInt("-2147483649",&resultat,10);printf("4. -2147483649,10 =>");testEQ(entier,1,3);
    entier = parseInt("-214748364999",&resultat,10);printf("5. -214748364999,10 =>");testEQ(entier,1,3);
    entier = parseInt("-214748364999",&resultat,10);printf("6. -214748364999,10 =>");testEQ(entier,1,3);

    printf("----- resultat test ----\n");
    printf("resultat OK = %d\n",resOK);
    printf("résultat FAUX = %d\n",resErreur);
    return score;
}
int main(){
    return test();
}
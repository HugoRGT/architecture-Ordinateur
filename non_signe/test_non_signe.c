// Didier Teifreto - Septembre 2021
#include <stdio.h> // 
#include <string.h> // pour les test de chaines
#include "nombre_non_signe.h"

int resOK=0,resErreur=0,score=0;


#define testEQ(ok,res,increment) printf("Attendu: %d,Trouvé:%d",res,ok);if (ok==res){ printf("->Correct\n");resOK++;score=score+increment;} else {printf("->Erreur\n");resErreur++;}

#define testSTREQ(ok,res,increment) printf("Attendu: \"%s\",Trouvé:\"%s\"",res,ok);if (strcmp(ok,res)==0){ printf("->Correct\n");resOK++;score=score+increment;} else {printf("->Erreur\n");resErreur++;}


int test() {
    unsigned N1=0x42FA8001; // en base 10 = 1 123 713 025
    unsigned N2=0xBEC01234; // en base 10 = 3 200 258 612
    unsigned N3=0xFFFFFFFF; // en base 10 = 4 294 967 295
    char res[33];
    unsigned entier;

    printf("---- bitCount -----\n");
    entier = bitCount(N1);testEQ(entier,10,1);
    entier = bitCount(N2);testEQ(entier,13,1);
    entier = bitCount(N3);testEQ(entier,32,1);
    entier = bitCount(123);testEQ(entier,6,1);
    entier = bitCount(0);testEQ(entier,0,1);

    printf("---- forDigit ----\n");
    *(res+1)=(char)0;
    *res=forDigit(6);testEQ(*res,'6',1);
    *res=forDigit(0xA);testEQ(*res,'A',1);

    printf("---- digit ----\n");
    *(res+1)=(char)0;    
    entier = digit('7');testEQ(entier,7,1);    
    entier = digit('A');testEQ(entier,0xA,1); 


    printf("---- toHexString ----\n");
    toHexString(N1,res);testSTREQ(res,"42FA8001",1);
    toHexString(N2,res);testSTREQ(res,"BEC01234",1);
    toHexString(N3,res);testSTREQ(res,"FFFFFFFF",1);
    toHexString(123,res);testSTREQ(res,"0000007B",1);
    toHexString(0,res);testSTREQ(res,"00000000",1);

    printf("---- toBinaryString ----\n");
    toBinaryString(N1,res);testSTREQ(res,"01000010111110101000000000000001",1);
    toBinaryString(N2,res);testSTREQ(res,"10111110110000000001001000110100",1);
    toBinaryString(N3,res);testSTREQ(res,"11111111111111111111111111111111",1);
    toBinaryString(123,res);testSTREQ(res,"00000000000000000000000001111011",1);
    toBinaryString(0,res);testSTREQ(res,"00000000000000000000000000000000",1);

    
    printf("---- toUnsignedString -----\n");
    toUnsignedString(N1,res,10);testSTREQ(res,"1123713025",1);
    toUnsignedString(N2,res,16);testSTREQ(res,"BEC01234",1);
    toUnsignedString(N3,res,10);testSTREQ(res,"4294967295",1);
    toUnsignedString(123,res,10);testSTREQ(res,"123",1);
    toUnsignedString(0,res,10);testSTREQ(res,"0",1);


    printf("---- parseUnsigned ----\n");
    entier = parseUnsigned("1123713025",10);testEQ(entier,1123713025,1);
    entier = parseUnsigned("BEC01234",16);testEQ(entier,(unsigned)3200258612,1);
    entier = parseUnsigned("4294967295",10);testEQ(entier,(unsigned)4294967295,1);
    entier = parseUnsigned("123",10);testEQ(entier,123,1);
    entier = parseUnsigned("0",10);testEQ(entier,0,1);    


    printf("----- resultat test ----\n");
    printf("résultat(s) correct(s)=%u\n",resOK);
    printf("résultat(s) inexact(s) %u\n",resErreur);
    return score;
}
int main(){
    return test();
}

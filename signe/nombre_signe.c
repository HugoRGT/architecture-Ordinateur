// Didier Teifreto - Novembre 2020
#include "nombre_signe.h"

#define srl(a,b) (int)((unsigned)a >> (unsigned)b);

// comptage du nombre de bit a 1
unsigned bitCount(int nombre){
    // A écrire
    unsigned resultat;
    resultat = 0;
    while(nombre != 0){
        resultat = resultat + (nombre & 1);
        nombre = srl(nombre,1);
    }
    return resultat;
}
// digit -> caractere
char forDigit(int nombre,int base){
    char tab[16]="0123456789ABCDEF";
    // A écrire
    if(base < 2 || base > 16 || nombre >= base){
        return '\0';
    }
    return *tab+nombre;
}
// caractere -> digit
int digit(char caractere,int base){
    // A écrire
    if(base < 2 || base > 16){
        return -1;
    }else if((caractere>=48 && caractere <= 57 && caractere-48 > base) || (caractere>=65 && caractere <= 70 && caractere-54 > base) || (caractere>=97 && caractere <= 102 && caractere-86 > base)){
        return -1;
    }
    char tab[12] = "abdcefABCDEF";
    char retChar = 0;
    int retCharExa;
    int i;
    for(i = 0; tab[i] != caractere && i < 12; ++i){}
    if(i > 5){
        retChar = 'A';
        retCharExa = 0xA;
    }else{
        retChar = 'a';
        retCharExa = 0xa;
    }
    if(caractere > '9' && (caractere >= 'A' && caractere <= 'Z' || caractere >= 'a' && caractere <= 'z')){
        return caractere + retCharExa - retChar;
    }else if(caractere >= '0' && caractere <= '9'){
        return caractere - '0';
    }else{
        return -1;
    }
}
// entier  -> chaine de caracteres
int toString(int nombre,char *res,int base){
    // A écrire
    if(base < 2 || base >= 16){
        return 1;
    }
    int position,nombre1;
    if(nombre >= 0){
        nombre -= nombre;
        position = 0;
    }else{
        *res = '-';
        position = 1;
    }
    nombre1 = nombre;
    do{
        nombre = nombre / base;
        position = position + 1;
    }while(nombre != 0);
    *(res+position) = (char)0;
    do{
        position = position - 1;
        if(forDigit(-(nombre1%base),base) == '\0'){
            return 1;
        }
        *(res+position) = forDigit(-(nombre1%base),base);
        nombre1 = nombre / base;
    }while(nombre1 != nombre/base);
    return 0;
}
// chaine de caracteres -> entier 
int parseInt(char *chaine,int *resultat,int base){
    if(base < 2 || base > 16){
        return 1;
    }
    int position,result;
    result = 0;
    position = 0;
    if(*(chaine+position) == '-' || *(chaine+position) == '+'){
        position += 1;
    }
    while(*(chaine+position) != '\0'){
        if(digit(*(chaine+position),base) == -1){
            return 1;
        }
        int prev = result;
        result = result * base - digit(*(chaine+position),base);
        if(result > prev){
            return 1;
        }
        if(result == -2147483648 && *chaine != '-'){
            return 1;
        }
        position = position + 1;
    }
    if(*chaine != '-'){
        result = result;
    }
    return result;
}
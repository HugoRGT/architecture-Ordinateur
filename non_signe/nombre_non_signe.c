// Hugo Rougetet Septembre 2021
#include "nombre_non_signe.h"

unsigned bitCount(unsigned nombre){
    // A ecrire
    unsigned resultat;
    resultat = 0;
    while(nombre != 0){
        resultat = resultat + (nombre & 1);
        nombre = nombre >> 1;
    }
    return resultat;
}

// digit -> caractere
char forDigit(unsigned nombre){
    // A ecrire
    if(nombre > 9){
        return (char)(nombre - 0xA + 'A');
    }else{
        return (char)(nombre + '0');
    }
}
// caractere -> digit
unsigned digit(char caractere){
    // A ecrire
    if(caractere > '9'){
        return (unsigned)caractere + 0xA - 'A';
    }else{
        return (unsigned)caractere - '0';
    }
}

// entier non signe -> chaine de caracteres hexadecimaux
void toHexString(unsigned nombre,char *res){
    // A écrire
    unsigned cpt;
    for(cpt = 0; cpt <= 7; ++cpt){
        res[cpt] = forDigit(nombre >> 28);
        nombre = nombre << 4;
    }
    res[cpt] = '\0';
}
// entier non signe -> chaine de caracteres binaires
void toBinaryString(unsigned nombre,char *res){
    // A écrire
    unsigned cpt;
    for(cpt = 0; cpt <= 31; ++cpt){
        res[cpt] = (char)((nombre >> 31) + '0');
        nombre = nombre << 1;
    }
    res[cpt] = '\0';
}
// entier non signe -> chaine de caracteres
void toUnsignedString(unsigned nombre,char *res,int base){
    // A écrire
    unsigned position,nombre1;
    position = 0;
    nombre1 = nombre;
    do{
        position = position + 1;
        nombre = nombre / base;
    }while(nombre != 0);
    res[position] = (char)0;
    do{
        position = position - 1;
        res[position] = forDigit(nombre1 % base);
        nombre1 = nombre1 / base;
    }while(nombre1 != 0);
}
// chaine de caracteres -> entier non signé
unsigned parseUnsigned(char *chaine,int base){
    // A ecrire
    unsigned resultat,position;
    resultat = 0;
    position = 0;
    while(chaine[position] != (char) 0){
        resultat = resultat * base + digit(chaine[position]);
        position = position +1;
    }
    return resultat;
}
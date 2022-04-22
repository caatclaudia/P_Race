// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019
// Cláudia Tavares

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define nomeFichCarros "carros.txt"
#define nomeFichPilotos "pilotos.txt"
#define nomeFichCampeonatos "campeonato.dat"
#define MAX_VOLTAS 10
    
int scanfInteiro();
    
typedef struct data data;    
    
struct data{
    int dia, mes, ano;
};    

#define LESAO 0    //impedimento do piloto
#define PENALIZADO 1    //impedimento do piloto
typedef struct piloto piloto, *ptrPiloto;

struct piloto{
    char nome[100];
    int Id;
    data dataNasc;
    int peso;
    float experiencia;
    int penalizacao;
    int impedimento;
    int corridasParticipadas;
};

#define NAO_AVARIADO 0    //avariado do carro
#define AVARIADO 1    //avariado do carro
typedef struct carro carro, *ptrCarro;

struct carro{
    int Id, potencia, avariado;
};

#define DESISTIU 1    //desistiu do treino
#define NAO_DESISTIU 0    //desistiu do treino
typedef struct treino treino, *ptrTreino;

struct treino{
    ptrPiloto Piloto;
    ptrCarro Carro;
    int segundos[MAX_VOLTAS], atual;
    int voltasEmPrimeiro, desistiu;
    ptrTreino prox;
};

typedef struct campeonato campeonato, *ptrCampeonato;

struct campeonato{
    int numCorrida;
    ptrTreino corrida;
    ptrCampeonato prox;
};

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */


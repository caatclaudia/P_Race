// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019
// Cláudia Tavares

#ifndef FICHEIROS_H
#define FICHEIROS_H

#ifdef __cplusplus
extern "C" {
#endif

void escrevePilotos(ptrPiloto piloto, int *totalPilotos);
ptrPiloto lePilotos(ptrPiloto pilotos, int *totalPilotos);
void escreveCarros(ptrCarro carro, int *totalCarros);
ptrCarro leCarros(ptrCarro carros, int *totalCarros);
void escreveCampeonatos(ptrCampeonato camp, int *numCorridas);
ptrCampeonato leCampeonatos(ptrCampeonato camp, int *numCorridas, ptrPiloto pilotos, int *totalPilotos, ptrCarro carros, int *totalCarros);

#ifdef __cplusplus
}
#endif

#endif /* FICHEIROS_H */


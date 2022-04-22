// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019
// Cláudia Tavares

#ifndef CORRIDA_H
#define CORRIDA_H

#ifdef __cplusplus
extern "C" {
#endif

void menuSecundario();
void mostraVolta(ptrTreino treino, int volta);   
ptrTreino Corrida(ptrTreino listaTreino, ptrPiloto listaPilotos, int totalPilotos, ptrCarro listaCarros, int totalCarros);
ptrCampeonato Campeonato(ptrCampeonato listaCampeonato, ptrPiloto listaPilotos, int totalPilotos, ptrCarro listaCarros, int totalCarros, int *numCorridas);

#ifdef __cplusplus
}
#endif

#endif /* CORRIDA_H */


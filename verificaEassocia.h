// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019
// Cláudia Tavares

#ifndef VERIFICA_ASSOCIA_H
#define VERIFICA_ASSOCIA_H

#ifdef __cplusplus
extern "C" {
#endif

int VerificaIdPilotos(ptrPiloto pilotos, int *totalPilotos, int id);
int VerificaDadosPilotos(int peso, float experiencia, int penalizacao);
int VerificaDataPilotos(int dia, int mes, int ano);
int calculaIdade(int diaNasc, int mesNasc, int anoNasc);

int VerificaIdCarros(ptrCarro carros, int *totalCarros, int id);
int VerificaDadosCarros(int potencia, int avariado);

ptrTreino preencheTreino(ptrPiloto pilotos, ptrCarro carros);
ptrTreino copiaTreino(ptrTreino original);
ptrTreino eliminaTreino(ptrTreino treino, int idCarro);
ptrTreino insereTreino(ptrTreino treino, ptrTreino aux);
ptrCampeonato insereCampeonato(ptrCampeonato camp, ptrCampeonato aux);

ptrTreino associaCarros(ptrTreino treino, int max, ptrPiloto pilotos, int *totalPilotos, ptrCarro carros, int *totalCarros);
void mostraEmperelhamentosCarros(ptrTreino treino, int max, ptrPiloto pilotos, int *totalPilotos, ptrCarro carros, int *totalCarros);
ptrTreino ordenaListaTreino(ptrTreino listaTreino);

#ifdef __cplusplus
}
#endif

#endif /* VERIFICA_ASSOCIA_H */


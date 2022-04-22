// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019
// Cláudia Tavares

#include "main.h"
#include "ficheiros.h"
#include "corrida.h"

void principal(){
    printf("\n-----------------------------------------------------------------------------------------------------\n"
             "-                                                                                                   -\n" 
             "-                                                                                                   -\n"
             "-         _  __          _____ _______ _____         _____  _____ ______ _____                      -\n"
             "-        | |/ /    /\\   |  __ \\__   __/ ____|  ____ |_   _|/ ____|  ____/ ____|                     -\n"
             "-        | ' /    /  \\  | |__) | | | | (___   / __ \\  | | | (___ | |__ | |                          -\n"
             "-        |  <    / /\\ \\ |  _  /  | |  \\___ \\ / / _` | | |  \\___ \\|  __|| |                          -\n"
             "-        | . \\  / ____ \\| | \\ \\  | |  ____) | | (_| |_| |_ ____) | |___| |____                      -\n"
             "-        |_|\\_\\/_/    \\_\\_|  \\_\\ |_| |_____/ \\ \\__,_|_____|_____/|______\\_____|                     -\n"
             "-                                             \\____/                                                -\n"
             "-                                                                                                   -\n"
             "-                                                                                                   -\n"
             "-                                                                                                   -\n"
             "-                                             1.Treino                                              -\n"
             "-                                             2.Campeonato                                          -\n"
             "-                                             3.Sair                                                -\n"
             "-                                                                                                   -\n"
             "-                                                                                                   -\n"
             "-                                                                     Claudia Tavares - 21270617    -\n"
             "-                                                                          Programacao 18/19        -\n"  
             "-----------------------------------------------------------------------------------------------------\n"
             ">>Opcao: ");                                            
}

int scanfInteiro(){
  int inteiro, fim=0;
  char tmp;
  while (fim < 1) {
    if(scanf(" %d", &inteiro)== 1) 
        fim++;
    scanf("%c", &tmp);
  }
  return inteiro;
}

int main(int argc, char** argv) {
    int op, totalPilotos=0, totalCarros=0, numCorridas;
    ptrCarro listaCarros=NULL;
    ptrPiloto listaPilotos=NULL;
    ptrTreino listaCorrida=NULL, tmp=NULL;
    ptrCampeonato listaCampeonato=NULL;
    
    listaCarros=leCarros(listaCarros, &totalCarros);
    listaPilotos=lePilotos(listaPilotos, &totalPilotos);
 
    listaCampeonato=leCampeonatos(listaCampeonato, &numCorridas, listaPilotos, &totalPilotos, listaCarros, &totalCarros);
    do{
        principal();
        op = scanfInteiro();
        listaCorrida=NULL;
        switch(op){
            case 1: //TREINO
                if(listaCampeonato!=NULL)
                    printf("\nHa campeonatos em execucao!\n");
                else{
                    listaCorrida=Corrida(listaCorrida, listaPilotos, totalPilotos, listaCarros, totalCarros);
                    if(listaCorrida!=NULL){
                        tmp=listaCorrida;
                        while(tmp!=NULL){
                            //Quem desistiu perde 1 ponto de experiencia
                            if(tmp->desistiu==DESISTIU){
                                tmp->Piloto->experiencia=tmp->Piloto->experiencia-1;
                                if(tmp->Piloto->experiencia<0)
                                    tmp->Piloto->experiencia=0;
                            }
                            else
                                tmp->Piloto->experiencia=tmp->Piloto->experiencia+tmp->voltasEmPrimeiro*0.5;
                            tmp=tmp->prox;
                        }
                    }
                }
                break;
            case 2: //CAMPEONATO
                listaCampeonato=Campeonato(listaCampeonato, listaPilotos, totalPilotos, listaCarros, totalCarros, &numCorridas);
                break;
            default:
                break;
        }
        free(listaCorrida);
    }while(op!=3);
    
    escreveCarros(listaCarros, &totalCarros);
    escrevePilotos(listaPilotos, &totalPilotos);
    free(listaCampeonato);
    free(listaCarros);
    free(listaPilotos);
    free(tmp);
    return (EXIT_SUCCESS);
}
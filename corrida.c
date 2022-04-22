// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019
// Cláudia Tavares

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include "verificaEassocia.h"
#include "utils.h"
#include "ficheiros.h"

void menuSecundario(){
    printf("\n\n-----------------------------------------------------------------------------------------------------\n"
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
             "-                                   1.Visualisar volta a volta                                      -\n"
             "-                                   2.Visualizar volta especifica                                   -\n"
             "-                                   3.Continuar                                                     -\n"
             "-                                                                                                   -\n"
             "-                                                                                                   -\n"
             "-                                                                     Claudia Tavares - 21270617    -\n"
             "-                                                                          Programacao 18/19        -\n"  
             "-----------------------------------------------------------------------------------------------------\n"
             ">>Opcao: ");
}

void mostraVolta(ptrTreino treino, int volta){
    ptrTreino tmp=treino;
    int i=1, j, primeiro=1;
    printf("\nClassificacao no final da %d volta ", volta);
    
    while(tmp!=NULL){
        if(tmp->desistiu==NAO_DESISTIU){
            printf("\n%d : %s (Id: %d) / Carro %d : ", i, tmp->Piloto->nome, tmp->Piloto->Id, tmp->Carro->Id);
            for(j=0; j<volta; j++){
                printf("%d", tmp->segundos[j]);
                if(j!=-1 && j!=volta-1)
                    printf(" + ");
            }
            printf(": %d segundos", tmp->atual);
            i++;
        }
        tmp=tmp->prox;
    }
    tmp=treino;
    while(tmp!=NULL){
        if(tmp->desistiu==DESISTIU){
            if(primeiro==1){
                printf("\n  Desistentes:");
                primeiro=0;
            }
            printf("\n %s (Id: %d) / Carro %d : ", tmp->Piloto->nome, tmp->Piloto->Id, tmp->Carro->Id);
            for(j=0; j<volta && tmp->segundos[j]>0; j++);
            printf("%d segundos ate %d volta\n", tmp->atual, j);
        }
        tmp=tmp->prox;
    }
    free(tmp);
    return;
}

ptrTreino Corrida(ptrTreino listaTreino, ptrPiloto listaPilotos, int totalPilotos, ptrCarro listaCarros, int totalCarros){
    int numVoltas, comprimentoPista, maximoCarros;
    int volta, idade, segundos;
    int primeiro, op;
    do{
        printf("\n>>Quantas voltas vao ser efetuadas?");
        numVoltas = scanfInteiro();
        if(numVoltas<5 || numVoltas>MAX_VOLTAS)
            printf("Valor invalido! Tem de ser entre 5-10!!\n");
    }while(numVoltas<5 || numVoltas>MAX_VOLTAS);
    do{
        printf(">>Qual e o comprimento da pista (em metros)?");
        comprimentoPista = scanfInteiro();
        if(comprimentoPista<500 || comprimentoPista>1000)
            printf("Valor invalido! Tem de ser entre 500-1000!!\n");
    }while(comprimentoPista<500 || comprimentoPista>1000);
    do{
        printf(">>Qual e o numero maximo de carros?");
        maximoCarros = scanfInteiro();
        if(maximoCarros<=0)
            printf("Valor invalido!!\n");
    }while(maximoCarros<=0);
    //Associar carros a pilotos
    listaTreino=associaCarros(listaTreino, maximoCarros, listaPilotos, &totalPilotos, listaCarros, &totalCarros);
    if(listaTreino==NULL)
        return NULL;
    //mostra os emparelhamentos
    mostraEmperelhamentosCarros(listaTreino, maximoCarros, listaPilotos, &totalPilotos, listaCarros, &totalCarros);

    ptrTreino tmp=NULL, aux=listaTreino;
    
    for(volta=1; volta<=numVoltas; volta++){
        espera(5);
        primeiro=1;
        
        tmp=listaTreino;        
        while(tmp!=NULL){
            if(tmp->desistiu!=DESISTIU){
                //Em cada volta, cada par piloto/carro tem uma probabilidade de 5% de ter um acidente. 
                if(probEvento(0.05)==1){ //tem acidente
                    tmp->Piloto->impedimento=LESAO;
                    tmp->Piloto->penalizacao=tmp->Piloto->penalizacao+2;
                    tmp->segundos[volta-1]=0;
                    tmp->Carro->avariado=AVARIADO;
                    //Um acidente implica que o par piloto/carro desiste da corrida
                    tmp->desistiu=DESISTIU;
                }
                else{
                    idade=calculaIdade(tmp->Piloto->dataNasc.dia, tmp->Piloto->dataNasc.mes, tmp->Piloto->dataNasc.ano);
                    //Por volta, por cada carro/piloto -> calculaSegundos()
                    segundos=calculaSegundos(idade, tmp->Piloto->peso, tmp->Piloto->experiencia, tmp->Carro->potencia, comprimentoPista);
                    tmp->segundos[volta-1]=segundos;
                    tmp->atual=tmp->atual+segundos;
                }
            }
            if(primeiro==1)
                aux=tmp;
            primeiro=0;
            tmp=tmp->prox;
        }
        listaTreino=aux;
        listaTreino=ordenaListaTreino(listaTreino);
        listaTreino->voltasEmPrimeiro=listaTreino->voltasEmPrimeiro+1;
        //No final de cada volta, o programa mostra a classificação nessa altura, incluindo os pilotos que já desistiram
        mostraVolta(listaTreino, volta);
    }
    tmp=listaTreino;
    char c;
    int id, quanto;
    do{
        quanto=0;
        primeiro=1;
        printf("\n>>Algum piloto teve comportamento incorreto? ");
        scanf(" %c", &c);
        if(c=='S' || c=='s'){
            printf(">>Insira o id do mesmo: ");
            scanf("%d", &id);
            while(tmp!=NULL && quanto==0){
                if(id==tmp->Piloto->Id){
                    do{
                        printf(">>Qual sera a penalizacao? (1-3): ");
                        scanf("%d", &quanto);
                        if(quanto<1 || quanto>3)
                            printf("Valor invalido! Tem de ser entre 1-3!!\n");
                    }while(quanto<1 || quanto>3);
                    tmp->Piloto->penalizacao=tmp->Piloto->penalizacao+quanto;
                }
                if(primeiro==1)
                    listaTreino=tmp;
                tmp=tmp->prox;
                primeiro=0;
            }
            if(quanto==0)
                printf("Valor invalido! ID nao encontrado!!\n");
            tmp=listaTreino;
        }
    }while(c!='N' && c!='n');
    
    do{
        menuSecundario();
        op = scanfInteiro();
        switch(op){
            case 1: //Visualização da classificação detalhada volta a volta
                for(volta=1; volta<=numVoltas; volta++){
                    aux=tmp;
                    primeiro=0;
                    while(aux!=NULL){
                        segundos=0;
                        for(int j=0; j<volta; j++)
                            segundos=segundos+aux->segundos[j];
                        aux->atual=segundos;
                        if(primeiro==0)
                            tmp=aux;
                        primeiro=1;
                        aux=aux->prox;
                    }
                    tmp=ordenaListaTreino(tmp);
                    mostraVolta(tmp, volta);
                    free(aux);
                }
                break;
            case 2: //Visualização detalhada da classificação numa volta específica
                do{
                    printf("\n>>Insira a volta que deseja visualizar: ");
                    volta = scanfInteiro();
                }while(volta>numVoltas);
                aux=tmp;
                primeiro=0;
                while(aux!=NULL){
                    segundos=0;
                    for(int j=0; j<volta; j++)
                        segundos=segundos+aux->segundos[j];
                    aux->atual=segundos;
                    if(primeiro==0)
                        tmp=aux;
                    primeiro=1;
                    aux=aux->prox;
                }
                tmp=ordenaListaTreino(tmp);
                mostraVolta(tmp, volta);
                free(aux);
                break;
            default:
                break;
        }
        
    }while(op!=3);
    return listaTreino;
}

ptrCampeonato Campeonato(ptrCampeonato listaCampeonato, ptrPiloto listaPilotos, int totalPilotos, ptrCarro listaCarros, int totalCarros, int *numCorridas){
    ptrTreino listaCorrida=NULL, auxCorrida=NULL, campeaoCampeonato=NULL, auxCampeao=NULL;
    ptrCampeonato auxCamp=NULL, antCamp=NULL;
    int corrida, pontosCinco, primeiro=1, feito=0;
    char c;
    corrida=1;
    antCamp=malloc(sizeof(campeonato));
    if(antCamp==NULL){
        printf("Erro de alocacao de memoria!!\n");
        return listaCampeonato;
    }
    if(listaCampeonato!=NULL){
        printf("\nO Campeonato vai continuar...\n");
        auxCamp=listaCampeonato;
        while(auxCamp!=NULL){
            auxCorrida=auxCamp->corrida;
            while(auxCorrida!=NULL){
                feito=0;
                if(auxCorrida->desistiu=DESISTIU){
                    campeaoCampeonato=eliminaTreino(campeaoCampeonato, auxCorrida->Carro->Id);
                }
                auxCampeao=campeaoCampeonato;
                while(auxCampeao!=NULL){
                    if(auxCorrida->Piloto->Id==auxCampeao->Piloto->Id){
                        auxCampeao->atual=auxCampeao->atual+auxCorrida->atual;
                        feito=1;
                    }
                    if(primeiro==1)
                        campeaoCampeonato=auxCampeao;
                    primeiro=0;
                    auxCampeao=auxCampeao->prox;
                }
                if(feito!=1)
                    campeaoCampeonato=insereTreino(campeaoCampeonato, auxCorrida);
                auxCorrida=auxCorrida->prox;
            }
            campeaoCampeonato=ordenaListaTreino(campeaoCampeonato);
            
            corrida++;
            auxCamp=auxCamp->prox;
        }
    }
    else{
        do{
            printf(">>Quantas corridas vao ser efetuadas?");
            *numCorridas =scanfInteiro();
            if(*numCorridas<3 || *numCorridas>8)
                printf("Valor invalido! Tem de ser entre 3-8!!\n");
        }while(*numCorridas<3 || *numCorridas>8);
    }
    auxCamp=malloc(sizeof(campeonato));
    if(auxCamp==NULL){
        printf("Erro de alocacao de memoria!!\n");
        return listaCampeonato;
    }               
    do{
        listaCorrida=NULL;
        printf("\nCorrida %d:\n", corrida);
        listaCorrida=Corrida(listaCorrida, listaPilotos, totalPilotos, listaCarros, totalCarros);
        if(listaCorrida==NULL)
            return listaCampeonato;
        auxCorrida=listaCorrida;
        feito=0;
        while(auxCorrida!=NULL){
            auxCorrida->Piloto->corridasParticipadas=auxCorrida->Piloto->corridasParticipadas+1;
            if(feito!=1)
                listaCorrida=auxCorrida;
            feito=1;
            auxCorrida=auxCorrida->prox;
        }
        //Campeao do Campeonato
        if(campeaoCampeonato==NULL){
            campeaoCampeonato=listaCorrida;
        }
        else{
            while(auxCorrida!=NULL){
                feito=0;
                if(auxCorrida->desistiu=DESISTIU){
                    campeaoCampeonato=eliminaTreino(campeaoCampeonato, auxCorrida->Carro->Id);
                }
                auxCampeao=campeaoCampeonato;
                while(auxCampeao!=NULL){
                    if(auxCorrida->Piloto->Id==auxCampeao->Piloto->Id){
                        auxCampeao->atual=auxCampeao->atual+auxCorrida->atual;
                        feito=1;
                    }
                    if(primeiro==1)
                        campeaoCampeonato=auxCampeao;
                    primeiro=0;
                    auxCampeao=auxCampeao->prox;
                }
                if(feito!=1)
                    campeaoCampeonato=insereTreino(campeaoCampeonato, auxCorrida);
                auxCorrida=auxCorrida->prox;
            }
            campeaoCampeonato=ordenaListaTreino(campeaoCampeonato);
        }
        printf("\nQuem vai em primeiro lugar no Campeonato e: %s\n", campeaoCampeonato->Piloto->nome);
        
        auxCorrida=listaCorrida;
        //Pontuações para os primeiros cinco classificados
        pontosCinco=5;    
        while(auxCorrida!=NULL){
            if(auxCorrida->desistiu==NAO_DESISTIU){
                if(pontosCinco>0)
                    auxCorrida->Piloto->experiencia=auxCorrida->Piloto->experiencia+pontosCinco;
                auxCorrida->Piloto->experiencia=auxCorrida->Piloto->experiencia+auxCorrida->voltasEmPrimeiro*0.5;
                if(pontosCinco>0)
                    pontosCinco--;
            }
            if(pontosCinco==4)
                listaCorrida=auxCorrida;
            auxCorrida=auxCorrida->prox;
        }
        auxCamp->corrida=listaCorrida;
        auxCamp->numCorrida=corrida;
        listaCampeonato=insereCampeonato(listaCampeonato, auxCamp);                  
        if(corrida<*numCorridas){
            do{
                printf("\n>>Deseja continuar? (S/N) ");
                scanf(" %c", &c);
            }while(c!='s' && c!='S' && c!='n' && c!='N');
        }
        corrida++;
    }while(corrida<=*numCorridas && (c!='N' && c!='n'));
    
    if(corrida>*numCorridas){
        campeaoCampeonato->Piloto->experiencia=campeaoCampeonato->Piloto->experiencia+10;
        printf("\nO campeao deste Campeonato e %s! Parabens!\n", campeaoCampeonato->Piloto->nome);
        listaCampeonato=NULL;
    }
    escreveCampeonatos(listaCampeonato, numCorridas);
    free(listaCorrida);
    return listaCampeonato;
}
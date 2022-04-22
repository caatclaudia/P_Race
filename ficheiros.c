// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019
// Cláudia Tavares

#include "main.h"
#include "verificaEassocia.h"

void escrevePilotos(ptrPiloto piloto, int *totalPilotos){
    if (piloto==NULL && totalPilotos==0)
        return ;
    
    FILE *f;
    f=fopen(nomeFichPilotos, "wt");
    if(f==NULL){
        printf("\nNao foi possivel abrir ficheiro\n");
        return ;
    }
    for(int i=0; i<*totalPilotos; i++){
        fprintf(f, "%s\n", piloto[i].nome);
        fprintf(f, "%d %d %d %d %d %.1f %d\n\n", piloto[i].Id, piloto[i].dataNasc.dia, piloto[i].dataNasc.mes,
            piloto[i].dataNasc.ano, piloto[i].peso, piloto[i].experiencia, piloto[i].penalizacao);  
    }
    fclose(f);
    return ;
}

ptrPiloto lePilotos(ptrPiloto pilotos, int *totalPilotos){
    FILE *f;
    char nome[100];
    int id, dia, mes, ano, peso, penalizacao;
    float experiencia;
    
    f=fopen(nomeFichPilotos, "rt");
    if(f==NULL){
        printf("\nNao foi possivel abrir ficheiro %s\n", nomeFichPilotos);
        return pilotos;
    }
    
    ptrPiloto tmp;
    while(fscanf(f, "%[^\n]s\n", nome)==1){
        fscanf(f, "%d %d %d %d %d %f %d\n\n", &id, &dia, &mes,
            &ano, &peso, &experiencia, &penalizacao);
        tmp=realloc(pilotos, sizeof(piloto)*(*totalPilotos+1));
        if(tmp==NULL){
            printf("Erro de alocacao de memoria!!\n");
            return pilotos;
        }
        pilotos=tmp;
        
        if(VerificaIdPilotos(pilotos, totalPilotos, id) != -1){
            printf("O piloto com o ID %d no ficheiro %s ja existe e vai ser ignorado, por favor verifique no ficheiro!\n", id, nomeFichPilotos );
            continue;
        }
        if(VerificaDadosPilotos(peso, experiencia, penalizacao) == -1){
            printf("Os dados no ficheiro %s nao estao corretos e vao ser ignorados, por favor verifique no ficheiro!\n", nomeFichPilotos );
            continue;
        }
        if(VerificaDataPilotos(dia, mes, ano) == -1){
            printf("Os dados no ficheiro %s nao estao corretos e vao ser ignorados, por favor verifique no ficheiro!\n", nomeFichPilotos );
            continue;
        }
        pilotos[*totalPilotos].Id=id;
        pilotos[*totalPilotos].dataNasc.dia=dia;
        pilotos[*totalPilotos].dataNasc.mes=mes;
        pilotos[*totalPilotos].dataNasc.ano=ano;
        pilotos[*totalPilotos].peso=peso;
        pilotos[*totalPilotos].experiencia=experiencia;
        pilotos[*totalPilotos].penalizacao=penalizacao;
        pilotos[*totalPilotos].corridasParticipadas=0;
        strcpy(pilotos[*totalPilotos].nome, nome);
        (*totalPilotos)++;
    }
    fclose(f);
    return pilotos;
}

void escreveCarros(ptrCarro carro, int *totalCarros){
    if (carro==NULL && totalCarros==0)
        return ;
  
    FILE *f;
    f=fopen(nomeFichCarros, "wt");
    if(f==NULL){
        printf("\nNao foi possivel abrir ficheiro\n");
        return ;
    }
    for(int i=0; i<*totalCarros; i++){
        fprintf(f, "%d %d %d\n\n", carro[i].Id, carro[i].potencia, carro[i].avariado);
    }
    fclose(f);
    return ;
}

ptrCarro leCarros(ptrCarro carros, int *totalCarros){
    FILE *f;
    int id, potencia, avariado;
    
    f=fopen(nomeFichCarros, "rt");
    if(f==NULL){
        printf("\nNao foi possivel abrir ficheiro %s\n", nomeFichCarros);
        return carros;
    }

    ptrCarro tmp;
    while(fscanf(f, "%d %d %d\n\n", &id, &potencia, &avariado)==3){
        tmp=realloc(carros, sizeof(carro)*(*totalCarros+1));
        if(tmp==NULL){
            printf("Erro de alocacao de memoria!!\n");
            return carros;
        }
        carros=tmp;
        
        if(VerificaIdCarros(carros, totalCarros, id) != -1){
            printf("O carro com o ID %d no ficheiro %s ja existe e vai ser ignorado, por favor verifique no ficheiro!\n", id, nomeFichCarros );
            continue;
        }
        if(VerificaDadosCarros(potencia, avariado) == -1){
            printf("Os dados no ficheiro %s nao estao corretos e vao ser ignorados, por favor verifique no ficheiro!\n", nomeFichCarros );
            continue;
        }
        carros[*totalCarros].Id=id;
        carros[*totalCarros].potencia=potencia;
        carros[*totalCarros].avariado=avariado;
        (*totalCarros)++;
    }
    fclose(f);
    return carros;
}

void escreveCampeonatos(ptrCampeonato camp, int *numCorridas){
    FILE *f;
    ptrCampeonato aux = camp;
    ptrTreino auxTreino=malloc(sizeof(treino)), percorreTreino=malloc(sizeof(treino));
    int corrida, conta;
    if(auxTreino==NULL || percorreTreino==NULL){
        printf("\nErro ao alocar memoria!");
        return;
    }
    f = fopen(nomeFichCampeonatos, "wb");
    if (f==NULL) {
        printf("\nErro ao abrir o ficheiro!");
        return;
    }
    if(aux!=NULL)
        fwrite(numCorridas, sizeof (int), 1, f);
    while (aux != NULL) {
        corrida=aux->numCorrida;
        fwrite(&corrida, sizeof (int), 1, f);
        auxTreino=aux->corrida;
        conta=0;
        percorreTreino=auxTreino;
        while(percorreTreino!=NULL){
            conta++;
            percorreTreino=percorreTreino->prox;
        }
        fwrite(&conta, sizeof (int), 1, f);
        for(int i=0; i<conta; i++, auxTreino=auxTreino->prox){
            fwrite(auxTreino, sizeof (treino), 1, f);
            fwrite(&auxTreino->Carro->Id, sizeof (int), 1, f);
            fwrite(&auxTreino->Piloto->Id, sizeof (int), 1, f);            
        }
        aux = aux->prox;
    }
    free(aux);
    free(percorreTreino);
    free(auxTreino);
    fclose(f);
    return;
}

ptrCampeonato leCampeonatos(ptrCampeonato camp, int *numCorridas, ptrPiloto pilotos, int *totalPilotos, ptrCarro carros, int *totalCarros){
    FILE *f;
    ptrCampeonato aux=NULL;
    ptrTreino novo=NULL;
    int corrida, conta;
    aux = malloc(sizeof (campeonato));
    if (aux == NULL) {
        printf("\nErro ao alocar memoria!");
        return camp;
    }
    novo = malloc(sizeof (treino));
    if (novo == NULL) {
        printf("\nErro ao alocar memoria!");
        return camp;
    }
    
    f = fopen(nomeFichCampeonatos, "rb");
    if (f == NULL) {
        printf("\nErro ao abrir ficheiro!\n");
        return camp;
    }

    if (fread(numCorridas, sizeof (int), 1, f) == 0) {
        printf("\nNao existem campeonatos a decorrer!");
        fclose(f);
        return camp;
    }
    while (fread(&corrida, sizeof (int), 1, f)==1) {
        aux->numCorrida=corrida;
        aux->prox=NULL;
        aux->corrida=NULL;
        fread(&conta, sizeof(int), 1, f);
        for(int i=0; i<conta; i++){
            int CarroId, PilotoId;
            fread(novo, sizeof (treino), 1, f);
            fread(&CarroId, sizeof (int), 1, f);
            fread(&PilotoId, sizeof (int), 1, f);
            for(int i=0; i<*totalPilotos && pilotos[i].Id!=PilotoId; i++);
            novo->Piloto=&pilotos[i];
            for(int i=0; i<*totalCarros && carros[i].Id!=CarroId; i++);
            novo->Carro=&carros[i];
            aux->corrida=insereTreino(aux->corrida, novo);
        }
        camp=insereCampeonato(camp, aux);

        aux = malloc(sizeof (campeonato));
        if (aux == NULL) {
            printf("\nErro ao alocar memoria!");
            return camp;
        }
    }
    fclose(f);
    free(aux);
    free(novo);
    return camp;
}
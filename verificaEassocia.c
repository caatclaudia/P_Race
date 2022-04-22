// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019
// Cláudia Tavares

#include "main.h"
#include "utils.h"

//devolve -1 se não existir
int VerificaIdPilotos(ptrPiloto pilotos, int *totalPilotos, int id){
    if(id<=0)
        return -1;
    for(int i=0; i<*totalPilotos; i++){
        if(pilotos[i].Id==id)
            return id;
    }
    return -1;
}

//devolve -1 se algum dado estiver errado
int VerificaDadosPilotos(int peso, float experiencia, int penalizacao){
    if(peso<=0)
        return -1;
    if(experiencia<0)
        return -1;
    if(penalizacao<0 || penalizacao>3)
        return -1;
    return 0;
}

//devolve -1 se algum dado estiver errado
int VerificaDataPilotos(int dia, int mes, int ano){
    int meses[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int dias[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int diaAtual, mesAtual, anoAtual, horaAtual, minutoAtual, segundoAtual;
    obtemData(&diaAtual, &mesAtual, &anoAtual, &horaAtual, &minutoAtual, &segundoAtual);
    
    if(mes > meses[11] || mes < meses[0])
        return -1;
    if(dia > dias[mes - 1] || dia < 1){
        if(mes==2 && ano%4==0 && dia<=29){
            if(ano<0 || ano>anoAtual)
                return -1;
        }
        else
            return -1;
    }
    if(ano<0 || ano>anoAtual)
        return -1;
    return 0;
}

int calculaIdade(int diaNasc, int mesNasc, int anoNasc){
    int dia, mes, ano, hora, minuto, segundo;
    int idade;
    obtemData(&dia, &mes, &ano, &hora, &minuto, &segundo);
    idade=ano-anoNasc;
    if(mes<mesNasc)
        idade--;
    else if(mes==mesNasc){
        if(dia<diaNasc)
            idade--;
    }
    return idade;
}

//devolve -1 se não existir
int VerificaIdCarros(ptrCarro carros, int *totalCarros, int id){
    if(id<=0)
        return -1;
    for(int i=0; i<=*totalCarros; i++){
        if(carros[i].Id==id)
            for(int j=i+1; j<*totalCarros; j++)
                if(carros[j].Id==carros[i].Id)
                    return id;
    }
    return -1;
}

//devolve -1 se algum dado estiver errado
int VerificaDadosCarros(int potencia, int avariado){
    if(potencia<=0)
        return -1;
    if(avariado!=0 && avariado!=1)
        return -1;
    return 0;
}

ptrTreino preencheTreino(ptrPiloto pilotos, ptrCarro carros){
    ptrTreino novo=malloc(sizeof(treino));
    if(novo==NULL){
        printf("Erro de alocacao de memoria!!\n");
        return novo;
    }
    novo->prox=NULL;
    novo->Carro=carros;
    novo->Piloto=pilotos;
    novo->atual=0;
    novo->desistiu=NAO_DESISTIU;
    novo->voltasEmPrimeiro=0;
    for(int i=0; i<MAX_VOLTAS; i++)
        novo->segundos[i]=-1;
    return novo;
}

ptrTreino copiaTreino(ptrTreino original){
    ptrTreino novo=malloc(sizeof(treino));
    if(novo==NULL){
        printf("Erro de alocacao de memoria!!\n");
        return original;
    }
    novo->prox=NULL;
    novo->Carro=original->Carro;
    novo->Piloto=original->Piloto;
    novo->atual=original->atual;
    novo->desistiu=original->desistiu;
    novo->voltasEmPrimeiro=original->voltasEmPrimeiro;
    for(int i=0; i<MAX_VOLTAS; i++)
        novo->segundos[i]=original->segundos[i];
    return novo;
}

ptrTreino eliminaTreino(ptrTreino treino, int idCarro){
    ptrTreino atual, anterior=NULL;
    atual=treino;
    while(atual!=NULL && atual->Carro->Id != idCarro){
        anterior=atual;
        atual=atual->prox;
    }
    if(atual==NULL)
        return treino;
    if(anterior==NULL)
        treino=atual->prox;
    else
        anterior->prox=atual->prox;
    return treino;
}

ptrTreino insereTreino(ptrTreino treino, ptrTreino aux){
    ptrTreino novo=malloc(sizeof(treino)), percorre;
    if(novo==NULL){
        printf("Erro de alocacao de memoria!!\n");
        return treino;
    }
    novo=copiaTreino(aux);
    novo->prox=NULL;
    if(treino==NULL)
        treino=novo;
    else{
        percorre=treino;
        while(percorre->prox!=NULL)
            percorre=percorre->prox;
        percorre->prox=novo;
    }
    return treino;
}

ptrCampeonato insereCampeonato(ptrCampeonato camp, ptrCampeonato aux){
    ptrCampeonato novo=malloc(sizeof(campeonato)), percorre;
    if(novo==NULL){
        printf("Erro de alocacao de memoria!!\n");
        return camp;
    }
    novo->corrida=aux->corrida;
    novo->numCorrida=aux->numCorrida;
    novo->prox=NULL;
    if(camp==NULL)
        camp=novo;
    else{
        percorre=camp;
        while(percorre->prox!=NULL)
            percorre=percorre->prox;
        percorre->prox=novo;
    }
    return camp;
}

ptrTreino associaCarros(ptrTreino treino, int max, ptrPiloto pilotos, int *totalPilotos, ptrCarro carros, int *totalCarros){
    ptrTreino novo=malloc(sizeof(treino));
    if(novo==NULL){
        printf("Erro de alocacao de memoria!!\n");
        return treino;
    }
    int i, j, a, existe=0, total=0;
    int pilotosDisponiveis=0, carrosDisponiveis=0;
    
    for(j=0; j<*totalPilotos; j++){
        if(pilotos[j].penalizacao<=0)
            pilotosDisponiveis++;
    }
    for(j=0; j<*totalCarros; j++){
        if(carros[j].avariado<=0)
            carrosDisponiveis++;
    }
    if(pilotosDisponiveis>=carrosDisponiveis && max>=carrosDisponiveis)
        max=carrosDisponiveis;
    else if(carrosDisponiveis>pilotosDisponiveis && max>=pilotosDisponiveis)
        max=pilotosDisponiveis;
    if(max==0){
        printf("\nNao pilotos nem carros disponiveis para continuar!");
        return NULL;
    }
    int idPilotos[max], idCarros[max];
    for(j=0; j<max; j++){
        idPilotos[j]=-1;
        idCarros[j]=-1;
    }
    
    while(total<max){
        do{
            i=intUniformRnd(0, *totalCarros-1);
            for(a=0, existe=0; idCarros[a]>=0; a++){
                if(carros[i].Id==idCarros[a])
                    existe=1;
            }
        }while(carros[i].avariado>0 || existe==1); //CARRO NAO PODE ESTAR AVARIADO
        
        do{
            j=intUniformRnd(0, *totalPilotos-1);
            for(a=0, existe=0; idPilotos[a]>=0; a++){
                if(pilotos[j].Id==idPilotos[a])
                    existe=1;
            }
        }while(pilotos[j].penalizacao>0 || existe==1); //UTILIZADOR NAO PODE ESTAR PENALIZADO
          
        idCarros[a]=carros[i].Id; //ARMAZENA IDS DE CARROS  
        idPilotos[a]=pilotos[j].Id; //ARMAZENA IDS DE PILOTOS
        
        novo=preencheTreino(&pilotos[j], &carros[i]);
        treino=insereTreino(treino, novo);
        
        total++;
    }
    free(novo);
    return treino;
}

void mostraEmperelhamentosCarros(ptrTreino treino, int max, ptrPiloto pilotos, int *totalPilotos, ptrCarro carros, int *totalCarros){
    int i, j, verd;
    int idCarros[max], idPilotos[max];
    ptrTreino tmp;
    
    tmp=treino;
    printf("\nConjuntos: ");
    for(i=0; tmp!=NULL && i<=max; i++){
        idCarros[i]=tmp->Carro->Id;
        idPilotos[i]=tmp->Piloto->Id;
        printf("\n %s - carro %d", tmp->Piloto->nome, tmp->Carro->Id);
        tmp=tmp->prox;
    }
    while(i<max){
        i++;
    }
    max=i;
    printf("\n\nCarros que nao estao em treino: ");
    for(j=0; j<*totalCarros; j++){
        verd=0;
        for(i=0; i<=max; i++){
            if(carros[j].Id==idCarros[i])
                verd=1;
        }
        if(verd==0 && carros[j].avariado==1){
            printf("\n   Carro %d - motivo: avariado", carros[j].Id);
            carros[j].avariado=carros[j].avariado-1;
        }
        else if(verd==0 && carros[j].avariado==0)
            printf("\n   Carro %d - motivo: devido ao numero maximo de pilotos/carros", carros[j].Id);
    }
    printf("\n\nPilotos que nao estao em treino: ");
    for(j=0; j<*totalPilotos; j++){
        verd=0;
        for(i=0; i<=max; i++){
            if(pilotos[j].Id==idPilotos[i])
                verd=1;
        }
        if(verd==0 && pilotos[j].penalizacao!=0){
            if(pilotos[j].impedimento==1)
                printf("\n   Piloto %s - motivo: penalizado", pilotos[j].nome);
            else
                printf("\n   Piloto %s - motivo: lesao", pilotos[j].nome);
            pilotos[j].penalizacao=pilotos[j].penalizacao-1;
        }
        else if(verd==0 && pilotos[j].penalizacao==0)
            printf("\n   Piloto %s - motivo: devido ao numero maximo de pilotos/carros", pilotos[j].nome);
    }
    printf("\n");
    free(tmp);
    return;
}

ptrTreino ordenaListaTreino(ptrTreino listaTreino){
    ptrTreino aux=listaTreino, treino=listaTreino, novoDefinitivo=NULL;
    int idCarro=0, total=0, num, idade, idadeMax=0, j, minimo, primeiro=1, corridasParticipadas;  
    
    while(aux!=NULL){
        total++;
        aux=aux->prox;
    }
            
    //O primeiro critério de desempate é o número de corridas em que
    //participaram e o segundo critério de desempate é a idade do piloto.
    for(int i=0; i<total; i++){
        aux=treino;
        for(j=0, primeiro=1; aux!=NULL; j++, aux=aux->prox){
                idade=calculaIdade(aux->Piloto->dataNasc.dia, aux->Piloto->dataNasc.mes, aux->Piloto->dataNasc.ano);
                if(primeiro==1){
                    minimo=aux->atual;
                    idadeMax=idade;
                    num=j;
                    primeiro=0;
                    corridasParticipadas=aux->Piloto->corridasParticipadas;
                }
                else if(aux->atual<minimo){
                    minimo=aux->atual;
                    idadeMax=idade;
                    num=j;
                    corridasParticipadas=aux->Piloto->corridasParticipadas;
                }
                else if(aux->atual==minimo && aux->Piloto->corridasParticipadas>corridasParticipadas){
                    minimo=aux->atual;
                    idadeMax=idade;
                    num=j;
                    corridasParticipadas=aux->Piloto->corridasParticipadas;
                }
                else if(aux->atual==minimo && idade<idadeMax){
                    minimo=aux->atual;
                    idadeMax=idade;
                    num=j;
                    corridasParticipadas=aux->Piloto->corridasParticipadas;
            }
        }
        aux=treino;
        for(int a=0; aux!=NULL; a++, aux=aux->prox){
            if(a==num){
                novoDefinitivo=insereTreino(novoDefinitivo, aux);
                idCarro=aux->Carro->Id;
            }
        }
        treino=eliminaTreino(treino, idCarro);
    }
    listaTreino=novoDefinitivo;
    free(aux);
    free(treino);
    return listaTreino;
}
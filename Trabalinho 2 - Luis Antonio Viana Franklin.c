// Luis Antonio Viana Franklin
// Turma 1 - Engenharia de Software



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//Variáveis
int cont = 0;
int bloco = 0; qt_blocos = 1;  
int qt_tweets = 0; qt_hashtag = 0; 


//Arquivo
FILE *arquivo;
FILE *arquivo2;


//Estruturas de dados
typedef struct bloco{
    char **tweets;
    struct bloco *prox;}Bloco;
Bloco *inicio = NULL;
Bloco *fim = NULL;

typedef struct hashtag{ 
    char hashtag[50];
    int quantidade;
    struct hashtag *prox;}Hashtag;
Hashtag *inicio_tag = NULL;
Hashtag *fim_tag = NULL;

Bloco* blocos_dinamicos(int tam){
    Bloco* novo_bloco = malloc(sizeof(Bloco));
    novo_bloco->prox = NULL;
    novo_bloco->tweets = malloc(tam * sizeof(char*));

    for (int j = 0; j < tam; ++j){
        novo_bloco->tweets[j] = (char *)malloc(281);
        novo_bloco->tweets[j] = "\0";}
    if(inicio == NULL){
        inicio = novo_bloco;
        fim = novo_bloco;}
    else{
        fim->prox = novo_bloco;
        fim = novo_bloco;}
    return novo_bloco;}



//0 - Contador
void contador(int tam){
    cont++;
    qt_tweets++;

    while(cont == tam){
        cont = 0;
        bloco++;
        qt_blocos++;}}


//1 - Função de Tweetar
void adcionar_tweets(int tam){
    char frase[281] = "\0";
    int tamanho, tam_2;

    printf("===============================================\n");
    printf("              Funcao Tweetar\n");
    printf("===============================================\n");
    printf("O que voce deseja tuitar?\n\n");
    printf("Insira: ");
    fflush(stdin);
    scanf("%[^\n]s",frase);

    tamanho = strlen(frase);
    tam_2 = tamanho - 281;

    while(tamanho > 281){
        printf("\n!!O seu tweet ultrapassou o maximo de 280 caracteres!!\nTweet novamente com %d caracteres a menos!!\n", tam_2);
        fflush(stdin);
        scanf("%[^\n]s",frase);
        tamanho = strlen(frase);
        tam_2 = tamanho - 281;}
        printf("-----------------------------------------------\n");
        tweetar(frase, tam);
        menu(tam);}

void tweetar(char* frase[281], int tam){
    Bloco* novo_bloco = blocos_dinamicos(tam);
    novo_bloco->tweets[cont] = frase;
    char *tweet = malloc(281 *sizeof(char));
    strcpy(tweet,frase);
    verificar_hastag(tweet);
    contador(tam);}


//2 - Função de Listar
void listar(int tam){
    Bloco* aux = inicio;
    int j = 0;
    int n = 0;

    printf("===============================================\n");
    printf("              Listando Tweets\n");
    printf("===============================================\n\n");

    if(aux == NULL){
        printf("Nao existem tweets na memoria :/\n");
        menu(tam);}

    printf("BLOCO 0\n");
    for(aux = inicio; aux != NULL;aux = aux->prox){
        for(int i = 0; i < tam; i++){
            if(j == tam){j = 0;n++; 
                printf("\nBLOCO %d\n",n);}
            printf("%s", aux->tweets[i]);}
            printf("\n");j++;}
            printf("-----------------------------------------------\n");
            menu(tam);}


//3 - Função de Filtrar Hashtag
void filtrar(int tam){
    Bloco* aux = inicio;
    char hashtag[281];
    char *busca;
    int resul;

    printf("===============================================\n");
    printf("                 FILTRAR #\n");
    printf("===============================================\n\n");
    printf("Qual # que voce deseja procurar?\n");
    printf("Digite na forma #NOME: ");
    fflush(stdin);
    scanf("%s", hashtag);

    if(aux == NULL){
    printf("\nNao existem tweets na memoria\n");printf("\n----------------------------------------\n");menu(tam);}


    for(aux = inicio; aux != NULL; aux = aux->prox){
        for(int i = 0; i < tam; i++){
            busca = strstr(aux->tweets[i], hashtag); //Encontra a primeira ocorrência da substring que e a #procurada
            if(busca){//Se for verdade, imprime a frase com a #
                printf("\nTweet: %s\n", aux->tweets[i]);}
            else{printf("\nNao existem tweets com a %s\n",hashtag);}}}
            printf("\n----------------------------------------\n");
            menu(tam);}


//4 - Listar Treding Topics
void verificar_hastag(char *frase){
    int c;
    char *cp_1;
    char *cp_2;

    while(cp_1 != NULL){
        cp_1 = strchr(frase, '#');
        if(cp_1 == NULL){
            break;}
        cp_2 = strchr(cp_1, ' ');
        if(!cp_2){
            cp_2 = strchr(cp_1, '\0');}

        c = cp_2 - cp_1;
        char hashtag[280] = "\0";
        strncpy(hashtag, cp_1, c);
        cadastrar_hashtag(hashtag);
        strcpy(cp_1, cp_2);}}

void cadastrar_hashtag(char * hashtag){
    Hashtag * aux;
    int resul = 0;

    if (inicio_tag  == NULL){//Adciona a primeira ocorrência na priemira posição da fila com quantidade 1
        Hashtag* nova_hashtag = malloc(sizeof(Hashtag));
        nova_hashtag->prox = NULL;
        strcpy(nova_hashtag->hashtag, hashtag);
        nova_hashtag->quantidade = 1; 
        qt_hashtag++;

        if(inicio_tag == NULL){
            inicio_tag = nova_hashtag;
            fim_tag = nova_hashtag;}
        else{
            fim_tag->prox = nova_hashtag;
            fim_tag = nova_hashtag;}}
        else{
            for (aux = inicio_tag; aux != NULL; aux = aux->prox){//Se a tag for igual, so aumenta a quantidade
                if(strcmp(hashtag, aux->hashtag) == 0){
                    aux->quantidade += 1;
                    resul = 1;
                    qt_hashtag++;}}

        if (resul == 1){}
        else{
            Hashtag* nova_hashtag = malloc(sizeof(Hashtag));//Adciona a segunda ocorrência na fila com quantidade 1
            nova_hashtag->prox = NULL;
            strcpy(nova_hashtag->hashtag, hashtag);
            nova_hashtag->quantidade = 1;
            qt_hashtag++;

            if(inicio_tag == NULL){
                inicio_tag = nova_hashtag;
                fim_tag = nova_hashtag;}
            else{
                fim_tag->prox = nova_hashtag;
                fim_tag = nova_hashtag;}}}}

void trending_topics(int tam){
    Hashtag * aux = inicio_tag;
    printf("===============================================\n");
    printf("              Trending Topics\n");
    printf("===============================================\n\n");
    printf("       | %-20s %-5s |\n", "Tags", "Qtd");
    
    for( aux = inicio_tag; aux != NULL; aux = aux->prox){
        printf("       | %-22s %-3d |", aux->hashtag, aux->quantidade);
        printf("\n");}
        printf("-----------------------------------------------\n");
        menu(tam);}


//5 - Informações do Administrador
void adm(int tam){
    int opcao;
    int esp_livre;

    printf("===============================================\n");
    printf("              FUNCAO ADM\n");
    printf("===============================================\n");
    printf("1)Quantidade de tweets?\n2)Quantidade de blocos?\n3)Quantidade de hashtags?\n4)Espaco livre no ultimo bloco?\n5)Voltar ao menu?:\n");
    scanf("%d", &opcao);

        while(opcao < 1 || opcao > 5){
        printf("!!OPCAO INVALIDA!!\n");
        printf("O que dejesa ver?\n");
        printf("1)Quantidade de tweets?\n2)Quantidade de blocos?\n3)Quantidade de hashtags?\n4)Espaco livre no ultimo bloco?\n5)Voltar ao menu?:\n");
        scanf("%d", &opcao);}

        switch (opcao){

            case 1:
                if (qt_tweets == 1){
                    printf("Existe 1 tweet na memoria!\n");
                    printf("-----------------------------------------------\n");}
                else{
                    printf("Existem %d tweets na memoria!\n", qt_tweets);
                    printf("-----------------------------------------------\n");}
                    printf("O que voce deseja?\n1)Continuar no Menu ADM\n2)Voltar ao menu principal\n");
                    scanf("%d",&opcao);

                while(opcao < 1 || opcao > 2){
                    printf("!!OPCAO INVALIDA!!\n");
                    printf("O que voce deseja?\n1)Continuar no Menu ADM\n2)Voltar ao menu principal\n");
                    scanf("%d", &opcao);}

                switch(opcao){
                case 1:
                    adm(tam); break;
                case 2:
                    menu(tam); break;}

            case 2:
                if(qt_blocos == 1){
                    printf("Existe 1 bloco na memoria!\n");}
                else{
                    printf("Existem %d blocos na memoria!\n", qt_blocos);}

                printf("O que voce deseja?\n1)Continuar no Menu ADM\n2)Voltar ao menu principal\n");
                scanf("%d",&opcao);

                while(opcao < 1 || opcao > 2){
                    printf("!!OPCAO INVALIDA!!\n");
                    printf("O que voce deseja?\n1)Continuar no Menu ADM\n2)Voltar ao menu principal\n");
                    scanf("%d", &opcao);}

                switch(opcao){
                case 1:
                    adm(tam); break;
                case 2:
                    menu(tam); break;}

            case 3:
                if(qt_hashtag == 1){
                    printf("Existe 1 hashtag na memoria!\n");
                    printf("-----------------------------------------------\n");}
                else{
                    printf("Existem %d hashtags na memoria!\n", qt_hashtag);
                    printf("-----------------------------------------------\n");}

                printf("O que voce deseja?\n1)Continuar no Menu ADM\n2)Voltar ao menu principal\n");
                scanf("%d",&opcao);

                while(opcao < 1 || opcao > 2){
                    printf("!!OPCAO INVALIDA!!\n");
                    printf("O que voce deseja?\n1)Continuar no Menu ADM\n2)Voltar ao menu principal\n");
                    scanf("%d", &opcao);}

                switch(opcao){
                case 1:
                    adm(tam); break;
                case 2:
                    menu(tam); break;}

            case 4:
                esp_livre = tam - cont;
                if (esp_livre == 0){
                    printf("O Bloco %d\n nao tem mais espaco livre!\n", bloco);
                    printf("-----------------------------------------------\n");}
                else if(esp_livre == 1){
                    printf("O Bloco %d tem 1 espaco livre!\n", bloco);
                    printf("-----------------------------------------------\n");}
                else{
                    printf("O Bloco %d tem %d espacos livres!\n", bloco, esp_livre);
                    printf("-----------------------------------------------\n");}

                printf("O que voce deseja?\n1)Continuar no Menu ADM\n2)Voltar ao menu principal\n");
                scanf("%d",&opcao);

                    while(opcao < 1 || opcao > 2){
                    printf("!!OPCAO INVALIDA!!\n");
                    printf("O que voce deseja?\n1)Continuar no Menu ADM\n2)Voltar ao menu principal\n");
                    scanf("%d", &opcao);}

                switch(opcao){
                case 1:
                    adm(tam); break;
                case 2:
                    menu(tam); break;}

            case 5:
                printf("Voltando para o menu principal\n");
                printf("-----------------------------------------------\n");
                menu(tam);
                break;}}


//6 - Salvar arquivos
void salvar(int tam){
    char nome_arquivo[50] = "\0";
    Bloco* aux = inicio;

    char frase[281];
    printf("\n------------------------------\n");
    printf("Insira o nome\no seu arquivo: ");
    scanf("%s",nome_arquivo);
    fflush(stdin);

    arquivo = fopen(nome_arquivo,"w");

    //Adcionar data e hora
    time_t seconds;
    struct tm *timeStruct;
    seconds = time(NULL);
    timeStruct = localtime(&seconds);
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    fprintf(arquivo,"Data: %d/%d/%d ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    fprintf(arquivo,"Hora: %d:%d\n\n", timeStruct->tm_hour, timeStruct->tm_min);

    for(aux = inicio; aux != NULL;aux = aux->prox){
        for (int i = 0; i < tam; i++){
            fprintf(arquivo,"%s", aux->tweets[i]);}
            fprintf(arquivo,"\n");}
    fclose(arquivo);
    printf("\n------------------------------\n");
    menu(tam);}


//7 - Carregar arquivos - Arrumar
void zerar_lista(){
    Bloco *lixo;;
    qt_tweets = 0;
    qt_tweets = 0;
    while(inicio != NULL){
        lixo = inicio;
        inicio = inicio->prox;}}

void zerar_hashtag(){
    Hashtag *lixo;;
    while(inicio_tag != NULL){
        lixo = inicio_tag;
        inicio_tag = inicio_tag->prox;}
        qt_hashtag = 0;}

void carregar_arquivos(int tam){
    char nome_arquivo[20];
    char frase[281];
    int opcao;

    printf("\n------------------------------\n");
    printf("Insira o nome do arquivo\nque deseja carregar: ");
    fflush(stdin);
    scanf("%s",nome_arquivo);
    arquivo2 = fopen(nome_arquivo,"r");

    while (arquivo2==NULL){
        printf("\nEsse aqurivo nao existe!!!");
        printf("\nInsira um nome de arquivo valido: ");
        scanf("%s",nome_arquivo);
        arquivo2 = fopen(nome_arquivo,"r");}

    printf("\n\nImprimindo Arquivo...\n");
    arquivo2 = fopen(nome_arquivo,"r");

    while(fgets(frase,281,arquivo2) != NULL){
        printf("%s",frase);}
    printf("\n");

    printf("O que voce deseja fazer?\n[1]Adcionar esses Tweets junto aos existentes\n[2]Zerar a lista e adcionar os tweets desse arquivo: ");
    scanf("%d",&opcao);
    printf("\n");

    while(opcao < 1 || opcao > 2){
        printf("!!OPCAO INVALIDA!!\n");
        printf("O que dejesa fazer?\n");
        printf("O que voce deseja fazer?\n[1]Adcionar esses Tweets junto aos existentes\n[2]Zerar a lista e adcionar os tweets desse arquivo: ");
        scanf("%d", &opcao);
        printf("\n");}

    switch(opcao){
    
    case 1:
        arquivo2 = fopen(nome_arquivo, "r");
        fgets(frase, 281, arquivo2);
        fgets(frase, 281, arquivo2);

        while(fgets(frase, 281, arquivo2) != NULL){
            char *tweet = malloc(281 *sizeof(char));
            strcpy(tweet, frase);
            tweetar(tweet,tam);}
        fclose(arquivo2);
        menu(tam);
        break;

    case 2:
        zerar_lista();
        zerar_hashtag();
        arquivo2 = fopen(nome_arquivo, "r");
        fgets(frase, 281, arquivo2);
        fgets(frase, 281, arquivo2);

        while(fgets(frase, 281, arquivo2) != NULL){
            char *tweet = malloc(281 *sizeof(char));
            strcpy(tweet, frase);
            tweetar(tweet,tam);}
        fclose(arquivo2);
        menu(tam);
        break;}}


//Menu
void menu(int tam){
    int opcao;
    printf("===============================================\n");
    printf("                   MENU\n");
    printf("===============================================\n");
    printf("O que dejesa fazer?\n");
    printf("[1]Fazer um tweet\n[2]Listar todos seus tweets\n[3]Filtrar uma hastag?(#)\n[4]Listar os Treding Topics\n[5]Entrar nas Informacoes de Administrador\n[6]Salvar seus tweets\n[7]Carregar um arquivo\n[8]Sair: ");
    scanf("%d", &opcao);

    while(opcao < 1 || opcao > 8){
        printf("!!OPCAO INVALIDA!!\n");
        printf("O que dejesa fazer?\n");
        printf("[1]Fazer um tweet\n[2]Listar todos seus tweets\n[3]Filtrar uma hastag?(#)\n[4]Listar os Treding Topics\n[5]Entrar nas Informacoes de Administrador\n[6]Salvar seus tweets\n[7]Carregar um arquivo\n[8]Sair: ");
        scanf("%d", &opcao);}

    switch(opcao){
    case 1:
        adcionar_tweets(tam);
        break;
    case 2:
        listar(tam);
        break;
    case 3:
        filtrar(tam);
        break;
    case 4: 
        trending_topics(tam);
        break;
    case 5:
        adm(tam);
        break;
    case 6:
        salvar(tam);
        break;
    case 7:
        carregar_arquivos(tam);
        break;
    case 8:
        printf("Obrigado, ate logo!");
        exit(0);}}

//Main
int main(){
    int opcao;
    int tt_blocos;
    printf("Seja bem-vindo(a) ao 'Twitter Lite'\nQuantos Tweets voce deseja ter por bloco?\n");
    scanf("%d",&tt_blocos);

    menu(tt_blocos);}


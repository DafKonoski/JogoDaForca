#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

char palavrasecreta [TAMANHO_PALAVRA];
char chutes [26];
int chutesdados = 0;

void abertura(){
    printf("\n");
    printf("                       JOGO DA FORCA\n");
    printf("\n");
    printf(",---,---,---,---,---,---,---,---,---,---,---,---,---,-------, \n");
    printf("| ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | [ | ] | <-    | \n");
    printf("|---'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-----| \n");
    printf("| ->|  "" | , | . | P | Y | F | G | C | R | L | / | = |    ""   | \n");
    printf("|-----',--',--',--',--',--',--',--',--',--',--',--',--'-----| \n");
    printf("| Caps | A | O | E | U | I | D | H | T | N | S | - |  Enter | \n");
    printf("|------'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'--------| \n");
    printf("|        | ; | Q | J | K | X | B | M | W | V | Z |          | \n");
    printf("|------,-',--'--,'---'---'---'---'---'---'-,-'---',--,------| \n");
    printf("| ctrl |  | alt |                          | alt  |  | ctrl | \n");
    printf("'------'  '-----'--------------------------'------'  '------' \n");
    printf("\n");
    printf("                    DIGITE UMA LETRA!\n");
    printf("\n");

}

void chuta(){
    char chute;
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra){
    int achou = 0;
    for(int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca(){
    int erros = chuteserrados();

    printf("   +---+      \n");
    printf("   |   |      \n");
    printf("   |   |      \n");
    printf("   %c   |     \n", (erros >= 1 ? 'O' : ' ')); //if ternario. se for >= 1 ? printa O senão : printa espaço
    printf("  %c%c%c  |   \n", (erros >= 3 ? '/' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 4 ? '\\' : ' '));
    printf("  %c %c  |     \n", (erros >= 5 ? '/' : ' '), (erros >= 6 ? '\\' : ' '));
    printf("       |      \n");
    printf(" =========''' \n");
    printf("\n\n");

    for(int i = 0; i <strlen(palavrasecreta); i++){

        int achou = jachutou(palavrasecreta[i]);

        if(achou){
            printf("%c ", palavrasecreta[i]);
        } else{
            printf("_ ");
        }
    }
    printf("\n");
}

void adicionapalavra(){
    char quer;
    printf("Deseja adicionar uma nova palavra no jogo? (S/N)\n");
    scanf(" %c", &quer); //o espaço avisa o scanf q quero capturar um char só

    if(quer == 's'){
        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra?\n");
        scanf("%s", &novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+"); //r+ é leitura e escrita
        if(f == 0){ //caso o arquivo esteja corrompido
           printf("Desculpe, banco de dados nao disponivel\n\n");
            exit(1); //exit e um numero maior q 0, significa q o programa deu problema (exit 0 é q funcionou)
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET); //acrescentar 1 no começo do arquivo - fseek pra posicionar
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END); //acrescentar 1 no final do arquivo 
        fprintf(f, "\n%s", novapalavra); //abre o arquivo, coloca um enter e escreve, guarda na variavel

        fclose(f);
    }
}

void escolhepalavra(){
    FILE* f; //criei uma variavel pra receber o ponteiro do arquivo
    f = fopen("palavras.txt", "r"); //abro o arquivo primeiro e depois pra q eu quero esse arquivo, como eu quero pra ler, eu uso r de read
    if(f == 0){ //caso o arquivo esteja corrompido
        printf("Desculpe, banco de dados nao disponivel\n\n");
        exit(1); //exit e um numero maior q 0, significa q o programa deu problema (exit 0 é q funcionou)
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras); //arquivo, sei q a primeira coisa é um num, entao coloco a variavel d, por fim o ponteiro 

    srand(time(0)); 
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavrasecreta); //lê do arquivo, é uma string, guardo na variavel 
    }

    fclose(f); //sempre fecha pra desocupar
}

int acertou(){
    for(int i =0; i < strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int chuteserrados(){
    int erros = 0;
    for(int i = 0; i < chutesdados; i++){
        int existe = 0;
        for(int j = 0; j <strlen(palavrasecreta); j++){
            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros;
}

int enforcou(){
    return chuteserrados() >= 7;
}

int main(){
    escolhepalavra();
    abertura();

    do {
        desenhaforca();
        chuta();
        
    } while (!acertou() && !enforcou());

    if (acertou()){
        printf("Parabens! Voce ganhou!\n");

        printf("                     ***************** \n");
        printf("                ******               ****** \n");
        printf("            ****                           **** \n");
        printf("         ****                                 *** \n");
        printf("       ***                                       *** \n");
        printf("      **           ***               ***           ** \n");
        printf("    **           *******           *******          *** \n");
        printf("   **            *******           *******            ** \n");
        printf("  **             *******           *******             ** \n");
        printf("  **               ***               ***               ** \n");
        printf(" **                                                     ** \n");
        printf(" **       *                                     *       ** \n");
        printf(" **      **                                     **      ** \n");
        printf("  **   ****                                     ****   ** \n");
        printf("  **      **                                   **      ** \n");
        printf("   **       ***                             ***       ** \n");
        printf("    ***       ****                       ****       *** \n");
        printf("      **         ******             ******         ** \n");
        printf("       ***            ***************            *** \n");
        printf("         ****                                 **** \n");
        printf("            ****                           **** \n");
        printf("                ******               ****** \n");
        printf("                     ***************** \n");
    } else {
        printf("Voce perdeu!\n");
        
        printf("              ;::::; \n");
        printf("            ;::::; :; \n");
        printf("          ;:::::'   :; \n");
        printf("         ;:::::;     ;. \n");
        printf("        ,:::::'       ;           OOO\\ \n");
        printf("        ::::::;       ;          OOOOO\\ \n");
        printf("        ;:::::;       ;         OOOOOOOO \n");
        printf("       ,;::::::;     ;'         / OOOOOOO \n");
        printf("     ;:::::::::`. ,,,;.        /  / DOOOOOO \n");
        printf("   .';:::::::::::::::::;,     /  /     DOOOO \n");
        printf("  ,::::::;::::::;;;;::::;,   /  /        DOOO \n");
        printf(" ;`::::::`'::::::;;;::::: ,#/  /          DOOO \n");
        printf(" :`:::::::`;::::::;;::: ;::#  /            DOOO \n");
        printf(" ::`:::::::`;:::::::: ;::::# /              DOO \n");
        printf(" `:`:::::::`;:::::: ;::::::#/               DOO \n");
        printf("  :::`:::::::`;; ;:::::::::##                OO \n");
        printf("  ::::`:::::::`;::::::::;:::#                OO \n");
        printf("  `:::::`::::::::::::;'`:;::#                O \n");
        printf("   `:::::`::::::::;' /  / `:# \n");
        printf("    ::::::`:::::;'  /  /   `# \n");
    }
    

    adicionapalavra();
    

}
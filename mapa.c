#include <stdio.h>
#include <string.h>

//Define as constantes que controla programa
#define TAMANHO_ACERVO 20
#define MAX_TITULO 50
#define MAX_AUTOR 30
#define MAX_AREA 30
#define MAX_EDITORA 30


//Estrutura que representa um livro, e armazena tipos distintos de dados
struct livro{
    int codigo;
    char titulo[50];
    char autor[30];
    int ano;
    char area[30];
    char editora[30];
};
//variavel global, armazena os livros salvos
int quant_liv = 0;
//assinatura de funções
void strip_newline(char *s); //Remove o caaracter "\n" que fica ao final quando usa fgets
//cadastra livros ao acervo
void cadastrarLivro(struct livro acervo[],int tamanho);
//Imprime  todos os livros cadastrados no acervo
void imprimirLivro(struct livro acervo[],int tamanho);
//Pesquisa livros cadastrados por codigo registrado
void pesquisarLivro(struct livro acervo[],int tamanho);
//Ordena os livros por ano
void ordenarLivro(struct livro acervo[],int tamanho);
//Busca em todos os livros cadastrados se aquele codigo ja existe
int codigoExistente(struct livro acervo[], int quantidade, int codigo);

//Função principal
int main(){
struct livro acervo[TAMANHO_ACERVO];
int opc_menu;
do{
printf("\n=========== MENU ===========");
printf("\n======= Biblioteca =========\n");
printf("1-Cadastrar Livros\n");
printf("2-Imprimir todos os livros\n");
printf("3-Pesquisar livro por codigo\n");
printf("4-Ordenar livros por ano de publicacao\n");
printf("5-Sair do programa\n");
printf("Escolha uma opcao: ");
//verifica se o usuario digitou um numero valido
if (scanf("%d", &opc_menu) != 1) {
printf("opcao invalida, tente outra vez");
fflush(stdin);
continue;
}
fflush(stdin); //limpa o buffer do teclado


            //utilizado para mostrar o menu ao usuario, conforme ele escolhe  uma opcao, as outras   sao ignoradas.
            switch (opc_menu) {
            case 1:
                cadastrarLivro(acervo, TAMANHO_ACERVO);
                break;
            case 2:
                imprimirLivro(acervo, TAMANHO_ACERVO);
                break;
            case 3:
                pesquisarLivro(acervo, TAMANHO_ACERVO);
                break;
            case 4:
                ordenarLivro(acervo, TAMANHO_ACERVO);
                printf("Livros ordenado por ano de publicacao(crescente)");
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("opcao invalida, tente outra vez. \n");
        }

    } while (opc_menu != 5); //repete o menu enquanto a opcao nao for 5, que e a de sair.

    return 0;
}
//Remove o caractere "\n" que o fgets() deixa ao final da string.
void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') {
        s[len-1] = '\0';
    }
}
//verifica o estoque do acervo.
void cadastrarLivro(struct livro acervo[],int tamanho) {
    if (quant_liv >= tamanho) {
        printf("Sistema cheio. Não é mais possivel cadastrar livros. \n");
        return;
    }

    //cadastra novos livros enquanto estiver  espaco no acervo.
    for (int i = quant_liv; i < tamanho; i++) {
        struct livro novo;
        char opcao;

        printf("=== Cadastrar livro (posicao %d de %d) ====\n", i + 1, tamanho);

        printf("Codigo: ");
        while(1){ //criei um loop controlado,


            if (scanf("%d", &novo.codigo) != 1) {
                printf("Codigo invalido. Tente novamente: " );
                fflush(stdin);
                continue;
            }

            if (codigoExistente(acervo, quant_liv, novo.codigo)) {
                printf("Codigo ja existente. Digite outro: "); //mostra que ja tem um codigo idêntico cadastrado no sistema
                fflush(stdin);
                continue;
            }
            break;
        }
        fflush(stdin);

        printf("Titulo: ");
        fgets(novo.titulo, MAX_TITULO, stdin);
        strip_newline(novo.titulo);

        printf("Autor: ");
        fgets(novo.autor, MAX_AUTOR, stdin);
        strip_newline(novo.autor);

        printf("Area: ");
        fgets(novo.area, MAX_AREA, stdin);
        strip_newline(novo.area);

        printf("Ano de publicacao: ");
        while (scanf("%d", &novo.ano) != 1) {
            printf("Ano invalido. Tente novamente com um numero inteiro: " );
            fflush(stdin);
        }
        fflush(stdin);

        printf("Editora: ");
        fgets(novo.editora, MAX_EDITORA, stdin);
        strip_newline(novo.editora);

        acervo[quant_liv] = novo;
        quant_liv++;

        printf("Livro cadastrado! Contem %d livro(s) cadastrado de %d. Restam %d vagas disponiveis\n", quant_liv,TAMANHO_ACERVO, TAMANHO_ACERVO - quant_liv); //mostra quantos livros  esta cadastrados e quantos ainda cabe no acervo
        fflush(stdin);


        if (quant_liv >= tamanho) {
            printf("O acervo esta cheio, nao e mais possivel cadastrar livro(s). "); //verifica se o acervo esta cheio.
            break;
        }

        printf("Deseja cadastrar outro(s) livro(s)? (s|n): ");  // pergunta ao usuario se deseja cadastrar mais livros ou  nao
        scanf("%c", &opcao);
        fflush(stdin);

        if (opcao != 's' && opcao != 'S') {  //verifica se o usuario digitou 's' para cadastrar mais livros, e nao digitou ele para o laço
            break;
        }
    }

}

void imprimirLivro(struct livro acervo[],int tamanho) {
    if (quant_liv == 0) {   //verifica se tem algum livro cadastrado
        printf("Nao foi possivel imprimir livro, nao existe livro cadastrado ao sistema");
        return;
    }

    printf("---- Livros cadastrados (%d) de (%d)", quant_liv, TAMANHO_ACERVO); //mostra quantos livros foram cadastrados
    for (int i = 0; i < quant_liv; i++) {    //percorre o vetor e imprime os dados de cada livro.
        printf("\nPosicao %d\n", i + 1); //coloquei +1 para ficar melhor para  o usuario entender.
        printf("Codigo: %d\n", acervo[i].codigo);
        printf("Titulo: %s\n", acervo[i].titulo);
        printf("Autor: %s\n", acervo[i].autor);
        printf("Area: %s\n", acervo[i].area);
        printf("Ano %d\n", acervo[i].ano);
        printf("Editora: %s\n", acervo[i].editora);
    }
}

void pesquisarLivro(struct livro acervo[], int tamanho)
{
    if (quant_liv == 0) {   //verifica se algum livro foi cadastrado.
        printf("Nenhum livro(s) cadastrado, nao e possivel pesquisar.");
        return; // sai da função.
    }

    int codigoPesquisa;
    printf("Digite o codigo do livro que deseja pesquisar: ");
    while (scanf("%d", &codigoPesquisa) != 1) {                  // se o usuario digitar algo errado ele avisa.
        printf("Codigo invalido. Tente novamente: " );
        fflush(stdin);//limpa buffer do teclado.
    }
    fflush(stdin);



    int i = 0; //pecoorre o vetor posicao por posicao
    int encontrada = 0; //utilazado para indicar se  encontrou um livro.
    while (i < quant_liv) { //aqui eu uso um while pra percorrer cada posição do vetor de livros ate a quantidade cadastrada.
        if (acervo[i].codigo == codigoPesquisa) { //verifica se o codigo do livro e igual ao digitado
            printf("\nLivro identificado (posicao %d de %d): ", i + 1, TAMANHO_ACERVO); //coloquei +1 so para ficar melhor do usuario ver e entender.
            printf("Codigo: %d\n", acervo[i].codigo);
            printf("Titulo: %s\n", acervo[i].titulo);
            printf("Autor: %s\n", acervo[i].autor); //mostra todas as inf do liivro cadastrado
            printf("Area: %s\n", acervo[i].area);
            printf("Ano %d\n", acervo[i].ano);
            printf("Editora: %s\n", acervo[i].editora);
            encontrada = 1;        // marca que encontrou e sai do laço
            break;
        }
        i++; //incremento para o proximo livro.
    }
    if (encontrada == 0) {
        printf("Livro nao identificado. \n"); //se nenhum livro  for encontrado ele mostra a mensagem.

    }

}

void ordenarLivro(struct livro acervo[], int tamanho)
{
    if (quant_liv < 2) return; //verifica se tem pelo menos 2 livros cadastrados.

    for (int i = 0; i < quant_liv - 1; i++) { //define quantas vezes o laço vai percorrer o vetor.
        for (int j = 0; j < quant_liv - 1 - i; j++) {   //compara cada livro com o proximo.
            if (acervo[j].ano > acervo[j + 1].ano) {  //aqui verifica se os ano do livro atual é maior que o proximo para fazer a troca de posição.
                struct livro aux = acervo[j]; //aqui para ficar em ordem, usei uma variavel auxiliar para nao perder os dados e ordenar os anos.
                acervo[j] = acervo[j + 1];
                acervo[j + 1] = aux;
            }
        }
    }
}

int codigoExistente(struct livro acervo[], int quantidade, int codigo) {
    for (int i = 0; i < quantidade; i++) {
        if (acervo[i].codigo == codigo) {
            return 1;
        }
    }
return 0;
}
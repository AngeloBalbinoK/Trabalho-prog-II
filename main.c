#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    char nome[50];
    char sexo;
    int idade;
}Cliente;
typedef struct {
    Cliente cliente;
    int num_itens;
    char franquia;
    float valor_total;
} Compra;


void carregarCompras(Compra **lista, int *total);
void salvarCompras(Compra *lista, int total);
void cadastrarCompras(Compra **lista, int *total);
void pesquisarCompra(Compra *lista, int total);
void relatorioCompras(Compra *lista, int total);


int main() {
    Compra *lista = NULL;
    int total = 0;
    int opcao;
    char voltar;

    carregarCompras(&lista, &total);

    do {
        printf("\n===== STORE FLAMENGO&SAQUAREMA =====\n");
        printf("1 - Cadastrar novas compras\n");
        printf("2 - pesquisar compra por nome\n");
        printf("3 - Ver todas as compras\n");
        printf("4 - Encerrar\n\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarCompras(&lista, &total);
                break;

            case 2:
                pesquisarCompra(lista, total);
                break;

            case 3:
                relatorioCompras(lista, total);
                printf("\nDeseja voltar ao menu? (s/n): ");
                scanf(" %c", &voltar);
                if (voltar == 'n' || voltar == 'N') {
                    opcao = 4;
                    printf("Programa encerrado.\n");
                }
                break;

            case 4:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 4);

    free(lista);
    return 0;
}

void carregarCompras(Compra **lista, int *total) {
    FILE *arquivo = fopen("camisas.txt", "r");

    if (arquivo == NULL) {
        return;
    }

    Compra temp;

    while (fscanf(arquivo, " %[^\n]\n%c\n%d\n%d\n%c\n%f\n",
           temp.cliente.nome,
           &temp.cliente.sexo,
           &temp.cliente.idade,
           &temp.num_itens,
           &temp.franquia,
           &temp.valor_total) == 6) {

        *lista = realloc(*lista, (*total + 1) * sizeof(Compra));
        (*lista)[*total] = temp;
        (*total)++;
    }

    fclose(arquivo);
}

void salvarCompras(Compra *lista, int total) {
    FILE *arquivo = fopen("camisas.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar arquivo.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s\n", lista[i].cliente.nome);
        fprintf(arquivo, "%c\n", lista[i].cliente.sexo);
        fprintf(arquivo, "%d\n", lista[i].cliente.idade);
        fprintf(arquivo, "%d\n", lista[i].num_itens);
        fprintf(arquivo, "%c\n", lista[i].franquia);
        fprintf(arquivo, "%.2f\n", lista[i].valor_total);
    }

    fclose(arquivo);
}

void cadastrarCompras(Compra **lista, int *total) {
    int qtd;
    char continuar;

    do {
        printf("Quantidade de compras: ");
        scanf("%d", &qtd);

        while (qtd <= 0) {
            printf("Valor invalido.\n");
            printf("Quantidade de compras: ");
            scanf("%d", &qtd);
        }

        *lista = realloc(*lista, (*total + qtd) * sizeof(Compra));

        for (int i = 0; i < qtd; i++) {
            Compra nova;

            printf("\nCompra %d\n", i + 1);
            printf("Nome: ");
            scanf(" %[^\n]", nova.cliente.nome);

            while (strlen(nova.cliente.nome) < 4) {
                printf("invalido. só caracter e no minimo 4.\n");
                printf("Nome: ");
                scanf(" %[^\n]", nova.cliente.nome);
            }

            printf("Sexo (m/f/n): ");
            scanf(" %c", &nova.cliente.sexo);

            while (nova.cliente.sexo != 'm' && 
                   nova.cliente.sexo != 'f' && 
                   nova.cliente.sexo != 'n') {
                printf("Sexo invalido.\n");
                printf("Sexo (m/f/n): ");
                scanf(" %c", &nova.cliente.sexo);
            }

            printf("Idade: ");
            scanf("%d", &nova.cliente.idade);

            while (nova.cliente.idade <= 0) {
                printf("Idade invalida.\n");
                printf("Idade: ");
                scanf("%d", &nova.cliente.idade);
            }

            printf("Numero de itens: ");
            scanf("%d", &nova.num_itens);

            while (nova.num_itens < 0) {
                printf("Valor invalido.\n");
                printf("Numero de itens: ");
                scanf("%d", &nova.num_itens);
            }

            printf("Franquia (A/B/C): ");
            scanf(" %c", &nova.franquia);

            while (nova.franquia != 'A' && 
                   nova.franquia != 'B' && 
                   nova.franquia != 'C') {
                printf("Franquia invalida.\n");
                printf("Franquia (A/B/C): ");
                scanf(" %c", &nova.franquia);
            }

            printf("Valor total: ");
            scanf("%f", &nova.valor_total);

            while (nova.valor_total < 0) {
                printf("Valor invalido.\n");
                printf("Valor total: ");
                scanf("%f", &nova.valor_total);
            }

            (*lista)[*total] = nova;
            (*total)++;
            printf("Compra cadastrada com sucesso.\n");
        }

        salvarCompras(*lista, *total);

        printf("\nCadastrar mais compras? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');
}

void pesquisarCompra(Compra *lista, int total) {
    char nome[50];
    char repetir;
    int encontrou;
    int quantidade;
    float soma;

    do{
        encontrou = 0;
        soma = 0;
        quantidade = 0;

        printf("\nNome do cliente: ");
        scanf(" %[^\n]", nome);

        for (int i = 0; i < total; i++) {
            if (strcmp(lista[i].cliente.nome, nome) == 0) {
                printf("\nCompra %d\n", quantidade + 1);
                printf("Valor total: %.2f\n", lista[i].valor_total);
                printf("Franquia: %c\n", lista[i].franquia);
                printf("Quantidade de itens: %d\n", lista[i].num_itens);

                soma += lista[i].valor_total;
                quantidade++;
                encontrou = 1;
            }
        }

        if (encontrou){
            printf("Media das compras: %.2f\n", soma / quantidade);
        } else{
            printf("Cliente nao encontrado.\n");
        }

        printf("\npesquisar novamente? (s/n): ");
        scanf(" %c", &repetir);

    } while (repetir == 's' || repetir == 'S');
}

void relatorioCompras(Compra *lista, int total) {
    float valor;
    float total_mulheres = 0;
    float total_compras = 0;
    float media;
    float maior_homem = 0;
    int abaixo_valor = 0;
    int dois_itens = 0;
    int franquia_c = 0;
    int sem_sexo = 0;
    int total_itens = 0;
    int maior_nome = 0;
    int menor_idade = 6700; //SIX SEVENNNNNNN

    printf("mostrar compras abaixo de qual valor? ");
    scanf("%f", &valor);

    for (int i = 0; i < total; i++) {
        if (lista[i].valor_total < valor) {
            abaixo_valor++;
        }
        if (lista[i].num_itens == 2) {
            dois_itens++;
        }
        if (lista[i].franquia == 'C') {
            franquia_c++;
        }
        if (lista[i].cliente.sexo == 'n') {
            sem_sexo++;
        }
        if (lista[i].cliente.sexo == 'f') {
            total_mulheres += lista[i].valor_total;
        }
        
        total_itens += lista[i].num_itens;
        total_compras += lista[i].valor_total;

        if (lista[i].cliente.sexo == 'm' && lista[i].valor_total > maior_homem) {
            maior_homem = lista[i].valor_total;
        }
        if (strlen(lista[i].cliente.nome) > maior_nome) {
            maior_nome = strlen(lista[i].cliente.nome);
        }
        if (lista[i].cliente.idade < menor_idade) {
            menor_idade = lista[i].cliente.idade;
        }
    }

    media = total_compras / total;

    printf("\nCompras abaixo do valor: %d\n", abaixo_valor);
    printf("Compras com 2 itens: %d\n", dois_itens);
    printf("Compras franquia C: %d\n", franquia_c);
    printf("Sexo nao informado: %d\n", sem_sexo);
    printf("total comprado por mulheres: %.2f\n", total_mulheres);
    printf("Total de itens vendidos: %d\n", total_itens);
    printf("Valor total das compras: %.2f\n", total_compras);
    printf("Media das compras: %.2f\n", media);

    if (maior_homem >= 0) {
        printf("Maior compra feita por homem: %.2f\n", maior_homem);
    }

    printf("\nClientes com maior nome:\n");
    for (int i = 0; i < total; i++) {
        if (strlen(lista[i].cliente.nome) == maior_nome) {
            printf("\nNome: %s\n", lista[i].cliente.nome);
            printf("Sexo: %c\n", lista[i].cliente.sexo);
            printf("Idade: %d\n", lista[i].cliente.idade);
            printf("Itens: %d\n", lista[i].num_itens);
            printf("Franquia: %c\n", lista[i].franquia);
            printf("Valor: %.2f\n", lista[i].valor_total);
        }
    }

    printf("\nCliente mais novo:\n");
    for (int i = 0; i < total; i++) {
        if (lista[i].cliente.idade == menor_idade) {
            printf("\nNome: %s\n", lista[i].cliente.nome);
            printf("Sexo: %c\n", lista[i].cliente.sexo);
            printf("Idade: %d\n", lista[i].cliente.idade);
            printf("Itens: %d\n", lista[i].num_itens);
            printf("Franquia: %c\n", lista[i].franquia);
            printf("Valor: %.2f\n", lista[i].valor_total);
        }
    }
}
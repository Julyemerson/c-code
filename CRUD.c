#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 200
#define FILENAME "items.txt"

typedef struct {
    char cod[50];
    char name[50];
    char category[50];
    char quantity[20];
} Item;

// Prototipo da função para abrir arquivo, evita repetição de código
FILE *openFile(char *mode);

Item Items[MAX_ITEMS];
int numItems = 0;

void createItem() {
    if (numItems >= MAX_ITEMS) {  // Verifica se a lista de itens está cheia
        printf("A lista de items esta cheia.\n");
        return;
    }

    Item newItem;  // Declara uma nova variável do tipo Item para armazenar os dados do novo item

    printf("Digite (* p/ sair):\n");

    printf("Digite o codigo do item: ");
    scanf("%s", newItem.cod);

    fflush(stdin);

    if (strcmp(newItem.cod, "*") == 0) {
        return;
    }

    printf("Digite o nome do item: ");
    scanf("%s", newItem.name);

    fflush(stdin);

    if (strcmp(newItem.name, "*") == 0) {
        return;
    }

    printf("Digite a categoria do item: ");
    scanf("%s", newItem.category);

    fflush(stdin);

    if (strcmp(newItem.category, "*") == 0) {
        return;
    }

    printf("Digite a quantidade de item(s): ");
    scanf("%s", newItem.quantity);

    fflush(stdin);

    if (strcmp(newItem.quantity, "*") == 0) {
        return;
    }

    // Verifica se o item já existe na lista
    int itemIndex = -1;  // Declara e inicializa uma variável para armazenar o índice do item na lista, iniciando com -1

    for (int i = 0; i < numItems; i++) {  // Itera sobre os itens existentes na lista

        if (strcmp(Items[i].cod, newItem.cod) == 0) {  // Verifica se o código do item atual é igual ao código do novo item
            itemIndex = i;                             // Armazena o índice do item atual na variável itemIndex
            break;                                     // Sai do loop
        }
    }

    if (itemIndex == -1) {          // Verifica se o item não existe na lista (índice igual a -1)
        Items[numItems] = newItem;  // Adiciona o novo item na lista, na posição numItems
        numItems++;                 // Incrementa o contador de itens
        printf("Item criado com sucesso.\n");

        FILE *file = openFile("w");  // Abre o arquivo items.txt no modo de escrita ("w")

        for (int i = 0; i < numItems; i++) {                                                                                                         // Itera sobre os itens na lista
            fprintf(file, "Codigo: %s Nome: %s Categoria: %s Quantidade: %s\n", Items[i].cod, Items[i].name, Items[i].category, Items[i].quantity);  // Escreve as informações do item no arquivo
        }
        fclose(file);
        createItem();  // Chama recursivamente a função para permitir a criação de mais itens

    } else {                                         // Caso o item já exista na lista
        int num1 = atoi(Items[itemIndex].quantity);  // Converte a quantidade do item existente para um inteiro
        int num2 = atoi(newItem.quantity);           // Converte a quantidade do novo item para um inteiro
        int num3 = num1 + num2;                      // Soma as quantidades
        sprintf(newItem.quantity, "%d", num3);       // Converte o resultado de volta para uma string
        Items[itemIndex] = newItem;                  // Atualiza o item existente na lista com as informações
        printf("Item atualizado com sucesso.\n");

        FILE *file = openFile("w");

        for (int i = 0; i < numItems; i++) {                                                                                                         // Itera sobre os itens na lista
            fprintf(file, "Codigo: %s Nome: %s Categoria: %s Quantidade: %s\n", Items[i].cod, Items[i].name, Items[i].category, Items[i].quantity);  // Escreve as informações do item no arquivo
        }
        fclose(file);
        createItem();
    }
}

void readItems() {
    FILE *file = openFile("r");  // Abre o arquivo items.txt no modo de leitura ("r")

    int lineCount = 1;                                 // Declara e inicializa uma variável para contar as linhas do arquivo, começando em 1
    char line[200];                                    // Declara um array de caracteres para armazenar cada linha lida do arquivo
    while (fgets(line, sizeof(line), file) != NULL) {  // Lê cada linha do arquivo até o final
        printf("%s", line);
        lineCount++;
    }

    fclose(file);
}

void updateItem() {
    char searchCod[50];  // Declara um array de caracteres para armazenar o código de busca
    int itemIndex = -1;  // Declara e inicializa uma variável para armazenar o índice do item a ser atualizado, iniciando com -1

    if (numItems == 0) {  // Verifica se a lista de itens está vazia
        printf("A lista de items esta vazia.\n");
        return;
    }

    printf("Digite o codigo do item que deseja atualizar(* p/ sair): ");
    scanf("%s", searchCod);

    fflush(stdin);

    if (strcmp(searchCod, "*") == 0) {
        return;
    }

    for (int i = 0; i < numItems; i++) {  // Itera sobre os itens existentes na lista

        if (strcmp(Items[i].cod, searchCod) == 0) {  // Verifica se o código do item atual é igual ao código de busca
            itemIndex = i;                           // Armazena o índice do item atual na variável itemIndex
            break;                                   // Sai do loop
        }
    }

    if (itemIndex == -1) {  // Verifica se o item não foi encontrado (índice igual a -1)
        printf("Item nao encontrado, Digite novamente.\n");
        updateItem();  // Chama recursivamente a função para permitir nova tentativa de atualização

    } else {  // Caso o item tenha sido encontrado
        printf("Digite o nome do novo item: ");
        scanf("%s", Items[itemIndex].name);  // Solicita ao usuário o novo nome do item e armazena
        fflush(stdin);

        printf("Digite a categoria do novo item: ");
        scanf("%s", Items[itemIndex].category);
        fflush(stdin);
        printf("Digite a quantidade de novo(s) item(s): ");
        scanf("%s", Items[itemIndex].quantity);
        fflush(stdin);

        FILE *file = openFile("w");  // Abre o arquivo items.txt no modo de escrita ("w")

        for (int i = 0; i < numItems; i++) {                                                                                                         // Itera sobre os itens na lista                                                                                                     // Itera sobre os itens na lista
            fprintf(file, "Codigo: %s Nome: %s Categoria: %s Quantidade: %s\n", Items[i].cod, Items[i].name, Items[i].category, Items[i].quantity);  // Escreve as informações do item no arquivo
        }

        fclose(file);

        printf("Item atualizado com sucesso.\n");
        updateItem();  // Chama recursivamente a função para permitir a atualização de mais itens
    }
}

void deleteItem() {
    if (numItems == 0)  // Verifica se a lista de itens está vazia
    {
        printf("A lista de items esta vazia.\n");
        return;
    }

    char searchCod[50];  // Declara um array de caracteres para armazenar o código de busca
    printf("Digite o codigo do item que deseja excluir(* p/ sair): ");
    scanf("%s", searchCod);  // Solicita ao usuário o código do item a ser excluído e armazena em searchCod
    fflush(stdin);

    if (strcmp(searchCod, "*") == 0) {
        return;
    }

    int itemIndex = -1;                            // Declara e inicializa uma variável para armazenar o índice do item a ser excluído, iniciando com -1
    for (int i = 0; i < numItems; i++) {           // Itera sobre os itens existentes na lista
        if (strcmp(Items[i].cod, searchCod) == 0)  // Verifica se o código do item atual é igual ao código de busca
        {
            itemIndex = i;  // Armazena o índice do item atual na variável itemIndex
            break;          // Sai do loop
        }
    }

    if (itemIndex == -1) {  // Verifica se o item não foi encontrado (índice igual a -1)
        printf("Item nao encontrado.\n");
        deleteItem();  // Chama recursivamente a função para permitir nova tentativa de exclusão
    }

    for (int i = itemIndex; i < numItems - 1; i++) {  // Desloca os itens seguintes para preencher o espaço do item excluído
        Items[i] = Items[i + 1];
    }

    numItems--;  // Decrementa o número total de itens

    FILE *file = openFile("w");  // Abre o arquivo items.txt no modo de escrita ("w")

    for (int i = 0; i < numItems; i++)  // Itera sobre os itens na lista
    {
        fprintf(file, "Codigo: %s Nome: %s Categoria: %s Quantidade: %s\n", Items[i].cod, Items[i].name, Items[i].category, Items[i].quantity);  // Escreve as informações do item no arquivo
    }

    fclose(file);
    printf("Item excluido com sucesso.\n");
    deleteItem();  // Chama recursivamente a função para permitir a exclusão de mais itens
}

void queryItem() {
    if (numItems == 0) {  // Verifica se a lista de itens está vazia
        printf("A lista de items esta vazia.\n");
        return;
    }

    char searchCod[50];
    printf("Digite o codigo do item que deseja consultar(* p/ sair): ");
    scanf("%s", searchCod);
    fflush(stdin);

    if (strcmp(searchCod, "*") == 0) {
        return;
    }

    int itemIndex = -1;
    for (int i = 0; i < numItems; i++)  // Itera sobre os itens existentes na lista
    {
        if (strcmp(Items[i].cod, searchCod) == 0) {  // Verifica se o código do item atual é igual ao código de busca
            itemIndex = i;                           // Armazena o índice do item atual na variável itemIndex
            break;
        }
    }

    if (itemIndex == -1) {
        printf("Item nao encontrado.\n");
        queryItem();  // Chama recursivamente a função para permitir nova tentativa de consulta
    }

    printf("Codigo: %s Nome: %s Categoria: %s Quantidade: %s\n", Items[itemIndex].cod, Items[itemIndex].name, Items[itemIndex].category, Items[itemIndex].quantity);  // Exibe as informações do item consultado
}

FILE *openFile(char *mode) {
    FILE *file = fopen(FILENAME, mode);
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    return file;
}

void menu() {
    printf("\n");
    printf("Selecione uma opcao:\n");
    printf("[ 1 ] Criar um item\n");
    printf("[ 2 ] Listar items\n");
    printf("[ 3 ] Atualizar um item\n");
    printf("[ 4 ] Excluir um item\n");
    printf("[ 5 ] Consultar item\n");
    printf("[ 0 ] Sair\n");
}
void switchMenu(int choice) {
    switch (choice) {
        case 0:
            printf("Saindo...\n");
            exit(0);
        case 1:
            createItem();
            break;
        case 2:
            readItems();
            break;
        case 3:
            updateItem();
            break;
        case 4:
            deleteItem();
            break;
        case 5:
            queryItem();
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
    }
}

int main() {
    int choice;

    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        Item item;
        char line[200];
        while (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "Codigo: %s Nome: %s Categoria: %s Quantidade: %s\n", item.cod, item.name, item.category, item.quantity);
            Items[numItems] = item;
            numItems++;
        }
        fclose(file);
    }

    while (1) {
        menu();
        scanf("%d", &choice);
        switchMenu(choice);
    }

    return 0;
}

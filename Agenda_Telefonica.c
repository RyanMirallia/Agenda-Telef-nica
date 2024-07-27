#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char nome_usuario[100];
int escolha_usuario;
int escolha_lista_usuario;
int count = 0;

void limpar_tela();
void tela_inicial();
void cadastrar_contato();
void menu();
int contador();
void consultar_contato();
void editar_contato();
void remover_contato();
void carregando();
void atualizar_lista();
void ligar_contato();


typedef struct {
    char nome_complt_contato[100];
    char numero_telefone[50];
    char endereco[100];
    char email[100];
    char estado[50];
    char cep[50];
} contato;

contato info[100];

int main() {
    tela_inicial();
    
    return 0;
}

void atualizar_lista() {
    FILE *ptr_arquivo;

    ptr_arquivo = fopen("lista.txt", "w+");
    if (ptr_arquivo == NULL) {
        printf("falha ao abrir o arquivo");
        return;
    }
  
    for (int i = 0; i < count; i++) {
        fprintf(ptr_arquivo, "Nome: %s\nNumero: %s\nEndereco: %s\nEmail: %s\nEstado: %s\nCEP: %s\n\n",
                info[i].nome_complt_contato,
                info[i].numero_telefone,
                info[i].endereco,
                info[i].email,
                info[i].estado,
                info[i].cep);
    }

    fclose(ptr_arquivo);
    menu();
}

int contador() {
    return ++count;
}



void menu() {
    printf("============================================\n");
    printf("|                  MENU                    |\n");
    printf("============================================\n");
    printf("| 1 - Cadastrar novo contato               |\n");
    printf("| 2 - Consultar informacoes dos contatos   |\n");
    printf("| 3 - Editar informacoes de algum contato  |\n");
    printf("| 4 - Remover contato                      |\n");
    printf("| 5 - Ligar para alguem                    |\n");
    printf("| 0 - Sair do programa                     |\n");
    printf("============================================\n");
    printf("O que deseja? Digite o numero correspondente a funcao: ");

    scanf("%d", &escolha_usuario);
    getchar();

    switch (escolha_usuario) {
        case 0:
            limpar_tela();
            printf("Encerrando Programa");
            sleep(1);
            for (int i = 0; i < 3; i++) {
                printf(".");
                sleep(1);
            }
            printf("\n");
            printf("Ate a proxima, %s!", nome_usuario);
            exit(0);
        case 1:
            limpar_tela();
            cadastrar_contato();
            
            break;
        case 2:
            limpar_tela();
            consultar_contato();
            break;
        case 3:
            limpar_tela();
            editar_contato();
            
            break;
        case 4:
            limpar_tela();
            remover_contato();
            break;
        case 5:
            limpar_tela();
            ligar_contato();
            break;
        default:
            limpar_tela();
            printf("\033[1;31mopcao invalida tente novamente em 3 segundos\033[0m\n");
            sleep(3);
            limpar_tela();
            menu();
            break;
    }
}

void remover_contato(){
    char nome[100];
    printf("digite o nome do contato que deseja remover: ");
    fgets(nome, 100, stdin);
    strtok(nome, "\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(info[i].nome_complt_contato, nome) == 0) {
            for (int j = i; j < count - 1; j++) {
                info[j] = info[j + 1];
            }
            count--; 
            limpar_tela();
            printf("\033[1;32mContato removido com sucesso.\033[0m\n");
            printf("Pressione enter para continuar...");
            getchar();
            limpar_tela();
            atualizar_lista();
            exit(0);
        }
        
    }
    printf("\033[1;31mNenhum contato encontrado!!!\033[0m\n");
    printf("Pressione enter para continuar...");
    getchar();
    limpar_tela();
    menu();
}

void cadastrar_contato() {
    if (count >= 100) {
        printf("\033[1;31mLimite de contatos atingido!\033[0m\n");
        return;
    }

    contador();

    printf("Digite o nome completo do contato: ");
    fgets(info[count - 1].nome_complt_contato, 100, stdin);
    strtok(info[count - 1].nome_complt_contato, "\n");

    printf("Digite o numero de telefone: ");
    fgets(info[count - 1].numero_telefone, 50, stdin);
    strtok(info[count - 1].numero_telefone, "\n");

    printf("Digite o endereco: ");
    fgets(info[count - 1].endereco, 100, stdin);
    strtok(info[count - 1].endereco, "\n");

    printf("Digite o email: ");
    fgets(info[count - 1].email, 100, stdin);
    strtok(info[count - 1].email, "\n");

    printf("Digite o CEP: ");
    fgets(info[count - 1].cep, 50, stdin);
    strtok(info[count - 1].cep, "\n");

    printf("Digite o estado: ");
    fgets(info[count - 1].estado, 50, stdin);
    strtok(info[count - 1].estado, "\n");

    printf("\033[1;32mContato cadastrado com sucesso!\033[0m\n");
            printf("Pressione enter para continuar...");
            getchar();
            limpar_tela();
            atualizar_lista();
}

void consultar_contato() {
    char nome[100];
    printf("Digite o nome do contato que deseja consultar: ");
    fgets(nome, 100, stdin);
    strtok(nome, "\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(info[i].nome_complt_contato, nome) == 0) {
            printf("Informacoes do contato:\n");
            printf("Nome: %s\n", info[i].nome_complt_contato);
            printf("Numero: %s\n", info[i].numero_telefone);
            printf("Endereco: %s\n", info[i].endereco);
            printf("Email: %s\n", info[i].email);
            printf("CEP: %s\n", info[i].cep);
            printf("Estado: %s\n", info[i].estado);
            printf("\n");
            printf("Pressione enter para continuar...");
            getchar();
            limpar_tela();
            menu();
            return;
        }
    }

    printf("\033[1;31mContato nao encontrado\033[0m\n");
    printf("Pressione enter para continuar...");
    getchar();
    limpar_tela();
    menu();
}

void ligar_contato(){
    printf("Para quem deseja ligar?\n");
    char contato_ligar[100];
    fgets(contato_ligar, 100, stdin);
    strtok(contato_ligar, "\n");
    limpar_tela();

    for(int i = 0; i < count; i++){
        if(strcmp(info[i].nome_complt_contato, contato_ligar) == 0){
            printf("\033[1;32mLigando para %s\033[0m", info[i].nome_complt_contato);
            sleep(1);
            for(int j = 0; j < 3; j++){
                printf("\033[1;32m.\033[0m");
                sleep(1);
            }
            limpar_tela();
            printf("\033[1;31m%s nao atendeu\033[0m\n", info[i].nome_complt_contato);
            printf("Pressione enter para continuar...");
            getchar();
            limpar_tela();
            menu();
            return;
        }
    }
    printf("\033[1;31mContato nao encontrado\033[0m\n");
    printf("Pressione enter para continuar...");
    getchar();
    limpar_tela();
    menu();
}

void editar_contato() {
    char nome[100];
    printf("Digite o nome do contato que deseja editar: ");
    fgets(nome, 100, stdin);
    strtok(nome, "\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(info[i].nome_complt_contato, nome) == 0) {
            printf("Digite o novo numero de telefone: ");
            fgets(info[i].numero_telefone, 50, stdin);
            strtok(info[i].numero_telefone, "\n");

            printf("Digite o novo endereco: ");
            fgets(info[i].endereco, 100, stdin);
            strtok(info[i].endereco, "\n");

            printf("Digite o novo email: ");
            fgets(info[i].email, 100, stdin);
            strtok(info[i].email, "\n");

            printf("Digite o novo CEP: ");
            fgets(info[i].cep, 50, stdin);
            strtok(info[i].cep, "\n");

            printf("Digite o novo estado: ");
            fgets(info[i].estado, 50, stdin);
            strtok(info[i].estado, "\n");

            limpar_tela();

            printf("\033[1;32mContato atualizado!\033[0m\n");
            printf("Pressione enter para continuar...");
            getchar();
            limpar_tela();
            atualizar_lista();
            
            return;
        }
    }

    printf("\033[1;31mContato nao encontrado.\033[0m\n");
    printf("Pressione enter para continuar...");
    getchar();
    limpar_tela();
    menu();
}


void tela_inicial() {
    printf("Digite seu nome: ");
    fgets(nome_usuario, 100, stdin);
    strtok(nome_usuario, "\n");

    carregando();
    limpar_tela(); 

    printf("\033[36mBem-vindo(a) a sua agenda telefonica, %s\033[0m\n", nome_usuario);

    menu();
}

void limpar_tela() {
    printf("\033[H\033[J");
}

void carregando() {
    limpar_tela();
    printf("Carregando");
    sleep(1);
    for (int i = 0; i < 3; i++) {
        printf(".");
        sleep(1);
    }
    printf("\n");
}

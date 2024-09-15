#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    int codigo;
    char nome[50];
    char email[50];
    char cpf[20];
    char dataNascimento[20];
    char dataCadastro[20];
} Client;

typedef struct{
    int numero;
    Client client;
    float saldo;
    float limite;
    float saldoTotal; //saldo + limite
} Conta;


void criarConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
float atualizarSaldoTotal(Conta conta);
void listarContas();
void menu();
Conta buscarContaPorNumero(int num);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);


static int contador_conta = 0;
static int contador_cliente = 0;

static Conta conta[50];

void imprimirConta(Conta conta){
    printf("=============================\n");
    printf("Dados da conta adicionada: \n");
    printf("=============================\n");
    printf("Numero da conta: %d\nCliente: %s\nData Nascimento: %s\nData Cadastro: %s\nSaldoTotal: %.2f\n",
    conta.numero, strtok(conta.client.nome, "\n"), strtok(conta.client.dataNascimento, "\n"),
    strtok(conta.client.dataCadastro, "\n"), conta.saldoTotal);
}

int main(){

    menu();
    return 0;

}

void menu(){
    printf("\n===============================\n");
    printf("--------------ATM--------------\n");
    printf("-----------GEEK BANK-----------\n");
    printf("===============================\n");

    printf("Selecione uma opção do menu: \n");
    printf("1 - Criar conta\n");
    printf("2 - Efetuar saque\n");
    printf("3 - Efetuar deposito\n");
    printf("4 - Efetuar transferencia\n");
    printf("5 - Listar contas\n");
    printf("6 - Sair programa\n");
    int opc;
    scanf("%d", &opc);
    getchar();

    switch(opc){
        case 1:
            criarConta();
            break;
        case 2:
            efetuarSaque();
            break;
        case 3:
            efetuarDeposito();
            break;
        case 4:
            efetuarTransferencia();
            break;
        case 5:
            listarContas();
            break;
        case 6:
            printf("Encerrando programa...\n");
            sleep(1.5);
            printf("Programa encerrado!\n");
            exit(0);
        default:
            printf("Opcão invalida\n");
            menu();
            break;
    }

}

void criarConta(){

    Client cliente;

    printf("\n===================\n");
    printf("Criando conta: \n");
    printf("===================\n");
    printf("Informe os dados do client: \n");

    printf("Nome:  ");
    fgets(cliente.nome, 50, stdin);

    printf("Email do cliente: ");
    fgets(cliente.email, 50, stdin);

    printf("Cpf: ");
    fgets(cliente.cpf, 20, stdin);

    printf("Data de nascimento do cliente: ");
    fgets(cliente.dataNascimento, 20, stdin);

    printf("Data de cadastro: ");
    fgets(cliente.dataCadastro, 20, stdin);

    conta[contador_conta].client = cliente;
    conta[contador_conta].numero = contador_conta + 1;
    conta[contador_conta].saldo = 400.0;
    conta[contador_conta].limite = 100.0;
    conta[contador_conta].saldoTotal = atualizarSaldoTotal(conta[contador_conta]);
    printf("Adicionando conta...\n");
    sleep(1.5);
    imprimirConta(conta[contador_conta]);
    contador_conta ++;
    sleep(2);
    menu();
}

float atualizarSaldoTotal(Conta conta){
    return conta.saldo + conta.limite;
}

void sacar(Conta count, float valor){
    if(valor > 0 && count.saldoTotal >= valor){
        for(int i = 0; i < contador_conta; i++){
            if(conta[i].numero == count.numero){
                if(conta[i].saldo >= valor){
                    conta[i].saldo = conta[i].saldo - valor;
                    conta[i].saldoTotal = atualizarSaldoTotal(conta[i]);
                    printf("\n===========================\n");
                    printf("SAQUE REALIZADO COM SUCESSO\n");
                    printf("\n===========================\n");
                    imprimirConta(conta[i]);
                }
                else{
                    printf("Valor de saque excede os limites...\n");
                    sleep(2);
                    menu();
                }
            }
        }
    }

}

void efetuarSaque(){

    if(contador_conta > 0){
        printf("Digite o número da conta: ");
        int numConta;
        scanf("%d%*c", &numConta);
        Conta conta = buscarContaPorNumero(numConta);

        if(conta.numero == numConta){
            printf("Digite o valor a sacar: ");
            float valorSacar;
            scanf("%f", &valorSacar);

            sacar(conta, valorSacar);
            sleep(1.5);
            menu();
        }
        else{
            printf("Nao foi encontrada uma conta com o numero %d\n", numConta);
            sleep(2);
            menu();
        }

    }
    else{
        printf("Ainda nao existe contas para sacar...\n");
        sleep(1.5);
        menu();
    }

}

Conta buscarContaPorNumero(int num){
    Conta c;
    if(contador_conta > 0){
        for(int i = 0; i < contador_conta; i++){
            if(conta[i].numero == num){
                c = conta[i];
            }
        }
    }
    return c;
}

void deposito(Conta count, float valor){

    if(valor > 0){
        for(int i = 0; i < contador_conta; i++){
            if(conta[i].numero == count.numero){
                conta[i].saldo += valor;
                conta[i].saldoTotal = atualizarSaldoTotal(conta[i]);
                printf("Deposito realizado...\n");
                sleep(1.4);
                menu();
            }
        }
    }
    else{
        printf("Saque não realizado, tente novamente...\n");
        sleep(1.4);
        menu();
    }

}

void efetuarDeposito(){

    if(contador_conta > 0){
        printf("Digite o numero da conta: ");
        int numConta;
        scanf("%d%*c", &numConta);
        Conta contaBusca = buscarContaPorNumero(numConta);
        if(contaBusca.numero == numConta){
            float valor;
            printf("Digite o valor: ");
            scanf("%f%*c", &valor);

            deposito(contaBusca, valor);
            sleep(1.5);
            menu();
        }
        printf("Nao foi possivel encontrar a conta...\n");
        sleep(1.5);
        menu();
    }
    else{
        printf("Ainda nao existe contas criadas...\n");
        sleep(1.5);
        menu();
    }

}

void transferencia(Conta conta_origem, Conta conta_destino, float valor){
    if(valor > 0 && conta_origem.saldoTotal >= valor){
        for(int i = 0; i < contador_conta; i++){
            if(conta_origem.numero == conta[i].numero){
                for(int j = 0; j < contador_conta; j++){
                    if(conta_destino.numero == conta[j].numero){
                        if(conta[i].saldo >= valor){
                            conta[i].saldo -= valor;
                            conta[j].saldo += valor;
                            conta[i].saldoTotal = atualizarSaldoTotal(conta[i]);
                            conta[j].saldoTotal = atualizarSaldoTotal(conta[j]);
                            printf("Transferencia realizada com sucesso!\n");
                            sleep(2);
                        }
                        else{
                            float restante = conta[i].saldo - valor;
                            conta[i].limite = conta[i].limite + restante;
                            conta[i].saldo = 0.0;
                            conta[j].saldo += valor;
                            conta[i].saldoTotal = atualizarSaldoTotal(conta[i]);
                            conta[j].saldoTotal = atualizarSaldoTotal(conta[j]);
                            printf("Transferencia realizada com sucesso!\n");
                            sleep(2);
                        }
                    }
                }
            }
        }
    }
    else{
        printf("Transferencia não realizada, tente novamente...\n");
        sleep(2);
    }
}

void efetuarTransferencia(){

    if(contador_conta > 0){
        printf("Qual a conta de origem? ");
        int numConta1;
        scanf("%d%*c", &numConta1);
        Conta conta_original = buscarContaPorNumero(numConta1);

        if(conta_original.numero == numConta1){
            printf("Qual a conta de desitono? ");
            int numConta2;
            scanf("%d%*c", &numConta2);
            Conta conta_destino = buscarContaPorNumero(numConta2);

            if(conta_destino.numero == numConta2){
                float valor;
                printf("Insira o valor da transferencia: ");
                scanf("%f", &valor);
                transferencia(conta_original, conta_destino, valor);
                sleep(1.4);
                menu();
            }
            else{
                printf("A conta destino nao tem esse numero\n");
                sleep(1.5);
                menu();
            }

        }
        printf("A conta original nao tem esse numero\n");
        sleep(1.5);
        menu();
    }
    else{
        printf("Nao ah contas para realizar transferencia\n");
        sleep(1.5);
        menu();
    }

}
void listarContas(){

    if(contador_conta > 0){
        printf("============LISTA DE CONTAS============\n");
        for(int i = 0; i < contador_conta; i++){
            imprimirConta(conta[i]);
        }
    }
    else{
        printf("Nao existe contas cadastradas\n");
    }
    sleep(2);
    menu();

}
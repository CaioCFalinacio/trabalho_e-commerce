#include <iostream>

using namespace std;

int main(){

    int opcao;

do{
    cout << "MENU - COMERCIO ELETRONICO \n";
    cout << "1- Cadastrar Produto; \n";
    cout << "2- Cadastrar Vendedor; \n";
    cout << "3- Cadastrar Comprador; \n";
    cout << "4- Cadastrar Venda; \n";
    cout << "5- Emissao de Nota Fiscal; \n";
    cout << "0 - Sair \n";

    cout << "\n \n";

    cout << "Digite a sua escolha: ";
    cin >> opcao;

    switch (opcao){
        case 1:
        //função de cadastro de produto
        //cadastro_produtos();
        break;
        case 2:
        //função de cadastro de vendedor (função que vai abrir um menu para os vendedores);
        //menu_vendedores(); //função para o menu de cadastro dos vendedores.
        break;
        case 3:
        //função de cadastro de comprador
        break;
        case 4:
        //função de cadastro de vendas
        break;
        case 5:
        //função de emissão de nota fiscal
        break;
        case 0:
        cout << "Fim de execucao!";
        return 0;
        break;
        default:
            cout << "Opcao invalida! \n";
    };        }while(opcao != 0);

    return 0;
}

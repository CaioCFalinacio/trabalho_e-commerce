#include <iostream>
#include <locale.h>

int main(){

    int opcao;

    std::cout << "MENU - COMERCIO ELETRONICO \n";
    std::cout << "1- Cadastrar Produto; \n";
    std::cout << "2- Cadastrar Vendedor; \n";
    std::cout << "3- Cadastrar Comprador; \n";
    std::cout << "4- Cadastrar Venda; \n";
    std::cout << "5- Emissao de Nota Fiscal; \n";

    std::cout << "\n \n";

    
    std::cout << "Digite a opcao correspondente a sua escolha: ";
    std::cin >> opcao;

    switch (opcao){
        case 1:
        //função de cadastro de produto
        break;
        case 2: 
        //função de cadastro de vendedor
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
        default:
        do{
            std::cout << "\n";
            std::cout << "Opcao invalida! Repita. \n";
            std::cout << "\nDigite a opcao correspondente a sua escolha:  ";
            std::cin >> opcao;
         }while (opcao < 1 || opcao > 5);
    }
    


    



    return 0;
}
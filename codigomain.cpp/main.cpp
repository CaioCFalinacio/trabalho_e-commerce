/*

DEMONSTRAÇÃO DE COMO O MAIN DO E-COMMERCE SERÁ.

*/






#include <iostream>

using namespace std;

// Função principal do programa
int main() {
    int opcao;
    do {
        // Exibe o menu principal do sistema
        cout << "====== MENU - COMERCIO ELETRONICO ======\n";
        cout << "1- Gerenciar Produtos\n";
        cout << "2- Gerenciar Vendedores (Nao implementado)\n";
        cout << "3- Gerenciar Compradores (Nao implementado)\n";
        cout << "4- Realizar Venda (Nao implementado)\n";
        cout << "5- Emitir Nota Fiscal (Nao implementado)\n";
        cout << "0- Sair\n";
        cout << "========================================\n";
        cout << "Digite a sua escolha: ";
        cin >> opcao;

        // Validação da entrada da opção
        if (cin.fail()) {
            cout << "\nERRO: Por favor, digite apenas numeros.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
        }

        cout << "\n";

        // Executa a opção escolhida pelo usuário
        switch (opcao) {
            case 1:
                menu_produtos();  
                break;
            case 2:
                menu_vendedores();
                ; 
                break;
            case 3:
                cadastro_global_compradores.menuCompradores()
                break;
            case 4:
                menu_vendas();
                break;
            case 5:
                 menu_notaFiscal();
                break;
            case 0:
                cout << "Fim de execucao do programa.\n"; // Encerra o programa
                break;
            default:
                cout << "Opcao invalida! Tente novamente.\n\n"; // Opção inválida
        }
    } while (opcao != 0);

    return 0; // Fim do programa
}
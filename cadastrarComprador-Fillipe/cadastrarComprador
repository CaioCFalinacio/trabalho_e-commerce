#include <iostream>
#include <vector>
#include <string>
using namespace std;

// classe do endereço
class Endereco {
public:
    string rua;
    string bairro;
    string cidade;
    string estado;
    string cep;

    void lerEndereco() {
        cout << "rua: ";
        getline(cin, rua);
        cout << "bairro: ";
        getline(cin, bairro);
        cout << "cidade: ";
        getline(cin, cidade);
        cout << "estado: ";
        getline(cin, estado);
        cout << "CEP: ";
        getline(cin, cep);
    }

    void mostrarEndereco() const {
        cout << rua << ", " << bairro << ", " << cidade << ", " << estado << ", CEP: " << cep;
    }
};

// classe do comprador
class Comprador {
private:
    string nome;
    string cpf;
    string email;
    Endereco endereco;

public:
    // getter
    string getCpf() const {
        return cpf;
    }

    // cadastrar dados do comprador
    void cadastrar() {
        cout << "\n CADASTRO DE COMPRADOR \n";
        cout << "nome: ";
        getline(cin, nome);
        cout << "CPF: ";
        getline(cin, cpf);
        cout << "email: ";
        getline(cin, email);
        cout << "\n ENDEREÇO \n";
        endereco.lerEndereco();
    }

    // mostrar dados do comprador
    void mostrar() const {
        cout << "nome: " << nome << endl;
        cout << "CPF: " << cpf << endl;
        cout << "email: " << email << endl;
        cout << "endereco: ";
        endereco.mostrarEndereco();
        cout << endl;
    }

    // alterar dados do comprador
    void alterar() {
        cout << "\n ALTERAR DADOS \n";
        cout << "novo nome: ";
        getline(cin, nome);
        cout << "novo email: ";
        getline(cin, email);
        cout << "\n NOVO ENDEREÇO \n";
        endereco.lerEndereco();
        cout << "comprador alterado com sucesso\n";
    }
};

// classe cadastro de compradores
class CadastroCompradores {
private:
    vector<Comprador> lista;

public:
    void cadastrarComprador() {
        Comprador novo;
        novo.cadastrar();
        lista.push_back(novo);
        cout << "comprador cadastrado com sucesso\n";
    }

    void consultarCompradores() const {
        cout << "\n LISTA DE COMPRADORES \n";
        if (lista.empty()) {
            cout << "nenhum comprador cadastrado.\n";
            return;
        }
        for (size_t i = 0; i < lista.size(); i++) {
            cout << "\ncomprador " << i + 1 << ":" << endl;
            lista[i].mostrar();
        }
    }

    void alterarComprador() {
        string cpfBusca;
        cout << "\ndigite o CPF do comprador que deseja alterar: ";
        getline(cin, cpfBusca);

        for (Comprador& c : lista) {
            if (c.getCpf() == cpfBusca) {
                c.alterar();
                return;
            }
        }
        cout << "CPF nao encontrado\n";
    }

    void excluirComprador() {
        string cpfBusca;
        cout << "\ndigite o CPF do comprador que deseja excluir: ";
        getline(cin, cpfBusca);

        for (size_t i = 0; i < lista.size(); i++) {
            if (lista[i].getCpf() == cpfBusca) {
                lista.erase(lista.begin() + i);
                cout << "comprador excluido com sucesso\n";
                return;
            }
        }
        cout << "CPF nao encontrado\n";
    }

    void menuCompradores() {
        int opcao;
        do {
            cout << "\n====== MENU COMPRADORES ======" << endl;
            cout << "1 - Cadastrar Comprador" << endl;
            cout << "2 - Consultar Compradores" << endl;
            cout << "3 - Alterar Comprador" << endl;
            cout << "4 - Excluir Comprador" << endl;
            cout << "0 - Sair" << endl;
            cout << "Escolha uma opcao: ";
            cin >> opcao;
            cin.ignore();

            switch (opcao) {
                case 1: cadastrarComprador(); break;
                case 2: consultarCompradores(); break;
                case 3: alterarComprador(); break;
                case 4: excluirComprador(); break;
                case 0: cout << "Saindo do menu de compradores...\n"; break;
                default: cout << "Opcao invalida!\n"; break;
            }
        } while (opcao != 0);
    }
};

int main() {
    //para testes
    CadastroCompradores cadastro; 
    cadastro.menuCompradores();   

    return 0;
}

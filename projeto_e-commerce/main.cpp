#include <iostream>
#include <stdio.h>

using namespace std;

// Classe que representa um vendedor
class Vendedor{
private:
    string nome_vendedor; // Nome do vendedor
    int id_vendedor; // ID único do vendedor
    double salario_fixo; // Salário fixo do vendedor
    double total_comissoes = 0; // Total de comissões acumuladas
    static int proximo_id; // Próximo ID disponível (auto-incremento)
public:
    static constexpr float taxa_comissao = 0.03; // Taxa de comissão fixa
    Vendedor(){}
    // Construtor que inicializa nome, salário e ID
    Vendedor(string nome_vendedor, double salario_fixo){
    set_nome_vendedor(nome_vendedor);
    set_salario_fixo(salario_fixo);
    set_id_vendedor();
    }

    // Métodos de acesso (getters)
    string get_nome_vendedor(){ return nome_vendedor; }
    int get_id_vendedor(){ return id_vendedor; }
    double get_salario_fixo(){ return salario_fixo; }
    double get_salario_total(){ return (salario_fixo + total_comissoes); }

    // Métodos de modificação (setters) e ações
    void set_nome_vendedor(string novo_nome);
    void set_salario_fixo(double novo_salario);
    void set_id_vendedor();
    void consultar_vendedor();
    void registrar_venda(double valor_venda);
};

// Inicialização do membro estático
int Vendedor::proximo_id = 1;

// Define o nome do vendedor
void Vendedor::set_nome_vendedor(string novo_nome){
nome_vendedor = novo_nome;
}
// Define o salário fixo do vendedor
void Vendedor::set_salario_fixo(double novo_salario){
salario_fixo = novo_salario;
}
// Define o ID do vendedor e incrementa o próximo ID
void Vendedor::set_id_vendedor(){
id_vendedor = proximo_id++;
}
// Registra uma venda e adiciona a comissão ao total
void Vendedor::registrar_venda(double valor_venda){
    total_comissoes += valor_venda * taxa_comissao;
}
// Exibe as informações do vendedor
void Vendedor::consultar_vendedor(){
    cout<<"Nome do vendedor: "<<nome_vendedor<<endl;
    cout<<"ID: "<<id_vendedor<<endl;
    cout<<"Salario fixo: R$"<<salario_fixo<<endl;
    cout<<"Comissoes acumuladas: R$"<<total_comissoes<<endl;
    cout<<"Salario total: R$"<<get_salario_total()<<endl;
}

// Busca o índice de um vendedor pelo ID
int buscar_vendedor(Vendedor vendedores[], int total_vendedores, int id){
for(int i = 0;i < total_vendedores; i++){
  if(vendedores[i].get_id_vendedor() == id)
        return i;
}
return -1;
}

// Menu principal para operações com vendedores
void menu_vendedores(){
    Vendedor vendedores[100]; // Vetor de vendedores
    int opcao;
    int total_vendedores = 0;
do{
cout << "O que voce deseja fazer?" << endl;
cout << "1. Cadastrar vendedor" << endl;
cout << "2. Listar todos os vendedores" << endl;
cout << "3. Exibir vendedor por ID" << endl;
cout << "4. Registrar venda" << endl;
cout << "5. Editar informacoes" << endl;
cout << "6. Excluir vendedor" << endl;
cout << "0. Sair" << endl;
cout << "Escolha uma opcao: " << endl;
cin >> opcao;

switch(opcao){
case 1:
    // Cadastro de novo vendedor
    string nome;
    double salario;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Salario fixo: ";
    cin >> salario;
    vendedores[total_vendedores++] = Vendedor(nome, salario);
    cout << "Cadastro realizado com sucesso!" << endl;
    break;
case 2:
    // Listar todos os vendedores
    for(int i = 0; i < total_vendedores; i++){
        vendedores[i].consultar_vendedor();
    }
    break;
case 3:
    // Consultar vendedor por ID
    int id;
    cout << "Qual o ID do vendedor que deseja consultar?" << endl;
    cin >> id;
    int idx = buscar_vendedor(vendedores, total_vendedores, id);
    if(idx != -1){
    vendedores[idx].consultar_vendedor();
    }else{
    cout << "Vendedor nao encontrado!" << endl;
    }
    break;
case 4:
    // Registrar venda para um vendedor
    int id;
    double valor_venda;
    cout << "Digite o ID de quem realizou a venda: ";
    cin >> id;
    int idx = buscar_vendedor(vendedores, total_vendedores, id);
    if(idx != -1){
    cout << "Valor da venda: R$";
    cin >> valor_venda;
    vendedores[idx].registrar_venda(valor_venda);
    cout << "Venda registrada com sucesso!" << endl;
    }else{
    cout << "Nao ha esse vendedor!" << endl;
    }
    break;
case 5:
    // Editar informações de um vendedor
    int id;
    double novo_salario;
    string novo_nome;
    cout << "ID do vendedor: ";
    cin >> id;
    int idx = buscar_vendedor(vendedores, total_vendedores, id);
    if(idx != -1){
        cout << "Novo nome: ";
        cin.ignore();
        getline(cin, novo_nome);
        cout << "Novo salario: ";
        cin >> novo_salario;
        vendedores[idx].set_nome_vendedor(novo_nome);
        vendedores[idx].set_salario_fixo(novo_salario);
    } else {
        cout << "Vendedor nao encontrado!" << endl;
    }
    break;
case 6:
    // Excluir vendedor do sistema
    int id;
    cout << "Digite o ID de quem deseja excluir: ";
    cin >> id;
    int idx = buscar_vendedor(vendedores, total_vendedores, id);
    if(idx != -1){
        for(int i = idx; i < total-1; i++){
            vendedores[i] = vendedores[i+1];
        }
        total--;
        cout<<"Vendedor excluido com sucesso!" << endl;
    }else{
    cout << "Vendedor nao encontrado!" << endl;
    }
    break;
case 0:
    // Sair do programa
    cout << "Encerrando o programa." << endl;
    break;
default:
    cout << "Opcao invalida!" << endl;
}
}while(opcao != 0);
}

int main()
{
    
    return 0;
}

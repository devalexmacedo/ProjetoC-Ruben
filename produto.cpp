#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void exibirMenu() {
    int opcao;
    //menu com as opções de compra e adição do estoque
    do {
        cout << "------MENU PRINCIPAL ------" << endl;
        cout << "1. Efetuar Venda" << endl;
        cout << "2. Criar Artigo Novo" << endl;
        cout << "3. Eliminar Produto" << endl;
        cout << "4. Mostrar Stock" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                // chamar função de venda aqui
                break;
            case 2:
                // chamar função de criação
                break;
            case 3:
                // chamar função de eliminação
                break;
            case 4:
                // mostrar stock
                break;
            case 5:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }

        cout << endl;

    } while (opcao != 5);
}

// Estrutura do produto
struct Produto {
    int id;
    string nome;
    int quantidade;
    float precoCusto;
};

int main () {
    exibirMenu();
}

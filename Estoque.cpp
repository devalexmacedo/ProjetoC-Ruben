#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <locale.h> // Para permitir caracteres especiais
#include <conio.h> // Adicionado para usar o comando _getch, que interrompe limpezas de tela for de hora esperando um input do user
#include <vector>


using namespace std;


//Estrutura do produto.
struct Produto {
    int id;
    string nome;
    int quantidade;
    float precoCusto;
};

//função que diz ao cout como mostrar item por item.
ostream& operator<<(ostream& os, const Produto& p) {
    os << "ID: " << p.id << " | "
        << "Nome: " << p.nome << " | "
        << "Quantidade: " << p.quantidade << " | "
        << "Preco: " << p.precoCusto << endl;
    return os;
}

//Insere produtos no estoque.
vector<Produto> estoque = {
    {1, "Placa", 20, 85.00},
    {2, "Processador Ryzen 5 5600X", 20, 140.00},
    {3, "Memoria RAM 16GB DDR4", 20, 35.00},
    {4, "Disco SSD 1TB NVMe", 20, 55.00},
    {5, "Fonte 650W 80+ Bronze", 20, 45.00},
    {6, "Placa Grafica RTX 3060", 20, 260.00},
    {7, "Caixa Mid Tower", 20, 40.00},
    {8, "Cooler CPU ARGB", 20, 25.00},
    {9, "Monitor 24'' Full HD", 20, 90.00},
    {10, "Teclado Mecânico RGB", 20, 30.00},
    {11, "Rato Gaming 7200 DPI", 20, 15.00},
    {12, "Hub USB 3.0", 20, 10.00},
    {13, "Adaptador Wi-Fi USB", 20, 12.00},
    {14, "Pasta Térmica", 20, 3.00},
    {15, "Cabo HDMI 2.0", 20, 4.00},
    {16, "Ventoinha 120mm", 20, 5.00},
    {17, "Kit Chave Torx PC", 20, 6.00},
    {18, "Extensão de Energia", 20, 7.00},
    {19, "Suporte Monitor", 20, 8.00},
    {20, "Base Refrigerada Notebook", 20, 14.00}
};

//função mostrar estoque
void mostrarEstoque() {
    for (int i = 0; i < estoque.size(); i++) {
        if (estoque[i].quantidade != 0)
            cout << fixed << setprecision(2) << estoque[i];
    }
}

//função para verificar se o produto escolhido tem no estoque
void checarProdutoEstoque(int idProduto, Produto*& produtoSelecionado) {
    //percorre o estoque e se encontrar o produto no estoque, guarda o vetor no ponteiro.
    produtoSelecionado = nullptr; // Inicia o ponteiro a nullo, para não haver lixo
    for (int i = 0; i < estoque.size(); i++) {
        if (estoque[i].id == idProduto) {
            produtoSelecionado = &estoque[i];
            break;
        }
    }
}

// Função para gerar venda aleatória grátis a cada 4 compras
int vendaGratis() {
    return rand() % 4 == 0;
}

// Função para adicionar 30% ao valor de custo
float calcValorVenda(float precoCusto) {
    return precoCusto * 1.3;
}

// Função para calular o iva
float calcIVA(float precoTotal) {
    return precoTotal * 0.23;
}

void removerProduto() {
    mostrarEstoque();
    int idProduto;

    cout << "Insira o ID do produto: ";
    cin >> idProduto;

    Produto* produtoSelecionado = nullptr; // Inicialmente não sabemos se o ID/Produto que o utilizador vai inserir existe, então inicializamos um ponteiro nulo que é atualizado
    checarProdutoEstoque(idProduto, produtoSelecionado);

    // Verifica se o produto existe
    if (produtoSelecionado == nullptr) {
        cout << "Produto com ID " << idProduto << " não encontrado.\n";
    }
    else if (produtoSelecionado->quantidade == 0) { // Se o produto existe, mas não está mais em estoque
        cout << "Este produto já não está em estoque.";
    }
    else { // O produto existe e está em estoque
        produtoSelecionado->quantidade = 0;
        cout << "Produto removido.\n";
    }

    _getch();
}


void adicionarProduto() {  

    string nome;
    bool existe = false; // Flag inspeciona se o artigo já existe

    cout << "Insira o nome do novo artigo: ";
    cin.ignore();
    getline(cin, nome); // Lê a linha inteira, permitindo espaços nos nomes 

    for (int i = 0; i < estoque.size(); i++) {
        if (estoque[i].nome == nome) {  // Compara o nome do produto com cada item do estoque. Se encontrar um igual, deixa de adicionar e começa a alterar o produto existente
            cout << "Atualize a quantidade: ";
            cin >> estoque[i].quantidade;
            cout << "Artigo atualizado.";
            existe = true;
            break;
        }
    }
    if (existe == false) {
        Produto p; // Novo produto que iremos adicionar ao array no final

        p.nome = nome; // O nome do produto é o nome que inserimos acima
        p.id = estoque.size() + 1; // Id atribuido é um a mais do que o tamanho do estoque, que seria o ultimo id por default

        cout << "Insira o custo: ";
        cin >> p.precoCusto;
        cout << "Insira a quantidade: ";
        cin >> p.quantidade;

        // Adiciona ao vetor e aumenta o tamanho do estoque para que mais adições sejam possiveis
        estoque.push_back(p);

        cout << "Artigo adicionado.";
    }
    _getch();
}

//Função para escolher os produtos e a quantidade.
// void venda() {
//     int qtdProdutoVenda, idProduto, qtdVenda, numCliente;
//     static int numFatura = 1;
//     float valorPago, IVA, precoTotal, precoUnit, troco, totalComIVA=0;
//     //coloca o apontador do produto selecionado a nulo.
//     Produto* produtoSelecionado = nullptr; // Já declarado fora do loop

//     mostrarEstoque();

//     cout << "Inserir a quantidade de produtos desejados: ";
//     cin >> qtdProdutoVenda;

//     //iniciar Matriz
//     float mat[qtdProdutoVenda][5];

//     for (int i = 0; i < qtdProdutoVenda; i++) {
//         cout << "Digite o id do produto: ";
//         cin >> idProduto;
//         checarProdutoEstoque(idProduto, produtoSelecionado);
//         produtoSelecionado = &estoque[idProduto-1];
//         cout << "Digite a quantidade de " << produtoSelecionado->nome << " que deseja: ";
//         cin >> qtdVenda;

//         //caso o id digitado não esteja na lista, informa que não foi encontrado.
//         if (!produtoSelecionado) {
//             cout << "Produto nao encontrado.\n";
//             return;
//         }
//         //caso a quantidade vendida seja maior que o estoque, informa que não tem disponibilidade.
//         if (qtdVenda > produtoSelecionado->quantidade) {
//             cout << "Quantidade em stock insuficiente.\n";
//             qtdProdutoVenda--;
//             mostrarEstoque();
//             continue;
//         }

//         precoUnit = calcValorVenda(produtoSelecionado->precoCusto);
//         precoTotal = precoUnit * qtdVenda;
//         IVA = calcIVA(precoTotal);
//         totalComIVA = precoTotal + IVA;

//         mat[i][0] = idProduto;
//         mat[i][1] = qtdVenda;
//         mat[i][2] = precoTotal;
//         mat[i][3] = IVA;
//         mat[i][4] = totalComIVA;

//     //diminui os produtos vendidos do estoque
//     produtoSelecionado -> quantidade -= qtdVenda;

//     mostrarEstoque();
//     }

//     //verifica se a venda sorteada é verdadeira e coloca o Total = 0
//     bool vendaSorteada = vendaGratis();
//     if (vendaSorteada) {
//         totalComIVA = 0;
//         IVA = 0;
//         cout << "Informe ao cliente que a venda dele foi sorteada e será gratis.\n";
//     }

//     cout << "Digite o Numero do cliente: ";
//     cin >> numCliente;

//     //calcula o valor total usando um operador ternário
//     float somaTotal = 0;
//     for (int i = 0; i < qtdProdutoVenda; ++i) {
//         somaTotal += vendaSorteada ? 0 : mat[i][4];
//     }
//     //Verifica se a venda foi sorteada, caso não informa o valor total e pede o valor pago pelo cliente para calcular o troco
//     if (!vendaSorteada) {
//         cout << "Total a pagar: " << somaTotal << " euros\n";
//         cout << "Inserir o valor pago: ";
//         cin >> valorPago;
//     } else {
//         valorPago = 0;
//     }

//     troco = valorPago - somaTotal;

//     //imprir talão
//     time_t t = time(nullptr);
//     tm* dataAtual = localtime(&t);

//     cout << "\n======= TALAO DE COMPRA =======\n";
//     cout << "Fatura N: " << numFatura++ << endl;
//     cout << "Data: " << put_time(dataAtual, "%d/%m/%Y %H:%M") << endl;
//     cout << "Cliente N: " << numCliente << endl;
//     for (int i = 0; i < qtdProdutoVenda; i++) {
//         int produtoTalao = static_cast<int>(mat[i][0]);
//         Produto* produtoTalao = nullptr;
//         if (produtoTalao) {
//             cout << "Produto: " << produtoTalao->nome << endl;
//             cout << "Preço Unitário: " << calcValorVenda(produtoTalao->precoCusto) << " euros" << endl;
//             cout << "Quantidade: " << static_cast<int>(mat[i][1]) << endl;
//             cout << "Preço s/IVA do produto: " << mat[i][2] << " euros" << endl;
//             cout << "IVA (23%): " << mat[i][3] << " euros" << endl;
//         }
//     }
//     cout << "Total c/IVA: " << somaTotal << " euros" << endl;
//     cout << "Valor Entregue: " << valorPago << " euros" << endl;
//     cout << "Troco: " << troco << " euros" << endl;
//     cout << "===============================\n";
// }


//função menu
void exibirMenu() {
    int opcao;
    //menu com as interações do programa
    do {
        system("cls"); // Limpa a tela toda a vez que uma opção é selecionada

        cout << "------MENU PRINCIPAL------" << endl;
        cout << "1. Efetuar Venda" << endl;
        cout << "2. Criar Novo Artigo/Atualizar Artigo" << endl;
        cout << "3. Excluir Produto" << endl;
        cout << "4. Exibir Stock" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            // chamar função de venda aqui
            //venda();
            break;
        case 2:
            // chamar função de criação
            adicionarProduto();
            break;
        case 3:
            // chamar função de eliminação
            removerProduto();
            break;
        case 4:
            // chamar função mostrar estoque
            mostrarEstoque();
            // System pause é utilizao para funções que não pedem por input, pra impedir a tela de limpar fora de hora
            _getch();
            break;
        case 5:
            cout << "Pressione qualquer tecla..." << endl;
            _getch();
            break;
        default:
            cout << "Opcao invalida! Tente novamente." << endl;
            _getch();
        }

        cout << endl;

    } while (opcao != 5);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    exibirMenu();
}
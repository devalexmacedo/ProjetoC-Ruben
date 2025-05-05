#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <locale.h> // Para permitir caracteres especiais
#include <conio.h> // Adicionado para usar o comando _getch, que interrompe limpezas de tela for de hora esperando um input do user

using namespace std;

//Estrutura do produto.
struct Produto {
    int id;
    string nome;
    int quantidade;
    float precoCusto;
};

//função da biblioteca iostream para o cout conseguir ler os objetos da estrutura Produto.l
ostream& operator<<(ostream& os, const Produto& p) {
    os << "ID: " << p.id << " | "
       << "Nome: " << p.nome << " | "
       << "Quantidade: " << p.quantidade << " | "
       << "Preco: " << fixed << setprecision(2) << p.precoCusto << " euros" << endl;
    return os;
}

//Insere produtos no estoque.
Produto estoque[] = {
    {1, "Placa Mae ASUS B550", 20, 85.00},
    {2, "Processador Ryzen 5 5600X", 20, 140.00},
    {3, "Memoria RAM 16GB DDR4", 20, 35.00},
    {4, "Disco SSD 1TB NVMe", 20, 55.00},
    {5, "Fonte 650W 80+ Bronze", 20, 45.00},
    {6, "Placa Grafica RTX 3060", 20, 260.00},
    {7, "Caixa Mid Tower", 20, 40.00},
    {8, "Cooler CPU ARGB", 20, 25.00},
    {9, "Monitor 24'' Full HD", 20, 90.00},
    {10, "Teclado Mecânico RGB", 20, 30.00}
    // {11, "Rato Gaming 7200 DPI", 20, 15.00},
    // {12, "Hub USB 3.0", 20, 10.00},
    // {13, "Adaptador Wi-Fi USB", 20, 12.00},
    // {14, "Pasta Térmica", 20, 3.00},
    // {15, "Cabo HDMI 2.0", 20, 4.00},
    // {16, "Ventoinha 120mm", 20, 5.00},
    // {17, "Kit Chave Torx PC", 20, 6.00},
    // {18, "Extensão de Energia", 20, 7.00},
    // {19, "Suporte Monitor", 20, 8.00},
    // {20, "Base Refrigerada Notebook", 20, 14.00}
};

//Calcula o tamanho do estoque para o usar o ciclo de repetição.
int tamEstoque = sizeof (estoque) / sizeof (estoque[0]);

//função mostrar estoque
void mostrarEstoque() {
    cout << "=============================== ESTOQUE ================================" << endl;
    for(int i = 0; i < tamEstoque; i++) {
        if (estoque[i].quantidade != 0)
        cout << estoque[i];
    }
    cout << "========================================================================" << endl;
}

//função para verificar se o produto escolhido tem no estoque
void checarProdutoEstoque(int idProduto, Produto*& produtoSelecionado){
    //percorre o estoque e se encontrar o produto no estoque, guarda o vetor no ponteiro.
    produtoSelecionado = nullptr; // Inicia o ponteiro a nullo, para não haver lixo
    for (int i = 0; i < tamEstoque; i++) {
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

//Função para escolher os produtos e a quantidade.
void venda() {
    int qtdProdutoVenda=0, idProduto, qtdVenda, numCliente;
    static int numFatura = 1;
    float valorPago, IVA, precoTotal, precoUnit, troco, totalComIVA=0, ivaUnitario, precoSemIVA;
    //coloca o apontador do produto selecionado a nulo.
    Produto* produtoSelecionado = nullptr; // Já declarado fora do loop

    mostrarEstoque();
    cout << endl;
    cout << "Inserir a quantidade de produtos desejados: ";
    cin >> qtdProdutoVenda;
    cout << endl;
    //iniciar Matriz
    float mat[qtdProdutoVenda][6]; // Aumentei para guardar o preço unitário

    for (int i = 0; i < qtdProdutoVenda; i++) {
        cout << "Digite o id do produto: ";
        cin >> idProduto;
        cout << endl;
        checarProdutoEstoque(idProduto, produtoSelecionado);
        if (!produtoSelecionado) {
            cout << "Produto nao encontrado.\n";
            return;
        }
        cout << "Digite a quantidade de " << produtoSelecionado->nome << " que deseja: ";
        cin >> qtdVenda;
        cout << endl;
        //caso a quantidade vendida seja maior que o estoque, informa que não tem disponibilidade.
        if (qtdVenda > produtoSelecionado->quantidade) {
            cout << "Quantidade em stock insuficiente para " << produtoSelecionado->nome << " (Estoque disponivell: " << produtoSelecionado->quantidade << ").\n";
            cout << "Digite uma nova quantidade (ou 0 para cancelar este item): ";
            cin >> qtdVenda;
            cout << endl;
            if (qtdVenda == 0) {
                cout << "Item cancelado.\n";
                continue; // Passa para o próximo produto
            } else if (qtdVenda > produtoSelecionado->quantidade) {
                cout << "Quantidade ainda insuficiente. Item cancelado.\n";
                continue; // Passa para o próximo produto
            }
        }
        ivaUnitario = calcIVA(calcValorVenda(produtoSelecionado->precoCusto));
        precoUnit = calcValorVenda(produtoSelecionado->precoCusto)+ivaUnitario;
        precoSemIVA = precoUnit - ivaUnitario;
        precoTotal = precoUnit * qtdVenda;
        IVA = calcIVA(precoTotal);
        totalComIVA = precoTotal + IVA;

        mat[i][0] = idProduto;
        mat[i][1] = qtdVenda;
        mat[i][2] = precoSemIVA;
        mat[i][3] = IVA;
        mat[i][4] = totalComIVA;
        mat[i][5] = precoUnit; // Guardar o preço unitário

    }
    cout << "=========== Checkout ===========\n";
    for (int i = 0; i < qtdProdutoVenda; i++) {
        float somaTotal;
        int idProduto = mat[i][0];
        checarProdutoEstoque(idProduto, produtoSelecionado); // Usar a função para encontrar o produto
        if (produtoSelecionado) {
            cout << "Produto: " << produtoSelecionado->nome << endl;
            cout << "Quantidade: " << static_cast<int>(mat[i][1]) << endl;
            cout << "Preço Unitário: " << fixed << setprecision(2) << mat[i][5] << " euros" << endl;
            cout << "Produto s/IVA: " << fixed << setprecision(2) << mat[i][2] << " euros" << endl;
            cout << "IVA (23%): " << fixed << setprecision(2) << mat[i][3] << " euros" << endl;
            somaTotal += mat[i][5];
            cout << endl;
        }
        cout << "Total c/IVA: " << fixed << setprecision(2) << somaTotal << " euros" << endl;
        cout << endl;
    }
        

    //verifica se a venda sorteada é verdadeira e coloca o Total = 0
    bool vendaSorteada = vendaGratis();
    if (vendaSorteada) {
        totalComIVA = 0;
        IVA = 0;
        cout << "Informe ao cliente que a venda dele foi sorteada e será gratis.\n";
    }
    cout << "Digite o codigo do cliente: ";
    cin >> numCliente;
    cout << endl;

    //calcula o valor total usando um operador ternário
    float somaTotal = 0;
    for (int i = 0; i < qtdProdutoVenda; ++i) {
        somaTotal += vendaSorteada ? 0 : mat[i][4];
    }
    //Verifica se a venda foi sorteada, caso não informa o valor total e pede o valor pago pelo cliente para calcular o troco
    if (!vendaSorteada) {
        cout << "Total a pagar: " << fixed << setprecision(2) << somaTotal << " euros\n";
        cout << "Inserir o valor pago: ";
        cin >> valorPago;
        cout << endl;
    } else {
        valorPago = 0;
    }

    troco = valorPago - somaTotal;

    //imprir talão
    time_t t = time(nullptr);
    tm* dataAtual = localtime(&t);
    Produto* produtoSelecionadoTalao = nullptr;

    cout << "\n======= TALÃO DE COMPRAS =======\n";
    cout << "Fatura N: " << numFatura++ << endl;
    cout << "Data: " << put_time(dataAtual, "%d/%m/%Y %H:%M") << endl;
    cout << "Cliente N: " << numCliente << endl;
    cout << endl;
    cout << "----- Detalhes dos Produtos -----" << endl;
    cout << "---------------------------------\n";
    for (int i = 0; i < qtdProdutoVenda; i++) {
        int idProduto = mat[i][0];
        checarProdutoEstoque(idProduto, produtoSelecionadoTalao); // Usar a função para encontrar o produto
        if (produtoSelecionadoTalao) {
            cout << "Produto: " << produtoSelecionadoTalao->nome << endl;
            cout << "Quantidade: " << static_cast<int>(mat[i][1]) << endl;
            //diminui os produtos vendidos do estoque
            produtoSelecionado -> quantidade -= static_cast<int>(mat[i][1]);
            cout << "Preço Unitário: " << fixed << setprecision(2) << mat[i][5] << " euros" << endl;
            cout << "Produto s/IVA: " << fixed << setprecision(2) << mat[i][2] << " euros" << endl;
            cout << "IVA (23%): " << fixed << setprecision(2) << mat[i][3] << " euros" << endl;
        }
        cout << endl;
        cout << "---------------------------------\n";
    }
    cout << "Total c/IVA: " << fixed << setprecision(2) << somaTotal << " euros" << endl;
    cout << "Valor Pago: " << fixed << setprecision(2) << valorPago << " euros" << endl;
    cout << "Troco: " << fixed << setprecision(2) << troco << " euros" << endl;
    cout << "=====================================\n";
    _getch();
}

void removerProduto() {
    // Mostra o estoque pra o utilizador ver o que quer remover
    mostrarEstoque();
    int idProduto;  // Id do produto que vai ser removido

    cout << "Insira o ID do produto a remover: ";
    cin >> idProduto;

    Produto* produtoSelecionado = nullptr;
    checarProdutoEstoque(idProduto, produtoSelecionado);

    if (produtoSelecionado) {
        produtoSelecionado->quantidade = 0;
        cout << "Produto com ID " << idProduto << " removido (quantidade definida como 0).\n";
    } else {
        cout << "Produto com ID " << idProduto << " não encontrado no estoque.\n";
    }
    _getch();
}

void adicionarProduto() { // FUN��O COM PROBLEMA, CONSERTA(Primeiro caractere errado, espa�os d�o problema, e inser��o de char em int da problema)
    // A fun��o usa o item no index tamanho estoque, pois este vai sempre ser o ultimo item do array
    // Id atribuido � um a mais do que o tamanho do estoque, que seria o ultimo id por default
    estoque[tamEstoque].id = tamEstoque + 1;

    cout << "Insira o nome do novo artigo: ";
    cin >> estoque[tamEstoque].nome;
    cout << "Insira o custo: ";
    cin >> estoque[tamEstoque].precoCusto;
    cout << "Insira a quantidade em stock: ";
    cin >> estoque[tamEstoque].quantidade;

    // Aumenta o tamanho do estoque para que mais adi��es sejam possiveis
    tamEstoque++;
    cout << "Artigo adicionado.";
    _getch();
}

//função menu
void exibirMenu() {
    int opcao;
    //menu com as interações do programa
    do {
        system("cls"); // Limpa a tela toda a vez que uma opo  selecionada

        cout << "======= MENU PRINCIPAL ========" << endl;
        cout << "1. Efetuar Venda" << endl;
        cout << "2. Criar Novo Artigo" << endl;
        cout << "3. Excluir Produto" << endl;
        cout << "4. Exibir Stock" << endl;
        cout << "5. Sair" << endl;
        cout << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cout << endl;
        switch (opcao) {
            case 1:
                // chamar função de venda aqui
                venda();
                break;
            case 2:
                // chamar funo de criao
                adicionarProduto();
                break;
            case 3:
                // chamar funo de eliminao
                removerProduto();
                break;
            case 4:
                // chamar funo mostrar estoque
                mostrarEstoque();
                // System pause  utilizao para funes que no pedem por input, pra impedir a tela de limpar fora de hora
                _getch();
                break;
            case 5:
                cout << "Pressione qualquer tecla para sair..." << endl;
                _getch();
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
                _getch();
                break;
        }

        cout << endl;

    } while (opcao != 5);
}

int main () {
    setlocale (LC_ALL, ""); // Deixar o sistema determinar a locale padrão

    exibirMenu();
}
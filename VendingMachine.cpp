#include <iostream>

using namespace std;

// Estrutura para representar um produto
struct Product {
    char name[30];
    float price;
    int quantity;
};

// Funcao para exibir os produtos disponiveis
void displayProducts(const Product* products, int numProducts) {
    cout << "Produtos disponiveis:" << endl;

    for (int i = 0; i < numProducts; i++) {
        cout << i + 1 << ". " << products[i].name << " - R$" << products[i].price << " (Quantidade: " << products[i].quantity << ")" << endl;
    }
}

// Funcao para realizar uma compra
void purchaseProduct(Product* products, int choice) {
    int quantity;
    cout << "Digite a quantidade desejada: ";
    cin >> quantity;

    if (quantity > 0 && quantity <= products[choice - 1].quantity) {
        float totalAmount = products[choice - 1].price * quantity;

        cout << "Total a pagar: R$" << totalAmount << endl;

        float insertedAmount;
        cout << "Digite o valor inserido na maquina: ";
        cin >> insertedAmount;

        if (insertedAmount >= totalAmount) {
            float change = insertedAmount - totalAmount;
            cout << "Retire seu produto: " << products[choice - 1].name << endl;
            cout << "Troco: R$" << change << endl;
            products[choice - 1].quantity -= quantity;
        } else {
            cout << "Valor inserido insuficiente. Transacao cancelada." << endl;
        }
    } else {
        cout << "Quantidade invalida. Transacao cancelada." << endl;
    }
}

// Funcao para exibir o inventario de produtos
void displayInventory(const Product* products, int numProducts) {
    cout << "Inventario de produtos:" << endl;

    for (int i = 0; i < numProducts; i++) {
        cout << products[i].name << " - Quantidade: " << products[i].quantity << endl;
    }
}

// Funcao para calcular o faturamento total
float calculateTotalRevenue(const Product* products, int numProducts) {
    float totalRevenue = 0.0;

    for (int i = 0; i < numProducts; i++) {
        totalRevenue += products[i].price * products[i].quantity;
    }

    return totalRevenue;
}

// Funcao para repor produtos no modo administrador
void restockProducts(Product* products, int numProducts) {
    cout << "----- Repor Produtos -----" << endl;
    displayInventory(products, numProducts);

    int choice;
    cout << "Escolha o numero do produto para repor (ou digite 0 para voltar): ";
    cin >> choice;

    if (choice >= 1 && choice <= numProducts) {
        int quantity;
        cout << "Digite a quantidade a ser adicionada: ";
        cin >> quantity;

        products[choice - 1].quantity += quantity;

        cout << "Produto " << products[choice - 1].name << " reposto com sucesso. Quantidade atual: " << products[choice - 1].quantity << endl;
    } else if (choice != 0) {
        cout << "Opcao invalida." << endl;
    }
}

int main() {
    Product products[] = {
        {"1. Refrigerante", 3.5, 5},
        {"2. Salgadinho", 2.0, 10},
        {"3. Chocolate", 2.5, 8},
        {"4. Suco", 1.5, 7}
    };

    int mode;
    bool exit = false;

    while (!exit) {
        cout << "Selecione o modo: " << endl;
        cout << "1. Modo Usuario" << endl;
        cout << "2. Modo Administrador" << endl;
        cout << "0. Sair" << endl;
        cin >> mode;

        switch (mode) {
            case 1:
            {
                cout << "----- Modo Usuario -----" << endl;
                displayProducts(products, sizeof(products) / sizeof(Product));

                int choice;
                cout << "Escolha o numero do produto que deseja comprar (ou digite 0 para voltar): ";
                cin >> choice;

                if (choice >= 1 && choice <= sizeof(products) / sizeof(Product)) {
                    purchaseProduct(products, choice);
                } else if (choice != 0) {
                    cout << "Opcao invalida." << endl;
                }

                break;
            }
            case 2:
            {
                cout << "----- Modo Administrador -----" << endl;
                float totalRevenue = calculateTotalRevenue(products, sizeof(products) / sizeof(Product));

                displayInventory(products, sizeof(products) / sizeof(Product));

                cout << "Total faturado: R$" << totalRevenue << endl;
                cout << "Total ainda pode faturar: R$" << totalRevenue << endl;

                restockProducts(products, sizeof(products) / sizeof(Product));

                break;
            }
            case 0:
                exit = true;
                break;
            default:
                cout << "Opcao invalida." << endl;
                break;
        }

        cout << endl;
    }

    cout << "Volte Sempre!";

    return 0;
}
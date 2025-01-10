#include <iostream>
#include <openssl/des.h>
#include <string.h>

using namespace std;

// Função para criptografar e descriptografar com 3DES
void process3DES(int mode) {
    // Definindo a chave diretamente dentro da função
    unsigned char key[24] = {'T', 'h', 'i', 's', 'I', 's', 'A', 'K', 'e', 'y', 'F', 'o', 'r', '3', 'D', 'E', 'S', '3', 'T', 'e', 's', 't', 'K', 'e'};
    
    // Mensagem a ser criptografada/descriptografada
    const unsigned char* input = (const unsigned char*)"Evertec simplificando o mercado de pagamentos";
    unsigned char encrypted[1024], decrypted[1024];

    DES_key_schedule key_schedule1, key_schedule2, key_schedule3;
    DES_cblock des_key1, des_key2, des_key3;
    unsigned char iv[8] = {0}; // IV (vetor de inicialização) iniciado com 0
    
    // Copiar a chave para três blocos de 8 bytes
    memcpy(des_key1, key, 8);
    memcpy(des_key2, key + 8, 8);
    memcpy(des_key3, key + 16, 8);
    
    // Definir as chaves para 3DES
    DES_set_key_unchecked(&des_key1, &key_schedule1);
    DES_set_key_unchecked(&des_key2, &key_schedule2);
    DES_set_key_unchecked(&des_key3, &key_schedule3);
    
    // Criptografar ou descriptografar com 3DES
    DES_ede3_cbc_encrypt(input, encrypted, strlen((const char*)input) + 1, &key_schedule1, &key_schedule2, &key_schedule3, iv, mode);

    if (mode == DES_ENCRYPT) {
        // Exibe a mensagem criptografada
        cout << "Mensagem criptografada (hex): ";
        for (int i = 0; i < strlen((const char*)input); ++i) {
            printf("%02x", encrypted[i]);
        }
        cout << endl;
    } else {
        // Descriptografando
        DES_ede3_cbc_encrypt(encrypted, decrypted, strlen((const char*)input) + 1, &key_schedule1, &key_schedule2, &key_schedule3, iv, mode);
        cout << "Mensagem descriptografada: " << decrypted << endl;
    }
}

int main() {
    // Criptografar a mensagem
    process3DES(DES_ENCRYPT);
    
    // Descriptografar a mensagem
    process3DES(DES_DECRYPT);

    return 0;
}

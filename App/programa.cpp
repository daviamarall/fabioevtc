#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

// Função para simular a operação DES (de forma simplificada)
void DES_encrypt_block(const unsigned char* input, unsigned char* output, const unsigned char* key) {
    // Este é um lugar para implementar o DES real.
    // Aqui, para fins educacionais, simularemos com uma operação XOR simples (não seguro!).
    for (int i = 0; i < 8; ++i) {
        output[i] = input[i] ^ key[i % 8];
    }
}

void DES_decrypt_block(const unsigned char* input, unsigned char* output, const unsigned char* key) {
    // A descriptografia é o inverso da criptografia (neste caso, usando XOR).
    for (int i = 0; i < 8; ++i) {
        output[i] = input[i] ^ key[i % 8];
    }
}

// Função para realizar o 3DES (Triple DES)
void TripleDES_encrypt(const vector<unsigned char>& plaintext, vector<unsigned char>& ciphertext,
    const unsigned char* key1, const unsigned char* key2, const unsigned char* key3) {
    size_t block_size = 8; // O tamanho do bloco para DES é de 8 bytes
    size_t num_blocks = (plaintext.size() + block_size - 1) / block_size;

    ciphertext.resize(num_blocks * block_size);

    for (size_t i = 0; i < num_blocks; ++i) {
        unsigned char block[8] = { 0 };
        unsigned char temp[8] = { 0 };

        // Copiar o bloco de entrada (com preenchimento, se necessário)
        size_t start = i * block_size;
        size_t length = min(block_size, plaintext.size() - start);
        memcpy(block, plaintext.data() + start, length);

        // Aplicar 3DES: E(key1), D(key2), E(key3)
        DES_encrypt_block(block, temp, key1); // Primeira encriptação
        DES_decrypt_block(temp, block, key2); // Primeira desencriptação
        DES_encrypt_block(block, temp, key3); // Segunda encriptação

        // Copiar o bloco cifrado para a saída
        memcpy(ciphertext.data() + start, temp, block_size);
    }
}

void TripleDES_decrypt(const vector<unsigned char>& ciphertext, vector<unsigned char>& plaintext,
    const unsigned char* key1, const unsigned char* key2, const unsigned char* key3) {
    size_t block_size = 8; // O tamanho do bloco para DES é de 8 bytes
    size_t num_blocks = ciphertext.size() / block_size;

    plaintext.resize(ciphertext.size());

    for (size_t i = 0; i < num_blocks; ++i) {
        unsigned char block[8] = { 0 };
        unsigned char temp[8] = { 0 };

        // Copiar o bloco de entrada
        size_t start = i * block_size;
        memcpy(block, ciphertext.data() + start, block_size);

        // Aplicar 3DES inverso: D(key3), E(key2), D(key1)
        DES_decrypt_block(block, temp, key3); // Primeira desencriptação
        DES_encrypt_block(temp, block, key2); // Primeira encriptação
        DES_decrypt_block(block, temp, key1); // Segunda desencriptação

        // Copiar o bloco decifrado para a saída
        memcpy(plaintext.data() + start, temp, block_size);
    }
}

int main() {
    string plaintext = "Evertec simplificando o mercado de pagamentos";
    unsigned char key1[8] = { 'K', 'E', 'Y', '1', '2', '3', '4', '5' };
    unsigned char key2[8] = { 'S', 'E', 'C', 'O', 'N', 'D', '2', 'K' };
    unsigned char key3[8] = { 'T', 'H', 'I', 'R', 'D', '3', 'K', 'E' };

    // Converter o texto plano para um vetor de bytes
    vector<unsigned char> plaintext_bytes(plaintext.begin(), plaintext.end());
    vector<unsigned char> ciphertext;
    vector<unsigned char> decryptedtext;

    // Criptografar
    TripleDES_encrypt(plaintext_bytes, ciphertext, key1, key2, key3);

    // Exibir o texto cifrado em hexadecimal
    cout << "Ciphertext (hex): ";
    for (unsigned char c : ciphertext) {
        cout << hex << setw(2) << setfill('0') << (int)c;
    }
    cout << endl;

    // Descriptografar
    TripleDES_decrypt(ciphertext, decryptedtext, key1, key2, key3);

    // Converter o vetor de bytes de volta para string
    string decrypted_string(decryptedtext.begin(), decryptedtext.end());
    cout << "Decrypted text: " << decrypted_string << endl;

    return 0;
}
#include <iostream>
#include <string>
#include <vector>

void generateMatrix(std::vector<std::string>& matrix, const std::string& key) {
    const int col = 5;
    std::vector<std::string> alphabet;
    alphabet.resize(26);
    matrix.resize(26);

    int code = 'a';
    for (int i = 0; i < 26; i++) {
        alphabet[i] = std::string(1, code + i);
    }

    for (int i = 0; i < key.length(); i++) {
        matrix[i] = std::string(1, key[i]);
    }

    for (int i = 0, k = key.length(); k < 26; i++) {
        bool check = true;
        for (int j = 0; j < key.length(); j++) {
            if (alphabet[i] == matrix[j]) {
                check = false;
                break;
            }
        }
        if (check) {
            matrix[k] = alphabet[i];
            k++;
        }
    }
}

std::string encryption(const std::string& message, const std::string& key) {
    std::vector<std::string> matrix;
    generateMatrix(matrix, key);

    std::string enMessage = "";
    std::string buf;
    for (int i = 0; i < message.length(); i++) {
        if (message[i] <= 'z' && message[i] >= 'a') {
            for (int j = 0; j < matrix.size(); j++) {
                if (message[i] == matrix[j][0]) {
                    if (j == 25) {
                        buf = matrix[j - 25];
                    }
                    else if (j > 20) {
                        buf = matrix[j - 20];
                    }
                    else {
                        buf = matrix[j + 5];
                    }
                    break;
                }
            }
            enMessage += buf;
        }
        else {
            enMessage += message[i];
        }
    }
    return enMessage;
}

std::string decryption(const std::string& message, const std::string& key) {
    std::vector<std::string> matrix;
    generateMatrix(matrix, key);

    std::string enMessage = "";
    std::string buf;
    for (int i = 0; i < message.length(); i++) {
        if (message[i] <= 'z' && message[i] >= 'a') {
            for (int j = 0; j < matrix.size(); j++) {
                if (message[i] == matrix[j][0]) {
                    if (j == 0) {
                        buf = matrix[j + 25];
                    }
                    else if (j < 5) {
                        buf = matrix[j + 20];
                    }
                    else {
                        buf = matrix[j - 5];
                    }
                    break;
                }
            }
            enMessage += buf;
        }
        else {
            enMessage += message[i];
        }
    }
    return enMessage;
}

int main() {
    std::string key = "secret";
    std::string message = "But eyes are blind. You have to look with the heart.";
    std::cout << "Key: " << key << std::endl;
    std::cout << "Origin message: " << message << std::endl;

    std::string encryptedMessage = encryption(message, key);
    std::cout << "Encrypted message: " << encryptedMessage << std::endl;

    std::string decryptedMessage = decryption(encryptedMessage, key);
    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

    return 0;
}

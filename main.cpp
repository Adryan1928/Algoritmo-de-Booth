#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int verify_input(int value, int bits) {
    int potential_value = pow(2, bits - 1);
    int min_val = -potential_value;
    int max_val = potential_value - 1;

    if (value < min_val || value > max_val) {
        throw invalid_argument(
            "Valor deve estar entre " + to_string(min_val) + " e " +
            to_string(max_val) + " para " + to_string(bits) + " bits."
        );
    }

    return value;
}

bool logic_or(bool a, bool b) {
    return a || b;
}

bool logic_and(bool a, bool b = true) {
    return a && b;
}

bool logic_xor(bool a, bool b) {
    return (a && !b) || (!a && b);
}

pair<bool, bool> sum_bit(bool a, bool b, bool carry_in) {
    bool carry_out = logic_or(logic_and(a, b), logic_and(logic_or(a, b), carry_in));
    bool sum_result = logic_xor(logic_xor(a, b), carry_in);
    return {carry_out, sum_result};
}

vector<bool> sum_bits(const vector<bool>& value1, const vector<bool>& value2, int bits) {
    vector<bool> result(bits, false);
    bool carry = false;

    for (int i = bits - 1; i >= 0; --i) {
        pair<bool, bool> bit_sum = sum_bit(value1[i], value2[i], carry);
        carry = bit_sum.first;
        result[i] = bit_sum.second;
    }

    return result;
}

vector<bool> twos_complement(vector<bool> bits_in_binary, int bits) {
    for (int i = 0; i < bits; ++i) {
        bits_in_binary[i] = !bits_in_binary[i];
    }

    vector<bool> sum_one_bit(bits, false);
    sum_one_bit[bits - 1] = true;

    bits_in_binary = sum_bits(bits_in_binary, sum_one_bit, bits);
    return bits_in_binary;
}

vector<bool> to_binary(int n, int bits) {
    vector<bool> bits_in_binary;
    bool negative = n < 0;

    if (negative) {
        n *= -1;
    }

    for (int i = bits; i > 0; --i) {
        int potential_value = pow(2, i - 1);
        if (n % potential_value != n) {
            n -= potential_value;
            bits_in_binary.push_back(true);
        } else {
            bits_in_binary.push_back(false);
        }
    }

    if (negative) {
        bits_in_binary = twos_complement(bits_in_binary, bits);
    }

    return bits_in_binary;
}

int to_decimal(vector<bool> bits_in_binary) {
    int value = 0;
    int bits = static_cast<int>(bits_in_binary.size());
    bool negative = bits_in_binary[0];

    if (negative) {
        bits_in_binary = twos_complement(bits_in_binary, bits);
    }

    for (int i = 0; i < bits; ++i) {
        if (bits_in_binary[i]) {
            value += pow(2, bits - 1 - i);
        }
    }

    if (negative) {
        value *= -1;
    }

    return value;
}

string to_binary_string(const vector<bool>& bits_in_binary) {
    string binary;
    binary.reserve(bits_in_binary.size());

    for (bool bit : bits_in_binary) {
        binary += bit ? '1' : '0';
    }

    return binary;
}

int booth_algorithm(int multiplicand, int multiplier, int bits = 8) {
    vector<bool> M = to_binary(multiplicand, bits);
    vector<bool> Q = to_binary(multiplier, bits);
    vector<bool> A(bits, false);
    bool Q_1 = false;

    cout << "Inicial -> A=" << to_binary_string(A)
         << ", Q=" << to_binary_string(Q)
         << ", Q-1=" << to_binary_string(vector<bool>{Q_1})
         << ", M=" << to_binary_string(M) << "\n";

    for (int step = 0; step < bits; ++step) {
        cout << "\nPasso " << step + 1 << ":\n";

        if (logic_and(Q[bits - 1]) && !logic_and(Q_1)) {
            cout << "A = A - M\n";
            A = sum_bits(A, twos_complement(M, bits), bits);
        } else if (!logic_and(Q[bits - 1]) && logic_and(Q_1)) {
            cout << "A = A + M\n";
            A = sum_bits(A, M, bits);
        }

        bool A_1 = A[bits - 1];

        vector<bool> new_A;
        new_A.reserve(bits);
        new_A.push_back(A[0]);
        for (int i = 0; i < bits - 1; ++i) {
            new_A.push_back(A[i]);
        }
        A = new_A;

        Q_1 = Q[bits - 1];

        vector<bool> new_Q;
        new_Q.reserve(bits);
        new_Q.push_back(A_1);
        for (int i = 0; i < bits - 1; ++i) {
            new_Q.push_back(Q[i]);
        }
        Q = new_Q;

        cout << "A=" << to_binary_string(A)
             << ", Q=" << to_binary_string(Q)
             << ", Q-1=" << to_binary_string(vector<bool>{Q_1}) << "\n";
    }

    vector<bool> result = A;
    result.insert(result.end(), Q.begin(), Q.end());

    cout << "\nResultado binário: " << to_binary_string(result) << "\n";

    int decimal_result = to_decimal(result);
    cout << "Resultado decimal: " << decimal_result << "\n";

    return decimal_result;
}

int read_int(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }

        cout << "Por favor, insira um número inteiro válido.\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    cout << "Algoritmo de Booth para multiplicação binária\n\n";

    int bits;
    while (true) {
        bits = read_int("Digite o numero de bits para a representação (ex: 8): ");
        if (bits <= 0) {
            cout << "Por favor, insira um número de bits positivo.\n";
            continue;
        }
        break;
    }

    while (true) {
        int multiplicand;
        int multiplier;

        while (true) {
            multiplicand = read_int("Digite o multiplicando (inteiro): ");
            multiplier = read_int("Digite o multiplicador (inteiro): ");

            try {
                verify_input(multiplicand, bits);
                verify_input(multiplier, bits);
                break;
            } catch (const invalid_argument& e) {
                cout << "Erro: " << e.what() << "\n";
            }
        }

        cout << "\nMultiplicando: " << multiplicand
             << ", Multiplicador: " << multiplier << "\n";

        booth_algorithm(multiplicand, multiplier, bits);

        cout << "\nDeseja realizar outra multiplicacao? (s/n): ";
        string cont;
        cin >> cont;

        if ((cont[0] == 'n' || cont[0] == 'N')) {
            cout << "Encerrando o programa. Obrigado por usar!\n";
            break;
        }
    }

    return 0;
}

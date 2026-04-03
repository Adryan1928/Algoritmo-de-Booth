from typing import List

def verify_input(value: int, bits: int) -> int:
    potential_value = 2 ** (bits - 1)
    min_val = -potential_value
    max_val = potential_value - 1

    if value < min_val or value > max_val:
        raise ValueError(f"Valor deve estar entre {min_val} e {max_val} para {bits} bits.")
    return value

def logic_or(a: bool, b: bool) -> bool:
    return a or b

def logic_and(a: bool, b: bool=True) -> bool:
    return a and b

def logic_xor(a: bool, b: bool) -> bool:
    return (a and not b) or (not a and b)

def sum_bit(a: bool, b: bool, carry_in: bool) -> List[bool, bool]:
    carry_out = logic_or(logic_and(a, b), logic_and(logic_or(a, b), carry_in))
    sum_bit = logic_xor(logic_xor(a, b), carry_in)
    return carry_out, sum_bit

def sum_bits(value1: List[bool], value2: List[bool], bits: int) -> List[bool]:
    result = [False] * bits
    carry = False

    for i in range(bits - 1, -1, -1):
        carry, result[i] = sum_bit(value1[i], value2[i], carry)

    return result

def twos_complement(bits_in_binary:List[bool], bits: int) -> List[bool]:
    bits_in_binary = [not bit for bit in bits_in_binary]
    sum_one_bit = [False] * bits
    sum_one_bit[-1] = True

    bits_in_binary = sum_bits(bits_in_binary, sum_one_bit, bits)

    return bits_in_binary

def to_binary(n: int, bits: int) -> List[bool]:
    bits_in_binary = []
    negative = n < 0

    if (negative):
        n *= -1

    for i in range(bits, 0, -1):
        potential_value = 2 ** (i - 1)
        if n % potential_value != n:
          n-= potential_value
          bits_in_binary.append(True)
        else:
          bits_in_binary.append(False)

    if (negative):
        bits_in_binary = twos_complement(bits_in_binary, bits)

    return bits_in_binary

def to_decimal(bits_in_binary: List[bool]) -> int:
    value = 0
    bits = len(bits_in_binary)
    negative = bits_in_binary[0]

    if (negative):
        bits_in_binary = twos_complement(bits_in_binary, bits)

    for i in range(bits):
        if bits_in_binary[i]:
            value += 2 ** (bits - 1 - i)

    if (negative):
        value *= -1

    return value

def to_binary_string(bits_in_binary: List[bool]) -> str:
    return ''.join(['1' if bit else '0' for bit in bits_in_binary])

def booth_algorithm(multiplicand: int, multiplier: int, bits: int=8) -> int:
    M = to_binary(multiplicand, bits)
    Q = to_binary(multiplier, bits)
    A = [False] * bits
    Q_1 = False

    print(f"Inicial -> A={to_binary_string(A)}, Q={to_binary_string(Q)}, Q-1={to_binary_string([Q_1])}, M={to_binary_string(M)}")

    for step in range(bits):
        print(f"\nPasso {step + 1}:")

        if logic_and(Q[-1]) and not logic_and(Q_1):
            print("A = A - M")
            A = sum_bits(A, twos_complement(M, bits), bits)

        elif not logic_and(Q[-1]) and logic_and(Q_1):
            print("A = A + M")
            A = sum_bits(A, M, bits)
        A_1 = A[-1]
        A = [A[0]] + A[:-1]
        Q_1 = Q[-1]
        Q = [A_1] + Q[:-1]

        print(f"A={to_binary_string(A)}, Q={to_binary_string(Q)}, Q-1={to_binary_string([Q_1])}")

    result = A + Q
    print(f"\nResultado binário: {to_binary_string(result)}")

    decimal_result = to_decimal(result)
    print(f"Resultado decimal: {decimal_result}")

    return decimal_result
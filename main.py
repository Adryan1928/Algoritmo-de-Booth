from utils import *

def main():
    print("Algoritmo de Booth para multiplicação binária\n")

    while True:
        try:
            bits = int(input("Digite o número de bits para a representação (ex: 8): "))
            if bits <= 0:
                print("Por favor, insira um número de bits positivo.")
                continue 
            break
        except ValueError:
            print("Por favor, insira um número inteiro válido para os bits.")    

    while True:
      while True:
          try:
              multiplicand = int(input("Digite o multiplicando (inteiro): "))
              multiplier = int(input("Digite o multiplicador (inteiro): "))
              verify_input(multiplicand, bits)
              verify_input(multiplier, bits)
              break
          except ValueError as e:
              if (e.args and "Valor deve estar entre" in e.args[0]):
                print(f"Erro: {e}")
              else:
                print("Por favor, insira um número inteiro válido para o multiplicando e multiplicador.")
        


      print(f"\nMultiplicando: {multiplicand}, Multiplicador: {multiplier}")

      result = booth_algorithm(multiplicand, multiplier, bits)

      cont = input("\nDeseja realizar outra multiplicação? (s/n): ").strip().lower()
      if cont == 'n':
          print("Encerrando o programa. Obrigado por usar!")
          break
      

main()
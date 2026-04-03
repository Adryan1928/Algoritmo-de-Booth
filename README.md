# 📘 Algoritmo de Booth em Python

Este projeto implementa o **Algoritmo de Booth** para multiplicação de números inteiros com sinal utilizando representação em **complemento de dois**.

O objetivo é simular, de forma didática, como essa multiplicação é realizada em nível de hardware, utilizando operações binárias e manipulação de bits.

---

# 🎯 Objetivo do projeto

Este projeto tem como foco:

- Entender multiplicação binária em baixo nível
- Aprender sobre:
  - Complemento de dois
  - Operações bit a bit
  - Shift aritmético
- Simular comportamento de hardware usando software

---

# 🧠 O que é o Algoritmo de Booth?

O **Algoritmo de Booth** é um método eficiente para multiplicação binária que:

- Suporta números **positivos e negativos**
- Utiliza **complemento de dois**
- Reduz o número de operações em sequências de bits iguais

---

## 🔍 Ideia principal

Ao invés de simplesmente somar várias vezes, o algoritmo:

- Analisa pares de bits: **Q₀ (último bit de Q)** e **Q-1**
- Decide se deve:
  - Somar (`A = A + M`)
  - Subtrair (`A = A - M`)
  - Ou não fazer nada

---

## 📊 Regras de decisão

| Q₀ | Q-1 | Ação        |
|----|-----|------------|
| 0  | 0   | Nenhuma    |
| 1  | 1   | Nenhuma    |
| 0  | 1   | A = A + M  |
| 1  | 0   | A = A - M  |

---


# ▶️ Como executar o projeto

## ✅ Pré-requisitos

- Python 3 instalado

---

## 🚀 Execução

No terminal, execute:

```sh
python main.py
```


---

# 👨‍💻 Melhorias

- Implementar interface gráfica
- Usar bitwise shift (Não foi utilizado para tornar mais didático)
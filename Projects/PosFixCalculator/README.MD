# Projeto de Calculadora Simples

Esse projeto/trabalho da disciplina Estrutura de Dados consiste em criar uma calculadora simples que recebe expressões/operações do tipo in-fixo, transforma-as em operações pos-fixadas (notação polonesa) e, finalmente, avalia a expressão.

Para resolver este problema, resolvi definir alguns conceitos para facilitar o entendimento do problema e a sua resolução, conforme será descrito a seguir.

## Definições
### Operador
- Um operador representa o que será feito em uma operação, podendo ser do tipo 
adição (+), subtração(-), multiplicação(*), divisão(/) ou exponenciação (^).
- Um operador deve sempre estar entre dois operandos.
- Os operadores possuem precedências diferentes, seguindo a ordem:
  1. Exponenciação
  2. Multiplicação e Divisão (ordem em que aparecem)
  3. Adições e Subtrações (ordem em que aparecem)
- As operações de exponenciação que estiverem em sequência devem ser realizadas da direita para a esquerda, enquanto as dos outros operadores devem ser realizadas da esquerda para direita

### Operando
- Um operando representa um número, de forma direta, ou, de forma indireta, uma expressão que, dentro de um contexto, será transformada em um valor numérico.

### Contexto
- Um contexto representa um conjunto de operações a serem realizadas em uma ordem específica.
- Na minha implementação, um contexto é composto de uma fila (FIFO) de operações.
- Pode ser iniciado por '(', '[' ou '{' e finalizado, respectivamente, por ')', ']', '}'.


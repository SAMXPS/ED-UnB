# Projeto de Calculadora Simples

Esse projeto/trabalho da disciplina Estrutura de Dados consiste em criar uma calculadora simples que recebe expressões/operações do tipo in-fixo, transforma-as em operações pos-fixadas (notação polonesa) e, finalmente, avalia a expressão.

Para resolver este problema, resolvi definir alguns conceitos para facilitar o entendimento do problema e a sua resolução, conforme será descrito a seguir.

## Definições
### Operador
- Um operador representa o que será feito em uma operação, podendo ser do tipo 
adição (+), subtração(-), multiplicação(*), divisão(/) ou exponenciação (^).
- Um operador deve sempre estar entre dois operandos.

### Operando
- Um operando representa um número, de forma direta, ou, de forma indireta, uma expressão que, dentro de um contexto, será transformada em um valor numérico.

### Operação
- Uma operação é o conjunto de dois operandos e um operador.

### Contexto
- Um contexto representa um conjunto de operações a serem realizadas em uma ordem específica.
- Na minha implementação, um contexto é composto de uma fila (FIFO) de operações.
- Pode ser iniciado por '(', '[' ou '{' e finalizado, respectivamente, por ')', ']', '}'.


# Threads Moving in a Grid

Autor: Igor Joaquim da Silva Costa

## Introdução

Este projeto tem como objetivo simular a movimentação de vários threads em uma grid, onde cada thread segue um caminho predefinido enquanto acessa as posições da grid de forma sincronizada.
Cada thread, após ser criado e obter seus dados de identificação e caminho, executa a seguinte sequência de operações:

1. Extrai a primeira posição P do caminho.
2. Entra na posição de grid identificada por P (sempre possível, pois todos os threads começam em posições diferentes).
3. Executa a função passa_tempo com o tempo associado à posição P.
4. Para o restante do caminho:
    - Obtém a próxima posição P' do caminho.
    - Quando as regras permitirem:
        - Entra na próxima posição.
        - Libera a posição anterior (Observação: ele só sai de uma posição quando pode entrar na próxima).
        - Executa a função passa_tempo com o tempo associado à posição P'.
  
## Como funciona a sincronização
### Percurso do Caminho
A função thread_t::run representa o loop principal de uma thread, onde ela percorre um caminho predefinido através da grid. Os mecanismos de sincronização garantem que as threads possam navegar com segurança pela grid sem conflitos, coordenando seus movimentos para evitar colisões e garantir uma execução eficiente.

Ao empregar mutexes, variáveis de condição e rastreamento de ocupação, os mecanismos de sincronização neste projeto permitem uma coordenação eficaz e acesso simultâneo seguro dentro do ambiente baseado em grid.

### Operações de Threads e Interação com a grid
As threads em execução no sistema aderem a um protocolo rigoroso quando interagem com a grid. Antes de entrar numa célula, uma thread adquire o mutex associado a essa célula, garantindo acesso exclusivo. Em seguida, verifica o estado de ocupação da célula e aguarda, se necessário, utilizando a variável de condição correspondente. Quando a célula fica disponível, a thread prossegue com a sua operação, marcando a célula como ocupada. Ao concluir sua tarefa dentro da célula, a thread libera o mutex, sinalizando sua saída.


## Uso

Para usar este projeto, siga estas etapas:

1. Compile os arquivos de origem usando um compilador C++.
2. Execute o executável com a entrada apropriada.
## Example

In this input: 
```
4 3
11 98 4
    0 0 50 
    1 0 60 
    2 0 90 
    3 0 60
12 99 4
    0 2 10
    1 2 20 
    2 2 60 
    3 2 180
13 99 4
    2 3 40 
    2 2 60 
    2 1 10 
    2 0 120
```

Gives the result
```
  0 [ 11 @( 0, 0) z  50
  0 [ 12 @( 0, 2) z  10
  0 [ 13 @( 2, 3) z  40
 10 ) 12 @( 0, 2) z  10
 10 [ 12 @( 1, 2) z  20
 30 ) 12 @( 1, 2) z  20
 30 [ 12 @( 2, 2) z  60
 40 ) 13 @( 2, 3) z  40
 50 ) 11 @( 0, 0) z  50
 50 [ 11 @( 1, 0) z  60
 90 ) 12 @( 2, 2) z  60
 90 [ 12 @( 3, 2) z 180
 90 [ 13 @( 2, 2) z  60
110 ) 11 @( 1, 0) z  60
110 [ 11 @( 2, 0) z  90
150 ) 13 @( 2, 2) z  60
150 [ 13 @( 2, 1) z  10
160 ) 13 @( 2, 1) z  10
200 ) 11 @( 2, 0) z  90
200 [ 11 @( 3, 0) z  60
200 [ 13 @( 2, 0) z 120
260 ) 11 @( 3, 0) z  60
270 ) 12 @( 3, 2) z 180
320 ) 13 @( 2, 0) z 120
```

## Instruções de compilação


Para compilar o projeto, execute o seguinte comando no terminal:

```
make build
```

Para executar o caso teste o projeto, execute o seguinte comando no terminal:

```
make test
```

### Compiler and flags
CC = g++ -g
CXXFLAGS = -std=c++17 -Wall -pthread
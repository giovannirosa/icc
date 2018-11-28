# Introdução a Computação Científica Trabalho 2

Trabalho 2 da matéria de Introdução a Computação Científica do segundo semestre de 2018, Universidade Federal do Paraná - UFPR.

## Início

Existe um makefile neste diretório com os seguintes comandos disponíveis:

* make: compila os arquivos
* make clean: limpa os arquivos
* make purge: limpa e deleta os arquivos gerados

### Pré-requisitos

É necessario gcc para compilar o código.

## Testes

A seguir será detalhado a entrada e saída do programa para realização de testes.

### Entrada

O programa deve ser executado com os seguintes parâmetros:  

`cgSolver -n <n> -k <k> -p <ω> -i <i> -e <ε> -o <arquivo_saida>`

`<n>`: (n>10) parâmetro obrigatório definindo a dimensão do Sistema Linear.  
`<k>`: (k>1 e k ímpar)  parâmetro obrigatório definindo o número de diagonais da matriz A.  
`<ω>`: parâmetro obrigatório indicando o pré-condicionador a ser utilizado:  
- `ω=0.0`: sem pré-condicionador  
- `0.0 < ω < 1.0`: pré-condicionador de Jacobi  

`<i>`: parâmetro obrigatório definindo o número máximo de iterações a serem executadas.  
`<ε>`: parâmetro opcional definindo o erro aproximado absoluto máximo, considerando a norma max (relativa) em x `(max|xi - xi-1| * 1/|xi| < ε)`.  
`<arquivo_saida>`: parâmetro obrigatório no qual arquivo_saida é o caminho completo para o arquivo que vai conter a solução.

### Saída

```
# login1 Nome1
# login2 Nome2
#
# iter 1: <||x||>
# iter 2: <||x||>
# ...
# iter k: <||x||>
# residuo: <||r||>
# Tempo PC: <tempo para cálculo do pré-condicionador>
# Tempo iter: <tempo para resolver uma iteração do método>
# Tempo residuo: <tempo para calcular o residuo do SL>
#
n
x_1 x_2 ... x_n
```

Onde:
- iter k: norma máxima do erro aproximado em x após a k-ésima iteração (max|xi - xi-1|);
- residuo: A norma euclidiana do resíduo (||r||), onde r= b - Ax
- Tempo: deve ser calculado em segundos, utilizando-se a função especificada abaixo.
- Tempo PC: tempo para calcular a matriz pré-condicionante M e preparar o SL para o uso do pré-condicionante. Não incluir tempo de leitura ou geração da matriz de entrada, nem a impressão dos resultados ou cálculo do erro.
- Tempo iter: Tempo médio para calcular cada iteração do método, inclusive o cálculo do erro.
- Tempo residuo: Tempo para calcular a norma do resíduo ao final do processo.

### Script de Testes

Nesse diretório se encontra um script tests.sh que contém 4 tipos de testes (Tempo, Banda de Memória, Cache Miss, Operações Aritméticas) para diferentes tamanhos (32,64,128,256,512,1000,2000) de ordem do sistema linear, com k = 7 diagonais, para i = 10 iterações.

### Limitações encontradas no projeto [BUGS]

Sistemas Lineares de ordem acima de 4000 demoram um tempo significativo para serem solucionados.

## Autor

* **Giovanni Rosa** - [giovannirosa](https://github.com/giovannirosa)

## Licença

Código aberto, qualquer um pode usar para qualquer propósito.
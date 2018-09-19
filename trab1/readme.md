# Introdução a Computação Científica Trabalho 1

Trabalho 1 da matéria de Introdução a Computação Científica do segundo semestre de 2018, Universidade Federal do Paraná - UFPR.

## Início

Existe um makefile neste diretório com os seguintes comandos disponíveis:

* make: compila os arquivos
* make clean: limpa os arquivos
* make clean: limpa e deleta os arquivos gerados

### Pré-requisitos

É necessario gcc para compilar o código.

### Entrada

O programa deve ser executado com os seguintes parâmetros:
cgSolver -n `<n>` -k `<k>` -p <ω> -i `<i>` -e <ε> -o `<arquivo_saida>`
`<n>`: (n>10) parâmetro obrigatório definindo a dimensão do Sistema Linear.
`<k>`: (k>1 e k ímpar)  parâmetro obrigatório definindo o número de diagonais da matriz A.
<ω>: parâmetro obrigatório indicando o pré-condicionador a ser utilizado:
    ω=0.0: sem pré-condicionador
    0.0 < ω < 1.0: pré-condicionador de Jacobi
`<i>`: parâmetro obrigatório definindo o número máximo de iterações a serem executadas.
<ε>: parâmetro opcional definindo o erro aproximado absoluto máximo, considerando a norma max (relativa) em x (max|xi - xi-1| * 1/|xi| < ε).
`<arquivo_saida>`: parâmetro obrigatório no qual arquivo_saida é o caminho completo para o arquivo que vai conter a solução.

### Limitações encontradas no projeto [BUGS]

Pré-condicionadores não implementados.

## Autor

* **Giovanni Rosa** - [giovannirosa](https://github.com/giovannirosa)

## Licença

Código aberto, qualquer um pode usar para qualquer propósito.
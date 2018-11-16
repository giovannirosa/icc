#!/usr/bin/gnuplot -c

# Execute o comando:
#    ./plot.gp < arquivo_dados
#
# Arquivo de dados recebido pela STDIN deve conter 2 colunas:
#    eixo x = coluna 1 = tamanho em Bytes
#    eixo y = coluna 2 em diante = indicadores
#
# Gerando gráfico a partir de tabela
set ylabel "FLOPS_DP (MFlops/s)"
set xlabel "N (bytes)"

set style data point
set style function line
set style line 1 lc 3 pt 7 ps 0.3

set terminal qt title "N x FLOPS_DP"
plot '< cat -' using 1:2 ls 1 notitle
pause mouse

# Gerando figura PNG
set terminal png
# set output "NxFLOPS_DP.png"
## plot '< cat -' using 1:2 ls 1 notitle
## replot
# unset output


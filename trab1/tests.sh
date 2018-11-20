#!/bin/bash
# clear

# echo "Running time tests:"
# ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida32.txt
# ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida64.txt
# ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida128.txt
# ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida256.txt
# ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida512.txt
# ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida1000.txt
# ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida2000.txt
# ./cgSolver -n 4000 -k 7 -p 0.1 -i 1000 -e 1e-4 -o saida4000.txt
#./cgSolver -n 8000 -k 7 -p 0.1 -i 1000 -e 1e-4 -o saida8000.txt

# echo "Running bandwidth tests:"
# likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data32.txt
# likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data64.txt
# likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data128.txt
# likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data256.txt
# likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data512.txt
# likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data1000.txt
# likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data2000.txt
# likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 4000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data4000.txt
# likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 8000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data8000.txt

# echo "Running cache miss tests:"
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data32.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data64.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data128.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data256.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data512.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data1000.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data2000.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 4000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data4000.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 8000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data8000.txt

echo "Running operations tests:\n"
echo "Running 32:\n"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data32.txt
echo "Running 64:\n"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data64.txt
echo "Running 128:\n"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data128.txt
echo "Running 256:\n"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data256.txt
echo "Running 512:\n"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data512.txt
echo "Running 1000:\n"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data1000.txt
echo "Running 2000:\n"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data2000.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 4000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data4000.txt
# likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 8000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data8000.txt
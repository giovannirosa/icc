#!/bin/bash
# clear

echo "Running time tests:"
<<<<<<< HEAD
#echo "Running 32:"
#./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida32.txt
#echo "Running 64:"
#./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida64.txt
#echo "Running 128:"
#./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida128.txt
#echo "Running 256:"
#./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida256.txt
#echo "Running 512:"
#./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida512.txt
#echo "Running 1000:"
#./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida1000.txt
#echo "Running 2000:"
#./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida2000.txt
echo "Running 4000:"
./cgSolver -n 4000 -k 7 -p 0.1 -i 1000 -e 1e-4 -o saida4000.txt
#echo "Running 8000:"
#./cgSolver -n 8000 -k 7 -p 0.1 -i 1000 -e 1e-4 -o saida8000.txt

echo "Running bandwidth tests:"
#echo "Running 32:"
#likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data32.txt
#echo "Running 64:"
#likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data64.txt
#echo "Running 128:"
#likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data128.txt
#echo "Running 256:"
#likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data256.txt
#echo "Running 512:"
#likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data512.txt
#echo "Running 1000:"
#likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data1000.txt
#echo "Running 2000:"
#likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data2000.txt
echo "Running 4000:"
likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 4000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data4000.txt
#echo "Running 8000:"
#likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 8000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l3-data8000.txt

echo "Running cache miss tests:"
#echo "Running 32:"
#likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data32.txt
#echo "Running 64:"
#likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data64.txt
#echo "Running 128:"
#likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data128.txt
#echo "Running 256:"
#likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data256.txt
#echo "Running 512:"
#likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data512.txt
#echo "Running 1000:"
#likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data1000.txt
#echo "Running 2000:"
#likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data2000.txt
echo "Running 4000:"
likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 4000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data4000.txt
#echo "Running 8000:"
#likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 8000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > l2cache-data8000.txt

echo "Running operations tests:"
#echo "Running 32:"
#likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data32.txt
#echo "Running 64:"
#likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data64.txt
#echo "Running 128:"
#likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data128.txt
#echo "Running 256:"
#likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data256.txt
#echo "Running 512:"
#likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data512.txt
#echo "Running 1000:"
#likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data1000.txt
#echo "Running 2000:"
#likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data2000.txt
echo "Running 4000:"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 4000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data4000.txt
#echo "Running 8000:"
#likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 8000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > flopsdp-data8000.txt
=======
echo "Running 32:"
./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o likwid-data/saida32.txt
echo "Running 64:"
./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o likwid-data/saida64.txt
echo "Running 128:"
./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o likwid-data/saida128.txt
echo "Running 256:"
./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o likwid-data/saida256.txt
echo "Running 512:"
./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o likwid-data/saida512.txt
echo "Running 1000:"
./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o likwid-data/saida1000.txt
echo "Running 2000:"
./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o likwid-data/saida2000.txt

echo "Running bandwidth tests:"
echo "Running 32:"
likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l3-data32.txt
echo "Running 64:"
likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l3-data64.txt
echo "Running 128:"
likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l3-data128.txt
echo "Running 256:"
likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l3-data256.txt
echo "Running 512:"
likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l3-data512.txt
echo "Running 1000:"
likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l3-data1000.txt
echo "Running 2000:"
likwid-perfctr -C 0-3 -g L3 -m ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l3-data2000.txt

echo "Running cache miss tests:"
echo "Running 32:"
likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l2cache-data32.txt
echo "Running 64:"
likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l2cache-data64.txt
echo "Running 128:"
likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l2cache-data128.txt
echo "Running 256:"
likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l2cache-data256.txt
echo "Running 512:"
likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l2cache-data512.txt
echo "Running 1000:"
likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l2cache-data1000.txt
echo "Running 2000:"
likwid-perfctr -C 0-3 -g L2CACHE -m ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/l2cache-data2000.txt

echo "Running operations tests:"
echo "Running 32:"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 32 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/flopsdp-data32.txt
echo "Running 64:"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 64 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/flopsdp-data64.txt
echo "Running 128:"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 128 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/flopsdp-data128.txt
echo "Running 256:"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 256 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/flopsdp-data256.txt
echo "Running 512:"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 512 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/flopsdp-data512.txt
echo "Running 1000:"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 1000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/flopsdp-data1000.txt
echo "Running 2000:"
likwid-perfctr -C 0-3 -g FLOPS_DP -m ./cgSolver -n 2000 -k 7 -p 0.1 -i 10 -e 1e-4 -o saida.txt > likwid-data/flopsdp-data2000.txt
>>>>>>> 60d78e2f2bc3d2e477c09ced136383d9b2d206ae

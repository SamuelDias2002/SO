#!/bin/bash

echo Escreva 5 números para serem ordenados - 
read n1 n2 n3 n4 n5

printf "$n1\n$n2\n$n3\n$n4\n$n5" > numerosLidos.txt

echo Números ordenados - 

sort -n numerosLidos.txt

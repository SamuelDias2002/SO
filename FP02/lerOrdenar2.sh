#!/bin/bash

echo Ordenado por ID >> res.txt
sort -n frutas.txt >> res.txt
printf "\nOrdenado alfabeticamente\n" >> res.txt
sort -n -t : -k 2 frutas.txt >> res.txt
printf "\nOrdenado por quantidade\n" >> res.txt
sort -n -t : -k 3 frutas.txt >> res.txt

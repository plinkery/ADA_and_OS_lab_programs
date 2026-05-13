#!/bin/bash

declare -A x
declare -A y
declare -A z

echo "Enter elements of first matrix:"
for (( i=0; i<3; i++ ))
do
        for (( j=0; j<3; j++ ))
        do
                read x["$i,$j"]
        done
done

echo "Enter elements of second matrix:"
for (( i=0; i<3; i++ ))
do
        for (( j=0; j<3; j++ ))
        do
                read y["$i,$j"]
        done
done

echo "First matrix:"
for (( i=0; i<3; i++ ))
do
        for (( j=0; j<3; j++ ))
        do
                echo -ne "${x[$i,$j]} "
        done
        echo
done

echo "Second matrix:"
for (( i=0; i<3; i++ ))
do
        for (( j=0; j<3; j++ ))
        do
                echo -ne "${y[$i,$j]} "
        done
        echo
done

echo "Resultant matrix:"
for (( i=0; i<3; i++ ))
do
        for (( j=0; j<3; j++ ))
        do
                z["$i,$j"]=$(( x[$i,$j] + y[$i,$j] ))
                echo -ne "${z[$i,$j]} "
        done
        echo
done	



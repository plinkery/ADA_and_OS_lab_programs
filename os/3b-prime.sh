#!/bin/bash

echo "enter the lower bound :"
read n1

echo "enter the upper bound :"
read n2

for (( i=n1; i<=n2; i++ ))
do
        if (( i < 2 ))
        then
                continue
        fi

        flag=0   # reset for each number

        for (( j=2; j<=i/2; j++ ))
        do
                if (( i % j == 0 ))
                then
                        flag=1
                        break
                fi
        done

        if (( flag == 0 ))
        then
                echo "$i"
        fi
done



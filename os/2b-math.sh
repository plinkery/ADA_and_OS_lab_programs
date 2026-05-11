#!/bin/bash
choice=0
until [[ $choice == 6 ]]
do
	echo "enter the two numbers : "
	read num1 num2
	echo "enter the operation to be performed : "
	echo "1) addition"
	echo "2) subtraction"
	echo "3) multiplication"
	echo "4) division"
	echo "5) modulo"
	echo "6) exit"
	read choice
	case "${choice}" in
		1)
			res=$((num1+num2))
			operation=addition
			;;

		2)
			res=$((num1-num2))
			operation=subtraction
			;;
		3)
			res=$((num1*num2))
			operation=multiplication
			;;
		4)
			if [[ $num2 == 0 ]]
			then
				echo "cannot divide by zero"
				flag=1
			else
				res=$((num1/num2))
				operation=division
			fi
			;;
		5)
			res=$((num1%num2))
			operation=modulo
			;;
		6)
			echo "thank you"
			break
			;;
		*)
			echo "wrong operation"
			;;
	esac
	if [[ $flag == 1 ]]
	then
		flag=0
		continue
	fi
	echo "the result of the $operation is $res"
done


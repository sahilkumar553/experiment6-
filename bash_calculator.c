#!/bin/bash

# prompt user for first number
echo "Enter first number: "
read num1

# prompt user for second number
echo "Enter second number: "
read num2

# prompt user for operation
echo "Choose an operation (+, -, *, /): "
read operation

# perform operation based on user input
case $operation in
    +) result=$(echo "$num1 + $num2" | bc)
       ;;
    -) result=$(echo "$num1 - $num2" | bc)
       ;;
    \*) result=$(echo "$num1 * $num2" | bc)
       ;;
    /) result=$(echo "scale=2; $num1 / $num2" | bc)
       ;;
    *) echo "Invalid operation"
       exit 1
       ;;
esac

# print the result
echo "Result: $result"

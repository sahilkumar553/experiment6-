#!/bin/bash

# Loop through the rows of the multiplication table
for (( i=1; i<=10; i++ ))
do
    # Loop through the columns of the multiplication table
    for (( j=1; j<=10; j++ ))
    do
        # Multiply the row and column numbers to get the product
        product=$((i*j))
        # Print the product with formatting to align columns
        printf "%-4d" $product
    done
    # Print a newline to move to the next row
    echo ""
done

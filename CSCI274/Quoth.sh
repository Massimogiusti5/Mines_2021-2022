#! /bin/bash

echo "Pick a quote-sayer from:"
ls -1 
echo "... or enter QUIT to exit the script."

while [ true ]; do
	read quoteSayer

	if [ $quoteSayer = "QUIT" ]; then
		exit
	fi
	if [ ! -e $quoteSayer ]; then
		exit 7
	fi

	cat $quoteSayer/quote.txt
done

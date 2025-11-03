# Name: Hayden Le
# Date: 1/14/25
# Title: Lab1 - circle
# Description: calc area of circle

#Sample shell programs for Lab assignment
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$="$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "hle3" ] #Replace with your own username!
then
	echo "Now you can proceed!"
else
	echo "Check who logged in!"
	exit 1
fi

response="Yes"
while [ $response != "No" ]
do
	echo "Enter radius of circle: "
	read radius
	area=$(echo "3.14159 * $radius * $radius" | bc)
	echo "The area of the circle is $area"
	echo "Would you like to repeat for another circle [Yes/No]?"
	read response
done

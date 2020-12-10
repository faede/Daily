#!/bin/bash
#
# Daily_Archive - Archive designated files & directories
########################################################
#
# Gather Current Date
#
DATE=$(date +%y%m%d)
#
# Set Archive File Name
#
FILE=archive$DATE.tar.gz
#
# Set Configuration and Destination File
#
CONFIG_FILE=/Users/zyy/Documents/archive/Files_to_Backup
DESTINATION=/Users/zyy/Documents/archive/$FILE 
#
############## Main Script ###################
#
# Check Back Config file exists
#
if [ -f $CONFIG_FILE ]
then
    echo
else
    echo 
    echo "$CONFIG_FILE does not exist."
    echo 
    exit
fi 

FILE_NO=1
exec < $CONFIG_FILE 
read FILE_NAME
while [ $? -eq 0 ]
do 
   if [ -f $FILE_NAME -o -d $FILE_NAME ]
   then 
       FILE_LIST="$FILE_LIST $FILE_NAME"
   else 
       echo 
       echo "$FILE_NAME , doesn't exist."
       echo "Obviously, I will not include it in this archive."
       echo "It is listed on line $FILE_NO of the config file."
       echo "Continuing to build archive list..."
       echo 
   fi 
   FILE_NO=$[$FILE_NO + 1]
   read FILE_NAME 
done

echo "Starting archive..."
echo 
tar -czf $DESTINATION $FILE_LIST 2> /dev/null 
echo "Archive completed"
echo "Resulting archive file is: $DESTINATION"
echo 
exit

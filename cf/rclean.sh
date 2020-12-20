#!/bin/bash
cur_path="$1"
pwd_dir=`pwd`
if [ ! -d "$cur_path" ]
then
	cur_path=$pwd_dir
	echo "You does'n input path so I set path to pwd :$pwd_dir"
fi

cur_path=`realpath $cur_path`
for doc in `find ${cur_path} -type f ! -name "*.*" `
do
	tag=`echo $doc | grep ".git"`
	tag2=`echo $doc | grep "LICENSE"`
    if [ "$tag" = "" ] && [ "$tag2" = "" ] 
#	if [ "${doc:0:$[5+${#cur_path}]}" != "${cur_path}/.git"  ]
	then
		`rm -i $doc`
	fi
done

for doc in `find ${cur_path} -type f -name "*.exe"`
do 
	rm -i $doc
done


for doc in `find ${cur_path} -type f -name "*.out"`
do 
	rm -i $doc
done

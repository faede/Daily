#!/bin/bash
cur_path="$1"
cur_path=`realpath $cur_path`
pwd_dir=`pwd`
if [ ! -d "$cur_path" ]
then
	cur_path=$pwd_dir
	echo "You does'n input path so I set path to pwd :$pwd_dir"
fi

for doc in `find ${cur_path} -type f ! -name "*.*" `
do
	tag=`echo $doc | grep ".git"`
	if [ "$tag" = "" ] 
#	if [ "${doc:0:$[5+${#cur_path}]}" != "${cur_path}/.git"  ]
	then
		`rm -i $doc`
	fi
done

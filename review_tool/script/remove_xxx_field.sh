#! /bin/bash

source ../conf/topic.conf

bin_path=../bin
data_path=../data

[ ! -d ${bin_path} ] && echo "${bin_path} not exist!" && exit 1
[ ! -d ${data_path} ] && echo "${data_path} not exist!" && exit 1

input_file="${data_path}/${topic}.json"
[ ! -f ${input_file} ] && echo "${input_file} not exist!" && exit 1

if [ ! $# -eq 1 ]
then
    echo "usage : field"
    exit 1
fi

field=$1

./${bin_path}/remove_xxx_field ${input_file} ${field}

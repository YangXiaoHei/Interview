#! /bin/bash

source ../conf/topic.conf

bin_path=../bin
data_path=../data

[ ! -d ${bin_path} ] && echo "${bin_path} not exist!" && exit 1
[ ! -d ${data_path} ] && echo "${data_path} not exist!" && exit 1

input_file="${data_path}/${topic}.json"

if [ ! $# -eq 3 ]
then
    echo "usage : field type default_value"
    exit 1
fi

[ ! -f ${input_file} ] && echo "${input_file} not exist!" && exit 1

field=$1
type=$2
default_value=$3

./${bin_path}/add_xxx_field ${input_file} ${field} ${type} ${default_value}

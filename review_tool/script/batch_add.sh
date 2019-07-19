#! /bin/bash

source ../conf/topic.conf

bin_path=../bin
data_path=../data

[ ! -d ${bin_path} ] && echo "${bin_path} not exist!" && exit 1
[ ! -d ${data_path} ] && echo "${data_path} not exist!" && exit 1

input_file="${data_path}/${topic}.json"
add_file="${data_path}/${topic}.add.json"

[ ! -f ${input_file} ] && echo "${input_file} not exist!" && exit 1
[ ! -f ${add_file} ] && echo "${add_file} not exist!" && exit 1

./${bin_path}/batch_add_question ${input_file} ${add_file} 

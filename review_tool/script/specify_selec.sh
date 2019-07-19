#! /bin/bash

source ../conf/topic.conf

bin_path=../bin
data_path=../data
input_file="${data_path}/${topic}.json"
bk_file="${data_path}/${topic}.bk.json"

[ ! -d ${bin_path} ] && echo "${bin_path} not exist!" && exit 1
[ ! -d ${data_path} ] && echo "${data_path} not exist!" && exit 1
[ ! -f ${input_file} ] && echo "${input_file} not exist!" && exit 1

total_num=5
total_cost=120

./${bin_path}/specify_select ${input_file} ${bk_file} ${total_num} ${total_cost}

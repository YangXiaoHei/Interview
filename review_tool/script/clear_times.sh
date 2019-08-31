#! /bin/bash

source ../conf/topic.conf

bin_path=../bin
data_path=../data
input_file="${data_path}/${topic}.json"

[ ! -d ${bin_path} ] && echo "${bin_path} not exist!" && exit 1
[ ! -f ${input_file} ] && echo "${input_file} not exist!" && exit 1

module="大数据"

./${bin_path}/clear_times ${input_file} ${module}

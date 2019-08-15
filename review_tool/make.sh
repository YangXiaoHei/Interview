#! /bin/bash

bin_path=bin
src_path=src

[ ! -d ${bin_path} ] && echo "${bin_path} not exist!" && exit 1
[ ! -d ${src_path} ] && echo "${src_path} not exist!" && exit 1

c++ -std=c++11 ${src_path}/add_xxx_field.cc -o ${bin_path}/add_xxx_field 
echo "add_xxx_field succ!"
c++ -std=c++11 ${src_path}/batch_add_question.cc -o ${bin_path}/batch_add_question 
echo "batch_add succ!"
c++ -std=c++11 ${src_path}/clear_times.cc -o ${bin_path}/clear_times 
echo "clear_times succ!"
c++ -std=c++11 ${src_path}/remove_xxx_field.cc -o ${bin_path}/remove_xxx_field 
echo "remove_xxx_field succ!"
c++ -std=c++11 ${src_path}/specify_select.cc -o ${bin_path}/specify_select 
echo "specify_select succ!"

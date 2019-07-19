#! /bin/bash

pack_name=review.zip
zip -r ${pack_name} bin script 

while read target_dir
do
    cp ${pack_name} ${target_dir}
    echo "cp ${pack_name} to ${target_dir}"

    cd ${target_dir} 
    rm -r bin script && echo "rm bin and script dir succ!"
    unzip ${pack_name}
    echo "unzip ${pack_name}"
    rm ${pack_name}

    [ ! -d conf ] && mkdir conf && echo "mkdir conf succ!"
    [ ! -d data ] && mkdir data && echo "mkdir data succ!"
    cd -
done < conf/sync.list

rm ${pack_name}


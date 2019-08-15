#! /bin/bash

pack_name=review.zip

# 打包 bin 和 script
zip -r ${pack_name} bin script 

# 对于 sync.list 中列出的目录, 逐个同步
while read target_dir
do
    # 把 bin 和 script 压缩包复制到目标路径
    cp ${pack_name} ${target_dir}
    echo "cp ${pack_name} to ${target_dir}"

    # 切到目标路径
    cd ${target_dir} 

    # 把原来的删掉
    rm -r bin script && echo "rm bin and script dir succ!"

    # 解压缩
    unzip ${pack_name}
    echo "unzip ${pack_name}"
    rm ${pack_name}

    [ ! -d conf ] && mkdir conf && echo "mkdir conf succ!"
    [ ! -d data ] && mkdir data && echo "mkdir data succ!"
    cd -
done < conf/sync.list

rm ${pack_name}


#!/bin/bash
#user and its password 
users=(fbase mc algo oracle root)
#the suffix of the file that will be handle
suffix=(xml ini cfg)
#get current ip address 
newIP=$(/sbin/ifconfig eth0 | grep 'inet addr:'| grep -v '127.0.0.1'| cut -d: -f2 | awk '{ print $1}')
#old ip address
oldIP=192.168.159.75
#replace the old ip address with the new ip address
for i in "${!users[@]}"; do 
    printf "%s\t%s\n" "$i" "${users[$i]}"
    su - ${users[$i]} -c 'find ./workspace -regex ".*\.\(xml\|ini\|cfg\)"|xargs sed -i 's/$oldIP/$newIP/g''
done



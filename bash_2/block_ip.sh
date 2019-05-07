#!/bin/bash


is_ip_valid()
{
	if [[ $1 =~ "([0-9]{1,3}\.)+([0-9]{1,3})" ]]; then
		return 1
	fi

	return 0
}

###
# MAIN
###

if [ "$EUID" -ne 0 ]; then
	echo "Root access is needed. Run with sudo!"
	exit
fi

if [ "$#" -ne 2 ]; then
	echo "Invalid number of arguments! Expecting 2"
	echo "Usage: ./block_ip "ip_source" "duration" "
	exit
fi

source_file=$1
duration="$(( 60 * $2 ))"

# check if duration is valid number
if [[ $duration =~ "[0-9]+" ]]; then
	echo "Duration is not a number"
	exit
fi

ipset_name="blacklist"

readarray ip_list < $source_file

# create ipset named blacklist, default no timeout
ipset create -exist $ipset_name hash:ip hashsize 4096 timeout 0

for ip in "${ip_list[@]}"
do
	if is_ip_valid $ip; then
		echo "adding $ip"
		ipset -exist add $ipset_name $ip timeout $duration
	fi
done

# set iptables using the created ipset
iptables -F
iptables -I INPUT 1 -m set -j DROP --match-set $ipset_name src
iptables -I FORWARD 1 -m set -j DROP --match-set $ipset_name src

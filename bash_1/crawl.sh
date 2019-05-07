#!/bin/bash


get_main_domain()
{
	result_main_domain="`echo $1 | sed -e 's|^[^/]*//||' -e 's|/.*$||' | sed 's/.*\.\(.*\..*\)/\1/'`"
	echo $result_main_domain
}

###
# MAIN
###

if [ "$#" -ne 2 ]; then
	echo "Invalid number of arguments! Expecting 2"
	echo "Usage: ./crawl "URL" "keyword" "
	exit
fi

website_address=$1
search_word=$2

curl_result="`curl -s $website_address`"

words_found="`echo $curl_result | grep -Eoi $search_word`"

echo $website_address: $words_found

# get <a href> tag to extract the URL, assign it to an array
hyperlinks=(`echo $curl_result | grep -Eoi '<a [^>]+>' | grep -Eoi 'href="[^\"]+"' | grep -Eoi '(http|https)://[^"]+'`)

website_domain="`get_main_domain $website_address`"

# iterate over the hypelinks and recursively crawl the subsequent URL
for link in "${hyperlinks[@]}"
do
	#get parent URL
	parent_domain="`get_main_domain $link`"

	# pass if it is the same domain as the parent to avoid endless loop
	if [ $parent_domain != $website_domain ]; then
		$0 $link $search_word
	fi
done

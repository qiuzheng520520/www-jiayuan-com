#!/bin/sh


start_no=203436725
export LANG=en_us.utf-8
num=$start_no

main()
{
   while true
   do
		file_name="$num""_10000.txt"
		echo "id  |  昵称 |  省  | 市  | 年龄  |  身高  |   婚姻状况" > $file_name
		for i in {1..10000}
		do 
			num=`expr $start_no + $i`
			result_data=`curl -i -s "http://www.jiayuan.com/$num" | tr '\n' ' ' | tr '\r' ' ' | sed -E "s/member_layer_con/\n/g" | sed -n 2p | sed -E "s/member_btn1/\n/g" | sed -n 1p | sed "s/<[^>]*//g" | awk -F'>' '{print $3,$5,$6,$7,$8}'  | sed "s/，/ /g"`
			if [ -z "$result_data"];then
				num=`expr $num + 1`
				continue
			fi
			echo "$num $result_data"
			echo "$num $result_data" >> $file_name
			num=`expr $num + 1`
			#exit
		done
   done

}

main










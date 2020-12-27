list=(a b c d e f g h i j k l m n o p q r s t u v w x y z)
wordlist=0
word=aa
for var in ${list[@]} ; do
	touch $var.txt
	cat /usr/share/dict/words | sort | grep ^$var > $var.txt
	current=$( cat $var.txt | wc -w )
	if [ $current -gt $wordlist ] ; then
		wordlist=$current
		word=$var
	fi
done
echo $word
cat $word.txt | head -n 20

i=72
for f in *; do
	if [[ -d $f ]]; then		
        	# $f is a directory
		cd "$f"
		echo "I am in $f"
		mv prr45.dat ../prr45_$i.dat
		((i++))
		cd ..
	fi
done

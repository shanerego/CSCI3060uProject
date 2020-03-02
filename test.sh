

cp output.exe testing/output.exe

	# echo $i
for i in $(find testing/input/ -name "*.inp"); do
    base=${i##*/}
    testname=${base%.*}

    echo running test: $testname

    testing/output.exe -testmode testing/output/$testname.fout < "$i" > testing/output/$testname.cout
    if [ -e testing/output/$testname.fout ] 
    then
        diff testing/output/$testname.fout testing/expectedoutput/$testname.fexp
    fi
done

    # echo | ./output.exe -testmode output/$trans$transfile.fout < $t

    # compare output files


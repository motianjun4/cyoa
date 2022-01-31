make clean
make all
cat testcases.txt |grep cyoa | xargs -L 1 -I {} bash -c "./{}" 
gcov -b page.cpp path.cpp story.cpp cyoa-step1.cpp cyoa-step2.cpp cyoa-step3.cpp cyoa-step4.cpp> covresult.txt

lcov -d . -c -o covinfo
lcov --extract covinfo "$PWD/*" -o covinfo_filtered
genhtml -o docs covinfo_filtered
echo ""
echo "---------------------------"
echo "coverage result in covresult.txt"
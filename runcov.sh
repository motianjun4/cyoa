make all
cat testcases.txt |grep cyoa | xargs -L 1 -I {} bash -c "./{}" 
gcov page.cpp path.cpp story.cpp cyoa-step1.cpp cyoa-step2.cpp cyoa-step3.cpp cyoa-step4.cpp> covresult.txt
echo ""
echo "---------------------------"
echo "coverage result in covresult.txt"
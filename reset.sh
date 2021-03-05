git log -5 --pretty=oneline
while read -p "Enter Anything to reset" num
do
    echo "-------Begin-------"
    git reset --hard HEAD
    echo "--------End--------"   
done

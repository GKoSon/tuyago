::#!/bin/bash 注释 暂时有问题CMD不能到git里面来
echo "-------Begin[writed commit.txt]-------"
git log -5 --pretty=oneline
git status
git add .
git status
read -p "start:" num
git commit -F commit.txt
git push -u origin master
git log -5 --pretty=oneline
echo "--------End--------"
read -p "goodbye" num
@echo off
chcp 65001>nul
title Baggage Consignment Calculator Test

echo 1.清理文件
if exist htmlcov (
	echo 清理htmlcov文件
	rmdir /s/q htmlcov
) else (
echo 不存在htmlcov文件
)
if exist ".coverage" (
	echo 清理.coverage文件
	del .coverage
) else (
echo 不存在.coverage文件
)
echo 2.安装所需模块
pip install -r requirements.txt

echo 3.运行测试和覆盖率检测
coverage run test.py

echo 4.生成覆盖率检测报告
coverage html

echo 5.打开报告
start ./htmlcov/index.html
pause
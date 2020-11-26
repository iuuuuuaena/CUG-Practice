@echo off
chcp 65001>nul
title Baggage Consignment Calculator Backend
pip install -r requirements.txt
start http://localhost:5000
python app.py
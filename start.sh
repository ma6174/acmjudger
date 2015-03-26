#!/bin/bash
sudo kill `ps aux | egrep "^nobody .*? protect.py" | awk '{print $2}'`
sudo nohup python protect.py &

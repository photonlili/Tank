# !/bin/sh
ps -o pid,comm | grep -i tank | awk '{print $0}'

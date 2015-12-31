# !/bin/sh
kill -9 $(ps -o pid,comm | grep -i tank | awk '{print $1}')

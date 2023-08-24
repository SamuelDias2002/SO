#/bin/bash
if [ $# -lt 1 ]; then echo "usage ./1.sh <string>"; exit 1; fi
while [ 1 ]; do 
  echo $1
  sleep 2
done

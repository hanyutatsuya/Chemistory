db2 connect to kea00db user db2inst1 using db2inst1

DATE=`date +"%Y%m%d%H%M%S"`
db2look -m -d kea00db -i db2inst1 -w db2inst1 -t IRAI KEKKA KENORDER REALCHK -o db2look_${DATE}.txt

db2 terminate

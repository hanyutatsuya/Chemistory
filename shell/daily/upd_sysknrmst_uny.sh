#!/bin/sh
#######################################################################
# ‰^—pƒtƒ‰ƒOÝ’è
# $1 : ‰^—pƒtƒ‰ƒO(1or0)
# $2 : DB–¼
# $3 : ƒ†[ƒU–¼
# $4 : ƒpƒXƒ[ƒh
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 connect to $2 user $3 using $4
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ‚c‚aÚ‘±‚ÉŽ¸”s‚µ‚Ü‚µ‚½" >> $LOG_DIR/$NAME_ERRLOG"upd_sysknrmst_uny.log"
    exit 1
fi

db2 "UPDATE SYSKNRMST SET UNYFLG = '$1'";
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ‰^—pƒtƒ‰ƒO‚ÌÝ’è‚ÉŽ¸”s‚µ‚Ü‚µ‚½" >> $LOG_DIR/$NAME_ERRLOG"upd_sysknrmst_uny.log"
    exit 1
fi

db2 terminate

exit 0

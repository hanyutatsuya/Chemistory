#!/bin/bash -

/usr/bin/rsh 10.1.181.41 /usr/bin/sudo /bin/umount  /apdata/today/file/KEA00/kea00ap
/usr/bin/rsh 10.1.181.41 /usr/bin/sudo /bin/umount  /apdata/aplog/DBOUT
/usr/bin/rsh 10.1.181.41 /bin/df -k >> IA_umount.log
echo "" >> IA_umount.log

/usr/bin/rsh 10.1.181.42 /usr/bin/sudo /bin/umount  /apdata/today/file/KEA00/kea00ap
/usr/bin/rsh 10.1.181.42 /usr/bin/sudo /bin/umount  /apdata/aplog/DBOUT
/usr/bin/rsh 10.1.181.42 /bin/df -k >> IA_umount.log
echo "" >> IA_umount.log

/usr/bin/rsh 10.1.181.43 /usr/bin/sudo /bin/umount  /apdata/today/file/KEA00/kea00ap
/usr/bin/rsh 10.1.181.43 /usr/bin/sudo /bin/umount  /apdata/aplog/DBOUT
/usr/bin/rsh 10.1.181.43 /bin/df -k >> IA_umount.log
echo "" >> IA_umount.log

/usr/bin/rsh 10.1.181.44 /usr/bin/sudo /bin/umount  /apdata/today/file/KEA00/kea00ap
/usr/bin/rsh 10.1.181.44 /usr/bin/sudo /bin/umount  /apdata/aplog/DBOUT
/usr/bin/rsh 10.1.181.44 /bin/df -k >> IA_umount.log
echo "" >> IA_umount.log

#! /bin/bash

/usr/bin/find /tmp -mtime +7 -name 'MD102*' -exec /usr/bin/rm {} \; > /dev/null 2>&1
/usr/bin/find /tmp -mtime +7 -name 'A00_*' -exec /usr/bin/rm {} \; > /dev/null 2>&1


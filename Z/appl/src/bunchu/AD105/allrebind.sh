#!/bin/bash -

db2 connect to $1 user $2 using $3

if [ $? -gt 0 ]; then
    exit 1
fi

for bnd in ./*.bnd; do
    echo $bnd
    echo rebind package `basename $bnd .bnd`
    db2 rebind package `basename $bnd .bnd`
    if [ $? -gt 0 ]; then
        exit 1
    fi
done

db2 terminate


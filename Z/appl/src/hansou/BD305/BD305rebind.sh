#!/bin/bash
db2 connect to kea00db9 user kea00dbt using kea00dbt
db2 rebind BD305_01
db2 terminate

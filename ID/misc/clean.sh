#!/bin/bash
touch clean.sql
 > clean.sql
for user in $(compgen -u)
do
echo "DROP DATABASE \"$user\";" >> clean.sql
echo "DROP USER \"$user\";" >> clean.sql
done


#!/bin/bash
touch commands.sql
touch hasla.sql
 > commands.sql
 > hasla.sql
for user in $(ls /home)
do
rand=$(openssl rand -hex 8)
echo "$user:$rand" >> hasla.sql
echo "CREATE USER \"$user\" WITH PASSWORD '$rand';" >> commands.sql
echo "CREATE DATABASE \"$user\" OWNER \"$user\";" >> commands.sql
done
sudo -H -u postgres bash -c 'psql < commands.sql'

#!/usr/bin/env bash
db="personnel"

docker compose exec db /bin/bash -c "mysqldump -u root -p --set-gtid-purged=OFF $db > /root/$db.sql || exit 1" || exit 1
docker compose cp db:/root/$db.sql ./$db.sql

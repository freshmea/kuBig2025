#!/bin/bash
# sudo chmod +x mydaemon.sh
mkdir -p /var/log/mydaemon

while true; do
    date >> /var/log/mydaemon/system_info.log
    uptime >> /var/log/mydaemon/system_info.log
    echo "-------------------------" >> /var/log/mydaemon/system_info.log
    sleep 5
done

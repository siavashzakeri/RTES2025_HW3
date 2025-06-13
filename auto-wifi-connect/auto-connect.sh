#!/bin/bash

SSID="Siavash"
PASSWORD="sia12345"
IFACE="wlan0"
LOGFILE="/var/log/auto-connect.log"

echo "$(date +"%Y-%m-%d %H:%M:%S") : auto-wifi.sh STARTED by Cron" >> "$LOGFILE"

timestamp() { date +"%Y-%m-%d %H:%M:%S"; }

CURRENT=$(/usr/bin/nmcli -t -f active,ssid dev wifi | awk -F: '$1=="yes"{print $2}')

if [[ "$CURRENT" != "$SSID" ]]; then
    echo "$(timestamp) : Not on '$SSID' (was '${CURRENT:-none}'). Reconnecting…" >> "$LOGFILE"
    /usr/bin/nmcli dev wifi connect "$SSID" password "$PASSWORD" ifname "$IFACE" >>"$LOGFILE" 2>&1
    RET=$?
    if [[ $RET -eq 0 ]]; then
        echo "$(timestamp) : Connected to '$SSID'." >> "$LOGFILE"
    else
        echo "$(timestamp) : Connection FAILED (code $RET)." >> "$LOGFILE"
    fi
else
    echo "$(timestamp) : Already on '$SSID'." >> "$LOGFILE"
fi

/usr/bin/nmcli -f SSID,SIGNAL dev wifi list | head -n 7 >>"$LOGFILE" 2>&1
echo "----------------------------------------" >> "$LOGFILE"


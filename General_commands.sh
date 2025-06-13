#!/bin/bash

#wifi ans ssh connection

sudo nmcli dev wifi connect "Siavash" password "sia12345" ifname wlan0

nmcli device status

nmcli dev wifi list

ip a show wlan0 | grep inet

ping -c 3 8.8.8.8

sudo systemctl enable --now ssh

ssh-keygen -t ed25519 -C "orangepi@$(hostname)"

cat ~/.ssh/id_ed25519.pub

git clone git@github.com:Mah-De/RTES2025_HW3.git

#automatic wifi connection

cd RTES2025_HW3

cd auto-wifi-connect
 
nano auto-connect.sh

chmod +x auto-wifi.sh

sudo touch /var/log/auto-connect.log

sudo chmod 644 /var/log/auto-connect.log

sudo crontab -e

tail -n 20 /var/log/auto-connect.log

#IPC

#FIFO


cd ~/RTES2025_HW3/

cd ipc

nano fifo-reader.sh
 
nano fifo-writer.sh
  
chmod +x fifo-reader.sh

chmod +x fifo-writer.sh
  
./fifo-reader.sh
  
./fifo-writer.sh

#linux signals

nano signal-sender.cpp

nano signal-receiver.cpp

g++ -std=c++17 signal-sender.cpp   -o signal-sender

g++ -std=c++17 signal-receiver.cpp -o signal-receiver

./signal-sender

./signal-receiver

#shared memory

nano shm-reader.cpp
 
nano shm-writer.cpp

g++ -std=c++17 -O2 shm-writer.cpp -o shm-writer -lrt

g++ -std=c++17 -O2 shm-reader.cpp -o shm-reader -lrt

./shm-writer

./shm-reader

#web server

cd ~/RTES2025_HW3/simple-web-server

nano simple-web-server.sh

chmod +x simple-web-server.sh

./simple-web-server.sh

sudo systemctl enable --now simple-web-server

sudo systemctl status simple-web-server --no-pager -l

journalctl -u simple-web-server -f






  
  
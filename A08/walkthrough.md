~/reverse $ make
~/reverse $ sudo insmod reverse.ko
~/reverse $ dmesg | tail -10
[    2.311067] dmesg (72) used greatest stack depth: 12632 bytes left
[    2.892023] udevd[197]: Starting systemd-udevd version 257.3
[    2.935504] udevd[198]: Using default interface naming scheme 'v257'.
[    3.094771] e1000 0000:00:03.0 enp0s3: renamed from eth0
[    3.576860] Adding 2097148k swap on /dev/sda3.  Priority:1 extents:1 across:2097148k 
[    3.634914] EXT4-fs (sda4): re-mounted b4d903e0-5961-41e9-b8ca-3feff5a7b0cd.
[    3.803818] EXT4-fs (sda4): re-mounted b4d903e0-5961-41e9-b8ca-3feff5a7b0cd r/w.
[    3.852718] EXT4-fs (sda2): mounted filesystem 66e69e5f-db59-4298-aff6-c4926247c4a9 r/w with ordered data mode. Quota mode: none.
[    4.593746] e1000: enp0s3 NIC Link is Up 1000 Mbps Full Duplex, Flow Control: RX
[  104.742931] reverse: loading out-of-tree module taints kernel.
/home/login/reverse # echo "123" > /dev/reverse 
/home/login/reverse # cat /dev/reverse 

321/home/login/reverse #
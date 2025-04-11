
~/debugfs $ mount | grep debugfs
~/debugfs $ sudo mount -t debugfs none /sys/kernel/debug
~/debugfs $ sudo /usr/sbin/insmod debugfs_files.ko
~/debugfs $ sudo ls /sys/kernel/debug/fortytwo
foo  id  jiffies
/home/login/debugfs # echo "1234" > /sys/kernel/debug/fortytwo/id
bash: echo: write error: Invalid argument
/home/login/debugfs # cat /sys/kernel/debug/fortytwo/id
login
/home/login/debugfs # ls -al /sys/kernel/debug/fortytwo/foo
-rw-r--r-- 1 login login 0 Apr  8 22:50 /sys/kernel/debug/fortytwo/foo
/home/login/debugfs # echo "test" > /sys/kernel/debug/fortytwo/foo
/home/login/debugfs # cat /sys/kernel/debug/fortytwo/foo
test
~/debugfs $ echo "test" > /sys/kernel/debug/fortytwo/foo
-bash: /sys/kernel/debug/fortytwo/foo: Permission denied
~/debugfs $ sudo bash mutex_test.sh
Starting writes...
Operations complete
Final content of foo
foo2
~/debugfs $  dmesg | grep "foo_mutex"
[ 4829.939491] Attempting to lock foo_mutex...
[ 4829.939499] foo_mutex locked.
[ 4829.939501] Write complete, unlocking foo_mutex...
[ 4829.939503] foo_mutex unlocked.
[ 4977.904932] Attempting to lock foo_mutex...
[ 4977.904945] foo_mutex locked.
[ 4977.904947] Write complete, unlocking foo_mutex...
[ 4977.904948] foo_mutex unlocked.
[ 4978.016995] Attempting to lock foo_mutex...
[ 4978.017003] foo_mutex locked.
[ 4978.017006] Write complete, unlocking foo_mutex...
[ 4978.017008] foo_mutex unlocked.

// Testing acces rights 

~/debugfs $ sudo mount -o remount,mode=0777 -t debugfs none /sys/kernel/debug
~/debugfs $  echo 1 > /sys/kernel/debug/fortytwo/id
-bash: echo: write error: Invalid argument
~/debugfs $ cat /sys/kernel/debug/fortytwo/id
login
~/debugfs $ cat /sys/kernel/debug/fortytwo/jiffies 
4300076739
~/debugfs $ cat /sys/kernel/debug/fortytwo/foo
foo2
~/debugfs $ echo "test"> /sys/kernel/debug/fortytwo/foo
-bash: /sys/kernel/debug/fortytwo/foo: Permission denied
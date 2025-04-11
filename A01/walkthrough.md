## Kernel

- Retrieve the latest version on the oficial linux repo https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git

`
~ $ GIT_SSL_CAINFO=/etc/ssl/certs/ca-bundle.crt git clone --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
~ $ cd linux/
~/linux $ make defconfig
~/linux $ vim .config 
~/linux $ make -j$(nproc)
~/linux # make modules
~/linux # make modules_install
~/linux # make install
~/linux # cp arch/x86/boot/bzImage /boot/vmlinuz-6.15.0
~/linux # cp System.map /boot/System.map-6.15.0
~/linux # cp .config /boot/config-6.15.0
~/linux # grub-mkconfig -o /boot/grub/grub.cfg
`

## Creating the module

https://docs.redhat.com/fr/documentation/red_hat_enterprise_linux/9/html/managing_monitoring_and_updating_the_kernel/proc_compiling-custom-kernel-modules_managing-kernel-modules#proc_compiling-custom-kernel-modules_managing-kernel-modules

// Create the source code (main.c) and the makefile to compile

`
~/linux $ make
~/linux $ sudo /usr/sbin/insmod main.ko
~/linux $  dmesg -T | tail -1
[Tue Apr  8 15:27:57 2025] Hello world!
~/linux $ sudo /usr/sbin/rmmod main
~/linux $  dmesg -T | tail -1
[Tue Apr  8 15:28:19 2025] Cleaning up module.
`
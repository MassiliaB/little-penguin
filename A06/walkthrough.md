https://www.kernel.org/doc/html/v4.14/process/2.Process.html

~ $ GIT_SSL_CAINFO=/etc/ssl/certs/ca-bundle.crt git clone --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/next/linux-next.git
~ $ cd linux-next/
~/usr/src/linux-next $ make defconfig
~/usr/src/linux-next $ vim .config 
~/usr/src/linux-next $ make -j$(nproc)
~/usr/src/linux-next # make modules
~/usr/src/linux-next # make modules_install
~/usr/src/linux-next # make install
~/usr/src/linux-next # cp arch/x86/boot/bzImage /boot/vmlinuz-6.15.0
~/usr/src/linux-next # cp System.map /boot/System.map-6.15.0
~/usr/src/linux-next # cp .config /boot/config-6.15.0
~/usr/src/linux-next # grub-mkconfig -o /boot/grub/grub.cfg
`
// On reboot
~ $ uname -r
6.15.0-rc1-next-20250408
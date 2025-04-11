// Ouvrir le makefile du noyau de l'assignement00

```
~/usr/src/linux $ vim /usr/src/linux/Makefile
EXTRAVERSION = -thor_kernel
~/usr/src/linux # make menuconfig
~/usr/src/linux # make -j$(nproc)
~/usr/src/linux # make modules_install && make install
~/usr/src/linux # cp arch/x86/boot/bzImage /boot/vmlinuz-6.15.0-thor_kernel
cp System.map /boot/System.map-6.15.0-thor_kernel
cp .config /boot/config-6.15.0-thor_kernel
~/usr/src/linux # grub-mkconfig -o /boot/grub/grub.cfg
~/usr/src/linux # /usr/local/bin/git diff Makefile
diff --git a/Makefile b/Makefile
index 38689a0c3..686204b61 100644
--- a/Makefile
+++ b/Makefile
@@ -2,7 +2,7 @@
 VERSION = 6
 PATCHLEVEL = 15
 SUBLEVEL = 0
-EXTRAVERSION = -rc1
+EXTRAVERSION = -thor_kernel
 NAME = Baby Opossum Posse
```
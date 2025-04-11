## Gestion des Devices par le kernel

https://static.lwn.net/images/pdf/LDD3/ch14.pdf

  Hotplug : Le terme hotplug désigne la capacité d'un système d'exploitation à détecter l'ajout ou le retrait d'un périphérique sans nécessiter de redémarrage. Cela concerne généralement les périphériques USB, les cartes réseau, les disques durs externes, etc.

    udev : udev est le gestionnaire de périphériques sur Linux. Il est responsable de la gestion dynamique des périphériques qui apparaissent et disparaissent (comme les périphériques USB). Lorsqu'un périphérique est ajouté au système, udev exécute des règles définies dans des fichiers de configuration pour effectuer des actions spécifiques, telles que le chargement de modules noyau ou l'attribution de noms spécifiques aux périphériques.

    Modules noyau : Un module noyau est un morceau de code qui peut être ajouté au noyau Linux pour étendre ses fonctionnalités. Par exemple, vous pouvez écrire un module noyau pour interagir avec un périphérique matériel, comme un clavier USB. Un module peut être chargé au démarrage ou en réponse à un événement matériel, comme l'ajout d'un périphérique.

    Gestion des périphériques USB sous Linux : Lorsqu'un périphérique USB est connecté, il est détecté par le noyau, qui crée un fichier de périphérique dans /dev/ (par exemple, /dev/usbkbd pour un clavier USB). Si vous avez écrit un module pour gérer ce périphérique, vous pouvez configurer le système pour charger automatiquement ce module lorsque le périphérique est branché.



`
~ $ cat /etc/udev/rules.d/00-usb-keyboards.rules
SUBSYSTEM=="usb", ATTR{bInterfaceClass}=="03", ATTR{bInterfaceProtocol}=="01", ACTION=="add", RUN+="/usr/sbin/insmod /home/login/keyboad_module/usb_kbd_detector.ko"
`
- SUBSYSTEM=="usb"	USB device	Cible uniquement les périphériques USB
- bInterfaceClass=="03"	HID	Human Interface Device (souris, clavier...)
- bInterfaceProtocol=="01"	Keyboard	Spécifiquement un clavier USB

`
~/keyboard_module $ udevadm monitor --udev
~ $ dmesg | tail -1
[ 7444.046314] [usb_kbd_detector] Module de clavier USB retiré.
`
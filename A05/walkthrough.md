## Les fichiers /dev

Ces fichiers ne sont pas des fichiers "normaux", mais des fichiers de périphériques, associés à des pilotes (drivers) dans le noyau.

Character devices (périphériques de type caractère)
    - Transmission caractère par caractère (ou octet par octet).
    - Lecture/écriture séquentielle.
    Exemples : /dev/tty, /dev/zero, /dev/null, /dev/input/eventX, /dev/mouse

Block devices (périphériques de type bloc)
    - Transmission par blocs (souvent 512 octets ou plus)
    - Accès aléatoire aux données (seek, etc)
    Exemples : /dev/sda, /dev/mmcblk0, /dev/loop0

Un character device est un périphérique qui transmet des données en flux de caractères, comme une liaison série, un clavier, ou même un device virtuel que tu crées toi-même.
C’est géré dans le noyau par un driver qui implémente les opérations de fichier classiques :
open(), read(), write(), ioctl(), etc.

Un fichier comme /dev/mon_device est en fait un pont entre :
    - l’espace utilisateur (user space), via les appels système (read, write, etc.),
    - et un driver dans le noyau, qui fait le vrai boulot.

Dans le noyau Linux, il y a 2 grandes façons de créer un device de type "caractère". 
- Classique / manuel
Allouer un numero majeur/mineur, enregistrer ton struc cdev, creer une entrée dans dev, creer la classe dans sysfs

- Avec miscdevice
Tu laisse le noyau gerer tout ca pour toi
Tu rempli une struct miscdevice
Tu l'enregistre avec misc_register()
Et tu as automatiquement une entrée dans /dev/nom
Le numéro majeur indique quel driver doit gérer ce périphérique.
Le numéro mineur permet de différencier plusieurs instances (ex: /dev/tty0, /dev/tty1, etc)

`
~/misc_device $ vim misc_device.c
~/misc_device $ make
~/misc_device $ sudo insmod misc_device.ko
~ #  echo "$(cat /dev/fortytwo)"
login
~ # echo -n "test" | cat > /dev/fortytwo
cat: write error: Invalid argument
~ # echo -n "login" | cat > /dev/fortytwo
`
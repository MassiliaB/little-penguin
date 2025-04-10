#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init usb_kbd_detector_init(void)
{
    printk(KERN_INFO "[usb_kbd_detector] Clavier USB détecté et module inséré.\n");
    return 0;
}


static int __exit usb_kbd_detector_exit(void)
{
    printk(KERN_INFO "[usb_kbd_detector] Module de clavier USB retiré.\n");
    return 0;
}

module_init(usb_kbd_detector_init);
module_exit(usb_kbd_detector_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module de détection de clavier USB");

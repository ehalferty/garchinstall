print("Hello, world!");
system("mkdir /mnt/installer-root");
system("mount -t tmpfs -o size=4g tmpfs /mnt/installer-root");
system("pacstrap /mnt/installer-root base linux");
system("arch-chroot /mnt/installer-root pacman -Syu");
system("arch-chroot /mnt/installer-root pacman -Sy glib2 pango --noconfirm");

# TODO: Check if we have network connectivity. If not, run the framebuffer-based network manager
# TODO: Throw up a splash screen to tell the user that we're downloading dependencies...
# system("mkdir /mnt/installer-root");
# system("mount -t tmpfs -o size=4g tmpfs /mnt/installer-root");
# system("pacstrap /mnt/installer-root base linux");
# system("arch-chroot /mnt/installer-root pacman -Syu");
# system("arch-chroot /mnt/installer-root pacman -Sy xorg xfce4 xorg-xinit xorg-xeyes xf86-video-fbdev xorg-server xf86-video-vmware --noconfirm");
# system("arch-chroot /mnt/installer-root pacman -Sy xf86-video-fbdev xf86-input-evdev xf86-input-synaptics weston lightdm --noconfirm");
# system("unset DBUS_SESSION_BUS_ADDRESS");
# system("arch-chroot /mnt/installer-root systemctl enable lightdm");
# system("arch-chroot /mnt/installer-root startxfce4");
# system("/usr/bin/perl", "perl/garchinstall2.pl");

# mount -t tmpfs -o size=512m tmpfs /mnt/root1
# pacstrap /mnt/root1 base linux
# arch-chroot /mnt/root1
# pacman -Syu
# pacman -Sy gcc vim


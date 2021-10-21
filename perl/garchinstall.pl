print("Hello, world!");
system("mkdir /mnt/installer-root");
system("mount -t tmpfs -o size=4g tmpfs /mnt/installer-root");
system("pacstrap /mnt/installer-root base linux");
system("arch-chroot /mnt/installer-root");
system("pacman -Syu");
system("pacman -Sy xorg xfce4 xorg-xinit xorg-xeyes xf86-video-fbdev xorg-server xf86-video-vmware --noconfirm");
system("pacman -Sy xf86-video-fbdev xf86-input-evdev xf86-input-synaptics weston lightdm --noconfirm");
system("unset DBUS_SESSION_BUS_ADDRESS");
system("systemctl enable lightdm");
# system("startxfce4")
system("startxfce4");

# mount -t tmpfs -o size=512m tmpfs /mnt/root1
# pacstrap /mnt/root1 base linux
# arch-chroot /mnt/root1
# pacman -Syu
# pacman -Sy gcc vim


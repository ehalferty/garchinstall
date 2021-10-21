print("Hello, world!");
system("mkdir /mnt/installer-root");
print("1")
<STDIN>;
system("mount -t tmpfs -o size=4g tmpfs /mnt/installer-root");
print("2")
<STDIN>;
system("pacstrap /mnt/installer-root base linux");
print("3")
<STDIN>;
system("arch-chroot /mnt/installer-root");
print("4")
<STDIN>;
system("pacman -Syu");
print("5")
<STDIN>;
system("pacman -Sy xorg xfce4 xorg-xinit xorg-xeyes xf86-video-fbdev xorg-server xf86-video-vmware --noconfirm");
print("6")
<STDIN>;
system("pacman -Sy xf86-video-fbdev xf86-input-evdev xf86-input-synaptics weston lightdm --noconfirm");
print("7")
<STDIN>;
system("unset DBUS_SESSION_BUS_ADDRESS");
print("8")
<STDIN>;
system("systemctl enable lightdm");
# system("startxfce4")
print("9")
<STDIN>;
system("startxfce4");

# mount -t tmpfs -o size=512m tmpfs /mnt/root1
# pacstrap /mnt/root1 base linux
# arch-chroot /mnt/root1
# pacman -Syu
# pacman -Sy gcc vim


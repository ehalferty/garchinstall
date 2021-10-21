print("Loading garchinstaller...");
# Check if we have network connectivity. If not, run the framebuffer-based network manager

system("mkdir /mnt/installer-root >/dev/null 2>&1");
# print("1");
# <STDIN>;
system("mount -t tmpfs -o size=4g tmpfs /mnt/installer-root >/dev/null 2>&1");
# print("2");
# <STDIN>;
system("pacstrap /mnt/installer-root base linux >/dev/null 2>&1");
# print("3");
# <STDIN>;
# system("arch-chroot /mnt/installer-root");
# print("4");
# <STDIN>;
system("arch-chroot /mnt/installer-root pacman -Syu >/dev/null 2>&1");
# print("5");
# <STDIN>;
system("arch-chroot /mnt/installer-root pacman -Sy xorg xfce4 xorg-xinit xorg-xeyes xf86-video-fbdev xorg-server xf86-video-vmware --noconfirm >/dev/null 2>&1");
# print("6");
# <STDIN>;
system("arch-chroot /mnt/installer-root pacman -Sy xf86-video-fbdev xf86-input-evdev xf86-input-synaptics weston lightdm --noconfirm >/dev/null 2>&1");
# print("7");
# <STDIN>;
system("unset DBUS_SESSION_BUS_ADDRESS");
# print("8");
# <STDIN>;
system("arch-chroot /mnt/installer-root systemctl enable lightdm >/dev/null 2>&1");
# system("startxfce4")
# print("9");
# <STDIN>;
system("arch-chroot /mnt/installer-root startxfce4 >/dev/null 2>&1");

# mount -t tmpfs -o size=512m tmpfs /mnt/root1
# pacstrap /mnt/root1 base linux
# arch-chroot /mnt/root1
# pacman -Syu
# pacman -Sy gcc vim


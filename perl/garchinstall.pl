print("Hello, world!");
system("mkdir /mnt/installer-root");
system("mount -t tmpfs -o size=4g tmpfs /mnt/installer-root");
system("pacstrap /mnt/installer-root base linux");
system("arch-chroot /mnt/installer-root");
system("pacman -Syu");
system("pacman -Sy xfce4");

# mount -t tmpfs -o size=512m tmpfs /mnt/root1
# pacstrap /mnt/root1 base linux
# arch-chroot /mnt/root1
# pacman -Syu
# pacman -Sy gcc vim


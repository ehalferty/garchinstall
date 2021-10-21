#!/usr/bin/bash

# mkdir /mnt/installer-root
# mount -t tmpfs -o size=4g tmpfs /mnt/installer-root
# cp -r /bin /mnt/installer-root
# cp -r /boot /mnt/installer-root
# mkdir /mnt/installer-root/dev
# cp -r /etc /mnt/installer-root
# cp -r /home /mnt/installer-root
# cp -r /lib /mnt/installer-root
# cp -r /lib64 /mnt/installer-root
# mkdir /mnt/installer-root/mnt
# cp -r /opt /mnt/installer-root
# mkdir /mnt/installer-root/proc
# cp -r /root /mnt/installer-root
# cp -r /run /mnt/installer-root
# cp -r /sbin /mnt/installer-root
# cp -r /srv /mnt/installer-root
# mkdir /mnt/installer-root/sys
# cp -r /tmp /mnt/installer-root
# cp -r /usr /mnt/installer-root
# cp -r /var /mnt/installer-root
# cp -r /version /mnt/installer-root
# arch-chroot /mnt/installer-root
# pacman -Syu
# pacman -Sy which xorg xorg-xinit xorg-xeyes xorg-drivres --noconfirm

# pacstrap /mnt/installer-root base linux
# pacman -Syu
# pacman -Sy which xorg xfce4 lxde xorg-xinit \
# xorg-xeyes xorg-drivers --noconfirm

# ssh root@192.168.56.102
print("Welcome to garchinstaller!\n");

system("stty -echo");

system("echo \"12e45\n12e45\" | passwd root");

print("Increasing temporary filesystem size to 3GB (I hope you have the RAM buddy!)...\n");
system("mount -o remount,size=3G /run/archiso/cowspace");

print("Updating package list...\n");
system("pacman -Syu --noconfirm");
system("pacman -Syy");

print("Downloading & installing Xorg stuff...\n");
system("pacman -Sy mesa --noconfirm");
system("pacman -Sy gnu-free-fonts --noconfirm");
system("pacman -Sy libffi --noconfirm");
system("pacman -Sy xf86-video-fbdev --noconfirm");
system("pacman -Sy xf86-video-vmware --noconfirm");
system("pacman -Sy xf86-input-libinput --noconfirm");
system("pacman -Sy xorg-server --noconfirm");
system("pacman -Sy xorg-xinit --noconfirm");
system("pacman -Sy xorg-apps --noconfirm");
system("pacman -Sy xterm --noconfirm");
system("pacman -Sy xorg-xclock --noconfirm");

print("Downloading & installing calamares dependencies...\n");
system("pacman -Sy cmake --noconfirm");
system("pacman -Sy qt5-base --noconfirm");
system("pacman -Sy yaml-cpp --noconfirm");
system("pacman -Sy boost --noconfirm");
system("pacman -Sy kcoreaddons --noconfirm");
system("pacman -Sy extra-cmake-modules --noconfirm");

print("Starting graphics server...\n");
system("Xorg :0 -configure");
system("X -config /root/xorg.conf.new &");

print("Starting Calamares...\n");
system("cd bundle/calamares && cmake && make && make install");






# system("pacman -Sy glib2 pango gdk-pixbuf2 gtk2 gtk3 perl gtk2-perl perl-gtk3 weston --noconfirm");
# system("mkdir /mnt/installer-root");
# system("mount -t tmpfs -o size=4g tmpfs /mnt/installer-root");
# system("pacstrap /mnt/installer-root base linux");
# system("cp ./perl/garchinstall2.pl /mnt/installer-root/root/");
# system("cp ./perl/garchinstall3.pl /mnt/installer-root/root/");
# system("arch-chroot /mnt/installer-root pacman -Syu");
# system("arch-chroot /mnt/installer-root pacman -Sy glib2 pango gdk-pixbuf2 gtk2 gtk3 perl gtk2-perl perl-gtk3 weston --noconfirm");
# system("arch-chroot /mnt/installer-root perl /root/garchinstall2.pl");

# system("killall gui_server");
# print("Starting gui_server...\n");
# system("chmod +x ./bundle/gui_server");
# system("./bundle/gui_server &> /tmp/serverlog.txt &");




# system("perl -Ibundle/installer ./bundle/installer/01_language_chooser.pl");
# system("perl ./bundle/")
# TODO: gui_server should listen on a socket
# TODO: Should start sending it messages here, polling for messages here. Polled messages like.

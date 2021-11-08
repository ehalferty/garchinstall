# ssh root@192.168.56.102
print("Welcome to garchinstaller!\n");

system("stty -echo");

print("Increasing temporary filesystem size to 4GB (I hope you have the RAM buddy!)...\n");
system("echo \"12e45\n12e45\" | passwd root");
system("mount -o remount,size=4G /run/archiso/cowspace");

print("Downloading & installing a bunch of graphics packages...\n");
system("pacman -Syu --noconfirm");
system("pacman -Syy");
system("pacman -Sy libffi xf86-video-fbdev xf86-video-vmware xf86-input-libinput xorg-server xorg-xinit xorg-xclock --noconfirm");
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

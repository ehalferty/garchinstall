# Prints welcome, starts gui server

print("Welcome to garchinstaller!\n");
# system("mkdir /mnt/installer-root");
# system("mount -t tmpfs -o size=4g tmpfs /mnt/installer-root");
# system("pacstrap /mnt/installer-root base linux");
# system("cp ./perl/garchinstall2.pl /mnt/installer-root/root/");
# system("cp ./perl/garchinstall3.pl /mnt/installer-root/root/");
# system("arch-chroot /mnt/installer-root pacman -Syu");
# system("arch-chroot /mnt/installer-root pacman -Sy glib2 pango gdk-pixbuf2 gtk2 gtk3 perl gtk2-perl perl-gtk3 weston --noconfirm");
# system("arch-chroot /mnt/installer-root perl /root/garchinstall2.pl");

system("stty -echo");
system("killall gui_server");
print("Starting gui_server...\n");
system("chmod +x ./bundle/gui_server");
system("./bundle/gui_server &> /tmp/serverlog.txt &");
# system("perl -Ibundle/installer ./bundle/installer/01_language_chooser.pl");
# system("perl ./bundle/")
# TODO: gui_server should listen on a socket
# TODO: Should start sending it messages here, polling for messages here. Polled messages like.

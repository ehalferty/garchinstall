print("Downloading packages for garchinstaller... (This may take awhile)");
# TODO: Check if we have network connectivity. If not, run the framebuffer-based network manager
# TODO: Throw up a splash screen to tell the user that we're downloading dependencies...
$tmpRt = "/mnt/installer-root"
$chrt = "arch-chroot ${tmpRt}";
$pcmn = "pacman -Sy";
$dependencies = "xorg xfce4 xorg-xinit xorg-xeyes xf86-video-fbdev xorg-server xf86-video-vmware xf86-video-fbdev
    xf86-input-evdev xf86-input-synaptics weston lightdm perl-gtk3";

system("mkdir", $tmpRt, ">/dev/null 2>&1");
system("mount -t tmpfs -o size=4g tmpfs", $tmpRt, ">/dev/null 2>&1");
system("pacstrap", $tmpRt, "base linux >/dev/null 2>&1");
system($chrt, "pacman -Syu >/dev/null 2>&1");
system($chrt, $pcmn, $dependencies, "--noconfirm >/dev/null 2>&1");
system("unset DBUS_SESSION_BUS_ADDRESS");
# TODO: Remove splash screen before starting XFCE
system($chrt, "startxfce4 >/dev/null 2>&1");

use Gtk3 -init;
my $hello = Gtk3::MessageDialog->new (undef, 'modal', 'info', 'ok', "Hello world!");
$hello->set ('secondary-text' => 'This is an example dialog.');
$hello->run;


# system($chrt, "arch-chroot /mnt/installer-root pacman -Sy xorg xfce4 xorg-xinit xorg-xeyes xf86-video-fbdev xorg-server xf86-video-vmware --noconfirm >/dev/null 2>&1");
# system($chrt, "arch-chroot /mnt/installer-root pacman -Sy xf86-video-fbdev xf86-input-evdev xf86-input-synaptics weston lightdm --noconfirm >/dev/null 2>&1");
# system($chrt, "arch-chroot /mnt/installer-root systemctl enable lightdm >/dev/null 2>&1");
# system($chrt, "arch-chroot /mnt/installer-root startxfce4 >/dev/null 2>&1");

# mount -t tmpfs -o size=512m tmpfs /mnt/root1
# pacstrap /mnt/root1 base linux
# arch-chroot /mnt/root1
# pacman -Syu
# pacman -Sy gcc vim


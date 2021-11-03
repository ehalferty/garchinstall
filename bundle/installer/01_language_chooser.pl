# User selects language and langauge-region here
use IO::Socket::UNIX;

my $SOCK_PATH = "/tmp/gui_server_socket";

# foregroundColor = 0x483dc7FF, backgroundColor = 0xBCC73DFF

use constant MSG_CLEAR_SCREEN => 1;
use constant MSG_SET_FGCOLOR => 2;
use constant MSG_SET_BGCOLOR => 3;
use constant MSG_DRAW_RECT => 4;
use constant MSG_LOAD_BITMAP => 5;
use constant MSG_DRAW_BITMAP => 6;
use constant MSG_DRAW_TEXT => 7;
use constant MSG_GET_EVENTS => 8;
use constant MSG_GET_KEYS => 9;
use constant MSG_SET_CORNER_RADIUS => 10;
use constant MSG_GET_RESOLUTION => 11;

sub send_msg {
    my $client = IO::Socket::UNIX->new(Type => SOCK_STREAM(), Peer => $SOCK_PATH);
    my $len = length(@_[1]) + 5;
    my $msg = sprintf("%c%c%c%c\x01\x00%c%c%s\x00", $len & 0xFF, ($len >> 8) & 0xFF, ($len >> 16) & 0xFF,
        ($len >> 24) & 0xFF, @_[0] & 0xFF, (@_[0] >> 8) & 0xFF, @_[1]);
    print {$client} $msg;
    my $resBuff = 0;
    my $resBuffSize = 1024;
    $res = "";
    while (sysread($client, $resBuff, $resBuffSize)) { $res = $res . $resBuff; }
    close $client;
    return $res;
}

sub draw_text {
    my ($x, $y, $str) = @_;
    my $msg = sprintf("%c%c%c%c%s", $x & 0xFF, ($x >> 8) & 0xFF, $y & 0xFF, ($y >> 8) & 0xFF, $str);
    send_msg(MSG_DRAW_TEXT, $msg);
}

sub set_fg_color {
    my ($r, $g, $b) = @_;
    my $msg = sprintf("%c%c%c", $r, $g, $b);
    send_msg(MSG_SET_FGCOLOR, $msg);
}

sub set_bg_color {
    my ($r, $g, $b) = @_;
    my $msg = sprintf("%c%c%c", $r, $g, $b);
    send_msg(MSG_SET_BGCOLOR, $msg);
}

sub set_corner_radius {
    my $r = @_[0];
    my $msg = sprintf("%c", $r);
    send_msg(MSG_SET_CORNER_RADIUS, $msg);
}

sub draw_rect {
    my ($x, $y, $w, $h) = @_;
    my $msg = sprintf("%c%c%c%c%c%c%c%c", $x & 0xFF, ($x >> 8) & 0xFF, $y & 0xFF, ($y >> 8) & 0xFF,
        $w & 0xFF, ($w >> 8) & 0xFF, $h & 0xFF, ($h >> 8) & 0xFF);
    send_msg(MSG_DRAW_RECT, $msg);
}

sub draw_rounded_rect {
    my ($x, $y, $w, $h, $radius) = @_;
    set_corner_radius($radius);
    draw_rect($x, $y, $w, $h);
    set_corner_radius(0);
}

sub load_bmp { return substr(send_msg(MSG_LOAD_BITMAP, @_[0]), 8, 8); }

sub draw_bmp {
    my ($x, $y, $w, $h, $addr) = @_;
    my $msg = pack('S<4', $x, $y, $w, $h) . $addr;
    my $r1 = send_msg(MSG_DRAW_BITMAP, $msg);
    return $r1;
}

sub get_events {
    return send_msg(MSG_GET_EVENTS, "");
}

sub get_resolution {
    my @r = split(send_msg(MSG_GET_RESOLUTION, ""));
    my $x = ord($r[0]) + (ord($r[1]) << 8);
    my $y = ord($r[2]) + (ord($r[3]) << 8);
    return ($x, $y);
}


my ($screen_width, $screen_height) = get_resolution();
printf("$screen_width=${screen_width} $screen_height=${screen_height}\n");
exit 1;

set_fg_color(0, 50, 200);
draw_rect(0, 400, 100, 50);
set_fg_color(90, 0, 128);
draw_rounded_rect(100, 400, 100, 50, 10);

draw_text(100, 100, "Hello, world!");
my $arch_logo_ref = load_bmp("bundle/images/archlogo65.png");
# print "Return val from load_bmp:\n";
# print map { sprintf '%02X ', ord } split //, $arch_logo_ref;
# print "\n";
draw_bmp(150, 150, 65, 65, $arch_logo_ref);
# print "Done?\n";
# print "\n";
my $events = 0;
while (1) {
    $events = get_events();
    print map { sprintf '%02X ', ord } split //, $events;
    print "\n";
}

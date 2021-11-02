# User selects language and langauge-region here
use IO::Socket::UNIX;

my $SOCK_PATH = "/tmp/gui_server_socket";

use constant MSG_CLEAR_SCREEN => 1;
use constant MSG_SET_FGCOLOR => 2;
use constant MSG_SET_BGCOLOR => 3;
use constant MSG_DRAW_RECT => 4;
use constant MSG_LOAD_BITMAP => 5;
use constant MSG_DRAW_BITMAP => 6;
use constant MSG_DRAW_TEXT => 7;
use constant MSG_GET_EVENTS => 8;

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

sub draw_rect {
    my ($x, $y, $w, $h) = @_;
    my $msg = sprintf("%c%c%c%c%c%c%c%c", $x & 0xFF, ($x >> 8) & 0xFF, $y & 0xFF, ($y >> 8) & 0xFF,
        $w & 0xFF, ($w >> 8) & 0xFF, $h & 0xFF, ($h >> 8) & 0xFF);
    send_msg(MSG_DRAW_RECT, $msg);
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

draw_rect(0, 400, 400, 10);
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
}

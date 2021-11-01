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

sub send_msg {
    my $client = IO::Socket::UNIX->new(Type => SOCK_STREAM(), Peer => $SOCK_PATH);
    my $len = length(@_[1]) + 5;
    printf("Sending a message with len=%d\n", $len);
    my $msg = sprintf("%c%c%c%c\x01\x00%c%c%s\x00", $len & 0xFF, ($len >> 8) & 0xFF, ($len >> 16) & 0xFF,
        ($len >> 24) & 0xFF, @_[0] & 0xFF, (@_[0] >> 8) & 0xFF, @_[1]);
    print map { sprintf '%02X ', ord } split //, $msg;
    print "\n";
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

sub load_bmp { return send_msg(MSG_LOAD_BITMAP, @_[0]); }

sub draw_bmp {
    my ($x, $y, $addr) = @_;
    my $msg = sprintf("%c%c%c%c%c%c%c%c%c%c%c%c", $x & 0xFF, ($x >> 8) & 0xFF, $y & 0xFF, ($y >> 8) & 0xFF,
        $addr & 0xFF, ($addr >> 8) & 0xFF, ($addr >> 16) & 0xFF, ($addr >> 24) & 0xFF,
        ($addr >> 32) & 0xFF, ($addr >> 40) & 0xFF, ($addr >> 48) & 0xFF, ($addr >> 56) & 0xFF);
    return send_msg(MSG_DRAW_BITMAP, $msg);
}

draw_rect(0, 400, 400, 10);
draw_text(100, 100, "Hello, world!");
my $arch_logo_ref = load_bmp("bundle/images/archlogo65.png");
print "===\n";
print map { sprintf '%02X ', ord } split //, $arch_logo_ref;
draw_bmp(150, 150,
    (($arch_logo_ref[8]) & 0xFF) | (($arch_logo_ref[9]) & 0xFF) |
    (($arch_logo_ref[10]) & 0xFF) | (($arch_logo_ref[11]) & 0xFF) |
    (($arch_logo_ref[12]) & 0xFF) | (($arch_logo_ref[13]) & 0xFF) |
    (($arch_logo_ref[14]) & 0xFF) | (($arch_logo_ref[15]) & 0xFF)
);
# print $arch_logo_ref
print "\n";

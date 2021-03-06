package InstallerHelpers;

use IO::Socket::UNIX;

my $SOCK_PATH = "/tmp/gui_server_socket";

use constant FONT_WIDTH => 10;
use constant FONT_HEIGHT => 16;

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

use constant MSG_2_CLEAR_SCREEN => 100;

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

sub clear_screen {
    return send_msg(MSG_CLEAR_SCREEN, "");
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

# TODO: Screen resolution > 800x600? Auto-detect and center virtual screen on actual screen.
# TODO: VERY large screen? (>1600 width, >1200 height)? Upscale 2x (or more!)
sub get_resolution {
    my ($x, $y, $bpp) = unpack('S<S<C', substr(send_msg(MSG_GET_RESOLUTION, ""), 8));
    return ($x, $y, $bpp);
}

sub get_button_dimensions {
    my ($xpadding, $ypadding, $w, $h, $text) = @_;
    my $width = ($w > 0 ? $w : length($text) * FONT_WIDTH) + $xpadding * 2;
    my $height = FONT_HEIGHT + $ypadding * 2;
    return ($width, $height);
}

sub draw_button {
    my ($x, $y, $xpadding, $ypadding, $w, $h, $text, $bgr, $bgg, $bgb, $fgr, $fgg, $fgb, $flags) = @_;
    my ($width, $height) = get_button_dimensions($xpadding, $ypadding, $w, $h, $text);
    set_fg_color($bgr, $bgg, $bgb);
    draw_rounded_rect($x, $y, $width, $height, 5);
    set_bg_color($bgr, $bgg, $bgb);
    set_fg_color($fgr, $fgg, $fgb);
    draw_text($x + $xpadding, $y + $ypadding, $text);
    return ($width, $height);
}

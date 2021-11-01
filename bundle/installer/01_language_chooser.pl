# User selects language and langauge-region here
use IO::Socket::UNIX;

my $SOCK_PATH = "/tmp/gui_server_socket";
use constant MSG_DRAW_TEXT => 7;

sub send_msg {
    my $client = IO::Socket::UNIX->new(Type => SOCK_STREAM(), Peer => $SOCK_PATH);
    my $len = length(@_[1]) + 5;
    my $msg = sprintf("%c%c%c%c\x01\x00%c%c%s\x00", $len & 0xFF, ($len >> 8) & 0xFF, ($len >> 16) & 0xFF,
        ($len >> 24) & 0xFF, @_[0] & 0xFF, (@_[0] >> 8) & 0xFF, @_[1]);
    print map { sprintf '%02X ', ord } split //, $msg;
    print {$client} $msg;
    my $res = scalar <$client>;
    # print "Got reponse: ", scalar <$client>; print "\n";
    close $client;
}

sub draw_text {
    my $x = @_[0];
    my $y = @_[1];
    my $str = @_[2];
    my $msg = sprintf("%c%c%c%c%s", $x & 0xFF, ($x >> 8) & 0xFF, $y & 0xFF, ($y >> 8) & 0xFF, $str);
    send_msg(MSG_DRAW_TEXT, $msg);
}

# send_msg(MSG_DRAW_TEXT, "\x15\x00\x15\x00ABCD");
draw_text(100, 100, "Hello, world!");

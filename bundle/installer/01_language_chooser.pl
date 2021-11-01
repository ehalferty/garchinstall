# User selects language and langauge-region here
use IO::Socket::UNIX;

my $SOCK_PATH = "/tmp/gui_server_socket";
use constant MSG_DRAW_TEXT => 7;

sub send_msg {
    my $client = IO::Socket::UNIX->new(Type => SOCK_STREAM(), Peer => $SOCK_PATH);
    my $len = length(@_[1]) + 5;
    printf("len=%d\n", $len);
    my $msg = sprintf(
        "%c%c%c%c\x01\x00%c%c%s\x00",
        $len & 0xFF,
        ($len >> 8) & 0xFF,
        ($len >> 16) & 0xFF,
        ($len >> 24) & 0xFF,
        @_[0] & 0xFF,
        (@_[0] >> 8) & 0xFF,
        @_[1]
    );
    printf("msg=%s\n", $msg);
    # print "$msg=" . $msg . "\n";
    print {$client} $msg;



    # print {$client} '\x03\x00\x00\x00\x01\x00\x01';
    # print {$client} "\x0B\x00\x00\x00\x01\x00\x05\x00\x05\x00ABCD\x00";
    # print {$client} "\x0B\x00\x00\x00\x01\x00\x05\x00\x05\x00" . @_[1] . "\x00";
    print "Got reponse: ", scalar <$client>;
    print "\n";
    close $client;
}

send_msg(MSG_DRAW_TEXT, "\x15\x00\x15\x00ABCD");

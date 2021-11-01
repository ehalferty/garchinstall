# User selects language and langauge-region here
use IO::Socket::UNIX;

my $SOCK_PATH = "/tmp/gui_server_socket";
use constant MSG_DRAW_TEXT => 7;

sub send_msg {
    my $client = IO::Socket::UNIX->new(Type => SOCK_STREAM(), Peer => $SOCK_PATH);
    my $msg = sprintf(
        "%c%c%c%c%s\x00",
        @_[0] & 0xFF,
        (@_[0] >> 8) & 0xFF,
        (@_[0] >> 16) & 0xFF,
        (@_[0] >> 24) & 0xFF,
        @_[1]
    );
    print {$client} $msg;



    # print {$client} '\x03\x00\x00\x00\x01\x00\x01';
    # print {$client} "\x0B\x00\x00\x00\x01\x00\x05\x00\x05\x00ABCD\x00";
    # print {$client} "\x0B\x00\x00\x00\x01\x00\x05\x00\x05\x00" . @_[1] . "\x00";
    print "Got reponse: ", scalar <$client>;
    close $client;
}

send_msg(MSG_DRAW_TEXT, "\x01\x00\x05\x00\x05\x00ABCD");

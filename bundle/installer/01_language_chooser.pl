# User selects language and langauge-region here
use IO::Socket::UNIX;
my $SOCK_PATH = "/tmp/gui_server_socket";
my $client = IO::Socket::UNIX->new(Type => SOCK_STREAM(), Peer => $SOCK_PATH);
print {$client} '\x03\x00\x00\x00\x01\x00\x01';
print "Got reponse: ", scalar <$client>;
close $client;

use Gtk3 -init;
my $hello = Gtk3::MessageDialog->new (undef, 'modal', 'info', 'ok', "Hello world!");
$hello->set ('secondary-text' => 'This is an example dialog.');
$hello->run;

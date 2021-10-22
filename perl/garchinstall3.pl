use Gtk3 -init;
my $hello = Gtk3::MessageDialog->new (undef, 'modal', 'info', 'ok', "Hello world!");
$hello->set ('secondary-text' => 'This is an example dialog.');
$hello->run;
# use Gtk2 qw/-init/;
# use Gtk2 qw/-init -threads-init/;
# use strict;     
# use warnings;   

# use Gtk2;      
# Gtk2->init;

# my $window = Gtk2::Window->new;
# my $label  = Gtk2::Label->new('Hello World!');

# $window->signal_connect('delete-event' => sub { Gtk2->main_quit });

# $window->add($label);

# $label ->show;
# $window->show;

# Gtk2->main;

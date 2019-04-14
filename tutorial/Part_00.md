## Part 0: Setting Up and Compiling

If you're a C beginner like I am, you might get into trouble trying to set up libtcod
and linking the source object to your compiler. The information you need to get this right
is a little disperse and can be hard to track down. Since I wouldn't like any of you 
to miss out on the opportunity of learning to program a roguelike in C with this great
library, I'm gonna try to go through it step by step, focusing on the parts which took
me more time to get through. Maybe I'm just an idiot, and this is all pretty obvious
for you, but whatever. This part is gonna be done from the perspective of a linux
user, so if you're using another OS you'll have to adapt it.

### Setting Up

The first thing you need to do is install all the dependencies libtcod needs to 
work. From the command line type the following:

    sudo apt-get install curl build-essential make cmake autoconf automake libtool mercurial libasound2-dev libpulse-dev libaudio-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxxf86vm-dev libxss-dev libgl1-mesa-dev libesd0-dev libdbus-1-dev libudev-dev libgles1-mesa-dev libgles2-mesa-dev libegl1-mesa-dev

Yes, that's a long list of dependencies. If your linux is as evil as mine is, you might get
some errors saying such and such package couldn't be found. Just erase them from the list and
if it recommends any replacements for them, add those. Then re enter the command, make
sure everything is nice and tidy and move on to installing SDL2. It may have a different
package name depending on your distro, mine was already installed as libsdl2-2.0 so:

    sudo apt-get install libsdl2-2.0 libsdl2-dev

I added libsdl2-dev to the command because I already had it installed, so I'm not sure
if the dev package is needed or not. Chances are you already have it installed anyways.
If these package names don't work for you, a quick google search for 'linux install sdl2'
will point you in the right direction.

Now what you need to do is get the source for libtcod, which is in github.
If you have git just type the following in the folder you want to put it.

    git clone https://github.com/libtcod/libtcod.git

If you don't use git, then go to [this repository](https://github.com/libtcod/libtcod) and
download it. Unzip it wherever you like and from that folder do the following:

    cd libtcod/build/autotools
    autoreconf -i
    ./configure CFLAGS='-O2' //that's not a letter o in '-O2' not a zero.
    make
    sudo make install

## Compiling

After you got that set up (and you might have to work through some errors specific
to your own environment) make a directory somewhere to start building your project.

    mkdir newRogue
    cd newRogue

Make a main.c file in whichever text editor or IDE you prefer and put the following in
it, just to test that libtcod is set up.

    #include <stdio.h>
    #include "libtcod.h"
    
    void main()
    {
        printf("Hello World\n");
    }

Now that you have your first file you should try compiling it. Here's where I ran into
a lot of trouble. Not being a proficient C user myself, I just tried to compile the
file like I had compile the only other project I had done with an external library.
So I did this:

    gcc -o main main.c -llibtcod //NOT THE RIGHT THING TO DO

As some of you may see already, this did not work. First of all, the lib in -llibtcod should
be skipped, apparently its already implied. Second, the headers and object files that were 
installed for libtcod did not end up in a PATH that my compiler would search, so the 
compilation would not work unless I specified the filepath to both the libtcod header files
and the libtcod shared objects, which happen to be in different folders.
Anyway, according to the README.md for building libtcod using autotools, libtcod static and
shared libraries are placed in /usr/local/lib and the header files are placed in 
/usr/local/include/libtcod. With that in mind we type:

    gcc -o main main.c -I/usr/local/include/libtcod -L/usr/local/lib -ltcod

And it should compile in a second. The -I argument is used to specify the path to include the 
headers while the -L argument is used to specify the path to the library objects. If you
type this in and the compiler still gives you an error due to not finding libtcod.h, check
if the libtcod.h file is in /usr/local/include/libtcod and if there are a bunch of libtcod.a
libtcod.o and libtcod.so files in /usr/local/lib. If not, recheck the whole installation process 
and may god have mercy on your soul, because the C compiler will not.

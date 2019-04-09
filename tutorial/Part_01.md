## Part 01: Creating the Console

Before we get the console running we need to have our tile source file, which is
simply 'terminal.png', in the same folder as your source files. So go to the
libtcod-master folder, which is the folder you extracted when you cloned or 
downloaded th github repository in Part 00. Inside that folder you will find
'terminal.png'. Copy it to your working directory. Your project directory
should now have the following files:

	main  main.c  terminal.png

If you do, we're set to go. Open up your main.c and replace everything in it
with the following code:

	#include "libtcod.h"

	void main()
	{
		TCOD_console_init_root(80, 50, "These Cunning Old Depths", false, TCOD_RENDERER_SDL);

		while (!TCOD_console_is_window_closed()) {
			TCOD_console_flush();
			TCOD_console_wait_for_keypress(true);
		}
	}

This simply renders a black console screen and waits infinitely for the window to close. Quit the
program by clicking the x on the window. Let's go through this a bit.

	TCOD_console_init_root(80, 50, "These Cunning Old Depths", false, TCOD_RENDERER_SDL);

This initializes the console window with a width of 80, a height of 50, the name, fullscreen set to false,
and the renderer set to one of the possible TCOD renderers, in this case the SDL one. If you already 
know the name of your project you can change the one I places as a fake acronym for TCOD. 

	while (!TCOD_console_is_window_closed()) {
		TCOD_console_flush();
		TCOD_console_wait_for_keypress(true);
	}

This is a while loop to keep the screen open long enough for you to see it. If you delete the whole while
loop, the console screen will blink into existence as you run the program and disappear.

	TCOD_console_is_window_closed()

returns true if you close the console window and false if it is still open. We add
the ! sign so we reverse the false and keep the while loop going.


	TCOD_console_flush();

This function "paints" the console screen. Try commenting this line out of the while loop and you'll
see the frame of the console window with a transparent screen. This will be called constantly to refresh
the characters drawn on the screen as they move.

	TCOD_console_wait_for_keypress(true);

This returns the players keypresses. We're going to assign its return value to a variable soon, but for
now I just added it like this because without it the console screen would not respond properly when I
try to close it. I'm not sure why that is right now. If you have any idea, let me know.

Let's try getting the classic '@' character to move on the screen. First we need to get it to print on
the console. Add the following to your while loop in main.c:

	while (!TCOD_console_is_window_closed()) {
<span style='color: green'>
		TCOD_console_clear(NULL);
		TCOD_console_put_char(NULL, 40, 25, '@', TCOD_BKGND_NONE);
</span>
		TCOD_console_flush();
		TCOD_console_wait_for_keypress(true);
	    }

Compile it now, and when you run it you should see an '@' sign in the middle of the screen.

	TCOD_console_clear(NULL);

This line doesn't do much right now, but it will be necessary when we start moving. Otherwise
we would leave a trail of '@' signs behind us. What it does is clean the screen every time
it's called.

	TCOD_console_put_char(NULL, 40, 25, '@', TCOD_BKGND_NONE);

This is what paints our nameless hero on the screen. The NULL argument in this function and
also in the console_clear function refers to the specific console we are either clearing
or drawing on. The NULL value makes the function default to the root console, which is the
only one we have right now. The next to arguments are the x and y positions we are drawing
on. The '@' obviously is the character we want to draw, and TCOD_BKGND_NONE is a special
flag which says we don't want to change the background color of the cell we're drawing on.
This function uses the default foreground color of the console, which is white. If we 
want to change the color of the '@' sign we need to use another function. We'll get to 
that when we add monsters. Let's get the bastard moving.

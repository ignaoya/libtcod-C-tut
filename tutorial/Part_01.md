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

		TCOD_console_clear(NULL);
		TCOD_console_put_char(NULL, 40, 25, '@', TCOD_BKGND_NONE);

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

First, add the stdlib.h at the top of your main.c file before your libtcode include, like this:

	#include <stdlib.h>
	#include "libtcod.h"

We're gonna need that library to start establishing the structure of our game.
Immediately after the include statements, add the following code:


	typedef struct Entity {
		int x;
		int y;
		int c;
	} Entity;

This will be the basic entity from which we make every single creature. Right now an entity
simply has an x and y int for its position, and a c int that will contain the character
that represents it on the screen.

After that, add these function declarations:

	void handle_input(Entity * entity, TCOD_key_t key);
	void move(Entity * entity, int direction);

Handle_input is the function we're gonna use to process the user's keypresses. Move is the
function we're going to use to move not only the the player character but also other creatures.
After the ending bracket of the main() function, add the define the functions like this:

	void handle_input(Entity * entity, TCOD_key_t key) {
		switch(key.c) {
			case 'k': move(entity, 'u'); break;
			case 'j': move(entity, 'd'); break;
			case 'h': move(entity, 'l'); break;
			case 'l': move(entity, 'r'); break;
			default: break;
		}
	}

	void move(Entity * entity, int direction) {
		switch(direction) {
			case 'u': entity->y--; break;
			case 'd': entity->y++; break;
			case 'l': entity->x--; break;
			case 'r': entity->x++; break;
			default: break;
		}
	}

You might think that this is overly repetitive. You might be right. It does seem kind of redundant,
but when I started I had both functions simplified into one move function that took the key and
modified the player's x or y position, and that function only worked for the player. So this is
how I refactored it so that I could have a universal move function and a specific handle_input
function for the player. I'm using the vim keys k j h l, but if you prefer w a s d, go with that.
In order to use the standard arrow keys, you just need to change the switch in handle_input
to the following:

	switch(key.vk) {
		   case TCODK_UP : move(entity, 'u'); break;
		   case TCODK_DOWN : move(entity, 'd'); break;
		   case TCODK_LEFT : move(entity, 'l'); break;
		   case TCODK_RIGHT : move(entity, 'r'); break;
		   default:break;

And now to set up the player, add the following code in the main() function, between the root
console initialization and the start of the while loop:

	TCOD_console_init_root(80, 50, "These Cunning Old Depths", false, TCOD_RENDERER_SDL);

	Entity * player;
	player = malloc(sizeof(Entity));
	player->x = 40;
	player->y = 25;
	player->c = '@';

	while (!TCOD_console_is_window_closed()) {

The first line generates a player variable that is a pointer to an Entity.
The second line uses the malloc() function from the stdlib.h to allocate the appropriate 
memory for the entity pointer. Then we assign an x and y value to the player and, in the
last line, we assign the '@' character to its c variable.

Finally, lets change our while loop to use this player pointer and the new functions:

	while (!TCOD_console_is_window_closed()) {
		TCOD_console_clear(NULL);
		TCOD_console_put_char(NULL, player->x, player->y, player->c, TCOD_BKGND_NONE);
		TCOD_console_flush();
		TCOD_key_t key = TCOD_console_wait_for_keypress(true);
		handle_input(player, key);
	}

As you can see, instead of using hard coded values in put_char, we use the variables inside the
player pointer. Then we assign the return value of console_wait_for_keypress to a TCOD_key_t
variable which we pass into the handle_input function along with the player pointer.
Summing up, your main.c file should now look like this:

	#include <stdlib.h>
	#include "libtcod.h"

	typedef struct Entity {
		int x;
		int y;
		int c;
	} Entity;

	void handle_input(Entity * entity, TCOD_key_t key);
	void move(Entity * entity, int direction);

	void main() {
		TCOD_console_init_root(80, 50, "These Cunning Old Depths", false, TCOD_RENDERER_SDL);

		Entity * player;
		player = malloc(sizeof(Entity));
		player->x = 40;
		player->y = 25;
		player->c = '@';

		while (!TCOD_console_is_window_closed()) {
			TCOD_console_clear(NULL);
			TCOD_console_put_char(NULL, player->x, player->y, player->c, TCOD_BKGND_NONE);
			TCOD_console_flush();
			TCOD_key_t key = TCOD_console_wait_for_keypress(true);
			handle_input(player, key);
		}
	}

	void handle_input(Entity * entity, TCOD_key_t key) {
		switch(key.c) {
			case 'k': move(entity, 'u'); break;
			case 'j': move(entity, 'd'); break;
			case 'h': move(entity, 'l'); break;
			case 'l': move(entity, 'r'); break;
			default: break;
		}
	}

	void move(Entity * entity, int direction) {
		switch(direction) {
			case 'u': entity->y--; break;
			case 'd': entity->y++; break;
			case 'l': entity->x--; break;
			case 'r': entity->x++; break;
			default: break;
		}
	}

Try compiling that using the same commands we learned in Part_00, and run the main object that is
built by the compiler. You should now be able to move the '@' character around the screen with
whatever movement keys you chose.

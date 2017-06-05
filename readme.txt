
Exam Assignment in PGR3400 2016 by Torstein Alvern

I've made a game of othello, and this text document is included to describe some of my choices and decisions.





Board:


I assumed I was supposed to not make changes to board.c and board.h, and due to this assumption, I kept them the way I got them.
I did consider at some point to add a character 'LEGAL' to the Field enum, and have this placed on all legal tiles, but due to my assumption about not changing the files, I did not. 





exam_v2:


This file has the main function, as well as the game loop. It also updates the board and exits the program.

Most of the code for the program was written in this class, but most of the functions written has since been refactored away to more fitting files.




input:


I chose to have a separate file for input. I needed to get input from stdin for getNumberOfPlayers(), getUserNameInput(), and getUserInput(). getUserInput() however, became obsolete when I got mouse click events on the GUI to work, and is commented out in the gameloop. 

I also have a function getAIInput() that I decided fit better into this file than the others, even though it doesn't use stdin. 

In getUserNameInput() I wanted to allow the user to write a name consisting of multiple words, and found out that scanf() didn't really allow for this, but fgets() did. After doing my best with hours of error searching and googling to find out how to make this work out as I wanted, I was left with one of two bugs. Either, the code allows you to write longer names than the 15 chars allocated, and removes the extra characters written from the buffer before the next player types his/her name, but at the same time makes it so that for names shorter than 15 characters, a double enter press is needed to proceed, or the other bug appears, which allows the user to write shorter names with only pressing enter to proceed, but if they write names longer than 15 characters, the rest will overflow into the next player's name.



AI:


I wanted to create an AI both for the sake of showing independence in coding, and for the sake of being able to quickly test my game. Even a badly made AI is many times quicker than I am at finding and choosing a valid move, and chooses moves I would not. This helps me find bugs in my code a lot quicker, and also gives me someone to play against if I do desire. 

The current AI is as simple as it gets. It's completely random within the borders of the game, and retries if the random move it chose was illegal. I considered creating an array of legal moves and choosing randomly from that, or implementing a greedy algorithm AI, but because of time constraints, I deemed other parts of the code more important. 






Utilities:


When I needed a struct to store data, I originally did it in exam_v2.h, but I've since realized that having a header file for the main program file is bad practice, and I created a helping file I called utilities. This is where I keep these structs that I might need throughout the project, as well as different functions that originated from exam_v2.c, that I wanted to move due to the file becoming very long and cluttered. 

I was continously using the values X and Y together as a position, and it became natural to refactor these into its own struct.

It also became natural after roughly half of the code was in place, that I needed a separate struct for Player. Having a bool that says if the player is an AI or human allowed me to easily allow for games with only AI, AI vs human, or only humans. 

exam_v2.c had a lot of global variables after a while of coding, and I decided that keeping these variables in a struct GameInfo seemed like a solid way to easily pass around the data I need, as well as keeping the data from being globally available. 





Checks:


The game needed a lot of boolean checks to create the rules logic, and I decided the best thing to do was to separate all these boolean checks into it's own file. 

the function isMoveLegal() has an (int mode). The reason I chose to add this is because I needed the program to run this function for 3 different purposes, and while I could have made threee separate functions, I decided that creating an int like this would allow myself to not repeat large bulks of code. 






Log:


When the assignment asked me to make a log file, I figured I could choose one of two ways of formatting it. One option was to make it super simple, with barely the data it needs, to easily be able to read this file and recreate a game with it later. The other option was a log file that's readable to a human, and that shows what moves were placed by whom. If the user wants to recreate a game with a wooden Othello board that'd be quite convenient with this style of log.

I wanted to add a little pun in my project somewhere, and thus, the name of the logfile became Othellog.txt 





Gui:


I've put some of the function declarations in the .c file. This is to simulate private methods, and essentially making sure only gui.c has access to these methods. 

I used a presentation video as well as a small chatroom to help me get the GUI working with SDL2. The reason I chose SDL2 is that it supports C and C++ that I'm using next semester. SDL2 also supports OpenGL, which I'm supposed to have 5th semester, and this was a good opportinity.
Here's the video that helped me set up SDL2 with C: https://www.youtube.com/watch?v=yFLa3ln16w0&spfreload=10

I have one global variable/struct here (GuiInfo), and that's because the information within it is needed throughout several functions in the file, one of which (exitGUI()) are called from other files who do not have access to the GuiInfo file. I chose to keep it as a global variable because creating it within a function (Which would need to be within another file than gui.c) and passing it back and forth between files would be very messy. 

I'm aware of some errors caused by the SDL2 library that Valgrind picks up on. I spent several hours digging into what these errors could be, and when I realized they do not originate in my code, I decided to leave them be. 






Resources:


For my game to look better than the console rendering, I needed a background image, as well as a black and white tile texture. I made these in photoshop and added them to a resources folder. I also have an older version of the tiles there. They worked for figuring out the functionality, but I was unhappy with their design, and I created something more visually appealing. 

For the background image, I took an old photoshop project of mine of a treasure map, removes the map, and expanded the size of the background. I found a nice font I had already installed, and created an 8x8 array of squares. If I could figure out the X and Y position of the top corner of this array, and have consisent size of the squares, the math should be fairly simple for placing tiles and reading mouse clicks, and it was. 





makeFile:

After learning how to use makeFiles, and understanding how nicely they compliment a C project, I created one for the project and gave it some functionality I found very useful. 







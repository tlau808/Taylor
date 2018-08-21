ReadMe.txt
Lab 3
Taylor Lau: t.lau@wustl.edu

This program plays a card game. The only one I have designed is five card draw. 

Errors/Warnings
- Undeclared identifier when I called an instance of FiveCardDraw in the start_game method. I fixed poor .cpp/.h structure to solve.
- Iterator was not working. I realized I could not reuse an iterator.
- Dynamic allocation was failing. I needed to review inheritance and switch some instances of FiveCardDraw vs Game.

Desgin/Diversions
- I don't think it's possible to have insufficent cards in both the main and discard decks. I designed an exception to handle this
scenario, but never attained it. When a player discards some cards, they immediately go to the discard deck. If the main deck is
empty, these discarded cards are then dealt to the player. Yes, this is silly for a real game of poker, but I am following the
instructions.
- Players discard cards one at a time. If they were to do so all at once, indices in the vector shift and it is hard to keep the
positions aligned properly. There are probably ways around this such as using a temporary vector, but discarding one at a time avoids
other issues such as spacing.
- While there are 2+ players in the game, rounds occur. When there are no players left, I call stop_game. The instructions did not
specify what to do with one player left, so I call stop_game as well. You cannot play poker by yourself.
- Not all of my exceptions return a non-zero value. Some of them, such as reprompts, simply continue with the game. The larger
exceptions such as an invalid game are caught in my main function.

Trial 1: less than 4 total arguments
Usage: supply a type of game and 2+ players

Trial 2: argv[1] is not FiveCardDraw
Unknown game

Trial 3: a proper game with two new players
Had a fun game

Trial 4: a proper game with two existing players with .txt game files
Was able to load these scores

Trial 5: add an existing player
Reprompted. Player was already playing

Trial 6: delete a nonexistent player
Reprompted. Player was never playing
 
Trial 7: discard invalid card
Reprompted. Was not an integer between 1 and 5

Trial 8 : two players of the same name as arguments
Game did not start. Duplicate players.

All trials performed as expected.
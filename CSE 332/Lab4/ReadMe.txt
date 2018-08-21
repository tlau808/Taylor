ReadMe.txt
Taylor Lau: t.lau@wustl.edu

This program can play FiveCardDraw or SevenCardStud with rounds of betting. Player files should read name, wins, losses, chips in that
order.

Errors
I was unable to access certain methods for SevenCardStud. I had to move them from FiveCardDraw to Game.

Design
If a pot does not split evenly among winners, some people may get one more chip than others. I preserved the total chip count.
I omitted after_turn for FiveCardDraw. I thought it was redundant to print everyone, only to print them again when calculating poker ranks.
I sort hands after the round is over. Sorting after every transfer from the deck changes the hole cards.
Antes do not count toward the amount a player has bet.


Trial 1: A good, fun game of SevenCardStud
It worked

Trial 2: A good, fun game of FiveCardDraw
It worked

Trial 3: Only one player as an argument
Usage: input 2+ players

Trial 4: No arguments to specify the game
Usage: input the name of a game

Trial 5: Bet more than 1 or 2 chips
Try again

Trial 6: Bet more chips than a player owned
Try again

Trial 7: Went all-in
Had no further obligations

Trial 8: Tried to play a new invalid game
Try again

Trial 9: Everybody but Rick folded
He instantly won the pot

Trial 10: Rick ran out of chips
Goodbye Rick

All trials worked as expected
Taylor Lau
Lab2

This program accepts a file of card definitions to use as a deck. It can shuffle the deck if given the appropriate command, then deal
five card hands to nine players. It prints the hands, the remaining deck, the hands in lexical order, and the hands in poker rank
order.

Design/Diversions
I treated the back of the card vector as the top of the deck.
When moving cards from the deck to hand, I sorted the hand using the sort algorithm after each move.
I did not need to define a destructor because there were no issues with lifetimes.
Lexically ordering the cards by the lowest one (because they are sorted) is essentially meaningless. Did I misinterpret the
instructions?

Errors/Warnings
The program kept printing lines out of order with a random 0 at the end. I had to account for the carriage return.
There was even more nonsense output. I had to change certain return values of functions from int to string, hand, etc.
The shuffle algorithm kept shuffling to the same permutation. I needed to use srand(time()) for randomness.

Notes
I fixed an issue with capitalization from lab 0

Trial 1:
Output: "Provide a deck and perhaps '-shuffle'"

Trial 2: circle square triangle
Output: "Delete extraneous arguments"

Trial 3: circle square
Output: "If you provide two arguments, one must be '-shuffle' and the other a deck"

Trial 4: deck.txt (with 52 valid card definitions) -shuffle
Output: The deck shuffled as expected. Printed 9 hands, printed the remaining deck, printed hands in lexical order, printed
hands in poker rank order

Trial 5: deck.txt
Output: The deck did not shuffle, as expected. Printed 9 hands, printed the remaining deck, printed hands in lexical order, printed
hands in poker rank order

Trial 6: -shuffle
Output: "You can't shuffle without a deck"

Trial 7: triangle
Output: "Invalid file name. Input a valid text file"

Trial 8: -shuffle deck.txt (with 52 card definitions)
Output: The deck shuffled as expected. Printed 9 hands, printed the remaining deck, printed hands in lexical order, printed
hands in poker rank order. '-shuffle' can be either argument

Trial 9: deck.txt (with 44 card definitions)
Output: Gave error message instead of poker rank order. "Not all players had five card hands. Poker ranks do not apply"

Trial 10: deck.txt (a very specific case where player 1 had 3c 4h, player 2 had 3c)
Output: Player 2 came before player 1 in lexical order. Good
Taylor Lau
436874
Lab 0

This program reads a file of cards, turns them into a vector of cards, then outputs them as card structs.

I wanted to define a card as an integer rank and character suit. Jack would correspond to rank 11, etc. However, when it came time to print the
cards, I would have had to change the ranks back to strings for face cards. The rank 10 also inhibited me from using characters. It was
a better decision to use strings for ranks and characters for suits.
My valid card tester is also unwieldy. Nevertheless, I think I made the right decision to test strings instead of card structs, as forming
ridiculous cards just to reject them seemed silly.


Errors
	Had to resolve signed vs unsigned integers. I changed definition.length to definition.length() to resolve.
	Card * gave an error. Turns out I didn't have a good understanding of pointers. Used card instead.
	Didn't use booleans in an if statement. I changed to booleans.

Trial 1
	Input cards.txt (containing 2c 3h)
	Output: 2c 3h
	Return 0

Trial 2
	Input cards.txt (containing 2c 3h 7z j3 ofwenfuenw 223894 Qs 10c 4g)
	Output: 2c 3h Qs 10c
	Return 0

Trial 3
	Input cards.txt (containing j3 ofwenfuenw 223894)
	Output: There are no valid cards to print
	Return 2

Trial 4
	Input Harambe
	Output: Invalid file name. Input a valid text file
	Return 2
Trial 5
	Input 
	Output: Input a single file that contains card definition strings
	Return 3
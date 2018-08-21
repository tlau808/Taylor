Taylor Lau: Lab 1
This program reads five card hands from a text file, computes the appropriate poker rank,
and prints the hand in ascending order with the rank.

Errors/Warnings
I tried to modify the vector of cards. I forgot it was constant.
Getline() kept failing. It turned out that my while loop was out of bounds.
I was unable to manipulate my card struct. I didn't initialize it properly.

Design
I made many modifications to lab 0 such as changing suits and ranks to integers for easy ordering.
My most interesting implementation was a set to check for a full house. I added the rank of each card to the set
and checked whether the size of the set was 2.

Trial 1: cards.txt (7c 2c 7H 8s 8D, 4s 4H JD Jc 4H)
Output: 7c 2c 7H 8s 8D Hand rank: two pair
4s 4H JD Jc 4H Hand rank: full house

Trial 2: cards.txt (7c 2c 7H 8s 8D 10H, 4s 4H JD Jc 4H)
Output: One or more lines had less or more than five cards and were not printed
4s 4H JD Jc 4H Hand rank: full house

Trial 3: cards.txt (7c 2c 7H 8s 8D, 4s 4H steak JD Jc 4H)
Output: One or more card definitions were invalid and were not printed
7c 2c 7H 8s 8D Hand rank: two pair
4s 4H JD Jc 4H Hand rank: full house

Trial 4: Mercury
Output: Invalid file name. Input a valid text file

Trial 5: Venus Mars
Output: Input a single file name that contains card definitions strings

Trial 6: cards.txt (empty)
Outupt: There are no valid hands to print

Each trial performed as expected.
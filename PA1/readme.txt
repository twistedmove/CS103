CSCI Programming Assignment 1, Going Broke, Fall 2014

Name: Will Gauthier

Lecture Section: T/Th @11pm

USC ID: 5677636772

Email Address: wgauthie@usc.edu

=============================== Prelab =======================================

Response 1: Finding the remainder of the random number divided by two (rand % 
2) will always generate a zero or one. Arbitrarily, heads can be mapped to 0 
and tails to 1.

Response 2: You do not need to check explicitly for a draw because nothing 
happens in that instance. Instead, check that player1 equals player2 
(player1Result == player2Result). If true, inside check that player2 does not 
equal player3 (player2Result != player3Result) and give the coins to player3. 
If the first check is false (else if), check that player2 equals player3 
(player2Result == player3Result). If true, give the coins to player1 and 
otherwise (else) give the coins to player2.

Response 3: The number of turns per game is not known beforehand, so a while 
loop should be used. Its terminating condition is when any one of the players 
goes broke (while player1Coins != 0 && player2Coins != 0 && player3Coins != 0).

Response 4: The total number of turns taken must be maintained for the entire 
simulation as an int.

Response 5: The number of simulations is specified by the user and so is known 
before entering the loop. Thus, a for loop should be used.

Response 6: The number of flips per game should go up dramatically. Fair coins 
are all heads or all tails (1/2)^3 or 0.125 of the time, for a 0.25 chance of 
a draw.  Although the weighted coins are all heads only (1/10)^3 or 0.001 of 
the time, they are all tails (9/10)^3 or 0.729 of the time, for a 0.73 chance 
of a draw.

====================== Data from Procedure Step 6 ==========================

   p | n         | coins | output
----------------------------------
 0.5 | 5         |   3   | 4.2
 0.5 | 10        |   3   | 3.8
 0.5 | 50        |   3   | 5.46
 0.5 | 100       |   3   | 4.99
 0.5 | 1000      |   3   | 5.191
 0.5 | 10000     |   3   | 5.1716
 0.5 | 100000    |   3   | 5.14446

====================== Data from Procedure Step 7 ==========================

   p | n         | coins | output
----------------------------------
 0.1 | 10000     |   3   | 14.3716
 0.2 | 10000     |   3   |  8.0114
 0.3 | 10000     |   3   |  6.1446
 0.4 | 10000     |   3   |  5.3249
 0.5 | 10000     |   3   |  5.0830
 0.6 | 10000     |   3   |  5.3121
 0.7 | 10000     |   3   |  6.1351
 0.8 | 10000     |   3   |  8.0377
 0.9 | 10000     |   3   | 14.2923

================================== Review ===================================

Response 1: In the first data set the average number of turns starts to vary 
only in the hundredths place after 1000 simulations. Since turns can only be 
whole numbers anyways, you could get away with only 100 simulations. To play 
it safe, I would choose 500 simulations as the point of diminishing returns.

Response 2: As p diverges from 0.5 the games take increasing amounts of turns 
because the odds of everyone getting the overweighted flip and a draw 
increase, like I explained in prelab response 6. Moving in either direction, p 
towards 0 or 1, has the same increase in turns because a coin flip is a binary 
system. There can be increased amounts of heads or increased amounts of tails, 
but either result is a draw.

Response 3: If the probability of getting heads is 0 or 1 then every person 
will always flip a tails or head, respectively. The game would never end.

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

: It didn't feel like that long -- not more than a few hours.

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

: I had to seek help on implementing fairness. I was on the right track but 
thrown off by comparing an integer with a double of an unknown number of 
decimal places.

Do you have any other remarks?

: Nope.

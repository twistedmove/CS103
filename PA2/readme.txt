CSCI 103 Programming Assignment 2, Chroma Key, Fall 2014

Name: Will Gauthier

Email Address: wgauthie@usc.edu

=============================== Prelab =======================================

Pixel                |    RGB Value     |  Distance from Chroma Key
-------------------------------------------------------------------
Top-left background  | ( 69, 138,  19)  |   n/a
Arm                  | (255, 165, 120)  | 213.368
Vest                 | ( 25,  29,  28)  | 117.890
Shirt                | (231, 205, 232)  | 275.866

================================== Review ===================================

Response 1: I chose to use the entire top 20 rows and the first and last 25 
columns of the remaining rows as reference pixels. This is based on the 
assumption that the subject of the photo will be as centered as possible, with
some head and edge room. I probably could have added in another row and/or 
column, but at the risk of using pixels that aren't part of the green screen 
for reference.

Response 2: Parts of Colbert's guitar start disappearing around a 65 threshold,
but it is not until an 80 threshold that all of the noticeable green patches
not in direct contact with Colbert disappear. It takes a threshold of 5 for 
only a thin green line to remain around the bird, which is more or less gone by
a 30 threshold. You can go up to a 70 threshold before the bird starts missing
noticeable chunks, though.
Colbert range: from 65 to 80
Bird range: from 5 to 80

Response 3: Instead of a single threshold for the distance between the input
image and average reference chromakey points in a 3D space, I used three
thresholds for the red, green, and blue distances because more parameters are
more exact. These three thresholds are the farthest red, green, and blue
distances between the average reference chromakey point and any of the edge
pixels used to find the reference. In the program I found the average chromakey
reference point in the same way as method1, but then walked through the
reference pixels again and found the distance for each color, updating the
threshold when a bigger value was found. To set the mask I walked through the
entire image and only used the background if all the colors were under their
thresholds.
Additionally, I could have stored the maximum and minimum values for each color
and foregone a single, numeric threshold entirely. In effect, I would run
through the colors of all the reference pixels and update whenever a larger or
smaller number is found. Then I would run through the entire image and set the
mask to background if all the input image pixels' colors were within the
ranges. However, this would not have reused any code from method1, and I cannot
guess whether it would be more effective than what I did.
Another alternative to make the program more automatic and dynamic would be to
select the reference pixels based on the picture, rather than an arbitrary 20
rows and 25 columns. Doing so reliably would probably require a second
hard-coded threshold to determine whether a pixel should be used for reference,
however.

================================ Remarks ====================================

Approximately how long did you spend on this assignment?

It's difficult to say how long this assignment took. I finished relatively
quickly, but I spent a lot of time trying different thresholds and tweaking my
methods over and over. I'd guess the most useful work took between 3 and 4
hours.

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

Nope.

Do you have any other remarks?

Also nope.

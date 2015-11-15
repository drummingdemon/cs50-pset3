# cs50-pset3
Harvard CS50x3 Online Course - Problem set 3

# breakout.c
See line 119-122 for my take on the dreaded 'ball-is-stuck-within-the-paddle' problem. Essentially, what happens is that the detectCollision fires away multiple times while the ball is touching the paddle, which results in it bouncing back and forth within the paddle GRect object. To fix this, we only react to collision from the paddle if the ball is in the process of moving down - as the bottom of the screen should never be touched by the ball (it results in losing one life) we do not have to care about the underside of the paddle.

Should someone be interested in a more complex solution (which involves the bottom part of the screen not acting like a pit of doom) please consider updating detectCollision in such a way that it takes the various parts of the paddle into consideration.

# helpers.c
It features my implementation of Binary Search using recursive function call and a simple Linear Search is included as well.

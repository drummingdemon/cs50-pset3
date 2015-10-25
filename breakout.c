/*
 *  breakout.c
 *
 *  Harvard CS50x3 - Problem Set 3 - Breakout
 *
 *  A simple Breakout clone using the Stanford Portable Library
 *
 *  Gábor Hargitai <gabriel.hargitai@gmail.com>
 *
 */

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of the paddle
#define PAD_H 10
#define PAD_W 60

// paddle starting position in percentage from bottom
#define PAD_Y 0.15

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // ball velocity
    int ball_x = 2.0;
    int ball_y = 2.0 + drand48();
    
    if (drand48() > 0.5)
    {
        ball_x = -ball_x;
    }
    
    // click to start the game
    waitForClick();
       
    // to store 50 through 0 (with '\0'), we need <= 3 chars
    char score[3];

    // convert i from int to string
    sprintf(score, "%i", points);
    
    // set the label to the amount of points we have
    setLabel(label, score);
    
    // re-center the label
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;    
    setLocation(label, x, y);

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        move(ball, ball_x, ball_y);
        
        GObject object = detectCollision(window, ball);
        
        // if we hit the paddle while moving down, we bounce back
        // this also fixes the 'ball is stuck in paddle' problem
        if (object == paddle && (ball_y > 0))
        {
            ball_y = -ball_y;
        }
       
        else if (object != NULL && object != paddle && strcmp(getType(object), "GRect") == 0)
        {
            removeGWindow(window, object);
            ball_y = -ball_y;
            points++;
            bricks--;
            updateScoreboard(window, label, points);
        }
    
        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            ball_x = -ball_x;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            ball_x = -ball_x;
        }

        // bounce top edge of window
        else if (getY(ball) <= 0)
        {
            ball_y = -ball_y;
        }

        // bounce bottom edge of window
        else if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            lives--;
            if (lives == 0) 
            {
                // game over
                setLabel(label, "YOU LOST! :-(");
                
                // re-center the label
                x = (getWidth(window) - getWidth(label)) / 2;
                y = (getHeight(window) - getHeight(label)) / 2;    
                setLocation(label, x, y);
                waitForClick();
                closeGWindow(window);
                return 0;
            }          
            else 
            {
                waitForClick();
                setLocation(ball, WIDTH/2, HEIGHT/2);
            }
        }

        // linger before moving again
        pause(10);
        
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // let the paddle slide to the movement of the cursor
                double x = getX(event)-(PAD_W/2);
                setLocation(paddle, x, getY(paddle));
            }
        }
    }
    
    // congratulate the player
    setLabel(label, "YOU WON! :-)");
    
    // re-center the label
    x = (getWidth(window) - getWidth(label)) / 2;
    y = (getHeight(window) - getHeight(label)) / 2;    
    setLocation(label, x, y);

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{   
    int initHeight = 60;
    char* rowColors[] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN"};

    for (int j=0; j < ROWS; ++j)
    {  
        for (int i=0; i <= COLS; i++)
        {
            int brick_w = WIDTH / COLS;
            int brick_h = 10;
            int brick_y = (j * brick_h) + initHeight + j * (brick_h / 2);
            
            GRect brick = newGRect(i*brick_w+1, brick_y, brick_w-(brick_w * 0.1), brick_h);
            setFilled(brick, true);
            setColor(brick, rowColors[j]);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(0, 0, 20, 20);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    setLocation(ball, WIDTH/2, HEIGHT/2);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int pos_x = (WIDTH / 2) - (PAD_W / 2);
    int pos_y = HEIGHT - HEIGHT * PAD_Y;
    GRect paddle = newGRect(pos_x, pos_y, PAD_W, PAD_H);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("Click to Start!");
    setFont(label, "SanSerif-36");
    setColor(label, "GRAY");
    add(window, label);
    
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    
    setLocation(label, x, y);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    if (getGObjectAt(window, x, y) != NULL)
    {
        return getGObjectAt(window, x, y);
    }

    // check for collision at ball's top-right corner
    if (getGObjectAt(window, x + 2 * RADIUS, y) != NULL)
    {
        return getGObjectAt(window, x + 2 * RADIUS, y);
    }

    // check for collision at ball's bottom-left corner
    if (getGObjectAt(window, x, y + 2 * RADIUS) != NULL)
    {
        return getGObjectAt(window, x, y + 2 * RADIUS);
    }

    // check for collision at ball's bottom-right corner
    if (getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS) != NULL)
    {
        return getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    }

    // no collision
    return NULL;
}

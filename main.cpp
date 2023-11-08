#include <iostream>
#include <raylib.h>

using namespace std;

// Consts -------------------------------------------
const int screen_width = 800;
const int screen_height = 600;
const float timer = 1;
const int ball_x_initial = screen_width/2;
const int ball_y_initial = 100;

const int rectangle_width = 10;
const int rectangle_height = 100;
const int rectangle1_x = 50;
const int rectangle2_x = screen_width - rectangle1_x;
// ---------------------------------------------------

void updateTimer(float &counter) {
    if(counter > 0)
        counter -= GetFrameTime();
}

bool timeDone(float counter) {
    return counter <= 0;
}

void player1Movement(int &rectangle1_y) {
    if(IsKeyDown(KEY_W) && rectangle1_y >= 5)
        rectangle1_y -= 5;
            
    if(IsKeyDown(KEY_S) && rectangle1_y <= (screen_height - rectangle_height))
        rectangle1_y += 5;
}

void player2Movement(int &rectangle2_y) {
    if(IsKeyDown(KEY_UP) && rectangle2_y >= 5)
        rectangle2_y -= 5;
            
    if(IsKeyDown(KEY_DOWN) && rectangle2_y <= (screen_height - rectangle_height))
        rectangle2_y += 5;
}

void resetBall(int &ball_x, int &ball_y, int &ball_speed_y) {
    ball_x = ball_x_initial;
    ball_y = ball_y_initial;

    if(ball_speed_y < 0)
        ball_speed_y *= -1;
}

void resetCounter(float &counter) {
    counter = timer;
}


int main () {

    // Initialization ---------------------------------------
    int ball_x = ball_x_initial;
    int ball_y = ball_y_initial;
    int ball_speed_x = -5;
    int ball_speed_y = 5;
    int ball_radius = 10;
    int rectangle1_y = (screen_height/2 - rectangle_height/2);
    int rectangle2_y = rectangle1_y;

    int player1_score = 0;
    int player2_score = 0;

    float counter = timer;
    bool start = false;

    InitWindow(screen_width, screen_height, "PONG!");
    SetTargetFPS(60);


    // Main game loop ---------------------------------------
    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);

        if(!start) {
            // Main screen
            DrawText(TextFormat("PONG!"), (screen_width/2 - 150), (screen_height/2 - 100), 100, WHITE);
            DrawText(TextFormat("PRESS ENTER TO PLAY"), (screen_width/2 - 190), (screen_height/2 + 50), 30, WHITE);

            if (IsKeyPressed(KEY_ENTER))
                start = true;
        } else {
            // Forms and text
            DrawRectangle(rectangle1_x, rectangle1_y, rectangle_width, rectangle_height, WHITE); // Player 1
            DrawRectangle(rectangle2_x, rectangle2_y, rectangle_width, rectangle_height, WHITE); // Player 2
            DrawRectangle(screen_width/2, 0, 2, screen_height, WHITE);
            DrawCircle(ball_x,ball_y,ball_radius, WHITE);
            DrawText(TextFormat("%i", player1_score), (screen_width/2 - 100), 100, 100, WHITE);
            DrawText(TextFormat("%i", player2_score), (screen_width/2 + 50), 100, 100, WHITE);

            // Game interval
            updateTimer(counter); 
            timeDone(counter);

            // Movement - Player 1
            player1Movement(rectangle1_y);

            // Movement - Player 2
            player2Movement(rectangle2_y);


            // Game logic ----------------------------------------
            if(timeDone(counter)) {

                // Ball movement
                ball_x += ball_speed_x;
                ball_y += ball_speed_y;

                // Check collision with the screen
                if(ball_y + ball_radius >= screen_height || ball_y + ball_radius <= 5)
                    ball_speed_y *= -1;

                // Score
                if(ball_x + ball_radius >= screen_width) { // Player 1 score
                    player1_score++;
                    resetBall(ball_x, ball_y, ball_speed_y);
                    resetCounter(counter);
                    
                }
                if(ball_x + ball_radius <= 0) { // Player 2 score
                    player2_score++;
                    resetBall(ball_x, ball_y, ball_speed_y);
                    resetCounter(counter);
                }

                // Collision with player
                if(ball_x + ball_radius == rectangle1_x + rectangle_width + 10) // Player 1
                    if(ball_y + ball_radius >= rectangle1_y && ball_y + ball_radius <= rectangle1_y + rectangle_height)
                        ball_speed_x *= -1;
                
                if(ball_x + ball_radius == rectangle2_x + rectangle_width - 10) // Player 2
                    if(ball_y + ball_radius >= rectangle2_y && ball_y + ball_radius <= rectangle2_y + rectangle_height)
                        ball_speed_x *= -1;
                
            }
            // ---------------------------------------------------
            }
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
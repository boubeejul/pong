#include <iostream>
#include <raylib.h>

using namespace std;

// Consts -------------------------------------------
const int screen_width = 800;
const int screen_height = 600;
const float timer = 1;
const int ball_x_initial = screen_width / 2;
const int ball_y_initial = 100;
const int ball_radius = 10;

const int rectangle_width = 10;
const int rectangle_height = 100;
const int rectangle1_x = 50;
const int rectangle2_x = screen_width - rectangle1_x;
// ---------------------------------------------------

// Screens -------------------------------------------
void mainScreen(bool &start)
{
    DrawText(TextFormat("PONG!"), (screen_width / 2 - 150), (screen_height / 2 - 100), 100, WHITE);
    DrawText(TextFormat("PRESS ENTER TO PLAY"), (screen_width / 2 - 190), (screen_height / 2 + 50), 30, WHITE);

    if (IsKeyPressed(KEY_ENTER))
        start = true;
}

void selectPlayers(int &selection)
{
    DrawText(TextFormat("PONG!"), (screen_width / 2 - 150), (screen_height / 2 - 100), 100, WHITE);
    DrawText(TextFormat("PRESS 1 TO PLAY SINGLE PLAYER"), (screen_width / 2 - 260), (screen_height / 2 + 50), 30, WHITE);
    DrawText(TextFormat("PRESS 2 TO PLAY MULTIPLAYER"), (screen_width / 2 - 260), (screen_height / 2 + 100), 30, WHITE);

    if (IsKeyPressed(KEY_ONE))
        selection = 1;

    if (IsKeyPressed(KEY_TWO))
        selection = 2;
}
// ---------------------------------------------------

// Timer functions -----------------------------------
void updateCounter(float &counter)
{
    if (counter > 0)
        counter -= GetFrameTime();
}

void resetCounter(float &counter)
{
    counter = timer;
}

bool timeDone(float counter)
{
    return counter <= 0;
}
// ---------------------------------------------------

// Players movement ----------------------------------
void player1Movement(int &rectangle1_y)
{
    if (IsKeyDown(KEY_W) && rectangle1_y >= 5)
        rectangle1_y -= 5;

    if (IsKeyDown(KEY_S) && rectangle1_y <= (screen_height - rectangle_height))
        rectangle1_y += 5;
}

void player2Movement(int &rectangle2_y)
{
    if (IsKeyDown(KEY_UP) && rectangle2_y >= 5)
        rectangle2_y -= 5;

    if (IsKeyDown(KEY_DOWN) && rectangle2_y <= (screen_height - rectangle_height))
        rectangle2_y += 5;
}

// void gameMovement(int &rectangle2_y, int ball_speed_y, int ball_y)
// {
//     if (ball_speed_y < 0 && rectangle2_y >= 5)
//         while(rectangle2_y > ball_y)
//             rectangle2_y -= 5;

//     if (ball_speed_y > 0 && rectangle2_y <= (screen_height - rectangle_height))
//         while(rectangle2_y < ball_y)
//             rectangle2_y += 5;
// }

// Reset ---------------------------------------------
void resetBall(int &ball_x, int &ball_y, int &ball_speed_y)
{
    ball_x = ball_x_initial;
    ball_y = ball_y_initial;

    if (ball_speed_y < 0)
        ball_speed_y *= -1;
}

int main()
{

    // Initialization ---------------------------------------
    int ball_x = ball_x_initial;
    int ball_y = ball_y_initial;
    int ball_speed_x = -5;
    int ball_speed_y = 5;
    int rectangle1_y = (screen_height / 2 - rectangle_height / 2);
    int rectangle2_y = rectangle1_y;

    int player1_score = 0;
    int player2_score = 0;

    float counter = timer;
    bool start = false;
    int selection = 0;

    InitWindow(screen_width, screen_height, "PONG!");
    SetTargetFPS(60);

    // Main game loop ---------------------------------------
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Call screens -------------------------------------
        if (!start)
            mainScreen(start);

        if (start && !selection)
            selectPlayers(selection);

        // Start game ---------------------------------------
        if (start && selection > 0)
        {
            DrawRectangle(rectangle1_x, rectangle1_y, rectangle_width, rectangle_height, WHITE); // Player 1
            DrawRectangle(rectangle2_x, rectangle2_y, rectangle_width, rectangle_height, WHITE); // Player 2
            DrawRectangle(screen_width / 2, 0, 2, screen_height, WHITE);
            DrawCircle(ball_x, ball_y, ball_radius, WHITE);
            DrawText(TextFormat("%i", player1_score), (screen_width / 2 - 100), 100, 100, WHITE);
            DrawText(TextFormat("%i", player2_score), (screen_width / 2 + 50), 100, 100, WHITE);

            // Game interval
            updateCounter(counter);
            timeDone(counter);

            // Movements
            player1Movement(rectangle1_y);
            player2Movement(rectangle2_y);
            // if (selection == 1)
            // {
            //     player1Movement(rectangle1_y);
            //     gameMovement(rectangle2_y, ball_speed_y, ball_y);
            // }
            // else
            // {
            //     player1Movement(rectangle1_y);
            //     player2Movement(rectangle2_y);
            // }

            // Game logic ----------------------------------------
            if (timeDone(counter))
            {

                // Ball movement
                ball_x += ball_speed_x;
                ball_y += ball_speed_y;

                // Check collision with the screen
                if (ball_y + ball_radius >= screen_height || ball_y + ball_radius <= 5)
                    ball_speed_y *= -1;

                // Score
                if (ball_x + ball_radius >= screen_width)
                {
                    player1_score++;
                    resetBall(ball_x, ball_y, ball_speed_y);
                    resetCounter(counter);
                }
                if (ball_x + ball_radius <= 0)
                {
                    player2_score++;
                    resetBall(ball_x, ball_y, ball_speed_y);
                    resetCounter(counter);
                }

                // Collision with player
                if (ball_x + ball_radius == rectangle1_x + rectangle_width + 10) // Player 1
                    if (ball_y + ball_radius >= rectangle1_y && ball_y + ball_radius <= rectangle1_y + rectangle_height)
                        ball_speed_x *= -1;

                if (ball_x + ball_radius == rectangle2_x + rectangle_width - 10) // Player 2
                    if (ball_y + ball_radius >= rectangle2_y && ball_y + ball_radius <= rectangle2_y + rectangle_height)
                        ball_speed_x *= -1;
            }
            // ------------------------------------------------
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
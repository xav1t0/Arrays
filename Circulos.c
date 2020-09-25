#include "raylib.h"

#define MAX_ENEMIES 100

typedef struct Circle {
    float x;
    float y;
    float radius;
    Color color;
    float speedX;
    float speedY;
} Circle;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Circle enemies[MAX_ENEMIES];
    
    int speed = 5;
    
    for(int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].x = GetRandomValue(20, 1520);
        enemies[i].y = GetRandomValue(25, 850 );
        enemies[i].radius = GetRandomValue(6,20);
        enemies[i].color.r = GetRandomValue(0,255);
        enemies[i].color.g = GetRandomValue(0,255);
        enemies[i].color.b = GetRandomValue(0,255);
        enemies[i].color.a = 255;
        enemies[i].speedX = GetRandomValue(GetRandomValue(-6,-1),GetRandomValue(1,6));
        enemies[i].speedY = GetRandomValue(GetRandomValue(-6,-1),GetRandomValue(1,6));
        
    }
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        for(int i = 0; i < MAX_ENEMIES; i++)
        {
            enemies[i].x += enemies[i].speedX ;
            enemies[i].y += enemies[i].speedY ;
            
            if ((enemies[i].x >= screenWidth - enemies[i].radius) || (enemies[i].x <= enemies[i].radius)) enemies[i].speedX *= -1;
            if ((enemies[i].y >= screenHeight - enemies[i].radius) || (enemies[i].y <= enemies[i].radius)) enemies[i].speedY *= -1;
            
            if(enemies[i].speedX == 0)
            {
                enemies[i].speedX = 1;
            }
            if(enemies[i].speedY == 0)
            {
                enemies[i].speedY = 1;
            }
            
            for(int j = 0; j < 25; j++)
            {
                if(i != j)
                {
                    if(CheckCollisionCircles((Vector2) {enemies[i].x, enemies[i].y},enemies[i].radius,(Vector2) {enemies[j].x, enemies[j].y},enemies[j].radius ))
                    {
                        
                       
                        
                            enemies[i].speedY *= -1;
                            enemies[j].speedX *= -1;
                            enemies[i].speedX *= -1;
                            enemies[j].speedY *= -1;
                        
                    }
                }
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            for(int i = 0; i < MAX_ENEMIES; i++)
            {
                DrawCircle(enemies[i].x,enemies[i].y,enemies[i].radius,enemies[i].color);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

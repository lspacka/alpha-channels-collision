#include "raylib.h"
#include <math.h>

int main()
{
    int width = 600;
    int height = 600;

    InitWindow(width, height, "Alpha Channels Collision");
    SetTargetFPS(60);

    Image rock = LoadImage("rock1.png");
    Image ship = LoadImage("ship.png");

    Color* r_pix = LoadImageColors(rock);
    Color* s_pix = LoadImageColors(ship);

    Texture2D r_tex = LoadTextureFromImage(rock);
    Texture2D s_tex = LoadTextureFromImage(ship);

    Vector2 r_pos = {100, 100};
    Vector2 s_pos = {300, 300};

    float r_radius = sqrtf(rock.width*rock.width + rock.height*rock.height) / 2;
    float s_radius = sqrtf(ship.width*ship.width + ship.height*ship.height) / 2;

    Vector2 r_center = {r_pos.x+rock.width/2, r_pos.y+rock.height/2};
    Vector2 s_center = {s_pos.x+ship.width/2, s_pos.y+ship.height/2};

    int show = 0;
    Vector2 mouse_pos;

    while (!WindowShouldClose()) {
        BeginDrawing();
        HideCursor();
        ClearBackground(BLACK);

        // update ship position to follow the mouse
        mouse_pos = GetMousePosition();
        s_pos = (Vector2){mouse_pos.x-s_tex.width/2, mouse_pos.y-s_tex.height/2};
        s_center = (Vector2){s_pos.x+ship.width/2, s_pos.y+ship.height/2};

        DrawTexture(r_tex, r_pos.x, r_pos.y, WHITE);
        DrawTexture(s_tex, s_pos.x, s_pos.y, WHITE);
        // DrawCircle(c_point.x, c_point.y, d, GREEN);

        if (CheckCollisionCircles(r_center, r_radius, s_center, s_radius)) {
            int start_x = (int)fmax(r_pos.x, s_pos.x);
            int end_x = (int)fmin(r_pos.x+rock.width, s_pos.x+ship.width);
            int start_y = (int)fmax(r_pos.y, s_pos.y);
            int end_y = (int)fmin(r_pos.y+rock.height, s_pos.y+ship.height);

            int collision_found = 0;

            for (int y = start_y; y < end_y && !collision_found; y++) {
                for (int x = start_x; x < end_x && !collision_found; x++) {
                    // convert world coordinates to local image coordinates
                    int r_local_x = x - (int)r_pos.x;
                    int r_local_y = y - (int)r_pos.y;
                    int s_local_x = x - (int)s_pos.x;
                    int s_local_y = y - (int)s_pos.y;

                    // get colors from both images
                    Color r_pixel = r_pix[r_local_y*rock.width + r_local_x];
                    Color s_pixel = s_pix[s_local_y*ship.width + s_local_x];

                    if (r_pixel.a > 0 && s_pixel.a > 0) {
                        collision_found = 1;
                        DrawText("Collision!", 10, 10, 40, RED);
                    }
                }
            }
        }

        if (IsKeyPressed(KEY_S))
            show = !show;

        if (show) {
            DrawCircleLines(r_center.x, r_center.y, r_radius, ORANGE);
            DrawCircleLines(s_center.x, s_center.y, s_radius, ORANGE);
        }
        
        EndDrawing();
    }

    UnloadTexture(r_tex);
    UnloadTexture(s_tex);
    UnloadImageColors(r_pix);
    UnloadImageColors(s_pix);
    UnloadImage(rock);
    UnloadImage(ship);

    CloseWindow();

    return 0;
}
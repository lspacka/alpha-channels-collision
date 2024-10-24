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


    float r_radius = rock.width / 1.7;
    float s_radius = ship.width / 1.7;

    Vector2 r_center = {r_pos.x+rock.width/2, r_pos.y+rock.height/2};
    Vector2 s_center = {s_pos.x+ship.width/2, s_pos.y+ship.height/2};

    Rectangle r_rect = {r_pos.x, r_pos.y, rock.width, rock.height};

    int show = 0;
    Vector2 mouse_pos;

    while (!WindowShouldClose()) {
        BeginDrawing();
        HideCursor();
        ClearBackground(BLACK);
        Rectangle s_rect = {s_pos.x, s_pos.y, ship.width, ship.height};

        // update ship position to follow the mouse
        mouse_pos = GetMousePosition();
        s_pos = (Vector2){mouse_pos.x-s_tex.width/2, mouse_pos.y-s_tex.height/2};
        s_center = (Vector2){s_pos.x+ship.width/2, s_pos.y+ship.height/2};

        DrawTexture(r_tex, r_pos.x, r_pos.y, WHITE);
        DrawTexture(s_tex, s_pos.x, s_pos.y, WHITE);

        if (CheckCollisionCircles(r_center, r_radius, s_center, s_radius)) {
            int collision_found = 0;
            DrawText("1st Check", 10, 10, 20, ORANGE);

            // Pixel-perfect collision check: Loop over all pixels in the images
            for (int y = 0; y < rock.height && !collision_found; y++) {
                for (int x = 0; x < rock.width && !collision_found; x++) {
                    // convert to local image coordinates
                    int r_local_x = x;
                    int r_local_y = y;
                    int s_local_x = (x + (int)(r_pos.x - s_pos.x));
                    int s_local_y = (y + (int)(r_pos.y - s_pos.y));

                    // Ensure we don't check outside of the ship image bounds
                    if (s_local_x >= 0 && s_local_y >= 0 && s_local_x < ship.width && s_local_y < ship.height) {
                        // Get colors from both images
                        Color r_pixel = r_pix[r_local_y * rock.width + r_local_x];
                        Color s_pixel = s_pix[s_local_y * ship.width + s_local_x];

                        // Check for non-transparent pixels
                        if (r_pixel.a > 0 && s_pixel.a > 0) {
                            collision_found = 1;
                            DrawText("Collision!", 10, 40, 20, RED);
                        }
                    }
                }
            }
        }

        if (IsKeyPressed(KEY_S))
            show = !show;

        if (show) {
            DrawCircleLines(r_center.x, r_center.y, r_radius, ORANGE);
            DrawCircleLines(s_center.x, s_center.y, s_radius, ORANGE);

            // DrawRectangleLinesEx(r_rect, 1.0f, GREEN);
            // DrawRectangleLinesEx(s_rect, 1.0f, GREEN);
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
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int a = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = a;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            while (j < round(0.5 * width))
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = temp;
                break; // without break the program runs forever
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            int blue = 0;
            int green = 0;
            int red = 0;
            int sq = 0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (a + x < 0 || a + x >= height || b + y < 0 || b + y >= width)
                    {
                        // continue;
                    }
                    else
                    {
                        blue += copy[a + x][b + y].rgbtBlue;
                        green += copy[a + x][b + y].rgbtGreen;
                        red += copy[a + x][b + y].rgbtRed;
                        sq++;
                    }
                }
            }
            image[a][b].rgbtBlue = round(blue * 1.0 / sq);
            image[a][b].rgbtGreen = round(green * 1.0 / sq);
            image[a][b].rgbtRed = round(red * 1.0 / sq);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // make kernels
    int kernelx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernely[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // main job
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 3 channels for each grid of ij
            int bx = 0;
            int gx = 0;
            int rx = 0;

            int by = 0;
            int gy = 0;
            int ry = 0;

            // kernels looped through for each grid
            for (int p = -1; p < 2; p++)
            {
                for (int q = -1; q < 2; q++)
                {
                    if (i + p < 0 || i + p >= height || j + q >= width || j + q < 0)
                    {
                        continue;
                    }

                    // debug
                    // w/ else :: bright blurry photo
                    // w/o else :: return to right photo seen when using exhaustion

                    rx += copy[i + p][j + q].rgbtRed * kernelx[p + 1][q + 1];
                    bx += copy[i + p][j + q].rgbtBlue * kernelx[p + 1][q + 1];
                    gx += copy[i + p][j + q].rgbtGreen * kernelx[p + 1][q + 1];

                    ry += copy[i + p][j + q].rgbtRed * kernely[p + 1][q + 1];
                    by += copy[i + p][j + q].rgbtBlue * kernely[p + 1][q + 1];
                    gy += copy[i + p][j + q].rgbtGreen * kernely[p + 1][q + 1];

                }
            }

            // ()^2 + ()^2 -> sqrt -> round -> bound -> assign
            int red_final = round(sqrt(rx * rx + ry * ry));
            int blue_final = round(sqrt(bx * bx + by * by));
            int green_final = round(sqrt(gx * gx + gy * gy));

            image[i][j].rgbtRed = fmin(red_final, 255);
            image[i][j].rgbtBlue = fmin(blue_final, 255);
            image[i][j].rgbtGreen = fmin(green_final, 255);
        }
    }
    return;
}
#include "helpers.h"
#include <math.h>

#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int rgbGrey = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgbGrey =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = rgbGrey;
            image[i][j].rgbtRed = rgbGrey;
            image[i][j].rgbtGreen = rgbGrey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed, originalGreen, originalBlue;
    // int sepiaRed , sepiaGreen , sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                .189 * image[i][j].rgbtBlue);
            originalGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                  .168 * image[i][j].rgbtBlue);
            originalBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                 .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = fmin(255, originalRed);
            image[i][j].rgbtGreen = fmin(255, originalGreen);
            image[i][j].rgbtBlue = fmin(255, originalBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
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
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            float count = 0.00;

            for (int row = (i - 1); row <= (i + 1); row++)
            {
                for (int col = (j - 1); col <= (j + 1); col++)
                {
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        red_sum += image[row][col].rgbtRed;
                        green_sum += image[row][col].rgbtGreen;
                        blue_sum += image[row][col].rgbtBlue;
                        count++;
                    }
                }
            }

            copy[i][j].rgbtRed = round(red_sum / count);
            copy[i][j].rgbtGreen = round(green_sum / count);
            copy[i][j].rgbtBlue = round(blue_sum / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}

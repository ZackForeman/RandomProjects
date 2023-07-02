#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BIAS 0.1f

#define WIDTH 10000
#define HEIGHT 10000

struct element {
    char red;
    char green;
    char blue;
};

int round4(int x) {
    return x % 4 == 0 ? x : x - x % 4 + 4;
}

void write_bmp(char *filename, char rgb[], int length, int width) {

    // Calculate the image height from its width and the array length
    int height = (length / 3) / width;
    int padded_width = round4(width * 3);

    // The size of the pixel data. For now, use width + 1 to handle 
    // row padding.
    int bitmap_size =  3 * height * padded_width;

    // The pixel data is now variable-length, so we need to use
    // malloc.
    char *bitmap = (char *) malloc(bitmap_size * sizeof(char));

    // Zeroing out the data will set all the pixels to black.
    for (int i = 0; i < bitmap_size; i++) bitmap[i] = 0;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            
            // For R, G, and B...
            for (int color = 0; color < 3; color++) {

                // Get the index of the destination image
                int index = row * padded_width + col * 3 + color;

                // Set the destination to the value of the src at row, col.
                bitmap[index] = rgb[3*(row * width + col) + (2 - color)];
            }
        }
    }

    char tag[] = { 'B', 'M' };
    int header[] = {
        0,                   // File size... update at the end.
        0, 0x36, 0x28,
        width, height,       // Image dimensions in pixels

        0x180001, 0, 0, 0x002e23, 0x002e23, 0, 0,
    };
    // Update file size: just the sum of the sizes of the arrays
    // we write to disk.
    header[0] = sizeof(tag) + sizeof(header) + bitmap_size;

    FILE *fp = fopen(filename, "w+");
    fwrite(&tag, sizeof(tag), 1, fp);
    fwrite(&header, sizeof(header), 1, fp);

    // Malloc returns a pointer, so we no longer need to get the
    // adress of bitmap
    fwrite(bitmap, bitmap_size * sizeof(char), 1, fp);
    fclose(fp);
    free(bitmap);
}

int f(int x, int y){
    float newx = ((float)x - (float)(WIDTH/2))/(float)(WIDTH/100);
    float newy = ((float)y - (float)(HEIGHT/2))/(float)(HEIGHT/100);
    
    return ((fabs(pow(newx,sin(newx*newx+newy*newy))-newy)) < BIAS);
}

int main() {
    int width  = WIDTH;
    int height = HEIGHT;
    int colourNumber = 3;

    char *graph = (char*) malloc(height*width*colourNumber*sizeof(char));

    for(int col = 0; col < width; col++){
        for(int row = 0; row < height; row++){
            for(int k = 0; k < colourNumber; k++){
                graph[row*width*colourNumber + col*colourNumber + k] = 255;
            }
        }
    }

    for(int col = 0; col < width; col++){
        for(int row = 0; row < height; row++){
            for(int k = 0; k < colourNumber; k++){
                if(f(col,row)){
                    graph[row*width*colourNumber + col*colourNumber + k] = 0;
                }                
            }
        }
    }

    for(int col = 0; col < width; col++){
        for(int row = 0; row < height; row++){
            for(int k = 0; k < colourNumber; k++){
                if(col == HEIGHT/2){
                    graph[row*width*colourNumber + col*colourNumber + k] = 0;
                }                
            }
        }
    }

    for(int col = 0; col < width; col++){
        for(int row = 0; row < height; row++){
            for(int k = 0; k < colourNumber; k++){
                if(row == WIDTH/2){
                    graph[row*width*colourNumber + col*colourNumber + k] = 0;
                }                
            }
        }
    }

    write_bmp("graph.bmp", graph, width*height*colourNumber, width);
   

}

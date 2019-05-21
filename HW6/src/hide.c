/*
 * pnmhide/src/hide.c --
 */

#include "image.h"
#include "hide.h"
#include <string.h>

#define BITMASK     1
#define MAX_BITS    8

int set_bit(int x, int y) {
    x = (x >> 1);
    x = (x << 1);
    x = (x | y);

    return x;
}

void tag(image_t *im) {
    // Last row of the image
    int i = im->rows - 1;
    int n = 1;

    // Tagging the last three pixels of the image
    for (int j = im->cols - 3; j < im->cols; j++) {
        // Taking the pixel from the image at position [i][j]
        xel pixel = im->xels[i][j];
        // Activating the least significant bits of the red, green and blue
        while(n < 3) {
            if (n == 0) {
                pixel.r = set_bit(pixel.r, 1);
                n++;
            } else if (n == 1) {
                pixel.g = set_bit(pixel.g, 1);
                n++;
            } else {
                pixel.b = set_bit(pixel.b, 1);
                n=0;
                break;
            }
        }
        // Saving the pixel back into the image
        im->xels[i][j] = pixel;
    }
}

bool checkTag(image_t *im) {
    // Last row of the image
    int i = im->rows - 1;
    int n = 1;
    int lsb = 0;

    // Checking the last three pixels
    for (int j = im->cols - 1; j > im->cols - 4; j--) {
        // Taking the pixel from the image at position [i][j]
        xel pixel = im->xels[i][j];
        // If one of the least significant bits of the RGB are inactive
        // then there is no message
        while (n >= 0) {
            if (n == 0) {
                lsb = (pixel.r & BITMASK);
                if (lsb == 0) {
                    return FALSE;
                }
                n--;
            } else if (n == 1) {
                lsb = (pixel.g & BITMASK);
                if (lsb == 0) {
                    return FALSE;
                }
                n--;
            } else {
                lsb = (pixel.b & BITMASK);
                if (lsb == 0) {
                    return FALSE;
                }
                n = 2;
                break;
            }
        }
    }
    // If all three pixels were active then there is a message
    return TRUE;
}

int im_encode(image_t *im, char *msg) {
    int lsb = MAX_BITS - 1;
    // Determining the length of the message
    int msg_len = strlen(msg);
    int msg_i = 0;

    // Checking if the message would fit in the image
    if ((msg_len * 8 * 3) > ((im->cols * im->rows * 3) - 8)) {
        return -1;
    }

    // Tagging the image for a message
    tag(im);

    for (int i = 0; i < im->rows; i++) {
        for (int j = 0; j < im->cols; j++) {
            // Going pixel by pixel
            xel pixel = im->xels[i][j];

            // Changing the least significant bit of the red, green
            // and blue of each pixel
            for (int n = 0; n < 3; n++) {
                // Taking the character that we need to import into the image
                char ch = msg[msg_i];
                // Taking only one bit out of the character
                u_int8_t bit = (ch >> lsb) & BITMASK;

                // Checking whose turn is it to change the lsb
                if (n == 0) {
                    pixel.r = set_bit(pixel.r, bit);
                } else if (n == 1) {
                    pixel.g = set_bit(pixel.g, bit);
                } else {
                    pixel.b = set_bit(pixel.b, bit);
                }

                // If we still haven't reached the end of the string
                if (msg_i < msg_len) {
                    if (lsb == 0) {
                        // If we set this character we go to a new character
                        lsb = MAX_BITS - 1;
                        msg_i += 1;
                    } else {
                        // Otherwise, we move to the next bit of the character
                        // in the next iteration
                        lsb -= 1;
                    }
                }

                // If we reached the end of the string
                if(msg_i >= msg_len) {
                    // Continuing where we left with the changing of the lsb
                    if (n == 2) {
                        n = 0;
                    } else {
                        n++;
                    }
                    
                    // Setting the next 8 lsb to 0 to mark the end of the string
                    for (int k = 0; k < 8; k++) {
                        if (n == 0) {
                            pixel.r = set_bit(pixel.r, 0);
                            n++;
                        } else if (n == 1) {
                            pixel.g = set_bit(pixel.g, 0);
                            n++;
                        } else {
                            // If the turn is to change the lsb of the blue
                            // then we need to go to the next pixel
                            pixel.b = set_bit(pixel.b, 0);
                            im->xels[i][j] = pixel;
                            if (j + 1 < im->cols) {
                                j++;
                            } else {
                                j = 0;
                                i++;
                            }
                            pixel = im->xels[i][j];
                            n = 0;
                        }
                    }
                    // After we have set the 8 lsb to 0 we can return the
                    // length of the encoded message
                    return msg_len;
                }  
            }
            // Saving the changes on this pixel so we can move on the next one
            im->xels[i][j] = pixel;
        }
    }
    // If the program doesn't raise any errors then it is never going
    // to reach this return
    return 0;
}

int im_decode(image_t *im, char *buffer, size_t size) {
    int msgLength = 0;
    char ch = '\0';
    int count = 0;

    // Checking if the image has a message at all
    if (checkTag(im) == FALSE) {
        return -1;
    }

    for (int i = 0; i < im->rows; i++) {
        for (int j = 0; j < im->cols; j++) {
            // Going pixel by pixel
            xel pixel = im->xels[i][j];

            // Taking the lsb from every red, green and blue
            for (int n = 0; n < 3; n++) {
                if (n == 0) {
                    ch = ((ch << 1) | (pixel.r & BITMASK));
                } else if (n == 1) {
                    ch = ((ch << 1) | (pixel.g & BITMASK));
                } else {
                    ch = ((ch << 1) | (pixel.b & BITMASK));
                }
                // Counting the bits that we have added to the character
                count++;

                // If the count reaches 8 bits then that is a character
                if (count == 8) {
                    count = 0;

                    // If the character is -1 it means it reached the end
                    if (ch == -1) {
                        buffer[msgLength] = '\0';
                        // Returning the length of the decoded message
                        return msgLength;
                    } else {
                        // Otherwise, we save the character to the buffer
                        buffer[msgLength] = ch;
                        msgLength++;
                        ch = '\0';
                    }
                    
                    // If the message length surpasses the buffer size
                    if (msgLength > size) {
                        return -1;
                    }
                }
            }
        }
    }
    // If the program doesn't raise any errors then it is never going
    // to reach this return
    return 0;
}

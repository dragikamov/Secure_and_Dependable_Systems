/*
 * pnmhide/src/hide.h --
 */

#ifndef _HIDE_H
#define _HIDE_H

#include "image.h"

/**
 * \brief Change the least significant bit.
 * 
 * \param x The number that the cnage is going to be implemented on.
 * \param y The bit that is set to x.
 * \result The result of the change.
 */ 
int set_bit(int x, int y);

/**
 * \brief Tag an image that it has a message inside.
 * 
 * \param im The image that is tagged.
 * \result void.
 */
void tag(image_t *im);

/**
 * \brief Checking if an image has been tagged for a message.
 * 
 * \param im The image that is being checked.
 * \result A boolean of whether it has a message or not.
 */
bool checkTag(image_t *im);

/**
 * \brief Encode a message in an image.
 *
 * \param im Pointer to the image.
 * \param msg Message to encode.
 * \result Length of the message encoded or negative number on error.
 */
int im_encode(image_t *im, char *msg);

/**
 * \brief Decode a message from an image.
 *
 * \param im Pointer to the image.
 * \param buffer Buffer to fill with the decoded message.
 * \param size The buffer size.
 * \result Length of the message decoded or negative number on error.
 */
int im_decode(image_t *im, char *buffer, size_t size);

#endif

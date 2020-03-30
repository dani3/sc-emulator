/** \file util.c
 */
#include <utilities/util.h>

#include <stdio.h>

/** \fn print
 * \brief prints the data to the stdout.
 *
 * \param data: data to be printed.
 * \param length: length of the data.
 *
 * \return Void.
 */
void print(u8* data, u16 length) {
    for (u16 i = 0; i < length; ++i) {
		if (i == 0) {
			printf(" -");
		}

		printf(" %02X", data[i]);
	}

    fflush(stdout);
}
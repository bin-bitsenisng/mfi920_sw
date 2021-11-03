/* f2decl.c
* Copyright (c) 2018-2020 Analog Devices Inc. All rights reserved
*
* Clear BSD license
* -----------------
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the disclaimer
* below) provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
* * Neither the name of Analog Devices, Inc. nor the names of its contributors
*   may be used to endorse or promote products derived from this software
*   without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
* THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
* f2decl.c: Converts a binary file to a C source file that defines an array
*           statically intialized to the contents of the input file.
*
* This program is provded to generate a memory resident version of the
* firmware distributed with the driver source. The generation is done automatically
* by the Visual Studio solution in example/platforms/win using the batch
* file driver/examples/platforms/win/example/call_f2decl.bat
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, const char **argv)
{
    FILE *in;
    const char *filename;
    char varname[21];
    const size_t max_varname_len = sizeof(varname) - 1;
    size_t i, j;
    int c;
    const unsigned long max_bytes_per_line = 12;
    unsigned long bytes_on_this_line, total_bytes;
    bool comma_needed;

    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        return -2;
    }
    filename = argv[1];

    /* open the binary file */
    in = fopen(filename, "rb");
    if (in == NULL) {
        fprintf(stderr, "cannot open '%s'\n", filename);
        return -1;
    }

    /* construct c variable name from filename: 1. get basename */
    for (i = strlen(filename) - 1; i > 0; i--) {
        if (filename[i] == '/' || filename[i] == '\\') {
            i++;
            break;
        }
    }
    /* construct c variable name from filename: 2. reduce to legal C identifier */
    for (j = 0; j < max_varname_len && filename[i] != 0; j++, i++) {
        if (isalnum(filename[i])) {
            varname[j] = filename[i];
        } else {
            varname[j] = '_';
        }
    }
    varname[j] = 0;

    /* generate c declarations and print to stdout */
    printf("/* Generated from '%s'\n", filename), printf(" * Copyright and licence same as original file.\n */\n");
    printf("#include <stdint.h>\n\nconst uint8_t %s[] = {\n    ", varname);
    bytes_on_this_line = 0;
    total_bytes = 0;
    comma_needed = false;
    while ((c = getc(in)) != EOF) {
        if (comma_needed) {
            printf(", ");
        } else {
            comma_needed = true;
        }
        if (bytes_on_this_line >= max_bytes_per_line) {
            printf("\n    ");
            bytes_on_this_line = 0;
        }
        printf("0x%02X", (unsigned char) c);
        bytes_on_this_line++;
        total_bytes++;
    }
    printf("\n};\n");
    printf("const uint32_t %s_len = %luUL;", varname, total_bytes);

    fclose(in);
    return 0;
}

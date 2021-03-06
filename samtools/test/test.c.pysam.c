#include "samtools.pysam.h"

/*  test/test.c -- test harness utility routines.

    Copyright (C) 2014, 2016 Genome Research Ltd.

    Author: Martin O. Pollard <mp15@sanger.ac.uk>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.  */

#include <config.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

#include "test.h"

void xfreopen(const char *path, const char *mode, FILE *stream)
{
    if (freopen(path, mode, stream) == NULL) {
        fprintf(samtools_stderr, __FILE__": error reopening %s: %s\n",
                path, strerror(errno));
        exit(2);
    }
}

void dump_hdr(const bam_hdr_t* hdr)
{
    fprintf(samtools_stdout, "n_targets: %d\n", hdr->n_targets);
    fprintf(samtools_stdout, "ignore_sam_err: %d\n", hdr->ignore_sam_err);
    fprintf(samtools_stdout, "l_text: %u\n", hdr->l_text);
    fprintf(samtools_stdout, "idx\ttarget_len\ttarget_name:\n");
    int32_t target;
    for (target = 0; target < hdr->n_targets; ++target) {
        fprintf(samtools_stdout, "%d\t%u\t\"%s\"\n", target, hdr->target_len[target], hdr->target_name[target]);
    }
    fprintf(samtools_stdout, "text: \"%s\"\n", hdr->text);
}

/*
 * rds.c
 *
 *  Created on: 03-07-2016
 *      Author: Tomek
 */

#include <sys/err.h>
#include <stdint.h>
#include <util/elems.h>

#define DEBUG
#include <dev/debug.h>

/* standard rds block size in bits */
#define BLOCK_SIZE							26
/* blocks in group, numbers correspond to syndromes */
#define BLOCK_A								0
#define BLOCK_B								1
#define BLOCK_C								2
#define BLOCK_D								3
/* 2nd variant of C block */
#define BLOCK_CA							4

/* currently processed word, bit count */
static uint32_t word, count;
/* currently expected block in group */
static int exp_block = BLOCK_A;
/* group that we are trying to re-assembly from incoming blocks (data only,
 * no check word thus 16b is sufficient) */
static uint16_t group[4];
/* parity matrix */
static const uint16_t pm[BLOCK_SIZE] = {
	0x0200, 0x0100, 0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004,
	0x0002, 0x0001, 0x02dc, 0x016e, 0x00b7, 0x0287, 0x039f, 0x0313,
	0x0355, 0x0376, 0x01bb, 0x0201, 0x03dc, 0x01ee, 0x00f7, 0x02a7,
	0x038f, 0x031b,
};
/* syndromes (last two entries have been substituted for eachother to allow for
 * using block #defines as group table indices */
static const uint16_t syndrome[5] = { 0x03d8, 0x03d4, 0x025c, 0x0258, 0x03cc };
/* radio text buffer, program service buffer */
static char rt[2][65], ps[9];

/* check for data integrity, return block id if we have a syndrome match */
static int RDS_VerifyCheckword(uint32_t w)
{
	/* checksum word */
	uint16_t chk = 0;
	/* status */
	int rc = EFATAL;

	/* process checksum word */
	for (int i = 0; i < BLOCK_SIZE; i++)
		if (w & (1 << i))
			chk ^= pm[BLOCK_SIZE - i - 1];

	/* check whether it is equal to syndrome */
	for (int i = 0; i < (int)elems(syndrome) && rc == EFATAL; i++)
		if (chk == syndrome[i])
			rc = i;

	/* report status */
	return rc;
}

/* process received group */
static void RDS_Process(uint16_t gr[4])
{
	/* group type (contained in block b) */
	int gt = gr[BLOCK_B] >> 11;

	/* switch on group type */
	switch (gt) {
	/* 0A and 0B groups - these contain program service name */
	case 0 :
	case 1 : {
		/* data offset */
		int offset = gr[BLOCK_B] & 0x3;
		/* store data */
		ps[offset * 2 + 0] = (gr[BLOCK_D] >> 8) & 0xff;
		ps[offset * 2 + 1] = (gr[BLOCK_D] >> 0) & 0xff;
		/* display string */
		dprintf_i("PS> %s\n", ps);
	} break;
	/* 2A groups contain radio text */
	case 4 : {
		/* text A/B flag, offset */
		int text_ab = (gr[BLOCK_B] >> 4) & 1, offset = gr[BLOCK_B] & 0xf;
		/* 4 characters per group */
		rt[text_ab][offset * 4 + 0] = (gr[BLOCK_C] >> 8) & 0xff;
		rt[text_ab][offset * 4 + 1] = (gr[BLOCK_C] >> 0) & 0xff;
		rt[text_ab][offset * 4 + 2] = (gr[BLOCK_D] >> 8) & 0xff;
		rt[text_ab][offset * 4 + 3] = (gr[BLOCK_D] >> 0) & 0xff;
		/* display string */
		dprintf_i("RT %d> %s\n", text_ab, rt[text_ab]);
	}
	/* 2B groups contain radio text */
	case 5 : {
		/* text A/B flag, offset */
		int text_ab = (gr[BLOCK_B] >> 4) & 1, offset = gr[BLOCK_B] & 0xf;
		/* 2 characters per group */
		rt[text_ab][offset * 2 + 0] = (gr[BLOCK_D] >> 8) & 0xff;
		rt[text_ab][offset * 2 + 1] = (gr[BLOCK_D] >> 0) & 0xff;
		/* display string */
		dprintf_i("RT %d> %s\n", text_ab, rt[text_ab]);
	} break;
	}
}

/* initialize rds module */
int RDS_Init(void)
{
	/* report status */
	return EOK;
}

/* input binary data */
void RDS_Input(uint32_t data, int bit_num)
{
	/* process every bit starting from msb */
	while (--bit_num >= 0) {
		/* update word */
		word = word << 1 | ((data >> bit_num) & 1);
		/* update bit count */
		if (++count < 26)
			continue;

		/* get block number */
		int block = RDS_VerifyCheckword(word);
		/* invalid checkword */
		if (block == EFATAL) {
			/* in middle of group reception and bit counter exceeded? */
			if (exp_block != BLOCK_A)
				count = 0, exp_block = BLOCK_A;
			/* no point in processing */
			continue;
		}

		/* switch on expected block */
		switch (exp_block) {
		/* two variant block */
		case BLOCK_C :
			if (block == BLOCK_CA)
				block = BLOCK_C;
		/* other blocks come in one variant only */
		case BLOCK_A :
		case BLOCK_B :
		case BLOCK_D : {
			/* blocks matched? */
			if (exp_block == block) {
				count = 0;
				/* store the part that contains data */
				group[exp_block] = word >> 10;
				/* end of block collecting? */
				if (exp_block == BLOCK_D) {
					exp_block = BLOCK_A;
					/* decode group */
					RDS_Process(group);
				/* skip over second variant of C block */
				} else if (exp_block == BLOCK_C) {
					exp_block = BLOCK_D;
				} else {
					exp_block++;
				}
			/* out of sequence */
			} else {
				block = BLOCK_A;
			}
		} break;
		}
	}
}

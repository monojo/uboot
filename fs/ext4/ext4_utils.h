/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _EXT4_UTILS_H_
#define _EXT4_UTILS_H_

#include <asm/types.h>
#include <common.h>
#include <part.h>
#include <config.h>
#include <command.h>
#include <image.h>
#include <linux/ctype.h>
#include <asm/byteorder.h>
#include <ext2fs.h>

#ifdef NULL
#undef NULL
#endif

#define NULL (void*) 0


extern int force;

#define warn(fmt, args...) do { printf( "warning: %s: " fmt "\n", __func__, ## args); } while (0);
#define error(fmt, args...) do { printf( "error: %s: " fmt "\n", __func__, ## args); }  while (0);
#define error_errno(s) error(s)
#define critical_error(fmt, args...) do { printf("critical error: %s: " fmt "\n", __func__, ## args); } while (0)
#define critical_error_errno(s) printf(s)

#define EXT4_SUPER_MAGIC 0xEF53
#define EXT4_JNL_BACKUP_BLOCKS 1

#define EXT4_DIV_ROUND_UP(x, y) (((x) + (y) - 1)/(y))
#define EXT4_ALIGN(x, y) ((y) * EXT4_DIV_ROUND_UP((x), (y)))

struct block_group_info;

struct ext2_group_desc {
	__le32 bg_block_bitmap;
	__le32 bg_inode_bitmap;
	__le32 bg_inode_table;
	__le16 bg_free_blocks_count;
	__le16 bg_free_inodes_count;
	__le16 bg_used_dirs_count;
	__le16 bg_pad;
	__le32 bg_reserved[3];
};

struct fs_info {
	s64 len;	/* If set to 0, ask the block device for the size,
			 * if less than 0, reserve that much space at the
			 * end of the partition, else use the size given. */
	u32 block_size;
	u32 blocks_per_group;
	u32 inodes_per_group;
	u32 inode_size;
	u32 inodes;
	u32 journal_blocks;
	u16 feat_ro_compat;
	u16 feat_compat;
	u16 feat_incompat;
	u32 bg_desc_reserve_blocks;
	const char *label;
	u8 no_journal;
};

struct fs_aux_info {
	struct ext4_super_block *sb;
	struct ext4_super_block **backup_sb;
	struct ext2_group_desc *bg_desc;
	struct block_group_info *bgs;
	u32 first_data_block;
	u64 len_blocks;
	u32 inode_table_blocks;
	u32 groups;
	u32 bg_desc_blocks;
	u32 default_i_flags;
	u32 blocks_per_ind;
	u32 blocks_per_dind;
	u32 blocks_per_tind;
};

extern struct fs_info info;
extern struct fs_aux_info aux_info;

static inline int log_2(int j)
{
	int i;

	for (i = 0; j > 0; i++)
		j >>= 1;

	return i - 1;
}

void ext4_malloc_init(void);
void* ext4_malloc(unsigned int size);
void* ext4_calloc(unsigned int size, unsigned int cnt);
void ext4_free(void* ptr);
int ext4_bg_has_super_block(int bg);
void write_ext4_image(block_dev_desc_t *dev_desc, disk_partition_t *part,const char *filename, int gz, int sparse, int crc,
		int wipe);
void ext4_create_fs_aux_info(void);
void ext4_free_fs_aux_info(void);
void ext4_fill_in_sb(void);
void ext4_create_resize_inode(void);
void ext4_create_journal_inode(void);
void ext4_update_free(void);
void ext4_queue_sb(void);
u64 get_file_size(const char *filename);
u64 parse_num(const char *arg);
void ext4_parse_sb(struct ext4_super_block *sb);

#endif

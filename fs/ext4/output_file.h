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
#include <linux/types.h>


struct output_file;

struct output_file *open_output_file(const char *filename, int gz, int sparse);
void write_data_block(block_dev_desc_t *dev_desc, disk_partition_t* part, u64 off, u8 *data, int len);
void write_fill_block(block_dev_desc_t *dev_desc, disk_partition_t* part, u64 off, u32 fill_val, int len);
void write_data_file(u64 off, const char *file,
		     int offset, int len);
void pad_output_file(u64 len);
void close_output_file(struct output_file *out);

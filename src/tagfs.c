/**
 * TagFS Filesystem. Allows a user to browse their files through tags instead of the traditional hierarchical method. Implemented using Filesystem in USErspace (FUSE).
 *
 * @file tagfs.c
 * @author Keith Woelke
 * @date 07/25/2010
 */

#include "tagfs_common.h"
#include "tagfs_db.h"
#include "tagfs_debug.h"

#include <assert.h>
#include <errno.h>
#include <fuse.h>
#include <string.h>

int tagfs_getattr(const char *path, struct stat *statbuf) {
	DEBUG(ENTRY);
	const char *file_location = NULL;
	int file_id = 0;
	int retstat = 0;

	INFO("Retrieving attributes for %s", path);

	if (valid_path_to_file(path)) {
		file_id = file_id_from_path(path);
		file_location = db_get_file_location(file_id);

		retstat = stat(file_location, statbuf);

		assert(file_location != NULL);
		free((void *)file_location);
		file_location = NULL;
	}
	else if(valid_path_to_folder(path)) {
		statbuf->st_mode = S_IFDIR | 0755;
	}
	else {
		retstat = -ENOENT;
	}

	DEBUG(EXIT);
	return retstat;
}

int tagfs_readlink(const char *path, char *link, size_t size) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_mknod(const char *path, mode_t mode, dev_t dev) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_mkdir(const char *path, mode_t mode) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_unlink(const char *path) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_rmdir(const char *path) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_symlink(const char *path, const char *link) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_rename(const char *path, const char *newpath) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_link(const char *path, const char *newpath) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_chmod(const char *path, mode_t mode) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_chown(const char *path, uid_t uid, gid_t gid) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_truncate(const char *path, off_t newsize) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_utime(const char *path, struct utimbuf *ubuf) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_open(const char *path, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_statfs(const char *path, struct statvfs *statv) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_flush(const char *path, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_release(const char *path, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_setxattr(const char *path, const char *name, const char *value, size_t size, int flags) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_getxattr(const char *path, const char *name, char *value, size_t size) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_listxattr(const char *path, char *list, size_t size) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_removexattr(const char *path, const char *name) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_opendir(const char *path, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int *file_array = NULL;
	char **folder_array = NULL;
	int i = 0;
	int num_files = 0;
	int num_folders = 0;
	int retstat = 0;
	int file_id = 0;
	char *file_name = NULL;
	
	INFO("Reading directory %s", path);

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);

	num_files = files_at_location(path, &file_array);
	for(i = 0; i < num_files; i++) {
		DEBUG("FILLING %d", file_array[i]);
		file_id = file_array[i];
		file_name = file_name_from_id(file_id);
		filler(buf, file_name, NULL, 0);
		free(file_name);
	}

	free(file_array);

//	free_char_ptr_array(&file_array, num_files);

	num_folders = folders_at_location(path, file_array, &folder_array);
	for(i = 0; i < num_folders; i++) {
		DEBUG("FILLING %s", folder_array[i]);
		filler(buf, folder_array[i], NULL, 0);
		free(folder_array[i]);
	}

	free(folder_array);
//	free_char_ptr_array(&folder_array, num_folders);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_releasedir(const char *path, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

void *tagfs_init(struct fuse_conn_info *conn) {
	const char *db_name = "tagfs.sl3";
	const char *log_name = "log_file.txt";
	const char *log_path = NULL;
	int written = 0; /* number of characters written by snprintf */
	int dir_length = 0;
	int log_dir_length = 0;
	int db_dir_length = 0;

	/* get directory length */
	dir_length = strlen(TAGFS_DATA->exec_dir) + strlen("/");

	/* set log path */
	log_dir_length = strlen(log_name) + dir_length;
	log_path = malloc(log_dir_length * sizeof(*log_path) + 1);
	assert(log_path != NULL);
	written = snprintf((char *)log_path, log_dir_length + 1, "%s/%s", TAGFS_DATA->exec_dir, log_name);
	assert(written == log_dir_length);

	printf("Initializing TagFS Filesystem...\n");
	printf("Opening log file: %s\n", log_name);
	TAGFS_DATA->log_file = fopen(log_path, "w");

	DEBUG(ENTRY);

	/* set database path */
	db_dir_length = strlen(db_name) + dir_length;
	TAGFS_DATA->db_path = malloc(db_dir_length * sizeof(*TAGFS_DATA->db_path) + 1);
	written = snprintf((char *)TAGFS_DATA->db_path, db_dir_length + 1, "%s/%s", TAGFS_DATA->exec_dir, db_name);
	assert(written == db_dir_length);

	assert(log_path != NULL);
	free((void *)log_path);
	log_path = NULL;

	DEBUG(EXIT);
	return TAGFS_DATA;
}

void tagfs_destroy(void *userdata) {
	DEBUG(ENTRY);
	struct tagfs_state *tagfs_data = (struct tagfs_state *)userdata;

	DEBUG("Finalizing data...");

	assert(tagfs_data->exec_dir != NULL);
	free((void *)tagfs_data->exec_dir);
	tagfs_data->exec_dir = NULL;

	assert(tagfs_data->db_path != NULL);
	free((void *)tagfs_data->db_path);
	tagfs_data->db_path = NULL;

	DEBUG(EXIT);

	assert(tagfs_data->log_file != NULL);
	fclose(tagfs_data->log_file);
	tagfs_data->log_file = NULL;
}

int tagfs_access(const char *path, int mask) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_ftruncate(const char *path, off_t offset, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

int tagfs_fgetattr(const char *path, struct stat *statbuf, struct fuse_file_info *fi) {
	DEBUG(ENTRY);
	int retstat = 0;

	ERROR("TODO: %s", __FUNCTION__);

	DEBUG(EXIT);
	return retstat;
}

struct fuse_operations tagfs_oper = {
  .getattr = tagfs_getattr,
  .readlink = tagfs_readlink,
  .mknod = tagfs_mknod,
  .mkdir = tagfs_mkdir,
  .unlink = tagfs_unlink,
  .rmdir = tagfs_rmdir,
  .symlink = tagfs_symlink,
  .rename = tagfs_rename,
  .link = tagfs_link,
  .chmod = tagfs_chmod,
  .chown = tagfs_chown,
  .truncate = tagfs_truncate,
  .utime = tagfs_utime,
//  .open = tagfs_open,
//  .read = tagfs_read,
  .write = tagfs_write,
//  .statfs = tagfs_statfs,
//  .flush = tagfs_flush,
//  .release = tagfs_release,
  .fsync = tagfs_fsync,
  .setxattr = tagfs_setxattr,
  .getxattr = tagfs_getxattr,
  .listxattr = tagfs_listxattr,
  .removexattr = tagfs_removexattr,
//  .opendir = tagfs_opendir,
  .readdir = tagfs_readdir,
//  .releasedir = tagfs_releasedir,
  .fsyncdir = tagfs_fsyncdir,
  .init = tagfs_init,
  .destroy = tagfs_destroy,
//  .access = tagfs_access,
//  .create = tagfs_create,
  .ftruncate = tagfs_ftruncate,
//  .fgetattr = tagfs_fgetattr
};

int main(int argc, char *argv[]) {
	struct tagfs_state tagfs_data;

	debug_init();
	tagfs_data.exec_dir = get_exec_dir(argv[0]);
	
	return fuse_main(argc, argv, &tagfs_oper, &tagfs_data);
} /* main */

SELECT file_name FROM files LEFT JOIN file_has_tag ON files.file_id == file_has_tag.file_id WHERE tag_id IS NULL
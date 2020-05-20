aux_source_directory(. BASE_DIR_ALL_SOURCE)

add_library(base ${BASE_DIR_ALL_SOURCE} task.cpp task.h QueueManager.cpp QueueManager.h)
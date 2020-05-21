aux_source_directory(. BASE_DIR_ALL_SOURCE)
set(BASE_SRC
        Mail.cpp
        Producer.cpp
        Queue_s.cpp
        QueueManager.cpp
        Task.cpp
        utility.hpp
        MailServer.cpp MailServer.h)

add_library(base ${BASE_SRC})
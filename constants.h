#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace PushTheScreen {
        static const char* const CREATE_IMG_TABLE_SQL = "CREATE TABLE IF NOT EXISTS images ("
                                                        "iid integer primary key, "
                                                        "img_data blob)";


        static const char* const CREATE_MESSAGES_TABLE_SQL = "CREATE TABLE IF NOT EXISTS messages ("
                                                        "mid integer, "
                                                        "iid integer, "
                                                        "puid integer, "
                                                        "uid integer, "
                                                        "align integer, "
                                                        "color integer, "
                                                        "create_time datetime, "
                                                        "font_size integer, "
                                                        "message varchar(200), "
                                                        "readed integer, "
                                                        "sh_color integer"
                                                        ")";

        static const char* const DB_NAME = "c:\\Data\\pushthescreen.db";
    }

#endif /* CONSTANTS_H_ */

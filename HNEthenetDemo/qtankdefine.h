#ifndef WBDEF_H
#define WBDEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef bool BOOL;
typedef int		s32;
typedef unsigned int   u32;
typedef unsigned char	u8;
typedef unsigned short  u16;
typedef short           s16;
typedef char            s8;
typedef long int		s64;
typedef unsigned long int u64;
typedef unsigned char uint8_t;

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR   1
#endif

#ifndef SEEK_END
#define SEEK_END   2
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef NULL
#define NULL   0
#endif

enum {
    Auth_Id = 0,
    Auth_Name,
    Auth_Passwd,
    Auth_Authrity,
    Auth_Creater,
    Auth_CreateTime,
    Auth_Comment,
};

enum {
    Lib_Id = 0,
    Lib_Name,
    Lib_Creater,
    Lib_CreateTime,
    Lib_Comment,
};

enum {
    Authority_Id = 0,
    Authority_Level,
};

enum {
    Method_Id = 0,
    Method_Name,
    Method_Type,
    Method_Vessel,
};

enum {
    Stage_Id = 0,
    Stage_Index,
    Stage_Vessel,
    Stage_Timeramp,
    Stage_Presspsi,
    Stage_Tempture,
    Stage_Hold,
    Stage_MethodId,
};


enum{
    Type_Standard = 0,
    Type_Temprature,
    Type_Stressure,
    Type_Extract,
};

enum {
    Login_Request,
    Login_Success,
};

enum{
    Language_English,
    Language_Chinese,
};

enum {
    FILE_NAME,
    FILE_ID,
    FILE_SIZE,
    FILE_DATE,
    FILE_MAX,
};

enum {
    DIR_NAME,
    DIR_CODE,
    DIR_PATH,
    DIR_MAX,
};

enum {
    Event_ID,
    Event_Name,
    Event_Time,
    Event_User,
    Event_Content,
};

enum {
    Event_TypeId,
    Event_TypeName,
};

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

#define MAX_LEN 1024

#define CONFIG_PATH "./conf"
#define LOG_PATH "./log"
#define DB_PATH "./db"
#define DB_METHOD "./db/Method"
#define DB_DATA "./db/Data"
#define AV_PATH "./res"
#define DB_TYPE "QSQLITE"
#define DB_PINYIN "PinYin"
#define DB_MANAGER "Manager"
#define DB_HANON "System"
#define DB_USER "User"
#define DB_EXTRACT "Extract"
#define DB_REPORT_P "Data/Method_Time.db"
#define DB_EVENT "SysEvent"
#define TABLE_USERINFO "User"
#define TABLE_AUTHORITY "Authority"
#define TABLE_LIBRARY "Library"
#define TABLE_METHOD "Method"
#define TABLE_STAGE "Stage"
#define TABLE_EVENT "Event"
#define TABLE_EVTYPE "Type"

#define WARNING "Warning"
#define NOTICE "Notice"

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif // WBDEF_H

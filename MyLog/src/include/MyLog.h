//
// Created by Total on 2019/11/7.
//

#ifndef TEST_MYLOG_H
#define TEST_MYLOG_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdint.h>
#include <ios>

typedef  enum log_rank{
    INFO,
    WARNING,
    ERROR,
    FATAL
}log_rank_t;

void init_mylog(const std::string&info_log_filename,
        const std::string&warn_log_filename,
        const std::string&error_log_filename);

class MyLog {
    friend void init_mylog(const std::string&info_log_filename,
                           const std::string&warn_log_filename,
                           const std::string&error_log_filename);

public:
    MyLog() = default;
    MyLog(log_rank_t log_rank) : m_log_rank(log_rank){};

    static std::ostream& start(log_rank_t log_rank, const int32_t line, const std::string& function);

    virtual ~MyLog();

    MyLog(const MyLog&) = delete;
    MyLog& operator=(const MyLog&) = delete;

private:
    static std::ostream& getStream(log_rank_t log_rank);

    static std::ofstream m_info_log_file;
    static std::ofstream m_warn_log_file;
    static std::ofstream m_error_log_file;
    log_rank_t m_log_rank;
};


///
/// \brief 根据不同等级进行用不同的输出流进行读写
///
#define LOG(log_rank)   MyLog(log_rank).start(log_rank, __LINE__,__FUNCTION__)

///
/// \brief 利用日记进行检查的各种宏
///
#define CHECK(a)                                            \
   if(!(a)) {                                              \
       LOG(ERROR) << " CHECK failed " << endl              \
                   << #a << "= " << (a) << endl;          \
       abort();                                            \
   }                                                      \

#define CHECK_NOTNULL(a)                                    \
   if( NULL == (a)) {                                      \
       LOG(ERROR) << " CHECK_NOTNULL failed "              \
                   << #a << "== NULL " << endl;           \
       abort();                                            \
    }

#define CHECK_NULL(a)                                       \
   if( NULL != (a)) {                                      \
       LOG(ERROR) << " CHECK_NULL failed " << endl         \
                   << #a << "!= NULL " << endl;           \
       abort();                                            \
    }


#define CHECK_EQ(a, b)                                      \
   if(!((a) == (b))) {                                     \
       LOG(ERROR) << " CHECK_EQ failed "  << endl          \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_NE(a, b)                                      \
   if(!((a) != (b))) {                                     \
       LOG(ERROR) << " CHECK_NE failed " << endl           \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_LT(a, b)                                      \
   if(!((a) < (b))) {                                      \
       LOG(ERROR) << " CHECK_LT failed "                   \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_GT(a, b)                                      \
   if(!((a) > (b))) {                                      \
       LOG(ERROR) << " CHECK_GT failed "  << endl          \
                  << #a <<" = " << (a) << endl            \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_LE(a, b)                                      \
   if(!((a) <= (b))) {                                     \
       LOG(ERROR) << " CHECK_LE failed "  << endl          \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_GE(a, b)                                      \
   if(!((a) >= (b))) {                                     \
       LOG(ERROR) << " CHECK_GE failed "  << endl          \
                   << #a << " = "<< (a) << endl            \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_DOUBLE_EQ(a, b)                               \
   do {                                                    \
       CHECK_LE((a), (b)+0.000000000000001L);              \
       CHECK_GE((a), (b)-0.000000000000001L);              \
    }while (0)

#endif //TEST_MYLOG_H

//
// Created by Total on 2019/11/7.
//

#include "MyLog.h"
#include <ctime>

std::ofstream MyLog::m_error_log_file;
std::ofstream MyLog::m_info_log_file;
std::ofstream MyLog::m_warn_log_file;

void init_mylog(const std::string&info_log_filename,
                const std::string&warn_log_filename,
                const std::string&error_log_filename){
    MyLog::m_info_log_file.open(info_log_filename.c_str(),std::ios::app);
    MyLog::m_warn_log_file.open(warn_log_filename.c_str(),std::ios::app);
    MyLog::m_error_log_file.open(error_log_filename.c_str(),std::ios::app);
}

std::ostream& MyLog::getStream(log_rank_t log_rank) {
    return (INFO == log_rank) ?
           (m_info_log_file.is_open()?m_info_log_file : std::cout) :
           (WARNING == log_rank ?
           (m_warn_log_file.is_open()? m_warn_log_file : std:: cerr) :
           (m_error_log_file.is_open()? m_error_log_file : std::cerr));
}

std::ostream& MyLog::start(log_rank_t log_rank, const int32_t line, const std::string &function) {
    time_t tm;
    time(&tm);
    char time_string[128];
    ctime_r(&tm,time_string);
    return getStream(log_rank) << time_string
    << "function (" << function << ") "
    << "line" << line << " "
    << std::flush;
}

MyLog::~MyLog() {
    getStream(m_log_rank) << std::endl << std::flush;

    if(FATAL == m_log_rank){
        m_info_log_file.close();
        m_error_log_file.close();
        m_warn_log_file.close();
        abort();
    }
}

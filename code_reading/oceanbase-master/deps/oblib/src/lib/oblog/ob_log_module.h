/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#ifndef OCEANBASE_LIB_OBLOG_OB_LOG_MODULE_
#define OCEANBASE_LIB_OBLOG_OB_LOG_MODULE_
#include <stdint.h>
#include <stdio.h>

#include "ob_log_level.h"
#include "ob_log_print_kv.h"
#include "lib/hash/fnv_hash.h"

namespace oceanbase {
namespace common {
#define LOG_MOD_BEGIN(ModName) \
  struct OB_LOG_##ModName {    \
    enum {

#define LOG_MOD_END(ModName) \
  }                          \
  ;                          \
  }                          \
  ;

#define DEFINE_LOG_SUB_MOD(ModName) M_##ModName,

// Currently it is divided by directory. Each module can be adjusted according to the specific situation during the use
// process After adding or modifying modules in this file, remember to make corresponding modifications in
// ob_log_module.ipp The number of modules is limited, see OB_LOG_MAX_PAR_MOD_SIZE for details statement of parent
// modules
LOG_MOD_BEGIN(ROOT)                  // src directory
DEFINE_LOG_SUB_MOD(CLIENT)           // client
DEFINE_LOG_SUB_MOD(CLOG)             // clog
DEFINE_LOG_SUB_MOD(COMMON)           // observer
DEFINE_LOG_SUB_MOD(ELECT)            // election
DEFINE_LOG_SUB_MOD(LIB)              // lib
DEFINE_LOG_SUB_MOD(OFS)              // OFS
DEFINE_LOG_SUB_MOD(RPC)              // rpc
DEFINE_LOG_SUB_MOD(RS)               // rootserver
DEFINE_LOG_SUB_MOD(BOOTSTRAP)        // rootserver
DEFINE_LOG_SUB_MOD(SERVER)           // rpc, common/server_framework
DEFINE_LOG_SUB_MOD(SHARE)            // share
DEFINE_LOG_SUB_MOD(SQL)              // sql
DEFINE_LOG_SUB_MOD(PL)               // pl
DEFINE_LOG_SUB_MOD(JIT)              // jit
DEFINE_LOG_SUB_MOD(STORAGE)          // storage, blocksstable
DEFINE_LOG_SUB_MOD(TLOG)             // liboblog
DEFINE_LOG_SUB_MOD(STORAGETEST)      // storagetest
DEFINE_LOG_SUB_MOD(LOGTOOL)          // logtool
DEFINE_LOG_SUB_MOD(WRS)              // weak read service
DEFINE_LOG_SUB_MOD(ARCHIVE)          // archive log
DEFINE_LOG_SUB_MOD(RESTORE_ARCHIVE)  // archive restore log
DEFINE_LOG_SUB_MOD(EASY)             // libeasy
LOG_MOD_END(ROOT)

// statement of WRS's sub_modules
LOG_MOD_BEGIN(WRS)
DEFINE_LOG_SUB_MOD(CLUSTER)
DEFINE_LOG_SUB_MOD(SERVER)
LOG_MOD_END(WRS)

// statement of LIB's sub-modules
LOG_MOD_BEGIN(LIB)           // lib directory
DEFINE_LOG_SUB_MOD(ALLOC)    // allocator
DEFINE_LOG_SUB_MOD(CONT)     // all container except hash: list, queue, array, hash
DEFINE_LOG_SUB_MOD(FILE)     // file
DEFINE_LOG_SUB_MOD(HASH)     // hash
DEFINE_LOG_SUB_MOD(LOCK)     // lock
DEFINE_LOG_SUB_MOD(MYSQLC)   // internal mysqlclient
DEFINE_LOG_SUB_MOD(STRING)   // string
DEFINE_LOG_SUB_MOD(TIME)     // time
DEFINE_LOG_SUB_MOD(UTIL)     // utility
DEFINE_LOG_SUB_MOD(CHARSET)  // charset
DEFINE_LOG_SUB_MOD(WS)       // word segment
LOG_MOD_END(LIB)

// statement of OFS's sub-modules
LOG_MOD_BEGIN(OFS)               // OFS directory
DEFINE_LOG_SUB_MOD(BLOCK)        // block
DEFINE_LOG_SUB_MOD(BLOCKSERVER)  // blockserver
DEFINE_LOG_SUB_MOD(CLIENT)       // client
DEFINE_LOG_SUB_MOD(CLUSTER)      // cluster
DEFINE_LOG_SUB_MOD(COMMON)       // common
DEFINE_LOG_SUB_MOD(FILE)         // file
DEFINE_LOG_SUB_MOD(MASTER)       // master
DEFINE_LOG_SUB_MOD(STREAM)       // stream
DEFINE_LOG_SUB_MOD(RPC)          // rpc
DEFINE_LOG_SUB_MOD(UTIL)         // util
DEFINE_LOG_SUB_MOD(FS)           // fs
DEFINE_LOG_SUB_MOD(REGRESSION)   // regression
DEFINE_LOG_SUB_MOD(LIBS)         // libs
DEFINE_LOG_SUB_MOD(SHARE)        // share
LOG_MOD_END(OFS)

// statements of RPC's sub-modules
LOG_MOD_BEGIN(RPC)
DEFINE_LOG_SUB_MOD(FRAME)
DEFINE_LOG_SUB_MOD(OBRPC)
DEFINE_LOG_SUB_MOD(OBMYSQL)
DEFINE_LOG_SUB_MOD(TEST)
LOG_MOD_END(RPC)

// statement of COMMON's sub-modules
LOG_MOD_BEGIN(COMMON)       // common directory
DEFINE_LOG_SUB_MOD(CACHE)   // cache
DEFINE_LOG_SUB_MOD(EXPR)    // expression
DEFINE_LOG_SUB_MOD(LEASE)   // lease
DEFINE_LOG_SUB_MOD(MYSQLP)  // mysql_proxy
DEFINE_LOG_SUB_MOD(PRI)     // privilege
DEFINE_LOG_SUB_MOD(STAT)    // stat
DEFINE_LOG_SUB_MOD(UPSR)    // ups_reclaim
LOG_MOD_END(COMMON)

// statement of SHARE's sub-modules
LOG_MOD_BEGIN(SHARE)           // share directory
DEFINE_LOG_SUB_MOD(CONFIG)     // config
DEFINE_LOG_SUB_MOD(FILE)       // file
DEFINE_LOG_SUB_MOD(INNERT)     // inner_table
DEFINE_LOG_SUB_MOD(INTERFACE)  // interface
DEFINE_LOG_SUB_MOD(LOG)        // log
DEFINE_LOG_SUB_MOD(PT)         // partition_table
DEFINE_LOG_SUB_MOD(SCHEMA)     // schema
DEFINE_LOG_SUB_MOD(TRIGGER)    // trigger
LOG_MOD_END(SHARE)

// statement of storage's sub-modules
LOG_MOD_BEGIN(STORAGE)    // storage, blocksstable directory
DEFINE_LOG_SUB_MOD(REDO)  // replay
DEFINE_LOG_SUB_MOD(COMPACTION)
DEFINE_LOG_SUB_MOD(BSST)    // blocksstable
DEFINE_LOG_SUB_MOD(MEMT)    // memtable
DEFINE_LOG_SUB_MOD(TRANS)   // transaction
DEFINE_LOG_SUB_MOD(RU)      // transaction
DEFINE_LOG_SUB_MOD(REPLAY)  // replay engine
LOG_MOD_END(STORAGE)

// statement of clog's sub-modules
LOG_MOD_BEGIN(CLOG)
DEFINE_LOG_SUB_MOD(EXTLOG)   // external fetch log
DEFINE_LOG_SUB_MOD(CSR)      // cursor cache
DEFINE_LOG_SUB_MOD(ARCHIVE)  // archive
LOG_MOD_END(CLOG)

// statement of SQL's sub-modules
LOG_MOD_BEGIN(SQL)           // sql directory
DEFINE_LOG_SUB_MOD(ENG)      // engine
DEFINE_LOG_SUB_MOD(EXE)      // execute
DEFINE_LOG_SUB_MOD(OPT)      // optimizer
DEFINE_LOG_SUB_MOD(JO)       // join order
DEFINE_LOG_SUB_MOD(PARSER)   // parser
DEFINE_LOG_SUB_MOD(PC)       // plan_cache
DEFINE_LOG_SUB_MOD(RESV)     // resolver
DEFINE_LOG_SUB_MOD(REWRITE)  // rewrite
DEFINE_LOG_SUB_MOD(SESSION)  // session
DEFINE_LOG_SUB_MOD(CG)       // code_generator
DEFINE_LOG_SUB_MOD(MONITOR)  // monitor
DEFINE_LOG_SUB_MOD(DTL)      // data transfer layer
LOG_MOD_END(SQL)

// observer submodules
LOG_MOD_BEGIN(SERVER)
DEFINE_LOG_SUB_MOD(OMT)  // user mode scheduler
LOG_MOD_END(SERVER)

// RS submodules
LOG_MOD_BEGIN(RS)
DEFINE_LOG_SUB_MOD(LB)       // load balance
DEFINE_LOG_SUB_MOD(RESTORE)  // restore related
LOG_MOD_END(RS)

// liboblog submodules
LOG_MOD_BEGIN(TLOG)
DEFINE_LOG_SUB_MOD(FETCHER)    // fetcher
DEFINE_LOG_SUB_MOD(PARSER)     // Parser
DEFINE_LOG_SUB_MOD(SEQUENCER)  // Sequencer
DEFINE_LOG_SUB_MOD(FORMATTER)  // Formatter
DEFINE_LOG_SUB_MOD(COMMITTER)  // committer
DEFINE_LOG_SUB_MOD(TAILF)      // oblog_tailf
DEFINE_LOG_SUB_MOD(SCHEMA)     // schema
LOG_MOD_END(TLOG)

// easy submodules
LOG_MOD_BEGIN(EASY)
DEFINE_LOG_SUB_MOD(IO)  // EasyIO
LOG_MOD_END(EASY)

// storagetest submodules
LOG_MOD_BEGIN(STORAGETEST)
DEFINE_LOG_SUB_MOD(TEST)  // Parser
LOG_MOD_END(STORAGETEST)
}  // namespace common
}  // namespace oceanbase

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)
#define OB_LOG_LOCATION_HASH_VAL                                                                                 \
  ({                                                                                                             \
    constexpr uint64_t hash_val = oceanbase::common::hash::fnv_hash_for_logger(__FILE__ "" STRINGIZE(__LINE__)); \
    hash_val;                                                                                                    \
  })
#define OB_LOG_LEVEL(level) OB_LOG_LEVEL_##level, __FILE__, __LINE__, _fun_name_, OB_LOG_LOCATION_HASH_VAL
#define OB_LOG_LEVEL_DIRECT(level) OB_LOG_LEVEL_##level, __FILE__, __LINE__, __FUNCTION__, OB_LOG_LOCATION_HASH_VAL
#define OB_LOG_NUM_LEVEL(level) level, __FILE__, __LINE__, __FUNCTION__, OB_LOG_LOCATION_HASH_VAL

#define _OB_PRINT(modName, level, _fmt_, args...)                                                           \
  (OB_LOGGER.is_async_log_used() ? OB_LOGGER.async_log_message(modName, OB_LOG_LEVEL(level), _fmt_, ##args) \
                                 : OB_LOGGER.log_message(modName, OB_LOG_LEVEL(level), _fmt_, ##args))

#define GET_SECOND(f, s, ...) s
#define MACRO_CALL(x, y) x(y)
#define MACRO_ARGS(x) MACRO_ARGS_##x, FOR_DEFAULT
#define MACRO_ARGS_DEBUG , FOR_DEBUG

#ifdef ENABLE_DEBUG_LOG
#define IS_LOG_ENABLED_FOR_DEBUG true
#else
#ifdef NDEBUG
#define IS_LOG_ENABLED_FOR_DEBUG false
#else
#define IS_LOG_ENABLED_FOR_DEBUG true
#endif
#endif
#define IS_LOG_ENABLED_FOR_DEFAULT true
#define IS_LOG_ENABLED(level) LOG_MACRO_JOIN(IS_LOG_ENABLED_, MACRO_CALL(GET_SECOND, MACRO_ARGS(level)))

#define GET_LOG_FUNC_ATTR_FOR_DEBUG always_inline
#define GET_LOG_FUNC_ATTR_FOR_DEFAULT noinline, cold
#define GET_LOG_FUNC_ATTR(level) LOG_MACRO_JOIN(GET_LOG_FUNC_ATTR_, MACRO_CALL(GET_SECOND, MACRO_ARGS(level)))

#define OB_LOG(level, infoString, args...)                                                 \
  do {                                                                                     \
    if (IS_LOG_ENABLED(level)) {                                                           \
      if (OB_LOG_NEED_TO_PRINT(level)) {                                                   \
        ::oceanbase::common::OB_PRINT("", OB_LOG_LEVEL_DIRECT(level), infoString, ##args); \
      }                                                                                    \
    }                                                                                      \
  } while (false)

#define _OB_LOG(level, _fmt_, args...)                                                 \
  do {                                                                                 \
    if (IS_LOG_ENABLED(level)) {                                                       \
      [&](const char* _fun_name_) __attribute__((GET_LOG_FUNC_ATTR(level)))            \
      {                                                                                \
        (OB_LOG_NEED_TO_PRINT(level) ? _OB_PRINT("", level, _fmt_, ##args) : (void)0); \
      }                                                                                \
      (__FUNCTION__);                                                                  \
    }                                                                                  \
  } while (false)

#define _OB_NUM_LEVEL_LOG(level, _fmt_, args...) \
  (OB_LOGGER.need_to_print(level) ? OB_LOGGER.log_message("", OB_LOG_NUM_LEVEL(level), _fmt_, ##args) : (void)0)

#define _OB_NUM_LEVEL_PRINT(level, _fmt_, args...) OB_LOGGER.log_message("", OB_LOG_NUM_LEVEL(level), _fmt_, ##args)

#define _OB_LOG_US(level, _fmt_, args...)                  \
  _OB_LOG(level,                                           \
      "[%ld][%ld] " _fmt_,                                 \
      ::oceanbase::common::ObLogger::get_cur_tv().tv_sec,  \
      ::oceanbase::common::ObLogger::get_cur_tv().tv_usec, \
      ##args)

#define IS_OB_LOG_TRACE_MODE() OB_LOGGER.is_trace_mode()
#define SET_OB_LOG_TRACE_MODE() OB_LOGGER.set_trace_mode(true)
#define CANCLE_OB_LOG_TRACE_MODE() OB_LOGGER.set_trace_mode(false)
#define PRINT_OB_LOG_TRACE_BUF(level) \
  (OB_LOG_NEED_TO_PRINT(level) ? OB_LOGGER.print_trace_buffer(OB_LOG_LEVEL_DIRECT(level)) : (void)0)

// for tests/ob_log_test or others
#define OB_LOG_MOD_NEED_TO_PRINT(parMod, level) \
  OB_LOGGER.need_to_print(::oceanbase::common::OB_LOG_ROOT::M_##parMod, OB_LOG_LEVEL_##level)

// for tests/ob_log_test or others
#define OB_LOG_SUBMOD_NEED_TO_PRINT(parMod, subMod, level)              \
  OB_LOGGER.need_to_print(::oceanbase::common::OB_LOG_ROOT::M_##parMod, \
      ::oceanbase::common::OB_LOG_##parMod::M_##subMod,                 \
      OB_LOG_LEVEL_##level)

#define OB_MOD_LOG(parMod, level, info_string, args...)                                                   \
  do {                                                                                                    \
    if (IS_LOG_ENABLED(level)) {                                                                          \
      if (OB_LOGGER.need_to_print(::oceanbase::common::OB_LOG_ROOT::M_##parMod, OB_LOG_LEVEL_##level)) {  \
        ::oceanbase::common::OB_PRINT("[" #parMod "] ", OB_LOG_LEVEL_DIRECT(level), info_string, ##args); \
      }                                                                                                   \
    }                                                                                                     \
  } while (false)

#define _OB_MOD_LOG(parMod, level, _fmt_, args...)                                                   \
  do {                                                                                               \
    if (IS_LOG_ENABLED(level)) {                                                                     \
      [&](const char* _fun_name_) __attribute__((GET_LOG_FUNC_ATTR(level)))                          \
      {                                                                                              \
        ((OB_LOGGER.need_to_print(oceanbase::common::OB_LOG_ROOT::M_##parMod, OB_LOG_LEVEL_##level)) \
                ? _OB_PRINT("[" #parMod "] ", level, _fmt_, ##args)                                  \
                : (void)0);                                                                          \
      }                                                                                              \
      (__FUNCTION__);                                                                                \
    }                                                                                                \
  } while (false)

#define OB_SUB_MOD_LOG(parMod, subMod, level, info_string, args...)                                                   \
  do {                                                                                                                \
    if (IS_LOG_ENABLED(level)) {                                                                                      \
      if (OB_LOGGER.need_to_print(::oceanbase::common::OB_LOG_ROOT::M_##parMod,                                       \
              ::oceanbase::common::OB_LOG_##parMod::M_##subMod,                                                       \
              OB_LOG_LEVEL_##level)) {                                                                                \
        ::oceanbase::common::OB_PRINT("[" #parMod "." #subMod "] ", OB_LOG_LEVEL_DIRECT(level), info_string, ##args); \
      }                                                                                                               \
    }                                                                                                                 \
  } while (false)

#define _OB_SUB_MOD_LOG(parMod, subMod, level, _fmt_, args...)                  \
  do {                                                                          \
    if (IS_LOG_ENABLED(level)) {                                                \
      [&](const char* _fun_name_) __attribute__((GET_LOG_FUNC_ATTR(level)))     \
      {                                                                         \
        ((OB_LOGGER.need_to_print(oceanbase::common::OB_LOG_ROOT::M_##parMod,   \
             oceanbase::common::OB_LOG_##parMod::M_##subMod,                    \
             OB_LOG_LEVEL_##level))                                             \
                ? _OB_PRINT("[" #parMod "." #subMod "] ", level, _fmt_, ##args) \
                : (void)0);                                                     \
      }                                                                         \
      (__FUNCTION__);                                                           \
    }                                                                           \
  } while (false)

// define ParMod_LOG
#define BLSST_LOG(level, info_string, args...) OB_MOD_LOG(BLSST, level, info_string, ##args)
#define _BLSST_LOG(level, _fmt_, args...) _OB_MOD_LOG(BLSST, level, _fmt_, ##args)
#define CLIENT_LOG(level, info_string, args...) OB_MOD_LOG(CLIENT, level, info_string, ##args)
#define _CLIENT_LOG(level, _fmt_, args...) _OB_MOD_LOG(CLIENT, level, _fmt_, ##args)
#define CLOG_LOG(level, info_string, args...) OB_MOD_LOG(CLOG, level, info_string, ##args)
#define _CLOG_LOG(level, _fmt_, args...) _OB_MOD_LOG(CLOG, level, _fmt_, ##args)
#define EXTLOG_LOG(level, info_string, args...) OB_SUB_MOD_LOG(CLOG, EXTLOG, level, info_string, ##args)
#define _EXTLOG_LOG(level, info_string, args...) _OB_SUB_MOD_LOG(CLOG, EXTLOG, level, info_string, ##args)
#define CSR_LOG(level, info_string, args...) OB_SUB_MOD_LOG(CLOG, CSR, level, info_string, ##args)
#define _CSR_LOG(level, info_string, args...) _OB_SUB_MOD_LOG(CLOG, CSR, level, info_string, ##args)
#define COMMON_LOG(level, info_string, args...) OB_MOD_LOG(COMMON, level, info_string, ##args)
#define _COMMON_LOG(level, _fmt_, args...) _OB_MOD_LOG(COMMON, level, _fmt_, ##args)
#define ELECT_LOG(level, info_string, args...) OB_MOD_LOG(ELECT, level, info_string, ##args)
#define _ELECT_LOG(level, _fmt_, args...) _OB_MOD_LOG(ELECT, level, _fmt_, ##args)
#define IMPS_LOG(level, info_string, args...) OB_MOD_LOG(IMPS, level, info_string, ##args)
#define _IMPS_LOG(level, _fmt_, args...) _OB_MOD_LOG(IMPS, level, _fmt_, ##args)
#define WRS_LOG(level, info_string, args...) OB_MOD_LOG(WRS, level, info_string, ##args)
#define _WRS_LOG(level, _fmt_, args...) _OB_MOD_LOG(WRS, level, _fmt_, ##args)
#define ARCHIVE_LOG(level, info_string, args...) OB_MOD_LOG(ARCHIVE, level, info_string, ##args)
#define _ARCHIVE_LOG(level, _fmt_, args...) _OB_MOD_LOG(ARCHIVE, level, _fmt_, ##args)
#define RESTORE_ARCHIVE_LOG(level, info_string, args...) OB_MOD_LOG(RESTORE_ARCHIVE, level, info_string, ##args)
#define _RESTORE_ARCHIVE_LOG(level, _fmt_, args...) _OB_MOD_LOG(RESTORE_ARCHIVE, level, _fmt_, ##args)
#define LIB_LOG(level, info_string, args...) OB_MOD_LOG(LIB, level, info_string, ##args)
#define _LIB_LOG(level, _fmt_, args...) _OB_MOD_LOG(LIB, level, _fmt_, ##args)
#define MEMT_LOG(level, info_string, args...) OB_MOD_LOG(MEMT, level, info_string, ##args)
#define _MEMT_LOG(level, _fmt_, args...) _OB_MOD_LOG(MEMT, level, _fmt_, ##args)
#define MRSST_LOG(level, info_string, args...) OB_MOD_LOG(MRSST, level, info_string, ##args)
#define _MRSST_LOG(level, _fmt_, args...) _OB_MOD_LOG(MRSST, level, _fmt_, ##args)
#define MYSQL_LOG(level, info_string, args...) OB_MOD_LOG(MYSQL, level, info_string, ##args)
#define _MYSQL_LOG(level, _fmt_, args...) _OB_MOD_LOG(MYSQL, level, _fmt_, ##args)
#define PS_LOG(level, info_string, args...) OB_MOD_LOG(PS, level, info_string, ##args)
#define _PS_LOG(level, _fmt_, args...) _OB_MOD_LOG(PS, level, _fmt_, ##args)
#define RPC_LOG(level, info_string, args...) OB_MOD_LOG(RPC, level, info_string, ##args)
#define _RPC_LOG(level, _fmt_, args...) _OB_MOD_LOG(RPC, level, _fmt_, ##args)
#define RS_LOG(level, info_string, args...) OB_MOD_LOG(RS, level, info_string, ##args)
#define _RS_LOG(level, _fmt_, args...) _OB_MOD_LOG(RS, level, _fmt_, ##args)
#define BOOTSTRAP_LOG(level, info_string, args...) OB_MOD_LOG(BOOTSTRAP, level, info_string, ##args)
#define _BOOTSTRAP_LOG(level, _fmt_, args...) _OB_MOD_LOG(BOOTSTRAP, level, _fmt_, ##args)
#define SERVER_LOG(level, info_string, args...) OB_MOD_LOG(SERVER, level, info_string, ##args)
#define _SERVER_LOG(level, _fmt_, args...) _OB_MOD_LOG(SERVER, level, _fmt_, ##args)
#define SHARE_LOG(level, info_string, args...) OB_MOD_LOG(SHARE, level, info_string, ##args)
#define _SHARE_LOG(level, _fmt_, args...) _OB_MOD_LOG(SHARE, level, _fmt_, ##args)
#define SQL_LOG(level, info_string, args...) OB_MOD_LOG(SQL, level, info_string, ##args)
#define _SQL_LOG(level, _fmt_, args...) _OB_MOD_LOG(SQL, level, _fmt_, ##args)
#define PL_LOG(level, info_string, args...) OB_MOD_LOG(PL, level, info_string, ##args)
#define _PL_LOG(level, _fmt_, args...) _OB_MOD_LOG(PL, level, _fmt_, ##args)
#define JIT_LOG(level, info_string, args...) OB_MOD_LOG(JIT, level, info_string, ##args)
#define _JIT_LOG(level, _fmt_, args...) _OB_MOD_LOG(JIT, level, _fmt_, ##args)
#define STORAGE_LOG(level, info_string, args...) OB_MOD_LOG(STORAGE, level, info_string, ##args)
#define _STORAGE_LOG(level, _fmt_, args...) _OB_MOD_LOG(STORAGE, level, _fmt_, ##args)
#define TRANS_LOG(level, info_string, args...) OB_SUB_MOD_LOG(STORAGE, TRANS, level, info_string, ##args)
#define _TRANS_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(STORAGE, TRANS, level, _fmt_, ##args)
#define RU_LOG(level, info_string, args...) OB_SUB_MOD_LOG(STORAGE, RU, level, info_string, ##args)
#define _RU_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(STORAGE, RU, level, _fmt_, ##args)
#define REPLAY_LOG(level, info_string, args...) OB_SUB_MOD_LOG(STORAGE, REPLAY, level, info_string, ##args)
#define _REPLAY_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(STORAGE, REPLAY, level, _fmt_, ##args)
#define OBLOG_LOG(level, info_string, args...) OB_MOD_LOG(TLOG, level, info_string, ##args)
#define _OBLOG_LOG(level, _fmt_, args...) _OB_MOD_LOG(TLOG, level, _fmt_, ##args)
#define LOGTOOL_LOG(level, info_string, args...) OB_MOD_LOG(LOGTOOL, level, info_string, ##args)
#define _LOGTOOL_LOG(level, _fmt_, args...) _OB_MOD_LOG(LOGTOOL, level, _fmt_, ##args)

// dfine ParMod_SubMod_LOG
#define WRS_CLUSTER_LOG(level, info_string, args...) OB_SUB_MOD_LOG(WRS, CLUSTER, level, info_string, ##args)
#define _WRS_CLUSTER_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(WRS, CLUSTER, level, _fmt_, ##args)
#define WRS_SERVER_LOG(level, info_string, args...) OB_SUB_MOD_LOG(WRS, SERVER, level, info_string, ##args)
#define _WRS_SERVER_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(WRS, SERVER, level, _fmt_, ##args)
#define LIB_ALLOC_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, ALLOC, level, info_string, ##args)
#define _LIB_ALLOC_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, ALLOC, level, _fmt_, ##args)
#define LIB_CHARSET_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, CHARSET, level, info_string, ##args)
#define _LIB_CHARSET_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, CHARSET, level, _fmt_, ##args)
#define LIB_CONTAIN_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, CONTAIN, level, info_string, ##args)
#define _LIB_CONTAIN_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, CONTAIN, level, _fmt_, ##args)
#define LIB_CPU_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, CPU, level, info_string, ##args)
#define _LIB_CPU_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, CPU, level, _fmt_, ##args)
#define LIB_ENCRYPT_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, ENCRYPT, level, info_string, ##args)
#define _LIB_ENCRYPT_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, ENCRYPT, level, _fmt_, ##args)
#define LIB_FILE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, FILE, level, info_string, ##args)
#define _LIB_FILE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, FILE, level, _fmt_, ##args)
#define LIB_HASH_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, HASH, level, info_string, ##args)
#define _LIB_HASH_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, HASH, level, _fmt_, ##args)
#define LIB_JASON_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, JASON, level, info_string, ##args)
#define _LIB_JASON_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, JASON, level, _fmt_, ##args)
#define LIB_LIST_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, LIST, level, info_string, ##args)
#define _LIB_LIST_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, LIST, level, _fmt_, ##args)
#define LIB_LOCK_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, LOCK, level, info_string, ##args)
#define _LIB_LOCK_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, LOCK, level, _fmt_, ##args)
#define LIB_MYSQLC_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, MYSQLC, level, info_string, ##args)
#define _LIB_MYSQLC_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, MYSQLC, level, _fmt_, ##args)
#define LIB_NUM_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, NUM, level, info_string, ##args)
#define _LIB_NUM_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, NUM, level, _fmt_, ##args)
#define LIB_OBJP_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, OBJP, level, info_string, ##args)
#define _LIB_OBJP_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, OBJP, level, _fmt_, ##args)
#define LIB_PROB_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, PROB, level, info_string, ##args)
#define _LIB_PROB_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, PROB, level, _fmt_, ##args)
#define LIB_PROFILE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, PROFILE, level, info_string, ##args)
#define _LIB_PROFILE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, PROFILE, level, _fmt_, ##args)
#define LIB_QUEUE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, QUEUE, level, info_string, ##args)
#define _LIB_QUEUE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, QUEUE, level, _fmt_, ##args)
#define LIB_REGEX_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, REGEX, level, info_string, ##args)
#define _LIB_REGEX_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, REGEX, level, _fmt_, ##args)
#define LIB_STRING_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, STRING, level, info_string, ##args)
#define _LIB_STRING_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, STRING, level, _fmt_, ##args)
#define LIB_TASK_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, TASK, level, info_string, ##args)
#define _LIB_TASK_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, TASK, level, _fmt_, ##args)
#define LIB_TRHEADL_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, THREADL, level, info_string, ##args)
#define _LIB_TRHEADL_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, THREADL, level, _fmt_, ##args)
#define LIB_TIME_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, TIME, level, info_string, ##args)
#define _LIB_TIME_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, TIME, level, _fmt_, ##args)
#define LIB_UTILITY_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, UTILITY, level, info_string, ##args)
#define _LIB_UTILITY_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, UTILITY, level, _fmt_, ##args)
#define LIB_WS_LOG(level, info_string, args...) OB_SUB_MOD_LOG(LIB, WS, level, info_string, ##args)
#define _LIB_WS_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(LIB, WS, level, _fmt_, ##args)

#define RPC_FRAME_LOG(level, _fmt_, args...) OB_SUB_MOD_LOG(RPC, FRAME, level, _fmt_, ##args)

#define _RPC_FRAME_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(RPC, FRAME, level, _fmt_, ##args)

#define RPC_OBRPC_LOG(level, _fmt_, args...) OB_SUB_MOD_LOG(RPC, OBRPC, level, _fmt_, ##args)

#define _RPC_OBRPC_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(RPC, OBRPC, level, _fmt_, ##args)

#define RPC_OBMYSQL_LOG(level, _fmt_, args...) OB_SUB_MOD_LOG(RPC, OBMYSQL, level, _fmt_, ##args)

#define _RPC_OBMYSQL_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(RPC, OBMYSQL, level, _fmt_, ##args)

#define RPC_TEST_LOG(level, _fmt_, args...) OB_SUB_MOD_LOG(RPC, TEST, level, _fmt_, ##args)

#define _RPC_TEST_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(RPC, TEST, level, _fmt_, ##args)

#define COMMON_CACHE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(COMMON, CACHE, level, info_string, ##args)
#define _COMMON_CACHE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(COMMON, CACHE, level, _fmt_, ##args)
#define COMMON_EXPR_LOG(level, info_string, args...) OB_SUB_MOD_LOG(COMMON, EXPR, level, info_string, ##args)
#define _COMMON_EXPR_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(COMMON, EXPR, level, _fmt_, ##args)
#define COMMON_LEASE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(COMMON, LEASE, level, info_string, ##args)
#define _COMMON_LEASE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(COMMON, LEASE, level, _fmt_, ##args)
#define COMMON_MYSQLP_LOG(level, info_string, args...) OB_SUB_MOD_LOG(COMMON, MYSQLP, level, info_string, ##args)
#define _COMMON_MYSQLP_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(COMMON, MYSQLP, level, _fmt_, ##args)
#define COMMON_PRI_LOG(level, info_string, args...) OB_SUB_MOD_LOG(COMMON, PRI, level, info_string, ##args)
#define _COMMON_PRI_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(COMMON, PRI, level, _fmt_, ##args)
#define COMMON_STAT_LOG(level, info_string, args...) OB_SUB_MOD_LOG(COMMON, STAT, level, info_string, ##args)
#define _COMMON_STAT_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(COMMON, STAT, level, _fmt_, ##args)
#define COMMON_UPSR_LOG(level, info_string, args...) OB_SUB_MOD_LOG(COMMON, UPSR, level, info_string, ##args)
#define _COMMON_UPSR_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(COMMON, UPSR, level, _fmt_, ##args)

#define SHARE_CONFIG_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SHARE, CONFIG, level, info_string, ##args)
#define _SHARE_CONFIG_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SHARE, CONFIG, level, _fmt_, ##args)
#define SHARE_FILE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SHARE, FILE, level, info_string, ##args)
#define _SHARE_FILE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SHARE, FILE, level, _fmt_, ##args)
#define SHARE_INNERT_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SHARE, INNERT, level, info_string, ##args)
#define _SHARE_INNERT_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SHARE, INNERT, level, _fmt_, ##args)
#define SHARE_INTERFACE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SHARE, INTERFACE, level, info_string, ##args)
#define _SHARE_INTERFACE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SHARE, INTERFACE, level, _fmt_, ##args)
#define SHARE_LOG_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SHARE, LOG, level, info_string, ##args)
#define _SHARE_LOG_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SHARE, LOG, level, _fmt_, ##args)
#define SHARE_PT_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SHARE, PT, level, info_string, ##args)
#define _SHARE_PT_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SHARE, PT, level, _fmt_, ##args)
#define SHARE_SCHEMA_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SHARE, SCHEMA, level, info_string, ##args)
#define _SHARE_SCHEMA_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SHARE, SCHEMA, level, _fmt_, ##args)
#define SHARE_TRIGGER_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SHARE, TRIGGER, level, info_string, ##args)
#define _SHARE_TRIGGER_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SHARE, TRIGGER, level, _fmt_, ##args)

#define STORAGE_REDO_LOG(level, info_string, args...) OB_SUB_MOD_LOG(STORAGE, REDO, level, info_string, ##args)
#define _STORAGE_REDO_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(STORAGE, REDO, level, _fmt_, ##args)
#define STORAGE_COMPACTION_LOG(level, info_string, args...) \
  OB_SUB_MOD_LOG(STORAGE, COMPACTION, level, info_string, ##args)
#define _STORAGE_COMPACTION_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(STORAGE, COMPACTION, level, _fmt_, ##args)

#define SQL_ENG_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, ENG, level, info_string, ##args)
#define _SQL_ENG_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, ENG, level, _fmt_, ##args)
#define SQL_EXE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, EXE, level, info_string, ##args)
#define _SQL_EXE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, EXE, level, _fmt_, ##args)
#define SQL_OPT_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, OPT, level, info_string, ##args)
#define _SQL_OPT_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, OPT, level, _fmt_, ##args)
#define SQL_JO_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, JO, level, info_string, ##args)
#define _SQL_JO_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, JO, level, _fmt_, ##args)
#define SQL_PARSER_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, PARSER, level, info_string, ##args)
#define _SQL_PARSER_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, PARSER, level, _fmt_, ##args)
#define SQL_PC_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, PC, level, info_string, ##args)
#define _SQL_PC_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, PC, level, _fmt_, ##args)
#define _SQL_PLANCACHE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, PLANCACHE, level, _fmt_, ##args)
#define SQL_RESV_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, RESV, level, info_string, ##args)
#define _SQL_RESV_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, RESV, level, _fmt_, ##args)
#define SQL_REWRITE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, REWRITE, level, info_string, ##args)
#define _SQL_REWRITE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, REWRITE, level, _fmt_, ##args)
#define SQL_SESSION_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, SESSION, level, info_string, ##args)
#define _SQL_SESSION_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, SESSION, level, _fmt_, ##args)
#define SQL_CG_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, CG, level, info_string, ##args)
#define _SQL_CG_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, CG, level, _fmt_, ##args)
#define SQL_MONITOR_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, MONITOR, level, info_string, ##args)
#define _SQL_MONITOR_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, MONITOR, level, _fmt_, ##args)
#define SQL_DTL_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SQL, DTL, level, info_string, ##args)
#define _SQL_DTL_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SQL, DTL, level, _fmt_, ##args)

// observer submodule definitions
#define SERVER_OMT_LOG(level, info_string, args...) OB_SUB_MOD_LOG(SERVER, OMT, level, info_string, ##args)
#define _SERVER_OMT_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(SERVER, OMT, level, _fmt_, ##args)

// rootserver submodule definitions
#define RS_LB_LOG(level, info_string, args...) OB_SUB_MOD_LOG(RS, LB, level, info_string, ##args)

#define RS_RESTORE_LOG(level, info_string, args...) OB_SUB_MOD_LOG(RS, RESTORE, level, info_string, ##args)
#define _RS_RESTORE_LOG(level, _fmt_, args...) _OB_SUB_MOD_LOG(RS, RESTORE, level, _fmt_, ##args)

#define STORAGETEST_LOG(level, info_string, args...) OB_SUB_MOD_LOG(STORAGETEST, TEST, level, info_string, ##args)
#define _STORAGETEST_LOG(level, info_string, args...) _OB_SUB_MOD_LOG(STORAGETEST, TEST, level, info_string, ##args)

// liboblog submod definition
#define OBLOG_FETCHER_LOG(level, fmt, args...) OB_SUB_MOD_LOG(TLOG, FETCHER, level, fmt, ##args)
#define _OBLOG_FETCHER_LOG(level, fmt, args...) _OB_SUB_MOD_LOG(TLOG, FETCHER, level, fmt, ##args)
#define OBLOG_PARSER_LOG(level, fmt, args...) OB_SUB_MOD_LOG(TLOG, PARSER, level, fmt, ##args)
#define _OBLOG_PARSER_LOG(level, fmt, args...) _OB_SUB_MOD_LOG(TLOG, PARSER, level, fmt, ##args)
#define OBLOG_SEQUENCER_LOG(level, fmt, args...) OB_SUB_MOD_LOG(TLOG, SEQUENCER, level, fmt, ##args)
#define _OBLOG_SEQUENCER_LOG(level, fmt, args...) _OB_SUB_MOD_LOG(TLOG, SEQUENCER, level, fmt, ##args)
#define OBLOG_FORMATTER_LOG(level, fmt, args...) OB_SUB_MOD_LOG(TLOG, FORMATTER, level, fmt, ##args)
#define _OBLOG_FORMATTER_LOG(level, fmt, args...) _OB_SUB_MOD_LOG(TLOG, FORMATTER, level, fmt, ##args)
#define OBLOG_COMMITTER_LOG(level, fmt, args...) OB_SUB_MOD_LOG(TLOG, COMMITTER, level, fmt, ##args)
#define _OBLOG_COMMITTER_LOG(level, fmt, args...) _OB_SUB_MOD_LOG(TLOG, COMMITTER, level, fmt, ##args)
#define OBLOG_TAILF_LOG(level, fmt, args...) OB_SUB_MOD_LOG(TLOG, TAILF, level, fmt, ##args)
#define _OBLOG_TAILF_LOG(level, fmt, args...) _OB_SUB_MOD_LOG(TLOG, TAILF, level, fmt, ##args)
#define OBLOG_SCHEMA_LOG(level, fmt, args...) OB_SUB_MOD_LOG(TLOG, SCHEMA, level, fmt, ##args)
#define _OBLOG_SCHEMA_LOG(level, fmt, args...) _OB_SUB_MOD_LOG(TLOG, SCHEMA, level, fmt, ##args)

// used for the log return for user;
// if you want to return ERROR message for user, and the error message parameters returned
// in mysql mode and oracle mode are the same. you should use LOG_USER_ERROR or FORWARD_USER_ERROR.
// otherwise, you should use it like below
// if (share::is_oracle_mode()) {
//  LOG_ORACLE_USER_ERROR(...);
// } else {
//  LOG_MYSQL_USER_ERROR(...);
// }
// the LOG_USER_* supports string format,
// while the LOG_USER_*_MSG dose not support and only can be used for rpc proxy on the remote/distribute msg.
#define _LOG_USER_MSG(level, errcode, umsg, args...)                                                        \
  do {                                                                                                      \
    OB_LOGGER.log_user_message(level, errcode, umsg, ##args);                                               \
    (OB_LOGGER.is_async_log_used() ? OB_LOGGER.async_log_message("", OB_LOG_NUM_LEVEL(level), umsg, ##args) \
                                   : OB_LOGGER.log_message("", OB_LOG_NUM_LEVEL(level), umsg, ##args));     \
  } while (0)

//
// const static int const_val = 0;
// __builtin_constant_p(const_val) expected to return 1,
// but we get 0 in g++ 5.2.0 if optimize level under O1 (must be a bug).
// So we disable the constant check in g++ debug compile.
#if defined(__clang__) || (defined(__OPTIMIZE__) && __OPTIMIZE__ >= 1)

#define CHECK_LOG_USER_CONST_FMT(x) \
  static_assert(__builtin_constant_p(x) == 1, "LOG_USER_XX(errcode..) need use const errcode instead of vairable ret");
#else
#define CHECK_LOG_USER_CONST_FMT(x)
#endif

#define LOG_USER(level, errcode, args...)                                                   \
  do {                                                                                      \
    CHECK_LOG_USER_CONST_FMT(errcode)                                                       \
    if (lib::is_oracle_mode()) {                                                            \
      _LOG_USER_MSG(level, errcode, LOG_MACRO_JOIN(errcode, __ORA_USER_ERROR_MSG), ##args); \
    } else {                                                                                \
      _LOG_USER_MSG(level, errcode, LOG_MACRO_JOIN(errcode, __USER_ERROR_MSG), ##args);     \
    }                                                                                       \
  } while (0)
#define LOG_USER_MYSQL(level, errcode, args...)                                       \
  do {                                                                                \
    CHECK_LOG_USER_CONST_FMT(errcode)                                                 \
    _LOG_USER_MSG(level, errcode, LOG_MACRO_JOIN(errcode, __USER_ERROR_MSG), ##args); \
  } while (0)
#define LOG_USER_ORACLE(level, errcode, args...)                                          \
  do {                                                                                    \
    CHECK_LOG_USER_CONST_FMT(errcode)                                                     \
    _LOG_USER_MSG(level, errcode, LOG_MACRO_JOIN(errcode, __ORA_USER_ERROR_MSG), ##args); \
  } while (0)
#define LOG_MYSQL_USER_ERROR(errcode, args...) \
  LOG_USER_MYSQL(::oceanbase::common::ObLogger::USER_ERROR, errcode, ##args)
#define LOG_MYSQL_USER_WARN(errcode, args...) LOG_USER_MYSQL(::oceanbase::common::ObLogger::USER_WARN, errcode, ##args)
#define LOG_MYSQL_USER_NOTE(errcode, args...) LOG_USER_MYSQL(::oceanbase::common::ObLogger::USER_NOTE, errcode, ##args)
#define LOG_ORACLE_USER_ERROR(errcode, args...) \
  LOG_USER_ORACLE(::oceanbase::common::ObLogger::USER_ERROR, errcode, ##args)
#define LOG_ORACLE_USER_WARN(errcode, args...) \
  LOG_USER_ORACLE(::oceanbase::common::ObLogger::USER_WARN, errcode, ##args)
#define LOG_ORACLE_USER_NOTE(errcode, args...) \
  LOG_USER_ORACLE(::oceanbase::common::ObLogger::USER_NOTE, errcode, ##args)
#define LOG_USER_ERROR(errcode, args...) LOG_USER(::oceanbase::common::ObLogger::USER_ERROR, errcode, ##args)
#define LOG_USER_WARN(errcode, args...) LOG_USER(::oceanbase::common::ObLogger::USER_WARN, errcode, ##args)
#define LOG_USER_NOTE(errcode, args...) LOG_USER(::oceanbase::common::ObLogger::USER_NOTE, errcode, ##args)
#define LOG_USER_ERROR_LINE_COLUMN(line, column)                                                   \
  do {                                                                                             \
    OB_LOGGER.log_user_error_line_column(::oceanbase::common::ObLogger::USER_ERROR, line, column); \
  } while (0)
#define LOG_USER_ERROR_WITH_LINE_COL(errcode, line, column, args...)   \
  LOG_USER(::oceanbase::common::ObLogger::USER_ERROR, errcode, ##args) \
  LOG_USER_ERROR_LINE_COLUMN(line, column)

// NOTE: No special reason, please use LOG_USER_ERROR, LOG_USER_WARN, LOG_USER_NOTE
// Three standard interfaces, do not use the following three interfaces.
//
//
// The FORWARD_USER_* interface is only used at the rpc interface layer. The specific application scenarios are as
// follows:
//   After the rpc executes the plan, the remote end returns the rcode structure, which contains the error code and the
//   formatted msg The rpc initiator needs to faithfully return the rcode content to the client, and cannot rebuild it
//   based on errcode.
// That is to say: LOG_USER_* is used for the error record of the initial error point, and FORWARD_USER_* is used to
// pass the error record
//
// For details, refer to deps/oblib/src/rpc/obrpc/ob_rpc_proxy.cpp: log_user_error_and_warn() usage
//
#define FORWARD_USER_ERROR(errcode, args...) \
  _LOG_USER_MSG(::oceanbase::common::ObLogger::USER_ERROR, errcode, "%s", ##args)

#define FORWARD_USER_WARN(errcode, args...) \
  _LOG_USER_MSG(::oceanbase::common::ObLogger::USER_WARN, errcode, "%s", ##args)

#define FORWARD_USER_ERROR_MSG(errcode, fmt, args...) \
  _LOG_USER_MSG(::oceanbase::common::ObLogger::USER_ERROR, errcode, fmt, ##args)

#define FORWARD_USER_NOTE(errcode, msg) \
  OB_LOGGER.log_user_message_info("", ::oceanbase::common::ObLogger::USER_NOTE, OB_LOG_LEVEL_DIRECT(WARN), errcode, msg)

// define USING_LOG_PREFIX in .cpp file to use LOG_ERROR, LOG_WARN ... macros
//
// example:
//    #define USING_LOG_PREFIX COMMON
//    LOG_ERROR(...) will expand to COMMON_LOG(ERROR, ...)

#define LOG_ERROR(args...) LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(ERROR, ##args)
#define _LOG_ERROR(args...) _LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(ERROR, ##args)
#define LOG_WARN(args...) LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(WARN, ##args)
#define _LOG_WARN(args...) _LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(WARN, ##args)
#define LOG_INFO(args...) LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(INFO, ##args)
#define _LOG_INFO(args...) _LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(INFO, ##args)
#define LOG_TRACE(args...) LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(TRACE, ##args)
#define _LOG_TRACE(args...) _LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(TRACE, ##args)
#define LOG_DEBUG(args...) LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(DEBUG, ##args)
#define _LOG_DEBUG(args...) _LOG_MACRO_JOIN(USING_LOG_PREFIX, _LOG)(DEBUG, ##args)

// print expr is human-readable format
#define LOG_PRINT_EXPR(level, statement, expr, args...) \
  LOG_##level(statement, "expr", ::oceanbase::common::ObLogPrintName<__typeof__(expr)>(expr), ##args);

// When key is the name of value, can use K(value) for key and value.
// example:
//   SQL_LOG(INFO, "test for K", K(value));
// When key is the name of a member in class, can use K_
// example:
//   value_ is a member of class T.Then in class T, can use
//   SQL_LOG(INFO, "test for K_", K_(value))
#define K(x) #x, x
#define K_(x) #x, x##_
#define KR(x) #x, x, #x, common::ob_error_name(x)
#define GETK(obj, member) #member, (obj).get_##member()

// If you declare a static const member in Class and do not define it in cpp file,
// you have to use LITERAL_K() to replace K or use static_cast<type> to print the member.
// Defining the member in cpp file is suggested.
#define LITERAL(x) static_cast<__typeof__(x)>(x)
#define LITERAL_(x) static_cast<__typeof__(x##_)>(x##_)
#define LITERAL_K(x) #x, static_cast < __typeof__(x)>(x)
#define LITERAL_K_(x) #x, static_cast < __typeof__(x##_)>(x##_)

// If you want to print the address of a variable with type 'char *' or 'const char *', you
// can use this macro P.
#define OB_P(x) reinterpret_cast<const void*>(x)

#define KP(x) #x, reinterpret_cast < const void*>(x)
#define KP_(x) #x, reinterpret_cast < const void*>(x##_)

// type of x should implement int64_t to_string(char *buf, const int64_t buf_len)
#define PC(x) ::oceanbase::common::ObLogPrintPointerCnt<__typeof__(x)>(x)
#define KPC(x) #x, ::oceanbase::common::ObLogPrintPointerCnt < __typeof__(x)>(x)
#define KPC_(x) #x, ::oceanbase::common::ObLogPrintPointerCnt < __typeof__(x##_)>(x##_)

// type of var should implement get_name(char *buf, const int64_t buf_len, int64_t &pos)
#define PNAME(var) ::oceanbase::common::ObLogPrintName<__typeof__(var)>(var)
#define KPNAME(var) #var, ::oceanbase::common::ObLogPrintName < __typeof__(var)>(var)
#define KPNAME_(var) #var, ::oceanbase::common::ObLogPrintName < __typeof__(var##_)>(var##_)

// print data to hex string, To use this should includ "lib/utility/ob_print_utils.h"
#define PHEX(data, data_size) ::oceanbase::common::ObLogPrintHex((data), (data_size))
#define KPHEX(data, data_size) #data, ::oceanbase::common::ObLogPrintHex((data), (data_size))
#define KPHEX_(data, data_size) #data, ::oceanbase::common::ObLogPrintHex((data##_), (data_size))

// As strerror(err_num) not thread-safe, need to call ERRMSG, KERRMSG to print errmsg of errno.
// And call ERRNOMSG, KERRNOMSG to print errmsg of err_num specified.
#define ERRMSG ::oceanbase::common::ObLogPrintErrMsg()
#define KERRMSG "errmsg", ::oceanbase::common::ObLogPrintErrMsg()

#define ERRNOMSG(num) ::oceanbase::common::ObLogPrintErrNoMsg(num)
#define KERRNOMSG(num) "errmsg", ::oceanbase::common::ObLogPrintErrNoMsg(num)

#endif

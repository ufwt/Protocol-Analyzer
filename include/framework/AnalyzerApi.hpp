// ============================================================================
// Copyright (c) 2017-2018, by Vitaly Grigoriev, <Vit.link420@gmail.com>.
// This file is part of ProtocolAnalyzer open source project under MIT License.
// ============================================================================

#ifndef PROTOCOL_ANALYZER_API_HPP
#define PROTOCOL_ANALYZER_API_HPP

#define PROTOCOL_ANALYZER_VERSION_MAJOR 0
#define PROTOCOL_ANALYZER_VERSION_MINOR 0
#define PROTOCOL_ANALYZER_VERSION_PATCH 10


#include "Log.hpp"  // In this header file also defined "Common.hpp".
#include "Mutex.hpp"
#include "System.hpp"
#include "LockedDeque.hpp"
#include "BinaryStructuredDataEngine.hpp"  // In this header file also defined "BinaryDataEngine.hpp".
#include "Parser.hpp"
#include "Socket.hpp"
#include "Utilities.hpp"
#include "Notification.hpp"


///////////////////   STRUCTURE OF PROTOCOL ANALYZER   ///////////////////
/**
 * @namespace analyzer
 * @brief The main namespace that contains definition of analyzer.
 */
namespace analyzer
{
    /**
     * @namespace framework
     * @brief The namespace that contains definition of framework module of analyzer.
     */
    namespace framework
    {
        /**
         * @namespace system
         * @brief The namespace that contains definition of various core functions.
         */
        namespace system {
        }  // namespace system.
        /**
         * @namespace storage
         * @brief The namespace that contains definition of various framework global storages.
         */
        namespace storage {
        }  // namespace storage.
        /**
         * @namespace callbacks
         * @brief The namespace that contains interfaces of various framework callback types.
         */
        namespace callbacks {
        }  // namespace callbacks.
        /**
         * @namespace modules
         * @brief The namespace that contains identifiers of various framework modules.
         */
        namespace modules {
        }  // namespace modules.
        /**
         * @namespace net
         * @brief The namespace that contains definitions of network transports.
         */
        namespace net
        {
            /**
             * @namespace protocols
             * @brief The namespace that contains definitions of network transports and protocols.
             */
            namespace protocols
            {
                /**
                 * @namespace http
                 * @brief The namespace that contains definitions of HTTP protocols.
                 */
                namespace http {
                }  // namespace http.
            }  // namespace protocols.
        }  // namespace net.
        /**
         * @namespace utility
         * @brief The namespace that contains definition of various utilities.
         */
        namespace utility {
        }  // namespace utility.
        /**
         * @namespace common
         * @brief The namespace that contains definition of common functions.
         */
        namespace common
        {
            /**
             * @namespace types
             * @brief The namespace that contains definition of various framework types.
             */
            namespace types {
            }  // namespace types.
            /**
             * @namespace text
             * @brief The namespace that contains definition of various functions which works with text.
             */
            namespace text {
            }  // namespace text.
            /**
             * @namespace file
             * @brief The namespace that contains definition of various functions which works with files.
             */
            namespace file {
            }  // namespace file.
            /**
             * @namespace convert
             * @brief The namespace that contains definition of various functions which converts various types of data to the desired representation.
             */
            namespace convert {
            }  // namespace convert.
        }  // namespace common.
        /**
         * @namespace log
         * @brief The namespace that contains definition of logging and error classes.
         */
        namespace log {
        }  // namespace log.
        /**
         * @namespace task
         * @brief The namespace that contains definitions of task class.
         */
        namespace task {
        }  // namespace task.
        /**
         * @namespace parser
         * @brief The namespace that contains definitions of various parsers.
         */
        namespace parser{
        }  // namespace parser.
        /**
         * @namespace diagnostic
         * @brief The namespace that contains definitions of diagnostic tools.
         */
        namespace diagnostic {
        }  // namespace diagnostic.
    }  // namespace framework.
}  // namespace analyzer.
///////////////////   STRUCTURE OF PROTOCOL ANALYZER   ///////////////////

#endif  // PROTOCOL_ANALYZER_API_HPP

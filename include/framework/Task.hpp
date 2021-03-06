// ============================================================================
// Copyright (c) 2017-2018, by Vitaly Grigoriev, <Vit.link420@gmail.com>.
// This file is part of ProtocolAnalyzer open source project under MIT License.
// ============================================================================

#ifndef PROTOCOL_ANALYZER_TASK_HPP
#define PROTOCOL_ANALYZER_TASK_HPP

#include <mutex>
#include <atomic>
#include <pthread.h>
#include <unordered_map>

#include "Log.hpp"  // In this header file also defined "Common.hpp".
#include "Notification.hpp"

#define DEFAULT_TIMEOUT_TASK   10  // In seconds.
#define TIMEOUT_TASK_UNLIMITED   0


namespace analyzer::framework::task
{
    using time = std::chrono::system_clock;

    /**
     * @enum TASK_STATUS
     * @brief Statuses of the task used in TaskContext class.
     */
    enum TASK_STATUS : uint16_t
    {
        TASK_STATE_IDLE = 0,         // This state set if the task has not started yet.
        TASK_STATE_ERROR = 1,        // This state set if the task finished with error and wait for return the result.
        TASK_STATE_TIMEOUT = 2,      // This state set if timeout expired (after that the id live 5 seconds).
        TASK_STATE_SKIP = 3,         // This state set if anyone skip the task.
        TASK_STATE_INIT = 4,         // This state set in initializing function.
        TASK_STATE_IN_PROGRESS = 5,  // This state set in start function before start new thread with task.
        TASK_STATE_PENDING = 6,      // This state set in thread after the task finished and wait for return the result.
        TASK_STATE_FINISHED = 7      // This state set in wait functions after the result was returned.
    };

    /**
     * @class TaskContext   Task.hpp   "include/framework/Task.hpp"
     * @brief The context of the new task that determines its status and needed values.
     */
    class TaskContext
    {
    private:
        const std::string workerName;
        mutable time::time_point startTime;
        std::atomic<std::chrono::seconds> timeout;
        std::atomic<TASK_STATUS> status;
        std::atomic<int32_t> exitCode;

    public:
        TaskContext (TaskContext &&) = delete;
        TaskContext (const TaskContext &) = delete;
        TaskContext & operator= (TaskContext &&) = delete;
        TaskContext & operator= (const TaskContext &) = delete;


        explicit TaskContext (std::string name, const uint32_t timeout = DEFAULT_TIMEOUT_TASK) noexcept
                : workerName(std::move(name)), timeout(std::chrono::seconds(timeout)), status(TASK_STATE_IDLE), exitCode(0)
        { }

        inline std::string GetWorkerName(void) const noexcept { return workerName; }

        inline void SetStartTime (const time::time_point start) noexcept
        {
            startTime = start;
            LOG_TRACE("TaskContext.SetStartTime: Task '", workerName, "' start time: ", common::clockToString(startTime), '.');
        }
        inline time::time_point GetStartTime(void) const noexcept { return startTime; }

        inline void SetTimeOut (const std::chrono::seconds n_timeout) noexcept { timeout.store(n_timeout, std::memory_order_release); }
        inline std::chrono::seconds GetTimeOut(void) const noexcept { return timeout.load(std::memory_order_acquire); }

        inline void SetStatus (const TASK_STATUS n_status) noexcept
        {
            status.store(n_status, std::memory_order_seq_cst);
            LOG_TRACE("TaskContext.SetStatus: Task '", workerName, "' changed status to: ", status.load(std::memory_order_seq_cst), '.');
        }
        inline TASK_STATUS GetStatus(void) const noexcept { return status.load(std::memory_order_seq_cst); }

        inline void SetExitCode (const int32_t new_code) noexcept { exitCode.store(new_code, std::memory_order_relaxed); }
        inline int32_t GetExitCode(void) const noexcept { return exitCode.load(std::memory_order_relaxed); }

        virtual ~TaskContext(void) = default;
    };

    /**
     * @typedef typedef void * (*Worker)(void *);
     * @brief The type of the internal thread worker in TaskManager.
     *
     * @note The Worker function starts in new thread.
     */
    using Worker = void * (*) (void *);


    /**
     * @class TaskManager   Task.hpp   "include/framework/Task.hpp"
     * @brief This class defined the work with pool of tasks.
     *
     * @note This class is not thread safe.
     */
    class TaskManager
    {
        using task_value_t = std::pair<pthread_t, TaskContext *>;

    private:
        /**
         * @class ThreadPool   Task.hpp   "include/framework/Task.hpp"
         * @brief This class defined the work with pool of thread IDs.
         *
         * @note It is the internal class of TaskManager class.
         */
        class ThreadPool
        {
            friend class TaskManager;

        private:
            std::mutex work_mutex = { };
            const task_value_t * const null_task_value_t = nullptr;
            std::unordered_map<std::size_t, task_value_t> id_set = { };

        public:
            ThreadPool(void) = default;
            ~ThreadPool(void) = default;

            ThreadPool (ThreadPool &&) = delete;
            ThreadPool (const ThreadPool &) = delete;
            ThreadPool & operator= (ThreadPool &&) = delete;
            ThreadPool & operator= (const ThreadPool &) = delete;


            std::size_t AddID (const task_value_t & /*value*/) noexcept;
            bool RemoveID (std::size_t /*value*/) noexcept;
            const task_value_t & FindID (std::size_t /*identifier*/) noexcept;
        };

        static void signal_handler (int32_t /*sig*/) noexcept;

        [[noreturn]]
        static void * ThreadsManager (void * /*input*/) noexcept;

    private:
        pthread_t manager_thread_id;
        ThreadPool pool = { };

    public:
        TaskManager (TaskManager &&) = delete;
        TaskManager (const TaskManager &) = delete;
        TaskManager & operator= (TaskManager &&) = delete;
        TaskManager & operator= (const TaskManager &) = delete;

        // Constructor.
        TaskManager(void) noexcept;

        // Adding a new task to the pool.
        std::size_t AddTask (Worker * /*worker*/, TaskContext * /*context*/) noexcept;
        // Skip the task.
        void SkipTask (std::size_t /*fd*/) noexcept;

        // Change timeout for certain thread work.
        void ChangeTimeOut (std::size_t /*fd*/, std::chrono::seconds /*timeout*/) noexcept;
        // Wait thread by descriptor (block operation).
        bool Wait (std::size_t /*fd*/) noexcept;
        // Wait all task threads (block operation).
        bool WaitAll(void) noexcept;

        // Destructor.
        ~TaskManager(void) noexcept;
    };

}  // namespace task.


#endif  // PROTOCOL_ANALYZER_TASK_HPP

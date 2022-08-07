#include "MockHeartbeatPublisher.hpp"
#include "MockProgressPublisher.hpp"
#include "MockStatusPublisher.hpp"
#include "MockTaskProvider.hpp"
#include "MockTaskSignalListener.hpp"
#include "MockWorkerSolutionPublisher.hpp"
#include "assfire/logger/impl/spdlog/SpdlogLoggerFactory.hpp"
#include "assfire/optimizer/api/test/MockRouteOptimizer.hpp"
#include "assfire/optimizer/api/test/MockSession.hpp"
#include "assfire/optimizer/worker/Exceptions.hpp"
#include "assfire/optimizer/worker/Worker.hpp"

#include <chrono>
#include <gtest/gtest.h>
#include <memory>

using namespace assfire::optimizer;
using namespace ::testing;
using namespace std::chrono_literals;

class WorkerTest : public ::testing::Test {
  protected:
    static void SetUpTestCase() {
        assfire::logger::SpdlogLoggerFactory::register_static_factory();
    }

    void SetUp() override {
        heartbeat_publisher       = std::make_shared<::testing::NiceMock<MockHeartbeatPublisher>>();
        progress_publisher        = std::make_shared<::testing::NiceMock<MockProgressPublisher>>();
        status_publisher          = std::make_shared<::testing::NiceMock<MockStatusPublisher>>();
        task_provider             = std::make_shared<::testing::NiceMock<MockTaskProvider>>();
        task_signal_listener      = std::make_shared<::testing::NiceMock<MockTaskSignalListener>>();
        worker_solution_publisher = std::make_shared<::testing::NiceMock<MockWorkerSolutionPublisher>>();
        route_optimizer           = std::make_shared<::testing::NiceMock<MockRouteOptimizer>>();

        worker = std::make_shared<Worker>(route_optimizer, task_provider, heartbeat_publisher, progress_publisher, status_publisher,
                                          worker_solution_publisher, task_signal_listener);
    }

    std::shared_ptr<Worker> worker;
    std::shared_ptr<::testing::NiceMock<MockHeartbeatPublisher>> heartbeat_publisher;
    std::shared_ptr<::testing::NiceMock<MockProgressPublisher>> progress_publisher;
    std::shared_ptr<::testing::NiceMock<MockStatusPublisher>> status_publisher;
    std::shared_ptr<::testing::NiceMock<MockTaskProvider>> task_provider;
    std::shared_ptr<::testing::NiceMock<MockTaskSignalListener>> task_signal_listener;
    std::shared_ptr<::testing::NiceMock<MockWorkerSolutionPublisher>> worker_solution_publisher;
    std::shared_ptr<::testing::NiceMock<MockRouteOptimizer>> route_optimizer;
};

TEST_F(WorkerTest, Start_DoubleStartNotAllowed) {
    EXPECT_CALL(*task_signal_listener, next()).WillRepeatedly(Return(TaskSignal(TaskSignal::Type::IGNORE, "2")));

    worker->start();

    EXPECT_THROW(worker->start(), WorkerAlreadyStarted);
}

TEST_F(WorkerTest, Start_LoadedTaskIsPassedToOptimizer) {
    Task task;
    task.set_id("1");

    Task::Orders orders;
    Order order;
    order.set_id(123);
    orders.push_back(order);
    task.set_orders(orders);

    WorkerTask worker_task(task, OptimizationStrategyId("Strategy"));

    EXPECT_CALL(*task_signal_listener, next())
        .WillOnce(Return(TaskSignal(TaskSignal::Type::START, "1")))
        .WillRepeatedly(Return(TaskSignal(TaskSignal::Type::IGNORE, "2")));
    EXPECT_CALL(*task_provider, load("1")).Times(1).WillOnce(Return(worker_task));
    EXPECT_CALL(*route_optimizer, solve(task, OptimizationStrategyId("Strategy"), false))
        .Times(1)
        .WillOnce(Return(std::make_shared<::testing::NiceMock<MockSession>>()));

    worker->start();

    std::this_thread::sleep_for(100ms);
}

TEST_F(WorkerTest, Start_ProgressPublisherIsCorrectlySetForOptimizationSession) {
    Task task;
    task.set_id("1");

    WorkerTask worker_task(task, OptimizationStrategyId("Strategy"));

    EXPECT_CALL(*task_signal_listener, next())
        .WillOnce(Return(TaskSignal(TaskSignal::Type::START, "1")))
        .WillRepeatedly(Return(TaskSignal(TaskSignal::Type::IGNORE, "2")));
    EXPECT_CALL(*task_provider, load("1")).Times(1).WillOnce(Return(worker_task));

    std::shared_ptr<::testing::NiceMock<MockSession>> session = std::make_shared<::testing::NiceMock<MockSession>>();

    EXPECT_CALL(*route_optimizer, solve(task, OptimizationStrategyId("Strategy"), false)).Times(1).WillOnce(Return(session));

    EXPECT_CALL(*progress_publisher, publish("1", 59)).Times(1).WillOnce(Return());

    EXPECT_CALL(*session, set_progress_listener(_)).WillOnce([&](auto listener) { listener(59); });

    worker->start();

    std::this_thread::sleep_for(100ms);
}

TEST_F(WorkerTest, Start_StatusPublisherIsCorrectlySetForOptimizationSession) {
    Task task;
    task.set_id("1");

    WorkerTask worker_task(task, OptimizationStrategyId("Strategy"));

    EXPECT_CALL(*task_signal_listener, next())
        .WillOnce(Return(TaskSignal(TaskSignal::Type::START, "1")))
        .WillRepeatedly(Return(TaskSignal(TaskSignal::Type::IGNORE, "2")));
    EXPECT_CALL(*task_provider, load("1")).Times(1).WillOnce(Return(worker_task));

    std::shared_ptr<::testing::NiceMock<MockSession>> session = std::make_shared<::testing::NiceMock<MockSession>>();

    EXPECT_CALL(*route_optimizer, solve(task, OptimizationStrategyId("Strategy"), false)).Times(1).WillOnce(Return(session));

    EXPECT_CALL(*status_publisher, publish("1", Session::Status::IN_PROGRESS)).Times(1).WillOnce(Return());

    EXPECT_CALL(*session, set_status_listener(_)).WillOnce([&](auto listener) { listener(Session::Status::IN_PROGRESS); });

    worker->start();

    std::this_thread::sleep_for(100ms);
}

TEST_F(WorkerTest, Start_HeartbeatPublisherIsStartedWithWorkerStart) {
    EXPECT_CALL(*task_signal_listener, next()).WillRepeatedly(Return(TaskSignal(TaskSignal::Type::IGNORE, "1")));

    EXPECT_CALL(*heartbeat_publisher, start()).Times(1).WillOnce(Return());

    worker->start();
}

TEST_F(WorkerTest, Shutdown_HeartbeatPublisherIsStoppedOnWorkerShutdown) {
    EXPECT_CALL(*task_signal_listener, next()).WillRepeatedly(Return(TaskSignal(TaskSignal::Type::IGNORE, "1")));

    EXPECT_CALL(*heartbeat_publisher, start()).Times(1).WillOnce(Return());
    EXPECT_CALL(*heartbeat_publisher, stop()).Times(1).WillOnce(Return());

    worker->start();

    std::this_thread::sleep_for(100ms);

    worker.reset();
}

TEST_F(WorkerTest, Shutdown_ActiveSessionsAreJoinedOnWorkerShutdown) {
    Task task;
    WorkerTask worker_task(task, OptimizationStrategyId("Strategy"));

    EXPECT_CALL(*task_signal_listener, next())
        .WillOnce(Return(TaskSignal(TaskSignal::Type::START, "1")))
        .WillOnce(Return(TaskSignal(TaskSignal::Type::START, "2")))
        .WillOnce(Return(TaskSignal(TaskSignal::Type::START, "3")))
        .WillRepeatedly(Return(TaskSignal(TaskSignal::Type::IGNORE, "4")));
    EXPECT_CALL(*task_provider, load("1")).Times(1).WillOnce(Return(worker_task));
    EXPECT_CALL(*task_provider, load("2")).Times(1).WillOnce(Return(worker_task));
    EXPECT_CALL(*task_provider, load("3")).Times(1).WillOnce(Return(worker_task));

    std::condition_variable cv;
    std::mutex mtx;

    std::atomic_int32_t active_sessions(0);

    auto start_func = [&]() {
        ++active_sessions;
    };

    auto waiting_func = [&] {
        std::unique_lock lck(mtx);
        cv.wait(lck);
        --active_sessions;
    };

    std::shared_ptr<::testing::NiceMock<MockSession>> session1 = std::make_shared<::testing::NiceMock<MockSession>>();
    std::shared_ptr<::testing::NiceMock<MockSession>> session2 = std::make_shared<::testing::NiceMock<MockSession>>();
    std::shared_ptr<::testing::NiceMock<MockSession>> session3 = std::make_shared<::testing::NiceMock<MockSession>>();

    EXPECT_CALL(*session1, start()).WillOnce(start_func);
    EXPECT_CALL(*session2, start()).WillOnce(start_func);
    EXPECT_CALL(*session3, start()).WillOnce(start_func);

    EXPECT_CALL(*session1, wait_until_completed()).WillOnce(waiting_func);
    EXPECT_CALL(*session2, wait_until_completed()).WillOnce(waiting_func);
    EXPECT_CALL(*session3, wait_until_completed()).WillOnce(waiting_func);

    EXPECT_CALL(*route_optimizer, solve(_, _, _)).WillOnce(Return(session1)).WillOnce(Return(session2)).WillOnce(Return(session3));

    worker->start();

    std::this_thread::sleep_for(200ms);

    auto ftr = std::async([&] {
        for (int i = 0; i < 3; ++i) {
            std::this_thread::sleep_for(300ms);
            cv.notify_one();
        }
    });

    EXPECT_EQ(active_sessions, 3);
    worker.reset();
    EXPECT_EQ(active_sessions, 0);
}

TEST_F(WorkerTest, Shutdown_NoNewTasksAreAcceptedOnShutdown) {
    Task task;
    WorkerTask worker_task(task, OptimizationStrategyId("Strategy"));

    std::atomic_int32_t counter(1);

    auto listen_func = [&] {
        std::this_thread::sleep_for(200ms);
        return TaskSignal(TaskSignal::Type::START, std::to_string(counter.fetch_add(1)));
    };

    EXPECT_CALL(*task_signal_listener, next()).WillRepeatedly(listen_func);

    EXPECT_CALL(*route_optimizer, solve(_, _, _))
        .Times(2)
        .WillOnce(Return(std::make_shared<::testing::NiceMock<MockSession>>()))
        .WillOnce(Return(std::make_shared<::testing::NiceMock<MockSession>>()));

    worker->start();

    std::this_thread::sleep_for(500ms);
    worker.reset();
}

TEST_F(WorkerTest, Cancel_CancelSignalIsProvidedToSession) {
    EXPECT_CALL(*task_signal_listener, next())
        .WillOnce(Return(TaskSignal(TaskSignal::Type::START, "1")))
        .WillOnce([&] {
            std::this_thread::sleep_for(50ms);
            return TaskSignal(TaskSignal::Type::CANCEL, "1");
        })
        .WillRepeatedly(Return(TaskSignal(TaskSignal::Type::IGNORE, "2")));

    std::shared_ptr<MockSession> session = std::make_shared<::testing::NiceMock<MockSession>>();
    
    EXPECT_CALL(*session, start()).Times(1).WillOnce(Return());
    EXPECT_CALL(*session, cancel()).Times(1).WillOnce(Return());

    EXPECT_CALL(*route_optimizer, solve(_, _, _))
        .Times(1)
        .WillOnce(Return(session));

    worker->start();

    std::this_thread::sleep_for(100ms);
}

TEST_F(WorkerTest, Cancel_CancelIsPossibleOnShutdown) {
    EXPECT_CALL(*task_signal_listener, next())
        .WillOnce(Return(TaskSignal(TaskSignal::Type::START, "1")))
        .WillOnce([&] {
            std::this_thread::sleep_for(500ms);
            return TaskSignal(TaskSignal::Type::CANCEL, "1");
        })
        .WillRepeatedly(Return(TaskSignal(TaskSignal::Type::IGNORE, "2")));

    std::shared_ptr<MockSession> session = std::make_shared<::testing::NiceMock<MockSession>>();
    
    EXPECT_CALL(*session, start()).Times(1).WillOnce(Return());
    EXPECT_CALL(*session, cancel()).Times(1).WillOnce(Return());

    EXPECT_CALL(*route_optimizer, solve(_, _, _))
        .Times(1)
        .WillOnce(Return(session));

    worker->start();
    std::this_thread::sleep_for(100ms);
    worker.reset();
}

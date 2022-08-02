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

#include <gtest/gtest.h>
#include <memory>

using namespace assfire::optimizer;
using namespace ::testing;

class WorkerTest : public ::testing::Test {
  protected:
    static void SetUpTestCase() {
        assfire::logger::SpdlogLoggerFactory::register_static_factory();
    }

    void SetUp() override {
        heartbeat_publisher       = std::make_shared<MockHeartbeatPublisher>();
        progress_publisher        = std::make_shared<MockProgressPublisher>();
        status_publisher          = std::make_shared<MockStatusPublisher>();
        task_provider             = std::make_shared<MockTaskProvider>();
        task_signal_listener      = std::make_shared<MockTaskSignalListener>();
        worker_solution_publisher = std::make_shared<MockWorkerSolutionPublisher>();
        route_optimizer           = std::make_shared<MockRouteOptimizer>();

        worker = std::make_shared<Worker>(route_optimizer, task_provider, heartbeat_publisher, progress_publisher, status_publisher,
                                          worker_solution_publisher, task_signal_listener);
    }

    std::shared_ptr<Worker> worker;
    std::shared_ptr<MockHeartbeatPublisher> heartbeat_publisher;
    std::shared_ptr<MockProgressPublisher> progress_publisher;
    std::shared_ptr<MockStatusPublisher> status_publisher;
    std::shared_ptr<MockTaskProvider> task_provider;
    std::shared_ptr<MockTaskSignalListener> task_signal_listener;
    std::shared_ptr<MockWorkerSolutionPublisher> worker_solution_publisher;
    std::shared_ptr<MockRouteOptimizer> route_optimizer;
};

TEST_F(WorkerTest, Start_DoubleStartNotAllowed) {
    EXPECT_CALL(*task_signal_listener, next()).WillOnce(Return(TaskSignal(TaskSignal::Type::START, "1")));
    EXPECT_CALL(*route_optimizer, solve(_, _, _)).WillOnce(Return(std::make_shared<MockSession>()));

    worker->start();

    EXPECT_THROW(worker->start(), WorkerAlreadyStarted);
}
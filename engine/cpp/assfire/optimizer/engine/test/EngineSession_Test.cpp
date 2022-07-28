#include "MockOptimizationStrategy.hpp"
#include "MockProgressTracker.hpp"
#include "MockSolutionPublisher.hpp"
#include "MockStateManager.hpp"
#include "assfire/optimizer/engine/EngineSession.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace assfire::optimizer;
using namespace testing;

class EngineSessionTest : public ::testing::Test {
  protected:
    void SetUp() override {
        task = std::make_shared<Task>();

        mock_optimization_context = std::make_shared<OptimizationContext>(
            std::make_shared<MockSolutionPublisher>(), std::make_shared<MockStateManager>(), std::make_shared<MockProgressTracker>());

        mock_optimization_strategy = std::make_shared<MockOptimizationStrategy>();
    }

    void create_session() {
        session = std::make_unique<EngineSession>(task, mock_optimization_context, mock_optimization_strategy);
    }

    std::shared_ptr<Task> task;
    std::shared_ptr<OptimizationContext> mock_optimization_context;
    std::shared_ptr<OptimizationStrategy> mock_optimization_strategy;
    std::unique_ptr<Session> session;
};

TEST_F(EngineSessionTest, GetId) {
    task->set_id("some_id");

    create_session();

    EXPECT_EQ(session->id(), "some_id");
}
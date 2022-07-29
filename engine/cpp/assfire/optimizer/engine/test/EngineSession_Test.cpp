#include "MockOptimizationStrategy.hpp"
#include "MockProgressTracker.hpp"
#include "MockSolutionPublisher.hpp"
#include "MockStateManager.hpp"
#include "assfire/optimizer/engine/EngineSession.hpp"
#include "assfire/optimizer/engine/SessionStateError.hpp"

#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <thread>

using namespace assfire::optimizer;
using namespace testing;
using namespace std::chrono_literals;

class EngineSessionTest : public ::testing::Test {
  protected:
    void SetUp() override {
        task = std::make_shared<Task>();

        mock_progress_tracker   = std::make_shared<MockProgressTracker>();
        mock_state_manager      = std::make_shared<MockStateManager>();
        mock_solution_publisher = std::make_shared<MockSolutionPublisher>();

        mock_optimization_context = std::make_shared<OptimizationContext>(mock_solution_publisher, mock_state_manager, mock_progress_tracker);

        mock_optimization_strategy = std::make_shared<MockOptimizationStrategy>();
    }

    void create_session() {
        session = std::make_unique<EngineSession>(task, mock_optimization_context, mock_optimization_strategy);
    }

    std::shared_ptr<Task> task;
    std::shared_ptr<MockProgressTracker> mock_progress_tracker;
    std::shared_ptr<MockSolutionPublisher> mock_solution_publisher;
    std::shared_ptr<MockStateManager> mock_state_manager;
    std::shared_ptr<OptimizationContext> mock_optimization_context;
    std::shared_ptr<MockOptimizationStrategy> mock_optimization_strategy;
    std::unique_ptr<EngineSession> session;
};

TEST_F(EngineSessionTest, Id_EqualsToTaskId) {
    task->set_id("some_id");

    create_session();

    EXPECT_EQ(session->id(), "some_id");
}

TEST_F(EngineSessionTest, CurrentProgress_TakenFromProgressTracker) {
    EXPECT_CALL(*mock_progress_tracker, progress()).Times(2).WillOnce(Return(45)).WillOnce(Return(78));

    create_session();

    EXPECT_EQ(session->current_progress(), 45);
    EXPECT_EQ(session->current_progress(), 78);
}

TEST_F(EngineSessionTest, CurrentStatus_Queued_InProgress_Finished) {
    EXPECT_CALL(*mock_optimization_strategy, solve(_, _)).WillOnce([](auto, auto) { std::this_thread::sleep_for(50ms); });

    create_session();

    EXPECT_EQ(session->current_status(), Session::Status::QUEUED);

    MockFunction<void(Session::Status)> mock_status_listener;
    std::vector<Session::Status> status_transitions;
    EXPECT_CALL(mock_status_listener, Call(_)).WillRepeatedly([&](auto st) { status_transitions.push_back(st); });
    session->set_status_listener(mock_status_listener.AsStdFunction());

    session->start();

    EXPECT_EQ(session->current_status(), Session::Status::IN_PROGRESS);

    session->wait_until_completed();

    EXPECT_EQ(session->current_status(), Session::Status::FINISHED);

    ASSERT_THAT(status_transitions, ElementsAre(Session::Status::QUEUED, Session::Status::IN_PROGRESS, Session::Status::FINISHED));
}

TEST_F(EngineSessionTest, CurrentStatus_Queued_InProgress_Failed) {
    EXPECT_CALL(*mock_optimization_strategy, solve(_, _)).WillOnce(Throw(std::runtime_error("Unexpected exception")));

    create_session();

    EXPECT_EQ(session->current_status(), Session::Status::QUEUED);

    MockFunction<void(Session::Status)> mock_status_listener;
    std::vector<Session::Status> status_transitions;
    EXPECT_CALL(mock_status_listener, Call(_)).WillRepeatedly([&](auto st) { status_transitions.push_back(st); });
    session->set_status_listener(mock_status_listener.AsStdFunction());

    session->start();

    EXPECT_EQ(session->current_status(), Session::Status::IN_PROGRESS);

    session->wait_until_completed();

    EXPECT_EQ(session->current_status(), Session::Status::FAILED);

    ASSERT_THAT(status_transitions, ElementsAre(Session::Status::QUEUED, Session::Status::IN_PROGRESS, Session::Status::FAILED));
}

TEST_F(EngineSessionTest, CurrentStatus_Queued_InProgress_Cancelled) {
    EXPECT_CALL(*mock_optimization_strategy, solve(_, _)).WillOnce([](auto, auto) { std::this_thread::sleep_for(50ms); });

    create_session();

    EXPECT_EQ(session->current_status(), Session::Status::QUEUED);

    MockFunction<void(Session::Status)> mock_status_listener;
    std::vector<Session::Status> status_transitions;
    EXPECT_CALL(mock_status_listener, Call(_)).WillRepeatedly([&](auto st) { status_transitions.push_back(st); });
    session->set_status_listener(mock_status_listener.AsStdFunction());

    session->start();

    EXPECT_EQ(session->current_status(), Session::Status::IN_PROGRESS);

    EXPECT_FALSE(mock_optimization_context->is_interrupted());

    session->cancel();

    EXPECT_TRUE(mock_optimization_context->is_interrupted());

    session->wait_until_completed();

    EXPECT_EQ(session->current_status(), Session::Status::CANCELLED);

    ASSERT_THAT(status_transitions, ElementsAre(Session::Status::QUEUED, Session::Status::IN_PROGRESS, Session::Status::CANCELLED));
}

TEST_F(EngineSessionTest, Start_DoubleStartNotAllowed) {
    EXPECT_CALL(*mock_optimization_strategy, solve(_, _)).WillOnce([](auto, auto) { std::this_thread::sleep_for(50ms); });

    create_session();

    EXPECT_EQ(session->current_status(), Session::Status::QUEUED);

    session->start();

    EXPECT_THROW(session->start(), SessionStateError);

    session->wait_until_completed();

    EXPECT_EQ(session->current_status(), Session::Status::FINISHED);
}

TEST_F(EngineSessionTest, WaitUntilCompleted_WaitingOnNotStartedSessionNotAllowed) {
    EXPECT_CALL(*mock_optimization_strategy, solve(_, _)).WillOnce([](auto, auto) { std::this_thread::sleep_for(50ms); });

    create_session();

    EXPECT_EQ(session->current_status(), Session::Status::QUEUED);

    EXPECT_THROW(session->wait_until_completed(), SessionStateError);
    EXPECT_THROW(session->wait_until_completed_for(50ms), SessionStateError);

    session->start();

    session->wait_until_completed();

    EXPECT_EQ(session->current_status(), Session::Status::FINISHED);
}

TEST_F(EngineSessionTest, Cancel_CancellingInactiveOrFinishedSessionNotAllowed) {
    EXPECT_CALL(*mock_optimization_strategy, solve(_, _)).WillOnce([](auto, auto) { std::this_thread::sleep_for(50ms); });

    create_session();

    EXPECT_EQ(session->current_status(), Session::Status::QUEUED);

    EXPECT_THROW(session->cancel(), SessionStateError);

    session->start();

    session->wait_until_completed();

    EXPECT_EQ(session->current_status(), Session::Status::FINISHED);

    EXPECT_THROW(session->cancel(), SessionStateError);
}

TEST_F(EngineSessionTest, Cancel_CancellingFailedSessionNotAllowed) {
    EXPECT_CALL(*mock_optimization_strategy, solve(_, _)).WillOnce(Throw(std::runtime_error("Unexpected exception")));

    create_session();

    EXPECT_EQ(session->current_status(), Session::Status::QUEUED);

    session->start();

    session->wait_until_completed();

    EXPECT_EQ(session->current_status(), Session::Status::FAILED);

    EXPECT_THROW(session->cancel(), SessionStateError);
}

TEST_F(EngineSessionTest, LatestSolution_IsTakenFromSolutionPublisher) {
    Solution expected_solution;
    expected_solution.set_cost(567);

    EXPECT_CALL(*mock_solution_publisher, latest_solution()).WillOnce(Return(std::nullopt)).WillOnce(Return(expected_solution));

    create_session();

    EXPECT_FALSE(session->latest_solution());
    EXPECT_EQ(session->latest_solution(), expected_solution);
}

TEST_F(EngineSessionTest, SetProgressListener_ListenerPropagatedToProgressTracker) {
    struct signal_exception : public std::logic_error {
        signal_exception(const char* what) : std::logic_error(what) {}
    };

    Session::ProgressListener listener = [](auto) {
        throw signal_exception("S");
    };

    EXPECT_CALL(*mock_progress_tracker, set_progress_listener(_)).Times(1).WillOnce([](Session::ProgressListener f) {
        EXPECT_THROW(f(5), signal_exception);
    });

    create_session();

    session->set_progress_listener(listener);
}

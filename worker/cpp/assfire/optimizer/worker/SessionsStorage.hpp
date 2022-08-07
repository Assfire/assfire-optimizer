#pragma once

#include "assfire/optimizer/api/Session.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace assfire::optimizer {
    class SessionsManager {
      public:
        void clear() {
            _active_sessions.clear();
        }

        void wait_for_all_sessions_to_complete() {
            for (const auto& p : _active_sessions) {
                p.second->wait_until_completed();
            }
        }

        bool cancel_session(const std::string& task_id) {
            auto iter = _active_sessions.find(task_id);
            if (iter == _active_sessions.end()) {
                return false;
            } else {
                iter->second->cancel();
                return true;
            }
        }

        void start_session(std::string task_id, std::shared_ptr<Session> session, Session::ProgressListener progress_listener,
                           Session::StatusListener status_listener) {
            cleanup_finished_sessions();

            session->set_progress_listener(progress_listener);
            session->set_status_listener(status_listener);
            session->start();

            _active_sessions.emplace(std::move(task_id), std::move(session));
        }

        bool contains(const std::string& task_id) const {
            return _active_sessions.contains(task_id);
        }

      private:
        void cleanup_finished_sessions() {
            for (auto it = _active_sessions.begin(); it != _active_sessions.end();) {
                if (it->second->is_in_terminal_state()) {
                    it = _active_sessions.erase(it);
                } else {
                    ++it;
                }
            }
        }

        std::unordered_map<std::string, std::shared_ptr<Session>> _active_sessions;
    };
} // namespace assfire::optimizer
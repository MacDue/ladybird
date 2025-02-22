/*
 * Copyright (c) 2022, Florent Castelli <florent.castelli@gmail.com>
 * Copyright (c) 2022, Linus Groh <linusg@serenityos.org>
 * Copyright (c) 2022, Tim Flynn <trflynn89@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Error.h>
#include <AK/RefPtr.h>
#include <LibWeb/WebDriver/Error.h>
#include <LibWeb/WebDriver/Response.h>
#include <WebDriver/WebContentConnection.h>
#include <unistd.h>

namespace WebDriver {

class Session {
public:
    Session(unsigned session_id, NonnullRefPtr<Client> client, Web::WebDriver::LadybirdOptions options);
    ~Session();

    unsigned session_id() const { return m_id; }

    WebContentConnection& web_content_connection()
    {
        VERIFY(m_web_content_connection);
        return *m_web_content_connection;
    }

    ErrorOr<void> start();
    Web::WebDriver::Response stop();

private:
    NonnullRefPtr<Client> m_client;
    Web::WebDriver::LadybirdOptions m_options;

    bool m_started { false };
    unsigned m_id { 0 };

    RefPtr<WebContentConnection> m_web_content_connection;
    Optional<pid_t> m_browser_pid;
};

}

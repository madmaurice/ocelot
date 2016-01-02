#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"

#include "pch.h"
#include "core/logging/Logger.h"
#include "core/logging/LoggingConfig.h"

using namespace OC;

class LoggingTestFormater : public ILogFormatter
{
public:
    virtual void ApplyFormat(const LogEvent& logEvent, std::ostream& ostream)
    {
        ostream << logEvent.m_message;
    }
};

class LoggingTestAppender : public LogAppenderBase
{
public:
    LoggingTestAppender() : LogAppenderBase(std::make_shared<LoggingTestFormater>())
    {
    }

    virtual std::string GetName() override
    {
        return "LoggingTestAppender";
    }

    virtual void Append(const LogEvent& logEvent) override
    {
        std::stringstream sstream;
        m_formatter->ApplyFormat(logEvent, sstream);
        m_output.push_back(sstream.str());
    }

    uint32 count()
    {
        return m_output.size();
    }
    
    void clear()
    {
        m_output.clear();
    }

    std::vector<std::string> m_output;
};

class LoggingFixture : public ::testing::Test
{
public:
    LoggingFixture() : m_config(LogLevel::Debug)
    {
    }

protected:
    virtual void SetUp()
    {
        m_appender = new LoggingTestAppender();
        m_config.AddAppender(std::unique_ptr<LoggingTestAppender>(m_appender));
        Logger::Init(m_config);
    }

    virtual void TearDown()
    {

    }

    LoggingTestAppender* m_appender;
    LoggingConfig m_config;
};

typedef LoggingFixture LOGGING;

TEST_F(LOGGING, ConfigLogLevel) 
{
    // Debug
    m_config.SetLogLevel(LogLevel::Debug);

    OC_LOG_DEBUG("Test");
    OC_LOG_INFO("Test");
    OC_LOG_WARN("Test");
    OC_LOG_ERROR("Test");
    OC_LOG_ALWAYS("Test");

    EXPECT_EQ(5, m_appender->count());

    // Info
    m_appender->clear();
    m_config.SetLogLevel(LogLevel::Info);

    OC_LOG_DEBUG("Test");
    OC_LOG_INFO("Test");
    OC_LOG_WARN("Test");
    OC_LOG_ERROR("Test");
    OC_LOG_ALWAYS("Test");

    EXPECT_EQ(4, m_appender->count());

    // Warn
    m_appender->clear();
    m_config.SetLogLevel(LogLevel::Warn);

    OC_LOG_DEBUG("Test");
    OC_LOG_INFO("Test");
    OC_LOG_WARN("Test");
    OC_LOG_ERROR("Test");
    OC_LOG_ALWAYS("Test");

    EXPECT_EQ(3, m_appender->count());

    // Error
    m_appender->clear();
    m_config.SetLogLevel(LogLevel::Error);

    OC_LOG_DEBUG("Test");
    OC_LOG_INFO("Test");
    OC_LOG_WARN("Test");
    OC_LOG_ERROR("Test");
    OC_LOG_ALWAYS("Test");

    EXPECT_EQ(2, m_appender->count());

    // Always
    m_appender->clear();
    m_config.SetLogLevel(LogLevel::Always);

    OC_LOG_DEBUG("Test");
    OC_LOG_INFO("Test");
    OC_LOG_WARN("Test");
    OC_LOG_ERROR("Test");
    OC_LOG_ALWAYS("Test");

    EXPECT_EQ(1, m_appender->count());
}

TEST_F(LOGGING, ConfigLogAppender) 
{
    class FakeAppender : public LogAppenderBase
    {
    public:
        virtual String GetName() override
        {
            return "FakeAppender";
        }

        virtual void Append(const LogEvent& logEvent) override
        {
            OC_UNUSED(logEvent);
        }
    };

    const String loggingAppender("LoggingTestAppender");
    const String fakeAppender("FakeAppender");

    ILogAppender* appender = m_config.GetAppender<ILogAppender>(loggingAppender);
    EXPECT_NE(nullptr, appender);

    appender = m_config.GetAppender<ILogAppender>(fakeAppender);
    EXPECT_EQ(nullptr, appender);

    m_config.AddAppender(std::make_unique<FakeAppender>());

    appender = m_config.GetAppender<ILogAppender>(fakeAppender);
    EXPECT_NE(nullptr, appender);

    const Vector<std::unique_ptr<ILogAppender> >& allAppender = m_config.GetAllAppenders();
    EXPECT_EQ(2, allAppender.size());

    m_config.RemoveAppender(fakeAppender);
    EXPECT_EQ(1, allAppender.size());
}

TEST_F(LOGGING, ValidateLogFormat) 
{
    int value = 5;
    OC_LOG_INFO("Test " << value);

    const char* output = m_appender->m_output[0].c_str();
    EXPECT_STREQ("Test 5", output);
}
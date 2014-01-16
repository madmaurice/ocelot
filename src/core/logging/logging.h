
#pragma once

// http://msdn.microsoft.com/en-us/library/b0084kay.aspx

#if defined(_DEBUG)
#define OC_LOG_INFO(msg) oc::Logger::getInstance().info(msg, __FILE__, __LINE__);
#else
#define OC_LOG_INFO(msg) (void)msg;
#endif
namespace cpp logger

struct LogMessage
{
    1:i64 timestamp,
    2:string message
}

struct LogMessageBatch
{
    1:list<LogMessage> msgs
}

exception LoggingException
{
    1:string msg
}

service Logger
{
    void log (1:LogMessage lm);
    void batch (1:LogMessageBatch lmb);
    LogMessage getLastMessage ();
}



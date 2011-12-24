#include "command_handler.impl.h"


CommandHandlerImpl::CommandHandlerImpl()
{
}

bool CommandHandlerImpl::Work(Slice& command)
{
    Slice mid;
    Slice ver;
    if (!GetMIDVer(command, mid, ver))
    {
        return false;
    }
    Serialize(mid, ver);
    return true;
}

bool CommandHandlerImpl::GetMIDVer(Slice& command, Slice& mid, Slice& ver)
{
    token_.reset(command.data(), command.size());
    char ch = 0;
    bool mid_found = false;
    bool ver_found = false;
    while (!token_.isEnd())
    {
        ch = token_.next();
        if ('?' == ch || '&' == ch) //beginning of the keyword
        {
            //qLogTraces(kLogName) << "find " << ch;
            ch = token_.next(); 
            if ('m' == ch) // try to get mid
            {
                //qLogTraces(kLogName) << "find " << ch;
                ch = token_.next();
                if ('=' == ch)//OK find a mid
                {
                    //qLogTraces(kLogName) << "find " << ch << " we try ot get mid";
                    GetMID(command, mid);
                    mid_found = true;
                    if (ver_found)
                    {
                        //qLogTraces(kLogName) << "ver_found=true, break";
                        break;
                    }
                }
                else if ('i' == ch && 
                          token_.next() == 'd' &&
                          token_.next() == '=')
                {
                    //qLogTraces(kLogName) << "find " << ch << " we try ot get mid";
                    GetMID(command, mid);
                    mid_found = true;
                    if (ver_found)
                    {
                        //qLogTraces(kLogName) << "ver_found=true, break";
                        break;
                    }
                }
            }
            else if ('v' == ch) // try to get ver
            {
                if (token_.next() == 'e' &&
                    token_.next() == 'r' &&
                    token_.next() == '=')
                {
                    //qLogTraces(kLogName) << "find " << ch << " we try ot get ver";
                    GetVer(command, ver);
                    ver_found = true;
                    if (mid_found)
                    {
                        //qLogTraces(kLogName) << "mid_found=true, break";
                        break;
                    }
                }

            }
        }
    }//end of while

    if (mid.size() > 0 || ver.size() > 0)
    {
        return true;
    }

    return false;
}


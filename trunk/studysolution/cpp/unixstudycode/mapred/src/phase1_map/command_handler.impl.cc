#include "command_handler.impl.h"


CommandHandlerImpl::CommandHandlerImpl()
{
}

bool CommandHandlerImpl::Work(osl::Slice& command)
{
    osl::Slice mid;
    osl::Slice ver;
    if (!GetMIDVer(command, mid, ver))
    {
        return false;
    }
    //Serialize(mid, ver);
    mid_verset_map[std::string(mid.data(), mid.size())].insert(std::string(ver.data(), ver.size()));
    return true;
}

bool CommandHandlerImpl::GetMIDVer(osl::Slice& command, osl::Slice& mid, osl::Slice& ver)
{
    token_.reset(command.data(), command.size());
    char ch = 0;
    bool mid_found = false;
    bool ver_found = false;
    while (!token_.isEnd())
    {
        ch = tolower(token_.next());
        if ('?' == ch || '&' == ch) //beginning of the keyword
        {
            //qLogTraces(kLogName) << "find " << ch;
            ch = tolower(token_.next()); 
            if ('m' == ch && !mid_found) // try to get mid
            {
                //qLogTraces(kLogName) << "find " << ch;
                ch = tolower(token_.next());
                if ('=' == ch)//OK find a mid
                {
                    //qLogTraces(kLogName) << "find " << ch << " we try ot get mid";
                    GetMID(command, mid);
                    if (mid.size() > 0)
                    {
                        mid_found = true;
                        if (ver_found)
                        {
                            //qLogTraces(kLogName) << "ver_found=true, break";
                            break;
                        }
                    }
                }
                else if ('i' == ch && 
                          tolower(token_.next()) == 'd' &&
                          token_.next() == '=')
                {
                    //qLogTraces(kLogName) << "find " << ch << " we try ot get mid";
                    GetMID(command, mid);
                    if (mid.size() > 0)
                    {
                        mid_found = true;
                        if (ver_found)
                        {
                            //qLogTraces(kLogName) << "ver_found=true, break";
                            break;
                        }
                    }
                }
            }
            else if ('v' == ch && !ver_found) // try to get ver
            {
                if (tolower(token_.next()) == 'e' &&
                    tolower(token_.next()) == 'r' &&
                    token_.next() == '=')
                {
                    //qLogTraces(kLogName) << "find " << ch << " we try ot get ver";
                    GetVer(command, ver);
                    if (ver.size() > 0)
                    {
                        ver_found = true;
                        if (mid_found)
                        {
                            //qLogTraces(kLogName) << "mid_found=true, break";
                            break;
                        }
                    }
                }
            }
        }
    }//end of while

    if (mid.size() > 0)
    {
        return true;
    }

    return false;
}


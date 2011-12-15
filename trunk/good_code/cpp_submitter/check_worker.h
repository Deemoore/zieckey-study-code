/*
 * =====================================================================================
 *
 *       Filename:  check_worker.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/26/2011 12:58:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xinjie Li ((jasonli)), xjason.li@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CLOUD_SCAN_CHECK_WORKER_H_
#define CLOUD_SCAN_CHECK_WORKER_H_

#include <string>
#include <vector>

class CheckWorkerFile {
public:
    CheckWorkerFile(int argc, char** argv);
    ~CheckWorkerFile();

    bool Init();
    bool Init(const std::string& directory, const std::string& prefix);

    bool Create();
    bool Remove();

    std::string GetPath() const;
    std::string GetCmd() const;

private:
    std::vector<std::string> argv_;
    std::string directory_;
    std::string prefix_;
    int pid_;
};

#endif // CLOUD_SCAN_CHECK_WORKER_H_

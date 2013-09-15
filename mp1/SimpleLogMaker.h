//
//  SimpleLogMaker.h
//  
//
//  Created by Genevieve LaBelle on 9/14/13.
//  Copyright (c) 2013 University of Illinois Urbana-Champaign. All rights reserved.
//

#ifndef _SimpleLogMaker_h
#define _SimpleLogMaker_h


#include <string>
using namespace std;

class SimpleLogMaker
{
public:
    enum severity{
        normal,
        notification,
        warning,
        error,
        critical
    };
    
    SimpleLogMaker();
    int RandomSeverityLogs(int numLines, char* filename);
    int RareLogs(int numLines, char* filename);
};


#endif

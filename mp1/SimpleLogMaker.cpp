//
//  simplelogger.cpp
//  
//
//  Created by Genevieve LaBelle on 9/14/13.
//  Copyright (c) 2013 University of Illinois Urbana-Champaign. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include "SimpleLogMaker.h"

#include <string>
#include <vector>
using namespace std;

SimpleLogMaker::SimpleLogMaker()
{
    return;
}

/*
 * Generates numLines number of files with random severity,
 * and "This is just a test" repeated 0-10 times in the value.
 * 1,000,000 lines is ~50mB
 */
int SimpleLogMaker::RandomSeverityLogs(int numLines, char* filename)
{
    ofstream log1 (filename);
    
    string severity_levels[] = {
        "normal",
        "notification",
        "warning",
        "error",
        "critical"
    };
    
    if (log1.is_open())
    {
        string key;
        string value;
        for(int i = 0; i<numLines; i++)
        {
            key = severity_levels[rand()%5];
            value = "This is just a test";
            log1 << key << ":";
            for(int i = 0; i<(rand()%10); i++)
            {
                log1 << value;
            }
            log1 << "\n";
        }
        log1.close();
    }
    else 
    {
        cout << "Unable to open file: " << filename << "\n";
        return 0;
    }
    return 1;
    
}

/* 
 * Creates file with numLines logs of normal to error keys
 * Creates 3 "rare" critical logs, one in beginning, middle
 * and end.
 */
int SimpleLogMaker::RareLogs(int numLines, char* filename)
{
    
    ofstream log1 (filename);
    
    string severity_levels[] = {
        "normal",
        "notification",
        "warning",
        "error",
        "critical"
    };
    
    if (log1.is_open())
    {
        string value = "This is just a test";
        string key = severity_levels[critical];
        log1 << key << ":" << value << "\n";
        
        int i;
        for(i = 0; i<numLines/2; i++)
        {
            key = severity_levels[rand()%4];
            log1 << key << ":";
            for(int i = 0; i<(rand()%10); i++)
            {
                log1 << value;
            }
            log1 << "\n";
        }
        
        key = severity_levels[critical];
        log1 << key << ":" << value << "\n";
        
        for(i; i<numLines; i++)
        {
            key = severity_levels[rand()%4];
            log1 << key << ":";
            for(int i = 0; i<(rand()%10); i++)
            {
                log1 << value;
            }
            log1 << "\n";
        }
        
        key = severity_levels[critical];
        log1 << key << ":" << value << "\n";
        
        log1.close();
    }
    else 
    {
        cout << "Unable to open file: " << filename << "\n";
        return 0;
    }
    return 1;
}

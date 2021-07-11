/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, <your name here if you made a change>
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/

#pragma once
/*
 * Elements:
 *      Control -            Permissions
 *      Asset -              Message: Messages now have a member called control.
 *      Subject Control -    User: Authenticate has been changed to return a Control
 *      Security Condition - Defined below for reading and writing
 *      Integration -        Handled in Step 4. Leverage the Security Condition.
 */

using namespace std;

enum Control{
    PUBLIC = 0,
    CONFIDENTIAL = 1,
    PRIVILEDGED = 2,
    SECRET = 3
};

extern Control globalSubjectControl;

class Security{
    public:
        
        static bool securityConditionRead(Control asset, Control subject) {
            return asset <= subject;
            
    }

        static bool securityConditionWrite(Control asset, Control subject) {
            return asset >= subject;
    }
};



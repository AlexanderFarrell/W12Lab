/***********************************************************************
 * COMPONENT:
 *    MESSAGES
 * Author:
 *    Br. Helfrich, <your name here if you made a change>
 * Summary:
 *    This class stores the notion of a collection of messages
 ************************************************************************/

#include <string>     // for convenience
#include <list>       // to store the messages
#include <iostream>   // standard input and output
#include <fstream>    // the messages are read from a file
#include <cassert>    // because I am paraniod
#include "control.h"  // all the Bell-LaPadula code
#include "message.h"  // all the code about a single message
#include "messages.h" // a collection messages

using namespace std;
Control globalSubjectControl;

/***********************************************
 * MESSAGES :: DISPLAY
 * display the list of messages
 ***********************************************/
void Messages::display() const
{
    for (list <Message> :: const_iterator it = messages.begin();
         it != messages.end();
         ++it)
         {
             if(!Security::securityConditionRead(it->getAssetControl(), globalSubjectControl)){
                    continue;
                }
            it->displayProperties();
         }
}

/***********************************************
 * MESSAGES :: SHOW
 * show a single message
 **********************************************/
void Messages::show(int id) const
{
    for (list <Message> :: const_iterator it = messages.begin();
         it != messages.end();
         ++it)
        {
            if (it->getID() == id){
               
                if(!Security::securityConditionRead(it->getAssetControl(), globalSubjectControl)){
                    cout<< "You do not have read access for this message";
                    break;
                }
                
                it->displayText();
            }
        }
}

/***********************************************
 * MESSAGES :: UPDATE
 * update one single message
 ***********************************************/
void Messages::update(int id, const string & text)
{
    for (list <Message> :: iterator it = messages.begin();
         it != messages.end();
         ++it)
        {
            if (it->getID() == id){
                if(!Security::securityConditionWrite(it->getAssetControl(), globalSubjectControl)){
                    cout<< "You do not have write access for this message";
                    break;
                }
                it->updateText(text);
            }
        }
}

/***********************************************
 * MESSAGES :: REMOVE
 * remove a single message
 **********************************************/
void Messages::remove(int id)
{
    for (list <Message> :: iterator it = messages.begin();
         it != messages.end();
         ++it)
        {
            if (it->getID() == id){
                if(!Security::securityConditionWrite( it->getAssetControl(), globalSubjectControl)){
                    cout<< "You do not have permission to delete this message";
                    break;
                }
                it->clear();
            }
                
        }
}

/***********************************************
 * MESSAGES :: ADD
 * add a new message
 **********************************************/
void Messages::add(const string & text,
                   const string & author,
                   const string & date,
                   const Control & assetControl)
{
    Message message(text, author, date, assetControl);
    messages.push_back(message);
}

/***********************************************
 * MESSAGES :: READ MESSAGES
 * read the messages from a file
 ***********************************************/
void Messages::readMessages(const char * fileName)
{
    // open the file
    ifstream fin(fileName);
    if (fin.fail())
    {
        cout << "ERROR! Unable to open file "
             << fileName
             << endl;
        return;
    }

    // continue reading until we fail
    while (!fin.fail() && !fin.eof())
    {
        string author;
        string date;
        string text;
        string textControl;
        getline(fin, textControl, '|');
        getline(fin, author, '|');
        getline(fin, date, '|');
        getline(fin, text);

        if (!fin.fail())
        {
            Message message(text, author, date, globalSubjectControl);
            messages.push_back(message);
        }
    }

    // close up shop!
    fin.close();
}
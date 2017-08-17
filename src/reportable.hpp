/*
 * Base klasse for klasser med raport funksjon
*/
#ifndef REPORTABLE_HPP
#define REPORTABLE_HPP
#include <sstream>

class reportable{
    std::stringstream report_;//holder informasjon om alt som skjer
public:
    void report(const std::string s);//skriver til raport
    const std::string get_report();//henter ut raporten, resetter raporten
};

#endif // REPORTABLE_HPP


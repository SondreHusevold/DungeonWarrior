#include "reportable.hpp"

void reportable::report(const std::string s){
    if(!(s.size()>0))//legger ikke til en tom string
        return;
    if(report_.str().size()>0)//legger til linjeskift hvis det er noe i loggen fra før
        report_<<"\n";
    report_<<s;
}

const std::string reportable::get_report(){
    const std::string temp=report_.str();
    report_.str("");//resetter loggen
    return temp;
}

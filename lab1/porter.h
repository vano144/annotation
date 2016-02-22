#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
//block of regular expressions of porters'algorithm
boost::regex REFLEXIVE("сь$|ся$");
boost::regex PERFECTIVEGEROUND("((ив|ивши|ившись|ыв|ывши|ывшись)|((?<=а|я)(в|вши|вшись)))$");
boost::regex ADJECTIVE("(ее|ие|ые|ое|ими|ыми|ей|ий|ый|ой|ем|им|ым|ом|его|ого|ему|ому|их|ых|ую|юю|ая|яя|ою|ею)$");
boost::regex PARTICIPLE ("((ивш|ывш|ующ)|((?<=а|я)(ем|нн|вш|ющ|щ)))$");
boost::regex VERB ("((ила|ыла|ена|ейте|уйте|ите|или|ыли|ей|уй|ил|ыл|им|ым|ен|ило|ыло|ено|ят|ует|уют|ит|ыт|ены|ить|ыть|ишь|ую|ю)|((?<=а|я)(ла|на|ете|йте|ли|й|л|ем|н|ло|но|ет|ют|ны|ть|ешь|нно)))$");
boost::regex NOUN ("(а|ев|ов|ие|ье|е|иями|ями|ами|еи|ии|и|ией|ей|ой|ий|й|иям|ям|ием|ем|ам|ом|о|у|ах|иях|ях|ы|ь|ию|ью|ю|ия|ья|я)$");
boost::regex SUPERLATIVE("(ейш|ейше)$");
boost::regex DERIVATIONAL("(ост|ость)$");
boost::regex I("и$");
boost::regex NN("((?<=н)н)$");
boost::regex SOFT("$ь");
boost::regex RV("(^.*?(?=и|у|е|э|о|а|ы|я|ю))");
// here 4 steps of porters algotihms
void step1(std::string* str) {
    std::string check;
    check=boost::regex_replace(*str, RV, "");
    if (boost::regex_search(check,PERFECTIVEGEROUND)) {
        *str=boost::regex_replace(*str, PERFECTIVEGEROUND, "");
    } else {
        *str=boost::regex_replace(*str, REFLEXIVE, "");
    }
    check=boost::regex_replace(*str, RV, "");
    if (boost::regex_search(check,ADJECTIVE)) {
        *str=boost::regex_replace(*str, ADJECTIVE, "");
        return;
    }
    if (boost::regex_search(check,VERB)) {
        *str=boost::regex_replace(*str, VERB, "");
        return;
    }
    if (boost::regex_search(check,NOUN)) {
        *str=boost::regex_replace(*str, NOUN, "");
        return;
    }
}
void step2(std::string* str) {
    std::string check;
    check=boost::regex_replace(*str, RV, "");
    if (boost::regex_search(check,I)) {
        *str=boost::regex_replace(*str, I, "");
        return;
    }
}
void step3(std::string* str) {
    std::string check;
    check=boost::regex_replace(*str, RV, "");
    check=boost::regex_replace(check, RV, "");
    check=boost::regex_replace(check, RV, "");
    if (boost::regex_search(check,DERIVATIONAL)) {
        *str=boost::regex_replace(*str, DERIVATIONAL, "");
        return;
    }
}
void step4(std::string* str) {
    std::string check;
    check=boost::regex_replace(*str, RV, "");
    if (boost::regex_search(check,NN)) {
        *str=boost::regex_replace(*str, NN, "");
        return;
    }
    if (boost::regex_search(check,SUPERLATIVE)) {
        *str=boost::regex_replace(*str, SUPERLATIVE, "");
        return;
    }
    if (boost::regex_search(check,SOFT)) {
        *str=boost::regex_replace(*str, SOFT, "");
        return;
    }
}
void porter(std::string* str) {
    boost::algorithm::to_lower(*str);
    if ((str)->length()/2<=3) return;
    step1(str);
    step2(str);
    step3(str);
    step4(str);
    
}
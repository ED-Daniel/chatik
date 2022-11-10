#ifndef VUEX_H
#define VUEX_H

#include <QString>

class Vuex
{
public:
    static Vuex& Instance() {
        static Vuex vuex;
        return vuex;
    }

    QString serverIp = "127.0.0.1";
    quint16 port = 45678;
    QString username = "Unkown User";

private:
    Vuex() {}
    ~Vuex() {}
    Vuex(const Vuex&);
    Vuex& operator=(const Vuex&);
};

#endif // VUEX_H

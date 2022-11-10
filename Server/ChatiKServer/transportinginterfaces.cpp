#include"transportinginterfaces.h"

BasicMessage::BasicMessage(SocketEvents event)
{
    jsonObject.insert("event", event);
    document.setObject(jsonObject);
}

BasicMessage::BasicMessage(QByteArray basicMessage)
{
    QJsonParseError parseError;
    document = QJsonDocument::fromJson(basicMessage, &parseError);
    jsonObject = document.object();
}

BasicMessage::BasicMessage(QJsonObject basicObject) {
    jsonObject = basicObject;
    document.setObject(jsonObject);
}

QByteArray BasicMessage::getBytes() const
{
    QByteArray bytes(document.toJson(QJsonDocument::Indented));
    return bytes;
}

int BasicMessage::getEvent() const
{
    return jsonObject["event"].toInt();
}

QJsonObject BasicMessage::getJsonObject() const
{
    return jsonObject;
}

ClientInfo::ClientInfo(QString name, QString ip, QString connectedTime, ClientStatuses status) : BasicMessage(SocketEvents::UPDATE_CLIENTS) {
    jsonObject.insert("name", name);
    jsonObject.insert("ip", ip);
    jsonObject.insert("connected_time", connectedTime);
    jsonObject.insert("status", status);

    document.setObject(jsonObject);
}

ClientInfo::ClientInfo(QByteArray fromJson) : BasicMessage(fromJson) {}
ClientInfo::ClientInfo(QJsonObject fromObject) : BasicMessage(fromObject) {}

QString ClientInfo::getName() const
{
    return jsonObject["name"].toString();
}

QString ClientInfo::getIp() const {
    return jsonObject["ip"].toString();
}

QString ClientInfo::getConnectedTime() const {
    return jsonObject["connected_time"].toString();
}

int ClientInfo::getStatus() const {
    return jsonObject["status"].toInt();
}

JoinInfo::JoinInfo(QString name) : BasicMessage(SocketEvents::JOIN) {
    jsonObject.insert("name", name);

    document.setObject(jsonObject);
}

JoinInfo::JoinInfo(QByteArray bytes) : BasicMessage(bytes) {}

QString JoinInfo::getName() const {
    return jsonObject["name"].toString();
}

std::string unixTimeToHumanReadable(quint64 seconds)
{

    // Save the time in Human
    // readable format
    std::string ans = "";

    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    long int currYear, daysTillNow, extraTime, extraDays,
        index, date, month, hours, minutes, secondss,
        flag = 0;

    // Calculate total days unix time T
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;

    // Calculating current year
    while (true) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0 && currYear % 100 != 0)) {
            if (daysTillNow < 366) {
                break;
            }
            daysTillNow -= 366;
        }
        else {
            if (daysTillNow < 365) {
                break;
            }
            daysTillNow -= 365;
        }
        currYear += 1;
    }
    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;

    if (currYear % 400 == 0
        || (currYear % 4 == 0 && currYear % 100 != 0))
        flag = 1;

    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {

            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays - daysOfMonth[index] < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {

            if (extraDays - daysOfMonth[index] < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }

    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }

    // Calculating HH:MM:YYYY
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;

    ans += std::to_string(date);
    ans += "/";
    ans += std::to_string(month);
    ans += "/";
    ans += std::to_string(currYear);
    ans += " ";
    ans += std::to_string(hours);
    ans += ":";
    ans += std::to_string(minutes);
    ans += ":";
    ans += std::to_string(secondss);

    // Return the time
    return ans;
}

ClientsInfo::ClientsInfo(QList<ClientInfo *> clientsInfo) : BasicMessage(SocketEvents::UPDATE_CLIENTS)
{
    QJsonArray clients;
    for (const auto client : clientsInfo) {
        clients.append(client->getJsonObject());
    }
    jsonObject.insert("clients", clients);
    document.setObject(jsonObject);
}

ClientsInfo::ClientsInfo(QByteArray fromJson) : BasicMessage(fromJson) {}

QJsonArray ClientsInfo::getClients() const
{
    return jsonObject["clients"].toArray();
}


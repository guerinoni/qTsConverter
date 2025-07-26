#pragma once

#include <QString>
#include <vector>

struct TranslationMessage {
    QString identifier; // attribute of message: optional
    QString source;
    QString translation;
    QString translationtype; // attribute of translation: {empty = finished,
                             // unfinished, vanished, obsolete}
    QString comment;
    QString extracomment;
    QString translatorcomment;
    std::vector<std::pair<QString, QString>> locations;
};

struct TranslationContext {
    QString name;
    std::vector<TranslationMessage> messages;
};

using Translations = std::vector<TranslationContext>;

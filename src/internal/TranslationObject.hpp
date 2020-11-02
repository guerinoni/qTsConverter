#pragma once

#include <QString>
#include <vector>

struct TranslationMessage {
    QString source;
    QString translation;
    std::vector<std::pair<QString, int>> locations;
};

struct TranslationContext {
    QString name;
    std::vector<TranslationMessage> messages;
};

using Translations = std::vector<TranslationContext>;

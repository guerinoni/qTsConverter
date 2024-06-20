#pragma once

#include "InOutParameter.hpp"
#include "TranslationObject.hpp"
#include "HeaderObject.hpp"

#include <QString>

struct Result {
    explicit Result(QString &&err, Translations &&tr, InOutParameter &&par, Header &&hd) :
        error{ std::move(err) }, translantions{ std::move(tr) }, params{std::move(par) }, header{std::move(hd)}
    {
    }

    QString error;
    Translations translantions;
    InOutParameter params;
    Header header;
};

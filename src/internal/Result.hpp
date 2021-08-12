#pragma once

#include "InOutParameter.hpp"
#include "TranslationObject.hpp"

#include <QString>

struct Result {
    explicit Result(QString &&err, Translations &&tr, InOutParameter &&par) :
        error{ std::move(err) }, translantions{ std::move(tr) }, params{
            std::move(par)
        }
    {
    }

    QString error;
    Translations translantions;
    InOutParameter params;
};

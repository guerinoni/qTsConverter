#pragma once

#include "InOutParameter.hpp"
#include "RootObject.hpp"
#include "TranslationObject.hpp"

#include <QString>

struct Result {
    explicit Result(QString &&err, Translations &&tr, InOutParameter &&par,
                    RootAttr &&rt) :
        error{ std::move(err) },
        translantions{ std::move(tr) }, params{ std::move(par) }, root{
            std::move(rt)
        }
    {
    }

    QString error;
    Translations translantions;
    InOutParameter params;
    RootAttr root;
};

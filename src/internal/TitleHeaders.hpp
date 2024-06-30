#pragma once

struct TitleHeader {
    static constexpr char Context[]             = "Context";
    static constexpr char ID[]                  = "ID";
    static constexpr char Source[]              = "Source";
    static constexpr char Translation[]         = "Translation";
    static constexpr char Location[]            = "Location";
    static constexpr char TsVersion[]           = "TsVersion";
    static constexpr char Language[]            = "language";
    static constexpr char SourceLanguage[]      = "sourcelanguage";
    static constexpr char Comment[]             = "comment";
    static constexpr char ExtraComment[]        = "extracomment";
    static constexpr char TranslatorComment[]   = "translatorcomment";
    static constexpr char TranslationType[]     = "TranslationType";
};


/* 

EXAMPLE - Expanded

<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="de" sourcelanguage="en">
<context>
    <name>context a</name>
    <message id = "-1">
        <location filename="../dir/file.ui" line="26"/>
        <source>source example</source>
		<comment>comment example</comment>
		<extracomment>extra comment example</extracomment>
		<translatorcomment>translator comment example</translatorcomment>
        <translation>translation example</translation>
		<translation type="unfinished"></translation>
		<translation type="vanished">Beispiel1</translation>
		<translation type="obsolete">Beispiel2</translation>
    </message>
</context>
</TS>
 */

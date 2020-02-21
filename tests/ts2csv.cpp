#include "../src/Ts2CsvConverter.hpp"
#include "Catch2/include/catch.hpp"

#include <QFile>

SCENARIO("file ts convert to csv", "[ts2csv]")
{
    GIVEN("a .ts input file")
    {
        const auto inputFile{ FILESPATH + std::string("/scenario1.ts") };

        AND_GIVEN("a .csv output file")
        {
            WHEN("Ts2CsvConverter is used to process")
            {
                Ts2CsvConverter ts2csv(inputFile, FILESPATH, ";", "\"");
                ts2csv.process();

                THEN("there is a csv file")
                {
                    const auto outputFile{ FILESPATH +
                                           std::string("/output.csv") };
                    QFile f(outputFile.c_str());
                    REQUIRE(f.exists());
                    REQUIRE(f.remove());
                }
            }
        }
    }
}

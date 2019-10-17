#include "../src/Ts2CsvConverter.hpp"
#include "Catch2/include/catch.hpp"

SCENARIO("file ts convert to csv", "[ts2csv]")
{
    GIVEN("a .ts input file")
    {
        std::string input_file = "files/scenario1.ts";

        AND_GIVEN("a .csv output file")
        {
            std::string output_file = "files/scenario1.csv";

            WHEN("Ts2CsvConverter is used to process")
            {
                //                Ts2CsvConverter ts2csv(input_file,
                //                output_file); ts2csv.process();

                //                THEN("there is a csv file") {}
            }
        }
    }
}
